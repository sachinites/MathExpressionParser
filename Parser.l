%{

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#include <arpa/inet.h>

int yylex();

typedef enum parse_rc_ {

    PARSE_ERR,
    PARSE_SUCCESS

} parse_rc_t;


#define MAX_STRING_SIZE 512

static unsigned char lex_buffer[MAX_STRING_SIZE] = {0};
static unsigned char *curr_ptr = lex_buffer;

#include "ParserExport.h"

typedef struct stack {

    int top;
    lex_data_t data[MAX_MEXPR_LEN];
} stack_t;

static stack_t undo_stack = {-1, {0, 0, 0}};

static void 
push(lex_data_t lex_data) {
    assert (undo_stack.top < MAX_MEXPR_LEN -1);
    undo_stack.data[++undo_stack.top] = lex_data;
}

static lex_data_t
pop() {
    assert (undo_stack.top > -1);
    lex_data_t res = undo_stack.data[undo_stack.top] ;
    undo_stack.top--;
    return res;
}

static void 
yyrewind (int n) {

    if (n <= 0) return;
    if (curr_ptr == lex_buffer) return;
    int data_len = 0;
    lex_data_t lex_data;
    while (n)  {
        lex_data = pop();
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

static unsigned char *
parser_alloc_token_value_default (uint16_t token_id) {

    unsigned char *ptr = (unsigned char *)(calloc (1, yyleng + 1));
    strncpy (ptr, yytext, yyleng);
    ptr [yyleng] = '\0';
    return (void *)ptr;
}

static int 
cyylex () {

    int token_code =  yylex();
    curr_ptr += yyleng;
    lex_data_t lex_data;
    lex_data.token_code = token_code;
    lex_data.token_len = yyleng;
    lex_data.token_val = parser_alloc_token_value_default  (token_code);
    push(lex_data);
    return token_code;
}

static void 
process_white_space(int n) {

    lex_data_t lex_data;
    curr_ptr += n;
    lex_data.token_code = 0;
    lex_data.token_len = n;
    lex_data.token_val = NULL;
    push(lex_data);
}

#define parse_init()             \
    int token_code = 0;          \
    int _lchkp = undo_stack.top;    \
    parse_rc_t err = PARSE_SUCCESS

#define RETURN_PARSE_ERROR      \
    {yyrewind(undo_stack.top - _lchkp);     \
    return PARSE_ERR;}

#define RETURN_PARSE_SUCCESS    \
    return PARSE_SUCCESS

#define PARSER_CALL(fn) \
    fn(NULL)

#define CHECKPOINT(a)    \
    a = undo_stack.top

#define RESTORE_CHKP(a) \
    yyrewind(undo_stack.top - a)
    
#define CHECK_FOR_EOL                \
    {token_code = cyylex();                   \
    if (token_code == EOL) {                \
        RETURN_PARSE_SUCCESS;   \
    }}

static inline int
cyylexlh() {

    int token_code = cyylex();
    yyrewind(1);
    return token_code;
}

static inline int
cyylexlb() {

    yyrewind(1);
    int token_code = cyylex();
    yyrewind(1);
    return token_code;
}

#define PARSER_LOG_ERR(token_obtained, expected_token)  \
    printf ("%s(%d) : Token Obtained = %d (%s) , expected token = %d\n",    \
        __FUNCTION__, __LINE__, token_obtained, yytext, expected_token);

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

#define ITERATE_LEX_STACK_BEGIN(i , j , token_code_, len_, value_)    \
{   int _k;                                                                                                              \
     for (_k = i; _k <= j && _k <= undo_stack.top; _k++) {                               \
     lex_data_t *lex_data = &undo_stack.data[_k];  \
     if (lex_data->token_code == 0 || lex_data->token_code == WHITE_SPACE) continue; \
     token_code_ = lex_data->token_code;               \
     len_ = lex_data->token_len;                               \
     value_ = lex_data->token_val;

#define ITERATE_LEX_STACK_END }}


/* ========================================
            Warning : Do  Not Modify this file above this line 
    ======================================= */
            /* User specific parsing logic starts below */



/* User specific header files */
#include "SQLParserStruct.h"
#include "common.h"
#include "MExpr.h"

%}

%%

"select" {
    return SQL_SELECT_Q;
}

"create table" {
    return SQL_CREATE_Q;
}

"insert into" {
    return SQL_INSERT_Q;
}

"delete" {
    return SQL_DELETE_Q;
}

"varchar" {
    return SQL_STRING;
}

"int" {
    return SQL_INT;
}

"double" {
    return SQL_DOUBLE;
}

"ipv4" {
    return SQL_IPV4_ADDR;
}

"primary key" {
    return SQL_PRIMARY_KEY;
}

"not null" {
    return SQL_NOT_NULL;
}

"max" {
    return SQL_MAX;
}

"sum" {
    return SQL_SUM;
}

"min" {
    return SQL_MIN;
}

"count" {
    return SQL_COUNT;
}

"avg" {
    return SQL_AVG;
}

"from" {
    return SQL_FROM;
}

"where" {
    return SQL_WHERE;
}

"group by" {
    return SQL_GROUP_BY;
}

"order by" {
    return SQL_ORDER_BY;
}

"limit" {
    return SQL_LIMIT;
}


"having" {
    return SQL_HAVING;
}

"asc" {
    return SQL_ORDERBY_ASC;
}

"desc" {
    return SQL_ORDERBY_DSC;
}


"(" {
    return BRACK_START;
}

")" {
    return BRACK_END;
}

"'" {
    return QUOTATION_MARK;
}

"<" {
    return SQL_LESS_THAN;
}

">" {
    return SQL_GREATER_THAN;
}

"=" {
    return SQL_EQ;
}

"!=" {
    return SQL_NOT_EQ;
}

"and" {
    return SQL_AND;
}

"or" {
    return SQL_OR;
}

"as" {
    return SQL_AS;
}

"*" {
    return SQL_MATH_MUL;
}

"+" {
    return SQL_MATH_PLUS;
}

"-" {
    return SQL_MATH_MINUS;
}

"/" {
    return SQL_MATH_DIV;
}

";" {
    return SEMI_COLON;
}

"sqrt" {
    return SQL_MATH_SQRT;
}

"sqr" {
    return SQL_MATH_SQR;
}

"mmax" {
    return SQL_MATH_MAX;
}

"mmin" {
    return SQL_MATH_MIN;
}

"sin" {
    return SQL_MATH_SIN;
}

"pow" {
    return SQL_MATH_POW;
}

\n {
    return EOL;
}

"\\\n" {

}

"\\dt\n" {
    return SHOW_DB_TABLES;
}

"," {
    return COMMA;
}

[ ] {
    /* Ignore */
    process_white_space(1);
}

[\t] {
    /*ignore*/
    process_white_space(4);
}

"\\q" {
    return QUIT;
}

(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9]) {

    return SQL_IPV4_ADDR_VALUE;
}

-?[1-9][0-9]* {
    return SQL_INTEGER_VALUE;
}

-?[0-9]*\.[0-9]+ {
    return SQL_DOUBLE_VALUE;
}

[a-zA-Z0-9_]+ {
    return SQL_IDENTIFIER;
}

[a-zA-Z0-9_]+\.[a-zA-Z0-9_]+ {
    return SQL_IDENTIFIER_IDENTIFIER;
}


%{

#if 0
^[a-zA-Z0-9][a-zA-Z0-9_.,-_'"!()\[\]{} ]* {
    
    return SQL_STRING_VALUE;
}
#endif

%}



. {
    printf ("Non parsable character : %c\n", *yytext);
    exit(0);
}

%%

/* #include other parser .c src files here */
#include "ExpressionParser.c"

void
Expression_Evaluation () {
    
    parse_init();

    while (1) {

        printf ("Math Expr: ");
        fgets (lex_buffer, sizeof (lex_buffer), stdin);

        if (lex_buffer[0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }
        yy_scan_string (lex_buffer);
        err = PARSER_CALL(E);

        if (err == PARSE_ERR) {
            printf ("Invalid Expression\n");
            Parser_stack_reset ();
            continue;
        }

        int size_out = 0;
        lex_data_t **postfix = mexpr_convert_infix_to_postfix (
                                            &undo_stack.data[0], undo_stack.top + 1, &size_out);
        int i;
        lex_data_t *lex_data;        

#if 0
        printf ("Postfix expression : ");
        for (i = 0; i < size_out; i++) {

            lex_data = postfix[i];
            printf ("%s ", (char *)lex_data->token_val);
        }

        printf("\n");
#endif 

        mexpt_node_t *root = 
            mexpr_convert_postfix_to_expression_tree (postfix, size_out);

#if 0
        printf ("Expression Tree : \n");
        mexpr_debug_print_expression_tree (root);
        printf ("\n");
#endif 

         res_t res = mexpt_evaluate (root);

        if (res.rc) {

            if (double_is_integer (res.ovalue)) {

                int temp = (int)res.ovalue;
                printf ("Result = %d\n", temp);
            }
            else {
                printf ("Result = %lf\n", res.ovalue);
            }
        }

        free(postfix);
        mexpt_destroy (root);
        Parser_stack_reset ();
    }
   
}

void
Inequality_Evaluation () {
    
    parse_init();

    while (1) {

        printf ("Ineq Expr: ");
        fgets (lex_buffer, sizeof (lex_buffer), stdin);

        if (lex_buffer[0] == '\n') {
            lex_buffer[0] = 0;
            continue;
        }

        yy_scan_string (lex_buffer);
        err = PARSER_CALL(E);

        if (err == PARSE_ERR) {
            printf ("Invalid Expression\n");
            Parser_stack_reset ();
            continue;
        }

        int size_out = 0;
        lex_data_t **postfix = mexpr_convert_infix_to_postfix (
                                            &undo_stack.data[0], undo_stack.top + 1, &size_out);

        mexpt_node_t *root1 = 
            mexpr_convert_postfix_to_expression_tree (postfix, size_out); 

        free(postfix);

        int token_code_ineqop = cyylex();

        switch (token_code_ineqop) {

            case SQL_LESS_THAN:
            case SQL_GREATER_THAN:
            case SQL_EQ:
            case SQL_NOT_EQ:
            break;
            default:
                printf ("Error : Ineq Op Not Supported/Specified\n");
                Parser_stack_reset ();
                mexpt_destroy (root1);
                continue;
        }

        int chkp = undo_stack.top + 1;

        err = PARSER_CALL(E);

        if (err == PARSE_ERR) {
            printf ("Invalid Expression\n");
            Parser_stack_reset ();
            mexpt_destroy (root1);
            continue;
        }

        size_out = 0;
        postfix = mexpr_convert_infix_to_postfix (
                                            &undo_stack.data[chkp], undo_stack.top + 1, &size_out);

        mexpt_node_t *root2 = 
            mexpr_convert_postfix_to_expression_tree (postfix, size_out); 

        free (postfix);

        res_t lrc = mexpt_evaluate (root1);
        res_t rrc = mexpt_evaluate (root2);

        assert (lrc.rc && rrc.rc);

        bool rc;
        char op_str[3];

        switch (token_code_ineqop) {
            
            case SQL_LESS_THAN:
                rc = lrc.ovalue < rrc.ovalue;
                op_str[0] = '<';  op_str[1] = '\0'; 
                break;
            case SQL_GREATER_THAN:
                rc = lrc.ovalue > rrc.ovalue;
                op_str[0] = '>';  op_str[1] = '\0'; 
                break;
            case SQL_EQ:
                rc = (lrc.ovalue == rrc.ovalue);
                op_str[0] = '=';  op_str[1] = '\0'; 
                break;
            case SQL_NOT_EQ: 
                rc = (lrc.ovalue != rrc.ovalue);
                op_str[0] = '!';  op_str[1] = '=';  op_str[2] = '\0';  
                break;
            default :
                assert(0);
        }

        printf ("Result : ");

        if (double_is_integer (lrc.ovalue)) {
            printf ("(%d)  ", (int) lrc.ovalue);
        }
        else {
            printf ("(%lf)  ", lrc.ovalue);
        }

        printf ("%s  ", op_str);

        if (double_is_integer (rrc.ovalue)) {
            printf ("(%d)  ", (int) rrc.ovalue);
        }
        else {
            printf ("(%lf)  ", rrc.ovalue);
        }

        if (rc) {
            printf ("   TRUE\n");
        }
        else {
            printf ("   FALSE\n");
        }

        Parser_stack_reset ();
        mexpt_destroy (root1);
        mexpt_destroy (root2);
    }
}

int 
main (int argc, char **argv) {

    while (1) {
        //Expression_Evaluation();
        Inequality_Evaluation();
    }
    return 0;
}
