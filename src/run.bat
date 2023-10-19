@echo off
cd ASSEMBLER
make
assembler.exe --source ../source.txt --target ../target.bin
cd ..
cd SPU
make
spu.exe --source ../target.bin
cd ..
