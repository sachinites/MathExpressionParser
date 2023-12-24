#include <stdlib.h>
#include "MexprcppEnums.h"
#include "ParserExport.h"
#include <stack>

static lex_data_t *
lex_data_dup (lex_data_t *lex_data) {

    lex_data_t *lex_data_new = (lex_data_t *)calloc (1, sizeof (lex_data_t));
    lex_data_new->token_code = lex_data->token_code;
    lex_data_new->token_len = lex_data->token_len;
    lex_data_new->token_val = lex_data->token_val;
    lex_data->token_val = NULL;
    return lex_data_new;
}

extern int 
Appln_to_Mexpr_enum_converter(int token_code);

lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out) {

    int i;
    int out_index = 0;
    lex_data_t *lex_data;
    lex_data_t *lex_data_cpy;
    lex_data_t **lex_data_arr_out;
    std::stack <lex_data_t *> stack;

    // replace all token codes in infix array with the MeprcppEnums.h Enums
    for (i = 0; i < sizein; i++) {

        lex_data = &infix[i];
        if (lex_data->token_code == PARSER_EOL ||
             lex_data->token_code == PARSER_WHITE_SPACE) continue;

        /* Convert SqlEnums to Mexpr Enums*/
        lex_data->token_code = Appln_to_Mexpr_enum_converter(lex_data->token_code);
        assert (lex_data->token_code != -1);
     }

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
                    stack.push(lex_data);
            }
            else if (lex_data->token_code == (int)MATH_CPP_BRACKET_END)
            {
                    while (!stack.empty() &&
                        ((stack.top())->token_code != (int)MATH_CPP_BRACKET_START)) {
                            lex_data_arr_out[out_index++] = lex_data_dup(stack.top()); stack.pop();
                    }
                    stack.pop();

                    while (!stack.empty()) {

                        lex_data = stack.top();

                        if (Math_cpp_is_unary_operator (lex_data->token_code)) {
                            lex_data_arr_out[out_index++] = lex_data_dup(stack.top());
                            stack.pop();
                            continue;
                        }
                        break;
                    }
            }

            else if (lex_data->token_code == (int) MATH_CPP_COMMA) {

                while (!stack.empty() && 
                    ((stack.top())->token_code != (int)MATH_CPP_BRACKET_START)) {
                            lex_data_arr_out[out_index++] = lex_data_dup(stack.top());
                    stack.pop();
                }
            }
            /* If I am operand */
            else if (!Math_cpp_is_operator(lex_data->token_code)) {
                lex_data_arr_out[out_index++] = lex_data_dup(lex_data);
            }

            /* If I am operator and and stack is empty*/
            else if (stack.empty())  {
                stack.push (lex_data);
            }

            /* If I am non-uniary operator and stack is not empty*/
            else if ( !Math_cpp_is_unary_operator(lex_data->token_code)) {

                while (!stack.empty() &&
                       (Math_cpp_operator_precedence(lex_data->token_code) <=
                        Math_cpp_operator_precedence((stack.top())->token_code))) {

                    lex_data_arr_out[out_index++] = lex_data_dup (stack.top());
                    stack.pop();
                }
                stack.push(lex_data);
            }

            /* If I a unary Operator and stack is not empty*/
            else {
                 stack.push(lex_data);
            }
    }

    while (!stack.empty()) {
        lex_data_arr_out[out_index++] =  lex_data_dup (stack.top());
        stack.pop();
    }

    *size_out = out_index;
    return lex_data_arr_out;
}