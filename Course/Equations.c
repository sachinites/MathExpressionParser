#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "ParserExport.h"
#include "MexprcppEnums.h"

// pow(x,2) + pow(y,2) = <CONSTANT>
parse_rc_t circle_eqn() {
    parse_init();

    token_code = cyylex();
    if (token_code != MATH_CPP_POW) {
        PARSER_LOG_ERR(token_code, MATH_CPP_POW);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_BRACKET_START) {
        PARSER_LOG_ERR(token_code, MATH_CPP_BRACKET_START);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_VARIABLE) {
        PARSER_LOG_ERR(token_code, MATH_CPP_VARIABLE);
        RETURN_PARSE_ERROR;
    }

    if (strcmp(lex_curr_token, "x") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_VARIABLE);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_COMMA) {
        PARSER_LOG_ERR(token_code, MATH_CPP_COMMA);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_INT) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }
    if (strcmp(lex_curr_token, "2") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_BRACKET_END) {
        PARSER_LOG_ERR(token_code, MATH_CPP_BRACKET_END);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_PLUS) {
        PARSER_LOG_ERR(token_code, MATH_CPP_PLUS);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_POW) {
        PARSER_LOG_ERR(token_code, MATH_CPP_POW);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_BRACKET_START) {
        PARSER_LOG_ERR(token_code, MATH_CPP_BRACKET_START);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_VARIABLE) {
        PARSER_LOG_ERR(token_code, MATH_CPP_VARIABLE);
        RETURN_PARSE_ERROR;
    }

    if (strcmp(lex_curr_token, "y") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_VARIABLE);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_COMMA) {
        PARSER_LOG_ERR(token_code, MATH_CPP_COMMA);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_INT) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }
    if (strcmp(lex_curr_token, "2") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_BRACKET_END) {
        PARSER_LOG_ERR(token_code, MATH_CPP_BRACKET_END);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_EQ) {
        PARSER_LOG_ERR(token_code, MATH_CPP_EQ);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_INT && token_code != MATH_CPP_DOUBLE) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }

    RETURN_PARSE_SUCCESS;
}

// pow(x,2)/pow(a,2) + pow(y,2)/pow(b,2) = 1
parse_rc_t ellipse_eqn() {
    parse_init();

    token_code = cyylex();
    if (token_code != MATH_CPP_POW) {
        PARSER_LOG_ERR(token_code, MATH_CPP_POW);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_BRACKET_START) {
        PARSER_LOG_ERR(token_code, MATH_CPP_BRACKET_START);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_VARIABLE) {
        PARSER_LOG_ERR(token_code, MATH_CPP_VARIABLE);
        RETURN_PARSE_ERROR;
    }

    if (strcmp(lex_curr_token, "x") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_VARIABLE);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_COMMA) {
        PARSER_LOG_ERR(token_code, MATH_CPP_COMMA);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_INT) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }

    if (strcmp(lex_curr_token, "2") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_BRACKET_END) {
        PARSER_LOG_ERR(token_code, MATH_CPP_BRACKET_END);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_DIV) {
        PARSER_LOG_ERR(token_code, MATH_CPP_DIV);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_POW) {
        PARSER_LOG_ERR(token_code, MATH_CPP_POW);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_BRACKET_START) {
        PARSER_LOG_ERR(token_code, MATH_CPP_BRACKET_START);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_VARIABLE) {
        PARSER_LOG_ERR(token_code, MATH_CPP_VARIABLE);
        RETURN_PARSE_ERROR;
    }

    if (strcmp(lex_curr_token, "a") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_VARIABLE);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_COMMA) {
        PARSER_LOG_ERR(token_code, MATH_CPP_COMMA);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_INT) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }

    if (strcmp(lex_curr_token, "2") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_BRACKET_END) {
        PARSER_LOG_ERR(token_code, MATH_CPP_BRACKET_END);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_PLUS) {
        PARSER_LOG_ERR(token_code, MATH_CPP_PLUS);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_POW) {
        PARSER_LOG_ERR(token_code, MATH_CPP_POW);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_BRACKET_START) {
        PARSER_LOG_ERR(token_code, MATH_CPP_BRACKET_START);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_VARIABLE) {
        PARSER_LOG_ERR(token_code, MATH_CPP_VARIABLE);
        RETURN_PARSE_ERROR;
    }

    if (strcmp(lex_curr_token, "y") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_VARIABLE);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_COMMA) {
        PARSER_LOG_ERR(token_code, MATH_CPP_COMMA);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_INT) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }

    if (strcmp(lex_curr_token, "2") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_BRACKET_END) {
        PARSER_LOG_ERR(token_code, MATH_CPP_BRACKET_END);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_EQ) {
        PARSER_LOG_ERR(token_code, MATH_CPP_EQ);
        RETURN_PARSE_ERROR;
    }

    token_code = cyylex();
    if (token_code != MATH_CPP_INT || strcmp(lex_curr_token, "1") != 0) {
        PARSER_LOG_ERR(token_code, MATH_CPP_INT);
        RETURN_PARSE_ERROR;
    }

    RETURN_PARSE_SUCCESS;  // Parsing successful if all checks passed
}



void Parse_Equations()
{
    bool re = circle_eqn();

    if(re)
    {
        printf("Eqn of Circle\n");
    }

    re = ellipse_eqn();

    if(re)
    {
        printf("Eqn of Ellipse\n");
    }
}