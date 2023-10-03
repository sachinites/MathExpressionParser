#include <cstddef>
#include <assert.h>
#include "Dtype.h"

Dtype_INT::Dtype_INT() {

    did = MATH_CPP_INT;
}

Dtype_INT::~Dtype_INT() {

}



Dtype_DOUBLE::Dtype_DOUBLE() {

    did = MATH_CPP_DOUBLE;
}

Dtype_DOUBLE::~Dtype_DOUBLE() {

}



Dtype_STRING::Dtype_STRING() {

    did = MATH_CPP_STRING;
}

Dtype_STRING::~Dtype_STRING() {

}



Dtype_IPv4_addr::Dtype_IPv4_addr() {

    did = MATH_CPP_IPV4;
}

Dtype_IPv4_addr::~Dtype_IPv4_addr() {

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
        case MATH_CPP_DTYPE_MAX:
            return NULL;
    }
    return NULL;
}