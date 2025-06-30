#ifndef GRAPH_DUMP_HPP
#define GRAPH_DUMP_HPP

#include "tree.hpp"

void dumpGraph(Node* node, const char* filePrefix, FILE* html);            

void dumpListNodes(Node* node, FILE* dumpTreeFile);                         
void dumpConnectNodes(Node* node, FILE* dumpTreeFile);                       
void caseOperation(Node* node, const char* operation, FILE* dumpTreeFile);   
void dumpGraphBegin(FILE* html);
void dumpGraphEnd(FILE* html);

const size_t MAX_NAME_FILE_LEN = 64;


#endif