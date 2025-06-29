#include "../headers/simplify.hpp"
#include "../headers/tree.hpp"
// свёртка констант при выходе из дерева (прм подъёме)
#define CHECKFLAG(flag_) \
    if (flag_ > 0) return THERE_IS_A_VARIBLE;

#define SEARCH_VAR_IN(direction_)                                 \
    if (node->direction_)                                         \
    {                                                             \
        checkOnPresenceOfVariableInThisSubTree(node->direction_); \
        CHECKFLAG(flag);                                          \
    }                                                             \

#define REPLACE(op_enum, sign)                                          \
op_enum:                                                                \
            {                                                           \
                node->type = TYPE_NUMBER;                               \
                                                                        \
                node->value = node->left->value sign node->right->value;\
                                                                        \
                FREE(node->left);                                       \
                FREE(node->right);                                      \
                                                                        \
                node->left = nullptr;                                   \
                node->right = nullptr;                                  \
                                                                        \
                return 1;                                               \
                                                                        \
                break;                                                  \
            }



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

int simplify(Node* root)
{
    if(!root)
    {
        printf(RED "ERROR: Bad root\n" RESET);
        assert(false);
    }

    int simplifyQuantity = 1;

    while(simplifyQuantity)
    {
        simplifyQuantity = 0;

        int temp = constantFolding(root);

        temp += TrivialOperations(&root);        

        simplifyQuantity += temp;


    }

    dumpGraph(root);
    
    return 0;
}

int constantFolding(Node* node)
{
    if(node->type == TYPE_OPERATION && node->left && node->right && node->left->type == TYPE_NUMBER && node->right->type == TYPE_NUMBER)
    {
        switch ((int)node->value)
        {
        case REPLACE(OPERATION_ADD, +)
        case REPLACE(OPERATION_SUB, -)
        case REPLACE(OPERATION_MUL, *)
        case REPLACE(OPERATION_DIV, /)
        
        case OPERATION_POW:
            {
                node->type = TYPE_NUMBER;

                int tempval = node->left->value;

                for(int i = 0; i < node->right->value - 1; i++)
                {
                    tempval *= node->left->value;
                }

                node->value = tempval;

                FREE(node->left);
                FREE(node->right);

                return 1;

                break;
            }

        default:
            printf("Unknown operation in folding\n");
            break;
        }
    }
    else
    {    
        if(node->left)
        {
            if(node->left->type == TYPE_OPERATION)
            {
                return constantFolding(node->left);
            }
        }
        if(node->right)
        {
            if(node->right->type == TYPE_OPERATION)
            {
                return constantFolding(node->right);
            }
        }
    }

    return 0;
}

int TrivialOperations(Node** node)
{
    if((*node)->type == TYPE_OPERATION)
    {
        switch ((int)(*node)->value)
        {
        case OPERATION_ADD:
            {
                if((*node)->left->type == TYPE_NUMBER && (*node)->left->value == 0)
                {
                    (*node) = (*node)->right;

                    return 1;
                }
                if((*node)->right->type == TYPE_NUMBER && (*node)->right->value == 0)
                {
                    (*node) = (*node)->left;

                    return 1;
                }

                break;
            }

        case OPERATION_SUB:
            {
                if((*node)->right->type == TYPE_NUMBER && (*node)->right->value == 0)
                {
                    (*node) = (*node)->right;

                    return 1;
                }

                break;
            }

        case OPERATION_MUL:
            {
                if(((*node)->left->type == TYPE_NUMBER && (*node)->left->value == 0) || ((*node)->right->type == TYPE_NUMBER && (*node)->right->value == 0))
                {
                    (*node)->type = TYPE_NUMBER;
                    (*node)->value = 0;

                    FREE((*node)->right);
                    FREE((*node)->left);

                    return 1;
                }

                if((*node)->left->type == TYPE_NUMBER && (*node)->left->value == 1)
                {
                    (*node) = (*node)->right;

                    return 1;
                }

                if((*node)->right->type == TYPE_NUMBER && (*node)->right->value == 1)
                {
                    (*node) = (*node)->left;

                    return 1;
                }

                break;
            }

        case OPERATION_DIV:
            {
                if((*node)->left->type == TYPE_NUMBER && (*node)->left->value == 0)
                {
                    (*node)->type = TYPE_NUMBER;
                    (*node)->value = 0;

                    FREE((*node)->right);
                    FREE((*node)->left);

                    return 1;
                }
                
                if((*node)->right->type == TYPE_NUMBER &&  (*node)->right->value == 1)
                {
                    (*node) = (*node)->left;

                    return 1;
                }
    

                break;
            }
     
        case OPERATION_POW:
        {   
            if((*node)->right->type == TYPE_NUMBER && (*node)->right->value == 0)
            {
                (*node)->type = TYPE_NUMBER;
                (*node)->value = 1;

                FREE((*node)->left);
                FREE((*node)->right);

                return 1;
            }
            else
            {
                if((*node)->left->type == TYPE_NUMBER && (*node)->left->value == 1)
                {
                    (*node)->type = TYPE_NUMBER;
                    (*node)->value = 1;

                    FREE((*node)->left);
                    FREE((*node)->right);

                    return 1;
                }
                if((*node)->right->type == TYPE_NUMBER && (*node)->right->value == 1)
                {
                    (*node) = (*node)->left;

                    return 1;
                }
            }

            break;
        }   
        
        default:
            break;
        }
    }

    int val = 0;

    if((*node)->left)
    {
        if((*node)->left->type == TYPE_OPERATION)
        {
            val += TrivialOperations(&((*node)->left));
        }
    }


    if((*node)->right)
    {
        if((*node)->right->type == TYPE_OPERATION)
        {
            val += TrivialOperations(&((*node)->right));
        }
    }

    return val;
}