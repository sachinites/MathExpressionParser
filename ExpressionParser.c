
/* This file implements the SQL Parser which accespts all SQL queries satisfying the below Grammar 

A Grammar to parse mathematical expression !

1. E -> E + T | E - T | T
2. T -> T * F | T / F | F
3. F -> ( E ) | INTEGER | DECIMAL | VAR

Grammar for Inequalities : 

Add this production Rule as Ist rule to above Grammar 
0. Q -> E Ineq E | (Q)  

Overall Grammar is :
1. Q -> E Ineq E | (Q)  
2. E -> E + T | E - T | T
3. T -> T * F | T / F | F
4. F -> ( E ) | INTEGER | DECIMAL | VAR

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
6. F  ->   ( E ) |  P ( E ) | INTEGER | DECIMAL | VAR | G ( E, E)
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

4. While Returning an Error, POP all elements of the stack that was pushed as a result of exploration of 
    production rule which has failed. This will be done automatically by 'RETURN_PARSE_ERROR' macro.
*/

#include <stdlib.h>
#include <assert.h>
#include "ParserExport.h"
#include "SQLParserStruct.h"
#include "common.h"

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
        case SQL_LESS_THAN:
        case SQL_GREATER_THAN:
        case SQL_EQ:
        case SQL_NOT_EQ:
            break;
        default:
            RETURN_PARSE_ERROR;
    }

    assert(err == PARSE_SUCCESS);
    RETURN_PARSE_SUCCESS;
}

/* Parse the Binary Math functions */
parse_rc_t
G () {

     parse_init();

     token_code = cyylex();

     switch (token_code) {

        case SQL_MATH_MAX:
        case SQL_MATH_MIN:
        case SQL_MATH_POW:
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

        case SQL_MATH_SQRT:
        case SQL_MATH_SQR:
        case SQL_MATH_SIN:
            RETURN_PARSE_SUCCESS;
        default:
            RETURN_PARSE_ERROR
    }
}

parse_rc_t
F () {

     parse_init();

    token_code = cyylex();

    switch (token_code) {

        case BRACK_START:
        {
            err = PARSER_CALL(E);
            switch (err) {
                case PARSE_ERR:
                    RETURN_PARSE_ERROR;
                case PARSE_SUCCESS:
                {
                    token_code = cyylex();
                    if (token_code != BRACK_END) {
                        RETURN_PARSE_ERROR;
                    }
                    RETURN_PARSE_SUCCESS;
                }
                break;
            }
        }
        break;
        case SQL_INTEGER_VALUE:
        case SQL_DOUBLE_VALUE:
        case SQL_IDENTIFIER:
        case SQL_IDENTIFIER_IDENTIFIER:
            RETURN_PARSE_SUCCESS;
        default:
            yyrewind(1);
            err = PARSER_CALL(P);
            switch(err) {
                case PARSE_ERR:
                    err = PARSER_CALL(G);
                    switch(err) {
                        case PARSE_ERR:
                            RETURN_PARSE_ERROR;
                        case PARSE_SUCCESS:
                            token_code = cyylex();
                            switch(token_code) {
                                case BRACK_START:
                                    err = PARSER_CALL(E);
                                    switch(err) {
                                        case PARSE_ERR:
                                            RETURN_PARSE_ERROR;
                                        case PARSE_SUCCESS:
                                            token_code = cyylex();
                                            switch(token_code) {
                                                case COMMA:
                                                    err = PARSER_CALL(E);
                                                    switch(err) {
                                                        case PARSE_ERR:
                                                            RETURN_PARSE_ERROR;
                                                        case PARSE_SUCCESS:
                                                            token_code = cyylex();
                                                            if (token_code != BRACK_END) {
                                                                RETURN_PARSE_ERROR;
                                                            }
                                                            RETURN_PARSE_SUCCESS;
                                                    }
                                                default:
                                                    RETURN_PARSE_ERROR;
                                            }
                                    }
                                default:
                                    RETURN_PARSE_ERROR;
                            }
                    }
                case PARSE_SUCCESS:
                    token_code = cyylex();
                    switch(token_code){
                        case BRACK_START:
                            err = PARSER_CALL(E);
                            switch(err) {
                                case PARSE_ERR:
                                    RETURN_PARSE_ERROR;
                                case PARSE_SUCCESS:
                                    token_code = cyylex();
                                    if (token_code != BRACK_END) {
                                        RETURN_PARSE_ERROR;
                                    }
                                    RETURN_PARSE_SUCCESS;
                            }
                    }
            }
    }
}

parse_rc_t
T_dash () {

    parse_init();

    token_code = cyylex();
    switch(token_code){

        case SQL_MATH_MUL:
        case SQL_MATH_DIV:
        {
            err = PARSER_CALL(F);
            switch (err) {
                case PARSE_ERR:
                    RETURN_PARSE_ERROR;
                case PARSE_SUCCESS:
                    err = PARSER_CALL(T_dash);
                    switch (err) {
                        case PARSE_ERR:
                            RETURN_PARSE_ERROR;
                        case PARSE_SUCCESS:
                            RETURN_PARSE_SUCCESS;
                    }
            }
        }
        break;
        default:
            yyrewind(1);
            RETURN_PARSE_SUCCESS;
    }
}


parse_rc_t
T () {

    parse_init();

    err = PARSER_CALL(F);
    switch (err) {
        case PARSE_ERR:
            RETURN_PARSE_ERROR;
        case PARSE_SUCCESS:
            err = PARSER_CALL(T_dash);
            switch(err) {
                case PARSE_ERR:
                    RETURN_PARSE_ERROR;
                case PARSE_SUCCESS:
                    RETURN_PARSE_SUCCESS;
            }
    }
}

parse_rc_t
E_dash () {

    parse_init();

    token_code = cyylex();

    switch (token_code) {
        case SQL_MATH_PLUS:
        case SQL_MATH_MINUS:
        {
            err = PARSER_CALL(T);
            switch(err){
                case PARSE_ERR:
                    RETURN_PARSE_ERROR;
                case PARSE_SUCCESS:
                    err = PARSER_CALL(E_dash);
                    switch(err) {
                        case PARSE_ERR:
                            RETURN_PARSE_ERROR;
                        case PARSE_SUCCESS:
                             RETURN_PARSE_SUCCESS;
                    }
            }
        }
        break;
        default:
            yyrewind(1);
            RETURN_PARSE_SUCCESS;
    }
}

parse_rc_t
E () {

    parse_init();

    err = PARSER_CALL(T);
    switch (err) {
        case PARSE_ERR:
            RETURN_PARSE_ERROR;
        case PARSE_SUCCESS:
            err = PARSER_CALL(E_dash);
            switch(err) {
                case PARSE_ERR:
                   RETURN_PARSE_ERROR;
                case PARSE_SUCCESS:
                    RETURN_PARSE_SUCCESS;
            }
    }
}

parse_rc_t
Q () {

    parse_init();
    int chkp_initial;
    
    CHECKPOINT(chkp_initial);

    token_code = cyylex();

    while (token_code == BRACK_START) {

        err = PARSER_CALL(Q);
        if (err == PARSE_ERR) break;
        
        token_code = cyylex();
        if (token_code != BRACK_END) break;

        RETURN_PARSE_SUCCESS;   // Q -> (Q)
    }

    RESTORE_CHKP(chkp_initial);

    err = PARSER_CALL(E);
    switch (err) {
        case PARSE_ERR:
            RETURN_PARSE_ERROR;
        case PARSE_SUCCESS:
            err = PARSER_CALL(Ineq);
            switch(err) {
                case PARSE_ERR:
                    RETURN_PARSE_ERROR;
                case PARSE_SUCCESS:
                    err = PARSER_CALL(E);
                    switch (err) {
                        case PARSE_ERR:
                            RETURN_PARSE_ERROR;
                        case PARSE_SUCCESS:
                            RETURN_PARSE_SUCCESS; // Q -> E Ineq E
                    }
            }
    }
}


// D -> Q lop Q
parse_rc_t
D () {

    parse_init();

    err = PARSER_CALL(Q);

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    token_code = cyylex();

    if (token_code != SQL_OR &&
            token_code != SQL_AND) {

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

    if (token_code != SQL_AND &&
        token_code != SQL_OR) {

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

        if (token_code != BRACK_START) break;

        err = PARSER_CALL(S);

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != BRACK_END) break;

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

    if (err = PARSE_ERR) RETURN_PARSE_ERROR;

    token_code = cyylex();

    if (token_code != SQL_OR &&
        token_code != SQL_AND) {

        RETURN_PARSE_ERROR;
    }

    err = PARSER_CALL(K);

    if (err = PARSE_ERR) RETURN_PARSE_ERROR;

    err = PARSER_CALL(K_dash);

    if (err = PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}

/*  J' -> and K J' | $ */
parse_rc_t
J_dash () {

    parse_init();

    token_code = cyylex();

    if (token_code != SQL_AND) {
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

    if (token_code != SQL_OR) {
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