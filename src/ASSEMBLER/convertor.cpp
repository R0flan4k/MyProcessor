#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "assembler.h"
#include "hash.h"
#include "my_assert.h"
#include "strings.h"
#include "stack.h"
#include "processor.h"

static bool is_label(const char * string);
static AssemblerErrors labels_array_ctor(Label_t * labels, size_t size);
static AssemblerErrors add_label(const char * string, Label_t * labels, size_t size, int ip);

const size_t LABELS_ARRAY_SIZE = 10;

AssemblerCommand ASSEMBLER_COMMANDS_ARRAY[] = {
    #define CMD(str, signature, enum_id, num_of_params, id, code) \
        assembler_create_command(str, signature, enum_id, num_of_params),

    #include "commands.h"

    #undef CMD
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

Label_t LABELS[LABELS_ARRAY_SIZE] = {}; // v assembler_convert

AssemblerErrors assembler_convert(char const * const * pointers, size_t strings_num, char * start_output_buffer)
{
    MY_ASSERT(pointers != nullptr && start_output_buffer != nullptr);

    AssemblerErrors error = NO_ERRORS;

    labels_array_ctor(LABELS, LABELS_ARRAY_SIZE);
    int ip = 0;
    char * output_buffer = start_output_buffer;

    for (size_t i = 0; i < strings_num; i++)
    {

        if (is_label(pointers[i]))
        {
            add_label(pointers[i], LABELS, LABELS_ARRAY_SIZE, output_buffer - start_output_buffer);
            continue;
        }

        char const * buffer_ptr = pointers[i];
        char command[MAX_COMMAND_SIZE] = "";
        sscanf(pointers[i], "%s", command); // prosto po buferr_ptr
        buffer_ptr = skip_word(buffer_ptr);
        Hash_t string_hash = calculate_hash(command, strlen(command) + 1);
        for (size_t j = 0; j < ASSEMBLER_COMMANDS_ARRAY_SIZE; j++)
        {
            if (string_hash == ASSEMBLER_COMMANDS_ARRAY[j].hash)
            {
                *output_buffer = (char) ASSEMBLER_COMMANDS_ARRAY[j].command_number;
                output_buffer++;

                for (int k = 0; k < ASSEMBLER_COMMANDS_ARRAY[j].num_of_params; k++)
                {
                    if ((error = assembler_argument_processing(&buffer_ptr, &output_buffer, ASSEMBLER_COMMANDS_ARRAY[j].signature)))
                        return error;

                    buffer_ptr = skip_word(buffer_ptr);
                }
            }
        }

        ip++;
    }

    return NO_ERRORS;
}


AssemblerErrors assembler_argument_processing(const char * * buffer, char * * output_buffer, int signature)
{

    Elem_t val = 0;
    char val_string[MAX_COMMAND_SIZE] = "";
    bool success = false;

    if (signature & NUMBER)
    {
        if (sscanf(*buffer, ELEM_SPEC, &val) == 1)
        {
            *buffer = skip_word(*buffer);
            *(*output_buffer) = (char) PUSH_NUMBER;
            (*output_buffer)++;
            for (size_t k = 0; k < sizeof(Elem_t); k++)
            {
                *(*output_buffer) = *((char *) &val + k);
                (*output_buffer)++;
            }
            success = true;
        }
        ///
    }

    if (signature & REGISTER && success == false)
    {
        if (sscanf(*buffer, "%s", val_string))
        {
            Hash_t val_string_hash = calculate_hash(val_string, strlen(val_string) + 1);


            for (size_t i = 0; i < ASSEMBLER_REGISTERS_ARRAY_SIZE; i++)
            {
                if (val_string_hash == ASSEMBLER_REGISTERS_ARRAY[i].hash)
                {
                    *buffer = skip_word(*buffer);
                    *(*output_buffer) = (char) PUSH_REGISTER;
                    (*output_buffer)++;
                    *(*output_buffer) = (char) ASSEMBLER_REGISTERS_ARRAY[i].id;
                    (*output_buffer)++;
                    success = true;
                    break;
                }
            }
        }
    }

    if (signature & LABEL && success == false)
    {
        int label_id = atoi(*buffer);
        *(*output_buffer) = (char) LABELS[label_id];
        (*output_buffer)++;
        success = true;
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
        .hash = calculate_hash(const_cast <char *> (command_str), strlen(command_str) + 1),
        .signature = signature,
        .command_number = id,
    };

    return command;
}


AssemblerRegister assembler_create_register(const char * register_str, ProcessorRegisters id)
{
    AssemblerRegister rgstr = {
        .rgstr = register_str,
        .hash = calculate_hash(const_cast <char *> (register_str), strlen(register_str) + 1),
        .id = id,
    };

    return rgstr;
}


static bool is_label(const char * string)
{
    return (*string == ':');
}


static AssemblerErrors labels_array_ctor(Label_t * labels, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        labels[i] = -1;
    }

    return NO_ERRORS;
}


static AssemblerErrors add_label(const char * string, Label_t * labels, size_t size, int ip)
{
    char * ptr = strchr(string, ':');

    MY_ASSERT(ptr);

    int label_id = (int) (*(ptr + 1) - '0');

    if (!(0 <= label_id && label_id < (int) size))
        return INVALID_LABEL;

    labels[label_id] = ip;

    return NO_ERRORS;
}
