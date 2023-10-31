#include "ParserExport.h"
#include "MexprcppEnums.h"

/*

A Grammar to parse mathematical expression !

1. E -> E + T | E - T | T
2. T -> T * F | T / F | F
3. F -> ( E ) | INTEGER | DECIMAL | VAR 

Now remove left recursion from it :

1. E -> E + T | E - T | T
E ->  T E'
E' -> + T E' | - T E' |  $   ( $ represents epsilon)

2. T -> T * F | T / F | F
T -> F T'
T' -> * F T' |   / F T'  |  $

Combining everything, final grammar is : 

1.    E   ->   T E’
2.    E’  ->  + T E' | - T E' |  $
3.    T  ->   F T’
4.    T’ ->   * F T' |   / F T'  |  $
5.    F  ->   ( E ) |  INTEGER | DECIMAL | VAR | G(E,E) | P(E)
6.    Q -> E INEQ E
7.    INEQ ->     MATH_CPP_EQ  |  MATH_CPP_NEQ |  MATH_CPP_LESS_THAN  |   MATH_CPP_LESS_THAN_EQ
8.   G -> max | min | pow
9.   P  -> sqr | sqrt
*/

parse_rc_t E() ;
static parse_rc_t E_dash() ;
static parse_rc_t T() ;
static parse_rc_t T_dash() ;
static parse_rc_t F() ;
parse_rc_t Q() ;
parse_rc_t INEQ() ;
static parse_rc_t G() ;
static parse_rc_t P() ;



// G -> max | min | pow
parse_rc_t 
G() {

    parse_init();

    token_code = cyylex();

    switch (token_code) {

        case MATH_CPP_POW:
        case MATH_CPP_MAX:
        case MATH_CPP_MIN:
            RETURN_PARSE_SUCCESS;
        default:
            RETURN_PARSE_ERROR;
    }
}

// P  -> sqr | sqrt
parse_rc_t 
P() {

    parse_init();

    token_code = cyylex();

    switch (token_code) {

        case MATH_CPP_SQR:
        case MATH_CPP_SQRT:
            RETURN_PARSE_SUCCESS;
        default:
            RETURN_PARSE_ERROR;
    }    
}


// F  ->   ( E ) |  INTEGER | DECIMAL | VAR | STRING | G(E,E) | P(E)
parse_rc_t 
F() {

    parse_init();
    int initial_chkp;
    CHECKPOINT(initial_chkp);


    // F --> (E)

    do {

        token_code = cyylex();

        if (token_code != MATH_CPP_BRACKET_START) break;

        err = E();

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != MATH_CPP_BRACKET_END) break;

        RETURN_PARSE_SUCCESS;

    } while (0);

    RESTORE_CHKP(initial_chkp);

    // F -> G(E,E) 
    do {

        err = G();

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != MATH_CPP_BRACKET_START) break;

        err = E();

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != MATH_CPP_COMMA) break;

        token_code = cyylex();

        if (token_code != MATH_CPP_BRACKET_END) break;

        RETURN_PARSE_SUCCESS;

    } while (0);
    
    RESTORE_CHKP(initial_chkp);

    // G -> P (E)
    do {

        err = P();

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != MATH_CPP_BRACKET_START) break;

        err = E();

         token_code = cyylex();

         if (token_code != MATH_CPP_BRACKET_END) break;

         RETURN_PARSE_SUCCESS;

    } while (0);


    RESTORE_CHKP(initial_chkp);

    // F --> INTEGER | DECIMAL | VAR | STRING

    token_code = cyylex();

    switch (token_code) {

        case MATH_CPP_INT:
        case MATH_CPP_DOUBLE:
        case MATH_CPP_VARIABLE:
        case MATH_CPP_STRING:
            RETURN_PARSE_SUCCESS;
        default:
            RETURN_PARSE_ERROR;
    }

    RETURN_PARSE_ERROR;
}


// T’ ->   * F T' |   / F T'  |  $
parse_rc_t 
T_dash() {

    parse_init();
    int intial_chkp;
    CHECKPOINT(intial_chkp);

    // T’ ->   * F T' 

    do {

        token_code = cyylex();

        if (token_code != MATH_CPP_MUL) break;

        err = F();

         if (err == PARSE_ERR) break;

         err = T_dash();

          if (err == PARSE_ERR) break;

          RETURN_PARSE_SUCCESS;

    } while (0);

    RESTORE_CHKP(intial_chkp);

    // T' = / F T'
    do {

        token_code = cyylex();

        if (token_code != MATH_CPP_DIV) break;

        err = F();

         if (err == PARSE_ERR) break;

         err = T_dash();

          if (err == PARSE_ERR) break;

          RETURN_PARSE_SUCCESS;


    } while (0);

    RESTORE_CHKP(intial_chkp);

    // T' --> $
    RETURN_PARSE_SUCCESS;
}


// 3.    T  ->   F T’
parse_rc_t 
T() {

    parse_init();

    err = F();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    err = T_dash();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}



// 2.    E’  ->  + T E' | - T E' |  $
parse_rc_t
E_dash() {

    parse_init();
    int intial_chkp;
    CHECKPOINT (intial_chkp);

    // E’  ->  + T E'
    do {

        token_code = cyylex();
        if (token_code != MATH_CPP_PLUS) break;
        err = T();
        if (err == PARSE_ERR) break;
        err = E_dash();
        if (err == PARSE_ERR) break;
        RETURN_PARSE_SUCCESS;
    } while (0);

    RESTORE_CHKP(intial_chkp);

    // E’  -> - T E'
    do {

        token_code = cyylex();
        if (token_code != MATH_CPP_MINUS) break;
        err = T();
        if (err == PARSE_ERR) break;
        err = E_dash();
        if (err == PARSE_ERR) break;
        RETURN_PARSE_SUCCESS;        
    } while (0);

    // E’  -> $
    RESTORE_CHKP(intial_chkp);
    RETURN_PARSE_SUCCESS;
}



// 1.    E   ->   T E’
parse_rc_t 
E() {

    parse_init();

    err = T();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    err = E_dash();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}

// 6. Q -> E INEQ E
parse_rc_t
Q() {

    parse_init();

    err = E();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    err = INEQ();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    err = E();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}

// 7.    INEQ ->     MATH_CPP_EQ  |  MATH_CPP_NEQ |  
//                           MATH_CPP_LESS_THAN  |   MATH_CPP_LESS_THAN_EQ

parse_rc_t
INEQ() {

    parse_init();

    token_code = cyylex();

    switch(token_code) {

        case MATH_CPP_EQ:
        case MATH_CPP_NEQ:
        case MATH_CPP_LESS_THAN:
        case MATH_CPP_LESS_THAN_EQ:
            RETURN_PARSE_SUCCESS;
        default:
            RETURN_PARSE_ERROR;
    }
}
