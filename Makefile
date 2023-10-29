all:
	make --directory="./src/SPU/"
	make --directory="./src/ASSEMBLER/"
clean:
	make --directory="./src/SPU/" clean
	make --directory="./src/ASSEMBLER/" clean

factorial:
	@./src/ASSEMBLER/assembler.exe --source ./src/factorial.txt --target ./src/target.bin
	@./src/SPU/spu.exe --source ./src/target.bin

run:
	@./src/ASSEMBLER/assembler.exe --source ./src/source.txt --target ./src/target.bin
	@./src/SPU/spu.exe --source ./src/target.bin
