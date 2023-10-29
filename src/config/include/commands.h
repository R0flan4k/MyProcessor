CMD("push", PROCESSOR_SIGNATURE_NUMBER | PROCESSOR_SIGNATURE_REGISTER | PROCESSOR_SIGNATURE_RAM, PUSH, 1, 1,
                spu->ip++;                                                                                 //obshaya funkciya obrabotki po kolvy elementov
                switch ((ProcessorSignatures) bytecode_ptr[spu->ip])
                {
                    case PROCESSOR_SIGNATURE_NUMBER:
                        spu->ip++;
                        in_val = *((Elem_t *) (bytecode_ptr + spu->ip));
                        spu->ip += sizeof(Elem_t) - 1;
                        break;
                    case PROCESSOR_SIGNATURE_REGISTER:
                        spu->ip++;
                        register_ip = (ProcessorRegisters) bytecode_ptr[spu->ip];

                        switch (register_ip)
                        {
                            case PROCESSOR_REGISTER_RAX:
                                in_val = spu->rax;
                                break;

                            case PROCESSOR_REGISTER_RBX:
                                in_val = spu->rbx;
                                break;

                            case PROCESSOR_REGISTER_RCX:
                                in_val = spu->rcx;
                                break;

                            case PROCESSOR_REGISTER_RDX:
                                in_val = spu->rdx;
                                break;

                            case PROCESSOR_REGISTER_IP:
                                in_val = spu->ip;
                                break;

                            default:
                                MY_ASSERT(0 && "UNREACHABLE");
                                break;
                        }
                        break;
                    case PROCESSOR_SIGNATURE_EMPTY:
                        printf("Error: can't push null mode\n");
                        return errors;
                        break;
                    case PROCESSOR_SIGNATURE_LABEL:
                        printf("ABOBSA\n");
                        break;
                    case PROCESSOR_SIGNATURE_RAM:
                        spu->ip++;
                        switch ((ProcessorSignatures) bytecode_ptr[spu->ip])
                        {
                            case PROCESSOR_SIGNATURE_NUMBER:
                                spu->ip++;
                                in_val = spu->ram[(int) *((Elem_t *) (bytecode_ptr + spu->ip))];
                                spu->ip += sizeof(Elem_t) - 1;
                                break;

                            case PROCESSOR_SIGNATURE_REGISTER:
                                spu->ip++;

                                register_ip = (ProcessorRegisters) bytecode_ptr[spu->ip];
                                switch (register_ip)
                                {
                                    case PROCESSOR_REGISTER_RAX:
                                        in_val = spu->ram[(int) spu->rax];
                                        break;

                                    case PROCESSOR_REGISTER_RBX:
                                        in_val = spu->ram[(int) spu->rbx];
                                        break;

                                    case PROCESSOR_REGISTER_RCX:
                                        in_val = spu->ram[(int) spu->rcx];
                                        break;

                                    case PROCESSOR_REGISTER_RDX:
                                        in_val = spu->ram[(int) spu->rdx];
                                        break;

                                    case PROCESSOR_REGISTER_IP:
                                        in_val = spu->ram[(int) spu->ip];
                                        break;

                                    default:
                                        MY_ASSERT(0 && "UNREACHABLE");
                                        break;
                                }
                                break;
                            case PROCESSOR_SIGNATURE_RAM:
                            case PROCESSOR_SIGNATURE_LABEL:
                            case PROCESSOR_SIGNATURE_EMPTY:
                            default:
                                MY_ASSERT(0 && "UNREACHABLE");
                                break;
                        }
                        break;
                    default:
                        MY_ASSERT(0 && "UNREACHABLE");
                        break;
                }
                SPU_STACK_PUSH(in_val)
    )

CMD("add", PROCESSOR_SIGNATURE_EMPTY, ADD, 0, 2,
                if ((errors = spu_binary(&spu->stk, BINARY_MATH_OPERATION_ADDITION)))
                {
                    return errors;
                }
   )

CMD("sub", PROCESSOR_SIGNATURE_EMPTY, SUB, 0, 3,
                if ((errors = spu_binary(&spu->stk, BINARY_MATH_OPERATION_SUBTRACTION)))
                {
                    return errors;
                }
   )

CMD("mul", PROCESSOR_SIGNATURE_EMPTY, MUL, 0, 4,
                if ((errors = spu_binary(&spu->stk, BINARY_MATH_OPERATION_MULTIPLICATION)))
                {
                    return errors;
                }
   )

CMD("div", PROCESSOR_SIGNATURE_EMPTY, DIV, 0, 5,
                if ((errors = spu_binary(&spu->stk, BINARY_MATH_OPERATION_DIVISION)))
                {
                    return errors;
                }
            )

CMD("sqrt", PROCESSOR_SIGNATURE_EMPTY, SQRT, 0, 6,
                if ((errors = spu_unary(&spu->stk, UNARY_MATH_OPERATION_SQUARE_ROOT)))
                {
                    return errors;
                }
   )

CMD("sin", PROCESSOR_SIGNATURE_EMPTY, SIN, 0, 7,
                if ((errors = spu_unary(&spu->stk, UNARY_MATH_OPERATION_SINUS)))
                {
                    return errors;
                }
   )

CMD("cos", PROCESSOR_SIGNATURE_EMPTY, COS, 0, 8,
                if ((errors = spu_unary(&spu->stk, UNARY_MATH_OPERATION_COSINUS)))
                {
                    return errors;
                }
   )

CMD("in", PROCESSOR_SIGNATURE_EMPTY, IN, 0, 9,
                if (!scanf(ELEM_SPEC, &in_val))
                {
                    printf("Error: Invalid input.\n");
                    break;
                }
                SPU_STACK_PUSH(in_val)
    )

CMD("out", PROCESSOR_SIGNATURE_EMPTY, OUT, 0, 10,
                SPU_STACK_POP(&out_val)
                printf(ELEM_SPEC "\n", out_val);
   )

CMD("hlt", PROCESSOR_SIGNATURE_EMPTY, HLT, 0, -1,
                return errors;
   )

CMD("pop", PROCESSOR_SIGNATURE_REGISTER | PROCESSOR_SIGNATURE_RAM, POP, 1, 11,
                if ((errors = stack_pop(&spu->stk, &out_val)))
                {
                    return errors;
                }
                spu->ip++;
                switch ((ProcessorSignatures) bytecode_ptr[spu->ip])
                {
                    case PROCESSOR_SIGNATURE_REGISTER:
                        spu->ip++;
                        register_ip = (ProcessorRegisters) bytecode_ptr[spu->ip];
                        switch (register_ip)
                        {
                            case PROCESSOR_REGISTER_RAX:
                                spu->rax = out_val;
                                break;

                            case PROCESSOR_REGISTER_RBX:
                                spu->rbx = out_val;
                                break;

                            case PROCESSOR_REGISTER_RCX:
                                spu->rcx = out_val;
                                break;

                            case PROCESSOR_REGISTER_RDX:
                                spu->rdx = out_val;
                                break;

                            case PROCESSOR_REGISTER_IP:
                                printf("Error: can't pop ip register\n");
                                return errors;
                                break;

                            default:
                                MY_ASSERT(0 && "UNREACHABLE");
                                break;
                        }
                        break;

                    case PROCESSOR_SIGNATURE_RAM:
                        spu->ip++;
                        switch ((ProcessorSignatures) bytecode_ptr[spu->ip])
                        {
                            case PROCESSOR_SIGNATURE_NUMBER:
                                spu->ip++;
                                spu->ram[(int) *((Elem_t *) (bytecode_ptr + spu->ip))] = out_val;
                                spu->ip += sizeof(Elem_t) - 1;
                                break;

                            case PROCESSOR_SIGNATURE_REGISTER:
                                spu->ip++;

                                register_ip = (ProcessorRegisters) bytecode_ptr[spu->ip];
                                switch (register_ip)
                                {
                                    case PROCESSOR_REGISTER_RAX:
                                        spu->ram[(int) spu->rax] = out_val;
                                        break;

                                    case PROCESSOR_REGISTER_RBX:
                                        spu->ram[(int) spu->rbx] = out_val;
                                        break;

                                    case PROCESSOR_REGISTER_RCX:
                                        spu->ram[(int) spu->rcx] = out_val;
                                        break;

                                    case PROCESSOR_REGISTER_RDX:
                                        spu->ram[(int) spu->rdx] = out_val;
                                        break;

                                    case PROCESSOR_REGISTER_IP:
                                        spu->ram[(int) spu->ip] = out_val;
                                        break;

                                    default:
                                        MY_ASSERT(0 && "UNREACHABLE");
                                        break;
                                }
                                break;
                            case PROCESSOR_SIGNATURE_RAM:
                            case PROCESSOR_SIGNATURE_LABEL:
                            case PROCESSOR_SIGNATURE_EMPTY:
                            default:
                                MY_ASSERT(0 && "UNREACHABLE");
                                break;
                        }
                        break;

                    case PROCESSOR_SIGNATURE_NUMBER:
                    case PROCESSOR_SIGNATURE_LABEL:
                    case PROCESSOR_SIGNATURE_EMPTY:
                    default:
                        MY_ASSERT(0 && "UNREACHABLE");
                        break;
                }
   )

CMD("jmp", PROCESSOR_SIGNATURE_LABEL, JMP, 1, 12,
                spu->ip++;
                spu->ip = (size_t) *((char *) &(bytecode_ptr[spu->ip])) - 1;
   )

CMD("jb", PROCESSOR_SIGNATURE_LABEL, JB, 1, 13,
                SPU_STACK_POP(&in_val)
                SPU_STACK_POP(&out_val)
                spu->ip++;
                if (out_val < in_val)
                {
                    spu->ip = (size_t) *((char *) &(bytecode_ptr[spu->ip])) - 1;/*  */
                }
    )

CMD("ja", PROCESSOR_SIGNATURE_LABEL, JA, 1, 14,
                SPU_STACK_POP(&in_val)
                SPU_STACK_POP(&out_val)
                spu->ip++;
                if (out_val > in_val)
                {
                    spu->ip = (size_t) *((char *) &(bytecode_ptr[spu->ip])) - 1;
                }
    )

CMD("jae", PROCESSOR_SIGNATURE_LABEL, JAE, 1, 15,
                SPU_STACK_POP(&in_val)
                SPU_STACK_POP(&out_val)
                spu->ip++;
                if (out_val > in_val || is_equal_double(out_val, in_val))
                {
                    spu->ip = (size_t) *((char *) &(bytecode_ptr[spu->ip])) - 1;
                }
    )

CMD("jbe", PROCESSOR_SIGNATURE_LABEL, JBE, 1, 16,
                SPU_STACK_POP(&in_val)
                SPU_STACK_POP(&out_val)
                spu->ip++;
                if (out_val < in_val || is_equal_double(out_val, in_val))
                {
                    spu->ip = (size_t) *((char *) &(bytecode_ptr[spu->ip])) - 1;
                }
    )

CMD("je", PROCESSOR_SIGNATURE_LABEL, JE, 1, 17,
                SPU_STACK_POP(&in_val)
                SPU_STACK_POP(&out_val)
                spu->ip++;
                if (is_equal_double(out_val, in_val))
                {
                    spu->ip = (size_t) *((char *) &(bytecode_ptr[spu->ip])) - 1;
                }
    )

CMD("jne", PROCESSOR_SIGNATURE_LABEL, JNE, 1, 18,
                SPU_STACK_POP(&in_val)
                SPU_STACK_POP(&out_val)
                spu->ip++;
                if (!is_equal_double(out_val, in_val))
                {
                    spu->ip = (size_t) *((char *) &(bytecode_ptr[spu->ip])) - 1;
                }
    )

CMD("call", PROCESSOR_SIGNATURE_LABEL, CALL, 1, 19,
                if ((errors = stack_push(&spu->call_stk, spu->ip)))
                {
                    return errors;
                }
                spu->ip++;
                spu->ip = (size_t) *((char *) &(bytecode_ptr[spu->ip])) - 1;
    )

CMD("ret", PROCESSOR_SIGNATURE_EMPTY, RET, 0, 20,
                if ((errors = stack_pop(&spu->call_stk, &out_val)))
                {
                    return errors;
                }
                spu->ip = (size_t) out_val;
                spu->ip++;
    )
