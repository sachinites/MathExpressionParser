#include <string>
#include <algorithm>
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

void 
Dtype_INT::SetValue(void *value) {

    int val = atoi ((const char *)value);
    this->dtype.int_val = val;
}

void 
Dtype_INT::SetValue(Dtype *value)  {

    this->dtype.int_val = dynamic_cast <Dtype_INT *> (value)->dtype.int_val;
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

void 
Dtype_DOUBLE::SetValue(void *value) {

    double val = (double)atof ((const char *)value);
    this->dtype.d_val = val;
}

void 
Dtype_DOUBLE::SetValue(Dtype *value)  {

    this->dtype.d_val = dynamic_cast <Dtype_DOUBLE *> (value)->dtype.d_val;
}





Dtype_STRING::Dtype_STRING() {

    this->did = MATH_CPP_STRING;
}

Dtype_STRING::~Dtype_STRING() {

}


void 
Dtype_STRING::SetValue(void *value) {

     this->dtype.str_val.assign(std::string ((char *)value));

     // remove the " " on both the sides of the strings if present.
     // remove the ' ' on both the sides of the string if present.
     // because user enters string in single or double quotes. While stroing the strings, we dont store the doubl/single quotes
    // Chat GPT gave me this to remove " (double quote) or ' (single quote)
    // #include <algorithm> to use below functions
    
         this->dtype.str_val.erase(
            std::remove(this->dtype.str_val.begin(), this->dtype.str_val.end(), '\"'), 
            this->dtype.str_val.end());
        this->dtype.str_val.erase(
            std::remove(this->dtype.str_val.begin(), this->dtype.str_val.end(), '\''), 
            this->dtype.str_val.end());
}

void 
Dtype_STRING::SetValue(Dtype *value)  {

    Dtype_STRING *value_str = dynamic_cast<Dtype_STRING *> (value);
    this->SetValue ((void *)value_str->dtype.str_val.c_str()); // leverage the Ist SetValue fn
}


 Dtype * 
 Dtype::factory(mexprcpp_dtypes_t did) {

    switch (did) {

        case MATH_CPP_INT:
            return new Dtype_INT();
        case MATH_CPP_DOUBLE:
            return new Dtype_DOUBLE();
        case MATH_CPP_STRING:
            return new Dtype_STRING();
        default:
            return NULL;
    }
 }