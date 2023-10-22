#ifndef PROCESSOR_H
    #define PROCESSOR_H

    enum ProcessorCommands {
    #define CMD(str, signature, enum_id, num_of_params, id, code) \
        enum_id = id,

        #include "commands.h"

    #undef CMD
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
