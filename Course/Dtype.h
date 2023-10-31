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
};



class Dtype_DOUBLE : public Dtype {

    private:

    protected:


    public:

        /* Data strure that would store int*/
        struct {
            int d_val;
        } dtype;

        Dtype_DOUBLE();
        Dtype_DOUBLE(double val); // paramterized constructor for convenience
        ~Dtype_DOUBLE();
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
};

#endif 