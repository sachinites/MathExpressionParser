#include <assert.h>
#include "MexprEnums.h"
#include "MexprTree.h"
#include "Dtype.h"
#include "Operators.h"

int 
main (int argc, char **argv) {

    MexprNode *plusOp = new OperatorPlus();
    MexprNode *const_int5 = new Dtype_INT (5);
    MexprNode *const_int6 = new Dtype_INT (6);
    MexprNode *const_d7 = new Dtype_DOUBLE (7);

    MexprTree *tree = new MexprTree();
    tree->root = plusOp;
    tree->root->left = const_int5;
    //tree->root->right = const_int6;
    tree->root->right = const_d7;

#if 0
    MexprTree *clone_tree = tree->clone(tree->root); 
    Dtype *res = clone_tree->evaluate();

#else

    Dtype *res = tree->evaluate();
#endif 

    switch (res->did) {
        case MATH_CPP_INT:
        {
            Dtype_INT *res_int = dynamic_cast<Dtype_INT *> (res);
            printf ("Result is = %d\n", res_int->dtype.int_val);
        }
        break;
        case MATH_CPP_DOUBLE:
        {
            Dtype_DOUBLE *res_d = dynamic_cast<Dtype_DOUBLE *> (res);
            printf ("Result is = %lf\n", res_d->dtype.d_val);
        }
        break;
        
        default: 
            assert(0);
    }
    delete res;
    delete const_int5;
    delete const_int6;
    delete plusOp;
    tree->root = NULL;
    delete tree;

    return 0;
}