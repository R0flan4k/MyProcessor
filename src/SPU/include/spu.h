#ifndef SPU_H
    #define SPU_H

    #include "stack.h"
    #include "file_processing.h"

    typedef Elem_t Register_t;

    struct SoftProcessorUnit {
        Register_t rax;
        Register_t rbx;
        Register_t rcx;
        Register_t rdx;
        unsigned int ip;
        char * bytecode;
        Stack stk;
    };

    enum PushMode {
        NULL_MODE =     0,
        PUSH_NUMBER =   1,
        PUSH_REGISTER = 2,
    };

    Error_t spu_process_comands(SoftProcessorUnit * spu, FILE * fp);

#endif // SPU_H
