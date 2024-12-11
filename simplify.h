#ifndef SIMPLIFY_H
#define SIMPLIFY_H
#include <math.h>
#include "tree.h"
enum PresenceOfVariable
{
    THERE_IS_A_VARIBLE = 1,
    NO_VARIABLE        = 2,
    NO_VARIABLE_E = 3
};

PresenceOfVariable checkOnPresenceOfVariableInThisSubTree(Node* node);





#endif