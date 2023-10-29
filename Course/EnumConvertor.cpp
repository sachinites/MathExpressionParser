#include <stdlib.h>
#include "MexprcppEnums.h"
#include "ParserExport.h"

#include "MiniStack.cpp"

lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out) {

    int i;
    int out_index = 0;
    lex_data_t *lex_data;
    lex_data_t *lex_data_cpy;
    lex_data_t **lex_data_arr_out;

    Stack_t *stack = get_new_stack();

    lex_data_arr_out = 
        (lex_data_t**)calloc(sizein, sizeof(lex_data_t *));

    for (i = 0; i < sizein; i++) {

            lex_data = &infix[i];
            if (!lex_data) continue;

            if ( lex_data->token_code == PARSER_WHITE_SPACE || 
                  lex_data->token_code == PARSER_EOL) continue;

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
    return lex_data_arr_out;
}