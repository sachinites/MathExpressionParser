#include <cstddef>
#include <assert.h>
#include "Dtype.h"

class MexprNode;

Dtype::Dtype() {} 

Dtype::~Dtype() {}


/* Dtype_INT */

Dtype_INT::Dtype_INT() {

    did = MATH_CPP_INT;
}

Dtype_INT::~Dtype_INT() {

}

mexprcpp_dtypes_t 
Dtype::ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) {

    return this->did;
}

 Dtype_INT::Dtype_INT(int val) {

        this->did = MATH_CPP_INT;
        this->dtype.int_val = val;
        this->is_resolved = true;
 }

Dtype *
Dtype_INT::compute(Dtype *dtype1, Dtype *dtype2) {

        Dtype *cpy = new Dtype_INT();
        Dtype_INT *cpy_int = dynamic_cast <Dtype_INT *>(cpy);
        *cpy_int = *this;
        return cpy;
}

MexprNode * 
Dtype_INT::clone() {

    Dtype_INT *obj = new Dtype_INT();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}




/* Dtype_DOUBLE */

Dtype_DOUBLE::Dtype_DOUBLE() {

    did = MATH_CPP_DOUBLE;
}

 Dtype_DOUBLE::Dtype_DOUBLE(double val) {

        this->did = MATH_CPP_DOUBLE;
        this->dtype.d_val = val;
        this->is_resolved = true;
 }


Dtype_DOUBLE::~Dtype_DOUBLE() {

}

Dtype *
Dtype_DOUBLE::compute(Dtype *dtype1, Dtype *dtype2) {

        Dtype *cpy = new Dtype_DOUBLE();
        Dtype_DOUBLE *cpy_d = dynamic_cast <Dtype_DOUBLE*>(cpy);
        *cpy_d = *this;
        return cpy;
}

MexprNode * 
Dtype_DOUBLE::clone() {

    Dtype_DOUBLE *obj = new Dtype_DOUBLE();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}




/* Dtype_STRING */

Dtype_STRING::Dtype_STRING() {

    did = MATH_CPP_STRING;
}

Dtype_STRING::~Dtype_STRING() {

}

Dtype *
Dtype_STRING::compute(Dtype *dtype1, Dtype *dtype2) {

        Dtype *cpy = new Dtype_STRING();
        Dtype_STRING *cpy_str = dynamic_cast <Dtype_STRING*>(cpy);
        *cpy_str = *this;
        return cpy;
}

MexprNode * 
Dtype_STRING::clone() {

    Dtype_STRING *obj = new Dtype_STRING();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}




/* Dtype : Dtype_IPv4_addr */

Dtype_IPv4_addr::Dtype_IPv4_addr() {

    did = MATH_CPP_IPV4;
}

Dtype_IPv4_addr::~Dtype_IPv4_addr() {

}

Dtype *
Dtype_IPv4_addr::compute(Dtype *dtype1, Dtype *dtype2) {

        Dtype *cpy = new Dtype_IPv4_addr();
        Dtype_IPv4_addr *cpy_ipv4 = dynamic_cast <Dtype_IPv4_addr*>(cpy);
        *cpy_ipv4 = *this;
        return cpy;
}

MexprNode * 
Dtype_IPv4_addr::clone() {

    Dtype_IPv4_addr *obj = new Dtype_IPv4_addr();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}


/* Dtype : Dtype_BOOL */

Dtype_BOOL::Dtype_BOOL () {

    did = MATH_CPP_BOOL;
}

Dtype_BOOL::~Dtype_BOOL() {

}

Dtype *
Dtype_BOOL::compute(Dtype *dtype1, Dtype *dtype2) {

    Dtype *cpy = new Dtype_BOOL();
    Dtype_BOOL *cpy_bool = dynamic_cast<Dtype_BOOL *>(cpy);
    *cpy_bool = *this;
    return cpy;
}

MexprNode * 
Dtype_BOOL::clone() {

    Dtype_BOOL *obj = new Dtype_BOOL();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}






/* Dtype : Dtype_WILDCARD */

Dtype_WILDCARD::Dtype_WILDCARD() {

    did = MATH_CPP_DTYPE_WILDCRAD;
}

Dtype_WILDCARD::~Dtype_WILDCARD() {

}

Dtype *
Dtype_WILDCARD::compute(Dtype *dtype1, Dtype *dtype2) {

        Dtype *cpy = new Dtype_WILDCARD();
        Dtype_WILDCARD *cpy_wd = dynamic_cast <Dtype_WILDCARD*>(cpy);
        *cpy_wd = *this;
        return cpy;
}

MexprNode * 
Dtype_WILDCARD::clone() {

    Dtype_WILDCARD *obj = new Dtype_WILDCARD();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}





/* Dtype : Dtype_INVALID */

Dtype_INVALID::Dtype_INVALID() {

    did = MATH_CPP_DTYPE_INVALID;
}

Dtype_INVALID::~Dtype_INVALID() {

}

Dtype *
Dtype_INVALID::compute(Dtype *dtype1, Dtype *dtype2) {

    return NULL;
}

MexprNode * 
Dtype_INVALID::clone() {

    Dtype_INVALID *obj = new Dtype_INVALID();
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}



/* Dtype : Dtype_VARIABLE*/

Dtype_VARIABLE::Dtype_VARIABLE(std::string var_name) {

    did = MATH_CPP_VARIABLE;
    this->variable_name = var_name;
}

Dtype_VARIABLE::Dtype_VARIABLE() {

    did = MATH_CPP_VARIABLE;
}

Dtype_VARIABLE::~Dtype_VARIABLE() {

}

Dtype *
Dtype_VARIABLE::compute(Dtype *dtype1, Dtype *dtype2) {

   if (!this->is_resolved)  return NULL;
    Dtype *res =  this->compute_fn_ptr(this->data_src);
    return res;
}

MexprNode * 
Dtype_VARIABLE::clone() {

    Dtype_VARIABLE *obj = new Dtype_VARIABLE(obj->variable_name);
    *obj = *this;
    obj->parent = NULL;
    obj->left = NULL;
    obj->right = NULL;
    obj->lst_left = NULL;
    obj->lst_right = NULL;
    return obj;
}

void  
Dtype_VARIABLE::InstallOperandProperties (
                void *data_src,
                Dtype *(*compute_fn_ptr)(void *))  {

    assert (!this->is_resolved);
    this->data_src = data_src;
    this->compute_fn_ptr = compute_fn_ptr;
    this->is_resolved = true;
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
        case MATH_CPP_IPV4:
            return new Dtype_IPv4_addr();
        case MATH_CPP_VARIABLE:
            return new Dtype_VARIABLE();
        case MATH_CPP_DTYPE_WILDCRAD:
            return new Dtype_WILDCARD();
        case MATH_CPP_DTYPE_INVALID:
            return new Dtype_INVALID();
        case MATH_CPP_DTYPE_MAX:
            return NULL;
    }
    return NULL;
}