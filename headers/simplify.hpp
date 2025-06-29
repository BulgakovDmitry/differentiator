#ifndef SIMPLIFY_H
#define SIMPLIFY_H
#include <math.h>
<<<<<<< HEAD:headers/simplify.hpp
#include "tree.hpp"
=======
#include "tree.h"
>>>>>>> bd16e690d2e5ded0d14e349537736a45217249a6:simplify.h
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