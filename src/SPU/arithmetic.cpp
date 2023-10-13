#include <stdio.h>
#include <math.h>

#include "arithmetic.h"
#include "stack.h"
#include "my_assert.h"
#include "spu.h"
#include "processor.h"


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


Error_t spu_process_comands(SoftProcessorUnit * spu, FILE * fp)
{
    Error_t errors;
    ProcessorCommands command = HLT;
    Elem_t in_val = 0;
    Elem_t out_val = 0;
    bool hlt_marker = false;
    PushMode push_mode = NULL_MODE;
    ProcessorRegisters register_ip = RAX;

    while (fscanf(fp, "%d", (int *) &command) != EOF) // huynsia
    {
        switch (command)
        {
            case PUSH:
                if (!fscanf(fp, "%d", (int *) &push_mode))
                {
                    printf("Error: Invalid push.\n");
                    break;
                }

                switch (push_mode)
                {
                    case PUSH_NUMBER:
                        if (!fscanf(fp, ELEM_SPEC, &in_val))
                        {
                            printf("Error: Invalid push.\n");
                            hlt_marker = true;
                        }
                        break;

                    case PUSH_REGISTER:
                        if (!fscanf(fp, "%d", (int *) &register_ip))
                        {
                            printf("Error: Invalid pushing register\n");
                            hlt_marker = true;
                        }

                        switch (register_ip)
                        {
                            case RAX:
                                in_val = spu->rax;
                                break;

                            case RBX:
                                in_val = spu->rbx;
                                break;

                            case RCX:
                                in_val = spu->rcx;
                                break;

                            case RDX:
                                in_val = spu->rdx;
                                break;

                            case IP:
                                in_val = spu->ip;
                                break;

                            default:
                                MY_ASSERT(0 && "UNREACHABLE");
                                break;
                        }
                        break;

                    case NULL_MODE:
                        printf("Error: can't push null mode\n");
                        hlt_marker = true; //return blyat
                        break;

                    default:
                        MY_ASSERT(0 && "UNREACHABLE");
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
                printf(ELEM_SPEC "\n", out_val);
                break;

            case HLT:
                hlt_marker = true;
                break;

            case POP:
                if ((errors = stack_pop(&spu->stk, &out_val)))
                {
                    return errors;
                }

                if (!fscanf(fp, "%d", (int *) &register_ip))
                {
                    printf("Error: Invalid pop.\n");
                    break;
                }
                switch (register_ip)
                {
                    case RAX:
                        spu->rax = out_val;
                        break;

                    case RBX:
                        spu->rbx = out_val;
                        break;

                    case RCX:
                        spu->rcx = out_val;
                        break;

                    case RDX:
                        spu->rdx = out_val;
                        break;

                    case IP:
                        printf("Error: can't pop ip register\n");
                        hlt_marker = true;
                        break;

                    default:
                        MY_ASSERT(0 && "UNREACHABLE");
                        break;
                }
                break;


            default:
                MY_ASSERT(0 && "UNREACHABLE");
                break;
        }

        if (hlt_marker == true)
            break;

        spu->ip++;
    }

    return errors;
}
