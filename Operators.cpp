#include <cstddef>
#include <assert.h>
#include <string>
#include "Operators.h"
#include "Dtype.h"

Operator::Operator() { 

    opid = MATH_CPP_OPR_MAX;
    is_unary = false;
    is_optimized = false;
    optimized_result = NULL;
}

Operator::~Operator() { 

    if (this->optimized_result) {
        delete this->optimized_result;
    }
}



/* MOD operator */

OperatorMod::OperatorMod() { 

     opid =  MATH_CPP_MOD;
     name = "Mod";
     is_unary = false;
}

OperatorMod::~OperatorMod() {  }

mexprcpp_dtypes_t
OperatorMod::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    switch (did1) {

        case MATH_CPP_INT:

            switch (did2) {

                case MATH_CPP_INT:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_INT;
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }

        case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_INT:
                    return MATH_CPP_INT;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DTYPE_WILDCRAD;
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }

        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

Dtype *
OperatorMod::compute(Dtype *dtype1, Dtype *dtype2) {

    mexprcpp_dtypes_t res_did = this->ResultStorageType (dtype1->did, dtype2->did);

    if (res_did == MATH_CPP_DTYPE_INVALID) return NULL;

    /* This Operator Supports only int results*/
    assert (res_did == MATH_CPP_INT);
    Dtype *res = Dtype::factory(res_did);
    Dtype_INT *res_int = dynamic_cast <Dtype_INT *> (res);
    Dtype_INT *dtype1_int = dynamic_cast <Dtype_INT *> (dtype1);
    Dtype_INT *dtype2_int = dynamic_cast <Dtype_INT *> (dtype2);
    res_int->dtype.int_val = dtype1_int->dtype.int_val % dtype2_int->dtype.int_val;
    res->del_after_use = true;
    return res;
}

MexprNode * 
OperatorMod::clone() {

    OperatorMod *obj = new OperatorMod();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}


/* PLUS operator */

OperatorPlus::OperatorPlus() { 

     opid =  MATH_CPP_PLUS;
     name = "Plus";
     is_unary = false;
}

OperatorPlus::~OperatorPlus() {  }

mexprcpp_dtypes_t
OperatorPlus::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    /* Allowed Combinations 

        int , int  => int  
        int, double => double
        double, int => double
        double, double => double
        string, string => string
    */
    switch (did1) {

        case MATH_CPP_INT:

            switch (did2) {

                case MATH_CPP_INT:
                    return MATH_CPP_INT;
                case MATH_CPP_DOUBLE:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_INT;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }

        case MATH_CPP_DOUBLE:

            switch (did2) {

                case MATH_CPP_INT:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DOUBLE:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DOUBLE;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }            


        case MATH_CPP_STRING:
            if (did2 == MATH_CPP_STRING || 
                    did2 == MATH_CPP_DTYPE_WILDCRAD) return MATH_CPP_STRING;
            return MATH_CPP_DTYPE_INVALID;


        case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_INT:
                case MATH_CPP_DOUBLE:
                case MATH_CPP_STRING:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return did2;
                case MATH_CPP_DTYPE_INVALID:
                    return MATH_CPP_DTYPE_INVALID;
            }

        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

Dtype*
OperatorPlus::compute(Dtype *dtype1, Dtype *dtype2) {

    Dtype *res;
    mexprcpp_dtypes_t res_did = this->ResultStorageType (dtype1->did, dtype2->did);
    
    if (res_did == MATH_CPP_DTYPE_INVALID || 
         res_did == MATH_CPP_DTYPE_WILDCRAD) return NULL;

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_INT);
                    Dtype_INT *res_int = dynamic_cast<Dtype_INT *> (res);
                    res_int->dtype.int_val = dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val + 
                                                            dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    res->del_after_use = true;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val +
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
                    res->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }
            break;


        case MATH_CPP_DOUBLE:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val +
                                                        (double)dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    res->del_after_use = true;
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val +
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
                    res->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }
            break;            


    case MATH_CPP_STRING:

            switch (dtype2->did) {

                case MATH_CPP_STRING:
                {
                    res = Dtype::factory (MATH_CPP_STRING);
                    Dtype_STRING *res_str = dynamic_cast<Dtype_STRING *> (res);
                    res_str->dtype.str_val = dynamic_cast<Dtype_STRING *> (dtype1)->dtype.str_val +
                                                           dynamic_cast<Dtype_STRING *> (dtype2)->dtype.str_val;
                    res->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }        
        break;


        default:
            return NULL;

    }
    
    return NULL;
}

MexprNode * 
OperatorPlus::clone() {

    OperatorPlus *obj = new OperatorPlus();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}


/* MINUS operator */

OperatorMinus::OperatorMinus() {

    opid = MATH_CPP_MINUS;
    name = "Minus";
    is_unary = false;
}

OperatorMinus::~OperatorMinus() { }

mexprcpp_dtypes_t
OperatorMinus::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    /* Allowed Combinations 

        int , int  => int  
        int, double => double
        double, int => double
        double, double => double
    */
    switch (did1) {

        case MATH_CPP_INT:

            switch (did2) {

                case MATH_CPP_INT:
                    return MATH_CPP_INT;
                case MATH_CPP_DOUBLE:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_INT;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }

        case MATH_CPP_DOUBLE:

            switch (did2) {

                case MATH_CPP_INT:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DOUBLE:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DOUBLE;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }            


           case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_INT:
                case MATH_CPP_DOUBLE:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return did2;
                case MATH_CPP_DTYPE_INVALID:
                    return MATH_CPP_DTYPE_INVALID;
            }

        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

Dtype*
OperatorMinus::compute(Dtype *dtype1, Dtype *dtype2) {

    Dtype *res;
    mexprcpp_dtypes_t res_did = this->ResultStorageType (dtype1->did, dtype2->did);
    
    if (res_did == MATH_CPP_DTYPE_INVALID || 
         res_did == MATH_CPP_DTYPE_WILDCRAD) return NULL;

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_INT);
                    Dtype_INT *res_int = dynamic_cast<Dtype_INT *> (res);
                    res_int->dtype.int_val = dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val -
                                                            dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    res->del_after_use = true;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val -
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
                    res->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }
            break;


        case MATH_CPP_DOUBLE:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val -
                                                        (double)dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    res->del_after_use = true;
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val -
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
                    res->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }
            break;            

        default:
            return NULL;

    }
    
    return NULL;
}

MexprNode * 
OperatorMinus::clone() {

    OperatorMinus *obj = new OperatorMinus();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}


/* MUL operator */

OperatorMul::OperatorMul() {

    opid = MATH_CPP_MUL;
    name = "Mul";
    is_unary = false;
}

OperatorMul::~OperatorMul() {

}

Dtype *
OperatorMul::compute(Dtype *dtype1, Dtype *dtype2) {

    Dtype *res;

    mexprcpp_dtypes_t res_did = this->ResultStorageType (dtype1->did, dtype2->did);
    
    if (res_did == MATH_CPP_DTYPE_INVALID || 
         res_did == MATH_CPP_DTYPE_WILDCRAD) return NULL;    

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_INT);
                    Dtype_INT *res_int = dynamic_cast<Dtype_INT *> (res);
                    res_int->dtype.int_val = dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val *
                                                            dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    res->del_after_use = true;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val *
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
                    res->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }
            break;


        case MATH_CPP_DOUBLE:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val *
                                                        (double)dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    res->del_after_use = true;
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val *
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
                    res->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }
            break;            

        default:
            return NULL;

    }    



}

mexprcpp_dtypes_t
OperatorMul::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    /* Allowed Combinations 

        int , int  => int  
        int, double => double
        double, int => double
        double, double => double
    */
    switch (did1) {

        case MATH_CPP_INT:

            switch (did2) {

                case MATH_CPP_INT:
                    return MATH_CPP_INT;
                case MATH_CPP_DOUBLE:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_INT;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }

        case MATH_CPP_DOUBLE:

            switch (did2) {

                case MATH_CPP_INT:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DOUBLE:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DOUBLE;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }            


           case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_INT:
                case MATH_CPP_DOUBLE:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return did2;
                case MATH_CPP_DTYPE_INVALID:
                    return MATH_CPP_DTYPE_INVALID;
            }

        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

MexprNode *
OperatorMul::clone() {

    OperatorMul *obj = new OperatorMul();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}


/* DIV operator */

OperatorDiv::OperatorDiv() {

    opid = MATH_CPP_DIV;
    name = "Div";
    is_unary = false;
}

OperatorDiv::~OperatorDiv() {

}

Dtype *
OperatorDiv::compute(Dtype *dtype1, Dtype *dtype2) {

    Dtype *res;

    mexprcpp_dtypes_t res_did = this->ResultStorageType (dtype1->did, dtype2->did);
    
    if (res_did == MATH_CPP_DTYPE_INVALID || 
         res_did == MATH_CPP_DTYPE_WILDCRAD) return NULL;    

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val /
                                                            (double)((dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val == 0) ? 1 : \
                                                            dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val );
                    res->del_after_use = true;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val /
                                                        (dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val == 0 ? 1 : \
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val );
                    res->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }
            break;


        case MATH_CPP_DOUBLE:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val /
                                                        (double)((double)dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val == 0 ? 1 : \
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val) ;
                    res->del_after_use = true;
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val /
                                                        (dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val == 0 ? 1 : \
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val);
                    res->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }
            break;            

        default:
            return NULL;

    }    
}

mexprcpp_dtypes_t
OperatorDiv::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    /* Allowed Combinations 

        int , int  => int  
        int, double => double
        double, int => double
        double, double => double
    */
    switch (did1) {

        case MATH_CPP_INT:

            switch (did2) {

                case MATH_CPP_INT:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DOUBLE:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_INT;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }

        case MATH_CPP_DOUBLE:

            switch (did2) {

                case MATH_CPP_INT:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DOUBLE:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DOUBLE;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }            


           case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_INT:
                case MATH_CPP_DOUBLE:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DOUBLE;
                case MATH_CPP_DTYPE_INVALID:
                    return MATH_CPP_DTYPE_INVALID;
            }

        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

MexprNode *
OperatorDiv::clone() {

    OperatorDiv *obj = new OperatorDiv();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}



/* EQ operator */

OperatorEq::OperatorEq() {

    opid = MATH_CPP_EQ;
    name = "=";
    is_unary = false;
}

OperatorEq::~OperatorEq() { }

mexprcpp_dtypes_t
OperatorEq::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    /* Allowed Combinations 

        int , int  => bool
        int, double => bool
        double, int => bool
        double, double => bool
        string, string => bool
    */
    switch (did1) {

        case MATH_CPP_INT:

            switch (did2) {

                case MATH_CPP_INT:
                case MATH_CPP_DOUBLE:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_BOOL;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }

        case MATH_CPP_DOUBLE:

            switch (did2) {

                case MATH_CPP_INT:
                case MATH_CPP_DOUBLE:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_BOOL;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }            


            case MATH_CPP_STRING:

            switch (did2) {

                case MATH_CPP_STRING:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_BOOL;
                default: 
                    return MATH_CPP_DTYPE_INVALID;
            }                


           case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_INT:
                case MATH_CPP_DOUBLE:
                case MATH_CPP_STRING:
                    return MATH_CPP_BOOL;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DTYPE_WILDCRAD;
                case MATH_CPP_DTYPE_INVALID:
                    return MATH_CPP_DTYPE_INVALID;
            }

        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

Dtype*
OperatorEq::compute(Dtype *dtype1, Dtype *dtype2) {

    if (this->is_optimized) {
        return this->optimized_result;
    }

    mexprcpp_dtypes_t res_did = this->ResultStorageType (dtype1->did, dtype2->did);
    
    if (res_did == MATH_CPP_DTYPE_INVALID || 
         res_did == MATH_CPP_DTYPE_WILDCRAD) {
    
        return NULL;
    }

  Dtype *res = Dtype::factory (MATH_CPP_BOOL);

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val = dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val ==
                                                        dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    res_b->del_after_use = true;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val  = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val ==
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
                     res_b->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }
            break;


        case MATH_CPP_DOUBLE:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                     res_b->dtype.b_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val ==
                                                        (double)dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                     res_b->del_after_use = true;
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val  = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val ==
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
                     res_b->del_after_use = true;
                    return res;
                }
                default:
                    return NULL;
            }
            break;            

        case MATH_CPP_STRING:

            switch (dtype2->did) {

                case MATH_CPP_STRING:
                {
                     Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                     res_b->dtype.b_val = dynamic_cast<Dtype_STRING *> (dtype1)->dtype.str_val ==
                                                        dynamic_cast<Dtype_STRING *> (dtype2)->dtype.str_val;
                     res_b->del_after_use = true;
                    return res_b;
                }
            }
            break;

        default:
            return NULL;

    }
    
    return NULL;
}

MexprNode * 
OperatorEq::clone() {

    OperatorEq *obj = new OperatorEq();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}


/* IN Operator*/

OperatorIn::OperatorIn() {

    opid = MATH_CPP_IN;
    name = "in";
    is_unary = false;
}

OperatorIn::~OperatorIn() { }

Dtype* 
OperatorIn::compute(Dtype *dtype1, Dtype *dtype2) {

    if (this->is_optimized) {
        return this->optimized_result;
    }

    assert (dtype1->did == MATH_CPP_STRING &&
        dtype2->did == MATH_CPP_STRING_LST);

    Dtype_BOOL *res = dynamic_cast <Dtype_BOOL *>( Dtype::factory (MATH_CPP_BOOL));
    res->dtype.b_val = false;
    res->del_after_use = true;
    Dtype_STRING_LST *str_lst = dynamic_cast <Dtype_STRING_LST *> (dtype2);
    Dtype_STRING *str = dynamic_cast <Dtype_STRING *> (dtype1);
    Dtype_STRING *elem;

    for (std::list<Dtype_STRING *>::iterator it = str_lst->dtype.str_lst.begin(); 
            it != str_lst->dtype.str_lst.end(); ++it) {

        elem = *it;

        if (elem->dtype.str_val == str->dtype.str_val) {
            res->dtype.b_val = true;
            return res;
        }
    }

    return res;
}

mexprcpp_dtypes_t 
OperatorIn::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    switch (did1) {

        case MATH_CPP_VARIABLE:

            switch (did2) {

                case MATH_CPP_STRING_LST:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_BOOL;
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }
            break;

        case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_STRING_LST:
                    return MATH_CPP_BOOL;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DTYPE_WILDCRAD;
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }

        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

MexprNode * 
OperatorIn::clone() {

    OperatorIn *obj = new OperatorIn();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}






/* AND Operator*/

OperatorAnd::OperatorAnd() {

    opid = MATH_CPP_AND;
    name = "and";
    is_unary = false;
}

OperatorAnd::~OperatorAnd() { }

Dtype* 
OperatorAnd::compute(Dtype *dtype1, Dtype *dtype2) {

    if (this->is_optimized) {
        return this->optimized_result;
    }

    assert (dtype1->did == MATH_CPP_BOOL &&
               dtype2->did == MATH_CPP_BOOL);

    Dtype_BOOL *res = dynamic_cast <Dtype_BOOL *>( Dtype::factory (MATH_CPP_BOOL));
    res->dtype.b_val = false;
    res->del_after_use = true;

    Dtype_BOOL *dtype1_res = dynamic_cast <Dtype_BOOL *> (dtype1);
    Dtype_BOOL *dtype2_res = dynamic_cast <Dtype_BOOL *> (dtype2);

    res->dtype.b_val = dtype1_res->dtype.b_val && dtype2_res->dtype.b_val ;

    return res;
}

mexprcpp_dtypes_t 
OperatorAnd::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    switch (did1) {

        case MATH_CPP_BOOL:

            switch (did2) {

                case MATH_CPP_BOOL:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_BOOL;
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }
            break;

        case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_BOOL:
                    return MATH_CPP_BOOL;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DTYPE_WILDCRAD;
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }

        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

MexprNode * 
OperatorAnd::clone() {

    OperatorAnd *obj = new OperatorAnd();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}



/* OR Operator*/

OperatorOr::OperatorOr() {

    opid = MATH_CPP_OPR_MAX;
    name = "or";
    is_unary = false;
}

OperatorOr::~OperatorOr() { }

Dtype* 
OperatorOr::compute(Dtype *dtype1, Dtype *dtype2) {

    if (this->is_optimized) {
        return this->optimized_result;
    }

    assert (dtype1->did == MATH_CPP_BOOL &&
               dtype2->did == MATH_CPP_BOOL);

    Dtype_BOOL *res = dynamic_cast <Dtype_BOOL *>( Dtype::factory (MATH_CPP_BOOL));
    res->dtype.b_val = false;
    res->del_after_use = true;

    Dtype_BOOL *dtype1_res = dynamic_cast <Dtype_BOOL *> (dtype1);
    Dtype_BOOL *dtype2_res = dynamic_cast <Dtype_BOOL *> (dtype2);

    res->dtype.b_val = dtype1_res->dtype.b_val || dtype2_res->dtype.b_val ;

    return res;
}

mexprcpp_dtypes_t 
OperatorOr::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    switch (did1) {

        case MATH_CPP_BOOL:

            switch (did2) {

                case MATH_CPP_BOOL:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_BOOL;
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }
            break;

        case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_BOOL:
                    return MATH_CPP_BOOL;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DTYPE_WILDCRAD;
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }

        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

MexprNode * 
OperatorOr::clone() {

    OperatorOr *obj = new OperatorOr();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}




Operator* 
Operator::factory (mexprcpp_operators_t opr_code) {

    switch (opr_code) {

        case MATH_CPP_MOD:
            return new OperatorMod();
        case MATH_CPP_PLUS:
            return new OperatorPlus();
        case MATH_CPP_MINUS:
            return new OperatorMinus();
        case MATH_CPP_MUL:
            return new OperatorMul();
        case MATH_CPP_DIV:
            return new OperatorDiv();
        case MATH_CPP_EQ:
            return new OperatorEq();
        case MATH_CPP_IN:
            return new OperatorIn();
        case MATH_CPP_OR:
            return new OperatorOr();
        case MATH_CPP_AND:
            return new OperatorAnd();
        default:
            return NULL;
    }
    return NULL;
}

