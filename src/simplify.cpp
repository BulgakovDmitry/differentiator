#include "../headers/simplify.hpp"
#include "../headers/tree.hpp"        

static void replaceRightSubtree(Node** root);
static void replaceLeftSubtree(Node** root);

static Node* optimisationAdd(Node* node);
static Node* optimisationSub(Node* node);
static Node* optimisationMul(Node* node);

#define IS_NUM(direction, x) ((node->direction) && (node->direction)->type == TYPE_NUMBER && doubleCmp((node->direction)->value.num, x))

static void replaceRightSubtree(Node** root)
{
    ASSERT(*root, "root = nullptr", stderr);
    ASSERT(root, "&root = nullptr", stderr);

    Node* oldRoot = *root;
    Node* newRoot = oldRoot->right;

    oldRoot->right = nullptr;
    dtorTree(oldRoot->left);   
    oldRoot->left = nullptr;

    dtorTree(oldRoot);         
    *root = newRoot;  
}

static void replaceLeftSubtree(Node** root)
{
    ASSERT(*root, "root = nullptr", stderr);
    ASSERT(root, "&root = nullptr", stderr);
    
    Node* oldRoot = *root;
    Node* newRoot = oldRoot->left;

    oldRoot->left = nullptr;   
    dtorTree(oldRoot->right);  
    oldRoot->right = nullptr;

    dtorTree(oldRoot);
    *root = newRoot;
}

bool containsVariable(Node* node) 
{
    if (!node) 
        return false;

    if (node->type == TYPE_VARIABLE) 
        return true;

    if (node->type == TYPE_OPERATION) 
    {
        if (node->left && containsVariable(node->left)) 
            return true;

        if (node->right && containsVariable(node->right)) 
            return true;
    }
    return false;
}

Node* constFolding (Node* node)
{
    if (!node) return nullptr;

    if (node->left)  node->left  = constFolding(node->left);
    if (node->right) node->right = constFolding(node->right);

    if (node->type == TYPE_OPERATION && !containsVariable(node))
    {
        double lhs = node->left  ? node->left ->value.num : 0; 
        double rhs = node->right ? node->right->value.num : 0;
        double res = 0;

        switch (node->value.op)
        {
            case OPERATION_ADD:  res = lhs + rhs;             break;
            case OPERATION_SUB:  res = lhs - rhs;             break;
            case OPERATION_MUL:  res = lhs * rhs;             break;
            case OPERATION_DIV:  res = lhs / rhs;             break;
            case OPERATION_POW:  res = pow(lhs, rhs);         break;

            case OPERATION_SIN:  res = sin(rhs);         break;
            case OPERATION_COS:  res = cos(rhs);         break;
            case OPERATION_TG:   res = tan(rhs);         break;
            case OPERATION_LN:   res = log(rhs);         break;
            case OPERATION_SQRT: res = sqrt(rhs);        break;

            default: return node; 
        }

        if (node->left)  
        { 
            dtorTree(node->left);  
            node->left  = nullptr; 
        }
        if (node->right)
        { 
            dtorTree(node->right); 
            node->right = nullptr; 
        }

        node->type       = TYPE_NUMBER;
        node->value.num  = res;
        node->value.op   = 0;
        node->left       = nullptr;
        node->right      = nullptr;
    }

    return node;
}

Node* optimization(Node* node)
{
    ASSERT(node, "node = nullptr, impossible to optimizate", stderr);

    if (node->left)  node->left  = optimization(node->left);
    if (node->right) node->right = optimization(node->right);

    if (node->type == TYPE_OPERATION)
    {
        switch (node->value.op)
        {
            case OPERATION_ADD:
                node = optimisationAdd(node);
                break;

            case OPERATION_SUB:
                node = optimisationSub(node);  
                break;

            case OPERATION_MUL:
                node = optimisationMul(node); 
                break;

            default:
                //TODO add another oper
                break;
        }
    }

    return node;
}

static Node* optimisationAdd(Node* node)
{
    ASSERT(node, "node = nullptr, impossible to do optimisationAdd", stderr);

    if      (IS_NUM(left,  0)) {replaceRightSubtree(&node);}
    else if (IS_NUM(right, 0)) {replaceLeftSubtree (&node);}

    return node;
}

static Node* optimisationSub(Node* node)
{
    ASSERT(node, "node = nullptr, impossible to do optimisationSUB", stderr);

    if (IS_NUM(right, 0)) 
        replaceLeftSubtree(&node);

    return node;
}

static Node* optimisationMul(Node* node)
{
    ASSERT(node, "node = nullptr, impossible to do optimisationMul", stderr);


    if      (IS_NUM(left,  0)) {replaceLeftSubtree (&node);}
    else if (IS_NUM(left,  1)) {replaceRightSubtree(&node);}
    else if (IS_NUM(right, 0)) {replaceRightSubtree(&node);}
    else if (IS_NUM(right, 1)) {replaceLeftSubtree (&node);}

    return node;
}