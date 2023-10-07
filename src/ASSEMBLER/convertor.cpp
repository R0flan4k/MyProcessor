#include <stdio.h>

#include "assembler.h"
#include "hash.h"
#include "my_assert.h"
#include "strings.h"


ConvertErrors assembler_convert(char const * const * pointers, size_t strings_num, char * output_buffer, AssemblerCommand * commands_array[], size_t commands_array_size)
{
    for (size_t i = 0; i < strings_num; i++)
    {
        char const * buffer_ptr = pointers[i];
        char command[MAX_COMMAND_SIZE] = "";
        sscanf(pointers[i], "%s", command);
        Hash_t string_hash = calculate_hash(command, strlen(command));

        for (size_t j = 0; j < commands_array_size; j++)
        {
            if (string_hash == commands_array[j]->hash)
            {
                buffer_ptr = skip_word(buffer_ptr);
                sprintf(output_buffer, "%d ", (int) commands_array[j]->command_number);
                output_buffer = next_word(output_buffer);

                if (commands_array[j]->num_of_params > 0)
                {
                    char val_string[MAX_COMMAND_SIZE] = "";

                    sscanf(buffer_ptr, "%s", val_string);
                    output_buffer += sprintf(output_buffer, "%s ", val_string);
                }
            }
        }
        // printf("Current output buffer : %s\n", output_buffer);
    }

    return NO_ERRORS;
}
