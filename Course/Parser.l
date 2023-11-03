%{

#include "ParserExport.h"


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
    lex_push(lex_data);
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

void 
Parser_stack_reset () {

    int i;
    lex_data_t *lex_data;

    for (i = 0; i < undo_stack.top; i++) {
        lex_data = &undo_stack.data[i];
        lex_data->token_code = 0;
        lex_data->token_len = 0;
        if (lex_data->token_val) {
            free (lex_data->token_val);
            lex_data->token_val = NULL;
        }
    }
    undo_stack.top = -1;
    curr_ptr = lex_buffer;
    lex_curr_token = NULL;
    lex_curr_token_len = 0;
}

void 
lex_set_scan_buffer (const char *buffer) {

    yy_scan_string (buffer);
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

extern void Parse_Equations(); 
extern parse_rc_t Z() ;
extern parse_rc_t A() ;
extern parse_rc_t C() ;
extern parse_rc_t  Q() ;
extern parse_rc_t E();
extern lex_data_t **
mexpr_convert_infix_to_postfix (lex_data_t *infix, int sizein, int *size_out);

#if 0
int main (int argc, char **argv) {

    while (1) {

        printf ("Input -> ");

        fgets (lex_buffer, sizeof (lex_buffer), stdin);

        if (lex_buffer [0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }

        lex_set_scan_buffer (lex_buffer);

#if 0
        //Parse_Equations();   
        parse_rc_t err = ();
        if (err == PARSE_ERR) {
            printf ("Rejected : Set of all Strings starting with a and have alternate a and b\n");
        }
        else {
            printf ("Accepted : Set of all Strings starting with a and have alternate a and b\n");
        }
#endif

#if 0
        parse_rc_t err = Qry();

        printf ("Parsed String : \n");
        
        if (err == PARSE_ERR) {
            printf ("Invalid Select Statemet\n");
        }
        else {
            printf ("Accepted : Valid Select Statement \n");
        }
#endif 
#if 0
        for (int i = 0; i <= undo_stack.top; i++) {

            lex_data_t *lex_data = (lex_data_t *)&undo_stack.data[i];
            printf ("%s ", lex_data->token_val);
        }
#endif

         parse_rc_t err = E();

        int token_code = cyylex();

        if (token_code != PARSER_EOL) {

            printf ("Rejectd : Entire String is not a Valid Mathematical Expression\n");
        }
        else {

            if (err == PARSE_ERR ) {

                printf ("Rejected\n");
            }
            else {

                printf ("Accepted\n");

                int size_out = 0;
                lex_data_t **postfix_array = mexpr_convert_infix_to_postfix (
                                                                undo_stack.data,
                                                                undo_stack.top + 1,
                                                                &size_out);

                // print the postfix_array here to verify !
                printf ("Postfix : ");

                for (int i = 0; i < size_out; i++) {

                    lex_data_t *lex_data = postfix_array[i];
                    printf ("%s ", lex_data->token_val);
                    free(lex_data->token_val);
                    free(lex_data);
                }
                free(postfix_array);
                
                printf ("\n");
            }
        }

        Parser_stack_reset();
    }

    return 0;
}
#endif