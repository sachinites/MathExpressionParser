#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "MexprEnums.h"
#include "MExpr.h"
#include "UserParserL.h"

/* ====================x================x=================== */
/* Internal Stack Implementation */

#define MAX_STACK_SIZE 256

typedef struct stack{
    int top;
    void* slot[MAX_STACK_SIZE];
    int count_of_push;
    int count_of_pop;
}Stack_t;

static Stack_t*
get_new_stack(void);
static int push(Stack_t *stack, void *node);
static void* pop(Stack_t *stack);
static int isStackEmpty(Stack_t *stack);
static void free_stack(Stack_t *stack);
static void* StackGetTopElem(Stack_t *stack);

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

void* 
StackGetTopElem(Stack_t *stack) {

    if(!stack || stack->top == -1)  return NULL;
    return stack->slot[stack->top];
}

int 
isStackEmpty(Stack_t *stack) {

    assert(stack);
    if (stack->top == -1) return 1;
    return 0;
}

void* 
pop(Stack_t *stack) {

    void *ret = NULL;
    if(!stack) return NULL;
    if(stack->top == -1) return NULL;
    ret = stack->slot[stack->top];
    stack->slot[stack->top] = NULL;
    stack->top--;
    stack->count_of_pop++;
    return ret;
}

int 
push(Stack_t *stack, void *node) {
    if(!stack || !node) return -1;
    if(stack->top < MAX_STACK_SIZE) {
        stack->top++;
        stack->slot[stack->top] = node;
        stack->count_of_push++;
        return 0;
     }
    return -1;
}

void
free_stack(Stack_t *stack)
{
    if(!stack) return;
    free(stack);
}

/* Internal Stack Implementation FINISHED*/
/* ====================x================x=================== */

static inline bool 
Math_is_operator (int token_code) {

    /* Supported Operators In MatheMatical Expression */

    switch (token_code) {

        case MATH_PLUS:
        case MATH_MINUS:
        case MATH_MUL:
        case MATH_DIV:
        case MATH_MAX:
        case MATH_MIN:
        case MATH_POW:
        case MATH_SIN:
        case MATH_SQR:
        case MATH_SQRT:
        case MATH_BRACKET_START:
        case MATH_BRACKET_END:
        case MATH_OR:
        case MATH_AND:
        case MATH_LESS_THAN:
        case MATH_GREATER_THAN:
        case MATH_EQ:
        case MATH_NOT_EQ:
        return true;
    }

    return false;
}

static inline bool 
Math_is_unary_operator (int token_code) {

    /* Supported Operators In MatheMatical Expression */

    switch (token_code) {

        case MATH_SIN:
        case MATH_SQR:
        case MATH_SQRT:
        return true;
    }

    return false;
}

static inline bool 
Math_is_binary_operator (int token_code) {

    /* Supported Operators In MatheMatical Expression */

    switch (token_code) {

        case MATH_MAX:
        case MATH_MIN:
        case MATH_PLUS:
        case MATH_MINUS:
        case MATH_MUL:
        case MATH_DIV:
        case MATH_POW:
        case MATH_AND:
        case MATH_OR:
        case MATH_GREATER_THAN:
        case MATH_LESS_THAN:
        case MATH_EQ:
        case MATH_NOT_EQ:
        return true;
    }

    return false;
}

static inline bool 
Math_is_ineq_operator (int token_code) {

    switch (token_code) {

        case MATH_LESS_THAN:
        case MATH_GREATER_THAN:
        case MATH_EQ:
        case MATH_NOT_EQ:
        return true;
    }

    return false;    
}

static inline bool 
Math_is_logical_operator (int token_code) {

    switch (token_code) {

        case MATH_OR:
        case MATH_AND:
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

        case MATH_MAX:
        case MATH_MIN:
        case MATH_POW:
            return 7;
        case MATH_MUL:
        case MATH_DIV:
            return 6;            
        case MATH_PLUS:
        case MATH_MINUS:
            return 5;
        case MATH_SIN:
        case MATH_SQR:
        case MATH_SQRT:
            return 4;
        case MATH_LESS_THAN:
        case MATH_GREATER_THAN:
        case MATH_NOT_EQ:
        case MATH_EQ:
            return 3;
        case MATH_AND:
            return 2;
        case MATH_OR:
            return 1;
        case MATH_BRACKET_START:
        case MATH_BRACKET_END:
            return 0;
    }
    assert(0);
    return 0;
} 

static bool 
mexpr_is_white_space (int token_code) {

    return (token_code == 0 || token_code == PARSER_EOL || token_code == PARSER_WHITE_SPACE);
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

            if (lex_data->token_code == MATH_BRACKET_START)
            {
                    push(stack, (void *)lex_data);
            }
            else if (lex_data->token_code == MATH_BRACKET_END)
            {
                    while (!isStackEmpty(stack) && 
                        (((lex_data_t *)stack->slot[stack->top])->token_code != MATH_BRACKET_START)) {
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

            else if (lex_data->token_code == MATH_COMMA) {

                while (!isStackEmpty(stack) && 
                    (((lex_data_t *)stack->slot[stack->top])->token_code != MATH_BRACKET_START)) {
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

static mexpt_node_t*
mexpr_create_mexpt_node (
                int token_id,
                int len,
                void *operand) {

    char *endptr;
    mexpt_node_t *mexpt_node;

    mexpt_node = (mexpt_node_t *)calloc (1, sizeof (mexpt_node_t));

    /* If this node is a Math Operator node*/
    if (Math_is_operator (token_id)) {
        mexpt_node->token_code = token_id;
        return mexpt_node;
    }

    /* If this node is a Math Operand Node*/
    switch (token_id) {

        case MATH_IDENTIFIER:
        case MATH_IDENTIFIER_IDENTIFIER:
            strncpy(mexpt_node->u.opd_node.variable_name, operand, len);
            mexpt_node->u.opd_node.is_resolved = false;
            mexpt_node->u.opd_node.math_val = 0;
            mexpt_node->token_code = token_id;
            return mexpt_node;
        case MATH_INTEGER_VALUE:
            mexpt_node->u.opd_node.math_val = (double)atoi(operand);
            mexpt_node->u.opd_node.is_resolved = true;
            mexpt_node->token_code = token_id;
            return mexpt_node;
        case MATH_DOUBLE_VALUE:
            mexpt_node->u.opd_node.math_val = strtod(operand, &endptr);
            mexpt_node->u.opd_node.is_resolved = true;
            mexpt_node->token_code = token_id;
            return mexpt_node;
        default:
            break;
    }

    return mexpt_node;
}

mexpt_node_t *
mexpr_convert_postfix_to_expression_tree (
                                    lex_data_t **lex_data, int size) {

    int i;
    mexpt_node_t *mexpt_node;
    Stack_t *stack = get_new_stack();

    for (i = 0; i < size; i++) {

        if (!Math_is_operator(lex_data[i]->token_code)) {
        
            mexpt_node = mexpr_create_mexpt_node (
                                    lex_data[i]->token_code, lex_data[i]->token_len, lex_data[i]->token_val);
            push(stack, (void *)mexpt_node);
        } 

        else if (Math_is_binary_operator (lex_data[i]->token_code)){

            mexpt_node_t *right = pop(stack);
            mexpt_node_t *left = pop(stack);
            mexpt_node_t * opNode = mexpr_create_mexpt_node (
                                                        lex_data[i]->token_code, 0, NULL);
            opNode->left = left;
            opNode->right = right;
            push(stack, opNode);
        }

        else if (Math_is_unary_operator (lex_data[i]->token_code)){

            mexpt_node_t *left = pop(stack);
            mexpt_node_t * opNode = mexpr_create_mexpt_node (
                                                        lex_data[i]->token_code, 0, NULL);
            opNode->left = left;
            opNode->right = NULL;
            push(stack, opNode);
        }

    }

    mexpt_node_t *root = pop(stack);
    assert (isStackEmpty (stack));
    free_stack(stack);
    return root;
}

void 
mexpr_print_mexpt_node (mexpt_node_t *root) {

    if (Math_is_operator (root->token_code)) {
        printf ("Mop (%d)  ", root->token_code);
    }
    else {
        printf ("Operand (%d)  ", root->token_code);
    }
}

/* Inorder traversal of expression tree print infix notation of 
    where clause */
void 
mexpr_debug_print_expression_tree (mexpt_node_t *root) {

    if (!root) return;
    mexpr_debug_print_expression_tree (root->left);
    mexpr_print_mexpt_node (root);
    mexpr_debug_print_expression_tree (root->right);
}

void 
mexpt_destroy(mexpt_node_t *root) {

    if (root != NULL) {

        mexpt_destroy(root->left);
        mexpt_destroy(root->right);
        free(root);
    }
}

bool 
mexpr_double_is_integer (double d) {

    double int_part = floor (d);
    return int_part == d;
}

res_t
mexpt_evaluate (mexpt_node_t *root) {

    res_t res;
    res.rc = false;
    res.ovalue = 0;

    if (!root) return res;

    res_t lrc = mexpt_evaluate (root->left);
    res_t rrc = mexpt_evaluate (root->right);

    /* If I am leaf */
    if (!root->left && !root->right) {

        assert (!Math_is_operator (root->token_code));

        if (!root->u.opd_node.is_resolved) return res;

        res.ovalue = root->u.opd_node.math_val;
        res.rc = true;
        return res;
    }

    /* If I am half node*/
    if (root->left && !root->right)
    {
        assert (Math_is_unary_operator (root->token_code));

        if (!lrc.rc) return res;

        switch (root->token_code)
        {
            case MATH_SIN:
            {
                res.ovalue = sin(lrc.ovalue);
            }
            break;

            case MATH_SQRT:
            {
                res.ovalue = sqrt(lrc.ovalue);
            }
            break;

            case MATH_SQR:
            {
                res.ovalue = lrc.ovalue * lrc.ovalue;
            }
            break;
        }
        res.rc = true;
        return res;
    }

    /* If I am Full node */
    if (!lrc.rc || !rrc.rc) return res;

    assert (Math_is_binary_operator (root->token_code));

    switch (root->token_code) {

        case MATH_MAX:
        {
            res.ovalue = lrc.ovalue < rrc.ovalue ? rrc.ovalue : lrc.ovalue;
        }
        break;
        case MATH_MIN:
        {
            res.ovalue = lrc.ovalue < rrc.ovalue ? lrc.ovalue : rrc.ovalue;
        }
        break;

        case MATH_PLUS:
        {
             res.ovalue = lrc.ovalue + rrc.ovalue;         
        }
        break;

        case MATH_MINUS:
        {
            res.ovalue = lrc.ovalue - rrc.ovalue;                    
        }
        break;

        case MATH_MUL:
        {
            res.ovalue = rrc.ovalue * lrc.ovalue;                            
        }
        break;

        case MATH_DIV:
        {
            if (rrc.ovalue == 0) {
                res.rc = false;
                return res;
            }
            res.ovalue = lrc.ovalue / rrc.ovalue;           
        }
        break;

        case MATH_POW:
        {
            res.ovalue = pow(lrc.ovalue , rrc.ovalue);           
        }
        break;

    }

    res.rc = true;
    return res;
}

