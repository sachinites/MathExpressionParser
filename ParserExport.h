#ifndef __PARSER_EXPORT__
#define __PARSER_EXPORT__

#include <stdint.h>
#include <assert.h>
#include "lex.yy.h" // dynamically generated

#define MAX_MEXPR_LEN  512

//extern "C" int yylex(yyscan_t scanner);

typedef enum parse_rc_ {

    PARSE_ERR,
    PARSE_SUCCESS

} parse_rc_t;

typedef struct lex_data_ {

    int token_code;
    int token_len;
    uint8_t *token_val;
} lex_data_t;

#define MAX_STRING_SIZE 512

typedef struct pinst_ {

    char lex_buffer[MAX_STRING_SIZE];
    char *curr_ptr ;
    char *lex_curr_token;
    int lex_curr_token_len;
    
    struct {
        int top;
        lex_data_t data[MAX_MEXPR_LEN];
    } undo_stack;

    FILE *yyin;
    yyscan_t scanner;

} pinst_t;

static inline void 
pinst_init (pinst_t *inst) {

    memset (inst, 0, sizeof (pinst_t));
    inst->undo_stack.top = -1;
    assert ( yylex_init(&inst->scanner) == 0);

    /* Create a File pointer to char * array */
    inst->yyin = fmemopen(inst->lex_buffer, MAX_STRING_SIZE, "r");
    yyset_in(inst->yyin, inst->scanner);
    inst->curr_ptr = inst->lex_buffer;
}

static inline void 
pinst_destroy (pinst_t *inst) {

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
    fclose(inst->yyin);
    yylex_destroy(inst->scanner);
}

extern void lex_push(pinst_t *inst, lex_data_t lex_data);
extern lex_data_t lex_pop(pinst_t *inst) ;
extern void yyrewind (pinst_t *inst, int n) ;
extern unsigned char *parser_alloc_token_value_default (pinst_t *inst, uint16_t token_id);
extern int cyylex (pinst_t *inst);
extern void process_white_space(pinst_t *inst, int n) ;
extern void RESTORE_CHKP(pinst_t *inst, int a);

#define parse_init(inst)             \
    int token_code = 0;          \
    int _lchkp = (inst)->undo_stack.top;    \
    parse_rc_t err = PARSE_SUCCESS

#define RETURN_PARSE_ERROR(inst)      \
    {RESTORE_CHKP(inst, _lchkp);     \
    return PARSE_ERR;}

#define RETURN_PARSE_SUCCESS    \
    return PARSE_SUCCESS

#define PARSER_CALL(inst, fn) \
    fn(inst)

#define CHECKPOINT(inst, a)    \
    a = inst->undo_stack.top

#define CHECK_FOR_EOL(inst)                \
    {token_code = cyylex(inst);                   \
    if (token_code == EOL) {                \
        RETURN_PARSE_SUCCESS;   \
    }}

extern int cyylexlh(pinst_t *inst) ;
extern  int cyylexlb(pinst_t *inst) ;

#define PARSER_LOG_ERR(token_obtained, expected_token)  \
    printf ("%s(%d) : Token Obtained = %d, expected token = %d\n",    \
        __FUNCTION__, __LINE__, token_obtained, expected_token);

extern void Parser_stack_reset (pinst_t *inst) ;
extern int  Parser_get_current_stack_index (pinst_t *inst);

#define ITERATE_LEX_STACK_BEGIN(inst, i , j , token_code_, len_, value_)    \
{   int _k;                                                                                                              \
     for (_k = i; _k <= j && _k <= inst->undo_stack.top; _k++) {                               \
     lex_data_t *lex_data = &inst->undo_stack.data[_k];  \
     if (lex_data->token_code == 0 || lex_data->token_code == WHITE_SPACE) continue; \
     token_code_ = lex_data->token_code;               \
     len_ = lex_data->token_len;                               \
     value_ = lex_data->token_val;

#define ITERATE_LEX_STACK_END }}

/* Common Codes */
#define PARSER_EOL  10000
#define PARSER_QUIT 10001
#define PARSER_WHITE_SPACE  10002
#define PARSER_INVALID_CODE INT32_MAX

#endif 
