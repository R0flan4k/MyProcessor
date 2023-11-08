CMD("push", PROCESSOR_SIGNATURE_NUMBER | PROCESSOR_SIGNATURE_REGISTER | PROCESSOR_SIGNATURE_RAM, PUSH, 1, 1,
                NEXT_BYTE;
                ARGUMENT_PROCESS(
                    ASSIGN_NUMBER(in_val);
                    SKIP_EIGHT_BYTES;
                    ,
                    REGISTER_PROCESS(
                        ASSIGN_REGISTER(in_val, rax),
                        ASSIGN_REGISTER(in_val, rbx),
                        ASSIGN_REGISTER(in_val, rcx),
                        ASSIGN_REGISTER(in_val, rdx),
                        ASSIGN_REGISTER(in_val, ip)
                    )
                    ,
                    UNREACHABLE;
                    ,
                    ARGUMENT_PROCESS(
                        ASSIGN_RAM(in_val, CURRENT_NUMBER);
                        SKIP_EIGHT_BYTES
                        ,
                        REGISTER_PROCESS(
                            ASSIGN_RAM(in_val, CURRENT_REGISTER(rax)),
                            ASSIGN_RAM(in_val, CURRENT_REGISTER(rbx)),
                            ASSIGN_RAM(in_val, CURRENT_REGISTER(rcx)),
                            ASSIGN_RAM(in_val, CURRENT_REGISTER(rdx)),
                            ASSIGN_RAM(in_val, CURRENT_REGISTER(ip))
                        );
                        ,
                        UNREACHABLE;
                        ,
                        UNREACHABLE;
                        ,
                        UNREACHABLE;
                    )
                    ,
                    UNREACHABLE;
                );

                SPU_STACK_PUSH(in_val);
    )

CMD("add", PROCESSOR_SIGNATURE_EMPTY, ADD, 0, 2,
                BINARY_OPERATION(ADDITION);
   )

CMD("sub", PROCESSOR_SIGNATURE_EMPTY, SUB, 0, 3,
                BINARY_OPERATION(SUBTRACTION);
   )

CMD("mul", PROCESSOR_SIGNATURE_EMPTY, MUL, 0, 4,
                BINARY_OPERATION(MULTIPLICATION);
   )

CMD("div", PROCESSOR_SIGNATURE_EMPTY, DIV, 0, 5,
                BINARY_OPERATION(DIVISION);
    )

CMD("sqrt", PROCESSOR_SIGNATURE_EMPTY, SQRT, 0, 6,
                UNARY_OPERATION(SQUARE_ROOT);
   )

CMD("sin", PROCESSOR_SIGNATURE_EMPTY, SIN, 0, 7,
                UNARY_OPERATION(SINUS);
   )

CMD("cos", PROCESSOR_SIGNATURE_EMPTY, COS, 0, 8,
                UNARY_OPERATION(COSINUS);
   )

CMD("in", PROCESSOR_SIGNATURE_EMPTY, IN, 0, 9,
                SCAN_VALUE(&in_val);
                SPU_STACK_PUSH(in_val);
    )

CMD("out", PROCESSOR_SIGNATURE_EMPTY, OUT, 0, 10,
                SPU_STACK_POP(&out_val);
                printf(ELEM_SPEC "\n", out_val);
   )

CMD("hlt", PROCESSOR_SIGNATURE_EMPTY, HLT, 0, -1,
                return errors;
   )

CMD("pop", PROCESSOR_SIGNATURE_REGISTER | PROCESSOR_SIGNATURE_RAM, POP, 1, 11,
                SPU_STACK_POP(&out_val);
                NEXT_BYTE;
                ARGUMENT_PROCESS(
                    UNREACHABLE;
                    ,
                    REGISTER_PROCESS(
                        ASSIGN_TO_REGISTER(rax, out_val),
                        ASSIGN_TO_REGISTER(rbx, out_val),
                        ASSIGN_TO_REGISTER(rcx, out_val),
                        ASSIGN_TO_REGISTER(rdx, out_val),
                        CANT_POP_IP_ERROR;
                    );
                    ,
                    UNREACHABLE;
                    ,
                    ARGUMENT_PROCESS(
                        ASSIGN_TO_RAM(CURRENT_NUMBER, out_val);
                        SKIP_EIGHT_BYTES;
                        ,
                        REGISTER_PROCESS(
                            ASSIGN_TO_RAM(CURRENT_REGISTER(rax), out_val),
                            ASSIGN_TO_RAM(CURRENT_REGISTER(rbx), out_val),
                            ASSIGN_TO_RAM(CURRENT_REGISTER(rcx), out_val),
                            ASSIGN_TO_RAM(CURRENT_REGISTER(rdx), out_val),
                            ASSIGN_TO_RAM(CURRENT_REGISTER(ip), out_val)
                        );
                        ,
                        UNREACHABLE;
                        ,
                        UNREACHABLE;
                        ,
                        UNREACHABLE;
                    );
                    ,
                    UNREACHABLE;
                );
   )

CMD("jmp", PROCESSOR_SIGNATURE_LABEL, JMP, 1, 12,
                NEXT_BYTE;
                JUMP;
   )

CMD("jb", PROCESSOR_SIGNATURE_LABEL, JB, 1, 13,
                SPU_STACK_POP(&in_val);
                SPU_STACK_POP(&out_val);
                NEXT_BYTE;
                JUMP_IF(out_val < in_val);
    )

CMD("ja", PROCESSOR_SIGNATURE_LABEL, JA, 1, 14,
                SPU_STACK_POP(&in_val);
                SPU_STACK_POP(&out_val);
                NEXT_BYTE;
                JUMP_IF(out_val > in_val);
    )

CMD("jae", PROCESSOR_SIGNATURE_LABEL, JAE, 1, 15,
                SPU_STACK_POP(&in_val);
                SPU_STACK_POP(&out_val);
                NEXT_BYTE;
                JUMP_IF(out_val > in_val || is_equal_double(out_val, in_val));
    )

CMD("jbe", PROCESSOR_SIGNATURE_LABEL, JBE, 1, 16,
                SPU_STACK_POP(&in_val);
                SPU_STACK_POP(&out_val);
                NEXT_BYTE;
                JUMP_IF(out_val < in_val || is_equal_double(out_val, in_val));
    )

CMD("je", PROCESSOR_SIGNATURE_LABEL, JE, 1, 17,
                SPU_STACK_POP(&in_val);
                SPU_STACK_POP(&out_val);
                NEXT_BYTE;
                JUMP_IF(is_equal_double(out_val, in_val));
    )

CMD("jne", PROCESSOR_SIGNATURE_LABEL, JNE, 1, 18,
                SPU_STACK_POP(&in_val);
                SPU_STACK_POP(&out_val);
                NEXT_BYTE;
                JUMP_IF(!is_equal_double(out_val, in_val));
    )

CMD("call", PROCESSOR_SIGNATURE_LABEL, CALL, 1, 19,
                SPU_CALL_STACK_PUSH(spu->ip);
                NEXT_BYTE;
                JUMP;
    )

CMD("ret", PROCESSOR_SIGNATURE_EMPTY, RET, 0, 20,
                SPU_CALL_STACK_POP(&out_val);
                spu->ip = (size_t) out_val;
                spu->ip++;
    )
