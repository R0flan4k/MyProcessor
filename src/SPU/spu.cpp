#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "vtor.h"
#include "cmd_input.h"
#include "my_assert.h"
#include "arithmetic.h"
#include "file_processing.h"
#include "spu.h"


int main(int argc, char * argv[])
{
    if (!check_cmd_input(argc, argv))
        return 1;

    SoftProcessorUnit spu = {};
    Error_t errors = 0;
    FILE * fp = 0;

    if ((errors = stack_ctor(&spu.stk)))
        return errors;

    if (!(fp = file_open(SPU_FILE_NAME, "r")))
        return 1;

    if ((errors = spu_process_comands(&spu, fp)))
    {
        fclose(fp);
        return errors;
    }

    fclose(fp);

    if ((errors = stack_dtor(&spu.stk)))
        return errors;

    return 0;
}
