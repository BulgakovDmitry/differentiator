#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>
#include "DSL.h"
#include "read.h"

static Node* Get(char* S);
static Node* GetG(GetParam* gp); // Главная начальственная функция
static Node* GetE(GetParam* gp); // функция для подсчёта сложения и вычитания
static Node* GetT(GetParam* gp); // функция для подсчёта умножения и деления
static Node* GetA(GetParam* gp); // функция для подсчёта степени
static Node* GetP(GetParam* gp); // функция для приоритета скобок
static Node* GetN(GetParam* gp); // функция для чтения числа или переменной

Node* read()
{
    const char* const FileName = "expression.txt";
    FILE* inputText = fopen(FileName, "r");
    assert(inputText);

    size_t bufferSize = getSizeOfFile(inputText, FileName);

    char* buffer = (char*) calloc(bufferSize, sizeof(char));
    assert(buffer);

    char* text = (char*) calloc(bufferSize, sizeof(char));
    assert(text);

    fread(buffer, sizeof(char), bufferSize, inputText);

    size_t currentTextElem = 0;
    for(size_t CurrentElem = 0; CurrentElem < bufferSize; CurrentElem++)
    {
        if(buffer[CurrentElem] == '\n' || buffer[CurrentElem] == ' ')
        {}
        else
        {
            text[currentTextElem] = buffer[CurrentElem];
            currentTextElem++;
        }
    }

    printf("%sYour expression%s:%s ", GREEN, RED, RESET);
    for(size_t i = 0; i < currentTextElem; i++)
    {
        if (text[i] == '$')
            printf(RED "%c" RESET, text[i]);
        else
            printf(CEAN "%c" RESET, text[i]);     
    }

    printf("\n");

    FREE(buffer);
    return Get(text);

    return 0;
}

GetParam* GetCtor()
{
    GetParam* gp = (GetParam*)calloc(1, sizeof(GetParam));
    assert(gp);
    gp->index = 0;
    gp->arr = NULL;
    return gp;
}

void GetDtor(GetParam* gp)
{
    assert(gp);
    if (gp->arr)
        FREE(gp->arr);
    gp->index = 0;
}

static Node* Get(char* S)
{
    assert(S);
    GetParam* gp = GetCtor();
    assert(gp);

    gp->arr = S;
    
    return GetG(gp);
}

static Node* GetG(GetParam* gp)
{
    assert(gp);
    Node* val = GetE(gp);

    if(gp->arr[gp->index] != '$')
    {
        printf("Syntax Error\n");

        return NULL;
    }
    gp->index++;
    
    GetDtor(gp);
    return val;
}

static Node* GetE(GetParam* gp)
{
    assert(gp);

    Node* val = GetT(gp);

    while(gp->arr[gp->index] == '+' || gp->arr[gp->index] == '-')
    {
        int op = gp->arr[gp->index];
        gp->index++;
        Node* val2 = GetT(gp);
        if(op == '+')
        {
            val = _ADD(val, val2);
        }
        else 
        {
            val = _SUB(val, val2);
        }
    }

    return val;
}

static Node* GetT(GetParam* gp)
{
    assert(gp);

    Node* val = GetA(gp);

    while(gp->arr[gp->index] == '*' || gp->arr[gp->index] == '/')
    {
        int op = gp->arr[gp->index];
        gp->index++;
        Node* val2 = GetA(gp);
        if(op == '*')
        {
            val = _MUL(val, val2);
        }
        else 
        {
            val = _DIV(val, val2);    
        }
    }

    return val;
}

static Node* GetA(GetParam* gp)
{
    assert(gp);
    Node* val = GetP(gp);

    while(gp->arr[gp->index] == '^')
    {
        gp->index++;
        Node* val2 = GetP(gp);
        val = _POW(val, val2);
    }
    
    return val;
}

static Node* GetP(GetParam* gp)
{
    assert(gp);

    if(gp->arr[gp->index] == '(')
    {
        gp->index++;
        Node* val = GetE(gp);

    
        if(gp->arr[gp->index] != ')')
        {
            printf("problem with GetP\n");
            exit(0);
        }
        gp->index++;
        
        return val;
    }
    else
    {
        return GetN(gp);
    }

}



static Node* GetN(GetParam* gp)
{
    assert(gp);

    int val = 0;
    int old_p = gp->index;

    if(gp->arr[gp->index] <= '9'  && '0' <= gp->arr[gp->index])
    {
        while ('0' <= gp->arr[gp->index] && gp->arr[gp->index] <= '9')
        {
            val = val * 10 + gp->arr[gp->index] - '0';
            gp->index++;
        }

        if(gp->index == old_p)
        {
            printf("problem with GetN\n");
            exit(0);
        }

        return _NUM(val);
    }
    else if(isalpha(gp->arr[gp->index]) != 0)
    {
        gp->index++;
        return _VAR((int)gp->arr[gp->index - STEP_P]);
    }
    else
    {
        printf(RED "problem with GetN\n" RESET);
        exit(0);
    }
}