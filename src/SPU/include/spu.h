#ifndef SPU_H
    #define SPU_H

    #include "stack.h"

    struct SoftProcessorUnit {
        Elem_t rax;
        Elem_t rbx;
        Elem_t rcx;
        Elem_t rdx;
        unsigned int ip;
        char * bytecode;
        Stack stk;
    };

    enum SPU_COMMANDS {
        HLT =  -1,
        PUSH = 1,
        ADD =  2,
        SUB =  3,
        MUL =  4,
        DIV =  5,
        SQRT = 6,
        SIN =  7,
        COS =  8,
        IN =   9,
        OUT =  10,
    };

    Error_t spu_process_comands(SoftProcessorUnit * spu, FILE * fp);

#endif // SPU_H
