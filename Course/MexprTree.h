#ifndef __MEXPR_TREE__
#define __MEXPR_TREE__

#include <stdbool.h>
#include <stdint.h>
#include "MexprcppEnums.h"


class MexprNode {

    private:

    protected:
        MexprNode(); 

    public:
        virtual ~MexprNode();

};

typedef struct lex_data_ lex_data_t;

class MexprTree {

    private:


    protected:


    public:
        MexprNode *root; 
        MexprNode *lst_head; /// will discuss in next lecture video !
        MexprTree(lex_data_t **postfix_lex_data_array, int size); // constructor 

} ;

#endif 