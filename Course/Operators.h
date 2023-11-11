#ifndef __OPERATORS__
#define __OPERATORS__

#include <stdbool.h>
#include <string>
#include "MexprTree.h"
#include "MexprcppEnums.h"


class Operator : public MexprNode {

    private:


    protected:
    Operator();
    virtual ~Operator();

    public:
        int opid;
        std::string name; // operator nname, for example "+"
        bool is_unary;
        static Operator* factory (mexprcpp_operators_t opr_code);
        virtual MexprNode * clone() = 0;
        virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) = 0;
        virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) = 0;
};



class OperatorPlus : public Operator {

    private:

    protected:

    public:
        OperatorPlus();
     ~OperatorPlus();
     virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};


class OperatorMinus : public Operator {

    private:

    protected:

    public:
        OperatorMinus();
     ~OperatorMinus();
     virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;

};



class OperatorMul : public Operator {

    private:

    protected:

    public:
        OperatorMul();
     ~OperatorMul();
     virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;

};



class OperatorDiv : public Operator {

    private:

    protected:

    public:
        OperatorDiv();
     ~OperatorDiv();
    virtual MexprNode * clone() override;
    virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
    virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};



class OperatorEq : public Operator {

    private:

    protected:

    public:
        OperatorEq();
     ~OperatorEq();
    virtual MexprNode * clone() override;
    virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1,mexprcpp_dtypes_t did2) override;
    virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};



class OperatorNeq : public Operator {

    private:

    protected:

    public:
        OperatorNeq();
     ~OperatorNeq();
    virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;    
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};



class OperatorLessThan : public Operator {

    private:

    protected:

    public:
        OperatorLessThan();
     ~OperatorLessThan();
    virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;    
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};



class OperatorGreaterThan : public Operator {

    private:

    protected:

    public:
        OperatorGreaterThan();
     ~OperatorGreaterThan();
    virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;    
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};



class OperatorSqr : public Operator {

    private:

    protected:

    public:
        OperatorSqr();
     ~OperatorSqr();
    virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;    
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};  



class OperatorSqrt : public Operator {

    private:

    protected:

    public:
        OperatorSqrt();
     ~OperatorSqrt();
    virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;    
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};



class OperatorMax : public Operator {

    private:

    protected:

    public:
        OperatorMax();
     ~OperatorMax();
    virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;    
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};


class OperatorMin : public Operator {

    private:

    protected:

    public:
        OperatorMin();
     ~OperatorMin();
    virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;    
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};




class OperatorAnd : public Operator {

    private:

    protected:

    public:
        OperatorAnd();
     ~OperatorAnd();
    virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;    
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};


class OperatorOr : public Operator {

    private:

    protected:

    public:
        OperatorOr();
     ~OperatorOr();
    virtual MexprNode * clone() override;
     virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;    
     virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};


#endif 