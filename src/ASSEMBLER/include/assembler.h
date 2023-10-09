#ifndef ASSEMBLER_H
    #define ASSEMBLER_H

    #include "hash.h"
    #include "stack.h"

    enum AssemblerErrors {
        NO_ERRORS,
        POP_ERROR,
    };

    enum PushMode {
        PUSH_NUMBER   = 1,
        PUSH_REGISTER = 2,
    };

    enum AssemblerCommands {
        HLT =  -1,
        PUSH = 1,
        ADD =  2,
        SUB =  3,
        MUL =  4,
        DIV =  5,
        SQRT = 6,
        SIN =  7,
        COS =  8,
        IN =   9,
        OUT =  10,
        POP =  11,
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
        AssemblerCommands command_number;
    };

    struct AssemblerRegister {
        const char * rgstr;
        const Hash_t hash;
        Elem_t value;
        AssemblerRegisters ip;
    };

    extern AssemblerCommand ASSEMBLER_PUSH;
    extern AssemblerCommand ASSEMBLER_ADD;
    extern AssemblerCommand ASSEMBLER_SUB;
    extern AssemblerCommand ASSEMBLER_MUL;
    extern AssemblerCommand ASSEMBLER_DIV;
    extern AssemblerCommand ASSEMBLER_SQRT;
    extern AssemblerCommand ASSEMBLER_SIN;
    extern AssemblerCommand ASSEMBLER_COS;
    extern AssemblerCommand ASSEMBLER_IN;
    extern AssemblerCommand ASSEMBLER_OUT;
    extern AssemblerCommand ASSEMBLER_HLT;
    extern AssemblerCommand ASSEMBLER_POP;
    extern AssemblerRegister ASSEMBLER_RAX;
    extern AssemblerRegister ASSEMBLER_RBX;
    extern AssemblerRegister ASSEMBLER_RCX;
    extern AssemblerRegister ASSEMBLER_RDX;
    extern AssemblerRegister ASSEMBLER_IP;

    const size_t MAX_COMMAND_SIZE = 16;

    AssemblerErrors assembler_convert(char const * const * pointers, size_t strings_num, char * output_buffer);

#endif // ASSEMBLER_H
