#ifndef SIMPLIFY_H
#define SIMPLIFY_H
#include <math.h>
#include "tree.hpp"
enum PresenceOfVariable
{
    THERE_IS_A_VARIBLE = 1,
    NO_VARIABLE        = 2,
};

enum Direction
{
    LEFT_DIRECTION,
    RIGHT_DIRECTION,
    PARENT_DIRECTION,
};

PresenceOfVariable checkOnPresenceOfVariableInThisSubTree(Node* node);

int simplify(Node* root);
int constantFolding(Node* node);
int TrivialOperations(Node** node);







#endif