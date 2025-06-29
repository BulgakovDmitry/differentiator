#ifndef TREE_H
#define TREE_H

#include <assert.h>
#include <stdlib.h>
<<<<<<< HEAD:headers/tree.hpp
#include <myLib.hpp>
=======
#include <myLib.h>
>>>>>>> bd16e690d2e5ded0d14e349537736a45217249a6:tree.h

typedef double value_t;

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
    OPERATION_POW  = 5, //
    OPERATION_ROOT = 6, 
    OPERATION_LOG  = 7,
    OPERATION_LN   = 8,
    OPERATION_SIN  = 9,
    OPERATION_COS  = 10,
    OPERATION_TG   = 11,
    OPERATION_SQRT = 12,
    OPERATION_QBRT = 13,
    NUMBER_OF_OPERATION,
};

const double PI = 3.1415;
const double E  = 2.7183;
const char* const DUMPTEX_FILE_NAME = "dumpTex.tex";

// TODO union value_t

struct Node
{
    Types type;
    value_t value;
    Node* right, *left, *parent;
};

Node* newNode(Types type, value_t value, Node* left, Node* right);
Node* copy(Node* node);

void dtorTree(Node* node);    
void deleteNode(Node* node);  

void dumpGraph(Node* node);                                                  //
void dumpListNodes(Node* node, FILE* dumpTreeFile);                          // Графический dump
void dumpConnectNodes(Node* node, FILE* dumpTreeFile);                       // 
void caseOperation(Node* node, const char* operation, FILE* dumpTreeFile);   //

void dumpPrint(Node* node);                                 // Консольный
void print(Node* node);                                     // dump
void casePrintOperation(Node* node, const char* operation); // 

void dumpTex(Node* root);                  // Теховский dump
void printHeadTex(FILE* file);             //
void printfEndTex(FILE* file);             //
void generateTex(Node* node, FILE* file);  //




#endif