#ifndef ARITHMETIC_H
    #define ARITHMETIC_H

    #include "stack.h"

    enum SpuBinaryMathOperations {
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
    };

    enum SpuUnaryMathOperations {
        SQUARE_ROOT,
        SINUS,
        COSINUS,
    };

    Error_t get_two_values(Stack * stk, Elem_t * val1, Elem_t * val2);
    Error_t spu_binary(Stack * stk, SpuBinaryMathOperations mode);
    Error_t spu_unary(Stack * stk, SpuUnaryMathOperations mode);
    Error_t spu_in(Stack * stk);

#endif
