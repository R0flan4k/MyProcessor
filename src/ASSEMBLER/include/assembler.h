#ifndef ASSEMBLER_H
    #define ASSEMBLER_H

    #include "hash.h"
    #include "stack.h"

    enum AssemblerErrors {
        NO_ERRORS      = 0,
        POP_ERROR      = 1,
        PUSH_ERROR     = 1 << 1,
        ARGUMENT_ERROR = 1 << 2,
    };

    enum PushMode {
        PUSH_NUMBER   = 1,
        PUSH_REGISTER = 2,
    };

    enum ProcessorCommands {
        HLT =  -1,
        PUSH =  1,
        ADD =   2,
        SUB =   3,
        MUL =   4,
        DIV =   5,
        SQRT =  6,
        SIN =   7,
        COS =   8,
        IN =    9,
        OUT =   10,
        POP =   11,
    };

    enum AssemblerSignatures {
        REGISTER = 1,
        NUMBER   = 1 << 1,
        EMPTY    = 1 << 2,
    };

    enum AssemblerRegisters {
        RAX = 1,
        RBX = 2,
        RCX = 3,
        RDX = 4,
        IP =  5,
    };

    struct AssemblerCommand {
        const char * command;
        int num_of_params;
        size_t size;
        const Hash_t hash;
        int signature;
        ProcessorCommands command_number;
    };

    struct AssemblerRegister {
        const char * rgstr;
        const Hash_t hash;
        AssemblerRegisters id;
    };

    extern AssemblerCommand ASSEMBLER_COMMANDS_ARRAY[];
    extern size_t ASSEMBLER_COMMANDS_ARRAY_SIZE;

    const size_t MAX_COMMAND_SIZE = 16;

    AssemblerErrors assembler_convert(char const * const * pointers, size_t strings_num, char * output_buffer);
    AssemblerErrors assembler_argument_processing(const char * * buffer, char * * output_buffer, int signature);
    AssemblerCommand assembler_create_command(const char * command_str, int signature, ProcessorCommands id, int number_of_params);
    AssemblerRegister assembler_create_register(const char * register_str, AssemblerRegisters id);

#endif // ASSEMBLER_H
