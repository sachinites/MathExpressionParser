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
};



class OperatorPlus : public Operator {

    private:

    protected:

    public:
        OperatorPlus();
     ~OperatorPlus();
     virtual MexprNode * clone() override;
};


class OperatorMinus : public Operator {

    private:

    protected:

    public:
        OperatorMinus();
     ~OperatorMinus();
     virtual MexprNode * clone() override;

};



class OperatorMul : public Operator {

    private:

    protected:

    public:
        OperatorMul();
     ~OperatorMul();
     virtual MexprNode * clone() override;

};



class OperatorDiv : public Operator {

    private:

    protected:

    public:
        OperatorDiv();
     ~OperatorDiv();
    virtual MexprNode * clone() override;
};



class OperatorEq : public Operator {

    private:

    protected:

    public:
        OperatorEq();
     ~OperatorEq();
    virtual MexprNode * clone() override;
};



class OperatorNeq : public Operator {

    private:

    protected:

    public:
        OperatorNeq();
     ~OperatorNeq();
    virtual MexprNode * clone() override;
};



class OperatorLessThan : public Operator {

    private:

    protected:

    public:
        OperatorLessThan();
     ~OperatorLessThan();
    virtual MexprNode * clone() override;
};



class OperatorGreaterThan : public Operator {

    private:

    protected:

    public:
        OperatorGreaterThan();
     ~OperatorGreaterThan();
    virtual MexprNode * clone() override;
};



class OperatorSqr : public Operator {

    private:

    protected:

    public:
        OperatorSqr();
     ~OperatorSqr();
    virtual MexprNode * clone() override;
};  



class OperatorSqrt : public Operator {

    private:

    protected:

    public:
        OperatorSqrt();
     ~OperatorSqrt();
    virtual MexprNode * clone() override;
};



class OperatorMax : public Operator {

    private:

    protected:

    public:
        OperatorMax();
     ~OperatorMax();
    virtual MexprNode * clone() override;
};


class OperatorMin : public Operator {

    private:

    protected:

    public:
        OperatorMin();
     ~OperatorMin();
    virtual MexprNode * clone() override;
};


#endif 