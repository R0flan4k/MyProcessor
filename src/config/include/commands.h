CMD("push", NUMBER | REGISTER, PUSH, 1, 1,                                                          \
                i++;                                                                                \
                switch ((PushMode) bytecode_ptr[i])                                                 \
                {                                                                                   \
                    case PUSH_NUMBER:                                                               \
                        i++;                                                                        \
                        in_val = *((Elem_t *) (bytecode_ptr + i));                                  \
                        i += sizeof(Elem_t) - 1;                                                    \
                        break;                                                                      \
                    case PUSH_REGISTER:                                                             \
                        i++;                                                                        \
                        register_ip = (ProcessorRegisters) bytecode_ptr[i];                         \
                                                                                                    \
                        switch (register_ip)                                                        \
                        {                                                                           \
                            case RAX:                                                               \
                                in_val = spu->rax;                                                  \
                                break;                                                              \
                                                                                                    \
                            case RBX:                                                               \
                                in_val = spu->rbx;                                                  \
                                break;                                                              \
                                                                                                    \
                            case RCX:                                                               \
                                in_val = spu->rcx;                                                  \
                                break;                                                              \
                                                                                                    \
                            case RDX:                                                               \
                                in_val = spu->rdx;                                                  \
                                break;                                                              \
                                                                                                    \
                            case IP:                                                                \
                                in_val = spu->ip;                                                   \
                                break;                                                              \
                                                                                                    \
                            default:                                                                \
                                MY_ASSERT(0 && "UNREACHABLE");                                      \
                                break;                                                              \
                        }                                                                           \
                        break;                                                                      \
                    case NULL_MODE:                                                                 \
                        printf("Error: can't push null mode\n");                                    \
                        return errors;                                                              \
                        break;                                                                      \
                    default:                                                                        \
                        MY_ASSERT(0 && "UNREACHABLE");                                              \
                        break;                                                                      \
                }                                                                                   \
                if ((errors = stack_push(&spu->stk, in_val)))                                       \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
    )

CMD("add", EMPTY, ADD, 0, 2, \
                if ((errors = spu_binary(&spu->stk, ADDITION)))                                     \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
   )

CMD("sub", EMPTY, SUB, 0, 3, \
                if ((errors = spu_binary(&spu->stk, SUBTRACTION)))                                  \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
   )

CMD("mul", EMPTY, MUL, 0, 4, \
                if ((errors = spu_binary(&spu->stk, MULTIPLICATION)))                               \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
   )

CMD("div", EMPTY, DIV, 0, 5, \
                if ((errors = spu_binary(&spu->stk, DIVISION)))                                     \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
            )

CMD("sqrt", EMPTY, SQRT, 0, 6, \
                if ((errors = spu_unary(&spu->stk, SQUARE_ROOT)))                                   \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
   )

CMD("sin", EMPTY, SIN, 0, 7, \
                if ((errors = spu_unary(&spu->stk, SINUS)))                                         \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
   )

CMD("cos", EMPTY, COS, 0, 8, \
                if ((errors = spu_unary(&spu->stk, COSINUS)))                                       \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
   )

CMD("in", EMPTY, IN, 0, 9, \
                if (!scanf(ELEM_SPEC, &in_val))                                                     \
                {                                                                                   \
                    printf("Error: Invalid input.\n");                                              \
                    break;                                                                          \
                }                                                                                   \
                if ((errors = stack_push(&spu->stk, in_val)))                                       \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
   )

CMD("out", EMPTY, OUT, 0, 10, \
                if ((errors = stack_pop(&spu->stk, &out_val)))                                      \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
                printf(ELEM_SPEC "\n", out_val);                                                    \
   )

CMD("hlt", EMPTY, HLT, 0, -1, \
                return errors;                                                                      \
   )

CMD("pop", REGISTER, POP, 1, 11, \
                if ((errors = stack_pop(&spu->stk, &out_val)))                                      \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
                                                                                                    \
                i++;                                                                                \
                i++;                                                                                \
                register_ip = (ProcessorRegisters) bytecode_ptr[i];                                 \
                switch (register_ip)                                                                \
                {                                                                                   \
                    case RAX:                                                                       \
                        spu->rax = out_val;                                                         \
                        break;                                                                      \
                                                                                                    \
                    case RBX:                                                                       \
                        spu->rbx = out_val;                                                         \
                        break;                                                                      \
                                                                                                    \
                    case RCX:                                                                       \
                        spu->rcx = out_val;                                                         \
                        break;                                                                      \
                                                                                                    \
                    case RDX:                                                                       \
                        spu->rdx = out_val;                                                         \
                        break;                                                                      \
                                                                                                    \
                    case IP:                                                                        \
                        printf("Error: can't pop ip register\n");                                   \
                        return errors;                                                              \
                        break;                                                                      \
                                                                                                    \
                    default:                                                                        \
                        MY_ASSERT(0 && "UNREACHABLE");                                              \
                        break;                                                                      \
                }                                                                                   \
   )

CMD("jmp", LABEL, JMP, 1, 12, \
                i++;                                                                                \
                i = (size_t) *((char *) &(bytecode_ptr[i]));                                        \
   )

CMD("jb", LABEL, JB, 1, 13, \
                if ((errors = stack_pop(&spu->stk, &in_val)))                                       \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
                if ((errors = stack_pop(&spu->stk, &out_val)))                                      \
                {                                                                                   \
                    return errors;                                                                  \
                }                                                                                   \
                i++;                                                                                \
                if (out_val < in_val)                                                               \
                {                                                                                   \
                    i = (size_t) *((char *) &(bytecode_ptr[i]));                                    \
                }                                                                                   \
                )
