#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include "tree.hpp"

Node* simplify(Node* node, size_t* count);
bool containsVariable(Node* node);

#endif