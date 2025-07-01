#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include <math.h>
#include "tree.hpp"

Node* simplify(Node* node);
bool containsVariable(Node* node);

#endif