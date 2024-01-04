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

    this->destroy_internal (this->root);
}

void 
MexprTree::destroy_internal(MexprNode *root) {

    Dtype_VARIABLE *dtype_var;

    if (!root) return;

    destroy_internal (root->left);
    destroy_internal (root->right);

    dtype_var = dynamic_cast <Dtype_VARIABLE *> (root);

    if (dtype_var)  this->NodeRemoveFromList (root);
    /* Mexpr Lib never release the data src, it is application
        responsibility to delete the data srcs*/
    delete root;
}

void 
MexprTree::destroy(MexprNode *root) {

    bool rc = this->root == root;

    MexprNode *parent = root->parent;

    if (parent) {

        if (parent->left == root) parent->left = NULL;
        if (parent->right == root) parent->right = NULL;
        root->parent = NULL;
    }

    destroy_internal (root);

    if (rc) {
        this->root = NULL;
        assert(!this->lst_head);
        delete this;
    }
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

void 
MexprTree::NodeRemoveFromList (MexprNode *node) {

    if (node->lst_left == NULL) {

        /* Is is Ist node in the list*/
        assert(this->lst_head == node);
        this->lst_head = node->lst_right;
        if (this->lst_head)
            this->lst_head->lst_left = NULL;
    }
    else {

        node->lst_left->lst_right = node->lst_right;
        if (node->lst_right)
            node->lst_right->lst_left = node->lst_left;
    }

    node->lst_left = NULL;
    node->lst_right = NULL;
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

 bool 
MexprTree::IsLoneVariableOperandNode() {

    MexprNode *opnd_node;

    if (!this->root) return false;
    if (this->root->left || this->root->right) return false;

    opnd_node = this->lst_head;
    if (!opnd_node) return false;

    Dtype_VARIABLE *d_var = dynamic_cast <Dtype_VARIABLE *>(opnd_node);
    assert (d_var);
    assert (this->root == opnd_node);
    return true;
}

bool
MexprTree::concatenate (MexprNode *leaf_node,
                                         MexprTree *child_tree) {

    MexprNode *curr_node;
    Dtype_VARIABLE *dtype_var;
    
    MexprTree *parent_tree = this;

    assert (leaf_node->left == NULL && leaf_node->right == NULL);
    assert (child_tree->root);
    dtype_var = dynamic_cast <Dtype_VARIABLE *> (leaf_node);
    assert (dtype_var);
    assert (!dtype_var->is_resolved);

    if (!leaf_node->parent) {
        assert (parent_tree->root == leaf_node);
        delete(leaf_node);
        parent_tree->root = child_tree->root;
        child_tree->root = NULL;
        parent_tree->lst_head = child_tree->lst_head;
        child_tree->lst_head = NULL;
        delete child_tree;
        return true;
    }

   MexprNode *parent_node = leaf_node->parent;

    if (parent_node->left == leaf_node)
        parent_node->left = child_tree->root;
    else
        parent_node->right = child_tree->root;

    child_tree->root->parent = parent_node;
    child_tree->root = NULL;

    this->NodeRemoveFromList (leaf_node);
    delete leaf_node;

    MexprTree_Iterator_Operands_Begin (parent_tree, curr_node) {

        if (!curr_node->lst_right) break;

    } MexprTree_Iterator_Operands_End;

     if (curr_node) {
        curr_node->lst_right = child_tree->lst_head;
        if (curr_node->lst_right) curr_node->lst_right->lst_left = curr_node;
     }
     else {
        parent_tree->lst_head = child_tree->lst_head;
     }

     child_tree->lst_head = NULL;
     delete child_tree;

     if (!parent_tree->validate (parent_tree->root)) return false;
     return true;
}

MexprTree *
MexprTree::clone(MexprNode *root) {

    MexprTree *clone_tree = new MexprTree();
    clone_tree->CloneNodesRecursively (root, NULL, 0);
    clone_tree->CreateOperandList( );
    return clone_tree;
}

void
MexprTree::CloneNodesRecursively (MexprNode *src_node, 
                                                             MexprNode *new_node, int child) {

    MexprNode *temp;

    if (!src_node) return;

    if (child == 0) {

        this->root = src_node->clone();
        new_node = this->root ;
    }
    else if (child == -1) {

        temp = src_node->clone();
        new_node->left = temp;
        temp->parent = new_node;
        new_node = temp;
    }
    else if (child == 1) {

        temp = src_node->clone();
        new_node->right = temp;
        temp->parent = new_node;
        new_node = temp;
    }    

    CloneNodesRecursively (src_node->left, new_node, -1);
    CloneNodesRecursively (src_node->right, new_node, 1);
}

void 
MexprTree::CreateOperandList (){

    this->CreateOperandList (this->root);
}


void 
MexprTree::CreateOperandList (MexprNode *node) {

    if (!node) return;

    Dtype_VARIABLE *dtype = dynamic_cast <Dtype_VARIABLE *>(node);

    if (dtype) {

        if (!this->lst_head) {
           this->lst_head = node;
        }
        else {
            node->lst_right = this->lst_head;
            this->lst_head->lst_left = node;
            this->lst_head = node;
        }
    }

    CreateOperandList (node->left);
    CreateOperandList (node->right);
}