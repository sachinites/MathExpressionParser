#include <stdlib.h>
#include <memory.h>
#include "../RDBMSImplementation/SqlParser/ParserExport.h"
#include "MExprcppEnums.h"
#include "../RDBMSImplementation/SqlParser/SqlParserStruct.h"
#include "../RDBMSImplementation/core/rdbms_struct.h"

#include "MiniStack.cpp"

static bool 
mexpr_is_white_space (int token_code) {

    return (token_code == PARSER_EOL || token_code == PARSER_WHITE_SPACE);
}

static inline bool 
Math_is_operator (int token_code) {

    /* Supported Operators In MatheMatical Expression */

    switch (token_code) {

        case SQL_MATH_PLUS:
        case SQL_MATH_MINUS:
        case SQL_MATH_MUL:
        case SQL_MATH_DIV:
        case SQL_MATH_MAX:
        case SQL_MATH_MIN:
        case SQL_MATH_POW:
        case SQL_MATH_SIN:
        case SQL_MATH_COS:
        case SQL_MATH_SQR:
        case SQL_MATH_SQRT:
        case SQL_BRACKET_START:
        case SQL_BRACKET_END:
        case SQL_OR:
        case SQL_AND:
        case SQL_LESS_THAN:
	    case SQL_LESS_THAN_EQ: 
        case SQL_GREATER_THAN:
        case SQL_GREATER_THAN_EQ:
        case SQL_EQ:
        case SQL_NOT_EQ:
        return true;
    }

    return false;
}

static inline bool 
Math_is_unary_operator (int token_code) {

    /* Supported Operators In MatheMatical Expression */

    switch (token_code) {

        case SQL_MATH_SIN:
        case SQL_MATH_COS:
        case SQL_MATH_SQR:
        case SQL_MATH_SQRT:
        return true;
    }

    return false;
}

/* Higher the returned value, higher the precedence. 
    Return Minimum value for '(*/
static int 
Math_operator_precedence (int token_code) {

    assert ( Math_is_operator (token_code));

    switch (token_code) {

        case SQL_MATH_MAX:
        case SQL_MATH_MIN:
        case SQL_MATH_POW:
            return 7;
        case SQL_MATH_MUL:
        case SQL_MATH_DIV:
            return 6;            
        case SQL_MATH_PLUS:
        case SQL_MATH_MINUS:
            return 5;
        case SQL_MATH_SIN:
	    case SQL_MATH_COS:
        case SQL_MATH_SQR:
        case SQL_MATH_SQRT:
            return 4;
        case SQL_LESS_THAN:
	    case SQL_LESS_THAN_EQ:
        case SQL_GREATER_THAN:
        case SQL_NOT_EQ:
        case SQL_EQ:
            return 3;
        case SQL_AND:
            return 2;
        case SQL_OR:
            return 1;
        case SQL_BRACKET_START:
        case SQL_BRACKET_END:
            return 0;
    }
    assert(0);
    return 0;
} 

lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out) {

    int i;
    int out_index = 0;
    lex_data_t *lex_data;

    Stack_t *stack = get_new_stack();

    lex_data_t **lex_data_arr_out = 
        (lex_data_t**)calloc(MAX_EXPR_LEN, sizeof(lex_data_t *));

    for (i = 0; i < sizein; i++) {

            lex_data = &infix[i];

            if (mexpr_is_white_space (lex_data->token_code)) continue;

            if (lex_data->token_code == SQL_BRACKET_START)
            {
                    push(stack, (void *)lex_data);
            }
            else if (lex_data->token_code == SQL_BRACKET_END)
            {
                    while (!isStackEmpty(stack) && 
                        (((lex_data_t *)stack->slot[stack->top])->token_code != SQL_BRACKET_START)) {
                            lex_data_arr_out[out_index++] = (lex_data_t *)pop(stack);
                    }
                    pop(stack);

                    while (!isStackEmpty(stack)) {

                        lex_data = (lex_data_t *)StackGetTopElem(stack);

                        if (Math_is_unary_operator (lex_data->token_code)) {

                            lex_data_arr_out[out_index++] = (lex_data_t *)pop(stack);
                            continue;
                        }
                        break;
                    }
            }

            else if (lex_data->token_code == SQL_COMMA) {

                while (!isStackEmpty(stack) && 
                    (((lex_data_t *)stack->slot[stack->top])->token_code != SQL_BRACKET_START)) {
                            lex_data_arr_out[out_index++] = (lex_data_t *)pop(stack);
                }
            }

            else if (!Math_is_operator(lex_data->token_code))
            {
                    lex_data_arr_out[out_index++] = lex_data;
            }
            else if (isStackEmpty (stack)) {
                push(stack, (void *)lex_data);
            }
            else
            {
                    while (!isStackEmpty(stack) &&
                        !Math_is_unary_operator(lex_data->token_code) &&
                        (Math_operator_precedence(lex_data->token_code) <= 
                          Math_operator_precedence(((lex_data_t *)stack->slot[stack->top])->token_code))) {
                        
                        lex_data_arr_out[out_index++] = (lex_data_t *)pop(stack);
                    }
                    push(stack, (void *)lex_data);
            }
    }

    while (!isStackEmpty(stack)) {
        lex_data_arr_out[out_index++] = (lex_data_t *)pop(stack);
    }

    *size_out = out_index;
    free_stack(stack);
    return lex_data_arr_out;
}


/* Returns 1 For operator
    Returns -1 for Operands 
    Returns 0 for None
*/
int 
Mexpr_Enum_Convertor (int external_code, 
                                          mexprcpp_operators_t *opr_code, 
                                          mexprcpp_dtypes_t *dtype_code) {

    *opr_code = MATH_CPP_OPR_MAX;
    *dtype_code = MATH_CPP_DTYPE_INVALID;

    switch (external_code) {

        /* Operators */
        case SQL_MATH_MINUS:
            *opr_code = MATH_CPP_MINUS;
            return MEXPR_OPR;

        case SQL_MATH_PLUS:
             *opr_code = MATH_CPP_PLUS;
              return MEXPR_OPR;

        case SQL_MATH_MOD:
            *opr_code = MATH_CPP_MOD;
            return MEXPR_OPR;


        /* Operands*/
        case SQL_INTEGER_VALUE:
            *dtype_code = MATH_CPP_INT;
            return MEXPR_OPND;

        case SQL_DOUBLE_VALUE:
            *dtype_code = MATH_CPP_DOUBLE;
            return MEXPR_OPND;

        case SQL_STRING_VALUE:
            *dtype_code = MATH_CPP_STRING;
             return MEXPR_OPND;

        case SQL_IPV4_ADDR_VALUE:
            *dtype_code = MATH_CPP_IPV4;
            return MEXPR_OPND;

        case SQL_IDENTIFIER:
        case SQL_IDENTIFIER_IDENTIFIER:
            *dtype_code =  MATH_CPP_VARIABLE;
            return MEXPR_OPND;

        default:
            assert(0);
            return 0;
    }
    assert(0);
    return 0;
}

