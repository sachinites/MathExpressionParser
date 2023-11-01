#ifndef __DTYPE__
#define __DTYPE__

#include <string>
#include "MexprTree.h"
#include "MexprcppEnums.h"

class Dtype : public MexprNode {

    private:

    protected:
        Dtype();

    public:
        mexprcpp_dtypes_t did;  // Dtype ID 
        virtual ~Dtype();
        static Dtype * factory(mexprcpp_dtypes_t did);
        virtual void SetValue(void *value) = 0;
        virtual void SetValue(Dtype *) = 0;
        virtual MexprNode * clone() = 0;
} ;


class Dtype_INT : public Dtype {

    private:

    protected:


    public:

        /* Data strure that would store int*/
        struct {
            int int_val;
        } dtype;

        Dtype_INT();
        Dtype_INT(int val); // paramterized constructor for convenience
        ~Dtype_INT();
        virtual void SetValue(void *value) override;
        virtual void SetValue(Dtype *)  override;
        virtual MexprNode * clone() override;
};



class Dtype_DOUBLE : public Dtype {

    private:

    protected:


    public:

        /* Data strure that would store int*/
        struct {
            double d_val;
        } dtype;

        Dtype_DOUBLE();
        Dtype_DOUBLE(double val); // paramterized constructor for convenience
        ~Dtype_DOUBLE();
        virtual void SetValue(void *value) override;
        virtual void SetValue(Dtype *)  override;
        virtual MexprNode * clone() override;
};




class Dtype_STRING : public Dtype {

    private:

    protected:


    public:

        /* Data structure that would store int*/
        struct {
            std::string str_val;
        } dtype;

        Dtype_STRING();
        ~Dtype_STRING();
        virtual void SetValue(void *value) override;
        virtual void SetValue(Dtype *)  override;
        virtual MexprNode * clone() override;
};



class Dtype_BOOL : public Dtype {

    private:

    protected:

    public:

        struct {
                bool b_val;
        }dtype;

        Dtype_BOOL();
        ~Dtype_BOOL();
        virtual void SetValue(void *value) override;
        virtual void SetValue(Dtype *)  override;
        virtual MexprNode * clone() override;
};

#endif 