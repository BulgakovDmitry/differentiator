#ifndef READ_H
#define READ_H

#include "tree.h"

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
    char* s;
    int p;
};

Node* Read();
Node* Get(char* S);
Node* GetG(GetParam* gp); // Главная начальственная функция
Node* GetE(GetParam* gp); // функция для подсчёта сложения и вычитания
Node* GetT(GetParam* gp); // функция для подсчёта умножения и деления
Node* GetA(GetParam* gp); // функция для подсчёта степени
Node* GetP(GetParam* gp); // функция для приоритета скобок
Node* GetN(GetParam* gp); // функция для чтения числа или переменной

GetParam* GetCtor();
void GetDtor(GetParam* gp);

#endif