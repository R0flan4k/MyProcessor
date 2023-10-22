#include <stdio.h>
#include <math.h>

#include "arithmetic.h"
#include "stack.h"
#include "my_assert.h"
#include "spu.h"
#include "processor.h"
#include "vtor.h"


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
    Elem_t val1 = 0, val2 = 0, result = 0;

    if ((errors = get_two_values(stk, &val1, &val2)))
        return errors;

    switch (mode)
    {
        case ADDITION:
            result = val2 + val1;
            break;

        case SUBTRACTION:
            result = val2 - val1;
            break;

        case MULTIPLICATION:
            result = val2 * val1;
            break;

        case DIVISION:
            result = val2 / val1;
            break;

        default:
            MY_ASSERT(0 && "UNREACHABLE");
            break;
    }

    errors = stack_push(stk, result);

    return errors;
}


Error_t spu_unary(Stack * stk, SpuUnaryMathOperations mode)
{
    Error_t errors = 0;
    Elem_t val = 0, result = 0;

    if ((errors = stack_pop(stk, &val)))
        return errors;

    switch (mode)
    {
        case SQUARE_ROOT:
            result = (Elem_t) sqrt((double) val);
            break;

        case SINUS:
            result = (Elem_t) sin((double) val);
            break;

        case COSINUS:
            result = (Elem_t) cos((double) val);
            break;

        default:
            MY_ASSERT(0 && "UNREACHABLE");
            break;
    }

    errors = stack_push(stk, result);

    return errors;
}


Error_t spu_process_comands(SoftProcessorUnit * spu)
{
    Error_t errors;
    Elem_t in_val = 0;
    Elem_t out_val = 0;
    ProcessorRegisters register_ip = RAX;
    char * bytecode_ptr = spu->bytecode;

    for (size_t i = 0; i < spu->bytecode_size && bytecode_ptr[i] != HLT; i++)
    {
        switch ((ProcessorCommands) bytecode_ptr[i])
        {
            #define CMD(str, signature, enum_id, num_of_params, id, code) case enum_id: \
                                                                               code     \
                                                                               break;

            #include "commands.h"

            #undef CMD

            default:
                MY_ASSERT(0 && "UNREACHABLE");
                break;
        }

        spu->ip++;
    }

    return errors;
}
