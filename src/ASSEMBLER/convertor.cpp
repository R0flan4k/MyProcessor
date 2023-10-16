#include <stdio.h>
#include <string.h>

#include "assembler.h"
#include "hash.h"
#include "my_assert.h"
#include "strings.h"
#include "stack.h"

AssemblerCommand ASSEMBLER_COMMANDS_ARRAY[] = {
//     #define assembler_create_command(str, sgnt, id, param_num)
//     {
//         .command = command_str,
//         .num_of_params = number_of_params,
//         .hash = calculate_hash(const_cast <char *> (command_str), sizeof(command_str)),
//         .signature = signature,
//         .command_number = id,
//     },
//
//     #include "commands.h"
//
//     #undef assembler_create_command













    assembler_create_command("push", NUMBER | REGISTER, PUSH, 1),
    assembler_create_command("add",  EMPTY,             ADD,  0),
    assembler_create_command("sub",  EMPTY,             SUB,  0),
    assembler_create_command("mul",  EMPTY,             MUL,  0),
    assembler_create_command("div",  EMPTY,             DIV,  0),
    assembler_create_command("sqrt", EMPTY,             SQRT, 0),
    assembler_create_command("sin",  EMPTY,             SIN,  0),
    assembler_create_command("sin",  EMPTY,             SIN,  0),
    assembler_create_command("cos",  EMPTY,             COS,  0),
    assembler_create_command("in",   EMPTY,             IN,   0),
    assembler_create_command("out",  EMPTY,             OUT,  0),
    assembler_create_command("hlt",  EMPTY,             HLT,  0),
    assembler_create_command("pop",  REGISTER,          POP,  1),
    // assembler_create_command("meow", REGISTER,          MEOW, 1, 10),

};
size_t ASSEMBLER_COMMANDS_ARRAY_SIZE = sizeof(ASSEMBLER_COMMANDS_ARRAY) /
                                       sizeof(ASSEMBLER_COMMANDS_ARRAY[0]);

AssemblerRegister ASSEMBLER_REGISTERS_ARRAY[] = {
    assembler_create_register("rax", RAX),
    assembler_create_register("rbx", RBX),
    assembler_create_register("rcx", RCX),
    assembler_create_register("rdx", RDX),
    assembler_create_register("ip",  IP),
};
size_t ASSEMBLER_REGISTERS_ARRAY_SIZE = sizeof(ASSEMBLER_COMMANDS_ARRAY) /
                                        sizeof(ASSEMBLER_COMMANDS_ARRAY[0]);

AssemblerErrors assembler_convert(char const * const * pointers, size_t strings_num, char * output_buffer)
{
    MY_ASSERT(pointers != nullptr && output_buffer != nullptr);

    AssemblerErrors error = NO_ERRORS;

    for (size_t i = 0; i < strings_num; i++)
    {
        char const * buffer_ptr = pointers[i];
        char command[MAX_COMMAND_SIZE] = "";
        sscanf(pointers[i], "%s", command); // prosto po buferr_ptr
        buffer_ptr = skip_word(buffer_ptr);
        Hash_t string_hash = calculate_hash(command, strlen(command));

        for (size_t j = 0; j < ASSEMBLER_COMMANDS_ARRAY_SIZE; j++)
        {
            if (string_hash == ASSEMBLER_COMMANDS_ARRAY[j].hash)
            {
                *output_buffer = (char) ASSEMBLER_COMMANDS_ARRAY[j].command_number;
                output_buffer++;

                for (int k = 0; k < ASSEMBLER_COMMANDS_ARRAY[j].num_of_params; k++)
                {
                    if ((error = assembler_argument_processing(buffer_ptr, output_buffer, ASSEMBLER_COMMANDS_ARRAY[j].signature)))
                        return error;

                    buffer_ptr = skip_word(buffer_ptr);
                    output_buffer = next_word(output_buffer);
                }
            }
        }
    }

    return NO_ERRORS;
}


AssemblerErrors assembler_argument_processing(char const * buffer, char * output_buffer, int signature)
{

    Elem_t val = 0;
    char val_string[MAX_COMMAND_SIZE] = "";
    bool success = false;

    if (signature & NUMBER)
    {
        if (sscanf(buffer, ELEM_SPEC, &val) == 1)
        {
            buffer = skip_word(buffer);
            *((Elem_t *) output_buffer) = val;
            output_buffer += sizeof(Elem_t);
            success = true;
        }
        ///
    }

    if (signature & REGISTER && success == false)
    {
        if (sscanf(buffer, "%s", val_string))
        {
            Hash_t val_string_hash = calculate_hash (val_string, strlen(val_string) + 1);

            for (size_t i = 0; i < ASSEMBLER_REGISTERS_ARRAY_SIZE; i++)
            {
                if (val_string_hash == ASSEMBLER_REGISTERS_ARRAY[i].hash)
                {
                    buffer = skip_word(buffer);
                    *output_buffer = (char) ASSEMBLER_REGISTERS_ARRAY[i].id;
                    output_buffer++;
                    success = true;
                    break;
                }
            }
        }
    }

    if (!(signature & EMPTY) && success == false)
    {
        return ARGUMENT_ERROR;
    }

    return NO_ERRORS;
}


AssemblerCommand assembler_create_command(const char * command_str, int signature, ProcessorCommands id, int number_of_params)
{
    AssemblerCommand command = {
        .command = command_str,
        .num_of_params = number_of_params,
        .hash = calculate_hash(const_cast <char *> (command_str), sizeof(command_str)),
        .signature = signature,
        .command_number = id,
    };

    return command;
}


AssemblerRegister assembler_create_register(const char * register_str, AssemblerRegisters id)
{
    AssemblerRegister rgstr = {
        .rgstr = register_str,
        .hash = calculate_hash(const_cast <char *> (register_str), sizeof(register_str)),
        .id = id,
    };

    return rgstr;
}
