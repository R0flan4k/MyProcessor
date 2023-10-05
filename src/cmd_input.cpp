#include <stdio.h>
#include <string.h>

#include "cmd_input.h"
#include "my_assert.h"

char * SPU_FILE_NAME = NULL;
static char * * cmd_input = NULL;

CmdLineArg SPU_FILE = {
    .name =          "--source",
    .num_of_param =  1,
    .flag_function = set_spu_file_name_flag,
    .argc_number =   0,
    .help =          "--source *file name*"
};

bool check_cmd_input(int argc, char * * argv)
{
    MY_ASSERT(argv != nullptr);

    cmd_input = argv;

    const char * program_name = argv[0];

    CmdLineArg * flags[] = {&SPU_FILE};
    size_t flags_array_size = sizeof(flags) / sizeof(flags[0]);

    for (size_t i = 0; i  < flags_array_size; i++)
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

        if (SPU_FILE_NAME == NULL)
        {
            printf("Error. Please, use %s %s *file name*\n", program_name, SPU_FILE.name);

            return false;
        }
    }

    return true;
}


void set_spu_file_name_flag()
{
    SPU_FILE_NAME = cmd_input[SPU_FILE.argc_number + 1];
}
