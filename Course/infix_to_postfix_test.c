#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include <stack>
#include "MexprcppEnums.h"
#include "ParserExport.h"
#include "MexprTree.h"
#include "Dtype.h"

static lex_data_t *
lex_data_dup (lex_data_t *lex_data) {

    lex_data_t *lex_data_new = (lex_data_t *)calloc (1, sizeof (lex_data_t));
    lex_data_new->token_code = lex_data->token_code;
    lex_data_new->token_len = lex_data->token_len;
    lex_data_new->token_val = lex_data->token_val;
    lex_data->token_val = NULL;
    return lex_data_new;
}

lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out) {

    int i;
    int out_index = 0;
    lex_data_t *lex_data;
    lex_data_t *lex_data_cpy;
    lex_data_t **lex_data_arr_out;
    std::stack <lex_data_t *> stack;

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
                            lex_data_arr_out[out_index++] = stack.top(); stack.pop();
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

static void
postfix_array_free(lex_data_t **lex_data_array, int size) {
   
    for (int i = 0; i < size; i++) {

        if (lex_data_array[i])
        {
            if (lex_data_array[i]->token_val) free(lex_data_array[i]->token_val);
            free(lex_data_array[i]);
        }
    }

    free(lex_data_array);
}

int 
main (int argc, char **argv) {

    int i;

    // a + b * c
    lex_data_t infix_array1[] = {

        {  MATH_CPP_VARIABLE, 1, "a" },
        {  PARSER_WHITE_SPACE, 1, " " },
        {  MATH_CPP_PLUS, 1, "+" },
        {  PARSER_WHITE_SPACE, 1, " " },
        {  MATH_CPP_VARIABLE, 1, "b" },
        {  PARSER_WHITE_SPACE, 1, " " },
        {  MATH_CPP_MUL, 1, "*" },
        {  PARSER_WHITE_SPACE, 3, "   " },
        {  MATH_CPP_VARIABLE, 1, "c" }

    };


    // max( a, b)
    lex_data_t infix_array2[] = {

        {  MATH_CPP_MAX, 1, "max" },
        {  MATH_CPP_VARIABLE, 1, "a" },
        {  MATH_CPP_VARIABLE, 1, "b" }

    };

    // a + sqr(b) * sqrt(c) + pow(d,e) 

    lex_data_t infix_array3[] = {

        {  MATH_CPP_VARIABLE, 1, "a" },
        {  MATH_CPP_PLUS, 1, "+" },
        {  MATH_CPP_SQR, 3, "sqr" },
        {  MATH_CPP_BRACKET_START, 1, "(" },
        {  MATH_CPP_VARIABLE, 1, "b" },
        {  MATH_CPP_BRACKET_END, 1, ")" },
        {  MATH_CPP_MUL, 1, "*" },
        {  MATH_CPP_SQRT, 4, "sqrt" },
        {  MATH_CPP_BRACKET_START, 1, "(" },
        {  MATH_CPP_VARIABLE, 1, "c" },
        {  MATH_CPP_BRACKET_END, 1, ")" },
        {  MATH_CPP_PLUS, 1, "+" },
        {  MATH_CPP_POW, 3, "pow" },
        {  MATH_CPP_BRACKET_START, 1, "(" },
        {  MATH_CPP_VARIABLE, 1, "d" },
        {  MATH_CPP_COMMA, 1, "," },
        {  MATH_CPP_VARIABLE, 1, "e" },
        {  MATH_CPP_BRACKET_END, 1, ")" }

    };    

    // ((-1*b) + sqrt(sqr(b) - 4*a*c))/(2*a)      square root formula

    lex_data_t infix_array4[] = {

        {  MATH_CPP_BRACKET_START, 1, "(" },
        {  MATH_CPP_BRACKET_START, 1, "(" },
        {  MATH_CPP_INT, 2, "-1" },
        {  MATH_CPP_MUL, 1, "*" },
        {  MATH_CPP_VARIABLE, 1, "b" },
        {  MATH_CPP_BRACKET_END, 1, ")" },
        {  MATH_CPP_PLUS, 1, "+" },
        {  MATH_CPP_SQRT, 4, "sqrt" },
        {  MATH_CPP_BRACKET_START, 1, "(" },
        {  MATH_CPP_SQR, 3, "sqr" },
        {  MATH_CPP_BRACKET_START, 1, "(" },
        {  MATH_CPP_VARIABLE, 1, "b" },
        {  MATH_CPP_BRACKET_END, 1, ")" },
        {  MATH_CPP_MINUS, 1, "-" },
        {  MATH_CPP_INT, 1, "4" },
        {  MATH_CPP_MUL, 1, "*" },
        {  MATH_CPP_VARIABLE, 1, "a" },
        {  MATH_CPP_MUL, 1, "*" },
        {  MATH_CPP_VARIABLE, 1, "c" },
        {  MATH_CPP_BRACKET_END, 1, ")" },
        {  MATH_CPP_BRACKET_END, 1, ")" },
        {  MATH_CPP_DIV, 1, "/" },
        {  MATH_CPP_BRACKET_START, 1, "(" },
        {  MATH_CPP_INT, 1, "2" },
        {  MATH_CPP_MUL, 1, "*" },
        {  MATH_CPP_VARIABLE, 1, "a" },
        {  MATH_CPP_BRACKET_END, 1, ")" }

    }; 

        // 2 + 3 + 4 
        lex_data_t infix_array5[] = {

        {  MATH_CPP_INT, 1, "2" },
        {  MATH_CPP_PLUS, 1, "+" },
        {  MATH_CPP_INT, 1, "3" },
        {  MATH_CPP_PLUS, 1, "+" },
        {  MATH_CPP_INT, 1, "4" }

    }; 

        // max (2, 3) + max (4, sqrt(16)) + 8 

        lex_data_t infix_array6[] = {

        {  MATH_CPP_MAX, 3, "max" },
        {  MATH_CPP_BRACKET_START, 1, "(" },        
        {  MATH_CPP_INT, 1, "2" },
        {  MATH_CPP_COMMA, 1, "," },
        {  MATH_CPP_INT, 1, "3" },
        {  MATH_CPP_BRACKET_END, 1, ")" },

        {  MATH_CPP_PLUS, 1, "+" },

        {  MATH_CPP_MAX, 3, "max" },
        {  MATH_CPP_BRACKET_START, 1, "(" },             
        {  MATH_CPP_INT, 1, "4" },
        {  MATH_CPP_COMMA, 1, "," },
        {  MATH_CPP_SQRT, 4, "sqrt" },
        {  MATH_CPP_BRACKET_START, 1, "(" },           
        {  MATH_CPP_INT, 2, "16" },
        {  MATH_CPP_BRACKET_END, 1, ")" },
        {  MATH_CPP_BRACKET_END, 1, ")" },

        {  MATH_CPP_PLUS, 1, "+" },

        {  MATH_CPP_INT, 1, "8" }

    }; 

        // 2 + 3 + "Hello" 
        lex_data_t infix_array7[] = {

        {  MATH_CPP_INT, 1, "2" },
        {  MATH_CPP_PLUS, 1, "+" },
        {  MATH_CPP_INT, 1, "3" },
        {  MATH_CPP_PLUS, 1, "+" },
        {  MATH_CPP_STRING, 5, "Hello" }

    }; 

    int size_out = 0;
    lex_data_t **postfix = mexpr_convert_infix_to_postfix (
                                        infix_array6,
                                        sizeof (infix_array6)/sizeof(infix_array6[0]),
                                        &size_out);

    printf ("Postfix : ");

    for (i = 0; i < size_out; i++) {

        lex_data_t *lex_data = postfix[i];
        printf ("%s ", lex_data->token_val);
    }
    printf ("\n");

    printf ("Constructing Expression Tree \n");

    MexprTree *tree = new MexprTree (postfix, size_out);

    printf ("Printing MexprTree : \n");
    MexprTree::InorderPrint (tree);
    printf ("\n");

    postfix_array_free (postfix, size_out);
    
    /* Validation Test */
    if (tree->validate (tree->root)) {

        printf ("Expression Tree is Valid\n");

        Dtype *res = tree->evaluate (tree->root);

        if (!res ) {
            printf ("Error : Expression Tree Could not be evaluated\n");
            return 0;
        }

        printf ("Result : ");
        switch (res->did) {

            case MATH_CPP_INT:
                printf ("%d\n",  reinterpret_cast <Dtype_INT *> (res)->dtype.int_val);
                break;
            case MATH_CPP_DOUBLE:
                printf ("%lf\n",  reinterpret_cast <Dtype_DOUBLE *> (res)->dtype.d_val);
                break;
            case MATH_CPP_STRING:
                printf ("%s\n",  reinterpret_cast <Dtype_STRING *> (res)->dtype.str_val.c_str());
                break;
            case MATH_CPP_BOOL:
            {
                Dtype_BOOL *dtype_b = reinterpret_cast <Dtype_BOOL *>(res);
                dtype_b->dtype.b_val == true ? printf ("True") : printf("False");
                printf("\n");
                break;
            }
            default:
                assert(0);
        }

        delete res;
    }
    else {
        printf ("Expression Tree is not Valid\n");
    }

    return 0;
}