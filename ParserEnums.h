#ifndef __PARSER_ENUMS__
#define __PARSER_ENUMS__

/* Update the values of these enums to match with the values used by 
    External project which is using this MathExpression Library*/

typedef enum parser_enums_ {

    PARSER_LESS_THAN,
    PARSER_GREATER_THAN,
    PARSER_EQ,
    PARSER_NOT_EQ,
    PARSER_OR,
    PARSER_AND,
    PARSER_EOL,
    PARSER_BRACKET_START,
    PARSER_BRACKET_END,
    PARSER_COMMA,
    PARSER_WHITE_SPACE,
    PARSER_OPERAND_LEN
    
} parser_enums_t;


#endif 