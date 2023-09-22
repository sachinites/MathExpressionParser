#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "UserParserL.h"
#include "ParserMexpr.h"

int 
main (int argc, char **argv) {

    parse_init();

    mexpt_tree_t *tree ;
    mexpr_tree_res_t res;

    while (1) {
        
        printf ("Type Expr: ");
        
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

        //mexpr_debug_print_expression_tree  (tree->root);

        assert (mexpr_validate_expression_tree (tree));
        
        res = mexpt_evaluate (tree->root);
        
        if (res.retc == failure_type_t) {

            printf ("Error : Exp Tree Evaluation Failed\n");
                    mexpt_destroy (tree->root);
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

        mexpt_destroy (tree->root);
        free(tree);
        Parser_stack_reset();
    }

    return 0;
}