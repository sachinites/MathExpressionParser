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
