#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "UserParserL.h"
#include "ParserMexpr.h"




#include "MexprEnums.h"

static mexpr_var_t
compute_opd_value_fn (void *data_src) {

    mexpr_var_t res;

    if ((char)data_src == 'a') {
        res.dtype = MEXPR_DTYPE_INT;
        res.u.int_val = 1;
    }

    else if ((char)data_src == 'b') {
        res.dtype = MEXPR_DTYPE_DOUBLE;
        res.u.d_val = (double)4;
    }

    else if ((char)data_src == 'c') {
        res.dtype = MEXPR_DTYPE_DOUBLE;
        res.u.d_val = 4;
    }

    else if ((char)data_src == 'd') {
        res.dtype = MEXPR_DTYPE_STRING;
        res.u.str_val = "Sagar";
    }

    return res;
}

#if 0
int 
main (int argc, char **argv) {

    parse_init();

    mexpt_tree_t *tree ;
    mexpr_tree_res_t res;

    while (1) {
        
        printf ("Calc : ");
        
        fgets (lex_buffer, sizeof (lex_buffer), stdin);

        if (lex_buffer[0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }

        lex_set_scan_buffer (lex_buffer);

        tree = Parser_Mexpr_Condition_build_expression_tree ();

        if (!tree) {
            tree = Parser_Mexpr_build_math_expression_tree ();
        }

        if (!tree) {
            printf ("Error : Exp Tree could not built\n");
            continue;
        }

    #if 0
        mexpr_debug_print_expression_tree (tree->root);
        tree = mexpt_clone (tree);
        printf ("\nPrinting Clone :\n");
        mexpr_debug_print_expression_tree (tree->root);
        printf ("\n");
    #endif

        if (!mexpr_validate_expression_tree (tree)) {
            
            printf ("Error : Exp Tree Validation Failed\n");

            mexpt_destroy (tree->root, false);
            assert (!tree->opd_list_head.lst_right);
            free(tree);
            Parser_stack_reset();
            continue;
        }
        printf ("Exp Tree Successfully Validated prior to resolution\n");


        printf ("Print Exp Tree Before Optimization\n");
        mexpr_debug_print_expression_tree (tree->root);
        printf("\n");
        mexpt_optimize (tree->root);
        printf ("Print Exp Tree After Optimization\n");
        mexpr_debug_print_expression_tree (tree->root);
        printf ("\n");

#if 1
        {
            mexpt_node_t *node;
            mexpt_iterate_operands_begin(tree, node) {

                if (strcmp (node->u.opd_node.opd_value.variable_name, "a") == 0) {
                                   mexpt_tree_install_operand_properties (node, true, 
                                             NULL, compute_opd_value_fn); 
                }
                else if (strcmp (node->u.opd_node.opd_value.variable_name, "b") == 0) {
                                mexpt_tree_install_operand_properties (node, true, 
                                    NULL, compute_opd_value_fn); 
                }
                else if (strcmp (node->u.opd_node.opd_value.variable_name, "c") == 0) {

                                mexpt_tree_install_operand_properties (node, true, 
                                    NULL, compute_opd_value_fn); 
                }
                else if (strcmp (node->u.opd_node.opd_value.variable_name, "d") == 0) {
                                mexpt_tree_install_operand_properties (node, true, 
                                    NULL, compute_opd_value_fn); 
                }                
            }mexpt_iterate_operands_end(tree, node);
        }
#endif 

        if (!mexpr_validate_expression_tree (tree)) {
            
            printf ("Error : Exp Tree Validation Failed\n");
            mexpt_destroy (tree->root, false);
            assert (!tree->opd_list_head.lst_right);
            free(tree);
            Parser_stack_reset();
            continue;
        }
        printf ("Exp Tree Successfully Validated after resolution\n");

#if 1
        uint8_t cnt = mexpt_remove_unresolved_operands (tree, false);
        printf ("No of unresolved operands removed = %d\n", cnt);

        if (cnt) {
            mexpt_optimize (tree->root);
            printf ("Print Exp Tree After Optimization\n");
            mexpr_debug_print_expression_tree (tree->root);
        }
#endif 
        res = mexpt_evaluate (tree->root);
        
        if (res.retc == failure_type_t) {

            printf ("Error : Exp Tree Evaluation Failed\n");
                    mexpt_destroy (tree->root, false);
                    assert (!tree->opd_list_head.lst_right);
                    free(tree);
                    Parser_stack_reset();
                    continue;
        }

        if (res.retc == numeric_type_t) {
            if (mexpr_double_is_integer (res.u.ovalue)) {
                printf ("= %d\n", ( int ) res.u.ovalue);
            }
            else {
                printf ("= %lf\n",  res.u.ovalue);
            }
        }
        else if (res.retc == alphanum_type_t){
                printf ("%s\n", res.u.o_str_value);
        }
        else if (res.retc == boolean_type_t) {
            if (res.u.rc) printf (" = TRUE\n");
            else printf  (" = FALSE\n");
        }

        mexpt_destroy (tree->root, false);
        assert (!tree->opd_list_head.lst_right);
        free(tree);
        Parser_stack_reset();
    }

    return 0;
}

#endif 


int 
main (int argc, char **argv) {

    parse_init();

    mexpt_tree_t *tree ;
    mexpr_var_t res;

    while (1) {
        
        printf ("Calc : ");
        
        fgets (lex_buffer, sizeof (lex_buffer), stdin);

        if (lex_buffer[0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }

        lex_set_scan_buffer (lex_buffer);

        tree = Parser_Mexpr_Condition_build_expression_tree ();

        if (!tree) {
            tree = Parser_Mexpr_build_math_expression_tree ();
        }

        if (!tree) {
            printf ("Error : Exp Tree could not built\n");
            continue;
        }

    #if 0
        mexpr_debug_print_expression_tree (tree->root);
        tree = mexpt_clone (tree);
        printf ("\nPrinting Clone :\n");
        mexpr_debug_print_expression_tree (tree->root);
        printf ("\n");
    #endif

        if (!mexpr_validate_expression_tree (tree)) {
            
            printf ("Error : Exp Tree Validation Failed\n");

            mexpt_destroy (tree->root, false);
            assert (!tree->opd_list_head.lst_right);
            free(tree);
            Parser_stack_reset();
            continue;
        }
        printf ("Exp Tree Successfully Validated prior to resolution\n");


        printf ("Print Exp Tree Before Optimization\n");
        mexpr_debug_print_expression_tree (tree->root);
        printf("\n");
        mexpt_optimize (tree->root);
        printf ("Print Exp Tree After Optimization\n");
        mexpr_debug_print_expression_tree (tree->root);
        printf ("\n");

#if 1
        {
            mexpt_node_t *node;
            mexpt_iterate_operands_begin(tree, node) {

                if (strcmp (node->u.opd_node.opd_value.variable_name, "a") == 0) {
                                   mexpt_tree_install_operand_properties (node,
                                             (void *)'a', compute_opd_value_fn); 
                }
                else if (strcmp (node->u.opd_node.opd_value.variable_name, "b") == 0) {
                                mexpt_tree_install_operand_properties (node, 
                                    (void *)'b', compute_opd_value_fn); 
                }
                else if (strcmp (node->u.opd_node.opd_value.variable_name, "c") == 0) {

                                mexpt_tree_install_operand_properties (node, 
                                    (void *)'c', compute_opd_value_fn); 
                }
                else if (strcmp (node->u.opd_node.opd_value.variable_name, "d") == 0) {
                                mexpt_tree_install_operand_properties (node, 
                                    (void *)'d', compute_opd_value_fn); 
                }                
            }mexpt_iterate_operands_end(tree, node);
        }
#endif 

        if (!mexpr_validate_expression_tree (tree)) {
            
            printf ("Error : Exp Tree Validation Failed\n");
            mexpt_destroy (tree->root, false);
            assert (!tree->opd_list_head.lst_right);
            free(tree);
            Parser_stack_reset();
            continue;
        }
        printf ("Exp Tree Successfully Validated after resolution\n");

#if 1
        uint8_t cnt = mexpt_remove_unresolved_operands (tree, false);
        printf ("No of unresolved operands removed = %d\n", cnt);

        if (cnt) {
            mexpt_optimize (tree->root);
            printf ("Print Exp Tree After Optimization\n");
            mexpr_debug_print_expression_tree (tree->root);
        }
#endif 
        res = mexpt_evaluate (tree->root);
        
        if (res.dtype== MEXPR_DTYPE_INVALID) {

            printf ("Error : Exp Tree Evaluation Failed\n");
                    mexpt_destroy (tree->root, false);
                    assert (!tree->opd_list_head.lst_right);
                    free(tree);
                    Parser_stack_reset();
                    continue;
        }

        switch (res.dtype) {

            case MEXPR_DTYPE_INT:
                printf ("= %d\n", ( int ) res.u.int_val);
                break;
            case MEXPR_DTYPE_DOUBLE:
                printf ("= %lf\n",  res.u.d_val);
                break;
            case MEXPR_DTYPE_STRING:
                printf ("%s\n", res.u.str_val);
                break;
            case MEXPR_DTYPE_BOOL:
                if (res.u.b_val)
                    printf(" = TRUE\n");
                else
                    printf(" = FALSE\n");
                break;
            }

        mexpt_destroy (tree->root, false);
        assert (!tree->opd_list_head.lst_right);
        free(tree);
        Parser_stack_reset();
    }

    return 0;
}
