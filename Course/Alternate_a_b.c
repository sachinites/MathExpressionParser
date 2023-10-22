#include <string.h>
#include "ParserExport.h"
#include "MexprcppEnums.h"

parse_rc_t A() ;
static parse_rc_t B() ;
parse_rc_t C() ;
static parse_rc_t D() ;
parse_rc_t Z() ;


// D -> aC | a | ab
parse_rc_t
D() {

    parse_init ();

    int intial_chkp;
    CHECKPOINT(intial_chkp);

    // D -> aC
    do {

        token_code = cyylex();

        if (token_code != MATH_CPP_VARIABLE) {
            break;
        }

        if (strcmp(lex_curr_token, "a")) {

            break;
        }

        err = C();

        if (err == PARSE_ERR) break;

        RETURN_PARSE_SUCCESS;

    } while (0);

    RESTORE_CHKP(intial_chkp);

    // D -> a
    do {

        token_code = cyylex();

        if (token_code != MATH_CPP_VARIABLE) {
            break;
        }

        if (strcmp(lex_curr_token, "a")) {

            break;
        }

        RETURN_PARSE_SUCCESS;        

    } while (0);

    RESTORE_CHKP(intial_chkp);

    // D -> ab
    do {

        token_code = cyylex();
        
        if (token_code != MATH_CPP_VARIABLE) {
            break;
        }

        if (strcmp(lex_curr_token, "a")) {

            break;
        }

        token_code = cyylex();
        
        if (token_code != MATH_CPP_VARIABLE) {
            break;
        }

        if (strcmp(lex_curr_token, "b")) {

            break;
        }                

        RETURN_PARSE_SUCCESS;

    } while (0);

    RETURN_PARSE_ERROR;
}



// C -> bD
parse_rc_t
C() {

    parse_init ();

    token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE) {
        RETURN_PARSE_ERROR;
    }

    if (strcmp(lex_curr_token, "b")) {

        RETURN_PARSE_ERROR;
    }

    err = D ();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}


// B -> bA | b | ba
parse_rc_t
B() {

    parse_init();

    // B -> bA
    do {

        token_code = cyylex();
        
        if (token_code != MATH_CPP_VARIABLE)  {
            yyrewind(1);
            break;
        }

        if (strcmp (lex_curr_token, "b")) {
             yyrewind(1);
             break;
        }
        
        err = A();

        if (err == PARSE_ERR) {

            yyrewind(1);
            break;
        }

        RETURN_PARSE_SUCCESS;

    } while (0);


    // B-> b
    do {

        token_code = cyylex();
        
        if (token_code != MATH_CPP_VARIABLE)  {
            yyrewind(1);
            break;
        }

        if (strcmp (lex_curr_token, "b")) {
             yyrewind(1);
             break;
        }

        RETURN_PARSE_SUCCESS;

    } while (0);

    // B-> ba

    do {

        token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE) {
        RETURN_PARSE_ERROR;
    }

    if (strcmp (lex_curr_token, "b")) {
            
        RETURN_PARSE_ERROR;
    }

        token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE) {
        RETURN_PARSE_ERROR;
    }

    if (strcmp (lex_curr_token, "a")) {
            
        RETURN_PARSE_ERROR;
    }

    RETURN_PARSE_SUCCESS;

    } while (0);

}


//A -> aB
parse_rc_t
A() {

    parse_init();

    token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE) {
        RETURN_PARSE_ERROR;
    }

    if (strcmp (lex_curr_token, "a")) {

        RETURN_PARSE_ERROR;
    }

    err = B ();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}


// Z --> A | C
parse_rc_t
Z() {

    parse_init();
    
     //Z --> A
    do {
   
        err = A();
        if (err == PARSE_SUCCESS) RETURN_PARSE_SUCCESS;
        break;

    } while (0);

    // Z --> C
    do {

        err = C();
        if (err == PARSE_SUCCESS) RETURN_PARSE_SUCCESS;
        break;
    } while (0);

    RETURN_PARSE_ERROR;
}