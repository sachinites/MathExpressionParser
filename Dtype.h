#ifndef __DTYPE__
#define __DTYPE__

#include <stdint.h>
#include <string>
#include "MExprcppEnums.h"

class Dtype {

protected:
    Dtype();
    virtual ~Dtype() {};

public:
    static Dtype * factory(mexprcpp_dtypes_t did);
     mexprcpp_dtypes_t did;
};


/* Dtype : Dtype_IPv4_addr*/ 

class Dtype_IPv4_addr : public Dtype {

public:
    
    struct {
        unsigned char ip_addr_str[16];
        uint32_t ipaddr_int;
    } dtype;

    Dtype_IPv4_addr();
    ~Dtype_IPv4_addr();
};


/* Dtype : Dtype_INT*/ 

class Dtype_INT : public Dtype {

public:
    
    struct {
        int int_val;
    } dtype;

    Dtype_INT();
    ~Dtype_INT();
};


/* Dtype : Dtype_DOUBLE*/ 


class Dtype_DOUBLE : public Dtype {

public:
    
    struct {
        double d_val;
    } dtype;

    Dtype_DOUBLE();
    ~Dtype_DOUBLE();
};


/* Dtype : Dtype_STRING*/
 
class Dtype_STRING : public Dtype {

public:
    
    struct {
        std::string str_val;
    } dtype;

    Dtype_STRING();
    ~Dtype_STRING();
};


#endif 