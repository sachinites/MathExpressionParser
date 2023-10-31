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
};



class OperatorPlus : public Operator {

    private:

    protected:

    public:
        OperatorPlus();
     ~OperatorPlus();

};


class OperatorMinus : public Operator {

    private:

    protected:

    public:
        OperatorMinus();
     ~OperatorMinus();

};



class OperatorMul : public Operator {

    private:

    protected:

    public:
        OperatorMul();
     ~OperatorMul();

};



class OperatorDiv : public Operator {

    private:

    protected:

    public:
        OperatorDiv();
     ~OperatorDiv();

};



class OperatorEq : public Operator {

    private:

    protected:

    public:
        OperatorEq();
     ~OperatorEq();

};



class OperatorNeq : public Operator {

    private:

    protected:

    public:
        OperatorNeq();
     ~OperatorNeq();

};



class OperatorLessThan : public Operator {

    private:

    protected:

    public:
        OperatorLessThan();
     ~OperatorLessThan();

};



class OperatorGreaterThan : public Operator {

    private:

    protected:

    public:
        OperatorGreaterThan();
     ~OperatorGreaterThan();

};



class OperatorSqr : public Operator {

    private:

    protected:

    public:
        OperatorSqr();
     ~OperatorSqr();

};



class OperatorSqrt : public Operator {

    private:

    protected:

    public:
        OperatorSqrt();
     ~OperatorSqrt();

};



class OperatorMax : public Operator {

    private:

    protected:

    public:
        OperatorMax();
     ~OperatorMax();

};


class OperatorMin : public Operator {

    private:

    protected:

    public:
        OperatorMin();
     ~OperatorMin();

};


#endif 