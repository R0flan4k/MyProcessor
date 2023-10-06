#ifndef ASSEMBLER_H
    #define ASSEMBLER_H

    enum ASSEMBLER_COMMANDS {
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

    struct AssemblerCommand {
        const char * command;
        size_t size;
        int hash;
        ASSEMBLER_COMMANDS command_number;
    };

#endif // ASSEMBLER_H
