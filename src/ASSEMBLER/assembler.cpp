#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"
#include "file_processing.h"
#include "cmd_input.h"
#include "strings.h"
#include "hash.h"


int main(int argc, char * argv[])
{
    if (!check_cmd_input(argc, argv))
        return 1;

    FILE * source_fp = NULL;
    FILE * target_fp = NULL;

    if ((source_fp = file_open(SOURCE_FILE_NAME, "r")) == NULL)
        return 1;

    long file_size = get_file_size(source_fp);
    long buffer_size = file_size + 1;

    char * buffer = NULL;
    if ((buffer = (char *) calloc(buffer_size, sizeof(char))) == NULL)
    {
        printf("Can't allocate memory.");
        fclose(source_fp);

        return 1;
    }

    if ((buffer = read_file(buffer, buffer_size, source_fp)) == NULL)
    {
        fclose(source_fp);
        free(buffer);

        return 1;
    }

    buffer[buffer_size - 1] = '\0';
    fclose(source_fp);

    size_t strings_num = get_strings_num(buffer);

    const char * * pointers = NULL;
    if ((pointers = (const char * *) calloc(strings_num, sizeof(char *))) == NULL)
    {
        printf("Can't allocate memory.");
        free(buffer);

        return 1;
    }

    get_pointers(buffer, pointers, strings_num);

    AssemblerCommand * commands_array[] = {
        &ASSEMBLER_PUSH, &ASSEMBLER_ADD,
        &ASSEMBLER_SUB,  &ASSEMBLER_MUL,
        &ASSEMBLER_DIV,  &ASSEMBLER_SQRT,
        &ASSEMBLER_SIN,  &ASSEMBLER_COS,
        &ASSEMBLER_IN,   &ASSEMBLER_OUT,
        &ASSEMBLER_HLT,  &ASSEMBLER_POP,
    };
    size_t commands_array_size = sizeof(commands_array) / sizeof(commands_array[0]);

    for (size_t i = 0; i < commands_array_size; i++)
    {
        commands_array[i]->hash = calculate_hash(const_cast <char *> (commands_array[i]->command), strlen(commands_array[i]->command));
    }

    AssemblerRegister * registers_array[] = {
        &ASSEMBLER_RAX, &ASSEMBLER_RBX,
        &ASSEMBLER_RCX, &ASSEMBLER_RDX,
        &ASSEMBLER_IP,
    };
    size_t registers_array_size = sizeof(registers_array) / sizeof(registers_array[0]);

    for (size_t i = 0; i < registers_array_size; i++)
    {
        registers_array[i]->hash = calculate_hash(const_cast <char *> (registers_array[i]->rgstr), strlen(registers_array[i]->rgstr));
    }

    char * output_buffer = NULL;
    if ((output_buffer = (char *) calloc(buffer_size, sizeof(char))) == NULL)
    {
        printf("Can't allocate memory.");
        free(pointers);
        free(buffer);

        return 1;
    }

    AssemblerErrors errors = NO_ERRORS;

    if ((errors = assembler_convert(pointers, strings_num,
                                    output_buffer, commands_array,
                                    commands_array_size, registers_array,
                                    registers_array_size)))
    {
        return errors;
    }

    free(pointers);
    free(buffer);

    // puts("");
    // printf("Result output buffer: %s\n", output_buffer);

    if ((target_fp = file_open(TARGET_FILE_NAME, "w")) == NULL)
    {
        free(output_buffer);
        return 1;
    }

    if (!write_file(output_buffer, buffer_size, target_fp))
    {
        free(output_buffer);
        fclose(target_fp);

        return 1;
    }

    free(output_buffer);
    fclose(target_fp);

    return 0;
}

