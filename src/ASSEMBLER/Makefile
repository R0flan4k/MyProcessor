CC = g++
FLAGS = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
IFLAGS = -Iinclude -I../config/include -I../MyStack/include
CONFIGDIR = ../config
OBJDIR = ./obj
ASSEMBLER = assembler
FILEPROCESSING = file_processing
MYASSERT = my_assert
STRINGS = strings
HASH = hash
CMDINPUT = cmd_input
CONVERTOR = convertor
PFLAGS = flags
OBJECTS = $(OBJDIR)/$(ASSEMBLER).o $(OBJDIR)/$(FILEPROCESSING).o $(OBJDIR)/$(MYASSERT).o $(OBJDIR)/$(STRINGS).o $(OBJDIR)/$(CMDINPUT).o $(OBJDIR)/$(HASH).o $(OBJDIR)/$(CONVERTOR).o $(OBJDIR)/$(PFLAGS).o

all: $(OBJECTS)
	@$(CC) $(OBJECTS) -o assembler

$(OBJDIR)/$(ASSEMBLER).o: $(ASSEMBLER).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(FILEPROCESSING).o: $(CONFIGDIR)/$(FILEPROCESSING).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(CMDINPUT).o: $(CONFIGDIR)/$(CMDINPUT).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(HASH).o: $(CONFIGDIR)/$(HASH).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(MYASSERT).o: $(CONFIGDIR)/$(MYASSERT).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(STRINGS).o: $(CONFIGDIR)/$(STRINGS).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(CONVERTOR).o: $(CONVERTOR).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

$(OBJDIR)/$(PFLAGS).o: $(PFLAGS).cpp
	@$(CC) $(FLAGS) $(IFLAGS) -c $^  -o $@

clean:
	@rm -f $(OBJDIR)/*.o *~ core *~ *.exe
