CC='wine ../tools/mwcceppc.exe'

$CC -I- -i ../loader -i ../k_stdlib -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o kamekLoader.o kamekLoader.cpp
$CC -I- -i ../loader -i ../k_stdlib -Cpp_exceptions off -enum int -Os -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -c -o nsmbw.o nsmbw.cpp

../Kamek kamekLoader.o nsmbw.o -static=0x80001900 -output-code=loader.bin -output-riiv=loader.xml -valuefile=Code/loader.bin