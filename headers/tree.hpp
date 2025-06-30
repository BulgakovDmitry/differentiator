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
    OPERATION_NIL  = 0,
    OPERATION_ADD  = 1,  
    OPERATION_SUB  = 2,
    OPERATION_MUL  = 3,
    OPERATION_DIV  = 4, 
    OPERATION_POW  = 5, 
    OPERATION_ROOT = 6, 
    OPERATION_LOG  = 7,
    OPERATION_LN   = 8,
    OPERATION_SIN  = 9,
    OPERATION_COS  = 10,
    OPERATION_TG   = 11,
    OPERATION_SQRT = 12,
    OPERATION_QBRT = 13,
    OPERATION_NEG  = 14,
    NUMBER_OF_OPERATION,
};

const double PI = 3.1415;
const double E  = 2.7183;
const char* const DUMPTEX_FILE_NAME = "dumpTex.tex";

struct Node
{
    Types type;
    Value_t value;
    Node* right, *left, *parent;
};

Node* newNode(Types type, Value_t value, Node* left, Node* right);
Node* copy(Node* node);

void dtorTree(Node* node);    
void deleteNode(Node* node);  

void dumpTex(Node* root);                  // Теховский dump
void printHeadTex(FILE* file);             //
void printfEndTex(FILE* file);             //
void generateTex(Node* node, FILE* file);  //




#endif