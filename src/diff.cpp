#include "../headers/diff.hpp"
#include "../headers/DSL.hpp"

Node* diff(Node* node)
{
    if (!node)
    {
        fprintf(stderr, RED "ERROR IN FUNCTION diff, diff get the null node\n" RESET);
        abort();
    }

    if (node->type == TYPE_NUMBER) 
        return _NUM(0);

    if (node->type == TYPE_VARIABLE) 
        return _NUM(1);

    if (node->type == TYPE_OPERATION) 
    {
        Node* left  = node->left;
        Node* right = node->right;
        switch (node->value.op)
        {
            /*case OPERATION_NEG:
            {
                return _NEG(diff(node->right)); //TODO add unarny operations
            }*/
            case OPERATION_ADD:
            {
                return _ADD(diff(left), diff(right));
            }    
            case OPERATION_SUB:
            {
                return _SUB(diff(left), diff(right));
            }
            case OPERATION_MUL:
            {
                return _ADD(_MUL(diff(left), copy(right)), _MUL(copy(left), diff(right)));
            }
            case OPERATION_DIV:
            {
                return _DIV(_SUB(_MUL(copy(right), diff(left)), _MUL(copy(left), diff(right))),_POW(copy(right), _NUM(2)));
            }
            case OPERATION_SIN:
            {
                return _MUL(_COS(copy(right)), diff(right));
            }
            case OPERATION_COS:
            {
                return _MUL(_NEG(_SIN(copy(right))), diff(right));
            }
            case OPERATION_TG:
            {
                return _MUL(_DIV(_NUM(1), _POW(_COS(copy(right)), _NUM(2))), diff(right));
            }
            case OPERATION_LN:
            {
                return _DIV(diff(right), copy(right));
            }
            case OPERATION_LOG:
            {
                Node* base = left;
                Node* arg  = right;
                Node* lnBase = _LN(copy(base));
                Node* lnArg  = _LN(copy(arg));

                Node* term1 = _DIV(diff(arg), _MUL(copy(arg), lnBase));
                Node* term2 = _DIV(_MUL(lnArg, diff(base)), _MUL(_POW(lnBase, _NUM(2)), copy(base)));

                return _SUB(term1, term2);
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
    
    return nullptr; 
}

Node* diffPow(Node* node) {
    Node* base = node->left;
    Node* exp  = node->right;

    bool varInBase = containsVariable(base);
    bool varInExp  = containsVariable(exp);

    if (varInBase && !varInExp) 
    {
        return _MUL(_MUL(copy(exp), _POW(copy(base), _SUB(copy(exp), _NUM(1)))), diff(base));
    }

    if (!varInBase && varInExp) 
    {
        return _MUL(_MUL(_POW(copy(base), copy(exp)), _LN(copy(base))), diff(exp));
    }

    return _MUL(copy(node), _ADD(_MUL(diff(exp), _LN(copy(base))), _MUL(copy(exp), _DIV(diff(base), copy(base)))));
}