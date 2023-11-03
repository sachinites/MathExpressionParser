#ifndef __MEXPR_TREE__
#define __MEXPR_TREE__

#include <stdbool.h>
#include <stdint.h>
#include "MexprcppEnums.h"

class Dtype;

class MexprNode {

    private:

    protected:
        MexprNode(); 

    public:
        virtual ~MexprNode();
        MexprNode *parent;
        MexprNode *left;
        MexprNode *right;
        MexprNode *lst_left;
        MexprNode *lst_right;
        virtual MexprNode * clone() = 0;
        virtual mexprcpp_dtypes_t ResultStorageType(mexprcpp_dtypes_t did1, mexprcpp_dtypes_t did2) = 0;
        virtual Dtype* compute(Dtype *dtype1, Dtype *dtype2) = 0;
};

typedef struct lex_data_ lex_data_t;

class MexprTree {

    private:
    mexprcpp_dtypes_t validate_internal  (MexprNode *root);
    Dtype *evaluate_internal(MexprNode *root);

    protected:

    public:
        MexprNode *root; 
        MexprNode *lst_head; /// will discuss in next lecture video !
        MexprTree();
        virtual ~MexprTree();
        MexprTree(lex_data_t **postfix_lex_data_array, int size); // constructor 
        static void InorderPrint (MexprTree *tree);
        bool validate (MexprNode *root);
        Dtype *evaluate(MexprNode *root);
        void destroy();
} ; 

#endif 