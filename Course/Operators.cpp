#include <math.h>
#include "Operators.h"
#include "Dtype.h"

// base class
Operator::Operator () {

    this->opid = MATH_CPP_OPR_INVALID;
    this->name = "";
    this->is_unary = false;
}

Operator::~Operator () {

}



// concrete class now

 OperatorPlus:: OperatorPlus() {

    this->opid = MATH_CPP_PLUS;
    this->name = "+";
    this->is_unary = false;
 }

  OperatorPlus::~OperatorPlus()  {}


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

mexprcpp_dtypes_t 
OperatorPlus::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

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
         break;

         case MATH_CPP_DOUBLE:
         switch (did2) {

            case MATH_CPP_INT:
            case MATH_CPP_DOUBLE:
            case MATH_CPP_DTYPE_WILDCRAD:
               return MATH_CPP_DOUBLE;
            default:
               return MATH_CPP_DTYPE_INVALID;
         }
         break;

         case MATH_CPP_STRING:
         switch (did2) {

            case MATH_CPP_STRING:
            case MATH_CPP_DTYPE_WILDCRAD:
               return MATH_CPP_STRING;
            default:
               return MATH_CPP_DTYPE_INVALID;
         }
         break;

         case MATH_CPP_DTYPE_WILDCRAD:
         switch (did2) {

            case MATH_CPP_INT:
            case MATH_CPP_DOUBLE:
            case MATH_CPP_STRING:
            case MATH_CPP_DTYPE_WILDCRAD:
               return did2;
            default:
               return  MATH_CPP_DTYPE_INVALID;
         }
         break;

         default:
            return MATH_CPP_DTYPE_INVALID;
   }
}

Dtype* 
OperatorPlus::compute(Dtype *dtype1, Dtype *dtype2) {

     Dtype *res;

    // a + b
    switch (dtype1->did) {

        case MATH_CPP_INT:
        {

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_INT);
                    Dtype_INT *res_int = dynamic_cast <Dtype_INT *> (res);
                    res_int->dtype.int_val = dynamic_cast <Dtype_INT *> (dtype1)->dtype.int_val +
                                                            dynamic_cast <Dtype_INT *> (dtype2)->dtype.int_val;
                    return res;
                }

                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast <Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = (double)dynamic_cast <Dtype_INT *> (dtype1)->dtype.int_val + 
                    dynamic_cast <Dtype_DOUBLE *> (dtype2)->dtype.d_val;
                    return res;
                }

                default:
                    return NULL;

            }
        }
        break;


        case MATH_CPP_DOUBLE:
        {

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast <Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast <Dtype_DOUBLE *> (dtype1)->dtype.d_val +
                        (double)dynamic_cast <Dtype_INT *> (dtype2)->dtype.int_val ;
                    return res;
                }

                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                     Dtype_DOUBLE *res_d = dynamic_cast <Dtype_DOUBLE *> (res);
                     res_d->dtype.d_val = dynamic_cast <Dtype_DOUBLE *> (dtype1)->dtype.d_val +
                                                        dynamic_cast <Dtype_DOUBLE *> (dtype2)->dtype.d_val;
                    return res;
                }

                default:
                    return NULL;
            }
        }

        case MATH_CPP_STRING:
        {
            switch (dtype2->did)
            {
                case MATH_CPP_STRING:
                {
                    res = Dtype::factory (MATH_CPP_STRING);
                    Dtype_STRING *res_str = dynamic_cast<Dtype_STRING *> (res);
                    res_str->dtype.str_val = dynamic_cast<Dtype_STRING *>(dtype1)->dtype.str_val +
                                                            dynamic_cast<Dtype_STRING *>(dtype2)->dtype.str_val ;
                    return res;
                }
                default:
                    return NULL;
            }
        }
        break;

        default:
            return NULL;

    }
}


 OperatorMinus:: OperatorMinus() {

    this->opid = MATH_CPP_MINUS;
    this->name = "-";
    this->is_unary = false;
 }

  OperatorMinus::~OperatorMinus()  {}
  
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

mexprcpp_dtypes_t
OperatorMinus::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

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

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_INT);
                    Dtype_INT *res_int = dynamic_cast<Dtype_INT *> (res);
                    res_int->dtype.int_val = dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val -
                                                            dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val -
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val -
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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




OperatorMul:: OperatorMul() {

    this->opid = MATH_CPP_MUL;
    this->name = "*";
    this->is_unary = false;
 }

OperatorMul::~OperatorMul()  {}
  
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

Dtype *
OperatorMul::compute(Dtype *dtype1, Dtype *dtype2) {

    Dtype *res;

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    res = Dtype::factory (MATH_CPP_INT);
                    Dtype_INT *res_int = dynamic_cast<Dtype_INT *> (res);
                    res_int->dtype.int_val = dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val *
                                                            dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val *
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val *
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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



OperatorDiv:: OperatorDiv() {

    this->opid = MATH_CPP_DIV;
    this->name = "/";
    this->is_unary = false;
 }

OperatorDiv::~OperatorDiv()  {}
  
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

mexprcpp_dtypes_t
OperatorDiv::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

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

Dtype *
OperatorDiv::compute(Dtype *dtype1, Dtype *dtype2) {

    Dtype *res;

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
                    res_d->dtype.d_val = (dynamic_cast<Dtype_DOUBLE *> (dtype1))->dtype.d_val /
                                                        (double)((double)(dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val) == 0 ? 1 : \
                                                        (dynamic_cast<Dtype_INT *> (dtype2))->dtype.int_val) ;
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    res = Dtype::factory (MATH_CPP_DOUBLE);
                    Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
                    res_d->dtype.d_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val /
                                                        (dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val == 0 ? 1 : \
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val);
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


OperatorEq:: OperatorEq() {

    this->opid = MATH_CPP_EQ;
    this->name = "=";
    this->is_unary = false;
 }

OperatorEq:: ~OperatorEq() {}

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

mexprcpp_dtypes_t
OperatorEq::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

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


            case MATH_CPP_IPV4:

            switch (did2) {

                case MATH_CPP_IPV4:
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
                case MATH_CPP_IPV4:
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

  Dtype *res = Dtype::factory (MATH_CPP_BOOL);

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val = dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val ==
                                                        dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val  = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val ==
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val  = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val ==
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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
                    return res_b;
                }
            }
            break;

        default:
            return NULL;

    }
    
    return NULL;
}


OperatorNeq:: OperatorNeq() {

    this->opid = MATH_CPP_NEQ;
    this->name = "!=";
    this->is_unary = false;
 }

OperatorNeq:: ~OperatorNeq() {}

MexprNode * 
OperatorNeq::clone() {

    OperatorNeq *obj = new OperatorNeq();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t
OperatorNeq::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

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


            case MATH_CPP_IPV4:

            switch (did2) {

                case MATH_CPP_IPV4:
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
                case MATH_CPP_IPV4:
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
OperatorNeq::compute(Dtype *dtype1, Dtype *dtype2) {

  Dtype *res = Dtype::factory (MATH_CPP_BOOL);

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val = dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val !=
                                                        dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val  = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val !=
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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
                     res_b->dtype.b_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val !=
                                                        (double)dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val  = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val !=
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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
                     res_b->dtype.b_val = dynamic_cast<Dtype_STRING *> (dtype1)->dtype.str_val !=
                                                        dynamic_cast<Dtype_STRING *> (dtype2)->dtype.str_val;
                    return res_b;
                }
            }
            break;

        default:
            return NULL;

    }
    
    return NULL;
}


OperatorLessThan:: OperatorLessThan() {

    this->opid = MATH_CPP_LESS_THAN;
    this->name = "<";
    this->is_unary = false;
 }

OperatorLessThan:: ~OperatorLessThan() {}

MexprNode * 
OperatorLessThan::clone() {

    OperatorLessThan *obj = new OperatorLessThan();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t
OperatorLessThan::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

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


           case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_INT:
                case MATH_CPP_DOUBLE:
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
OperatorLessThan::compute(Dtype *dtype1, Dtype *dtype2) {

  Dtype *res = Dtype::factory (MATH_CPP_BOOL);

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val = dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val <
                                                        dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val  = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val <
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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
                     res_b->dtype.b_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val <
                                                        (double)dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val  = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val <
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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




OperatorGreaterThan:: OperatorGreaterThan() {

    this->opid = MATH_CPP_GREATER_THAN;
    this->name = ">";
    this->is_unary = false;
 }

OperatorGreaterThan:: ~OperatorGreaterThan() {}

MexprNode * 
OperatorGreaterThan::clone() {

    OperatorGreaterThan *obj = new OperatorGreaterThan();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t
OperatorGreaterThan::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

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


           case MATH_CPP_DTYPE_WILDCRAD:

            switch (did2) {

                case MATH_CPP_INT:
                case MATH_CPP_DOUBLE:
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
OperatorGreaterThan::compute(Dtype *dtype1, Dtype *dtype2) {

  Dtype *res = Dtype::factory (MATH_CPP_BOOL);

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val = dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val >
                                                        dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val  = (double)dynamic_cast<Dtype_INT *> (dtype1)->dtype.int_val >
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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
                     res_b->dtype.b_val = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val >
                                                        (double)dynamic_cast<Dtype_INT *> (dtype2)->dtype.int_val;
                    return res;                
                }
                case MATH_CPP_DOUBLE:
                {
                    Dtype_BOOL *res_b = dynamic_cast<Dtype_BOOL *> (res);
                    res_b->dtype.b_val  = dynamic_cast<Dtype_DOUBLE *> (dtype1)->dtype.d_val >
                                                        dynamic_cast<Dtype_DOUBLE *> (dtype2)->dtype.d_val;
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




OperatorSqr:: OperatorSqr() {

    this->opid = MATH_CPP_SQR;
    this->name = "sqr";
    this->is_unary = true;
 }

OperatorSqr:: ~OperatorSqr() {}

MexprNode * 
OperatorSqr::clone() {

    OperatorSqr *obj = new OperatorSqr();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t
OperatorSqr::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    switch (did1) {

        case MATH_CPP_INT:
        case MATH_CPP_DOUBLE:
        case MATH_CPP_DTYPE_WILDCRAD:
            return did1;
        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

Dtype *
OperatorSqr::compute(Dtype *dtype1, Dtype *dtype2) {

    Dtype *res;

    switch (dtype1->did) {

        case MATH_CPP_INT:
        {
            Dtype_INT *dtype1_int = dynamic_cast <Dtype_INT *> (dtype1);
            res = new Dtype_INT (dtype1_int->dtype.int_val * dtype1_int->dtype.int_val);
            return res;
        }
        break;

        case MATH_CPP_DOUBLE:
        {
             Dtype_DOUBLE *dtype1_d = dynamic_cast <Dtype_DOUBLE *> (dtype1);
             res = new Dtype_DOUBLE (dtype1_d->dtype.d_val * dtype1_d->dtype.d_val);
             return res;
        }
        break;

        default:
            return NULL;
    }
}



OperatorSqrt:: OperatorSqrt() {

    this->opid = MATH_CPP_SQRT;
    this->name = "sqrt";
    this->is_unary = true;
 }

OperatorSqrt:: ~OperatorSqrt() {}

MexprNode * 
OperatorSqrt::clone() {

    OperatorSqrt *obj = new OperatorSqrt();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t
OperatorSqrt::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    switch (did1) {

        case MATH_CPP_INT:
        case MATH_CPP_DOUBLE:
            return MATH_CPP_DOUBLE;
        case MATH_CPP_DTYPE_WILDCRAD:
            return did1;
        default:
            return MATH_CPP_DTYPE_INVALID;
    }
}

Dtype *
OperatorSqrt::compute(Dtype *dtype1, Dtype *dtype2) {

    Dtype *res;

    switch (dtype1->did) {

        case MATH_CPP_INT:
        {
            Dtype_INT *dtype1_int = dynamic_cast <Dtype_INT *> (dtype1);
            res = new Dtype_DOUBLE (sqrt (dtype1_int->dtype.int_val));
            return res;
        }
        break;

        case MATH_CPP_DOUBLE:
        {
             Dtype_DOUBLE *dtype1_d = dynamic_cast <Dtype_DOUBLE *> (dtype1);
             res = new Dtype_DOUBLE (sqrt (dtype1_d->dtype.d_val));
             return res;
        }
        break;

        default:
            return NULL;
    }
}




OperatorMax:: OperatorMax() {

    this->opid = MATH_CPP_MAX;
    this->name = "max";
    this->is_unary = false;
 }

OperatorMax:: ~OperatorMax() {}

MexprNode * 
OperatorMax::clone() {

    OperatorMax *obj = new OperatorMax();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t 
OperatorMax::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    switch (did1) {


        case MATH_CPP_INT:
        {
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
        }
        break; 


        case MATH_CPP_DOUBLE:
        {

            switch (did2) {

                    case MATH_CPP_INT:
                    case MATH_CPP_DOUBLE:
                        return MATH_CPP_DOUBLE;
                    case MATH_CPP_DTYPE_WILDCRAD:
                        return MATH_CPP_DOUBLE;
                    default:
                         return MATH_CPP_DTYPE_INVALID;
            }
        }
        break;


        case MATH_CPP_STRING:
        {
            switch (did2) {

                case MATH_CPP_STRING:
                    return MATH_CPP_STRING;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_STRING;
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }
        }
        break;

        case MATH_CPP_DTYPE_WILDCRAD:
        {
            switch(did2) {

                case MATH_CPP_INT:
                case  MATH_CPP_DOUBLE:
                case MATH_CPP_STRING:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return did2;
            }
        }

    }

    return MATH_CPP_DTYPE_INVALID;
}

Dtype* 
OperatorMax::compute(Dtype *dtype1, Dtype *dtype2) {

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    Dtype_INT *Dtype_dtyp1_int = dynamic_cast<Dtype_INT *>(dtype1);
                    Dtype_INT *Dtype_dtyp2_int = dynamic_cast<Dtype_INT *>(dtype2);
                    int max =  Dtype_dtyp1_int->dtype.int_val < Dtype_dtyp2_int->dtype.int_val ? \
                                      Dtype_dtyp2_int->dtype.int_val : \
                                      Dtype_dtyp1_int->dtype.int_val;
                    Dtype_INT *res = dynamic_cast<Dtype_INT *> (Dtype::factory (MATH_CPP_INT));
                    res->dtype.int_val = max;
                    return res;
                }
                break;

                case MATH_CPP_DOUBLE:
                {
                    Dtype_INT *Dtype_dtyp1_int = dynamic_cast<Dtype_INT *>(dtype1);
                    Dtype_DOUBLE *Dtype_dtyp2_d = dynamic_cast<Dtype_DOUBLE *>(dtype2);
                    double max =  (double)Dtype_dtyp1_int->dtype.int_val < Dtype_dtyp2_d->dtype.d_val ? \
                                      Dtype_dtyp2_d->dtype.d_val : \
                                      (double)Dtype_dtyp1_int->dtype.int_val;
                    Dtype_DOUBLE *res = dynamic_cast<Dtype_DOUBLE *> (Dtype::factory (MATH_CPP_DOUBLE));
                    res->dtype.d_val = max;
                    return res;                    
                }
                break;

                default:
                    return NULL;
            } 
        break;

        case MATH_CPP_DOUBLE:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    Dtype_DOUBLE *Dtype_dtyp1_d = dynamic_cast<Dtype_DOUBLE *>(dtype1);
                    Dtype_INT *Dtype_dtyp2_int = dynamic_cast<Dtype_INT *>(dtype2);
                    double max =  Dtype_dtyp1_d->dtype.d_val < (double)Dtype_dtyp2_int->dtype.int_val ? \
                                             (double)Dtype_dtyp2_int->dtype.int_val : \
                                              Dtype_dtyp1_d->dtype.d_val;
                    Dtype_DOUBLE *res = dynamic_cast<Dtype_DOUBLE *> (Dtype::factory (MATH_CPP_DOUBLE));
                    res->dtype.d_val = max;
                    return res;
                }
                break;


                case MATH_CPP_DOUBLE:
                {
                    Dtype_DOUBLE *Dtype_dtyp1_d = dynamic_cast<Dtype_DOUBLE *>(dtype1);
                    Dtype_DOUBLE *Dtype_dtyp2_d = dynamic_cast<Dtype_DOUBLE *>(dtype2);
                    double max =  Dtype_dtyp1_d->dtype.d_val < Dtype_dtyp2_d->dtype.d_val ? \
                                            Dtype_dtyp2_d->dtype.d_val : \
                                            Dtype_dtyp1_d->dtype.d_val;
                    Dtype_DOUBLE *res = dynamic_cast<Dtype_DOUBLE *> (Dtype::factory (MATH_CPP_DOUBLE));
                    res->dtype.d_val = max;
                    return res;                    
                }
                break;

                default:
                    return NULL;
            } 
        break;

        case MATH_CPP_STRING:

            switch (dtype2->did) {

                case MATH_CPP_STRING:
                {
                    Dtype_STRING *Dtype_dtyp1_str = dynamic_cast<Dtype_STRING *>(dtype1);
                    Dtype_STRING *Dtype_dtyp2_str = dynamic_cast<Dtype_STRING *>(dtype2);                    
                    Dtype_STRING *res = dynamic_cast<Dtype_STRING *> (Dtype::factory (MATH_CPP_STRING));
                    res->dtype.str_val = Dtype_dtyp1_str->dtype.str_val.length() < Dtype_dtyp2_str->dtype.str_val.length() ?   \
                                                        Dtype_dtyp2_str->dtype.str_val :    \
                                                        Dtype_dtyp1_str->dtype.str_val;
                    return res;
                }
                break;
            }
        break;

        default:
            return NULL;
    }

    return NULL;
}






OperatorMin:: OperatorMin() {

    this->opid = MATH_CPP_MIN;
    this->name = "min";
    this->is_unary = false;
 }

OperatorMin:: ~OperatorMin() {}

MexprNode * 
OperatorMin::clone() {

    OperatorMin *obj = new OperatorMin();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

mexprcpp_dtypes_t 
OperatorMin::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    switch (did1) {


        case MATH_CPP_INT:
        {
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
        }
        break; 


        case MATH_CPP_DOUBLE:
        {

            switch (did2) {

                    case MATH_CPP_INT:
                    case MATH_CPP_DOUBLE:
                        return MATH_CPP_DOUBLE;
                    case MATH_CPP_DTYPE_WILDCRAD:
                        return MATH_CPP_DOUBLE;
                    default:
                         return MATH_CPP_DTYPE_INVALID;
            }
        }
        break;


        case MATH_CPP_STRING:
        {
            switch (did2) {

                case MATH_CPP_STRING:
                    return MATH_CPP_STRING;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_STRING;
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }
        }
        break;

        case MATH_CPP_DTYPE_WILDCRAD:
        {
            switch(did2) {

                case MATH_CPP_INT:
                case  MATH_CPP_DOUBLE:
                case MATH_CPP_STRING:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return did2;
            }
        }

    }

    return MATH_CPP_DTYPE_INVALID;
}

Dtype* 
OperatorMin::compute(Dtype *dtype1, Dtype *dtype2) {

    switch (dtype1->did) {

        case MATH_CPP_INT:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    Dtype_INT *Dtype_dtyp1_int = dynamic_cast<Dtype_INT *>(dtype1);
                    Dtype_INT *Dtype_dtyp2_int = dynamic_cast<Dtype_INT *>(dtype2);
                    int min =  Dtype_dtyp1_int->dtype.int_val > Dtype_dtyp2_int->dtype.int_val ? \
                                      Dtype_dtyp2_int->dtype.int_val : \
                                      Dtype_dtyp1_int->dtype.int_val;
                    Dtype_INT *res = dynamic_cast<Dtype_INT *> (Dtype::factory (MATH_CPP_INT));
                    res->dtype.int_val = min;
                    return res;
                }
                break;


                case MATH_CPP_DOUBLE:
                {
                    Dtype_INT *Dtype_dtyp1_int = dynamic_cast<Dtype_INT *>(dtype1);
                    Dtype_DOUBLE *Dtype_dtyp2_d = dynamic_cast<Dtype_DOUBLE *>(dtype2);
                    double min =  (double)Dtype_dtyp1_int->dtype.int_val > Dtype_dtyp2_d->dtype.d_val ? \
                                      Dtype_dtyp2_d->dtype.d_val : \
                                      (double)Dtype_dtyp1_int->dtype.int_val;
                    Dtype_DOUBLE *res = dynamic_cast<Dtype_DOUBLE *> (Dtype::factory (MATH_CPP_DOUBLE));
                    res->dtype.d_val = min;
                    return res;                    
                }
                break;

                default:
                    return NULL;
            } 
        break;



        case MATH_CPP_DOUBLE:

            switch (dtype2->did) {

                case MATH_CPP_INT:
                {
                    Dtype_DOUBLE *Dtype_dtyp1_d = dynamic_cast<Dtype_DOUBLE *>(dtype1);
                    Dtype_INT *Dtype_dtyp2_int = dynamic_cast<Dtype_INT *>(dtype2);
                    double min =  Dtype_dtyp1_d->dtype.d_val > (double)Dtype_dtyp2_int->dtype.int_val ? \
                                             (double)Dtype_dtyp2_int->dtype.int_val : \
                                              Dtype_dtyp1_d->dtype.d_val;
                    Dtype_DOUBLE *res = dynamic_cast<Dtype_DOUBLE *> (Dtype::factory (MATH_CPP_DOUBLE));
                    res->dtype.d_val = min;
                    return res;
                }
                break;


                case MATH_CPP_DOUBLE:
                {
                    Dtype_DOUBLE *Dtype_dtyp1_d = dynamic_cast<Dtype_DOUBLE *>(dtype1);
                    Dtype_DOUBLE *Dtype_dtyp2_d = dynamic_cast<Dtype_DOUBLE *>(dtype2);
                    double min =  Dtype_dtyp1_d->dtype.d_val > Dtype_dtyp2_d->dtype.d_val ? \
                                            Dtype_dtyp2_d->dtype.d_val : \
                                            Dtype_dtyp1_d->dtype.d_val;
                    Dtype_DOUBLE *res = dynamic_cast<Dtype_DOUBLE *> (Dtype::factory (MATH_CPP_DOUBLE));
                    res->dtype.d_val = min;
                    return res;                    
                }
                break;

                default:
                    return NULL;
            } 
        break;


        case MATH_CPP_STRING:

            switch (dtype2->did) {

                case MATH_CPP_STRING:
                {
                    Dtype_STRING *Dtype_dtyp1_str = dynamic_cast<Dtype_STRING *>(dtype1);
                    Dtype_STRING *Dtype_dtyp2_str = dynamic_cast<Dtype_STRING *>(dtype2);                    
                    Dtype_STRING *res = dynamic_cast<Dtype_STRING *> (Dtype::factory (MATH_CPP_STRING));
                    res->dtype.str_val = Dtype_dtyp1_str->dtype.str_val.length() > Dtype_dtyp2_str->dtype.str_val.length() ?   \
                                                        Dtype_dtyp2_str->dtype.str_val :    \
                                                        Dtype_dtyp1_str->dtype.str_val;
                    return res;
                }
                break;
            }
        break;

        default:
            return NULL;

    }

    return NULL;
}


/* AND Operator*/

OperatorAnd::OperatorAnd() {

    opid = MATH_CPP_AND;
    name = "and";
    is_unary = false;
}

OperatorAnd::~OperatorAnd() { }


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

mexprcpp_dtypes_t 
 OperatorAnd::ResultStorageType(
        mexprcpp_dtypes_t did1, 
        mexprcpp_dtypes_t did2) {

    switch (did1) {

        case MATH_CPP_BOOL:

            switch(did2) {

                case MATH_CPP_BOOL:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_BOOL;
                case MATH_CPP_DTYPE_INVALID:
                    return MATH_CPP_DTYPE_INVALID;
            }

        case MATH_CPP_DTYPE_WILDCRAD:

            switch(did2) {

                case MATH_CPP_BOOL:
                    return MATH_CPP_BOOL;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DTYPE_WILDCRAD;
                case MATH_CPP_DTYPE_INVALID:
                    return MATH_CPP_DTYPE_INVALID;
            }

        return MATH_CPP_DTYPE_INVALID;
    }

    return MATH_CPP_DTYPE_INVALID;
}

Dtype* 
OperatorAnd::compute(Dtype *dtype1, Dtype *dtype2) {

    assert (dtype1->did == MATH_CPP_BOOL &&
               dtype2->did == MATH_CPP_BOOL);

    Dtype_BOOL *res = dynamic_cast<Dtype_BOOL *> (Dtype::factory(MATH_CPP_BOOL));
    res->dtype.b_val = false;

    Dtype_BOOL *dtype1_res = dynamic_cast <Dtype_BOOL *> (dtype1);
    Dtype_BOOL *dtype2_res = dynamic_cast <Dtype_BOOL *> (dtype2);

    res->dtype.b_val = dtype1_res->dtype.b_val && dtype2_res->dtype.b_val ;
    return res;
}


/* OR Operator*/

OperatorOr::OperatorOr() {

    opid = MATH_CPP_OR;
    name = "or";
    is_unary = false;
}

OperatorOr::~OperatorOr() { }


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

mexprcpp_dtypes_t 
 OperatorOr::ResultStorageType(
        mexprcpp_dtypes_t did1, 
        mexprcpp_dtypes_t did2) {

    switch (did1) {

        case MATH_CPP_BOOL:

            switch(did2) {

                case MATH_CPP_BOOL:
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_BOOL;
                case MATH_CPP_DTYPE_INVALID:
                    return MATH_CPP_DTYPE_INVALID;
            }

        case MATH_CPP_DTYPE_WILDCRAD:

            switch(did2) {

                case MATH_CPP_BOOL:
                    return MATH_CPP_BOOL;
                case MATH_CPP_DTYPE_WILDCRAD:
                    return MATH_CPP_DTYPE_WILDCRAD;
                case MATH_CPP_DTYPE_INVALID:
                    return MATH_CPP_DTYPE_INVALID;
            }

        return MATH_CPP_DTYPE_INVALID;
    }
    return MATH_CPP_DTYPE_INVALID;
}

Dtype* 
OperatorOr::compute(Dtype *dtype1, Dtype *dtype2) {

    assert (dtype1->did == MATH_CPP_BOOL &&
               dtype2->did == MATH_CPP_BOOL);

    Dtype_BOOL *res = dynamic_cast<Dtype_BOOL *> (Dtype::factory(MATH_CPP_BOOL));
    res->dtype.b_val = false;

    Dtype_BOOL *dtype1_res = dynamic_cast <Dtype_BOOL *> (dtype1);
    Dtype_BOOL *dtype2_res = dynamic_cast <Dtype_BOOL *> (dtype2);

    res->dtype.b_val = dtype1_res->dtype.b_val || dtype2_res->dtype.b_val ;
    return res;
}


Operator* 
Operator::factory (mexprcpp_operators_t opr_code) {

    switch (opr_code) {

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
        case MATH_CPP_NEQ:
            return new OperatorNeq();
        case MATH_CPP_LESS_THAN:
            return new OperatorLessThan();
        case MATH_CPP_GREATER_THAN:
            return new OperatorGreaterThan();
        case MATH_CPP_SQR:
            return new OperatorSqr();
        case MATH_CPP_SQRT:
            return new OperatorSqrt();           
        case MATH_CPP_MAX:
            return new OperatorMax();
        case MATH_CPP_MIN:
            return new OperatorMin(); 
        case MATH_CPP_AND:
            return new OperatorAnd();
        case MATH_CPP_OR:
            return new OperatorOr();            
        default:
            return NULL;
    }
    return NULL;
}
