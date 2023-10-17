%{

// Write all the supporting C - code declarations/definitions

// Define all supporive data structures BEGIN




// Define all supporive data structures END


// dedicated to declare all global variables which parser will use BEGIN

extern "C" int yylex();

extern char lex_buffer[512];






char lex_buffer[512];


// dedicated to declare all global variables which parser will use END


#include "MexprcppEnums.h"

#define PARSER_EOL  10000

%}


%%

"(" {
    return MATH_CPP_BRACKET_START;
}

")" {
    return MATH_CPP_BRACKET_END;
}

"<=" {
    return MATH_CPP_LESS_THAN_EQ;
}

"<" {
    return MATH_CPP_LESS_THAN;
}

">" {
    return MATH_CPP_GREATER_THAN;
}

"=" {
    return MATH_CPP_EQ;
}

"!=" {
    return MATH_CPP_NEQ;
}

"and" {
    return MATH_CPP_AND;
}

"or" {
    return MATH_CPP_OR;
}

"*" {
    return MATH_CPP_MUL;
}

"+" {
    return MATH_CPP_PLUS;
}

"-" {
    return  MATH_CPP_MINUS;
}

"/" {
    return MATH_CPP_DIV;
}

"," {
    return MATH_CPP_COMMA;
}

"sqrt" {
    return MATH_CPP_SQRT;
}

"sqr" {
    return MATH_CPP_SQR;
}

"mmax" {
    return MATH_CPP_MAX;
}

"mmin" {
    return MATH_CPP_MIN;
}

"sin" {
    return MATH_CPP_SIN;
}

"cos" {
    return MATH_CPP_COS;
}

"pow" {
    return MATH_CPP_POW;
}

\n {
    return PARSER_EOL;
}

"\\\n" {

}

[ ] {
    /* Ignore */
    
}

[\t] {
    /*ignore tabs*/
    
}

0|-?[1-9][0-9]* {
    return MATH_CPP_INT;
}

-?[0-9]*\.[0-9]+ {
    return MATH_CPP_DOUBLE;
}

[a-zA-Z0-9_]+ {
    return MATH_CPP_VARIABLE;
}

[a-zA-Z0-9_]+\.[a-zA-Z0-9_]+ {
    return MATH_CPP_VARIABLE;
}

'[^']*' {
    // string enclosed within single quotes
    return MATH_CPP_STRING;
}

\"[^"]*\" {
    // string enclosed within double quotes
    return MATH_CPP_STRING;
}


. {
    printf ("ignore non-parsable character - %s\n", yytext);
}

%%


// C main function

int main (int argc, char **argv) {

    while (1) {

        printf ("Input -> ");

        fgets (lex_buffer, sizeof (lex_buffer), stdin);

        if (lex_buffer [0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }

        yy_scan_string (lex_buffer);


        int token_code;

        token_code = yylex();

        while (token_code != PARSER_EOL) {

            printf ("token_code = %d, token = %s ,  token_len = %d\n", token_code, yytext, yyleng);
            token_code = yylex();
        }

    }


    return 0;
}