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

static bool try_process_signature_number(const char * * buffer, char * * output_buffer);
static bool try_process_signature_register(const char * * buffer, char * * output_buffer);
static bool try_process_signature_label(const char * * buffer, char * * output_buffer);
static bool try_process_signature_ram(const char * * buffer, char * * output_buffer);
static bool is_label(const char * string);
static AssemblerErrors labels_array_ctor(Label_t * labels, size_t size);
static AssemblerErrors add_label(const char * string, Label_t * labels, size_t size, int ip);

const size_t LABELS_ARRAY_SIZE = 10;

AssemblerCommand ASSEMBLER_COMMANDS_ARRAY[] = {
    #define CMD(str, signature, enum_id, num_of_params, id, code) \
        assembler_create_command(str, signature, PROCESSOR_COMMAND_ ## enum_id, num_of_params),

    #include "commands.h"

    #undef CMD
};
size_t ASSEMBLER_COMMANDS_ARRAY_SIZE = sizeof(ASSEMBLER_COMMANDS_ARRAY) /
                                       sizeof(ASSEMBLER_COMMANDS_ARRAY[0]);

AssemblerRegister ASSEMBLER_REGISTERS_ARRAY[] = {
    assembler_create_register("rax", PROCESSOR_REGISTER_RAX),
    assembler_create_register("rbx", PROCESSOR_REGISTER_RBX),
    assembler_create_register("rcx", PROCESSOR_REGISTER_RCX),
    assembler_create_register("rdx", PROCESSOR_REGISTER_RDX),
    assembler_create_register("ip",  PROCESSOR_REGISTER_IP),
};
size_t ASSEMBLER_REGISTERS_ARRAY_SIZE = sizeof(ASSEMBLER_COMMANDS_ARRAY) /
                                        sizeof(ASSEMBLER_COMMANDS_ARRAY[0]);

Label_t LABELS[LABELS_ARRAY_SIZE] = {}; // v assembler_convert

AssemblerErrors assembler_convert(char const * const * pointers, size_t strings_num, char * start_output_buffer)
{
    MY_ASSERT(pointers != nullptr && start_output_buffer != nullptr);

    AssemblerErrors error = ASSEMBLER_NO_ERRORS;

    labels_array_ctor(LABELS, LABELS_ARRAY_SIZE);
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
    }

    return ASSEMBLER_NO_ERRORS;
}


AssemblerErrors assembler_argument_processing(const char * * buffer, char * * output_buffer, int signature)
{
    bool success = false;

    if (signature & PROCESSOR_SIGNATURE_EMPTY)
    {
        return ASSEMBLER_NO_ERRORS;
    }

    if (signature & PROCESSOR_SIGNATURE_NUMBER)
    {
        success = try_process_signature_number(buffer, output_buffer);
    }

    if (signature & PROCESSOR_SIGNATURE_REGISTER && success == false)
    {
        success = try_process_signature_register(buffer, output_buffer);
    }

    if (signature & PROCESSOR_SIGNATURE_LABEL && success == false)
    {
        success = try_process_signature_label(buffer, output_buffer);
    }

    if (signature & PROCESSOR_SIGNATURE_RAM && success == false)
    {
        success = try_process_signature_ram(buffer, output_buffer);
    }

    if (success == false)
    {
        return ASSEMBLER_ARGUMENT_ERROR;
    }

    return ASSEMBLER_NO_ERRORS;
}


static bool try_process_signature_number(const char * * buffer, char * * output_buffer)
{
    Elem_t val = 0;

    if (sscanf(*buffer, ELEM_SPEC, &val) == 1)
    {
        *buffer = skip_word(*buffer);
        *(*output_buffer) = (char) PROCESSOR_SIGNATURE_NUMBER;
        (*output_buffer)++;
        for (size_t k = 0; k < sizeof(Elem_t); k++)
        {
            *(*output_buffer) = *((char *) &val + k);
            (*output_buffer)++;
        }

        return true;
    }

    return false;
}


static bool try_process_signature_register(const char * * buffer, char * * output_buffer)
{
    char val_string[MAX_COMMAND_SIZE] = "";

    if (sscanf(*buffer, "%s", val_string))
    {
        Hash_t val_string_hash = calculate_hash(val_string, strlen(val_string) + 1);


        for (size_t i = 0; i < ASSEMBLER_REGISTERS_ARRAY_SIZE; i++)
        {
            if (val_string_hash == ASSEMBLER_REGISTERS_ARRAY[i].hash)
            {
                *buffer = skip_word(*buffer);
                *(*output_buffer) = (char) PROCESSOR_SIGNATURE_REGISTER;
                (*output_buffer)++;
                *(*output_buffer) = (char) ASSEMBLER_REGISTERS_ARRAY[i].id;
                (*output_buffer)++;
                return true;
            }
        }
    }

    return false;
}

static bool try_process_signature_label(const char * * buffer, char * * output_buffer)
{
    if (**buffer == ':')
    {
        (*buffer)++;
        int label_id = atoi(*buffer);
        *(*output_buffer) = (char) LABELS[label_id];
        (*output_buffer)++;

        return true;
    }

    return false;
}


static bool try_process_signature_ram(const char * * buffer, char * * output_buffer)
{
    if (**buffer == '[')
    {
        *(*output_buffer) = (char) PROCESSOR_SIGNATURE_RAM;
        (*output_buffer)++;
        // POFIKSIT RAM I SDELAT FACT I KV
        (*buffer)++;

        bool success = false;

        if ((success = try_process_signature_number(buffer, output_buffer)))
        {
            return success;
        }
        else if ((success = try_process_signature_register(buffer, output_buffer)))
        {
            return success;
        }
    }

    return false;
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

    return ASSEMBLER_NO_ERRORS;
}


static AssemblerErrors add_label(const char * string, Label_t * labels, size_t size, int ip)
{
    char * ptr = strchr(string, ':');

    MY_ASSERT(ptr);

    int label_id = (int) (*(ptr + 1) - '0');

    if (!(0 <= label_id && label_id < (int) size))
        return ASSEMBLER_LABEL_ERROR;

    labels[label_id] = ip;

    return ASSEMBLER_NO_ERRORS;
}


void assembler_dump(char const * const * pointers, size_t strings_num, const char * output_buffer, size_t buffer_size)
{
    MY_ASSERT(pointers);
    MY_ASSERT(output_buffer);

    printf("========================================================\n");
    printf("--------------------ASSEMBLER-DUMP----------------------\n");
    printf("|                                                      |\n");
    printf("|Inputed text:                                         |\n");

    for (size_t i = 0; i < strings_num; i++)
    {
        printf("|");
        printf("    ");
        size_t j = 0;
        for (; pointers[i][j] != '\0' && j < 50; j++)
        {
            printf("%c", pointers[i][j]);
        }
        while (j < 50)
        {
            printf(" ");
            j++;
        }
        printf("|\n");
    }

    printf("|Outputed bytecode:                                    |\n");

    char byte[9] = "";
    for (size_t i = 0; i < buffer_size / 16; i++)
    {
        printf("|");
        printf("    ");
        for (size_t j = 0; j < 16; j++)
        {
            sprintf(byte, "%-.8X", (char) output_buffer[i * 16 + j]);
            printf("%s ", byte + 6);
        }
        printf( "  |\n");
    }

    printf("========================================================\n");
}
