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

    long file_size = get_file_size(fp);
    long buffer_size = file_size + 1;

    Buffer_t * buffer = NULL;
    if ((buffer = (Buffer_t *) calloc(buffer_size, sizeof(char))) == NULL)
    {
        printf("Can't allocate memory.");
        fclose(fp);

        return 1;
    }

    if ((buffer = read_file(buffer, buffer_size, fp)) == NULL)
    {
        fclose(fp);
        free(buffer);

        return 1;
    }

    buffer[buffer_size - 1] = EOF;

    Buffer_t * pointer = buffer;
    Elem_t in_val = 0;
    Elem_t out_val = 0;
    bool hlt_marker = false;
    while (*pointer != EOF)
    {
        printf("%d\n", *pointer);
        switch (*pointer)
        {
            case PUSH:
                if ((errors = stack_push(&stk, *(pointer + 1))))
                {
                    free(pointer);
                    fclose(fp);
                    return errors;
                }
                pointer++;
                break;

            case ADD:
                if ((errors = spu_binary(&stk, ADDITION)))
                {
                    free(pointer);
                    fclose(fp);
                    return errors;
                }
                break;

            case SUB:
                if ((errors = spu_binary(&stk, SUBTRACTION)))
                {
                    free(pointer);
                    fclose(fp);
                    return errors;
                }
                break;

            case MUL:
                if ((errors = spu_binary(&stk, MULTIPLICATION)))
                {
                    free(pointer);
                    fclose(fp);
                    return errors;
                }
                break;

            case DIV:
                if ((errors = spu_binary(&stk, DIVISION)))
                {
                    free(pointer);
                    fclose(fp);
                    return errors;
                }
                break;

            case SQRT:
                if ((errors = spu_unary(&stk, SQUARE_ROOT)))
                {
                    free(pointer);
                    fclose(fp);
                    return errors;
                }
                break;

            case SIN:
                if ((errors = spu_unary(&stk, SINUS)))
                {
                    free(pointer);
                    fclose(fp);
                    return errors;
                }
                break;

            case COS:
                if ((errors = spu_unary(&stk, COSINUS)))
                {
                    free(pointer);
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
                    free(pointer);
                    fclose(fp);
                    return errors;
                }
                break;

            case OUT:
                if ((errors = stack_pop(&stk, &out_val)))
                {
                    free(pointer);
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

        pointer++;
    }

    free(buffer);
    fclose(fp);

    if ((errors = stack_dtor(&stk)))
        return errors;

    return 0;
}
