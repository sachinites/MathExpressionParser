#ifndef __MEXPR__
#define __MEXPR__

#include <stdint.h>
#include <stdbool.h>

#include "MexprEnums.h"

#define MEXPR_TREE_OPERAND_LEN_MAX  128
#define MAX_EXPR_LEN    512

typedef struct mexpt_tree_ mexpt_tree_t;

/* The fn returns 3 codes as below 
-1 - Numeric Data 
 0 - boolean data type
 1 - Alpha numeric data type
-2 - Failure
 This fn assumes that all operands of the tree has been resolved
*/

typedef enum ret_codes_ {

    numeric_type_t      =   -1,
    boolean_type_t      =    0,
    alphanum_type_t   =    1,
    failure_type_t        =    2

} ret_codes_t;

typedef struct res_{

    ret_codes_t retc;

    union {
        bool rc;
        double ovalue;
        unsigned char *o_str_value;
    }u;
   
} mexpr_tree_res_t; 

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
            bool is_resolved;

            union {
                double math_val;
                unsigned char string_name[MEXPR_TREE_OPERAND_LEN_MAX];
                unsigned char variable_name[MEXPR_TREE_OPERAND_LEN_MAX];
            } opd_value;

            void *app_data;
            mexpr_tree_res_t (*compute_fn_ptr) (void *);
            
        } opd_node;


        /* Below fields are relevant only when this node is INEQ operator node*/
        struct {

             /* Nothing to define as of now */
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
    struct mexpt_node_ *list_next;

} mexpt_node_t;


struct mexpt_tree_ {

     mexpt_node_t *root;
     mexpt_node_t *opd_list_head;
};

typedef struct lex_data_ lex_data_t;

lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out);

mexpt_tree_t *
mexpr_convert_postfix_to_expression_tree (
                                    lex_data_t **lex_data, int size) ;

void 
mexpr_print_mexpt_node (mexpt_node_t *root);

void 
mexpr_debug_print_expression_tree (mexpt_node_t *root) ;

void 
mexpt_destroy (mexpt_node_t *root);

mexpr_tree_res_t
mexpt_evaluate (mexpt_node_t *root);

bool 
mexpr_double_is_integer (double d);

bool
mexpr_validate_expression_tree (mexpt_tree_t *);

void 
mexpt_tree_operand_node_assign_properties (
                mexpt_node_t *node,
                bool is_numeric,
                void *app_data,
                mexpr_tree_res_t (*compute_fn_ptr)(void *)) ;

#endif 
