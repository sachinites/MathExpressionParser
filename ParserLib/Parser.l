%{

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <arpa/inet.h>

#include "ParserExport.h"

unsigned char lex_buffer[MAX_STRING_SIZE] = {0};
unsigned char *curr_ptr = lex_buffer;

stack_t undo_stack = {-1, {0, 0, 0}};

void 
lex_push(lex_data_t lex_data) {
    assert (undo_stack.top < MAX_MEXPR_LEN -1);
    undo_stack.data[++undo_stack.top] = lex_data;
}

lex_data_t
lex_pop() {
    assert (undo_stack.top > -1);
    lex_data_t res = undo_stack.data[undo_stack.top] ;
    undo_stack.top--;
    return res;
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

unsigned char *
parser_alloc_token_value_default (uint16_t token_id) {

    unsigned char *ptr = (unsigned char *)(calloc (1, yyleng + 1));
    strncpy (ptr, yytext, yyleng);
    ptr [yyleng] = '\0';
    return (void *)ptr;
}

int 
cyylex () {

    int token_code =  yylex();
    curr_ptr += yyleng;
    lex_data_t lex_data;
    lex_data.token_code = token_code;
    lex_data.token_len = yyleng;
    lex_data.token_val = parser_alloc_token_value_default  (token_code);
    lex_push(lex_data);
    return token_code;
}

void 
process_white_space(int n) {

    lex_data_t lex_data;
    curr_ptr += n;
    lex_data.token_code = 0;
    lex_data.token_len = n;
    lex_data.token_val = NULL;
    lex_push(lex_data);
}

int cyylexlh() {

    int token_code = cyylex();
    yyrewind(1);
    return token_code;
}

int cyylexlb() {

    yyrewind(1);
    int token_code = cyylex();
    yyrewind(1);
    return token_code;
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
}

int 
Parser_get_current_stack_index () {
    return undo_stack.top;
}

void 
lex_set_scan_buffer (const char *buffer) {

    yy_scan_string (buffer);
}

/* ========================================
            Warning : Do  Not Modify this file above this line 
    ======================================= */
            /* User specific parsing logic starts below */


