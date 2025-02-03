#include "diff.h"
#include "DSL.h"

Node* diff(Node* node)
{
    if (!node)
    {
        printf(RED "ERROR IN FUNCTION diff, diff get the null node\n" RESET);
        abort();
    }

    if (node->type == TYPE_NUMBER) 
        return _NUM(0);

    if (node->type == TYPE_VARIABLE) 
        return _NUM(1);

    if (node->type == TYPE_OPERATION) 
    {
        switch ((int)node->value)
        {
            case OPERATION_ADD:
            {
                return _ADD(diff(node->left), diff(node->right));
            }    
            case OPERATION_SUB:
            {
                return _SUB(diff(node->left), diff(node->right));
            }
            case OPERATION_MUL:
            {
                return _ADD(_MUL(diff(node->left), copy(node->right)), _MUL(copy(node->left), diff(node->right)));
            }
            case OPERATION_DIV:
            {
                return _DIV(_SUB(_MUL(diff(node->left), copy(node->right)), _MUL(copy(node->left), diff(node->right))), _MUL(copy(node->right), copy(node->right))); 
            }
            case OPERATION_SIN:
            {
                return _MUL(_COS(copy(node)->right), diff(node->right));
            }
            case OPERATION_COS:
            {
                return _MUL(_SUB(_NUM(0), _SIN(copy(node)->right)), diff(node->right));
            }
            case OPERATION_TG:
            {
                return _MUL(_DIV(_NUM(1), _POW(_COS(copy(node)->right), _NUM(2))), diff(node->right));
            }
            case OPERATION_LN:
            {
                return _MUL(_DIV(_NUM(1), copy(node->right)), diff(node->right));
            }
            case OPERATION_LOG:
            {
                return _MUL(_DIV(_NUM(1), _MUL(copy(node)->right, _LN(copy(node)->left))), diff(node->right));
            }
            case OPERATION_POW:
            {
                return diffPow(node);
            }
            default:
                printf(RED "SINTAX ERRROR IN FUNCTION DIFF\n" RESET);
                break;
        }
    }   
    else 
    {
        printf(RED "ERROR IN FUNCTION DIFF\n" RESET);
        return node;
    }
    return node; 
}

Node* diffPow(Node* node)
{
    assert(node);

    PresenceOfVariable prV = checkOnPresenceOfVariableInThisSubTree(node);

    if (prV == NO_VARIABLE)
        return _NUM(0);
    else
    {
        PresenceOfVariable prVleft  = checkOnPresenceOfVariableInThisSubTree(node->left);
        PresenceOfVariable prVright = checkOnPresenceOfVariableInThisSubTree(node->right);
        
        if (prVleft == THERE_IS_A_VARIBLE && prVright == NO_VARIABLE)
            return _MUL(_MUL(_POW(copy(node)->left, _SUB(copy(node)->right, _NUM(1))), copy(node)->right), diff(node->left));
        if (prVleft == NO_VARIABLE && prVright == THERE_IS_A_VARIBLE)
            return _MUL(_MUL(_POW(copy(node)->left, copy(node)->right), _LN(copy(node)->left)), diff(node->right));
        else
            return  _MUL(copy(node), diff(_MUL(_LN(copy(node->left)), copy(node->right))));
    }
}