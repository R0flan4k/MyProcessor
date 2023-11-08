all:
	make --directory="./SPU/"
	make --directory="./ASSEMBLER/"
clean:
	make --directory="./SPU/" clean
	make --directory="./ASSEMBLER/" clean
	@rm -f AsmBin/*.bin

factorial:
	@./ASSEMBLER/assembler.exe --source ./AsmSrc/factorial.txt --target ./AsmBin/factorial.bin
	@./SPU/spu.exe --source ./AsmBin/factorial.bin

quadratic:
	@./ASSEMBLER/assembler.exe --source ./AsmSrc/quadratic_equation.txt --target ./AsmBin/quadratic_equation.bin
	@./SPU/spu.exe --source ./AsmBin/quadratic_equation.bin

run:
	@./ASSEMBLER/assembler.exe --source ./AsmSrc/source.txt --target ./AsmBin/source.bin
	@./SPU/spu.exe --source ./AsmBin/source.bin
