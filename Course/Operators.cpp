#include "Operators.h"

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
               return did2;
            default:
               return  MATH_CPP_DTYPE_INVALID;
         }
         break;

         default:
            return MATH_CPP_DTYPE_INVALID;
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
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }
        }
        break;

    }

    return MATH_CPP_DTYPE_INVALID;
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
                default:
                    return MATH_CPP_DTYPE_INVALID;
            }
        }
        break;

    }

    return MATH_CPP_DTYPE_INVALID;
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
        default:
            return NULL;
    }
    return NULL;
}
