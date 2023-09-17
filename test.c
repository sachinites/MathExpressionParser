#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <arpa/inet.h>

/* Mandatory : #include the Parser Interface */
#include "ParserExport.h"


/* #include the files which contains Constants and IDs. These constants
    must match with those in Parser.l file */
#include "SQLParserStruct.h"
#include "common.h"


/* #include Other User heler file MExpr.h */
#include "MExpr.h"

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