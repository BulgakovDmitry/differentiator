#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>
#include "DSL.h"
#include "read.h"

Node* Read()
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
    gp->p = 0;
    gp->s = NULL;
    return gp;
}

void GetDtor(GetParam* gp)
{
    assert(gp);
    if (gp->s)
        FREE(gp->s);
    gp->p = 0;
}

Node* Get(char* S)
{
    assert(S);
    GetParam* gp = GetCtor();
    assert(gp);

    gp->s = S;
    
    return GetG(gp);
}

Node* GetG(GetParam* gp)
{
    assert(gp);
    Node* val = GetE(gp);

    if(gp->s[gp->p] != '$')
    {
        printf("Syntax Error\n");

        return NULL;
    }
    gp->p++;
    
    GetDtor(gp);
    return val;
}

Node* GetE(GetParam* gp)
{
    assert(gp);

    Node* val = GetT(gp);

    while(gp->s[gp->p] == '+' || gp->s[gp->p] == '-')
    {
        int op = gp->s[gp->p];
        gp->p++;
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

Node* GetT(GetParam* gp)
{
    assert(gp);

    Node* val = GetA(gp);

    while(gp->s[gp->p] == '*' || gp->s[gp->p] == '/')
    {
        int op = gp->s[gp->p];
        gp->p++;
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

Node* GetA(GetParam* gp) // TODO: static
{
    assert(gp);
    Node* val = GetP(gp);

    while(gp->s[gp->p] == '^')
    {
        gp->p++;
        Node* val2 = GetP(gp);
        val = _POW(val, val2);
    }
    
    return val;
}

Node* GetP(GetParam* gp)
{
    assert(gp);

    if(gp->s[gp->p] == '(')
    {
        gp->p++;
        Node* val = GetE(gp);

    
        if(gp->s[gp->p] != ')')
        {
            printf("problem with GetP\n");
            exit(0);
        }
        gp->p++;
        
        return val;
    }
    else
    {
        return GetN(gp);
    }

}



Node* GetN(GetParam* gp)
{
    assert(gp);

    int val = 0;
    int old_p = gp->p;

    if(gp->s[gp->p] <= '9'  && '0' <= gp->s[gp->p])
    {
        while ('0' <= gp->s[gp->p] && gp->s[gp->p] <= '9')
        {
            val = val * 10 + gp->s[gp->p] - '0';
            gp->p++;
        }

        if(gp->p == old_p)
        {
            printf("problem with GetN\n");
            exit(0);
        }

        return _NUM(val);
    }
    else if(isalpha(gp->s[gp->p]) != 0)
    {
        gp->p++;
        return _VAR((int)gp->s[gp->p - STEP_P]);
    }
    else
    {
        printf(RED "problem with GetN\n" RESET);
        exit(0);
    }
}