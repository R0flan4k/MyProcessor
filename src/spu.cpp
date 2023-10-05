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

    Stack stk = {};
    Error_t errors = 0;
    FILE * fp = 0;

    if ((errors = stack_ctor(&stk)))
        return errors;

    if (!(fp = file_open(SPU_FILE_NAME, "r")))
        return 1;

    SPU_COMMANDS command = HLT;
    Elem_t in_val = 0;
    Elem_t out_val = 0;
    bool hlt_marker = false;
    while (fscanf(fp, "%d", (int *) &command) != EOF)
    {
        switch (command)
        {
            case PUSH:
                if (!fscanf(fp, ELEM_SPEC, &in_val))
                {
                    printf("Error: Invalid input.\n");
                    break;
                }
                if ((errors = stack_push(&stk, in_val)))
                {
                    fclose(fp);
                    return errors;
                }
                break;

            case ADD:
                if ((errors = spu_binary(&stk, ADDITION)))
                {
                    fclose(fp);
                    return errors;
                }
                break;

            case SUB:
                if ((errors = spu_binary(&stk, SUBTRACTION)))
                {
                    fclose(fp);
                    return errors;
                }
                break;

            case MUL:
                if ((errors = spu_binary(&stk, MULTIPLICATION)))
                {
                    fclose(fp);
                    return errors;
                }
                break;

            case DIV:
                if ((errors = spu_binary(&stk, DIVISION)))
                {
                    fclose(fp);
                    return errors;
                }
                break;

            case SQRT:
                if ((errors = spu_unary(&stk, SQUARE_ROOT)))
                {
                    fclose(fp);
                    return errors;
                }
                break;

            case SIN:
                if ((errors = spu_unary(&stk, SINUS)))
                {
                    fclose(fp);
                    return errors;
                }
                break;

            case COS:
                if ((errors = spu_unary(&stk, COSINUS)))
                {
                    fclose(fp);
                    return errors;
                }
                break;

            case IN:
                if (!scanf(ELEM_SPEC, &in_val))
                {
                    printf("Error: Invalid input.\n");
                    break;
                }
                if ((errors = stack_push(&stk, in_val)))
                {
                    fclose(fp);
                    return errors;
                }
                break;

            case OUT:
                if ((errors = stack_pop(&stk, &out_val)))
                {
                    fclose(fp);
                    return errors;
                }
                printf(ELEM_SPEC, out_val);
                break;

            case HLT:
                hlt_marker = true;
                break;

            default:
                MY_ASSERT(0 && "UNREACHABLE");
                break;
        }

        if (hlt_marker == true)
            break;
    }

    fclose(fp);

    if ((errors = stack_dtor(&stk)))
        return errors;

    return 0;
}
