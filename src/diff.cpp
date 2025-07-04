#include "../headers/diff.hpp"
#include "../headers/DSL.hpp"

Node* diff(Node* node)
{
    ASSERT(node, "node = nullptr, impossible to diff", stderr);

    Node* result = nullptr;

    if (node->type == TYPE_NUMBER) 
        result = _NUM(0);

    else if (node->type == TYPE_VARIABLE) 
        result = _NUM(1);

    else if (node->type == TYPE_OPERATION) 
    {
        Node* left  = node->left;
        Node* right = node->right;
        switch (node->value.op)
        {
            case OPERATION_ADD:
            {
                result = _ADD(diff(left), diff(right));
                break;
            }    
            case OPERATION_SUB:
            {
                result = _SUB(diff(left), diff(right));
                break;
            }
            case OPERATION_MUL:
            {
                result = _ADD(_MUL(diff(left), copy(right)), _MUL(copy(left), diff(right)));
                break;
            }
            case OPERATION_DIV:
            {
                result = _DIV(_SUB(_MUL(copy(right), diff(left)), _MUL(copy(left), diff(right))),_POW(copy(right), _NUM(2)));
                break;
            }
            case OPERATION_NEG:
            {
                result = _NEG(diff(right));
                break;
            }
            case OPERATION_SIN:
            {
                result = _MUL(_COS(copy(right)), diff(right));
                break;
            }
            case OPERATION_COS:
            {
                result = _MUL(_NEG(_SIN(copy(right))), diff(right));
                break;
            }
            case OPERATION_TG:
            {
                result = _MUL(_DIV(_NUM(1), _POW(_COS(copy(right)), _NUM(2))), diff(right));
                break;
            }
            case OPERATION_CTG:
            {
                result = _NEG(_MUL(_DIV(_NUM(1), _POW(_SIN(copy(right)), _NUM(2))), diff(right)));
                break;
            }
            case OPERATION_LN:
            {
                result = _DIV(diff(right), copy(right));
                break;
            }
            case OPERATION_POW:
            {
                result = diffPow(node);
                break;
            }
            case OPERATION_SQRT:
            {
                result = _MUL(_DIV(_NUM(1), _MUL(_NUM(2), _SQRT(copy(right)))), diff(right));
                break;
            }
            case OPERATION_ARCSIN:
            {
                result = _MUL(_DIV(_NUM(1), _SQRT(_SUB(_NUM(1), _POW(copy(right), _NUM(2))))), diff(right));
                break;
            }
            case OPERATION_ARCCOS:
            {
                result = _MUL(_NEG(_DIV(_NUM(1), _SQRT(_SUB(_NUM(1), _POW(copy(right), _NUM(2)))))), diff(right));
                break;
            }
            case OPERATION_ARCTG:
            {
                result = _MUL(_DIV(_NUM(1), _ADD(_NUM(1), _POW(copy(right), _NUM(2)))), diff(right));
                break;
            }
            case OPERATION_SH:
            {
                result = _MUL(_CH(copy(right)), diff(right));
                break;
            }
            case OPERATION_CH:
            {
                result = _MUL(_SH(copy(right)), diff(right));
                break;
            }
            case OPERATION_TH:
            {
                result = _MUL(_DIV(_NUM(1), _POW(_CH(copy(right)), _NUM(2))), diff(right));
                break;
            }
            case OPERATION_CTH:
            {
                result = _MUL(_NEG(_DIV(_NUM(1), _POW(_SH(copy(right)), _NUM(2)))), diff(right));
                break;
            }
            case OPERATION_ARCCTG:
            {
                result = _MUL(_NEG(_DIV(_NUM(1), _ADD(_NUM(1), _POW(copy(right), _NUM(2))))), diff(right));
                break;
            }
            default:
                fprintf(stderr, RED"SINTAX ERRROR IN FUNCTION DIFF\n"RESET);
                break;
        }
    }   

    return result; 
}

Node* diffPow(Node* node) 
{
    Node* base = node->left;
    Node* exp  = node->right;

    bool varInBase = containsVariable(base);
    bool varInExp  = containsVariable(exp);

    if (varInBase && !varInExp) 
        return _MUL(_MUL(copy(exp), _POW(copy(base), _SUB(copy(exp), _NUM(1)))), diff(base));

    if (!varInBase && varInExp) 
        return _MUL(_MUL(_POW(copy(base), copy(exp)), _LN(copy(base))), diff(exp));

    return _MUL(copy(node), _ADD(_MUL(diff(exp), _LN(copy(base))), _MUL(copy(exp), _DIV(diff(base), copy(base)))));
}