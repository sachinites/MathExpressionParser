#ifndef __MEXPR__
#define __MEXPR__

#include <stdint.h>
#include <stdbool.h>

#include "MexprEnums.h"

/*
1. Appln must create an expression tree
2. mexpr_validate_expression_tree( ), abort query if failed
3. Optimize it
4. Resolve the exp tree operands
    4.1 If fully resolved, 
        mexpr_validate_expression_tree( )
        Use mexpt_evaluate( ) to evaluate the exp tree
    4.2 if not resolved fully
        If this is Math_Exp tree, then abort the Query
        if this is conditional Exp Tree, 
            - mexpr_validate_expression_tree( )
            - mexpt_evaluate_unresolved() to evaluate exp tree
*/


typedef struct mexpt_tree_ mexpt_tree_t;
typedef struct mexpt_node_  mexpt_node_t;

struct mexpt_node_ {

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

            
            bool is_resolved;
            bool is_numeric;     /* Is this Operand constant Number or constant AlphaNumberic ?*/
            
            /* ToDo : Replace this union with mexpr_var_t */
            union {
                double math_val;
                unsigned char string_name[MEXPR_TREE_OPERAND_LEN_MAX];
                unsigned char variable_name[MEXPR_TREE_OPERAND_LEN_MAX];
            } opd_value;

            void *data_src;
            mexpr_var_t (*compute_fn_ptr) (void *);

        } opd_node;


        /* Below fields are relevant only when this node is INEQ operator node*/
        struct {

             bool is_optimized;
             bool result;
        } ineq_node;

        struct {

             bool is_optimized;
             bool result;
        } log_op_node;

    } u;

    mexpt_node_t *left;
    mexpt_node_t *right;
    mexpt_node_t *lst_left;
    mexpt_node_t *lst_right;
    mexpt_node_t *parent;

} ;

struct mexpt_tree_ {

    mexpt_node_t *root;
    mexpt_node_t opd_list_head;
};

#define mexpt_iterate_operands_begin(tree_ptr, node_ptr)  \
    { mexpt_node_t *_next_node = NULL; \
    for (node_ptr = tree_ptr->opd_list_head.lst_right; node_ptr; node_ptr = _next_node){ \
        _next_node = node_ptr->lst_right;

#define mexpt_iterate_operands_end(tree_ptr, node_ptr) }}


typedef struct lex_data_ lex_data_t;

lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out);

mexpt_tree_t *
mexpr_convert_postfix_to_expression_tree (
                                    lex_data_t **lex_data, int size) ;

mexpt_node_t*
mexpr_create_mexpt_node (
                int token_id,
                int len,
                void *operand);

void 
mexpr_print_mexpt_node (mexpt_node_t *root);

void 
mexpr_debug_print_expression_tree (mexpt_node_t *root) ;

void 
mexpt_destroy (mexpt_node_t *root, bool free_data_src);

mexpr_var_t
mexpt_evaluate (mexpt_node_t *root);

bool 
mexpr_double_is_integer (double d);

bool
mexpr_validate_expression_tree (mexpt_tree_t *);

void 
mexpt_tree_install_operand_properties (
                mexpt_node_t *node,
                void *data_src,
                mexpr_var_t (*compute_fn_ptr)(void *)) ;

bool
mexpt_optimize (mexpt_node_t *root);

mexpt_node_t *
mexpt_get_unresolved_operand_node (mexpt_tree_t *tree);

uint8_t 
mexpt_remove_unresolved_operands (mexpt_tree_t *tree, bool free_data_src) ;

mexpt_tree_t *
mexpt_clone (mexpt_tree_t *tree);

static inline bool  
mexpt_node_is_operand (mexpt_node_t *node) {

    return (node->token_code == MATH_IDENTIFIER ||
        node->token_code == MATH_IDENTIFIER_IDENTIFIER) ;
}

void 
mexpt_node_remove_list (mexpt_node_t *node) ;

bool
mexpt_concatenate_mexpt_trees (mexpt_tree_t *parent_tree, 
                                                       mexpt_node_t *leaf_node,
                                                       mexpt_tree_t *child_tree);

#endif 
