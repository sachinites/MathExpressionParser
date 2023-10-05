#ifndef __DTYPE__
#define __DTYPE__

#include <stdint.h>
#include <string>
#include "MexprTree.h"
#include "MExprcppEnums.h"

class Dtype : public MexprNode {

protected:
    Dtype();

public:
    bool is_resolved;
    mexprcpp_dtypes_t did;

    virtual ~Dtype();
    static Dtype * factory(mexprcpp_dtypes_t did);
    virtual Dtype *compute(Dtype *dtype1, Dtype *dtype2) = 0;
    virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) ;
    virtual MexprNode * clone() = 0;
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
    Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
    MexprNode * clone() override;
};


/* Dtype : Dtype_INT*/ 

class Dtype_INT : public Dtype {

public:
    
    struct {
        int int_val;
    } dtype;

    Dtype_INT();
    Dtype_INT(int val);
    ~Dtype_INT();
    Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
    MexprNode * clone() override;
};


/* Dtype : Dtype_DOUBLE*/ 


class Dtype_DOUBLE : public Dtype {

public:
    
    struct {
        double d_val;
    } dtype;

    Dtype_DOUBLE();
    ~Dtype_DOUBLE();
    Dtype_DOUBLE(double val);
    Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
    MexprNode * clone() override;
};


/* Dtype : Dtype_STRING*/
 
class Dtype_STRING : public Dtype {

public:
    
    struct {
        std::string str_val;
    } dtype;

    Dtype_STRING();
    ~Dtype_STRING();
    Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
    MexprNode * clone() override;
};


/* Dtype : Dtype_WILDCARD*/

class Dtype_WILDCARD : public Dtype {

    public:
        Dtype_WILDCARD();
        ~Dtype_WILDCARD();
        Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
        MexprNode * clone() override;
};




/* Dtype : Dtype_INVALID*/

class Dtype_INVALID : public Dtype {

    public:
        Dtype_INVALID();
        ~Dtype_INVALID();
        Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
        MexprNode * clone() override;
};



/* Dtype : Dtype_VARIABLE*/

class Dtype_VARIABLE : public Dtype {

    public:
        std::string variable_name;
        void *data_src;
        Dtype *(*compute_fn_ptr)(void *);
        Dtype_VARIABLE(std::string var_name);
        Dtype_VARIABLE();
        ~Dtype_VARIABLE();
        Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
        MexprNode * clone() override;
};


#endif 