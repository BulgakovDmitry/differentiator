#include "../headers/tree.hpp"

Node* newNode(Types type, Value_t value, Node* left, Node* right)
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    if (!node)
    {
        fprintf(stderr, RED"ERROR: Calloc returned nullptr in newNode()\n"RESET);
        return nullptr;
    }

    if (type >= NUMBER_OF_TYPES) 
    {
        fprintf(stderr, RED"ERROR: type >= NUMBER_OF_TYPES\n"RESET);
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
    if (!node) 
    {
        fprintf(stderr, RED "node == nullptr, impossible to do dtor\n" RESET); 
        return;
    }

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
    if (!node) 
    {
        fprintf(stderr, RED "The node is not deleted\n" RESET); 
        return;
    }

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
    if(!node) return NULL;
    Node* n = newNode(node->type, node->value, copy(node->left), copy(node->right));
    return n;
}

