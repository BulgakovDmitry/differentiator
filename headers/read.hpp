#ifndef READ_H
#define READ_H

#include "tree.hpp"

const char* const EXPRESSION_FILE = "expression.txt";

Node* readExpression(FILE* expressionFile);

#endif