#ifndef ASSEMBLER_H
    #define ASSEMBLER_H

    #include "hash.h"
    #include "stack.h"
    #include "processor.h"

    typedef int Label_t;

    enum AssemblerErrors {
        ASSEMBLER_NO_ERRORS      = 0,
        ASSEMBLER_POP_ERROR      = 1 << 0,
        ASSEMBLER_PUSH_ERROR     = 1 << 1,
        ASSEMBLER_ARGUMENT_ERROR = 1 << 2,
        ASSEMBLER_LABEL_ERROR    = 1 << 3,
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
    void assembler_dump(char const * const * pointers, size_t strings_num, const char * output_buffer, size_t buffer_size);

#endif // ASSEMBLER_H
