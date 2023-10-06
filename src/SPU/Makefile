CC = g++
FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
IFLAGS = -Iinclude
STKDIR = ./MyStack
OBJDIR = ./obj
SPU = spu
FILEPROCESSING = file_processing
ARITHMETIC = arithmetic
STACK = stack
VERIFICATOR = vtor
MYASSERT = my_assert
CMDINPUT = cmd_input
HASH = hash
OBJECTS = $(OBJDIR)/$(SPU).o $(OBJDIR)/$(STACK).o $(OBJDIR)/$(VERIFICATOR).o $(OBJDIR)/$(MYASSERT).o $(OBJDIR)/$(CMDINPUT).o $(OBJDIR)/$(HASH).o $(OBJDIR)/$(ARITHMETIC).o $(OBJDIR)/$(FILEPROCESSING).o

all: $(OBJECTS)
	$(CC) $(OBJECTS) -o spu

$(OBJDIR)/$(SPU).o: $(SPU).cpp
	$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(FILEPROCESSING).o: $(FILEPROCESSING).cpp
	$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(ARITHMETIC).o: $(ARITHMETIC).cpp
	$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(STACK).o: $(STKDIR)/$(STACK).cpp
	$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(VERIFICATOR).o: $(STKDIR)/$(VERIFICATOR).cpp
	$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(MYASSERT).o: $(STKDIR)/$(MYASSERT).cpp
	$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(CMDINPUT).o: $(CMDINPUT).cpp
	$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(HASH).o: $(STKDIR)/$(HASH).cpp
	$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

clean:
	rm -f $(OBJDIR)/*.o *~ core *~ *.exe
