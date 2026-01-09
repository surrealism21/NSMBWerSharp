import os
import subprocess
import shutil
import sys
import re
import filecmp
import xml.etree.ElementTree as ET
from io import StringIO
from pathlib import Path
from subprocess import PIPE

region_friendly_names = {"REGION_GENERIC": "generic" or "p", "REGION_KW": "kor" or "twn" or "kw"}
region_kamek_names = {
    "REGION_GENERIC": ["-select-version=P1", "-select-version=E1", "-select-version=J1", "-select-version=E2", "-select-version=J2", "-select-version=P2"],
    "REGION_KW": ["-select-version=K", "-select-version=W"]
}

# this makes the script cross-platform
# why did i make this a class? so i can reference stuff from one place
class OSInfo:
    OS = str()
    slash = str() # just assume windows lmao
    dollar = "\\$" # never even used i think???
    wine = bool()

    def __init__(self):
        if os.name == "nt": # windows
            self.OS = "windows"
            self.slash = "\\"
        elif os.name == "posix":
            # actually, this also applies to macos. but why would i even
            self.OS = "linux"
            self.slash = "/"
            self.wine = True
            # check for wine as it produces some... wonderful errors if missing
            if not shutil.which("wine"):
                print("Please install Wine, it is currently not installed and is needed for the compiler/assembler")
                quit()
        else:
            print("WHAT ARE YOU DOING???")
            quit()

s = OSInfo()

# arguments


if(sys.argv.__contains__("--help")):
    print("NSMBWer# build script help")
    print("--------------------------")
    print("Run this file with a project xml file name, and, maybe some of these arguments:")
    print("NOTE: these args can be passed into the bash script, it only has the XML predefined!")
    print("--nocache: Disables the \"cache\" folder, generally everything will rebuild. Does not delete the cache in the process.")
    print("--profileBuild: Forcefully rebuilds the profiles.")
    print("--nocompression: Disables Kamekfile compression, erasing the need for nsmblib. 🤓☝️ \"But it saves about 50% of the file size!!!\"")
    print("NOTE: Disabling compression may break the loader unless you undefine COMPRESSION in nsmbw.cpp. A solution for this is being developed along with a loader build script.")
    print("--------------------------")
    print("Other stuff: This program features a cache in the source directory, but it really caches more than just the source files.")
    print("The .mta file is a \"meta xml\". It contains some ugly information you may not want to see in your version. You can still view it, but only the real XML matters...")

# disable the cache if you're changing this
nocache = False
if(sys.argv.__contains__("--nocache")):
    nocache = True

profileBuild = False
if(sys.argv.__contains__("--profileBuild")):
    profileBuild = True

compression = True
if(sys.argv.__contains__("--nocompression")):
    compression = False


########################
# OTHER PREBUILD STUFF #
########################

def appendAll(list1):
    returner = list()
    for string in list1:
        returner.append(string)
    
    return returner


#subprocess suppresses the thing where it whines about it existing here
subprocess.run(["mkdir", "build"], stderr=subprocess.DEVNULL)
subprocess.run(["mkdir", "build"+s.slash+"obj"], stderr=subprocess.DEVNULL)


#########
# Files #
#########

def promptUser(text):
    answer = input(text+" [Y/n]")
    if answer == "Y" or answer == "y":
        return True
    else:
        return False

class file:
    path = str()
    cachePath = str()
    exists = bool()
    filename = str()

    def __init__(self, filename, cached=True):
        self.filename = filename
        # nasty HACK but idc
        if cached:
            self.cachePath = sourceDirName+s.slash+"cache"+s.slash+filename

    def checkIfChanged(self):
        if Path(self.cachePath).is_file():
            if not filecmp.cmp(self.cachePath, self.path, False):
                    return True
        else:
            return True
    
    # a hack for the xml file, since it contains the source directory. Actually, all these weird cache things are hacks for the xml.
    # Seriously, don't use this!!! It is only defined for files that use "cached=False" in the constructor and is worthless, ~99% of the time!
    def setcachepath(self):
        self.cachePath = sourceDirName+s.slash+"cache"+s.slash+self.filename

    # this caches a file (but not the xml haha)
    def cache(self):
        dest = sourceDirName+s.slash+"cache"
        shutil.copyfile(self.path, dest+s.slash+self.filename)
    
    def cacheWipe(self):
        os.remove(self.cachePath)


##################
# XML PROCESSING #
##################

xml = file(sys.argv[1], cached=False)
reallytho = re.search("^.*\\.xml$", xml.filename)

if not reallytho:
    # NASTY HACK
    if xml.filename != "--help":
        print("Error: No XML specified")
        quit()

metaxml = file(sys.argv[1]+".mta", cached=False)
metaxml_exists = False

flushCache = False
if xml.checkIfChanged():
    flushCache = True
    # Ts is. A hack
    if Path(metaxml.filename).is_file():
        os.remove(metaxml.filename)

print(xml.checkIfChanged())

if Path(metaxml.filename).is_file():
    metaxml_exists = True
    tree = ET.parse(metaxml.filename)
else:
    tree = ET.parse(xml.filename)

print("Parsing and building: "+xml.filename)
if metaxml_exists:
    print("Using metaxml v1")

root = tree.getroot()

# check for meta data
meta = root.find("meta")
modules = root.find("modules")

if meta is None:
    print("Error: no meta section")
    quit()

if meta.find("include") is None:
    print("Error: no include folders")
    quit()

if meta.find("src") is None:
    print("Error: no source folder")
    quit()

if modules is None:
    print("Error: no modules section created")
    quit()

sourceDirName = meta.find("src").text
xml.setcachepath()

if flushCache and Path("src"+s.slash+"cache").is_file():
    shutil.rmtree(sourceDirName+s.slash+"cache")

#################
# Files, cont'd #
#################

# note: IMPORTANT include files only!
class includeFile(file):

    def __init__(self, filename):
        super().__init__(filename)
        self.filename = filename
        self.path = self.findInInclude()

    def findInInclude(self):
        for include in meta.findall("include"):
            p = include.text
            if Path(p+s.slash+self.filename).is_file():
                #print(self.filename+"... found!")
                self.exists = True
        if(self.exists):
            return p+s.slash+self.filename
        else:
            promptUser(self.filename+" was not found. This file may be required! Continue?")

# some checks n shit
gameHpp = includeFile("game.hpp")
if (gameHpp.checkIfChanged()):
    nocache = promptUser("game.hpp has been altered. Some files may break if you do not recompile all. Recompile?")

profileBuild = False

profileidHpp = includeFile("profileid.hpp")
asmProfiles = includeFile("asm_profiles.S")

if (profileidHpp.checkIfChanged() or asmProfiles.checkIfChanged()):
    # this one doesn't even need a noto it's so minor
    print("Rebuilding profiles as they have been altered")
    profileBuild = True

class codeFile(file):
    objPath = str()
    region = str()

    def __init__(self, filename, region):
        super().__init__(filename)
        self.region = region
        self.filename = filename
        self.path = self.findInSrc()

        # object path
        # i know this is evil
        self.objPath = "build"+s.slash+"obj"+s.slash+self.region+s.slash+self.filename+".o"
    
    def findInSrc(self):
        for src in meta.findall("src"):
            p = src.text
            if Path(p+s.slash+self.filename).is_file():
                #print(self.filename+"... found!")
                self.exists = True
                return p+s.slash+self.filename

class cppFile(codeFile):
    BuildDef = list()

    def __init__(self, filename, region):
        super().__init__(filename, region)
        self.BuildDef = self.getBuildDef()

    def getBuildDef(self):
        BuildDef = list()
        if(s.wine):
            BuildDef.append("wine")
        BuildDef.append("tools"+s.slash+"mwcceppc.exe")
        BuildDef.append("-I-")

        for include in meta.findall("include"):
            BuildDef.append("-i")
            BuildDef.append(include.text)
        
        #some other crap before C flags
        crap = ["-Cpp_exceptions", "off", "-enum", "int", "-Os", "-use_lmw_stmw", "on", "-fp", "hard", "-rostr", "-sdata", "0", "-sdata2", "0"]
        BuildDef += appendAll(crap)

        # C flags
        for define in meta.findall("define"):
            BuildDef.append("-D"+define.text) # yes this is intended
        BuildDef.append("-D"+self.region)

        BuildDef.append("-c")
        BuildDef.append("-o")

        BuildDef.append(self.objPath)
        BuildDef.append(self.path)
        
        return BuildDef

class asmFile(codeFile):
    BuildDef = list()

    def __init__(self, filename, region):
        super().__init__(filename, region)
        self.BuildDef = self.getBuildDef()

    # These are pretty poorly made here, honestly.
    def getBuildDef(self):
        BuildDef = list()
        if(s.wine):
            BuildDef.append("wine")
        BuildDef.append("tools"+s.slash+"mwasmeppc.exe")
        BuildDef.append("-I-")

        for include in meta.findall("include"):
            BuildDef.append("-i")
            BuildDef.append(include.text)

        BuildDef.append("-c")
        BuildDef.append("-o")
        
        BuildDef.append(self.objPath)
        BuildDef.append(self.path)
        
        return BuildDef
    
def prep_builddef(child, region):
    if ".cpp" in child.text:
        file = cppFile(child.text, region)
    elif ".S" in child.text:
        file = asmFile(child.text, region)
    else:
        print("Error: unknown file extension")
        quit()
    return file


##############
# BUILD ZONE #
##############

def build_objects(region, SHUTUP=False):
    DidSomething = False
    o_files = list()
    # regional build folders
    subprocess.run(["mkdir", "build"+s.slash+"obj"+s.slash+region], stderr=subprocess.DEVNULL)

    for child in modules:
        file = "a file. totally"

        # generic regions
        # ensure it's a build tag via regex, generic does not discriminate
        # this implementation of this function is STILL weird okay

        txt = child.tag
        x = re.search("^(build)", txt)

        generic = False
        if x and region == "REGION_GENERIC":
            generic = True
            file = prep_builddef(child, region)
        
        # make sure all regions are after the generic one because it will override the generic one then!
        if txt == "build_"+region_friendly_names["REGION_KW"] and region == "REGION_KW":
            file = prep_builddef(child, region)
        
        KWOverride = False
        if txt == "build_"+region_friendly_names["REGION_KW"]:
            KWOverride = True

        if file != "a file. totally" and (file.checkIfChanged() or nocache == True):
            if DidSomething == False:
                DidSomething = True # this is a edgecase
            if not SHUTUP:
                #print("Building "+file.filename+" for "+region)
                print(file.BuildDef)
                process = subprocess.Popen(file.BuildDef, stdin=PIPE, stdout=PIPE, text=True)
                outputTuple = process.communicate()

                if len(outputTuple[0]) > 0:
                    print(outputTuple[0])
                    print("Configured to exit here...")
                    exit()

        # yea this is evil
        if file != "a file. totally":
            if SHUTUP:
                if not (generic and KWOverride):
                    o_files.append(file.objPath)
            else:
                o_files.append(file.objPath)

    if not DidSomething and not SHUTUP:
        print("Did not do anything for "+region+" because all its files were already built.")
    
    return o_files

# pads a region's special o files with the international ones, that it does not replace
def get_worldwide_ofiles(my_files, generic_objects=None):
    # fail save
    if generic_objects is None:
        generic_objects = build_objects("REGION_GENERIC", SHUTUP=True)

    my_files += generic_objects
    return my_files


def link_objects(region, o_files):
    # I don't actually know what's up with the slashes on these, so i'm just manually setting them.
    crap = str()
    KmDef = list()

    # The program itself + garbage
    if s.OS == "windows":
        crap = "-output-kamek=build\\$KV$.bin"
        KmDef.append("Kamek.exe")
    else:
        crap = "-output-kamek=build/$KV$.bin"
        KmDef.append("./Kamek")
    
    KmDef += o_files
    KmDef.append("-externals=externals.txt")
    KmDef.append("-versions=versions-nsmbw.txt")
    KmDef += region_kamek_names[region]
    KmDef.append(crap)
    Kamek = subprocess.Popen(KmDef, text=True)
    Kamek.communicate()

generic_objects = build_objects("REGION_GENERIC")
kw_objects = build_objects("REGION_KW")
kw_objects = get_worldwide_ofiles(kw_objects)

link_objects("REGION_GENERIC", generic_objects)
link_objects("REGION_KW", kw_objects)

# TODO: quit program if there's an error in the 

# copy the REAL xml with all the slop to this extra file
tree.write(metaxml.filename)

# The build process is done, time to copy everything.
src = sourceDirName
dest = sourceDirName+s.slash+"cache"
src_files = os.listdir(src)

# delete existing cache because shutil can uh... do SCARY THINGS! don't say boob without the last b scariest shit ever
if s.OS == "windows":
    os.system("rmdir /s /q \""+dest+"\"")
else:
    os.system("rm -rf "+dest)

shutil.copytree(src, dest, dirs_exist_ok=True)
# i'm lazy
shutil.copyfile(xml.filename, dest+s.slash+xml.filename)
gameHpp.cache()
profileidHpp.cache()
asmProfiles.cache()

# compress code
if compression:
    import nsmblib
    import glob

    print("Code compression...")

    binFilter = "build"+s.slash+"*.bin"

    for filename in glob.glob(binFilter):
        print("Compressing: "+filename)

        with open(filename, "rb") as f:
            file_bytes = f.read()
            compressed = nsmblib.compress11LZS(file_bytes)

        with open(filename+".LZ", "wb") as cf:
            cf.write(compressed)
        
        os.remove(filename)