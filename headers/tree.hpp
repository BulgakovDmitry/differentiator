#ifndef TREE_H
#define TREE_H

#include <assert.h>
#include <stdlib.h>
#include <myLib.hpp>

union Value_t
{
    double num;
    int op;
    char var;
};

enum Types
{
    TYPE_NUL       = 0,
    TYPE_NUMBER    = 1,
    TYPE_VARIABLE  = 2,
    TYPE_OPERATION = 3,
    NUMBER_OF_TYPES,
};

enum Operations
{
    OPERATION_NIL    = 0, 
    OPERATION_ADD    = 1, 
    OPERATION_SUB    = 2, 
    OPERATION_MUL    = 3, 
    OPERATION_DIV    = 4,  
    OPERATION_POW    = 5,  
    OPERATION_LN     = 6,   
    OPERATION_SIN    = 7, 
    OPERATION_COS    = 8, 
    OPERATION_TG     = 9, 
    OPERATION_CTG    = 10,  
    OPERATION_ARCSIN = 11, 
    OPERATION_ARCCOS = 12,
    OPERATION_ARCTG  = 13,
    OPERATION_ARCCTG = 14,
    OPERATION_SQRT   = 15, 
    OPERATION_NEG    = 16, 
    OPERATION_SH     = 17,
    OPERATION_CH     = 18,
    OPERATION_TH     = 19,
    OPERATION_CTH    = 20,
    NUMBER_OF_OPERATION
};

struct Node
{
    Types type;
    Value_t value;
    Node* right, *left, *parent;
};

Node* newNode(Types type, Value_t value, Node* left, Node* right);
Node* copy(Node* node);

void dtorTree  (Node* node);    
void deleteNode(Node* node);  

#endif