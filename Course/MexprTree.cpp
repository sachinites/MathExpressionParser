#include <assert.h>
#include "MexprTree.h"
#include "ParserExport.h"
#include <stack>
#include "Dtype.h"
#include "Operators.h"

MexprNode::MexprNode() {

    this->parent = NULL;
    this->left = NULL;
    this->right = NULL;
    this->lst_left = NULL;
    this->lst_right = NULL;
}

MexprNode::~MexprNode() {


}

MexprTree:: MexprTree() {

    this->root = NULL;
    this->lst_head = NULL;
 }

MexprTree::~MexprTree() {

}


MexprTree::MexprTree(lex_data_t **postfix_lex_data_array, int size) {

    int i;
    MexprNode *node;

    MexprTree();

    std::stack<MexprNode *> stack;

    for (i= 0; i < size; i++) {

        if (!(Math_cpp_is_operand (postfix_lex_data_array[i]->token_code) ||
             Math_cpp_is_operator (postfix_lex_data_array[i]->token_code))) continue;

        if (Math_cpp_is_operand (postfix_lex_data_array[i]->token_code)) {

            node = Dtype::factory ((mexprcpp_dtypes_t)(postfix_lex_data_array[i]->token_code));

            Dtype *dtype = dynamic_cast<Dtype *> (node);

            /* If dtype Object is Dtype_VARIABLE */
            Dtype_VARIABLE *dvar = dynamic_cast<Dtype_VARIABLE *>(dtype);

            if (dvar) {
                // opernad node here is of type Dtype_VARIABLE
                dvar->dtype.variable_name.assign(std::string((char *)postfix_lex_data_array[i]->token_val));
                // add node into the Tree opernd list 
                node->lst_right = this->lst_head;
                if ( this->lst_head) this->lst_head->lst_left = node;
                this->lst_head = node;
            }
            else {
                // opernad node here is a constant opernad node ( int, double, string etc )
                dtype->SetValue((void *)postfix_lex_data_array[i]->token_val);
            }

             stack.push(node);
        }


        else if (Math_cpp_is_unary_operator (postfix_lex_data_array[i]->token_code)) {

            node = Operator::factory ((mexprcpp_operators_t) postfix_lex_data_array[i]->token_code);

            MexprNode *left = stack.top(); stack.pop();
            node->left = left;
            node->right = NULL;
            left->parent = node;
            stack.push(node);
        }


       else {

            assert (Math_cpp_is_operator (postfix_lex_data_array[i]->token_code));

            node = Operator::factory ((mexprcpp_operators_t) postfix_lex_data_array[i]->token_code);

            MexprNode *right = stack.top(); stack.pop();
            MexprNode *left = stack.top(); stack.pop();

            node->left = left;
            node->right = right;
            left->parent = node;
            right->parent = node;
            stack.push(node);
       }

    }

    this->root = stack.top(); stack.pop();
    assert (stack.empty());
    assert (!this->root->parent);
}

void 
MexprTree::destroy() {

    // Implement to destroy and free Expression Tree
}


Dtype *
MexprTree::evaluate_internal(MexprNode *root) {

    Dtype *res = NULL;

    if (!root) return NULL;

    Dtype *lrc = evaluate_internal (root->left);
    Dtype *rrc = evaluate_internal (root->right);

    /* If i am leaf*/
    if (!root->left && !root->right) {

        return root->compute(NULL, NULL);
    }

    /* If i am unary operator*/
    if (root->left && !root->right) {

        res = root->compute (lrc, NULL);
        delete lrc;
        return res;
    }

    /* If i am binary operator*/
    res = root->compute (lrc, rrc);
    delete lrc;
    delete rrc;
    return res;
}


Dtype *
MexprTree::evaluate(MexprNode *root) {

    if (!root) return NULL;
    return evaluate_internal (root);
}


static void 
_InorderPrint (MexprNode *node) {

    if (!node) return;

    _InorderPrint (node->left);

    // check if node is operator
    Operator *opr_node = dynamic_cast <Operator *> (node);

    if (opr_node) {

        printf ("%s ", opr_node->name.c_str());
    }
    else {

        Dtype *opnd_node = dynamic_cast <Dtype *> (node);
        assert (opnd_node);

        switch (opnd_node->did) {

            case MATH_CPP_INT:
            {
                Dtype_INT *dtype_int =  dynamic_cast <Dtype_INT *> (opnd_node);
                printf ("%d ", dtype_int->dtype.int_val);
            }
            break;
            case MATH_CPP_DOUBLE:
            {
                Dtype_DOUBLE *dtype_d =  dynamic_cast <Dtype_DOUBLE *> (opnd_node);
                printf ("%lf ", dtype_d->dtype.d_val);                
            }
            break;
            case MATH_CPP_STRING:
            {
                Dtype_STRING *dtype_str =  dynamic_cast <Dtype_STRING *> (opnd_node);
                printf ("%s ", dtype_str->dtype.str_val.c_str());                   
            }
            break;
            default:
                assert(0);
        }
    }

     _InorderPrint (node->right);
}

void 
 MexprTree::InorderPrint (MexprTree *tree) {

    if (!tree || !tree->root) return;

    _InorderPrint(tree->root);
 }

mexprcpp_dtypes_t
 MexprTree::validate_internal (MexprNode *root) {

    mexprcpp_dtypes_t res = MATH_CPP_DTYPE_INVALID;

    mexprcpp_dtypes_t lrc, rrc;

    if (!root) return res;

    lrc = validate_internal(root->left);
    rrc = validate_internal(root->right);


    /* if i am leaf*/

    if (!root->left && !root->right) {

        return root->ResultStorageType (MATH_CPP_DTYPE_INVALID,
                                                              MATH_CPP_DTYPE_INVALID);
    }

    /* If i am unary operator */

    if (root->left && !root->right) {

        return root->ResultStorageType (lrc, MATH_CPP_DTYPE_INVALID);
    }

    /* If I am binary operator */
    return root->ResultStorageType(lrc, rrc);

 }


 bool 
 MexprTree::validate (MexprNode *root) {

    mexprcpp_dtypes_t dtype = validate_internal (root);
    return (dtype != MATH_CPP_DTYPE_INVALID);
 }
