#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
#include "MexprcppEnums.h"
#include "ParserExport.h"

#define STACK_IMPL 



#ifdef STACK_IMPL

#define MAX_STACK_SIZE 256

typedef struct stack{
    int top;
    void* slot[MAX_STACK_SIZE];
    int count_of_push;
    int count_of_pop;
}Stack_t;

Stack_t*
get_new_stack(void);

int
reset_stack(Stack_t *stack);

int push(Stack_t *stack, void *node);

void* pop(Stack_t *stack);

void* StackGetTopElem(Stack_t *stack);
int isStackEmpty(Stack_t *stack);
void free_stack(Stack_t *stack);

Stack_t*
get_new_stack(void)
{
    Stack_t *stack = (Stack_t *)calloc(1, sizeof(Stack_t));
    if(!stack)
        return NULL;
    memset(stack, 0, sizeof(Stack_t));
    stack->top = -1;
    stack->count_of_push = 0;
    stack->count_of_pop = 0;
    return stack;
}

int
reset_stack(Stack_t *stack)
{
    if(!stack)
        return 0;

    memset(stack, 0, sizeof(Stack_t));
    stack->top = -1;
    return 0;
}

int push(Stack_t *stack, void *node)
{
    if(!stack || !node)
        return -1;
    if(stack->top < MAX_STACK_SIZE)
    {
        stack->top++;
        stack->slot[stack->top] = node;
        stack->count_of_push++;
        return 0;
     }
        printf("\nstack already full\n");
        return -1;
}

int isStackEmpty(Stack_t *stack)
{
    
    assert(stack);
     if(stack->top == -1) {
        return 1;
     }
     return 0;
}

void* pop(Stack_t *stack)
{
    void *ret = NULL;
    if(!stack) {
        return NULL;
    }

    if(stack->top == -1) {
        return NULL;
    }

    ret = stack->slot[stack->top];
    stack->slot[stack->top] = NULL;
    stack->top--;
    stack->count_of_pop++;
    return ret;
}

void* StackGetTopElem(Stack_t *stack)
{
    if(!stack || stack->top == -1) {
        return NULL;
    }
    return stack->slot[stack->top];
}

void free_stack(Stack_t *stack)
{
    if(!stack) {
        return;
    }
    free(stack);
}

#endif /* STACK_IMPL */




static lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out) {

    int i;
    int out_index = 0;
    lex_data_t *lex_data;

    Stack_t *stack = get_new_stack();

    lex_data_t **lex_data_arr_out = 
        (lex_data_t**)calloc(sizein, sizeof(lex_data_t *));

    for (i = 0; i < sizein; i++) {

            lex_data = &infix[i];

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

    int size_out = 0;
    lex_data_t **postfix = mexpr_convert_infix_to_postfix (
                                        infix_array4,
                                        sizeof (infix_array4)/sizeof(infix_array4[0]),
                                        &size_out);

    printf ("Postfix : ");

    for (i = 0; i < size_out; i++) {

        lex_data_t *lex_data = postfix[i];
        printf ("%s ", lex_data->token_val);
    }
    printf ("\n");

    return 0;
}