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
	    case MATH_COS:
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
	    case MATH_COS:
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
	    case MATH_COS:
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
            strncpy(mexpt_node->u.opd_node.opd_value.variable_name, operand, len);
            mexpt_node->u.opd_node.is_resolved = false;
            mexpt_node->token_code = token_id;
            return mexpt_node;
        case MATH_INTEGER_VALUE:
            mexpt_node->u.opd_node.opd_value.math_val= (double)atoi(operand);
            mexpt_node->u.opd_node.is_resolved = true;
            mexpt_node->token_code = token_id;
            return mexpt_node;
        case MATH_DOUBLE_VALUE:
            mexpt_node->u.opd_node.opd_value.math_val = strtod(operand, &endptr);
            mexpt_node->u.opd_node.is_resolved = true;
            mexpt_node->token_code = token_id;
            return mexpt_node;
        default:
            break;
    }

    return mexpt_node;
}

mexpt_tree_t *
mexpr_convert_postfix_to_expression_tree (
                                    lex_data_t **lex_data, int size) {

    int i;
    mexpt_tree_t *tree;
    mexpt_node_t *mexpt_node;
    Stack_t *stack = get_new_stack();

    tree = (mexpt_tree_t *)calloc (1, sizeof (mexpt_tree_t));

    for (i = 0; i < size; i++) {

        if (!Math_is_operator(lex_data[i]->token_code)) {
        
            mexpt_node = mexpr_create_mexpt_node (
                                    lex_data[i]->token_code, lex_data[i]->token_len, lex_data[i]->token_val);
            push(stack, (void *)mexpt_node);

            if (mexpt_node->token_code == MATH_IDENTIFIER ||
                mexpt_node->token_code == MATH_IDENTIFIER_IDENTIFIER) {

                if (!tree->opd_list_head) {
                    tree->opd_list_head = mexpt_node;
                }
                else {
                    mexpt_node->list_next = tree->opd_list_head;
                    tree->opd_list_head = mexpt_node;
                }
            }

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

    tree->root = pop(stack);
    assert (isStackEmpty (stack));
    free_stack(stack);
    return tree;
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
mexpt_destroy(mexpt_node_t *root, bool free_app_data) {

    if (root != NULL) {

        mexpt_destroy(root->left, free_app_data);
        mexpt_destroy(root->right, free_app_data);

        if ((root->token_code == MATH_IDENTIFIER ||
            root->token_code == MATH_IDENTIFIER_IDENTIFIER) &&
            free_app_data) {

            free(root->u.opd_node.app_data);
        }
        free(root);
    }
}

bool 
mexpr_double_is_integer (double d) {

    double int_part = floor (d);
    return int_part == d;
}

mexpr_tree_res_t
mexpt_evaluate (mexpt_node_t *root) {

    mexpr_tree_res_t res;
    res.retc = failure_type_t;

    if (!root) return res;

    mexpr_tree_res_t lrc = mexpt_evaluate (root->left);
    mexpr_tree_res_t rrc = mexpt_evaluate (root->right);

    /* If I am leaf */
    if (!root->left && !root->right) {

        switch (root->token_code) {

            case MATH_IDENTIFIER:
            case MATH_IDENTIFIER_IDENTIFIER:
                return root->u.opd_node.compute_fn_ptr(root->u.opd_node.app_data);
            case MATH_INTEGER_VALUE:
            case MATH_DOUBLE_VALUE:
                res.retc = numeric_type_t;
                res.u.ovalue = root->u.opd_node.opd_value.math_val;
                return res;
        }
    }

    /* If I am half node*/
    if (root->left && !root->right)
    {
        assert (Math_is_unary_operator (root->token_code));

        if (!lrc.retc) return res;

        switch (root->token_code)
        {
            case MATH_SIN:
            {
                res.retc = numeric_type_t;
                res.u.ovalue = sin(lrc.u.ovalue);
            }
            break;

	    case MATH_COS:
	    {
		res.retc = numeric_type_t;
		 res.u.ovalue = cos (lrc.u.ovalue);
	    }
	    break;

            case MATH_SQRT:
            {
                res.retc = numeric_type_t;
                res.u.ovalue = sqrt(lrc.u.ovalue);                
            }
            break;

            case MATH_SQR:
            {
                res.retc = numeric_type_t;
                res.u.ovalue = lrc.u.ovalue * lrc.u.ovalue;
            }
            break;
        }
        return res;
    }

    /* If I am Full node */
    if (lrc.retc == failure_type_t || rrc.retc == failure_type_t) return res;

    assert (Math_is_binary_operator (root->token_code));

    switch (root->token_code) {

        case MATH_MAX:
        {
            res.retc = numeric_type_t;
            res.u.ovalue = lrc.u.ovalue < rrc.u.ovalue ? rrc.u.ovalue : lrc.u.ovalue;
        }
        break;
        case MATH_MIN:
        {
            res.retc = numeric_type_t;
            res.u.ovalue = lrc.u.ovalue < rrc.u.ovalue ? lrc.u.ovalue : rrc.u.ovalue;
        }
        break;

        case MATH_PLUS:
        {
             res.retc = numeric_type_t;
             res.u.ovalue = lrc.u.ovalue + rrc.u.ovalue;         
        }
        break;

        case MATH_MINUS:
        {
            res.retc = numeric_type_t;
            res.u.ovalue = lrc.u.ovalue - rrc.u.ovalue;                    
        }
        break;

        case MATH_MUL:
        {
            res.retc = numeric_type_t;
            res.u.ovalue = rrc.u.ovalue * lrc.u.ovalue;                            
        }
        break;

        case MATH_DIV:
        {
            if (rrc.u.ovalue == 0) {
                res.retc = failure_type_t;
                return res;
            }
            res.retc = numeric_type_t;
            res.u.ovalue = lrc.u.ovalue / rrc.u.ovalue;           
        }
        break;

        case MATH_POW:
        {
            res.retc = numeric_type_t;
            res.u.ovalue = pow(lrc.u.ovalue , rrc.u.ovalue);           
        }
        break;

        case MATH_LESS_THAN:
            res.retc = boolean_type_t;
            res.u.rc = lrc.u.ovalue < rrc.u.ovalue;
            return res;

        case MATH_GREATER_THAN:
            res.retc = boolean_type_t;
            res.u.rc = lrc.u.ovalue > rrc.u.ovalue;
            return res;

        case MATH_EQ:
            if (lrc.retc == alphanum_type_t) {
                res.retc = boolean_type_t;
                res.u.rc = strcmp (lrc.u.o_str_value, rrc.u.o_str_value) == 0;
                return res;
            }
            if (lrc.retc == numeric_type_t) {
                res.retc = boolean_type_t;
                res.u.rc = lrc.u.ovalue == rrc.u.ovalue;
                return res;
            }
        break;

        case MATH_NOT_EQ:
            if (lrc.retc == alphanum_type_t) {
                res.retc = boolean_type_t;
                res.u.rc = strcmp (lrc.u.o_str_value, rrc.u.o_str_value) != 0;
                return res;
            }
            if (lrc.retc == numeric_type_t) {
                res.retc = boolean_type_t;
                res.u.rc = lrc.u.ovalue != rrc.u.ovalue;
                return res;
            }        
        break;

        case MATH_AND:
        {
            if (lrc.retc == rrc.retc &&
                    lrc.retc == boolean_type_t) {
                
                res.retc = boolean_type_t;
                res.u.rc = lrc.u.rc && rrc.u.rc;
                return res;
            }
        }
        break;
        case MATH_OR:
        {
            if (lrc.retc == rrc.retc &&
                    lrc.retc == boolean_type_t) {
                
                res.retc = boolean_type_t;
                res.u.rc = lrc.u.rc || rrc.u.rc;
                return res;
            }
        }        
        break;
    }
    return res;
}

static ret_codes_t
mexpr_validate_expression_tree_internal (mexpt_node_t *node) {

    if (!node) return failure_type_t ;
    
    ret_codes_t lrc = mexpr_validate_expression_tree_internal (node->left);
    ret_codes_t rrc = mexpr_validate_expression_tree_internal (node->right);

    /* Operand Nodes*/
    switch (node->token_code) {

        case MATH_IDENTIFIER:
        case MATH_IDENTIFIER_IDENTIFIER:
            if (!node->u.opd_node.is_resolved) return failure_type_t;
            if (node->u.opd_node.is_numeric) return numeric_type_t;
            return alphanum_type_t;
        case MATH_INTEGER_VALUE:
        case MATH_DOUBLE_VALUE:
            if (!node->u.opd_node.is_resolved) return failure_type_t;
            return numeric_type_t;
        case MATH_STRING_VALUE:
            if (!node->u.opd_node.is_resolved) return failure_type_t;
           return alphanum_type_t;
    }

    switch (node->token_code ) {

        case MATH_MAX:
        case MATH_MIN:
        case MATH_POW:
        case MATH_MUL:
        case MATH_DIV:
        case MATH_PLUS:
        case MATH_MINUS:
            if (lrc !=  numeric_type_t ||
                    rrc !=  numeric_type_t) return failure_type_t;
            return numeric_type_t;
        case MATH_SIN:
        case MATH_COS:
        case MATH_SQR:
        case MATH_SQRT:
            if (lrc == numeric_type_t) return lrc;
            return failure_type_t;
        case MATH_LESS_THAN:
        case MATH_GREATER_THAN:
            if (lrc == numeric_type_t &&
                rrc == numeric_type_t) return boolean_type_t;
            return failure_type_t;
        case MATH_NOT_EQ:
        case MATH_EQ:
            if (lrc == rrc && lrc != failure_type_t) return boolean_type_t;
            return failure_type_t;
        case MATH_AND:
        case MATH_OR:
            if (lrc == rrc && lrc == boolean_type_t) return boolean_type_t;
            return failure_type_t;
    }

    return failure_type_t;
}

bool
mexpr_validate_expression_tree (mexpt_tree_t *tree) {

    return (mexpr_validate_expression_tree_internal (tree->root) != failure_type_t);
}

void 
mexpt_tree_operand_node_assign_properties (
                mexpt_node_t *node,
                bool is_numeric,
                void *app_data,
                mexpr_tree_res_t (*compute_fn_ptr)(void *)) {

    assert (node->token_code == MATH_IDENTIFIER ||
            node->token_code == MATH_IDENTIFIER_IDENTIFIER);

    node->u.opd_node.is_numeric = is_numeric;
    node->u.opd_node.is_resolved = true;
    node->u.opd_node.app_data =  app_data;
    node->u.opd_node.compute_fn_ptr = compute_fn_ptr;
}
