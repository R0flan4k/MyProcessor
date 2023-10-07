#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"
#include "file_processing.h"
#include "cmd_input.h"
#include "strings.h"
#include "hash.h"

AssemblerCommand ASSEMBLER_PUSH = {
    .command = "push",
    .num_of_params = 1,
    .size = 4,
    .hash = 0,
    .command_number = PUSH,
};

AssemblerCommand ASSEMBLER_ADD = {
    .command = "add",
    .num_of_params = 0,
    .size = 3,
    .hash = 0,
    .command_number = PUSH,
};

AssemblerCommand ASSEMBLER_SUB = {
    .command = "sub",
    .num_of_params = 0,
    .size = 3,
    .hash = 0,
    .command_number = SUB,
};

AssemblerCommand ASSEMBLER_MUL = {
    .command = "mul",
    .num_of_params = 0,
    .size = 3,
    .hash = 0,
    .command_number = MUL,
};

AssemblerCommand ASSEMBLER_DIV = {
    .command = "div",
    .num_of_params = 0,
    .size = 3,
    .hash = 0,
    .command_number = DIV,
};

AssemblerCommand ASSEMBLER_SQRT = {
    .command = "sqrt",
    .num_of_params = 0,
    .size = 4,
    .hash = 0,
    .command_number = SQRT,
};

AssemblerCommand ASSEMBLER_SIN = {
    .command = "sin",
    .num_of_params = 0,
    .size = 3,
    .hash = 0,
    .command_number = SIN,
};

AssemblerCommand ASSEMBLER_COS = {
    .command = "cos",
    .num_of_params = 0,
    .size = 3,
    .hash = 0,
    .command_number = COS,
};

AssemblerCommand ASSEMBLER_IN = {
    .command = "in",
    .num_of_params = 0,
    .size = 2,
    .hash = 0,
    .command_number = IN,
};

AssemblerCommand ASSEMBLER_OUT = {
    .command = "out",
    .num_of_params = 0,
    .size = 3,
    .hash = 0,
    .command_number = OUT,
};

AssemblerCommand ASSEMBLER_HLT = {
    .command = "hlt",
    .num_of_params = 0,
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

    AssemblerCommand * commands_array[] = {
        &ASSEMBLER_PUSH, &ASSEMBLER_ADD,
        &ASSEMBLER_SUB,  &ASSEMBLER_MUL,
        &ASSEMBLER_DIV,  &ASSEMBLER_SQRT,
        &ASSEMBLER_SIN,  &ASSEMBLER_COS,
        &ASSEMBLER_IN,   &ASSEMBLER_OUT,
        &ASSEMBLER_HLT,
    };

    size_t commands_array_size = sizeof(commands_array) / sizeof(commands_array[0]);

    for (size_t i = 0; i < commands_array_size; i++)
    {
        commands_array[i]->hash = calculate_hash(const_cast <char *> (commands_array[i]->command), commands_array[i]->size);
    }

    char * output_buffer = NULL;
    if ((output_buffer = (char *) calloc(buffer_size, sizeof(char))) == NULL)
    {
        printf("Can't allocate memory.");
        free(pointers);
        free(buffer);

        return 1;
    }

    char * output_buffer_ptr = output_buffer;

    // printf("Strings num : %zd\n\n", strings_num);
    for (size_t i = 0; i < strings_num; i++)
    {
        char const * buffer_ptr = pointers[i];
        char command[MAX_COMMAND_SIZE] = "";
        sscanf(pointers[i], "%s", command);
        Hash_t string_hash = calculate_hash(command, strlen(command));
        // printf("String       : %s\n", pointers[i]);
        // printf("Current hash : %lld\n", string_hash);

//         if (string_hash == ASSEMBLER_PUSH.hash)
//         {
//             printf("In PUSH[%lld]\n", ASSEMBLER_PUSH.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_PUSH.command_number);
//             double val = 0;
//             sscanf(pointers[i], "%lf", &val);
//             sprintf(output_buffer, "%lf ", val);
//             printf("Output buffer : %s\n\n", output_buffer);
//
//         }
//         else if (string_hash == ASSEMBLER_ADD.hash)
//         {
//             printf("In ADD[%lld]\n", ASSEMBLER_ADD.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_ADD.command_number);
//             printf("Output buffer : %s\n\n", output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_SUB.hash)
//         {
//             printf("In SUB[%lld]\n", ASSEMBLER_SUB.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_SUB.command_number);
//             printf("Output buffer : %s\n\n", output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_MUL.hash)
//         {
//             printf("In MUL[%lld]\n", ASSEMBLER_MUL.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_MUL.command_number);
//             printf("Output buffer : %s\n\n", output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_DIV.hash)
//         {
//             printf("In DIV[%lld]\n", ASSEMBLER_DIV.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_DIV.command_number);
//             printf("Output buffer : %s\n\n", output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_SQRT.hash)
//         {
//             printf("In SQRT[%lld]\n", ASSEMBLER_SQRT.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_SQRT.command_number);
//             printf("Output buffer : %s\n\n", output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_SIN.hash)
//         {
//             printf("In SIN[%lld]\n", ASSEMBLER_SIN.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_SIN.command_number);
//             printf("Output buffer : %s\n\n", output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_COS.hash)
//         {
//             printf("In COS[%lld]\n", ASSEMBLER_COS.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_COS.command_number);
//             printf("Output buffer : %s\n\n", output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_IN.hash)
//         {
//             printf("In IN[%lld]\n", ASSEMBLER_IN.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_IN.command_number);
//             printf("Output buffer : %s\n\n", output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_OUT.hash)
//         {
//             printf("In OUT[%lld]\n", ASSEMBLER_OUT.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_OUT.command_number);
//             printf("Output buffer : %s\n\n", output_buffer);
//         }
//         else if (string_hash == ASSEMBLER_HLT.hash)
//         {
//             printf("In HLT[%lld]\n", ASSEMBLER_HLT.hash);
//             sprintf(output_buffer, "%d ", (int) ASSEMBLER_HLT.command_number);
//             printf("Output buffer : %s\n\n", output_buffer);
//         }

// Ya yebus v jopu
        for (size_t j = 0; j < commands_array_size; j++)
        {
            if (string_hash == commands_array[j]->hash)
            {
                buffer_ptr = skip_word(buffer_ptr);
                sprintf(output_buffer_ptr, "%d ", (int) commands_array[j]->command_number);
                output_buffer_ptr = next_word(output_buffer_ptr);

                if (commands_array[j]->num_of_params > 0)
                {
                    char val_string[MAX_COMMAND_SIZE] = "";

                    sscanf(buffer_ptr, "%s", val_string);
                    output_buffer_ptr += sprintf(output_buffer_ptr, "%s ", val_string);
                }
            }
        }
        // printf("Current output buffer : %s\n", output_buffer);
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

