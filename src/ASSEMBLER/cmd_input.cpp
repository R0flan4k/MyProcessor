#include <stdio.h>
#include <string.h>

#include "cmd_input.h"
#include "my_assert.h"

char * SOURCE_FILE_NAME = NULL;
char * TARGET_FILE_NAME = NULL;
static char * * cmd_input = NULL;

CmdLineArg ASSEMBLER_SOURCE_FILE = {
    .name =          "--source",
    .num_of_param =  1,
    .flag_function = set_assembler_source_file_name_flag,
    .argc_number =   0,
    .help =          "--source *file name*"
};

CmdLineArg ASSEMBLER_TARGET_FILE = {
    .name =          "--target",
    .num_of_param =  1,
    .flag_function = set_assembler_target_file_name_flag,
    .argc_number =   0,
    .help =          "--target *file name*"
};

bool check_cmd_input(int argc, char * * argv)
{
    MY_ASSERT(argv != nullptr);

    cmd_input = argv;

    const char * program_name = argv[0];

    CmdLineArg * flags[] = {&ASSEMBLER_TARGET_FILE, &ASSEMBLER_SOURCE_FILE};
    size_t flags_array_size = sizeof(flags) / sizeof(flags[0]);

    for (size_t i = 0; i < flags_array_size; i++)
    {
        for (int j = 1; j < argc; j++)
        {
            if (strcmp(flags[i]->name, argv[j]) == 0)
            {
                if (argc > j + flags[i]->num_of_param)
                {
                    flags[i]->argc_number = j;

                    flags[i]->flag_function();
                }
                else
                {
                    printf("Error. Please, use %s %s\n", program_name, flags[i]->help);
                    return false;
                }
            }
        }
    }

    if (SOURCE_FILE_NAME == NULL || TARGET_FILE_NAME == NULL)
    {
        printf("Error. Please, use %s %s *file name* %s *file name*\n", program_name, ASSEMBLER_SOURCE_FILE.name,
                ASSEMBLER_TARGET_FILE.name);

        return false;
    }


    return true;
}


void set_assembler_source_file_name_flag()
{
    SOURCE_FILE_NAME = cmd_input[ASSEMBLER_SOURCE_FILE.argc_number + 1];
}


void set_assembler_target_file_name_flag()
{
    TARGET_FILE_NAME = cmd_input[ASSEMBLER_TARGET_FILE.argc_number + 1];
}
