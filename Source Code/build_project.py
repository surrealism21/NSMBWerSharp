import filecmp
import xml.etree.ElementTree as ET
import os
import sys
import subprocess

print("Building XML:", sys.argv[1])
if sys.argv:
    tree = ET.parse(sys.argv[1])
    root = tree.getroot()
else:
    print("Error: no xml specified")

# Template
#CPP = "tools/mwcceppc -I- -i ../k_stdlib -i ../include -Cpp_exceptions off -enum int -Os  -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 %CFLAGS% -c -o"
#ASM = "tools/mwasmeppc -I- -i ../k_stdlib -i ../include -c -o"

import shutil
from pathlib import Path

# disable the cache if you're changing this
nocache = False
code_to_run = ""
all_build = ""
bindef =  "-select-version=P1  -select-version=P2  -select-version=E1 -select-version=E2  -select-version=J1  -select-version=J2 -select-version=K -select-version=W -externals=externals.txt -versions=versions-nsmbw.txt -output-kamek=build\\$KV$.bin"

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

# subprocess suppresses the thing where it whines about it existing here
# can you tell me if this works? it should, but, uh, yeah.
subprocess.run(["mkdir", "build"], stderr=subprocess.DEVNULL)
subprocess.run(["mkdir", "build/obj"], stderr=subprocess.DEVNULL)
# korean
subprocess.run(["mkdir", "build/obj/KW"], stderr=subprocess.DEVNULL)


# File finder
# this really just finds a few headers the game basically NEEDS, and we do things with them later anyway
# NOTE: i am updating this build system, and at the moment, this is the only updated code!

class includeFile:
    filename = "game.hpp"
    path = str()

    def __init__(self, filename):
        self.filename = filename
        self.path = self.findInInclude()

    def findInInclude(self):
        for include in meta.findall("include"):
            p = include.text
            if Path(p+"\\"+self.filename).is_file():
                print(p+"\\"+self.filename)
                return p+"\\"+self.filename
        
    def checkIfChanged(self):
        cachePath = sourceDirName+"\\cache\\"+self.filename
        if Path(cachePath).is_file():
            if not filecmp.cmp(cachePath, self.path, False):
                return True


def promptUser(filename):
    answer = input("You seem to have changed "+filename+". Sometimes you have to recompile some files for no symbol mismatches to occur. Do you want to rebuild? [Y/n]")
    if answer == "Y" or answer == "y":
        return True

gameHpp = includeFile("game.hpp")
gameChanged = gameHpp.checkIfChanged()
if (gameChanged):
    nocache = promptUser(gameHpp.filename)

profileBuild = False

profileidHpp = includeFile("profileid.hpp")
asmProfiles = includeFile("asm_profiles.S")

if (profileidHpp.checkIfChanged() or asmProfiles.checkIfChanged()):
    # this one doesn't even need a noto it's so minor
    profileBuild = True

def appendAll(list1):
    returner = list()
    for string in list1:
        returner.append(string)
    
    return returner

def buildCppBuildDef(region):
    BuildDef = list()
    #BuildDef.append("wine")
    BuildDef.append("tools\\mwcceppc.exe")
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
    BuildDef.append("-D"+region)
    
    return BuildDef

def buildAsmBuildDef():
    BuildDef = list()
    #BuildDef.append("wine")
    BuildDef.append("tools\\mwasmeppc.exe")
    BuildDef.append("-I-")

    for include in meta.findall("include"):
        BuildDef.append("-i")
        BuildDef.append(include.text)
    
    return BuildDef

from subprocess import PIPE

def buildAndCheck(BuildDef, child):
    print(BuildDef)
    process = subprocess.Popen(BuildDef, stdin=PIPE, stdout=PIPE, text=True)

    outputTuple = process.communicate()

    if len(outputTuple[0]) > 0:
        print(outputTuple[0])
        print("Adding the \"erroneous\" tag to this file. It will always compile for debugging.")
        child.attrib = {"erroneous": "true"}
        print("Configured to exit here...")
        exit()
    else:
        child.attrib = {}

"""REGION_K is the only special one added right now."""

for child in modules:
    CachePath = sourceDirName+"/cache/"+child.text
    SrcPath = sourceDirName+"/"+child.text


    tag = child.tag
    data = child.text
    attrib = child.attrib

    if child.tag == "build":
        if ".cpp" in child.text:
            BuildDef = buildCppBuildDef("ALL")
        elif ".S" in child.text:
            BuildDef = buildAsmBuildDef()
        else:
            print("Error: unknown file extension")
            quit()
        
    # the required shit
    BuildDef.append("-c")
    BuildDef.append("-o")
        
    o_file_path = "build/obj/"
    o_file = o_file_path
    o_file += child.text + ".o"
    all_build += o_file+" "

    BuildDef.append(o_file)
            
    BuildDef.append(SrcPath)

    if(child.attrib == {"erroneous": "true"}):
        buildAndCheck(BuildDef, child)
            
    if Path(CachePath).is_file() and Path(o_file).is_file() and nocache == False:
        if not filecmp.cmp(CachePath, SrcPath, shallow=False):
            buildAndCheck(BuildDef, child)
    else:
        buildAndCheck(BuildDef, child)


version_km = "-select-version=P1 -select-version=E1 -select-version=J1 -select-version=E2 -select-version=J2 -select-version=P2"


Kmdef = "Kamek.exe "+all_build+version_km+" "+bindef
print(Kmdef)
# subprocess doesn't like this at all, too long probably.
os.system(Kmdef)

all_build = str()

for child in modules:
    CachePath = sourceDirName+"/cache/"+child.text
    SrcPath = sourceDirName+"/"+child.text


    tag = child.tag
    data = child.text
    attrib = child.attrib

    if child.tag == "build":
        if ".cpp" in child.text:
            BuildDef = buildCppBuildDef("REGION_K")
        elif ".S" in child.text:
            BuildDef = buildAsmBuildDef()
        else:
            print("Error: unknown file extension")
            quit()
        
    # the required shit
    BuildDef.append("-c")
    BuildDef.append("-o")
        
    o_file_path = "build/obj/KW/"
    o_file = o_file_path
    o_file += child.text + ".o"
    all_build += o_file+" "

    BuildDef.append(o_file)
            
    BuildDef.append(SrcPath)

    if(child.attrib == {"erroneous": "true"}):
        buildAndCheck(BuildDef, child)

    # lazy profile build hardcode
    if(child.text == "profile.cpp" or child.text == "profile.S"):
        buildAndCheck(BuildDef, child)
            
    if Path(CachePath).is_file() and Path(o_file).is_file() and nocache == False:
        if not filecmp.cmp(CachePath, SrcPath, shallow=False):
            buildAndCheck(BuildDef, child)
    else:
        buildAndCheck(BuildDef, child)


version_km = "-select-version=K -select-version=W"


Kmdef = "Kamek.exe "+all_build+version_km+" "+bindef
print(Kmdef)
# subprocess doesn't like this at all, too long probably.
os.system(Kmdef)


src = sourceDirName
dest = sourceDirName+"\\cache"
src_files = os.listdir(src)

os.system("rmdir /s /q \""+dest+"\"")
shutil.copytree(src, dest, dirs_exist_ok=True)
shutil.copyfile(gameHpp.path, dest+"\\"+gameHpp.filename)
shutil.copyfile(profileidHpp.path, dest+"\\"+profileidHpp.filename)
shutil.copyfile(asmProfiles.path, dest+"\\"+asmProfiles.filename)

tree.write(sys.argv[1])
print("All done!")