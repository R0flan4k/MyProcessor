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

    // while (fscanf(fp, "%d", (int *) &command) != EOF) // huynsia
    for (size_t i = 0; i < spu->bytecode_size && bytecode_ptr[i] != HLT; i++)
    {
        // printf("Command : %x\n", bytecode_ptr[i]);
        switch ((ProcessorCommands) bytecode_ptr[i])
        {
            case PUSH:
                i++;
                // printf("Mode : %d\n", bytecode_ptr[i]);
                switch ((PushMode) bytecode_ptr[i])
                {
                    case PUSH_NUMBER:
                        i++;
                        in_val = *((Elem_t *) (bytecode_ptr + i));
                        // printf("Pushed value : %lf\n", *((Elem_t *) (bytecode_ptr + i)));
                        i += sizeof(Elem_t) - 1;
                        // if (!fscanf(fp, ELEM_SPEC, &in_val))
                        // {
                        //     printf("Error: Invalid push.\n");
                        //     hlt_marker = true;
                        // }
                        break;

                    case PUSH_REGISTER:
                        i++;
                        register_ip = (ProcessorRegisters) bytecode_ptr[i];
                        // printf("Register id : %d\n", register_ip);
                        // if (!fscanf(fp, "%d", (int *) &register_ip))
                        // {
                        //     printf("Error: Invalid pushing register\n");
                        //     hlt_marker = true;
                        // }

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
                        return errors; //return blyat
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
                return errors;
                break;

            case POP:
                if ((errors = stack_pop(&spu->stk, &out_val)))
                {
                    return errors;
                }
                // printf("Taken value : %lf\n", out_val);

                i++;
                i++;
                register_ip = (ProcessorRegisters) bytecode_ptr[i];
                // printf("Register id: %d\n", register_ip);
                // if (!fscanf(fp, "%d", (int *) &register_ip))
                // {
                //     printf("Error: Invalid pop.\n");
                //     break;
                // }
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
                        return errors;
                        break;

                    default:
                        MY_ASSERT(0 && "UNREACHABLE");
                        break;
                }
                break;

            case JMP:
                i++;
                i = *((size_t *) &(bytecode_ptr[i])) - 1; // EXIT POINT
                break;

            default:
                MY_ASSERT(0 && "UNREACHABLE");
                break;
        }

        spu->ip++;
        // printf("IP %d --- done.\n", spu->ip);
        // show_dump(&spu->stk, &errors);
        // printf("\n\n");
    }

    return errors;
}
