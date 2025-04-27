%option reentrant
%option header-file="lex.yy.h"

%{

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <arpa/inet.h>

#include "ParserExport.h"

void 
lex_push(pinst_t *inst, lex_data_t lex_data) {

    assert (inst->undo_stack.top < MAX_MEXPR_LEN -1);
    inst->undo_stack.data[++inst->undo_stack.top] = lex_data;
    inst->lex_curr_token = (char *)lex_data.token_val;
    inst->lex_curr_token_len = lex_data.token_len;
}

lex_data_t
lex_pop(pinst_t *inst) {
    assert (inst->undo_stack.top > -1);
    lex_data_t res = inst->undo_stack.data[inst->undo_stack.top] ;
    inst->undo_stack.top--;
    if (inst->undo_stack.top > -1) {
        lex_data_t stck_top_lexd = inst->undo_stack.data[inst->undo_stack.top] ;
        inst->lex_curr_token = (char *)stck_top_lexd.token_val;
        inst->lex_curr_token_len = stck_top_lexd.token_len;
    }
    else {
        inst->lex_curr_token = NULL;
        inst->lex_curr_token_len = 0;
    }
    return res;
}

void 
yyrewind (pinst_t *inst, int n) {

    if (n <= 0) return;
    if (inst->curr_ptr == inst->lex_buffer) return;
    int data_len = 0;
    lex_data_t lex_data;
    while (n)  {
        lex_data = lex_pop(inst);
        data_len += lex_data.token_len;
        if (lex_data.token_code == PARSER_WHITE_SPACE) {
            continue;
        }
        n--;
        lex_data.token_code = 0;
        lex_data.token_len = 0;
        if (lex_data.token_val) {
            free (lex_data.token_val);
            lex_data.token_val = NULL;
        }
    }
    inst->curr_ptr -= data_len;
    fseek (inst->yyin, -1 * data_len, SEEK_CUR);
}

void
RESTORE_CHKP(pinst_t *inst, int a) {

    lex_data_t lex_data;
    int data_len = 0;

    while (inst->undo_stack.top > a) {
        
        lex_data =  lex_pop(inst);
        data_len += lex_data.token_len;

        if (lex_data.token_val) { 
            free (lex_data.token_val);
            lex_data.token_val = NULL;
        }
    }
    inst->curr_ptr -= data_len;
    fseek (inst->yyin, -1 * data_len, SEEK_CUR);
}

unsigned char *
parser_alloc_token_value_default (pinst_t *inst, uint16_t token_id) {

    unsigned char *ptr = (unsigned char *)(calloc (1, inst->lex_curr_token_len + 1));
    strncpy (ptr, inst->lex_curr_token, inst->lex_curr_token_len);
    ptr [inst->lex_curr_token_len] = '\0';
    return (void *)ptr;
}

int 
cyylex (pinst_t *inst) {

    int token_code =  yylex(inst->scanner);
    inst->lex_curr_token = yyget_text (inst->scanner);
    inst->lex_curr_token_len = yyget_leng (inst->scanner) ;
    inst->curr_ptr += inst->lex_curr_token_len ;
    lex_data_t lex_data;
    lex_data.token_code = token_code;
    lex_data.token_len = inst->lex_curr_token_len;
    lex_data.token_val = parser_alloc_token_value_default  (inst, token_code);
    lex_push(inst, lex_data);
    return token_code;
}

void 
process_white_space(pinst_t *inst, int n) {

    lex_data_t lex_data;
    inst->curr_ptr += n;
    lex_data.token_code = PARSER_WHITE_SPACE;
    lex_data.token_len = n;
    lex_data.token_val = NULL;
    fseek(inst->yyin, n, SEEK_CUR);
    lex_push(inst, lex_data);
}

int cyylexlh(pinst_t *inst) {

    int token_code = cyylex(inst);
    yyrewind(inst, 1);
    return token_code;
}

int cyylexlb(pinst_t *inst) {

    yyrewind(inst, 1);
    int token_code = cyylex(inst);
    yyrewind(inst, 1);
    return token_code;
}

void 
Parser_stack_reset (pinst_t *inst) {

    int i;
    lex_data_t *lex_data;

    for (i = 0; i < inst->undo_stack.top; i++) {
        lex_data = &inst->undo_stack.data[i];
        lex_data->token_code = 0;
        lex_data->token_len = 0;
        if (lex_data->token_val) {
            free (lex_data->token_val);
            lex_data->token_val = NULL;
        }
    }
    inst->undo_stack.top = -1;
    inst->curr_ptr = inst->lex_buffer;
    fseek (inst->yyin, 0, SEEK_SET);
}

int 
Parser_get_current_stack_index (pinst_t *inst) {
    return inst->undo_stack.top;
}

/* ========================================
            Warning : Do  Not Modify this file above this line 
    ======================================= */
            /* User specific parsing logic starts below */



/* User specific header files */
#include "MExprcppEnums.h"


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
    //process_white_space(1);
}

[\t] {
    /*ignore*/
    //process_white_space(4);
}

"\\q" {
    return PARSER_QUIT;
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
    // ignore any other character
}

%%

#if 0
int 
main (int argc) {

    int token_code = cyylex();
    printf ("token_code = %d,  token = %s \n", token_code, yytext);
    return 0;
}
#endif
