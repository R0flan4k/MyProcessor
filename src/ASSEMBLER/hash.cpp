#include <stdio.h>
#include <math.h>

#include "hash.h"

#ifndef NHASHPOTECTION

    Hash_t calculate_hash(void * stk, const size_t size)
    {
        if (stk != nullptr)
        {
            char * pointer = (char *) stk;
            char * end_pointer = (char *) stk + size - 1;
            Hash_t hash = 0;
            double value = 2;
            Hash_t mod = 100000;

            while (pointer < end_pointer)
            {
                hash += ((Hash_t) (pow(value, (double) (end_pointer - pointer)) * (*pointer))) % mod;

                pointer++;
            }

            return hash;
        }
        else
        {
            return 0;
        }
    }

#else // NHASHPROTECTION

    Hash_t calculate_hash(Stack * stk, const size_t size)
    {
        return (Hash_t) 0;
    }

#endif // NHASHPOTECTION
