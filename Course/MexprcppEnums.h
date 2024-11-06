#ifndef MEXPR_CPP_ENUMS_H
#define MEXPR_CPP_ENUMS_H

#include <assert.h>
#include <stdbool.h>

#define MEXPR_OPR 1
#define MEXPR_OPND -1
#define MEXPR_INVALID_CODE 0

typedef enum {
    /* Mathematical Operators */
    MATH_CPP_OPR_FIRST, //0
    MATH_CPP_MOD,
    MATH_CPP_PLUS,
    MATH_CPP_MINUS,
    MATH_CPP_MUL,
    MATH_CPP_DIV,
    MATH_CPP_SQR,
    MATH_CPP_SQRT, 
    MATH_CPP_MAX,
    MATH_CPP_MIN,
    MATH_CPP_SIN,
    MATH_CPP_COS,
    MATH_CPP_POW, //12

    /* Inequality Operators */
    MATH_CPP_EQ,
    MATH_CPP_NEQ,
    MATH_CPP_LESS_THAN,
    MATH_CPP_LESS_THAN_EQ,
    MATH_CPP_GREATER_THAN_EQ,
    MATH_CPP_GREATER_THAN, //18

    /* Logical Operators */
    MATH_CPP_OR,
    MATH_CPP_AND,

    /* Other Math Expression Entities */
    MATH_CPP_BRACKET_START, //21
    MATH_CPP_BRACKET_END,
    MATH_CPP_COMMA,
    MATH_CPP_OPR_INVALID,
    MATH_CPP_OPR_MAX

} mexprcpp_operators_t;

typedef enum {
    // 26
    MATH_CPP_DTYPE_FIRST = (int)MATH_CPP_OPR_MAX + 1,
    MATH_CPP_INT,
    MATH_CPP_DOUBLE,
    MATH_CPP_STRING,
    MATH_CPP_IPV4,
    MATH_CPP_BOOL,
    MATH_CPP_VARIABLE,
    MATH_CPP_DTYPE_LAST,
    // 34
    MATH_CPP_DTYPE_WILDCARD, // Corrected typo
    MATH_CPP_DTYPE_INVALID,
    MATH_CPP_IDENTIFIER_IDENTIFIER,
    MATH_CPP_DTYPE_MAX,

} mexprcpp_dtypes_t;

typedef enum {
    // 38
    PARSER_EOL = (int)MATH_CPP_DTYPE_MAX + 1,
    PARSER_QUIT,
    PARSER_WHITE_SPACE,
} mexprcpp_parser_control_t;

static inline int Math_cpp_operator_precedence(int token_code)
{
    mexprcpp_operators_t opr_code = (mexprcpp_operators_t)token_code;

    switch (token_code) {
    case MATH_CPP_MAX:
    case MATH_CPP_MIN:
    case MATH_CPP_POW:
        return 7;
    case MATH_CPP_MUL:
    case MATH_CPP_DIV:
        return 6;
    case MATH_CPP_PLUS:
    case MATH_CPP_MINUS:
        return 5;
    case MATH_CPP_SIN:
    case MATH_CPP_COS:
    case MATH_CPP_SQR:
    case MATH_CPP_SQRT:
        return 4;
    case MATH_CPP_LESS_THAN:
    case MATH_CPP_LESS_THAN_EQ:
    case MATH_CPP_GREATER_THAN:
    case MATH_CPP_NEQ:
    case MATH_CPP_EQ:
        return 3;
    case MATH_CPP_AND:
        return 2;
    case MATH_CPP_OR:
        return 1;
    case MATH_CPP_BRACKET_START:
    case MATH_CPP_BRACKET_END:
        return 0;
    default:
        return -1; // Return -1 for invalid precedence
    }
}

static inline bool Math_cpp_is_operator(int opcode)
{
    return (opcode >= (int)MATH_CPP_OPR_FIRST && opcode < (int)MATH_CPP_OPR_MAX);
}

static inline bool Math_cpp_is_operand(int opcode)
{
    return (opcode >= (int)MATH_CPP_DTYPE_FIRST && opcode < (int)MATH_CPP_DTYPE_LAST);
}

static inline bool Math_cpp_is_unary_operator(int opcode)
{
    if (!Math_cpp_is_operator(opcode))
        return false;

    switch ((mexprcpp_operators_t)opcode) {
    case MATH_CPP_SIN:
    case MATH_CPP_COS:
    case MATH_CPP_SQR:
    case MATH_CPP_SQRT:
        return true;
    default:
        return false;
    }
}

#endif // MEXPR_CPP_ENUMS_H
