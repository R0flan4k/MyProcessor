#include <stdio.h>
#include <string.h>

#include "assembler.h"
#include "hash.h"
#include "my_assert.h"
#include "strings.h"
#include "stack.h"

AssemblerCommand ASSEMBLER_COMMANDS_ARRAY[] = {
    assembler_create_command("push", NUMBER | REGISTER, PUSH, 1),
    assembler_create_command("add",  EMPTY,             ADD,  0),
    assembler_create_command("sub",  EMPTY,             SUB,  0),
    assembler_create_command("mul",  EMPTY,             MUL,  0),
    assembler_create_command("div",  EMPTY,             DIV,  0),
    assembler_create_command("sqrt", EMPTY,             SQRT, 0),
    assembler_create_command("sin",  EMPTY,             SIN,  0),
    assembler_create_command("cos",  EMPTY,             COS,  0),
    assembler_create_command("in",   EMPTY,             IN,   0),
    assembler_create_command("out",  EMPTY,             OUT,  0),
    assembler_create_command("hlt",  EMPTY,             HLT,  0),
    assembler_create_command("pop",  REGISTER,          POP,  1),
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
    AssemblerErrors error = NO_ERRORS;

    for (size_t i = 0; i < strings_num; i++)
    {
        char const * buffer_ptr = pointers[i];
        char command[MAX_COMMAND_SIZE] = "";
        sscanf(pointers[i], "%s", command); // prosto po buferr_ptr
        buffer_ptr = skip_word(buffer_ptr);
        Hash_t string_hash = calculate_hash(command, strlen(command));

//         if (string_hash == ASSEMBLER_PUSH.hash)
//         {
//             Elem_t val = 0;
//             char val_string[MAX_COMMAND_SIZE] = "";
//
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_PUSH.command_number);
//             output_buffer = next_word(output_buffer);
//
//             if (sscanf(buffer_ptr, ELEM_SPEC, &val) == 1)
//             {
//                 buffer_ptr = skip_word(buffer_ptr);
//                 sprintf(output_buffer, "%d ", (int) PUSH_NUMBER);
//                 output_buffer = next_word(output_buffer);
//                 sprintf(output_buffer, ELEM_SPEC " ", val);
//                 output_buffer = next_word(output_buffer);
//             }
//             else
//             {
//                 sscanf(buffer_ptr, "%s", val_string);
//                 buffer_ptr = skip_word(buffer_ptr);
//                 sprintf(output_buffer, "%d ", (int) PUSH_REGISTER);
//                 output_buffer = next_word(output_buffer);
//
//                 Hash_t val_string_hash = calculate_hash (val_string, strlen(val_string));
//                 if      (val_string_hash == ASSEMBLER_RAX.hash) sprintf(output_buffer, "%d ", (int) ASSEMBLER_RAX.ip);
//                 else if (val_string_hash == ASSEMBLER_RBX.hash) sprintf(output_buffer, "%d ", (int) ASSEMBLER_RBX.ip);
//                 else if (val_string_hash == ASSEMBLER_RCX.hash) sprintf(output_buffer, "%d ", (int) ASSEMBLER_RCX.ip);
//                 else if (val_string_hash == ASSEMBLER_RDX.hash) sprintf(output_buffer, "%d ", (int) ASSEMBLER_RDX.ip);
//                 else if (val_string_hash == ASSEMBLER_IP.hash)  sprintf(output_buffer, "%d ", (int) ASSEMBLER_IP.ip);
//                 output_buffer = next_word(output_buffer);
//             }
//         }
//         else if (string_hash == ASSEMBLER_ADD.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_ADD.command_number);
//             output_buffer = next_word(output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_SUB.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_SUB.command_number);
//             output_buffer = next_word(output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_MUL.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_MUL.command_number);
//             output_buffer = next_word(output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_DIV.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_DIV.command_number);
//             output_buffer = next_word(output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_SQRT.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_SQRT.command_number);
//             output_buffer = next_word(output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_SIN.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_SIN.command_number);
//             output_buffer = next_word(output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_COS.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_COS.command_number);
//             output_buffer = next_word(output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_IN.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_IN.command_number);
//             output_buffer = next_word(output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_OUT.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_OUT.command_number);
//             output_buffer = next_word(output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_HLT.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_HLT.command_number);
//             output_buffer = next_word(output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_POP.hash)
//         {
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_POP.command_number);
//             output_buffer = next_word(output_buffer);
//
//             char val_string[MAX_COMMAND_SIZE] = "";
//             if (sscanf(buffer_ptr, "%s", val_string) != 1) return POP_ERROR;
//             buffer_ptr = skip_word(buffer_ptr);
//             Hash_t val_string_hash = calculate_hash(val_string, strlen(val_string));
//
//             if (val_string_hash == ASSEMBLER_RAX.hash) sprintf (output_buffer, "%d ", (int) ASSEMBLER_RAX.ip);
//             if (val_string_hash == ASSEMBLER_RBX.hash) sprintf (output_buffer, "%d ", (int) ASSEMBLER_RBX.ip);
//             if (val_string_hash == ASSEMBLER_RCX.hash) sprintf (output_buffer, "%d ", (int) ASSEMBLER_RCX.ip);
//             if (val_string_hash == ASSEMBLER_RDX.hash) sprintf (output_buffer, "%d ", (int) ASSEMBLER_RDX.ip);
//             output_buffer = next_word(output_buffer);
//         }

        for (size_t j = 0; j < ASSEMBLER_COMMANDS_ARRAY_SIZE; j++)
        {
            if (string_hash == ASSEMBLER_COMMANDS_ARRAY[j].hash)
            {
                sprintf(output_buffer, "%d ", (int) ASSEMBLER_COMMANDS_ARRAY[j].command_number);
                output_buffer = next_word(output_buffer);

                for (int k = 0; k < ASSEMBLER_COMMANDS_ARRAY[j].num_of_params; k++)
                {
                    if ((error = assembler_argument_processing(buffer_ptr, output_buffer, ASSEMBLER_COMMANDS_ARRAY[j].signature)))
                        return error;

                    buffer_ptr = skip_word(buffer_ptr);
                    output_buffer = next_word(output_buffer);
                }

//                 if (ASSEMBLER_COMMANDS_ARRAY[j].num_of_params > 0)
//                 {
//                     char val_string[MAX_COMMAND_SIZE] = "";
//                     Elem_t val = 0;
//
//                     if (sscanf(buffer_ptr, ELEM_SPEC, &val) != 0)
//                     {
//                         buffer_ptr = skip_word(buffer_ptr);
//                         sprintf(output_buffer, ELEM_SPEC " ", val);
//                         output_buffer = next_word(output_buffer);
//                     }
//                     else
//                     {
//                         sscanf(buffer_ptr, "%s", val_string);
//                         buffer_ptr = skip_word(buffer_ptr);
//                         Hash_t val_string_hash = calculate_hash(val_string, strlen(val_string));
//
//                         for (size_t k = 0; k < registers_array_size; k++)
//                         {
//                             if (ASSEMBLER_POP.hash == string_hash)
//                             {
//                                 sprintf(output_buffer, "%d ", (int) registers_array[i]->ip);
//                                 output_buffer = next_word(output_buffer);
//                                 break;
//                             }
//                             else if (registers_array[k]->hash == val_string_hash)
//                             {
//                                 sprintf(output_buffer, ELEM_SPEC " ", registers_array[k]->value);
//                                 output_buffer = next_word(output_buffer);
//                             }
//                         }
//                     }
//                 }
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
            sprintf(output_buffer, ELEM_SPEC " ", val);
            output_buffer = next_word(output_buffer);
            success = true;
        }
        ///
    }

    if (signature & REGISTER && success == false)
    {
        if (sscanf(buffer, "%s", val_string) == 1)
        {
            Hash_t val_string_hash = calculate_hash (val_string, strlen(val_string));

            for (size_t i = 0; i < ASSEMBLER_REGISTERS_ARRAY_SIZE; i++)
            {
                if (val_string_hash == ASSEMBLER_REGISTERS_ARRAY[i].hash)
                {
                    buffer = skip_word(buffer);
                    sprintf(output_buffer, "%d ", (int) ASSEMBLER_REGISTERS_ARRAY[i].id);
                    output_buffer = next_word(output_buffer);
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
