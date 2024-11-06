#ifndef __PARSER_EXPORT__
#define __PARSER_EXPORT__

#include <assert.h>

typedef enum parse_rc {
    PARSE_ERR,
    PARSE_SUCCESS
} parse_rc_t;

typedef struct lex_data_ {
    int token_code;
    int token_len;
    char* token_val;
} lex_data_t;

#define MAX_MEXPR_LEN 512
#define MAX_STRING_SIZE 512

typedef struct stack_ {
    int top;
    lex_data_t data[MAX_MEXPR_LEN];
} stack_t;

#ifdef __cplusplus
extern "C" {
#endif

extern int yylex();
extern char lex_buffer[MAX_STRING_SIZE];
extern stack_t undo_stack;
extern int cyylex();
extern void yyrewind(int n);
extern char* curr_ptr;
extern char* lex_curr_token;
extern int lex_curr_token_len;

#ifdef __cplusplus
}
#endif

#define CHECKPOINT(a) (a = undo_stack.top)
#define RESTORE_CHKP(a) yyrewind(undo_stack.top - (a))

#define RETURN_PARSE_SUCCESS \
    do { return PARSE_SUCCESS; } while(0)

#define RETURN_PARSE_ERROR \
    do { RESTORE_CHKP(_lchkp); return PARSE_ERR; } while(0)

#define PARSER_LOG_ERR(token_obtained, expected_token)  \
    printf("%s(%d): Token Obtained = %d (%s), Expected Token = %d\n", \
        __FUNCTION__, __LINE__, token_obtained, lex_curr_token, expected_token)


// single line init macro hence no do while loop
#define parse_init() \
    int token_code = 0; \
    int _lchkp = undo_stack.top; \
    parse_rc_t err = PARSE_SUCCESS

#endif
