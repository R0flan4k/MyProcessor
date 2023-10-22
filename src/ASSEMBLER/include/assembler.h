#ifndef ASSEMBLER_H
    #define ASSEMBLER_H

    #include "hash.h"
    #include "stack.h"
    #include "processor.h"

    typedef int Label_t;

    enum AssemblerErrors {
        NO_ERRORS      = 0,
        POP_ERROR      = 1,
        PUSH_ERROR     = 1 << 1,
        ARGUMENT_ERROR = 1 << 2,
        INVALID_LABEL  = 1 << 3,
    };

    enum PushMode {
        PUSH_NUMBER   = 1,
        PUSH_REGISTER = 2,
    };

    enum AssemblerSignatures {
        REGISTER = 1,
        NUMBER   = 1 << 1,
        LABEL    = 1 << 2,
        EMPTY    = 1 << 3,
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
        ProcessorRegisters id;
    };

    extern AssemblerCommand ASSEMBLER_COMMANDS_ARRAY[];
    extern size_t ASSEMBLER_COMMANDS_ARRAY_SIZE;

    const size_t MAX_COMMAND_SIZE = 16;

    AssemblerErrors assembler_convert(char const * const * pointers, size_t strings_num, char * output_buffer);
    AssemblerErrors assembler_argument_processing(const char * * buffer, char * * output_buffer, int signature);
    AssemblerCommand assembler_create_command(const char * command_str, int signature, ProcessorCommands id, int number_of_params);
    AssemblerRegister assembler_create_register(const char * register_str, ProcessorRegisters id);

#endif // ASSEMBLER_H
