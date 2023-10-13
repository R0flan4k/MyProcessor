all:
	make --directory="./src/SPU/"
	make --directory="./src/ASSEMBLER/"
clean:
	make --directory="./src/SPU/" clean
	make --directory="./src/ASSEMBLER/" clean

