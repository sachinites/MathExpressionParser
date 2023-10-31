#include "Dtype.h"

Dtype::Dtype() {

    did = MATH_CPP_DTYPE_INVALID;
}

Dtype::~Dtype() {

}


/* Concrete class now*/

Dtype_INT::Dtype_INT() {

    this->did = MATH_CPP_INT;
     this->dtype.int_val = 0;
}

Dtype_INT::Dtype_INT(int val) {

    this->did = MATH_CPP_INT;
    this->dtype.int_val = val;
}

Dtype_INT::~Dtype_INT() {

}



Dtype_DOUBLE::Dtype_DOUBLE() {

    this->did = MATH_CPP_DOUBLE;
     this->dtype.d_val = 0;
}

Dtype_DOUBLE::Dtype_DOUBLE(double val) {

    this->did = MATH_CPP_DOUBLE;
    this->dtype.d_val = val;
}

Dtype_DOUBLE::~Dtype_DOUBLE() {

}






Dtype_STRING::Dtype_STRING() {

    this->did = MATH_CPP_STRING;
}

Dtype_STRING::~Dtype_STRING() {

}




