#ifndef __OPERATORS__
#define __OPERATORS__

#include <stdbool.h>
#include "MExprcppEnums.h"

class Dtype;

class Operator {

private:

public:
    int opid;
    std::string name;
    bool is_unary;
   virtual Dtype *compute(Dtype *dtype1, Dtype *dtype2) = 0;
   virtual Operator *GetInstance () = 0;
   virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) = 0;
   virtual ~Operator() {};
};

/* MOD operator */

class OperatorMod : public Operator {

private:
    static OperatorMod *instance;
     OperatorMod();
     

public:
    ~OperatorMod();
    Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
    Operator *GetInstance () override;
    mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
};


/* PLUS operator */

class OperatorPlus : public Operator {

private:
    static OperatorPlus *instance;
     OperatorPlus();
     

public:
    ~OperatorPlus();
    Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
    Operator *GetInstance () override;
    mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
};



/* MINUS operator */

class OperatorMinus : public Operator {

private:
    static OperatorMinus *instance;
     OperatorMinus();
     

public:
    ~OperatorMinus();
    Dtype *compute(Dtype *dtype1, Dtype *dtype2) override;
    Operator *GetInstance () override;
    mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
};


#endif 