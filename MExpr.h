#ifndef __MEXPR__
#define __MEXPR__

#include <stdint.h>
#include <stdbool.h>

#include "MexprEnums.h"

#define MEXPR_TREE_OPERAND_LEN_MAX  128
#define MAX_EXPR_LEN    512

typedef struct mexpt_tree_ mexpt_tree_t;

typedef struct res_{

    bool rc;
    double ovalue;
    unsigned char o_str_value[128];
    
} res_t; 

typedef struct mexpt_node_ {

    /* Based on token_code, this node represents one of these nodes :
            1. Operand Node  (identified by token_code). The relevant fields are packed under opd_node
            2. Math Operator node  (identified by token_code). No more relevant fields needed
            3. Ineq Node  (identified by token_code = SQL_WHERE). The relevant fields are packed under ineq_node
            4. Logical Operator Node (identified by token_code = SQL_OR or SQL_AND)
    */
    int token_code;

    union {

        /* Below fields are relevant only when this node is operand nodes*/
        struct {

            bool is_numeric;     /* Is this Operand Number or AlphaNumberic ?*/
            bool is_resolved;    /* Have we obtained the math value of this operand*/
            double math_val;   /* Actual Math Value */
            unsigned char variable_name[MEXPR_TREE_OPERAND_LEN_MAX];
            void *app_data;
            
        } opd_node;


        /* Below fields are relevant only when this node is INEQ operator node*/
        struct {

            struct mexpt_tree_ *left_exp_tree;
            int ineq_op_code;
            struct mexpt_tree_ *right_exp_tree;

        } ineq_node;


        struct {

            /* Nothing to define as of now */
        } math_op_node;

        struct {

            /* Nothig to define as of now*/
        } log_op_node;

    } u;

    struct mexpt_node_ *left;
    struct mexpt_node_ *right;

} mexpt_node_t;


struct mexpt_tree_ {

     mexpt_node_t *root;
};

typedef struct lex_data_ lex_data_t;

lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out);

mexpt_node_t *
mexpr_convert_postfix_to_expression_tree (
                                    lex_data_t **lex_data, int size) ;

void 
mexpr_print_mexpt_node (mexpt_node_t *root);

void 
mexpr_debug_print_expression_tree (mexpt_node_t *root) ;

void 
mexpt_destroy(mexpt_node_t *root);

res_t
mexpt_evaluate (mexpt_node_t *root);

bool 
mexpr_double_is_integer (double d);

#endif 
