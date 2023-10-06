#include <stdio.h>
#include <stdlib.h>

#include "assembler.h"
#include "file_processing.h"
#include "cmd_input.h"
#include "strings.h"
#include "hash.h"

AssemblerCommand ASSEMBLER_PUSH = {
    .command = "push",
    .size = 4,
    .hash = 0,
    .command_number = PUSH,
};

AssemblerCommand ASSEMBLER_ADD = {
    .command = "add",
    .size = 3,
    .hash = 0,
    .command_number = PUSH,
};

AssemblerCommand ASSEMBLER_SUB = {
    .command = "sub",
    .size = 3,
    .hash = 0,
    .command_number = SUB,
};

AssemblerCommand ASSEMBLER_MUL = {
    .command = "mul",
    .size = 3,
    .hash = 0,
    .command_number = MUL,
};

AssemblerCommand ASSEMBLER_DIV = {
    .command = "div",
    .size = 3,
    .hash = 0,
    .command_number = DIV,
};

AssemblerCommand ASSEMBLER_SQRT = {
    .command = "sqrt",
    .size = 4,
    .hash = 0,
    .command_number = SQRT,
};

AssemblerCommand ASSEMBLER_SIN = {
    .command = "sin",
    .size = 3,
    .hash = 0,
    .command_number = SIN,
};

AssemblerCommand ASSEMBLER_COS = {
    .command = "cos",
    .size = 3,
    .hash = 0,
    .command_number = COS,
};

AssemblerCommand ASSEMBLER_IN = {
    .command = "in",
    .size = 2,
    .hash = 0,
    .command_number = IN,
};

AssemblerCommand ASSEMBLER_OUT = {
    .command = "out",
    .size = 3,
    .hash = 0,
    .command_number = OUT,
};

AssemblerCommand ASSEMBLER_HLT = {
    .command = "hlt",
    .size = 3,
    .hash = 0,
    .command_number = HLT,
};


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

    free(buffer);

    AssemblerCommand * commands_array[] = {
        &ASSEMBLER_PUSH, &ASSEMBLER_ADD,
        &ASSEMBLER_SUB,  &ASSEMBLER_MUL,
        &ASSEMBLER_DIV,  &ASSEMBLER_SQRT,
        &ASSEMBLER_SIN,  &ASSEMBLER_COS,
        &ASSEMBLER_IN,   &ASSEMBLER_OUT,
        &ASSEMBLER_HLT,
    };

    size_t commands_array_size = sizeof(commands_array) / sizeof(commands_array[0]);

    for (int i = 0; i < commands_array_size; i++)
    {
        commands_array[i]->hash = calculate_hash((void *) commands_array[i]->command, commands_array[i]->size);
    }

    if ((target_fp = file_open(TARGET_FILE_NAME, "w")) == NULL)
        return 1;

        printf("1\n");

    fclose(target_fp);

    free(pointers);

    return 0;
}

