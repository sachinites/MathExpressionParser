#include <string.h>
#include "ParserExport.h"
#include "MexprcppEnums.h"

/*
CFG:

Q -> select COLS from TAB
COLS -> COL | COL , COLS  
COL -> <variable>
TAB -> <variable>

*/

static parse_rc_t  TAB() ;
static parse_rc_t  COL() ;
static parse_rc_t  COLS() ;
 parse_rc_t  Qry() ;

// TAB -> <variable>
parse_rc_t 
TAB() {

    parse_init();

    token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}



// COL -> <variable>
parse_rc_t 
COL() {

    parse_init();

    token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE) RETURN_PARSE_ERROR;

    RETURN_PARSE_SUCCESS;
}


// COLS -> COL | COL , COLS  
parse_rc_t 
COLS() {

    parse_init();
    int intial_chkp;
    CHECKPOINT(intial_chkp);

    // COLS -> COL , COLS 
    do {

        err = COL();

        if (err == PARSE_ERR) break;

        token_code = cyylex();

        if (token_code != MATH_CPP_COMMA)  break;

        err = COLS();



        RETURN_PARSE_SUCCESS;

    } while (0);

    RESTORE_CHKP(intial_chkp);

     // COLS -> COL
    do {

        err = COL();
        
        if (err == PARSE_ERR) break;

        RETURN_PARSE_SUCCESS;

    } while (0);


    RETURN_PARSE_ERROR;
}


//Q -> select COLS from TAB

parse_rc_t 
Qry() {

    parse_init();

    token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE) RETURN_PARSE_ERROR;

    if (strcmp (lex_curr_token, "select")) RETURN_PARSE_ERROR;

    err = COLS();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    token_code = cyylex();

    if (token_code != MATH_CPP_VARIABLE) RETURN_PARSE_ERROR;

    if (strcmp (lex_curr_token, "from")) RETURN_PARSE_ERROR;

    err = TAB();

    if (err == PARSE_ERR) RETURN_PARSE_ERROR;

    token_code = cyylex();

    if (token_code != PARSER_EOL) RETURN_PARSE_ERROR;

    yyrewind(1);
    
    RETURN_PARSE_SUCCESS;
}