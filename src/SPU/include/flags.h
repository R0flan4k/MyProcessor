#ifndef FLAGS_H
    #define FLAGS_H

    #include "stack.h"
    #include "cmd_input.h"

    extern CmdLineArg SPU_FILE;

    extern char * SPU_FILE_NAME;

    extern char * * cmd_input;
    extern CmdLineArg * FLAGS[];
    extern size_t FLAGS_ARRAY_SIZE;

    void set_spu_file_name_flag(void);

#endif // FLAGS_H
