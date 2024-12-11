#include "simplify.h"

#define CHECKFLAG(flag_) \
    if (flag_ > 0) return THERE_IS_A_VARIBLE;

#define SEARCH_VAR_IN(direction_)                                 \
    if (node->direction_)                                         \
    {                                                             \
        checkOnPresenceOfVariableInThisSubTree(node->direction_); \
        CHECKFLAG(flag);                                          \
    }                                                             \

PresenceOfVariable checkOnPresenceOfVariableInThisSubTree(Node* node) 
{
    assert(node);
    static int flag = 0;
    if (node->type != TYPE_VARIABLE)
    {
        SEARCH_VAR_IN(left);
        SEARCH_VAR_IN(right);
        return NO_VARIABLE;
    }
    else    
    {
        flag++; 
        return THERE_IS_A_VARIBLE;
    }
}

value_t calculateSubTree(Node* node, const value_t variable)
{
    if (!node)
    {
        printf(RED "ERROR IN FUNCTION calculateSubTree\n" RESET);
        assert(false);
    }

    switch ((int)node->type)
    {
        case TYPE_NUMBER:
        {
            return node->value;
        }
        case TYPE_VARIABLE:
        {
            return variable;
        }
        case TYPE_OPERATION:
        {
            switch ((int)node->value)
            {
                case OPERATION_ADD:
                {
                    return calculateSubTree(node->left, variable) + calculateSubTree(node->right, variable); // CALC_SUBTREE(+);
                }
                case OPERATION_SUB:
                {
                    return calculateSubTree(node->left, variable) - calculateSubTree(node->right, variable); // CALC_SUBTREE(-);
                }
                case OPERATION_MUL:
                {
                    return calculateSubTree(node->left, variable) * calculateSubTree(node->right, variable); 
                }
                case OPERATION_DIV:
                {
                    return calculateSubTree(node->left, variable) / calculateSubTree(node->right, variable);
                }
                case OPERATION_POW:
                {
                    return pow(calculateSubTree(node->left, variable), calculateSubTree(node->right, variable));
                }
                case OPERATION_LOG:
                {
                    return log(calculateSubTree(node->right, variable))/log(calculateSubTree(node->left, variable));
                }
                case OPERATION_SQRT:
                {
                    return sqrt(calculateSubTree(node->right, variable));
                }
                default:
                {
                    printf(RED "UNDEFINED OPERATION\n" RESET);
                    return 0;
                    assert(false);
                }
            }
        }
    }
    return NULL;
}