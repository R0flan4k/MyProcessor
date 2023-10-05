#include <stdio.h>
#include <math.h>

#include "arithmetic.h"
#include "stack.h"
#include "my_assert.h"


Error_t get_two_values(Stack * stk, Elem_t * val1, Elem_t * val2)
{
    Error_t errors = 0;

    if (errors = stack_pop(stk, val1))
        return errors;

    if (errors = stack_pop(stk, val2))
        return errors;

    return errors;
}


Error_t spu_binary(Stack * stk, SpuBinaryMathOperations mode)
{
    Error_t errors = 0;
    Elem_t val1 = 0, val2 = 0;

    if (errors = get_two_values(stk, &val1, &val2))
        return errors;

    switch (mode)
    {
        case ADDITION:
            if (errors = stack_push(stk, val2 + val1))
                return errors;
            break;

        case SUBTRACTION:
            if (errors = stack_push(stk, val2 - val1))
                return errors;
            break;

        case MULTIPLICATION:
            if (errors = stack_push(stk, val2 * val1))
                return errors;
            break;

        case DIVISION:
            if (errors = stack_push(stk, val2 / val1))
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

    if (errors = stack_pop(stk, &val))
        return errors;

    switch (mode)
    {
        case SQUARE_ROOT:
            if (errors = stack_push(stk, (Elem_t) sqrt((double) val)))
                return errors;
            break;

        case SINUS:
            if (errors = stack_push(stk, (Elem_t) sin((double) val)))
                return errors;
            break;

        case COSINUS:
            if (errors = stack_push(stk, (Elem_t) cos((double) val)))
                return errors;
            break;

        default:
            MY_ASSERT(0 && "UNREACHABLE");
            break;
    }

    return errors;
}
