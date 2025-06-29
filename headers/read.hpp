#ifndef READ_H
#define READ_H

#include "tree.hpp"

struct ReadStruct
{
    Node* Root;
    size_t depth;
    size_t CurrentNum;
    bool IsRight;
};

const int FILENAMESIZE  = 25;
const int STEP_P        = 1;

struct GetParam
{
    char* arr;
    int index;
};

Node* read();
GetParam* GetCtor();
void GetDtor(GetParam* gp);

#endif