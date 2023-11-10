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
        bool is_resolved;
        mexprcpp_dtypes_t did;  // Dtype ID 
        virtual ~Dtype();
        static Dtype * factory(mexprcpp_dtypes_t did);
        virtual void SetValue(void *value) = 0;
        virtual void SetValue(Dtype *) = 0;
        virtual MexprNode * clone() = 0;
        virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) = 0;
        virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) = 0;
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
        virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;
        virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
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
        virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;        
        virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
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
        virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;        
        virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
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
        virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;        
        virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
};


class Dtype_VARIABLE : public Dtype {

    private:

    protected:

    public:
        struct {
            std::string variable_name;
        } dtype;

        // resolution information
        void *data_src;
        Dtype *(*compute_fn_ptr)(char *, void *);
        mexprcpp_dtypes_t resolved_did; // optional Dtype_INT

        Dtype_VARIABLE(std::string var_name);
        Dtype_VARIABLE();
        ~Dtype_VARIABLE();

        virtual void SetValue(void *value) override;
        virtual void SetValue(Dtype *)  override;
        virtual MexprNode * clone() override;
        virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) override;        
        virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) override;
        void ResolveOperand (
                mexprcpp_dtypes_t resolved_did,
                void *data_src,
                Dtype *(*compute_fn_ptr)(char *, void *));
}; 
#endif 