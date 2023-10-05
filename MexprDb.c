#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "MexprEnums.h"

typedef  mexpr_var_t (*operator_fn_ptr_t) (mexpr_var_t , mexpr_var_t);

//MATH_LESS_THAN_EQ
static inline mexpr_var_t  
math_less_than_eq_opr_fn_int_int_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_BOOL;

    int lopnd_val = lrc.u.int_val;
    int ropnd_val = rrc.u.int_val;

    ret.u.b_val = lopnd_val <= ropnd_val;
    return ret;
}

static inline mexpr_var_t  
math_less_than_eq_opr_fn_int_double_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_BOOL;

    int lopnd_val = lrc.u.int_val;
    double ropnd_val = rrc.u.d_val;

    ret.u.b_val = ((double)lopnd_val <= ropnd_val);
    return ret;
}

static inline mexpr_var_t  
math_less_than_eq_opr_fn_double_int_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_BOOL;

    double lopnd_val = lrc.u.d_val;
    int ropnd_val = rrc.u.int_val;

    ret.u.b_val = lopnd_val <= (double)ropnd_val;
    return ret;
}

static inline mexpr_var_t  
math_less_than_eq_opr_fn_double_double_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_BOOL;

    double lopnd_val = lrc.u.int_val;
    double ropnd_val = rrc.u.int_val;

    ret.u.b_val = lopnd_val <= ropnd_val;
    return ret;
}


// MATH_LESS_THAN
static inline mexpr_var_t  
math_less_than_opr_fn_int_int_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_BOOL;

    int lopnd_val = lrc.u.int_val;
    int ropnd_val = rrc.u.int_val;

    ret.u.b_val = lopnd_val < ropnd_val;
    return ret;
}

static inline mexpr_var_t  
math_less_than_opr_fn_int_double_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_BOOL;

    int lopnd_val = lrc.u.int_val;
    double ropnd_val = rrc.u.d_val;

    ret.u.b_val = (double)lopnd_val < ropnd_val;
    return ret;
}

static inline mexpr_var_t  
math_less_than_opr_fn_double_int_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_BOOL;

    double lopnd_val = lrc.u.d_val;
    int ropnd_val = rrc.u.int_val;

    ret.u.b_val = lopnd_val < (double)ropnd_val;
    return ret;
}

static inline mexpr_var_t  
math_less_than_opr_fn_double_double_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_BOOL;

    double lopnd_val = lrc.u.d_val;
    double ropnd_val = rrc.u.d_val;

    ret.u.b_val = lopnd_val < ropnd_val;
    return ret;
}


// MATH_GREATER_THAN
static inline mexpr_var_t  
math_greater_than_opr_fn_int_int_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_BOOL;

    int lopnd_val = lrc.u.int_val;
    int ropnd_val = rrc.u.int_val;

    ret.u.b_val = lopnd_val > ropnd_val;
    return ret;
}

static inline mexpr_var_t  
math_greater_than_opr_fn_int_double_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_BOOL;

    int lopnd_val = lrc.u.int_val;
    double ropnd_val = rrc.u.d_val;

    ret.u.b_val = (double)lopnd_val > ropnd_val;
    return ret;
}

static inline mexpr_var_t  
math_greater_than_opr_fn_double_int_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_BOOL;

    double lopnd_val = lrc.u.d_val;
    int ropnd_val = rrc.u.int_val;

    ret.u.b_val = lopnd_val > (double)ropnd_val;
    return ret;
}

static inline mexpr_var_t  
math_greater_than_opr_fn_double_double_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_BOOL;

    double lopnd_val = lrc.u.d_val;
    double ropnd_val = rrc.u.d_val;

    ret.u.b_val = lopnd_val > ropnd_val;
    return ret;
}

// MATH_EQ
static inline mexpr_var_t  
math_equal_opr_fn_int_int_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_BOOL;

    int lopnd_val = lrc.u.int_val;
    int ropnd_val = rrc.u.int_val;

    ret.u.b_val = (lopnd_val == ropnd_val);
    return ret;
}

static inline mexpr_var_t  
math_equal_opr_fn_int_double_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_BOOL;

    int lopnd_val = lrc.u.int_val;
    double ropnd_val = rrc.u.d_val;

    ret.u.b_val = ((double)lopnd_val == ropnd_val);
    return ret;
}

static inline mexpr_var_t  
math_equal_opr_fn_double_int_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_BOOL;

    double lopnd_val = lrc.u.d_val;
    int ropnd_val = rrc.u.int_val;

    ret.u.b_val = (lopnd_val == (double)ropnd_val);
    return ret;
}

static inline mexpr_var_t  
math_equal_opr_fn_double_double_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_BOOL;

    double lopnd_val = lrc.u.d_val;
    double ropnd_val = rrc.u.d_val;

    ret.u.b_val = (lopnd_val == ropnd_val);
    return ret;
}

static inline mexpr_var_t  
math_equal_opr_fn_string_string_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_STRING);
    assert (rrc.dtype == MEXPR_DTYPE_STRING);

    ret.dtype = MEXPR_DTYPE_BOOL;

    unsigned char* lopnd_val = lrc.u.str_val;
    unsigned char* ropnd_val = rrc.u.str_val;

    ret.u.b_val = (strcmp ( lopnd_val,  ropnd_val) == 0);
    return ret;
}



// MATH_NOT_EQ
static inline mexpr_var_t  
math_nequal_opr_fn_int_int_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_BOOL;

    int lopnd_val = lrc.u.int_val;
    int ropnd_val = rrc.u.int_val;

    ret.u.b_val = (lopnd_val != ropnd_val);
    return ret;
}

static inline mexpr_var_t  
math_nequal_opr_fn_int_double_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_BOOL;

    int lopnd_val = lrc.u.int_val;
    double ropnd_val = rrc.u.d_val;

    ret.u.b_val = ((double)lopnd_val != ropnd_val);
    return ret;
}

static inline mexpr_var_t  
math_nequal_opr_fn_double_int_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_BOOL;

    double lopnd_val = lrc.u.d_val;
    int ropnd_val = rrc.u.int_val;

    ret.u.b_val = (lopnd_val != (double)ropnd_val);
    return ret;
}

static inline mexpr_var_t  
math_nequal_opr_fn_double_double_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_BOOL;

    double lopnd_val = lrc.u.d_val;
    double ropnd_val = rrc.u.d_val;

    ret.u.b_val = (lopnd_val != ropnd_val);
    return ret;
}

static inline mexpr_var_t  
math_nequal_opr_fn_string_string_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_STRING);
    assert (rrc.dtype == MEXPR_DTYPE_STRING);

    ret.dtype = MEXPR_DTYPE_BOOL;

    unsigned char* lopnd_val = lrc.u.str_val;
    unsigned char* ropnd_val = rrc.u.str_val;

    ret.u.b_val = (strcmp ( lopnd_val,  ropnd_val) != 0);
    return ret;
}

// MATH_OR
static inline mexpr_var_t  
math_or_opr_fn_bol_bool_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_BOOL);
    assert (rrc.dtype == MEXPR_DTYPE_BOOL);

    ret.dtype = MEXPR_DTYPE_BOOL;

    ret.u.b_val = lrc.u.b_val || rrc.u.b_val;
    return ret;
}


// MATH_AND
static inline mexpr_var_t  
math_and_opr_fn_bol_bool_bool (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_BOOL);
    assert (rrc.dtype == MEXPR_DTYPE_BOOL);

    ret.dtype = MEXPR_DTYPE_BOOL;

    ret.u.b_val = lrc.u.b_val && rrc.u.b_val;
    return ret;
}

// MATH_MUL
static inline mexpr_var_t  
math_mul_opr_fn_int_int_int  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_INT;

    ret.u.int_val = lrc.u.int_val * rrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_mul_opr_fn_int_double_double  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = (double)lrc.u.int_val * rrc.u.d_val;
    return ret;
}

static inline mexpr_var_t  
math_mul_opr_fn_double_int_double  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = lrc.u.d_val * (double)rrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_mul_opr_fn_double_double_double  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = lrc.u.d_val * rrc.u.d_val;
    return ret;
}


// MATH_DIV
static inline mexpr_var_t  
math_div_opr_fn_int_int_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    if (rrc.u.int_val == 0) {
        printf ("Error : Divide by Zero\n");
        ret.dtype = MEXPR_DTYPE_INVALID;
        return ret;
    }
    
    ret.u.d_val= (double) (lrc.u.int_val / rrc.u.int_val);
    return ret;
}

static inline mexpr_var_t  
math_div_opr_fn_int_double_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    if (rrc.u.d_val == 0) {
        printf ("Error : Divide by Zero\n");
        ret.dtype = MEXPR_DTYPE_INVALID;
        return ret;
    }
    
    ret.u.d_val= (double) ((double)lrc.u.int_val / rrc.u.d_val);
    return ret;
}


static inline mexpr_var_t  
math_div_opr_fn_double_int_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    if (rrc.u.int_val == 0) {
        printf ("Error : Divide by Zero\n");
        ret.dtype = MEXPR_DTYPE_INVALID;
        return ret;
    }
    
    ret.u.d_val= (double) (lrc.u.d_val / (double)rrc.u.int_val);
    return ret;
}

static inline mexpr_var_t  
math_div_opr_fn_double_double_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    if (rrc.u.d_val == 0) {
        printf ("Error : Divide by Zero\n");
        ret.dtype = MEXPR_DTYPE_INVALID;
        return ret;
    }
    
    ret.u.d_val= (double) (lrc.u.d_val / rrc.u.d_val);
    return ret;
}


// MATH_SQR
static inline mexpr_var_t  
math_sqr_opr_fn_int_nan_int (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_INT;

    ret.u.int_val =  lrc.u.int_val * lrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_sqr_opr_fn_double_nan_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val =  lrc.u.d_val * lrc.u.d_val;
    return ret;
}


// MATH_SQRT
static inline mexpr_var_t  
math_sqrt_opr_fn_int_nan_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val =  sqrt((double)lrc.u.int_val) ;
    return ret;
}

static inline mexpr_var_t  
math_sqrt_opr_fn_double_nan_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = sqrt( lrc.u.d_val );
    return ret;
}

// MATH_MAX
static inline mexpr_var_t  
math_max_opr_fn_int_int_int (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_INT;

    ret.u.int_val = lrc.u.int_val > rrc.u.int_val ? lrc.u.int_val : rrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_max_opr_fn_int_double_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = (double)lrc.u.int_val > rrc.u.d_val ? (double)lrc.u.int_val : rrc.u.d_val;
    return ret;
}

static inline mexpr_var_t  
math_max_opr_fn_double_int_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = lrc.u.d_val > (double)rrc.u.int_val ? lrc.u.d_val : (double)rrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_max_opr_fn_double_double_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = lrc.u.d_val > rrc.u.d_val ? lrc.u.d_val : rrc.u.d_val;
    return ret;
}

static inline mexpr_var_t  
math_max_opr_fn_string_string_string (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_STRING);
    assert (rrc.dtype == MEXPR_DTYPE_STRING);

    ret.dtype = MEXPR_DTYPE_STRING;

    int l_len = strlen (lrc.u.str_val);
    int r_len = strlen (rrc.u.str_val);

    ret.u.str_val = l_len > r_len ? lrc.u.str_val : rrc.u.str_val;
    return ret;
}


// MATH_MIN
static inline mexpr_var_t  
math_min_opr_fn_int_int_int (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_INT;

    ret.u.int_val = lrc.u.int_val < rrc.u.int_val ? lrc.u.int_val : rrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_min_opr_fn_int_double_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = (double)lrc.u.int_val < rrc.u.d_val ? (double)lrc.u.int_val : rrc.u.d_val;
    return ret;
}

static inline mexpr_var_t  
math_min_opr_fn_double_int_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = lrc.u.d_val < (double)rrc.u.int_val ? lrc.u.d_val : (double)rrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_min_opr_fn_double_double_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = lrc.u.d_val < rrc.u.d_val ? lrc.u.d_val : rrc.u.d_val;
    return ret;
}

static inline mexpr_var_t  
math_min_opr_fn_string_string_string (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_STRING);
    assert (rrc.dtype == MEXPR_DTYPE_STRING);

    ret.dtype = MEXPR_DTYPE_STRING;

    int l_len = strlen (lrc.u.str_val);
    int r_len = strlen (rrc.u.str_val);

    ret.u.str_val = l_len < r_len ? lrc.u.str_val : rrc.u.str_val;
    return ret;
}

// MATH_PLUS
static inline mexpr_var_t  
math_plus_opr_fn_int_int_int  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_INT;

    ret.u.int_val = lrc.u.int_val + rrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_plus_opr_fn_int_double_double  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = (double)lrc.u.int_val + rrc.u.d_val;
    return ret;
}

static inline mexpr_var_t  
math_plus_opr_fn_double_int_double  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = lrc.u.d_val + (double)rrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_plus_opr_fn_double_double_double  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = lrc.u.d_val + rrc.u.d_val;
    return ret;
}

static inline mexpr_var_t  
math_plus_opr_fn_string_string_string (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    static unsigned char str_out [MEXPR_MAX_STRING_VAL_LEN + MEXPR_MAX_STRING_VAL_LEN];

    assert (lrc.dtype == MEXPR_DTYPE_STRING);
    assert (rrc.dtype == MEXPR_DTYPE_STRING);

    ret.dtype = MEXPR_DTYPE_STRING;    

    snprintf (str_out, sizeof (str_out), "%s%s", lrc.u.str_val, rrc.u.str_val);
    ret.u.str_val = str_out;
    return ret;
}

// MATH_MINUS
static inline mexpr_var_t  
math_minus_opr_fn_int_int_int  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_INT;

    ret.u.int_val = lrc.u.int_val -  rrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_minus_opr_fn_int_double_double  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = (double)lrc.u.int_val - rrc.u.d_val;
    return ret;
}

static inline mexpr_var_t  
math_minus_opr_fn_double_int_double  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = lrc.u.d_val - (double)rrc.u.int_val;
    return ret;
}

static inline mexpr_var_t  
math_minus_opr_fn_double_double_double  (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = lrc.u.d_val - rrc.u.d_val;
    return ret;
}



// MATH_SIN
static inline mexpr_var_t  
math_sin_opr_fn_int_nan_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val =  sin((double)lrc.u.int_val) ;
    return ret;
}

static inline mexpr_var_t  
math_sin_opr_fn_double_nan_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = sin( lrc.u.d_val );
    return ret;
}


// MATH_COS
static inline mexpr_var_t  
math_cos_opr_fn_int_nan_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val =  cos((double)lrc.u.int_val) ;
    return ret;
}

static inline mexpr_var_t  
math_cos_opr_fn_double_nan_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val = cos( lrc.u.d_val );
    return ret;
}


// MATH_POW
static inline mexpr_var_t  
math_pow_opr_fn_int_int_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val =  pow ((double)lrc.u.int_val, (double)rrc.u.int_val);
    return ret;
}


static inline mexpr_var_t  
math_pow_opr_fn_int_double_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val =  pow ((double)lrc.u.int_val, rrc.u.d_val);
    return ret;
}

static inline mexpr_var_t  
math_pow_opr_fn_double_int_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_INT);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val =  pow (lrc.u.d_val, (double)rrc.u.int_val);
    return ret;
}

static inline mexpr_var_t  
math_pow_opr_fn_double_double_double (mexpr_var_t lrc, mexpr_var_t rrc) {

    mexpr_var_t  ret;
    assert (lrc.dtype == MEXPR_DTYPE_DOUBLE);
    assert (rrc.dtype == MEXPR_DTYPE_DOUBLE);

    ret.dtype = MEXPR_DTYPE_DOUBLE;

    ret.u.d_val =  pow (lrc.u.d_val, rrc.u.d_val);
    return ret;
}

static mexpr_var_t
math_opr_fn_not_supported (mexpr_var_t a, mexpr_var_t b) {

    mexpr_var_t var;
    var.dtype = MEXPR_DTYPE_INVALID;
    return var;
}

// MATH_MOD

static mexpr_var_t
math_mod_opr_fn_int_int_double (mexpr_var_t a, mexpr_var_t b) {

    mexpr_var_t ret;
    assert (lrc.dtype == MEXPR_DTYPE_INT);
    assert (rrc.dtype == MEXPR_DTYPE_INT);


    ret.dtype = MEXPR_DTYPE_INT;

    ret.u.int_val = a.u.int_val % b.u.int_val;
    return ret;
}

static operator_fn_ptr_t MexprDb[MATH_OPR_MAX][MEXPR_DTYPE_MAX][MEXPR_DTYPE_MAX] =
    {

        // ---------------   MATH_LESS_THAN_EQ

        math_less_than_eq_opr_fn_int_int_bool,    /* op code 0, int , int */
        math_less_than_eq_opr_fn_int_double_bool, /* op code 0, int , double */
        math_opr_fn_not_supported,                /* op code 0, int , string*/
        math_opr_fn_not_supported,                /* op code 0, int , bool*/

        math_less_than_eq_opr_fn_double_int_bool,    /* op code 0, double , int */
        math_less_than_eq_opr_fn_double_double_bool, /* op code 0, double , double */
        math_opr_fn_not_supported,                   /* op code 0, double , string*/
        math_opr_fn_not_supported,                   /* op code 0, double , bool*/

        math_opr_fn_not_supported, /* op code 0, string , int */
        math_opr_fn_not_supported, /* op code 0, string , double */
        math_opr_fn_not_supported, /* op code 0, string , string*/
        math_opr_fn_not_supported, /* op code 0, string , bool*/

        math_opr_fn_not_supported, /* op code 0, bool , int */
        math_opr_fn_not_supported, /* op code 0, bool , double */
        math_opr_fn_not_supported, /* op code 0, bool , string*/
        math_opr_fn_not_supported, /* op code 0, bool , bool*/

        // --------------- MATH_LESS_THAN

        math_less_than_opr_fn_int_int_bool,    /* op code 1, int , int */
        math_less_than_opr_fn_int_double_bool, /* op code 1, int , double */
        math_opr_fn_not_supported,             /* op code 1, int , string*/
        math_opr_fn_not_supported,             /* op code 1, int , bool*/

        math_less_than_opr_fn_double_int_bool,    /* op code 1, double , int */
        math_less_than_opr_fn_double_double_bool, /* op code 1, double , double */
        math_opr_fn_not_supported,                /* op code 1, double , string*/
        math_opr_fn_not_supported,                /* op code 1, double , bool*/

        math_opr_fn_not_supported, /* op code 1, string , int */
        math_opr_fn_not_supported, /* op code 1, string , double */
        math_opr_fn_not_supported, /* op code 1, string , string*/
        math_opr_fn_not_supported, /* op code 1, string , bool*/

        math_opr_fn_not_supported, /* op code 1, bool , int */
        math_opr_fn_not_supported, /* op code 1, bool , double */
        math_opr_fn_not_supported, /* op code 1, bool , string*/
        math_opr_fn_not_supported, /* op code 1, bool , bool*/

        // --------------- MATH_GREATER_THAN

        math_greater_than_opr_fn_int_int_bool,    /* op code 2, int , int */
        math_greater_than_opr_fn_int_double_bool, /* op code 2, int , double */
        math_opr_fn_not_supported,                /* op code 2, int , string*/
        math_opr_fn_not_supported,                /* op code 2, int , bool*/

        math_greater_than_opr_fn_double_int_bool,    /* op code 2, double , int */
        math_greater_than_opr_fn_double_double_bool, /* op code 2, double , double */
        math_opr_fn_not_supported,                   /* op code 2, double , string*/
        math_opr_fn_not_supported,                   /* op code 2, double , bool*/

        math_opr_fn_not_supported, /* op code 2, string , int */
        math_opr_fn_not_supported, /* op code 2, string , double */
        math_opr_fn_not_supported, /* op code 2, string , string*/
        math_opr_fn_not_supported, /* op code 2, string , bool*/

        math_opr_fn_not_supported, /* op code 2, bool , int */
        math_opr_fn_not_supported, /* op code 2, bool , double */
        math_opr_fn_not_supported, /* op code 2, bool , string*/
        math_opr_fn_not_supported, /* op code 2, bool , bool*/

        // ---------------  MATH_EQ

        math_equal_opr_fn_int_int_bool,    /* int , int */
        math_equal_opr_fn_int_double_bool, /* int , double */
        math_opr_fn_not_supported,         /* int , string*/
        math_opr_fn_not_supported,         /* int , bool*/

        math_equal_opr_fn_double_int_bool,    /* double , int */
        math_equal_opr_fn_double_double_bool, /* double , double */
        math_opr_fn_not_supported,            /* double , string*/
        math_opr_fn_not_supported,            /* double , bool*/

        math_opr_fn_not_supported,            /* string , int */
        math_opr_fn_not_supported,            /* string , double */
        math_equal_opr_fn_string_string_bool, /* string , string*/
        math_opr_fn_not_supported,            /* string , bool*/

        math_opr_fn_not_supported, /* bool , int */
        math_opr_fn_not_supported, /* bool , double */
        math_opr_fn_not_supported, /* bool , string*/
        math_opr_fn_not_supported, /* bool , bool*/

        // ---------------  MATH_NOT_EQ

        math_nequal_opr_fn_int_int_bool,    /* int , int */
        math_nequal_opr_fn_int_double_bool, /* int , double */
        math_opr_fn_not_supported,          /* int , string*/
        math_opr_fn_not_supported,          /* int , bool*/

        math_nequal_opr_fn_double_int_bool,    /* double , int */
        math_nequal_opr_fn_double_double_bool, /* double , double */
        math_opr_fn_not_supported,             /* double , string*/
        math_opr_fn_not_supported,             /* double , bool*/

        math_opr_fn_not_supported,             /* string , int */
        math_opr_fn_not_supported,             /* string , double */
        math_nequal_opr_fn_string_string_bool, /* string , string*/
        math_opr_fn_not_supported,             /* string , bool*/

        math_opr_fn_not_supported, /* bool , int */
        math_opr_fn_not_supported, /* bool , double */
        math_opr_fn_not_supported, /* bool , string*/
        math_opr_fn_not_supported, /* bool , bool*/

        // ---------------  MATH_OR

        math_opr_fn_not_supported, /* int , int */
        math_opr_fn_not_supported, /* int , double */
        math_opr_fn_not_supported, /* int , string*/
        math_opr_fn_not_supported, /* int , bool*/

        math_opr_fn_not_supported, /* double , int */
        math_opr_fn_not_supported, /* double , double */
        math_opr_fn_not_supported, /* double , string*/
        math_opr_fn_not_supported, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_or_opr_fn_bol_bool_bool, /* bool , bool*/


        // ---------------  MATH_AND

        math_opr_fn_not_supported, /* int , int */
        math_opr_fn_not_supported, /* int , double */
        math_opr_fn_not_supported, /* int , string*/
        math_opr_fn_not_supported, /* int , bool*/

        math_opr_fn_not_supported, /* double , int */
        math_opr_fn_not_supported, /* double , double */
        math_opr_fn_not_supported, /* double , string*/
        math_opr_fn_not_supported, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_and_opr_fn_bol_bool_bool, /* bool , bool*/


        // ---------------  MATH_MUL

        math_mul_opr_fn_int_int_int, /* int , int */
        math_mul_opr_fn_int_double_double, /* int , double */
        math_opr_fn_not_supported, /* int , string*/
        math_opr_fn_not_supported, /* int , bool*/

        math_mul_opr_fn_double_int_double, /* double , int */
        math_mul_opr_fn_double_double_double, /* double , double */
        math_opr_fn_not_supported, /* double , string*/
        math_opr_fn_not_supported, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported, /* bool , bool*/


        // ---------------  MATH_DIV

        math_div_opr_fn_int_int_double, /* int , int */
        math_div_opr_fn_int_double_double, /* int , double */
        math_opr_fn_not_supported, /* int , string*/
        math_opr_fn_not_supported, /* int , bool*/

        math_div_opr_fn_double_int_double, /* double , int */
        math_div_opr_fn_double_double_double, /* double , double */
        math_opr_fn_not_supported, /* double , string*/
        math_opr_fn_not_supported, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_and_opr_fn_bol_bool_bool, /* bool , bool*/


        // ---------------  MATH_SQR

        math_sqr_opr_fn_int_nan_int, /* int , int */
        math_sqr_opr_fn_int_nan_int, /* int , double */
        math_sqr_opr_fn_int_nan_int, /* int , string*/
       math_sqr_opr_fn_int_nan_int,  /* int , bool*/

        math_sqr_opr_fn_double_nan_double, /* double , int */
        math_sqr_opr_fn_double_nan_double, /* double , double */
        math_sqr_opr_fn_double_nan_double, /* double , string*/
        math_sqr_opr_fn_double_nan_double, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported,   /* bool , bool*/



        // ---------------  MATH_SQRT

        math_sqrt_opr_fn_int_nan_double, /* int , int */
        math_sqrt_opr_fn_int_nan_double, /* int , double */
        math_sqrt_opr_fn_int_nan_double, /* int , string*/
        math_sqrt_opr_fn_int_nan_double,  /* int , bool*/

        math_sqrt_opr_fn_double_nan_double, /* double , int */
        math_sqrt_opr_fn_double_nan_double, /* double , double */
        math_sqrt_opr_fn_double_nan_double, /* double , string*/
        math_sqrt_opr_fn_double_nan_double, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported,    /* bool , bool*/


        // ---------------  MATH_MAX

        math_max_opr_fn_int_int_int, /* int , int */
        math_max_opr_fn_int_double_double, /* int , double */
        math_opr_fn_not_supported,  /* int , string*/
        math_opr_fn_not_supported,   /* int , bool*/

        math_max_opr_fn_double_int_double, /* double , int */
        math_max_opr_fn_double_double_double, /* double , double */
        math_opr_fn_not_supported, /* double , string*/
        math_opr_fn_not_supported, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_max_opr_fn_string_string_string, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported, /* bool , bool*/



        // ---------------  MATH_MIN

        math_min_opr_fn_int_int_int, /* int , int */
        math_min_opr_fn_int_double_double, /* int , double */
        math_opr_fn_not_supported,  /* int , string*/
        math_opr_fn_not_supported,   /* int , bool*/

        math_min_opr_fn_double_int_double, /* double , int */
        math_min_opr_fn_double_double_double, /* double , double */
        math_opr_fn_not_supported, /* double , string*/
        math_opr_fn_not_supported, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_min_opr_fn_string_string_string, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported, /* bool , bool*/


        // ---------------  MATH_PLUS

        math_plus_opr_fn_int_int_int, /* int , int */
        math_plus_opr_fn_int_double_double, /* int , double */
        math_opr_fn_not_supported, /* int , string*/
        math_opr_fn_not_supported, /* int , bool*/

        math_plus_opr_fn_double_int_double, /* double , int */
        math_plus_opr_fn_double_double_double, /* double , double */
        math_opr_fn_not_supported, /* double , string*/
        math_opr_fn_not_supported, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_plus_opr_fn_string_string_string, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported, /* bool , bool*/


        // ---------------  MATH_MINUS

        math_minus_opr_fn_int_int_int, /* int , int */
        math_minus_opr_fn_int_double_double, /* int , double */
        math_opr_fn_not_supported, /* int , string*/
        math_opr_fn_not_supported, /* int , bool*/

        math_minus_opr_fn_double_int_double, /* double , int */
        math_minus_opr_fn_double_double_double, /* double , double */
        math_opr_fn_not_supported, /* double , string*/
        math_opr_fn_not_supported, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported, /* bool , bool*/        


        // ---------------  MATH_SIN

        math_sin_opr_fn_int_nan_double, /* int , int */
        math_sin_opr_fn_int_nan_double, /* int , double */
        math_sin_opr_fn_int_nan_double, /* int , string*/
        math_sin_opr_fn_int_nan_double,  /* int , bool*/

        math_sin_opr_fn_double_nan_double, /* double , int */
        math_sin_opr_fn_double_nan_double, /* double , double */
        math_sin_opr_fn_double_nan_double, /* double , string*/
        math_sin_opr_fn_double_nan_double, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported,    /* bool , bool*/


        // ---------------  MATH_COS

        math_cos_opr_fn_int_nan_double, /* int , int */
        math_cos_opr_fn_int_nan_double, /* int , double */
        math_cos_opr_fn_int_nan_double, /* int , string*/
        math_cos_opr_fn_int_nan_double,  /* int , bool*/

        math_cos_opr_fn_double_nan_double, /* double , int */
        math_cos_opr_fn_double_nan_double, /* double , double */
        math_cos_opr_fn_double_nan_double, /* double , string*/
        math_cos_opr_fn_double_nan_double, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported,    /* bool , bool*/



        // ---------------  MATH_POW

        math_pow_opr_fn_int_int_double, /* int , int */
        math_pow_opr_fn_int_double_double, /* int , double */
        math_opr_fn_not_supported, /* int , string*/
        math_opr_fn_not_supported,  /* int , bool*/

        math_pow_opr_fn_double_int_double, /* double , int */
        math_pow_opr_fn_double_double_double, /* double , double */
        math_cos_opr_fn_double_nan_double, /* double , string*/
        math_cos_opr_fn_double_nan_double, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported,    /* bool , bool*/


      // ---------------  MATH_MOD

        math_mod_opr_fn_int_int_double, /* int , int */
        math_opr_fn_not_supported, /* int , double */
        math_opr_fn_not_supported, /* int , string*/
        math_opr_fn_not_supported,  /* int , bool*/

        math_opr_fn_not_supported, /* double , int */
        math_opr_fn_not_supported, /* double , double */
        math_opr_fn_not_supported, /* double , string*/
       math_opr_fn_not_supported, /* double , bool*/

        math_opr_fn_not_supported, /* string , int */
        math_opr_fn_not_supported, /* string , double */
        math_opr_fn_not_supported, /* string , string*/
        math_opr_fn_not_supported, /* string , bool*/

        math_opr_fn_not_supported,    /* bool , int */
        math_opr_fn_not_supported,    /* bool , double */
        math_opr_fn_not_supported,    /* bool , string*/
        math_opr_fn_not_supported,    /* bool , bool*/

};

typedef mexpr_dtypes_t (*operator_fn_dtypes_supported_ptr_t) (mexpr_dtypes_t , mexpr_dtypes_t);

// MATH_LESS_THAN_EQ
static mexpr_dtypes_t 
math_less_than_eq_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    switch (ld) {

        case MEXPR_DTYPE_INT:
        case MEXPR_DTYPE_DOUBLE:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_BOOL;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
        break;
        case MEXPR_DTYPE_UNKNOWN:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_BOOL;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_UNKNOWN;
                default:
                    return MEXPR_DTYPE_INVALID;
            }            
        break;
        default:
             return MEXPR_DTYPE_INVALID;
    }
}

// MATH_LESS_THAN
static mexpr_dtypes_t 
math_less_than_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    switch (ld) {

        case MEXPR_DTYPE_INT:
        case MEXPR_DTYPE_DOUBLE:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_BOOL;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
        break;
        case MEXPR_DTYPE_UNKNOWN:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_BOOL;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_UNKNOWN;
                default:
                    return MEXPR_DTYPE_INVALID;
            }            
        break;
        default:
             return MEXPR_DTYPE_INVALID;
    }
}

// MATH_GREATER_THAN
static mexpr_dtypes_t 
math_greater_than_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    switch (ld) {

        case MEXPR_DTYPE_INT:
        case MEXPR_DTYPE_DOUBLE:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_BOOL;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
        break;
        case MEXPR_DTYPE_UNKNOWN:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_BOOL;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_UNKNOWN;
                default:
                    return MEXPR_DTYPE_INVALID;
            }            
        break;
        default:
             return MEXPR_DTYPE_INVALID;
    }
}

// MATH_EQ
static mexpr_dtypes_t 
math_eq_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

        switch (ld) {

        case MEXPR_DTYPE_INT:
        case MEXPR_DTYPE_DOUBLE:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_BOOL;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
        break;
        case MEXPR_DTYPE_STRING:
            switch(rd) {
                case MEXPR_DTYPE_STRING:
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_BOOL;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
        break;
        case MEXPR_DTYPE_UNKNOWN:
            switch(rd) {
                case MEXPR_DTYPE_STRING:
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_BOOL;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_UNKNOWN;
                default:
                    return MEXPR_DTYPE_INVALID;
            }            
        break;
        default:
             return MEXPR_DTYPE_INVALID;
    }
}


// MATH_NOT_EQ
static mexpr_dtypes_t 
math_neq_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

        switch (ld) {

        case MEXPR_DTYPE_INT:
        case MEXPR_DTYPE_DOUBLE:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_BOOL;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
        break;
        case MEXPR_DTYPE_STRING:
            switch(rd) {
                case MEXPR_DTYPE_STRING:
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_BOOL;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
        break;
        case MEXPR_DTYPE_UNKNOWN:
            switch(rd) {
                case MEXPR_DTYPE_STRING:
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_BOOL;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_UNKNOWN;
                default:
                    return MEXPR_DTYPE_INVALID;
            }            
        break;
        default:
             return MEXPR_DTYPE_INVALID;
    }
}

// MATH_OR
static mexpr_dtypes_t 
math_or_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    if (ld == MEXPR_DTYPE_BOOL && rd == MEXPR_DTYPE_BOOL)
        return MEXPR_DTYPE_BOOL;
    if (ld == MEXPR_DTYPE_UNKNOWN && rd == MEXPR_DTYPE_BOOL)
        return rd;
    if (ld == MEXPR_DTYPE_BOOL && rd == MEXPR_DTYPE_UNKNOWN)
        return ld;
    if (ld == MEXPR_DTYPE_UNKNOWN && rd == MEXPR_DTYPE_UNKNOWN)
        return MEXPR_DTYPE_UNKNOWN;

    return MEXPR_DTYPE_INVALID;
}


// MATH_AND
static mexpr_dtypes_t 
math_and_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    if (ld == MEXPR_DTYPE_BOOL && rd == MEXPR_DTYPE_BOOL)
        return MEXPR_DTYPE_BOOL;
    if (ld == MEXPR_DTYPE_UNKNOWN && rd == MEXPR_DTYPE_BOOL)
        return rd;
    if (ld == MEXPR_DTYPE_BOOL && rd == MEXPR_DTYPE_UNKNOWN)
        return ld;
    if (ld == MEXPR_DTYPE_UNKNOWN && rd == MEXPR_DTYPE_UNKNOWN)
        return MEXPR_DTYPE_UNKNOWN;

    return MEXPR_DTYPE_INVALID;
}


// MATH_MUL
static mexpr_dtypes_t 
math_mul_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    if ( (ld == MEXPR_DTYPE_INT || ld == MEXPR_DTYPE_DOUBLE) &&
            (rd == MEXPR_DTYPE_DOUBLE || rd == MEXPR_DTYPE_INT))
        return MEXPR_DTYPE_DOUBLE;
    
    if (ld == MEXPR_DTYPE_UNKNOWN && (rd == MEXPR_DTYPE_INT || rd == MEXPR_DTYPE_DOUBLE))
        return rd;
     if (rd == MEXPR_DTYPE_UNKNOWN && (ld == MEXPR_DTYPE_INT || ld == MEXPR_DTYPE_DOUBLE))
        return ld;

    if (ld == MEXPR_DTYPE_UNKNOWN && rd == MEXPR_DTYPE_UNKNOWN)
        return MEXPR_DTYPE_UNKNOWN;

    return MEXPR_DTYPE_INVALID;
}


// MATH_DIV
static mexpr_dtypes_t 
math_div_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    if ( (ld == MEXPR_DTYPE_INT || ld == MEXPR_DTYPE_DOUBLE) &&
            (rd == MEXPR_DTYPE_DOUBLE || rd == MEXPR_DTYPE_INT))
        return MEXPR_DTYPE_DOUBLE;

    if (ld == MEXPR_DTYPE_UNKNOWN && (rd == MEXPR_DTYPE_INT || rd == MEXPR_DTYPE_DOUBLE))
        return MEXPR_DTYPE_DOUBLE;

     if (rd == MEXPR_DTYPE_UNKNOWN && (ld == MEXPR_DTYPE_INT || ld == MEXPR_DTYPE_DOUBLE))
        return MEXPR_DTYPE_DOUBLE;

    if (ld == MEXPR_DTYPE_UNKNOWN && rd == MEXPR_DTYPE_UNKNOWN)
        return MEXPR_DTYPE_UNKNOWN;

    return MEXPR_DTYPE_INVALID;
}


// MATH_SQR
static mexpr_dtypes_t 
math_sqr_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    if ( (ld == MEXPR_DTYPE_INT || ld == MEXPR_DTYPE_DOUBLE) )
        return MEXPR_DTYPE_DOUBLE;

    if (ld == MEXPR_DTYPE_UNKNOWN) return MEXPR_DTYPE_UNKNOWN;

    return MEXPR_DTYPE_INVALID;
}


// MATH_SQRT
static mexpr_dtypes_t 
math_sqrt_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    if (ld == MEXPR_DTYPE_INT || ld == MEXPR_DTYPE_DOUBLE)
        return MEXPR_DTYPE_DOUBLE;

     if (ld == MEXPR_DTYPE_UNKNOWN) return MEXPR_DTYPE_UNKNOWN;

    return MEXPR_DTYPE_INVALID;
}


// MATH_MAX
static mexpr_dtypes_t 
math_max_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    switch (ld) {
        case MEXPR_DTYPE_INT:

            switch (ld) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_INT;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_STRING:
                    return MEXPR_DTYPE_INVALID;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_INT;
                break;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;        

        case MEXPR_DTYPE_DOUBLE:

            switch (ld) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_STRING:
                    return MEXPR_DTYPE_INVALID;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_DOUBLE;
                break;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;       


        case MEXPR_DTYPE_STRING:

            switch (ld) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_INVALID;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_INVALID;
                case MEXPR_DTYPE_STRING:
                    return MEXPR_DTYPE_STRING;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_STRING;
                break;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;     

        case MEXPR_DTYPE_UNKNOWN:

            switch (ld) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_INT;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_STRING:
                    return MEXPR_DTYPE_STRING;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_UNKNOWN;
                break;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
        break;
        default:
            return MEXPR_DTYPE_INVALID;
    }

    return MEXPR_DTYPE_INVALID;
}


// MATH_MIN
static mexpr_dtypes_t 
math_min_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    switch (ld) {
        case MEXPR_DTYPE_INT:

            switch (ld) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_INT;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_STRING:
                    return MEXPR_DTYPE_INVALID;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_INT;
                break;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;        

        case MEXPR_DTYPE_DOUBLE:

            switch (ld) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_STRING:
                    return MEXPR_DTYPE_INVALID;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_DOUBLE;
                break;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;       

        case MEXPR_DTYPE_STRING:

            switch (ld) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_INVALID;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_INVALID;
                case MEXPR_DTYPE_STRING:
                    return MEXPR_DTYPE_STRING;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_STRING;
                break;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;     

        case MEXPR_DTYPE_UNKNOWN:

            switch (ld) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_INT;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_STRING:
                    return MEXPR_DTYPE_STRING;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_UNKNOWN;
                break;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
        break;
        default:
            return MEXPR_DTYPE_INVALID;
    }

    return MEXPR_DTYPE_INVALID;
}

// MATH_PLUS
static mexpr_dtypes_t 
math_plus_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    switch (ld) {

        case MEXPR_DTYPE_INT:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_INT;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_DOUBLE;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;
        case MEXPR_DTYPE_DOUBLE:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_DOUBLE;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;            
        case MEXPR_DTYPE_UNKNOWN:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_STRING:
                    return MEXPR_DTYPE_STRING;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_UNKNOWN;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;                 
        case MEXPR_DTYPE_STRING:
            switch (rd) {
                case MEXPR_DTYPE_STRING:
                 case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_STRING;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;
        default:
             return MEXPR_DTYPE_INVALID;
    }
}

// MATH_MINUS
static mexpr_dtypes_t 
math_minus_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    switch (ld) {

        case MEXPR_DTYPE_INT:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_INT;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_DOUBLE;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;
        case MEXPR_DTYPE_DOUBLE:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_DOUBLE;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;            
        case MEXPR_DTYPE_UNKNOWN:
            switch (rd) {
                case MEXPR_DTYPE_INT:
                case MEXPR_DTYPE_DOUBLE:
                    return MEXPR_DTYPE_DOUBLE;
                case MEXPR_DTYPE_UNKNOWN:
                    return MEXPR_DTYPE_UNKNOWN;
                default:
                    return MEXPR_DTYPE_INVALID;
            }
            break;                 
        default:
             return MEXPR_DTYPE_INVALID;
    }
}


// MATH_SIN
// MATH_COS
static mexpr_dtypes_t 
math_trignometry_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    if (ld == MEXPR_DTYPE_INT || ld == MEXPR_DTYPE_DOUBLE)
        return MEXPR_DTYPE_DOUBLE;
    if (ld == MEXPR_DTYPE_UNKNOWN) return MEXPR_DTYPE_UNKNOWN;
    return MEXPR_DTYPE_INVALID;
}


static mexpr_dtypes_t 
math_pow_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    if ( (ld == MEXPR_DTYPE_INT || ld == MEXPR_DTYPE_DOUBLE) &&
            (rd == MEXPR_DTYPE_DOUBLE || rd == MEXPR_DTYPE_INT))
        return MEXPR_DTYPE_DOUBLE;

    if (ld == MEXPR_DTYPE_UNKNOWN && (rd == MEXPR_DTYPE_INT || rd == MEXPR_DTYPE_DOUBLE))
        return MEXPR_DTYPE_DOUBLE;

    if (rd == MEXPR_DTYPE_UNKNOWN && (ld == MEXPR_DTYPE_INT || ld == MEXPR_DTYPE_DOUBLE))
        return MEXPR_DTYPE_DOUBLE;

    if (ld == MEXPR_DTYPE_UNKNOWN && rd == MEXPR_DTYPE_UNKNOWN) 
        return MEXPR_DTYPE_UNKNOWN;

    return MEXPR_DTYPE_INVALID;
}


static mexpr_dtypes_t 
math_mod_dtypes_supported (mexpr_dtypes_t ld, mexpr_dtypes_t rd) {

    if ( ld == MEXPR_DTYPE_INT  && rd == MEXPR_DTYPE_INT )
        return MEXPR_DTYPE_INT;

    if (ld == MEXPR_DTYPE_UNKNOWN && rd == MEXPR_DTYPE_INT)
        return MEXPR_DTYPE_INT;

    if (rd == MEXPR_DTYPE_UNKNOWN && ld == MEXPR_DTYPE_INT )
        return MEXPR_DTYPE_INT;

    if (ld == MEXPR_DTYPE_UNKNOWN && rd == MEXPR_DTYPE_UNKNOWN) 
        return MEXPR_DTYPE_UNKNOWN;

    return MEXPR_DTYPE_INVALID;
}


static operator_fn_dtypes_supported_ptr_t MexprDb_dtypes_supported[MATH_OPR_MAX] =
    {
        math_less_than_eq_dtypes_supported,
        math_less_than_dtypes_supported,
        math_greater_than_dtypes_supported,
        math_eq_dtypes_supported,
        math_neq_dtypes_supported,
        math_or_dtypes_supported,
        math_and_dtypes_supported,
        math_mul_dtypes_supported,
        math_div_dtypes_supported,
        math_sqr_dtypes_supported,
        math_sqrt_dtypes_supported,
        math_max_dtypes_supported,
        math_min_dtypes_supported,
        math_plus_dtypes_supported,
        math_minus_dtypes_supported,
        math_trignometry_dtypes_supported,
        math_trignometry_dtypes_supported,
        math_pow_dtypes_supported,
        math_mod_dtypes_supported,
        0,
        0
    };