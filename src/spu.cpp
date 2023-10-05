#include <stdio.h>
#include <stdlib.h>

#include "stack.h"
#include "vtor.h"
#include "cmd_input.h"
#include "my_assert.h"


int main(int argc, char * argv[])
{
    Stack stk = {};
    Error_t errors = 0;
    FILE * fp = 0;

    if (errors = stack_ctor(&stk))
        return errors;


    if (errors = stack_dtor(&stk))
        return errors;

    return 0;
}
