#ifndef SIMPLIFY_H
#define SIMPLIFY_H
#include <math.h>
#include "tree.hpp"

enum Direction
{
    LEFT_DIRECTION,
    RIGHT_DIRECTION,
    PARENT_DIRECTION,
};

Node* constFolding (Node* node);
Node* optimization(Node* node);
bool containsVariable(Node* node);

#endif