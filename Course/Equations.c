#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "ParserExport.h"
#include "MexprcppEnums.h"

// pow(x,2) + pow(y,2) = <CONSTANT> 
parse_rc_t
circle_eqn () {

    parse_init() ;

    token_code = cyylex();

    if (token_code != MATH_CPP_POW) {

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();

    if (token_code != MATH_CPP_BRACKET_START) {

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex ();

    if (token_code != MATH_CPP_VARIABLE) {

        RETURN_PARSE_ERROR;
    }

    if (strcmp (lex_curr_token, "x") != 0) {

        RETURN_PARSE_ERROR;
    }

    // pow(x,2) + pow(y,2) = <CONSTANT>   

    token_code = cyylex ();

    if (token_code != MATH_CPP_COMMA) {

       RETURN_PARSE_ERROR;
    }

    token_code = cyylex ();

    if (token_code != MATH_CPP_INT) {

       RETURN_PARSE_ERROR;
    }

    if (strcmp (lex_curr_token, "2") != 0) {

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();

    if (token_code != MATH_CPP_BRACKET_END) {

        RETURN_PARSE_ERROR;
    }

    // pow(x,2) + pow(y,2) = <CONSTANT>   

    token_code = cyylex();

    if (token_code != MATH_CPP_PLUS) {

       RETURN_PARSE_ERROR;
    }

    token_code = cyylex();

    if (token_code != MATH_CPP_POW) {

        //Parser_stack_reset();
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();

    if (token_code != MATH_CPP_BRACKET_START) {

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex ();

    if (token_code != MATH_CPP_VARIABLE) {

        RETURN_PARSE_ERROR;
    }

    if (strcmp (lex_curr_token, "y") != 0) {

       RETURN_PARSE_ERROR;
    }

    // pow(x,2) + pow(y,2) = <CONSTANT>   

    token_code = cyylex ();

    if (token_code != MATH_CPP_COMMA) {

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex ();

    if (token_code != MATH_CPP_INT) {

        RETURN_PARSE_ERROR;
    }

    if (strcmp (lex_curr_token, "2") != 0) {

        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();

    if (token_code != MATH_CPP_BRACKET_END) {

        RETURN_PARSE_ERROR;
    }

   // pow(x,2) + pow(y,2) = <CONSTANT>

   token_code = cyylex();

   if (token_code != MATH_CPP_EQ) {

        RETURN_PARSE_ERROR;
   }

   token_code = cyylex();

   if (token_code != MATH_CPP_INT &&
        token_code != MATH_CPP_DOUBLE) {

            RETURN_PARSE_ERROR;
    }

    RETURN_PARSE_SUCCESS;
}

// pow(x,2)/pow(a,2) + pow(y,2)/pow(b,2) = 1 
static bool 
ellipse_eqn () {

    return true;
}


void 
Parse_Equations () {

    bool rc = circle_eqn();

    if (rc) {
        printf ("Eqn of Circle\n");
    }

    rc = ellipse_eqn();

    if (rc) {
        printf ("Eqn of Ellipse\n");
    }

    else {

        printf ("Invalid Equation\n");
    }
}