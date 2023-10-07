#include <stdio.h>
#include <math.h>

#include "arithmetic.h"
#include "stack.h"
#include "my_assert.h"
#include "spu.h"


Error_t get_two_values(Stack * stk, Elem_t * val1, Elem_t * val2)
{
    Error_t errors = 0;

    if ((errors = stack_pop(stk, val1)))
        return errors;

    if ((errors = stack_pop(stk, val2)))
        return errors;

    return errors;
}


Error_t spu_binary(Stack * stk, SpuBinaryMathOperations mode)
{
    Error_t errors = 0;
    Elem_t val1 = 0, val2 = 0;

    if ((errors = get_two_values(stk, &val1, &val2)))
        return errors;

    switch (mode)
    {
        case ADDITION:
            if ((errors = stack_push(stk, val2 + val1)))
                return errors;
            break;

        case SUBTRACTION:
            if ((errors = stack_push(stk, val2 - val1)))
                return errors;
            break;

        case MULTIPLICATION:
            if ((errors = stack_push(stk, val2 * val1)))
                return errors;
            break;

        case DIVISION:
            if ((errors = stack_push(stk, val2 / val1)))
                return errors;
            break;

        default:
            MY_ASSERT(0 && "UNREACHABLE");
            break;
    }

    return errors;
}


Error_t spu_unary(Stack * stk, SpuUnaryMathOperations mode)
{
    Error_t errors = 0;
    Elem_t val = 0;

    if ((errors = stack_pop(stk, &val)))
        return errors;

    switch (mode)
    {
        case SQUARE_ROOT:
            if ((errors = stack_push(stk, (Elem_t) sqrt((double) val))))
                return errors;
            break;

        case SINUS:
            if ((errors = stack_push(stk, (Elem_t) sin((double) val))))
                return errors;
            break;

        case COSINUS:
            if ((errors = stack_push(stk, (Elem_t) cos((double) val))))
                return errors;
            break;

        default:
            MY_ASSERT(0 && "UNREACHABLE");
            break;
    }

    return errors;
}


Error_t spu_process_comands(SoftProcessorUnit * spu, FILE * fp)
{
    Error_t errors;
    SPU_COMMANDS command = HLT;
    Elem_t in_val = 0;
    Elem_t out_val = 0;
    bool hlt_marker = false;

    while (fscanf(fp, "%d", (int *) &command) != EOF) // huynsia
    {
        switch (command)
        {
            case PUSH:
                if (!fscanf(fp, ELEM_SPEC, &in_val))
                {
                    printf("Error: Invalid input.\n");
                    break;
                }
                if ((errors = stack_push(&spu->stk, in_val)))
                {
                    return errors;
                }
                break;

            case ADD:
                if ((errors = spu_binary(&spu->stk, ADDITION)))
                {
                    return errors;
                }
                break;

            case SUB:
                if ((errors = spu_binary(&spu->stk, SUBTRACTION)))
                {
                    return errors;
                }
                break;

            case MUL:
                if ((errors = spu_binary(&spu->stk, MULTIPLICATION)))
                {
                    return errors;
                }
                break;

            case DIV:
                if ((errors = spu_binary(&spu->stk, DIVISION)))
                {
                    return errors;
                }
                break;

            case SQRT:
                if ((errors = spu_unary(&spu->stk, SQUARE_ROOT)))
                {
                    return errors;
                }
                break;

            case SIN:
                if ((errors = spu_unary(&spu->stk, SINUS)))
                {
                    return errors;
                }
                break;

            case COS:
                if ((errors = spu_unary(&spu->stk, COSINUS)))
                {
                    return errors;
                }
                break;

            case IN:
                if (!scanf(ELEM_SPEC, &in_val))
                {
                    printf("Error: Invalid input.\n");
                    break;
                }
                if ((errors = stack_push(&spu->stk, in_val)))
                {
                    return errors;
                }
                break;

            case OUT:
                if ((errors = stack_pop(&spu->stk, &out_val)))
                {
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

    return errors;
}
