@echo off
cd ASSEMBLER
make
assembler.exe --source ../source.txt --target ../target.txt
cd ..
cd SPU
make
spu.exe --source ../target.txt
cd ..