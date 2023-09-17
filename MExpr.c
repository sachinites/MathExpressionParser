#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "SQLParserStruct.h"
#include "common.h"
#include "stack/stack.h"
#include "MExpr.h"

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
        case SQL_MATH_SQR:
        case SQL_MATH_SQRT:
        case BRACK_START:
        return true;
    }

    return false;
}

static inline bool 
Math_is_unary_operator (int token_code) {

    /* Supported Operators In MatheMatical Expression */

    switch (token_code) {

        case SQL_MATH_SIN:
        case SQL_MATH_SQR:
        case SQL_MATH_SQRT:
        return true;
    }

    return false;
}

static inline bool 
Math_is_binary_operator (int token_code) {

    /* Supported Operators In MatheMatical Expression */

    switch (token_code) {

        case SQL_MATH_MAX:
        case SQL_MATH_MIN:
        case SQL_MATH_PLUS:
        case SQL_MATH_MINUS:
        case SQL_MATH_MUL:
        case SQL_MATH_DIV:
        case SQL_MATH_POW:
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

        case SQL_MATH_PLUS:
        case SQL_MATH_MINUS:
            return 2;
        case SQL_MATH_MUL:
        case SQL_MATH_DIV:
            return 3;
        case SQL_MATH_MAX:
        case SQL_MATH_MIN:
        case SQL_MATH_POW:
            return 4;
        case SQL_MATH_SIN:
        case SQL_MATH_SQR:
        case SQL_MATH_SQRT:
            return 1;
        case BRACK_START:
            return 0;
    }
    printf ("token id - %d\n", token_code);
    assert(0);
    return 0;
} 

static bool 
mexpr_is_white_space (int token_code) {

    return (token_code == 0 || token_code == EOL || token_code == WHITE_SPACE);
}

lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out) {

    int i;
    int out_index = 0;
    lex_data_t *lex_data;

    Stack_t *stack = get_new_stack();

    lex_data_t **lex_data_arr_out = 
        (lex_data_t**)calloc(MAX_MEXPR_LEN, sizeof(lex_data_t *));

    for (i = 0; i < sizein; i++) {

            lex_data = &infix[i];

            if (mexpr_is_white_space (lex_data->token_code)) continue;

            if (lex_data->token_code == BRACK_START)
            {
                    push(stack, (void *)lex_data);
            }
            else if (lex_data->token_code == BRACK_END)
            {
                    while (!isStackEmpty(stack) && 
                        (((lex_data_t *)stack->slot[stack->top])->token_code != BRACK_START)) {
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

            else if (lex_data->token_code == COMMA) {

                while (!isStackEmpty(stack) && 
                    (((lex_data_t *)stack->slot[stack->top])->token_code != BRACK_START)) {
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
    mexpt_node->token_code = token_id;

    if (Math_is_operator (token_id)) {
            return mexpt_node;
    }

    switch (token_id)
    {
    case SQL_IDENTIFIER:
    case SQL_IDENTIFIER_IDENTIFIER:
        strncpy(mexpt_node->variable_name, operand, len);
        mexpt_node->is_resolved = false;
        break;
    case SQL_INTEGER_VALUE:
        mexpt_node->math_val = (double)atoi(operand);
        mexpt_node->is_resolved = true;
        break;
    case SQL_DOUBLE_VALUE:
        mexpt_node->math_val = strtod(operand, &endptr);
        mexpt_node->is_resolved = true;
        break;
    default:
        assert(0);
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
double_is_integer (double d) {

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

        if (!root->is_resolved) return res;

        res.ovalue = root->math_val;
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
            case SQL_MATH_SIN:
            {
                res.ovalue = sin(lrc.ovalue);
            }
            break;

            case SQL_MATH_SQRT:
            {
                res.ovalue = sqrt(lrc.ovalue);
            }
            break;

            case SQL_MATH_SQR:
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

        case SQL_MATH_MAX:
        {
            res.ovalue = lrc.ovalue < rrc.ovalue ? rrc.ovalue : lrc.ovalue;
        }
        break;
        case SQL_MATH_MIN:
        {
            res.ovalue = lrc.ovalue < rrc.ovalue ? lrc.ovalue : rrc.ovalue;
        }
        break;

        case SQL_MATH_PLUS:
        {
             res.ovalue = lrc.ovalue + rrc.ovalue;         
        }
        break;

        case SQL_MATH_MINUS:
        {
            res.ovalue = lrc.ovalue - rrc.ovalue;                    
        }
        break;

        case SQL_MATH_MUL:
        {
            res.ovalue = rrc.ovalue * lrc.ovalue;                            
        }
        break;

        case SQL_MATH_DIV:
        {
            if (rrc.ovalue == 0) {
                res.rc = false;
                return res;
            }
            res.ovalue = lrc.ovalue / rrc.ovalue;           
        }
        break;

        case SQL_MATH_POW:
        {
            res.ovalue = pow(lrc.ovalue , rrc.ovalue);           
        }
        break;

    }

    res.rc = true;
    return res;
}

mexpt_node_t *
Expression_build_expression_tree () {
    
    parse_init();

    printf ("Math Expr: ");

    int stack_chkp = undo_stack.top + 1;

    err = PARSER_CALL(E);

    if (err == PARSE_ERR) {
        printf ("Invalid Expression\n");
        Parser_stack_reset ();
        return NULL;
    }

    int size_out = 0;
    lex_data_t **postfix = mexpr_convert_infix_to_postfix (
                                            &undo_stack.data[stack_chkp], undo_stack.top + 1 - stack_chkp, &size_out);
    
    int i;
    lex_data_t *lex_data;        

#if 0
        printf ("Postfix expression : ");
        for (i = 0; i < size_out; i++) {

            lex_data = postfix[i];
            printf ("%s ", (char *)lex_data->token_val);
        }

        printf("\n");
#endif 

    mexpt_node_t *root = 
            mexpr_convert_postfix_to_expression_tree (postfix, size_out);

#if 0
        printf ("Expression Tree : \n");
        mexpr_debug_print_expression_tree (root);
        printf ("\n");
#endif 

        free(postfix);
        return root; 
}

int
Inequality_build_expression_trees (mexpt_node_t **tree1, mexpt_node_t **tree2) {

    int token_code_ineqop;

    *tree1 = NULL;
    *tree2 = NULL;

    printf ("Ineq Expr: ");

    *tree1 = Expression_build_expression_tree();

    if ((*tree1) == NULL) {
        Parser_stack_reset();
        return 0;
    }

    token_code_ineqop = cyylex();

    switch (token_code_ineqop) {

        case SQL_LESS_THAN:
        case SQL_GREATER_THAN:
        case SQL_EQ:
        case SQL_NOT_EQ:
            break;
        default:
            printf("Error : Ineq Op Not Supported/Specified\n");
            Parser_stack_reset();
            mexpt_destroy(*tree1);
            *tree1 = NULL;
            return 0;
    }

     int chkp = undo_stack.top + 1;

     *tree2 = Expression_build_expression_tree();

     if ((*tree2) == NULL) {

         Parser_stack_reset();
         mexpt_destroy(*tree1);
         *tree1 = NULL;
         return 0;
     }

    return token_code_ineqop;
}

#if 0
/* Test Math Expressions */
int 
main (int argc, char **argv) {

    while (1) {
        
        printf ("MExpr : ");
        
        fgets (lex_buffer, sizeof (lex_buffer), stdin);

        if (lex_buffer[0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }

        lex_set_scan_buffer (lex_buffer);
        mexpt_node_t *root = Expression_build_expression_tree();
        if (!root) continue;
        
        res_t res = mexpt_evaluate (root);

        if (res.rc) {

            if (double_is_integer (res.ovalue)) {

                int temp = (int)res.ovalue;
                printf ("Result = %d\n", temp);
            }
            else {
                printf ("Result = %lf\n", res.ovalue);
            }
        }

        mexpt_destroy (root);
        Parser_stack_reset ();
    }

    return 0;
}

#else 

/* Test Inequalities */
int 
main (int argc, char **argv) {

    int op_token_code;
    mexpt_node_t *tree1, *tree2;

    while (1) {
        
        printf ("Ineq : ");

        fgets (lex_buffer, sizeof (lex_buffer), stdin);

        if (lex_buffer[0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }

        lex_set_scan_buffer (lex_buffer);

        op_token_code = Inequality_build_expression_trees (&tree1, &tree2);

        if (op_token_code == 0) {
            continue;
        }

        res_t lrc = mexpt_evaluate (tree1);
        res_t rrc = mexpt_evaluate (tree2);        

        assert (lrc.rc && rrc.rc);

         bool rc;
        char op_str[3];

        switch (op_token_code) {
            
            case SQL_LESS_THAN:
                rc = lrc.ovalue < rrc.ovalue;
                op_str[0] = '<';  op_str[1] = '\0'; 
                break;
            case SQL_GREATER_THAN:
                rc = lrc.ovalue > rrc.ovalue;
                op_str[0] = '>';  op_str[1] = '\0'; 
                break;
            case SQL_EQ:
                rc = (lrc.ovalue == rrc.ovalue);
                op_str[0] = '=';  op_str[1] = '\0'; 
                break;
            case SQL_NOT_EQ: 
                rc = (lrc.ovalue != rrc.ovalue);
                op_str[0] = '!';  op_str[1] = '=';  op_str[2] = '\0';  
                break;
            default :
                assert(0);
        }

        printf ("Result : ");

        if (double_is_integer (lrc.ovalue)) {
            printf ("(%d)  ", (int) lrc.ovalue);
        }
        else {
            printf ("(%lf)  ", lrc.ovalue);
        }

        printf ("%s  ", op_str);

        if (double_is_integer (rrc.ovalue)) {
            printf ("(%d)  ", (int) rrc.ovalue);
        }
        else {
            printf ("(%lf)  ", rrc.ovalue);
        }

        if (rc) {
            printf ("   TRUE\n");
        }
        else {
            printf ("   FALSE\n");
        }

        mexpt_destroy (tree1);
        mexpt_destroy (tree2);
        Parser_stack_reset ();
    }
    
    return 0;
}

#endif 