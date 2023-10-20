%{

#include <assert.h>

// Write all the supporting C - code declarations/definitions

// Define all supporive data structures BEGIN

typedef struct lex_data_ {

    int token_code;
    int token_len;
    char* token_val;

} lex_data_t;


#define MAX_MEXPR_LEN  512
#define MAX_STRING_SIZE 512
#define PARSER_EOL  10000
#define PARSER_WHITE_SPACE 10002

typedef struct stack_ {

    int top;
    lex_data_t data[MAX_MEXPR_LEN];
} stack_t;


// Define all supporive data structures END


// dedicated to declare all global variables which parser will use BEGIN

extern "C" int yylex();

extern char lex_buffer[MAX_STRING_SIZE];
extern stack_t undo_stack;
extern int cyylex();
extern void yyrewind(int n);
extern char *curr_ptr ;
extern char *lex_curr_token;
extern int lex_curr_token_len;




stack_t undo_stack = {-1, {0, 0, 0}};

char lex_buffer[MAX_STRING_SIZE];
char *curr_ptr = lex_buffer;
char *lex_curr_token;
int lex_curr_token_len;

static void 
lex_push (lex_data_t lex_data) {

    assert (undo_stack.top < MAX_MEXPR_LEN - 1);
    undo_stack.data[++undo_stack.top] = lex_data;
    lex_curr_token = (char *)lex_data.token_val;
    lex_curr_token_len = lex_data.token_len;
}

static lex_data_t
lex_pop () {

    assert (undo_stack.top > -1);
    lex_data_t res = undo_stack.data[undo_stack.top];
    undo_stack.top--;
    lex_curr_token = ( char *)res.token_val;
    lex_curr_token_len = res.token_len;
    return res;
}

static void 
process_white_space(int n) {

    lex_data_t lex_data;
    curr_ptr += n;
    lex_data.token_code = PARSER_WHITE_SPACE;
    lex_data.token_len = n;
    lex_data.token_val = NULL;
    lex_push(lex_data);
}

int 
cyylex() {

    int token_code = yylex();
    lex_data_t lex_data;
    lex_data.token_code = token_code;
    lex_data.token_len = yyleng;
    curr_ptr += yyleng;
    lex_data.token_val = (char *)calloc (1, yyleng + 1);
    strncpy (lex_data.token_val, yytext, yyleng);
    lex_data.token_val[yyleng] = '\0';
    return token_code;
}

void 
yyrewind (int n) {

    if (n <= 0) return;
    if (curr_ptr == lex_buffer) return;
    int data_len = 0;
    lex_data_t lex_data;
    while (n)  {
        lex_data = lex_pop();
        data_len += lex_data.token_len;
        n--;
        lex_data.token_code = 0;
        lex_data.token_len = 0;
        if (lex_data.token_val) {
            free (lex_data.token_val);
            lex_data.token_val = NULL;
        }
    }
    curr_ptr -= data_len;
    yy_scan_string(curr_ptr);
}


// dedicated to declare all global variables which parser will use END


#include "MexprcppEnums.h"



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
    process_white_space(1);
}

[\t] {
    /*ignore tabs*/
    process_white_space(4);
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