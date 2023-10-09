#ifndef __DTYPE__
#define __DTYPE__

#include <stdint.h>
#include <string>
#include <list>
#include "MexprTree.h"
#include "MExprcppEnums.h"

class Dtype : public MexprNode {

protected:
    Dtype();

public:
    bool is_resolved;
    mexprcpp_dtypes_t did;
    bool del_after_use;
    
    virtual ~Dtype();
    static Dtype * factory(mexprcpp_dtypes_t did);
    virtual Dtype *compute(Dtype *dtype1, Dtype *dtype2) = 0;
    virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) ;
    virtual MexprNode * clone() = 0;
    virtual void SetValue(void *value) = 0;
};


/* Dtype : Dtype_IPv4_addr*/ 

class Dtype_IPv4_addr : public Dtype {

public:
    
    struct {
        std::string ip_addr_str;
        uint32_t ipaddr_int;
    } dtype;

    Dtype_IPv4_addr();
    ~Dtype_IPv4_addr();
    Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
    MexprNode * clone() override;
    void SetValue(void *value) override;
    mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
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
    void SetValue(void *value) override;
    mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
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
    void SetValue(void *value) override;
    mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
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
    void SetValue(void *value) override;
    void SetValue(std::string *string_ptr);
    mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
};


/* Dtype : Dtype_WILDCARD*/

class Dtype_WILDCARD : public Dtype {

    public:
        Dtype_WILDCARD();
        ~Dtype_WILDCARD();
        Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
        MexprNode * clone() override;
        void SetValue(void *value) override;
        mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
};



/* Dtype : Dtype_BOOL*/

class Dtype_BOOL : public Dtype {

    public:

        struct {
            bool b_val;
        } dtype;

        Dtype_BOOL();
        ~Dtype_BOOL();
        Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
        MexprNode * clone() override;
        void SetValue(void *value) override;
        mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
};




/* Dtype : Dtype_INVALID*/

class Dtype_INVALID : public Dtype {

    public:
        Dtype_INVALID();
        ~Dtype_INVALID();
        Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
        MexprNode * clone() override;
        void SetValue(void *value) override;
        mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
};



/* Dtype : Dtype_VARIABLE*/

class Dtype_VARIABLE : public Dtype {

    public:
        struct {
            std::string variable_name;
        } dtype;
        void *data_src;
        Dtype *(*compute_fn_ptr)(void *);
        mexprcpp_dtypes_t resolved_did;

        Dtype_VARIABLE(std::string var_name);
        Dtype_VARIABLE();
        ~Dtype_VARIABLE();
        Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
        MexprNode * clone() override;
        void  InstallOperandProperties (
                mexprcpp_dtypes_t resolved_did,
                void *data_src,
                Dtype *(*compute_fn_ptr)(void *)) ;

        void SetValue(void *value) override;
        mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
};


/* Dtype : Dtype_STRING_LST*/

class Dtype_STRING_LST : public Dtype {

    public:

        struct {
            std::list<Dtype_STRING *> str_lst;
        } dtype;
        
        Dtype_STRING_LST();
        ~Dtype_STRING_LST();
        Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
        MexprNode * clone() override;
        void SetValue(void *value) override;
        mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
};

#endif 