#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assembler.h"
#include "file_processing.h"
#include "cmd_input.h"
#include "strings.h"
#include "hash.h"
#include "flags.h"


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

    if ((buffer = read_file(buffer, file_size, source_fp)) == NULL)
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

    char * output_buffer = NULL;
    if ((output_buffer = (char *) calloc(buffer_size, sizeof(char))) == NULL)
    {
        printf("Can't allocate memory.");
        free(pointers);
        free(buffer);

        return 1;
    }

    // for (size_t i = 0; i < ASSEMBLER_COMMANDS_ARRAY_SIZE; i++)
    // {
    //     printf("%s hash : %lld\n", ASSEMBLER_COMMANDS_ARRAY[i].command, ASSEMBLER_COMMANDS_ARRAY[i].hash);
    // }

    AssemblerErrors errors = NO_ERRORS;

    if ((errors = assembler_convert(pointers, strings_num, output_buffer)))
    {
        printf("Assembler error code: %d", (int) errors);
        return errors;
    }

    // printf("100 on bytes:\n");
    // Elem_t tmp_value = 100;
    // printf("%x ", (int) *((char *) &tmp_value));
    // printf("%x ", (int) *((char *) &tmp_value + 1));
    // printf("%x ", (int) *((char *) &tmp_value + 2));
    // printf("%x ", (int) *((char *) &tmp_value + 3));
    // printf("%x ", (int) *((char *) &tmp_value + 4));
    // printf("%x ", (int) *((char *) &tmp_value + 5));
    // printf("%x ", (int) *((char *) &tmp_value + 6));
    // printf("%x ", (int) *((char *) &tmp_value + 7));
    // printf("\n");

    // printf("Output buffer:\n");
    // for (int i = 0; i < buffer_size; i++)
    // {
    //     printf("%x ", (int) output_buffer[i]);
    // }

    free(pointers);
    free(buffer);

    if ((target_fp = file_open(TARGET_FILE_NAME, "wb")) == NULL)
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

// MASSIV SIGNATUT, TK RAZNIYAE ARGUMENTI MOGUT IMET RAZNYUY SIGNATURY