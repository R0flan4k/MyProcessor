#ifndef PROCESSOR_H
    #define PROCESSOR_H

    enum ProcessorCommands {
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
        POP =  11,
    };

    enum ProcessorRegisters {
        RAX = 1,
        RBX = 2,
        RCX = 3,
        RDX = 4,
        IP =  5,
    };

    enum PushModes {
        REGISTER_MODE = 1 << 7,
        NUMBER_MODE =   1 << 6,
    };

#endif
