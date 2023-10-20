#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <list>
#include <string>
#include "../RDBMSImplementation/SqlParser/ParserExport.h"
#include "MExprcppEnums.h"
#include "../RDBMSImplementation/SqlParser/SqlParserStruct.h"

#include "MiniStack.cpp"

static int 
RDBMS_to_Mexpr_Enum_Convertor (int external_code, 
                                          mexprcpp_operators_t *opr_code, 
                                          mexprcpp_dtypes_t *dtype_code) ;
                                        
static lex_data_t **
mexpr_preprocess_infix_array (lex_data_t *infix, int sizein, int *size_out) {

    int i, j;
    int rc;
    bool error;
    lex_data_t *lex_out;
    lex_data_t *infix_lex_data;
    mexprcpp_dtypes_t dtype_code;
    mexprcpp_operators_t opr_code;

    *size_out = 0;
    error = false;

    lex_data_t **lex_data_arr_out = 
        (lex_data_t**)calloc(sizein, sizeof (lex_data_t *));

    j = 0;

    for (i = 0; i < sizein; i++) {

        infix_lex_data = &infix[i];

        if (infix_lex_data->token_code == PARSER_EOL  || 
             infix_lex_data->token_code == PARSER_WHITE_SPACE) {
            /* Remove unwanted tokens */
            continue;
        }

        rc = RDBMS_to_Mexpr_Enum_Convertor (
                                                infix_lex_data->token_code,
                                                &opr_code, &dtype_code);

        if (rc == 0) {
            error = true;
            printf ("Error : %s(%d) : Non-Convertible Token Found\n", __FUNCTION__, __LINE__);
            break;
        }

        lex_out = (lex_data_t *) calloc (1, sizeof (lex_data_t));
        lex_out->token_code = (rc == MEXPR_OPR)  ? (int) opr_code : (int)dtype_code;
        lex_out->token_len = infix_lex_data->token_len;
        lex_out->token_val = infix_lex_data->token_val;
        lex_data_arr_out[j++] = lex_out;
    }

    *size_out = j;

    int k;
    std::string *string_ptr; 
    std::list<std::string *> *str_lst_ptr;
    
        /* Now Fix up the Operators which operate on > 2 operands, 
            for example ' in ' Operator */

        for (i = 0; i < *size_out; i++) {
            
            if (lex_data_arr_out[i] == NULL) continue;

                switch (lex_data_arr_out[i]->token_code) {

                    case MATH_CPP_IN:
                    {
                        str_lst_ptr = new std::list<std::string *>();
                        k = i + 1;
                        assert(lex_data_arr_out[k]->token_code == MATH_CPP_BRACKET_START);
                        free(lex_data_arr_out[k]);
                        lex_data_arr_out[k] = NULL;
                        k++;
                        while (lex_data_arr_out[k]->token_code != MATH_CPP_BRACKET_END)
                        {
                            if (lex_data_arr_out[k]->token_code == MATH_CPP_STRING)
                            {
                                string_ptr = new std::string((char *)(lex_data_arr_out[k]->token_val));
                                str_lst_ptr->push_back(string_ptr);
                            }
                            free(lex_data_arr_out[k]);
                            lex_data_arr_out[k] = NULL;
                            k++;
                        }
                        free(lex_data_arr_out[k]);
                        lex_data_arr_out[k] = NULL;
                        lex_out = (lex_data_t *)calloc(1, sizeof(lex_data_t));
                        lex_out->token_code = MATH_CPP_STRING_LST;
                        lex_out->token_len = 0;
                        lex_out->token_val = (char *)str_lst_ptr;
                        lex_data_arr_out[i + 1] = lex_out;
                        i++;
                    }
                    break;
                    default:;
                }
        }

        if (error) {
            for (i = 0; i < *size_out; i++) {
                if (lex_data_arr_out[i]) free(lex_data_arr_out[i]);
            }
            free(lex_data_arr_out);
            lex_data_arr_out = NULL;
            *size_out = 0;
        }

    return lex_data_arr_out;
}


lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out) {

    int i;
    int out_index = 0;
    lex_data_t *lex_data;
    lex_data_t *lex_data_cpy;
    int infix_preprocessed_size;
    lex_data_t **lex_data_arr_out;
    lex_data_t **infix_preprocessed;

    /* Convert codes from Application to Mexpr Library, and combine the multiple 
        operands for Operators operating on multiple operands eg, IN Operator. Basically
        rearch the infix array to make it suitable to be consume by infix -> postfix conversion
        Algorithm*/
    infix_preprocessed = mexpr_preprocess_infix_array (infix, sizein, &infix_preprocessed_size);

    Stack_t *stack = get_new_stack();

    lex_data_arr_out = 
        (lex_data_t**)calloc(infix_preprocessed_size, sizeof(lex_data_t *));

    for (i = 0; i < infix_preprocessed_size; i++) {

            lex_data = infix_preprocessed[i];
            if (!lex_data) continue;
            infix_preprocessed[i] = NULL;

            if (lex_data->token_code == (int) MATH_CPP_OPR_INVALID) {
                free(lex_data);
                continue;
            }

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
                    free(pop(stack));

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
            /* If I am operand */
            else if (!Math_cpp_is_operator(lex_data->token_code)) {
                lex_data_arr_out[out_index++] = lex_data;
            }

            /* If I am operator and and stack is empty*/
            else if (isStackEmpty (stack)) {
                push(stack, (void *)lex_data);
            }

            /* If I am non-uniary operator and stack is not empty*/
            else if ( !Math_cpp_is_unary_operator(lex_data->token_code)) {

                while (!isStackEmpty(stack) &&
                       (Math_cpp_operator_precedence(lex_data->token_code) <=
                        Math_cpp_operator_precedence(((lex_data_t *)stack->slot[stack->top])->token_code))) {

                    lex_data_arr_out[out_index++] = (lex_data_t *)pop(stack);
                }
                push(stack, (void *)lex_data);
            }

            /* If I a unary Operator and stack is not empty*/
            else {
                push(stack, (void *)lex_data);
            }
    }

    while (!isStackEmpty(stack)) {
        lex_data_arr_out[out_index++] = (lex_data_t *)pop(stack);
    }

    *size_out = out_index;
    free_stack(stack);

    for (i = 0; i < infix_preprocessed_size; i++) {
        assert (infix_preprocessed[i] == NULL) ;
    }   
    free (infix_preprocessed);
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

        case SQL_IN:
            *opr_code = MATH_CPP_IN;
            return MEXPR_OPR;

        case SQL_BRACKET_START:
            *opr_code = MATH_CPP_BRACKET_START;
            return MEXPR_OPR;
        case SQL_BRACKET_END:
            *opr_code = MATH_CPP_BRACKET_END;
             return MEXPR_OPR;

        case SQL_OR:
            *opr_code = MATH_CPP_OR;
            return MEXPR_OPR;
        case SQL_AND:
             *opr_code = MATH_CPP_AND;
                return MEXPR_OPR;

        case SQL_MATH_SQR:
            *opr_code = MATH_CPP_SQR;
            return MEXPR_OPR;
        case SQL_MATH_SQRT:
            *opr_code = MATH_CPP_SQRT;
             return MEXPR_OPR;

        case SQL_MATH_MAX:
            *opr_code = MATH_CPP_MAX;
            return MEXPR_OPR;
        case SQL_MATH_MIN:
            *opr_code = MATH_CPP_MIN;
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

        /* Extras */
        case SQL_COMMA:
            *opr_code = MATH_CPP_COMMA;
             return MEXPR_OPR;

        default:
            return 0;
    }
    assert(0);
    return 0;
}

mexprcpp_dtypes_t
sql_to_mexpr_dtype_converter (sql_dtype_t sql_dtype) {

    switch (sql_dtype) {

        case SQL_INT:
            return MATH_CPP_INT;
        case SQL_DOUBLE:
            return MATH_CPP_DOUBLE;
        case SQL_STRING:
            return MATH_CPP_STRING;
        case SQL_IPV4_ADDR:
            return MATH_CPP_IPV4;
        default: 
            return MATH_CPP_DTYPE_INVALID;
    }
}

sql_dtype_t
mexpr_to_sql_dtype_converter (mexprcpp_dtypes_t dtype) {

    switch (dtype) {

        case MATH_CPP_INT:
            return SQL_INT;
        case MATH_CPP_DOUBLE:
            return SQL_DOUBLE;
        case MATH_CPP_STRING:
            return SQL_STRING;
        case MATH_CPP_IPV4:
            return SQL_IPV4_ADDR;
        default: 
            return SQL_DTYPE_MAX;
    }
}

mexprcpp_agg_t 
sql_to_mexpr_agg_fn_converter (sql_agg_fn_t agg_fn) {

    switch (agg_fn) {

        case SQL_SUM:
            return MATH_CPP_AGG_SUM;
        case SQL_MIN:
            return MATH_CPP_AGG_MIN;
        case SQL_MAX:
            return MATH_CPP_AGG_MAX;
        case SQL_COUNT:
            return MATH_CPP_AGG_COUNT;
        case SQL_AVG:
            return MATH_CPP_AGG_COUNT;
        default:
            assert(0);
    }
    return MATH_CPP_AGG_MAXX;
}



/* Register the library the converter fn */
int (*Mexpr_Enum_Convertor_fn_ptr) ( int external_code, 
                                          mexprcpp_operators_t *opr_code, 
                                          mexprcpp_dtypes_t *dtype_code)  = RDBMS_to_Mexpr_Enum_Convertor;