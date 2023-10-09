#include <stdio.h>
#include <string.h>

#include "assembler.h"
#include "hash.h"
#include "my_assert.h"
#include "strings.h"
#include "stack.h"

AssemblerCommand ASSEMBLER_PUSH = {
    .command = "push",
    .num_of_params = 1,
    .size = 4,
    .hash = calculate_hash(const_cast <char *> ("push"), strlen("push")),
    .command_number = PUSH,
};

AssemblerCommand ASSEMBLER_ADD = {
    .command = "add",
    .num_of_params = 0,
    .size = 3,
    .hash = calculate_hash(const_cast <char *> ("add"), strlen("add")),
    .command_number = ADD,
};

AssemblerCommand ASSEMBLER_SUB = {
    .command = "sub",
    .num_of_params = 0,
    .size = 3,
    .hash = calculate_hash(const_cast <char *> ("sub"), strlen("sub")),
    .command_number = SUB,
};

AssemblerCommand ASSEMBLER_MUL = {
    .command = "mul",
    .num_of_params = 0,
    .size = 3,
    .hash = calculate_hash(const_cast <char *> ("mul"), strlen("mul")),
    .command_number = MUL,
};

AssemblerCommand ASSEMBLER_DIV = {
    .command = "div",
    .num_of_params = 0,
    .size = 3,
    .hash = calculate_hash(const_cast <char *> ("div"), strlen("div")),
    .command_number = DIV,
};

AssemblerCommand ASSEMBLER_SQRT = {
    .command = "sqrt",
    .num_of_params = 0,
    .size = 4,
    .hash = calculate_hash(const_cast <char *> ("sqrt"), strlen("sqrt")),
    .command_number = SQRT,
};

AssemblerCommand ASSEMBLER_SIN = {
    .command = "sin",
    .num_of_params = 0,
    .size = 3,
    .hash = calculate_hash(const_cast <char *> ("sin"), strlen("sin")),
    .command_number = SIN,
};

AssemblerCommand ASSEMBLER_COS = {
    .command = "cos",
    .num_of_params = 0,
    .size = 3,
    .hash = calculate_hash(const_cast <char *> ("cos"), strlen("cos")),
    .command_number = COS,
};

AssemblerCommand ASSEMBLER_IN = {
    .command = "in",
    .num_of_params = 0,
    .size = 2,
    .hash = calculate_hash(const_cast <char *> ("in"), strlen("in")),
    .command_number = IN,
};

AssemblerCommand ASSEMBLER_OUT = {
    .command = "out",
    .num_of_params = 0,
    .size = 3,
    .hash = calculate_hash(const_cast <char *> ("out"), strlen("out")),
    .command_number = OUT,
};

AssemblerCommand ASSEMBLER_HLT = {
    .command = "hlt",
    .num_of_params = 0,
    .size = 3,
    .hash = calculate_hash(const_cast <char *> ("hlt"), strlen("hlt")),
    .command_number = HLT,
};

AssemblerCommand ASSEMBLER_POP = {
    .command = "pop",
    .num_of_params = 1,
    .size = 3,
    .hash = calculate_hash(const_cast <char *> ("pop"), strlen("pop")),
    .command_number = POP,
};

AssemblerRegister ASSEMBLER_RAX = {
    .rgstr = "rax",
    .hash = calculate_hash(const_cast <char *> ("rax"), strlen("rax")),
    .value = 0,
    .ip = RAX,
};

AssemblerRegister ASSEMBLER_RBX = {
    .rgstr = "rbx",
    .hash = calculate_hash(const_cast <char *> ("rbx"), strlen("rbx")),
    .value = 0,
    .ip = RBX,
};

AssemblerRegister ASSEMBLER_RCX = {
    .rgstr = "rcx",
    .hash = calculate_hash(const_cast <char *> ("rcx"), strlen("rcx")),
    .value = 0,
    .ip = RCX,
};

AssemblerRegister ASSEMBLER_RDX = {
    .rgstr = "rdx",
    .hash = calculate_hash(const_cast <char *> ("rdx"), strlen("rdx")),
    .value = 0,
    .ip = RDX,
};

AssemblerRegister ASSEMBLER_IP = {
    .rgstr = "ip",
    .hash = calculate_hash(const_cast <char *> ("ip"), strlen("ip")),
    .value = 0,
    .ip = IP,
};

AssemblerErrors assembler_convert(char const * const * pointers, size_t strings_num, char * output_buffer)
{
    for (size_t i = 0; i < strings_num; i++)
    {
        char const * buffer_ptr = pointers[i];
        char command[MAX_COMMAND_SIZE] = "";
        sscanf(pointers[i], "%s", command);
        buffer_ptr = skip_word(buffer_ptr);
        Hash_t string_hash = calculate_hash(command, strlen(command));

        if (string_hash == ASSEMBLER_PUSH.hash)
        {
            Elem_t val = 0;
            char val_string[MAX_COMMAND_SIZE] = "";

            sprintf(output_buffer, "%d ", (int) ASSEMBLER_PUSH.command_number);
            output_buffer = next_word(output_buffer);

            if (sscanf(buffer_ptr, ELEM_SPEC, &val) == 1)
            {
                buffer_ptr = skip_word(buffer_ptr);
                sprintf(output_buffer, "%d ", (int) PUSH_NUMBER);
                output_buffer = next_word(output_buffer);
                sprintf(output_buffer, ELEM_SPEC " ", val);
                output_buffer = next_word(output_buffer);
            }
            else
            {
                sscanf(buffer_ptr, "%s", val_string);
                buffer_ptr = skip_word(buffer_ptr);
                sprintf(output_buffer, "%d ", (int) PUSH_REGISTER);
                output_buffer = next_word(output_buffer);

                Hash_t val_string_hash = calculate_hash (val_string, strlen(val_string));
                if      (val_string_hash == ASSEMBLER_RAX.hash) sprintf(output_buffer, "%d ", (int) ASSEMBLER_RAX.ip);
                else if (val_string_hash == ASSEMBLER_RBX.hash) sprintf(output_buffer, "%d ", (int) ASSEMBLER_RBX.ip);
                else if (val_string_hash == ASSEMBLER_RCX.hash) sprintf(output_buffer, "%d ", (int) ASSEMBLER_RCX.ip);
                else if (val_string_hash == ASSEMBLER_RDX.hash) sprintf(output_buffer, "%d ", (int) ASSEMBLER_RDX.ip);
                else if (val_string_hash == ASSEMBLER_IP.hash)  sprintf(output_buffer, "%d ", (int) ASSEMBLER_IP.ip);
                output_buffer = next_word(output_buffer);
            }
        }
        else if (string_hash == ASSEMBLER_ADD.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_ADD.command_number);
            output_buffer = next_word(output_buffer);
        }
        else if (string_hash == ASSEMBLER_SUB.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_SUB.command_number);
            output_buffer = next_word(output_buffer);
        }
        else if (string_hash == ASSEMBLER_MUL.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_MUL.command_number);
            output_buffer = next_word(output_buffer);
        }
        else if (string_hash == ASSEMBLER_DIV.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_DIV.command_number);
            output_buffer = next_word(output_buffer);
        }
        else if (string_hash == ASSEMBLER_SQRT.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_SQRT.command_number);
            output_buffer = next_word(output_buffer);
        }
        else if (string_hash == ASSEMBLER_SIN.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_SIN.command_number);
            output_buffer = next_word(output_buffer);
        }
        else if (string_hash == ASSEMBLER_COS.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_COS.command_number);
            output_buffer = next_word(output_buffer);
        }
        else if (string_hash == ASSEMBLER_IN.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_IN.command_number);
            output_buffer = next_word(output_buffer);
        }
        else if (string_hash == ASSEMBLER_OUT.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_OUT.command_number);
            output_buffer = next_word(output_buffer);
        }
        else if (string_hash == ASSEMBLER_HLT.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_HLT.command_number);
            output_buffer = next_word(output_buffer);
        }
        else if (string_hash == ASSEMBLER_POP.hash)
        {
            sprintf(output_buffer, "%d ", (int) ASSEMBLER_POP.command_number);
            output_buffer = next_word(output_buffer);

            char val_string[MAX_COMMAND_SIZE] = "";
            if (sscanf(buffer_ptr, "%s", val_string) != 1) return POP_ERROR;
            buffer_ptr = skip_word(buffer_ptr);
            Hash_t val_string_hash = calculate_hash(val_string, strlen(val_string));

            if (val_string_hash == ASSEMBLER_RAX.hash) sprintf (output_buffer, "%d ", (int) ASSEMBLER_RAX.ip);
            if (val_string_hash == ASSEMBLER_RBX.hash) sprintf (output_buffer, "%d ", (int) ASSEMBLER_RBX.ip);
            if (val_string_hash == ASSEMBLER_RCX.hash) sprintf (output_buffer, "%d ", (int) ASSEMBLER_RCX.ip);
            if (val_string_hash == ASSEMBLER_RDX.hash) sprintf (output_buffer, "%d ", (int) ASSEMBLER_RDX.ip);
            output_buffer = next_word(output_buffer);
        }

//         for (size_t j = 0; j < commands_array_size; j++)
//         {
//             if (string_hash == commands_array[j]->hash)
//             {
//                 sprintf(output_buffer, "%d ", (int) commands_array[j]->command_number);
//                 output_buffer = next_word(output_buffer);
//
//                 if (commands_array[j]->num_of_params > 0)
//                 {
//                     char val_string[MAX_COMMAND_SIZE] = "";
//                     Elem_t val = 0;
//
//                     if (sscanf(buffer_ptr, ELEM_SPEC, &val) != 0)
//                     {
//                         buffer_ptr = skip_word(buffer_ptr);
//                         sprintf(output_buffer, ELEM_SPEC " ", val);
//                         output_buffer = next_word(output_buffer);
//                     }
//                     else
//                     {
//                         sscanf(buffer_ptr, "%s", val_string);
//                         buffer_ptr = skip_word(buffer_ptr);
//                         Hash_t val_string_hash = calculate_hash(val_string, strlen(val_string));
//
//                         for (size_t k = 0; k < registers_array_size; k++)
//                         {
//                             if (ASSEMBLER_POP.hash == string_hash)
//                             {
//                                 sprintf(output_buffer, "%d ", (int) registers_array[i]->ip);
//                                 output_buffer = next_word(output_buffer);
//                                 break;
//                             }
//                             else if (registers_array[k]->hash == val_string_hash)
//                             {
//                                 sprintf(output_buffer, ELEM_SPEC " ", registers_array[k]->value);
//                                 output_buffer = next_word(output_buffer);
//                             }
//                         }
//                     }
//                 }
//             }
//         }
        // printf("Current output buffer : %s\n", output_buffer);
    }

    return NO_ERRORS;
}
