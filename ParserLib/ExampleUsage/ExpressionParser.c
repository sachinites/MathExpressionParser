
/* This file implements the SQL Parser which accespts all SQL queries satisfying the below Grammar 

A Grammar to parse mathematical expression !

1. E -> E + T | E - T | T
2. T -> T * F | T / F | F
3. F -> ( E ) | INTEGER | DECIMAL | VAR | 'SENTENCE'

Grammar for Inequalities : 

Add this production Rule as Ist rule to above Grammar 
0. Q -> E Ineq E | (Q)  

Overall Grammar is :
1. Q -> E Ineq E | (Q)  
2. E -> E + T | E - T | T
3. T -> T * F | T / F | F
4. F -> ( E ) | INTEGER | DECIMAL | VAR | 'SENTENCE'

Now remove left recursion from it :

2. E -> E + T | E - T | T

E ->  T E'
E' -> + T E' | - T E' |  $   ( $ represents epsilon)

3. T -> T * F | T / F | F

T -> F T'
T' -> * F T' |   / F T'  |  $

Combining everything, final grammar is for computing one Inequality
==================================================

1. Q  ->   E Ineq E  | ( Q )
2. E  ->   T E'
3. E'  ->  + T E' | - T E' |  $
4. T  ->   F T'
5. T' ->   * F T' |   / F T'  |  $
6. F  ->   ( E ) |  P ( E ) | INTEGER | DECIMAL | VAR | G ( E, E) | 'SENTENCE'
7. P -> sqrt | sqr | sin        // urinary fns
8. G -> max | min | pow   // binary functions 

Implementing Logical Operators also (and , or ) which combines various inequalities

1. S -> S or J | J
2. J -> J and K | K 
3. K -> (S) | D | K lop Q | Q lop K
4. D -> Q lop Q
5. lop -> and | or

Removing Left Recursion :
1. S -> S or J | J
    S -> J S'
    S' -> or J S' | $
2. J -> J and K | K
    J -> K J'
    J' -> and K J' | $
3. K -> (S) | D | K lop Q | Q lop K
    K -> (S) K' |  D K' |  Q lop K K'
    K' -> lop Q K' | $

Overall Grammar will be :
===================
1. S -> J S'
2. S' -> or J S' | $
3. J -> K J'
4. J' -> and K J' | $
5. K -> (S) K' | D K' | Q lop K K'
6. K' -> lop Q K' | $
7. D -> Q lop Q
8. lop -> and | or

The above is the Grammar we will use to finally implement Logical Expression Parsing.
The predence of 'and' and 'or' will be handled at the infix to postfix conversion.

Overall Grammar to  represent an expression containing atleast two inequalities
joined by Logical operaration(s)  is below.
For example :   salary > amount and age > 30
                         (salary > amount and age > 30 ) or ( pin_code = 560103 or age > 60)


Rules for Grammar Parsing :

1. For a Production Rule, A -> BC | DE , Rule contains two alternatives :
        A -> BC   or   A -> DE 
        Explore A -> BC, if success , return SUCCESS
        if fails, try second alternative (A ->DE), if success return SUCCESS, else return ERROR
        i.e. we apply alternatives until we succeed. Alternatives could be applied in any order.

2.    For a Production Rule, A -> BC | DE | $, Rule contains three alternatives :
        A -> BC   or   A -> DE    or     A -> $
        Explore A -> BC, if success , return SUCCESS
        if fails, try second alternative A -> DE, if success return SUCCESS, else return SUCCESS
        i.e. we apply alternatives until we succeed. Alternatives could be applied in any order.
        If all alternatives failed, then return SUCCESS ($ means, return SUCCESS even if none of the alternatives succeed)

3. For a Production Rule, A -> BCD, 
        Non Terminal Symbol C is explored only when previous one B has succeeded.
        Non Terminal Symbol D is explored only when previous one C has succeeded.
        At any point, the exploration fails, We are done with A -> BCD production rule and return Error,
        and look for exploration of alterntive rule if present , eg, A -> EF

4. While Returning an Error, POP all elements of the stack that was pushed as a result of exploration  
    of production rule which has failed. This will be done automatically by 'RETURN_PARSE_ERROR' macro.
*/

/* This file represents the application whiich make use of Parser library (Parser.l/ParserExport.h) files to
    write parsing code */
#include <stdlib.h>
#include <assert.h>

// Must include ParserExport.h
#include "ParserExport.h"

// must include application specific hdr file which contains token IDs.
// This file need tobe included in Parser.l file as well.

#include "MexprEnums.h"

parse_rc_t Ineq () ;
parse_rc_t G ();
parse_rc_t P ();
parse_rc_t F ();
parse_rc_t T_dash () ;
parse_rc_t T () ;
parse_rc_t E_dash () ;
parse_rc_t E () ;

parse_rc_t Q () ;

parse_rc_t D ();
parse_rc_t K ();
parse_rc_t K_dash ();
parse_rc_t J_dash () ;
parse_rc_t J () ;
parse_rc_t  S_dash () ;
parse_rc_t  S () ;

parse_rc_t
Ineq () {

    parse_init();

    token_code = cyylex();

    switch(token_code) {
        case MATH_LESS_THAN:
	    case MATH_LESS_THAN_EQ:
        case MATH_GREATER_THAN:
        case MATH_EQ:
        case MATH_NOT_EQ:
            break;
        default:
            RETURN_PARSE_ERROR;
    }

    RETURN_PARSE_SUCCESS;
}

/* Parse the Binary Math functions */
parse_rc_t
G () {

     parse_init();

     token_code = cyylex();

     switch (token_code) {

        case MATH_MAX:
        case MATH_MIN:
        case MATH_POW:
            RETURN_PARSE_SUCCESS;
        default:
            RETURN_PARSE_ERROR;
     }

}

/* Parse the unary Math functions */
parse_rc_t
P () {

    parse_init();

    token_code = cyylex();

    switch (token_code) {

        case MATH_SQRT:
        case MATH_SQR:
        case MATH_SIN:
	case MATH_COS:
            RETURN_PARSE_SUCCESS;
        default:
            RETURN_PARSE_ERROR;
    }
}

/* F  ->   ( E ) |  P ( E ) | INTEGER | DECIMAL | VAR | G ( E, E) */
parse_rc_t
F () {

    parse_init();

    int initial_chkp;
    CHECKPOINT(initial_chkp);

    token_code = cyylex();

    // ( E )
    do {
        
        if (token_code != MATH_BRACKET_START) break;

        err = PARSER_CALL(E);

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != MATH_BRACKET_END) break;

        RETURN_PARSE_SUCCESS;

    } while (0);

    RESTORE_CHKP(initial_chkp);

    // INTEGER | DECIMAL | VAR | 'SENTENCE'
    do {

        token_code = cyylex();

        switch (token_code) {
            
            case MATH_INTEGER_VALUE:
            case MATH_DOUBLE_VALUE:
            case MATH_IDENTIFIER:
            case MATH_IDENTIFIER_IDENTIFIER:
            case MATH_STRING_VALUE:
                RETURN_PARSE_SUCCESS;
            default:
                break;
        }
    } while (0);

    RESTORE_CHKP(initial_chkp);

    // P ( E ) 
    do {

        err = PARSER_CALL(P);

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != MATH_BRACKET_START) break;

        err = PARSER_CALL(E);

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != MATH_BRACKET_END) break;

        RETURN_PARSE_SUCCESS;

    } while (0);

    RESTORE_CHKP(initial_chkp);

    // G ( E, E)

    do {

        err = PARSER_CALL(G);

        if (err == PARSE_ERR) RETURN_PARSE_ERROR;

        token_code = cyylex();

        if (token_code != MATH_BRACKET_START) RETURN_PARSE_ERROR;

        err = PARSER_CALL(E);

        if (err == PARSE_ERR) RETURN_PARSE_ERROR;

        token_code = cyylex();

        if (token_code != MATH_COMMA) RETURN_PARSE_ERROR;

        err = PARSER_CALL(E);

        if (err == PARSE_ERR) RETURN_PARSE_ERROR;

        token_code = cyylex();

        if (token_code != MATH_BRACKET_END) RETURN_PARSE_ERROR;

        RETURN_PARSE_SUCCESS;

    } while (0);
}

/* T' ->   * F T' |   / F T'  |  $ */
parse_rc_t
T_dash () {

    parse_init();

    int initial_chkp;
    CHECKPOINT(initial_chkp);

    token_code = cyylex();

    if (token_code != MATH_MUL &&
            token_code != MATH_DIV) {
        
        RESTORE_CHKP(initial_chkp);
        RETURN_PARSE_SUCCESS;
    }

    err = PARSER_CALL(F);

    if (err == PARSE_ERR) {

        RESTORE_CHKP(initial_chkp);
        RETURN_PARSE_SUCCESS;
    }

    err = PARSER_CALL(T_dash);

    if (err == PARSE_ERR) {

        RESTORE_CHKP(initial_chkp);
        RETURN_PARSE_SUCCESS;        
    }

    RETURN_PARSE_SUCCESS;
}

// 4. T  ->   F T'
parse_rc_t
T () {

    parse_init();

    err = PARSER_CALL(F);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    err = PARSER_CALL(T_dash);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}

//  E'  ->  + T E' | - T E' |  $
parse_rc_t
E_dash () {

    parse_init();

    int initial_chkp;
    CHECKPOINT(initial_chkp);

    token_code = cyylex();

    if (token_code != MATH_PLUS &&
            token_code !=  MATH_MINUS) {
        
        RESTORE_CHKP(initial_chkp);
        RETURN_PARSE_SUCCESS;
    }

    err = PARSER_CALL(T);

    if (err == PARSE_ERR) {

        RESTORE_CHKP(initial_chkp);
        RETURN_PARSE_SUCCESS;
    }

    err = PARSER_CALL(E_dash);

    if (err == PARSE_ERR) {

        RESTORE_CHKP(initial_chkp);
        RETURN_PARSE_SUCCESS;        
    }

    RETURN_PARSE_SUCCESS;
}

/* E  ->   T E' */
parse_rc_t
E () {

    parse_init();

    err = PARSER_CALL(T);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    err = PARSER_CALL(E_dash);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}

/* Q  ->   E Ineq E  | ( Q ) */

parse_rc_t
Q () {

    parse_init();
    int chkp_initial;
    
    CHECKPOINT(chkp_initial);

     // Q -> (Q)
    do {

        token_code = cyylex();

        if (token_code != MATH_BRACKET_START) break;

        err = PARSER_CALL(Q);

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != MATH_BRACKET_END) break;

        RETURN_PARSE_SUCCESS;

    } while (0);

    RESTORE_CHKP(chkp_initial);

    // E Ineq E
    err = PARSER_CALL(E);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    err = PARSER_CALL(Ineq);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    err = PARSER_CALL(E);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}


// D -> Q lop Q
parse_rc_t
D () {

    parse_init();

    err = PARSER_CALL(Q);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    token_code = cyylex();

    if (token_code != MATH_OR &&
            token_code != MATH_AND) {

        RETURN_PARSE_ERROR;
    }

    err = PARSER_CALL(Q);

     if (err == PARSE_ERR) RETURN_PARSE_ERROR;

     RETURN_PARSE_SUCCESS;
}

// K' -> lop Q K' | $
parse_rc_t
K_dash () {

    parse_init();

    token_code = cyylex();

    if (token_code != MATH_AND &&
        token_code != MATH_OR) {

        yyrewind(1);
        RETURN_PARSE_SUCCESS;
    }

    err = PARSER_CALL(Q);

    if (err == PARSE_ERR) {
        yyrewind(1);
        RETURN_PARSE_SUCCESS;
    }

    err = PARSER_CALL(K_dash);

    if (err == PARSE_ERR) {
        yyrewind(1);
        RETURN_PARSE_SUCCESS;
    }

    RETURN_PARSE_SUCCESS;
}

/* K -> (S) K' | D K'  | Q lop K K'  */
parse_rc_t
K () {

    parse_init();

    int initial_chkp;
    CHECKPOINT(initial_chkp);

    //  (S) K'
    do {

        token_code = cyylex();

        if (token_code != MATH_BRACKET_START) break;

        err = PARSER_CALL(S);

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != MATH_BRACKET_END) break;

        err = PARSER_CALL(K_dash);

        if (err == PARSE_ERR) break;

        RETURN_PARSE_SUCCESS;

    } while (0);

    RESTORE_CHKP(initial_chkp);
    // D K' 
    do {

        err = PARSER_CALL(D);

        if (err == PARSE_ERR) break;

        err = PARSER_CALL(K_dash);

        if (err == PARSE_ERR) break;

        RETURN_PARSE_SUCCESS;

    } while (0);

    RESTORE_CHKP(initial_chkp);

    // Q lop K K' 
    err = PARSER_CALL(Q);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    token_code = cyylex();

    if (token_code != MATH_OR &&
        token_code != MATH_AND) {

        RETURN_PARSE_ERROR;
    }

    err = PARSER_CALL(K);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    err = PARSER_CALL(K_dash);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}

/*  J' -> and K J' | $ */
parse_rc_t
J_dash () {

    parse_init();

    token_code = cyylex();

    if (token_code != MATH_AND) {
        yyrewind(1);
        RETURN_PARSE_SUCCESS;
    }

    err = PARSER_CALL(K);

    if (err == PARSE_ERR) RETURN_PARSE_SUCCESS;

    err = PARSER_CALL(J_dash);

    if (err == PARSE_ERR) RETURN_PARSE_SUCCESS;

    RETURN_PARSE_SUCCESS;
}

/* J -> K J' */
parse_rc_t
J () {

    parse_init();

    err = PARSER_CALL(K);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    err = PARSER_CALL(J_dash);

     if (err == PARSE_ERR) RETURN_PARSE_ERROR;

     RETURN_PARSE_SUCCESS;
}


/* S' -> or J S' | $ */
parse_rc_t
S_dash () {   

    parse_init();

    token_code = cyylex();

    if (token_code != MATH_OR) {
        yyrewind(1);
        RETURN_PARSE_SUCCESS;
    }

    err = PARSER_CALL(J);

    if (err == PARSE_ERR) RETURN_PARSE_SUCCESS;

    err = PARSER_CALL(S_dash);

    if (err == PARSE_ERR) RETURN_PARSE_SUCCESS;

    RETURN_PARSE_SUCCESS;
}

 /*S -> J S'  */
parse_rc_t
S () {     

    parse_init();

   err = PARSER_CALL(J);

   if (err == PARSE_ERR) RETURN_PARSE_ERROR;

   err = PARSER_CALL(S_dash);

   if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}
