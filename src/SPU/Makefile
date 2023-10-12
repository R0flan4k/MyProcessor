CC = g++
FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
IFLAGS = -Iinclude -I../config/include -I../MyStack/include
STKDIR = ../MyStack
OBJDIR = ./obj
CONFIGDIR = ../config
SPU = spu
FILEPROCESSING = file_processing
ARITHMETIC = arithmetic
STACK = stack
VERIFICATOR = vtor
MYASSERT = my_assert
CMDINPUT = cmd_input
HASH = hash
PFLAGS = flags
STACKHASH = stack_hash
OBJECTS = $(OBJDIR)/$(SPU).o $(OBJDIR)/$(STACK).o $(OBJDIR)/$(VERIFICATOR).o $(OBJDIR)/$(MYASSERT).o $(OBJDIR)/$(CMDINPUT).o $(OBJDIR)/$(HASH).o $(OBJDIR)/$(ARITHMETIC).o $(OBJDIR)/$(FILEPROCESSING).o $(OBJDIR)/$(PFLAGS).o $(OBJDIR)/$(STACKHASH).o

all: $(OBJECTS)
	@$(CC) $(OBJECTS) -o spu

$(OBJDIR)/$(SPU).o: $(SPU).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(FILEPROCESSING).o: $(CONFIGDIR)/$(FILEPROCESSING).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(ARITHMETIC).o: $(ARITHMETIC).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(STACK).o: $(STKDIR)/$(STACK).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(VERIFICATOR).o: $(STKDIR)/$(VERIFICATOR).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(MYASSERT).o: $(CONFIGDIR)/$(MYASSERT).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(CMDINPUT).o: $(CONFIGDIR)/$(CMDINPUT).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(HASH).o: $(CONFIGDIR)/$(HASH).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(PFLAGS).o: $(PFLAGS).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(STACKHASH).o: $(STKDIR)/$(STACKHASH).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

clean:
	@rm -f $(OBJDIR)/*.o *~ core *~ *.exe
