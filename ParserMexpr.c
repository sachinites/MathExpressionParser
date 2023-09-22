#include <stdlib.h>
#include <memory.h>
#include "ParserMexpr.h"
#include "UserParserL.h"

/* This file uses the facilities provided by Parser, Mexpr and ExpressionParser
combined. This file is not a part of MExpr Library*/

/* Imports from ExpressionParser*/
parse_rc_t S (); 
parse_rc_t Q (); 
parse_rc_t E (); 

mexpt_tree_t *
Parser_Mexpr_build_math_expression_tree ( ) {
    
    mexpt_tree_t *tree = NULL; 

    int stack_chkp = undo_stack.top + 1;

    parse_rc_t err = PARSER_CALL(E);

    if (err == PARSE_ERR) {
        return NULL;
    }

    int size_out = 0;
    lex_data_t **postfix = mexpr_convert_infix_to_postfix (
                                            &undo_stack.data[stack_chkp], undo_stack.top + 1 - stack_chkp, &size_out);
    
    int i;
    lex_data_t *lex_data;        

   tree = mexpr_convert_postfix_to_expression_tree (postfix, size_out);

    free(postfix);
    return tree; 
}

mexpt_tree_t *
Parser_Mexpr_Condition_build_expression_tree (void ) {

    mexpt_tree_t * mexpt_tree = NULL; 

    int stack_chkp = undo_stack.top + 1;

    parse_rc_t err = PARSER_CALL(S);

    do {

        if (err == PARSE_SUCCESS) break;
        err = PARSER_CALL(Q);
        if (err == PARSE_ERR) return NULL;

    } while (0);

    int size_out = 0;
    lex_data_t **postfix = mexpr_convert_infix_to_postfix (
                                            &undo_stack.data[stack_chkp], undo_stack.top + 1 - stack_chkp, &size_out);
    
    int i;
    lex_data_t *lex_data;        

    mexpt_tree_t *tree =
            mexpr_convert_postfix_to_expression_tree (postfix, size_out);

    free(postfix);
    return mexpt_tree; 
}
