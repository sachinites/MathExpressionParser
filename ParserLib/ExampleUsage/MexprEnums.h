#ifndef __MEXPR_ENUMS__
#define __MEXPR_ENUMS__

/* Update the values of these enums to match with the values used by 
    External project which is using this MathExpression Library*/

typedef enum mexpr_enums_ {

    MATH_LESS_THAN = 5001,
    MATH_GREATER_THAN,
    MATH_EQ,
    MATH_NOT_EQ,
    MATH_OR,
    MATH_AND,
    MATH_BRACKET_START,
    MATH_BRACKET_END,
    MATH_WHITE_SPACE,
    MATH_IDENTIFIER,  
    MATH_IDENTIFIER_IDENTIFIER,
    MATH_MUL,
    MATH_DIV,
    MATH_SQR,
    MATH_SQRT,
    MATH_MAX,
    MATH_MIN,
    MATH_PLUS,
    MATH_MINUS,
    MATH_SIN,
    MATH_COS,
    MATH_POW,
    MATH_INTEGER_VALUE,
    MATH_DOUBLE_VALUE,
    MATH_COMMA
    
} mexpr_enums_t;


#endif 
