#include <stdlib.h>
#include <memory.h>
#include "../RDBMSImplementation/SqlParser/ParserExport.h"
#include "MExprcppEnums.h"
#include "../RDBMSImplementation/SqlParser/SqlParserStruct.h"

#include "MiniStack.cpp"

static int 
RDBMS_to_Mexpr_Enum_Convertor (int external_code, 
                                          mexprcpp_operators_t *opr_code, 
                                          mexprcpp_dtypes_t *dtype_code) ;
                                        
static void 
Converter_convert_app_to_expression_library_codes (lex_data_t *infix,  int sizein) {

    int i, rc;
    mexprcpp_dtypes_t dtype_code;
    mexprcpp_operators_t opr_code;

    for (i = 0; i < sizein; i++) {

        if (infix[i].token_code == PARSER_EOL  || 
             infix[i].token_code == PARSER_WHITE_SPACE) {
            
            infix[i].token_code = (int)MATH_CPP_OPR_INVALID;
            continue;
        }

        rc = RDBMS_to_Mexpr_Enum_Convertor (infix[i].token_code,
                                                &opr_code, &dtype_code);

        if (rc == 0 ) 
            infix[i].token_code =  (int)MATH_CPP_OPR_INVALID;
        else 
            infix[i].token_code = (rc == MEXPR_OPR)  ? (int) opr_code : (int)dtype_code;

    }
}

lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out) {

    int i;
    int out_index = 0;
    lex_data_t *lex_data;

    /* Convert codes from Application to Mexpr Library*/
    Converter_convert_app_to_expression_library_codes (infix, sizein);

    Stack_t *stack = get_new_stack();

    lex_data_t **lex_data_arr_out = 
        (lex_data_t**)calloc(sizein, sizeof(lex_data_t *));

    for (i = 0; i < sizein; i++) {

            lex_data = &infix[i];

            if (lex_data->token_code == (int) MATH_CPP_OPR_INVALID) continue;
            if (!Math_cpp_is_operator (lex_data->token_code)  &&
                    !Math_cpp_is_operand (lex_data->token_code)) assert(0);

            if (lex_data->token_code == (int)MATH_CPP_BRACKET_START)
            {
                    push(stack, (void *)lex_data);
            }
            else if (lex_data->token_code == (int)MATH_CPP_BRACKET_END)
            {
                    while (!isStackEmpty(stack) && 
                        (((lex_data_t *)stack->slot[stack->top])->token_code != (int)MATH_CPP_BRACKET_START)) {
                            lex_data_arr_out[out_index++] = (lex_data_t *)pop(stack);
                    }
                    pop(stack);

                    while (!isStackEmpty(stack)) {

                        lex_data = (lex_data_t *)StackGetTopElem(stack);

                        if (Math_cpp_is_unary_operator (lex_data->token_code)) {

                            lex_data_arr_out[out_index++] = (lex_data_t *)pop(stack);
                            continue;
                        }
                        break;
                    }
            }

            else if (lex_data->token_code == (int) MATH_CPP_COMMA) {

                while (!isStackEmpty(stack) && 
                    (((lex_data_t *)stack->slot[stack->top])->token_code != (int)MATH_CPP_BRACKET_START)) {
                            lex_data_arr_out[out_index++] = (lex_data_t *)pop(stack);
                }
            }

            else if (!Math_cpp_is_operator(lex_data->token_code)) {
                
                lex_data_arr_out[out_index++] = lex_data;
            }
            else if (isStackEmpty (stack)) {
                
                push(stack, (void *)lex_data);
            }
            else {
                while (!isStackEmpty(stack) &&
                       !Math_cpp_is_unary_operator(lex_data->token_code) &&
                       (Math_cpp_operator_precedence(lex_data->token_code) <=
                        Math_cpp_operator_precedence(((lex_data_t *)stack->slot[stack->top])->token_code))) {

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
RDBMS_to_Mexpr_Enum_Convertor (int external_code, 
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

        case SQL_MATH_MUL:
            *opr_code = MATH_CPP_MUL;
            return MEXPR_OPR;

        case SQL_MATH_DIV:
            *opr_code = MATH_CPP_DIV;
            return MEXPR_OPR;
            
        case SQL_EQ:
            *opr_code = MATH_CPP_EQ;
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
            return 0;
    }
    assert(0);
    return 0;
}

/* Register the library the converter fn */
int (*Mexpr_Enum_Convertor_fn_ptr) ( int external_code, 
                                          mexprcpp_operators_t *opr_code, 
                                          mexprcpp_dtypes_t *dtype_code)  = RDBMS_to_Mexpr_Enum_Convertor;