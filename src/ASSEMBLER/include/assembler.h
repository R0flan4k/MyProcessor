#ifndef ASSEMBLER_H
    #define ASSEMBLER_H

    #include "hash.h"

    enum ConvertErrors {
        NO_ERRORS,
    };

    enum ASSEMBLER_COMMANDS {
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
    };

    struct AssemblerCommand {
        const char * command;
        int num_of_params;
        size_t size;
        Hash_t hash;
        ASSEMBLER_COMMANDS command_number;
    };

    const size_t MAX_COMMAND_SIZE = 16;

    ConvertErrors assembler_convert(char const * const * pointers, size_t strings_num, char * output_buffer, AssemblerCommand * commands_array[], size_t commands_array_size);

#endif // ASSEMBLER_H
