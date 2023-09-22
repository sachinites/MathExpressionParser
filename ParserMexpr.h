#ifndef __PARSER_MEXPR__
#define __PARSER_MEXPR__

#include <stdbool.h>

#include "MExpr.h"

mexpt_tree_t *
Parser_Mexpr_build_math_expression_tree (void  ) ;

mexpt_tree_t *
Parser_Mexpr_Condition_build_expression_tree (void );

#endif 