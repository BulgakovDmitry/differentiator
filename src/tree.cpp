#include "../headers/tree.hpp"

Node* newNode(Types type, Value_t value, Node* left, Node* right)
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    ASSERT(node, "node = nullptr, calloc error", stderr);

    if (type >= NUMBER_OF_TYPES) 
    {
        fprintf(stderr, RED"ERROR: type >= NUMBER_OF_TYPES\n"RESET);
        FREE(node); 
        return nullptr;
    }

    if (type == TYPE_OPERATION) 
    {
        if (value.op >= NUMBER_OF_OPERATION && value.op != OPERATION_NIL) 
            assert(false);
    }

    node->type  = type;
    node->value = value;
    node->left  = left;
    node->right = right;

    return node;
}

void dtorTree(Node* node)
{
    ASSERT(node, "node = nullptr, impossible to dtor tree with this root", stderr);

    if (node->left)  
    {
        dtorTree(node->left);
        node->left = NULL;
    }
    if (node->right) 
    {
        dtorTree(node->right);
        node->right = NULL;
    }    
    deleteNode(node);
}

void deleteNode(Node* node) 
{
    ASSERT(node, "node = nullptr, impossible to delete this node", stderr);

    node->type  = (Types)0;
    node->value.num = 0;
    node->value.op = 0;
    node->value.var = 0;

    assert(node->left  == NULL);
    assert(node->right == NULL);

    FREE(node);
}

Node* copy(Node* node)
{
    if(!node) return nullptr;
    Node* n = newNode(node->type, node->value, copy(node->left), copy(node->right));
    return n;
}

