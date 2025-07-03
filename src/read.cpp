#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <ctype.h>
#include "../headers/DSL.hpp"
#include "../headers/read.hpp"
#include "../headers/tree.hpp"

/*-----------------------------------------[_____GRAMMAR_____]-----------------------------------------*/
// GRAMMAR ::= ADD_SUB '$'
// ADD_SUB ::= MUL_DIV {['+', '-'] MUL_DIV}*
// MUL_DIV ::= POW {['*', '/'] POW}*
// POW     ::= FUNC {['^'] FUNC}*
// FUNC    ::= ['ln', 'sqrt', 'sin', 'cos', 'tg', 'ctg', 'arctg', 'arcctg', 'arcsin', 'arccos', 
//              'neg', 'sh', 'ch', 'th', 'cth'] '(' ADD_SUB ')' | EXPR
// EXPR    ::= '(' ADD_SUB ')' | ARG
// ARG     ::= NUM | VAR
// VAR     ::= ['a'-'z''A'-'Z']*
// NUM     ::= ['0'-'9']+
/*-----------------------------------------------------------------------------------------------------*/

static const char* cur = nullptr;

static inline void skipSpaces();
static Node* makeFunc(const char *name, Node *arg);
 
static Node* parseGrammar(); // rule - GRAMMAR
static Node* parseAddSub (); // rule - ADD_SUB
static Node* parseMulDiv (); // rule - MUL_DIV
static Node* parsePow    (); // rule - POW
static Node* parseFunc   (); // rule - FUNC
static Node* parseExpr   (); // rule - EXPR 
static Node* parseArg    (); // rule - ARG
static Node* parceVar    (); // rule - VAR
static Node* parceNum    (); // rule - NUM

static inline void skipSpaces() 
{
    while (*cur && isspace(*cur)) ++cur;
}

#define FUNC_LIST      \
    X(ln,     _LN)     \
    X(neg,    _NEG)    \
    X(sqrt,   _SQRT)   \
    X(sin,    _SIN)    \
    X(cos,    _COS)    \
    X(tg,     _TG)     \
    X(ctg,    _CTG)    \
    X(arctg,  _ARCTG)  \
    X(arcctg, _ARCCTG) \
    X(arcsin, _ARCSIN) \
    X(arccos, _ARCCOS) \
    X(sh,     _SH)     \
    X(ch,     _CH)     \
    X(th,     _TH)     \
    X(cth,    _CTH)

static Node *makeFunc(const char *name, Node *arg)
{
#define X(str, fn) if (strcmp(name, #str) == 0) return fn(arg);
    FUNC_LIST                
#undef X

    fprintf(stderr, RED"unknown function\n"RESET);
    return NULL;
}

Node* readExpression(FILE* expressionFile)
{
    ASSERT(expressionFile, "expressionFile = nullptr, impossible to read the math expression", stderr);

    size_t bufferSize = getFileSize(expressionFile);

    char* buffer = (char*)calloc(bufferSize, sizeof(char));
    ASSERT(buffer, "buffer = nullptr, calloc error", stderr);

    fread(buffer, sizeof(char), bufferSize, expressionFile);

    cur = buffer;

    Node* root = parseGrammar();
    
    FREE(buffer);
    return root;
}

//------------------------------------------------------------------------------
//  ADD_SUB '$'
//------------------------------------------------------------------------------
static Node* parseGrammar()
{
    Node* root = parseAddSub();
    ASSERT(root, "error in readExpression, expression unread", stderr);

    skipSpaces();
    if (*cur != '$') 
    {
        fprintf(stderr, RED"syntax error — expected '$' at end of input'\n"RESET);
        return nullptr;
    }

    return root;
}

//------------------------------------------------------------------------------
//  MUL_DIV {['+', '-'] MUL_DIV}*
//------------------------------------------------------------------------------
static Node* parseAddSub(void)
{
    Node* left = parseMulDiv();
    if (!left) return NULL;

    skipSpaces();
    while (*cur == '+' || *cur == '-') 
    {
        char op = *cur++;
        Node *right = parseMulDiv();
        if (!right) return NULL;

        left = (op == '+') ? _ADD(left, right)
                           : _SUB(left, right);
        skipSpaces();
    }
    return left;
}

//------------------------------------------------------------------------------
//  POW {['*', '/'] POW}*
//------------------------------------------------------------------------------
static Node* parseMulDiv()
{
    Node* left = parsePow();
    if (!left) return nullptr;

    skipSpaces();
    while (*cur == '*' || *cur == '/') 
    {
        char op = *cur++;
        Node* right = parsePow();
        if (!right) return nullptr;

        left = (op == '*') ? _MUL(left, right)
                           : _DIV(left, right);
        skipSpaces();
    }
    return left;
}

//------------------------------------------------------------------------------
//  FUNC {['^'] FUNC}*
//------------------------------------------------------------------------------
static Node* parsePow()
{
    Node* left = parseFunc();
    if (!left) return nullptr;

    skipSpaces();

    while (*cur == '^') 
    {
        ++cur; // skip '^'
        Node* right = parseFunc();
        if (!right) return nullptr;
        left = _POW(left, right);
        skipSpaces();
    }
    return left;
}

//------------------------------------------------------------------------------
//  FUNC     ::= FUNC '(' ADD_SUB ')' | EXPR
//------------------------------------------------------------------------------
static Node* parseFunc() 
{
    skipSpaces();

    const char *start = cur;

    char buf[8] = {0};      
    size_t len = 0;
    while (isalpha(*cur) && len < sizeof(buf)-1) 
    {
        buf[len++] = *cur++;
    }
    buf[len] = '\0';

    if (len > 0 && *cur == '(') 
    {
        ++cur; // skip '('
        Node* inside = parseAddSub();
        skipSpaces();
        if (*cur != ')') 
        {
            fprintf(stderr, RED"parseTrig(): expected ')' after function arg\n"RESET);
            return nullptr;
        }
        ++cur; // skip ')'
        return makeFunc(buf, inside);
    }

    cur = start;
    return parseExpr();
}

//------------------------------------------------------------------------------
//  EXPR     ::= '(' ADD_SUB ')' | ARG
//------------------------------------------------------------------------------
static Node* parseExpr() 
{
    skipSpaces();

    if (*cur == '(') 
    {
        ++cur; // skip '('
        Node* inside = parseAddSub(); 
        skipSpaces();
        if (*cur == ')')
            ++cur; // skip ')'
        else
            fprintf(stderr, RED "Syntax error: expected ')' before '%s'\n" RESET, cur);
        
        return inside;
    }
    return parseArg();
}

//------------------------------------------------------------------------------
//  ARG      ::= NUM | VAR
//------------------------------------------------------------------------------
static Node* parseArg() 
{
    if      (isdigit(*cur)) {return parceNum();}
    else if (isalpha(*cur)) {return parceVar();}

    fprintf(stderr, RED"Syntax error: expected number or variable at '%s'\n"RESET, cur);
    return nullptr;
}

//------------------------------------------------------------------------------
//  ['a'-'z''A'-'Z']*
//------------------------------------------------------------------------------
static Node* parceVar()
{
    char var = *cur;
    while (isalpha(*cur)) ++cur;
    return _VAR(var);
}

//------------------------------------------------------------------------------
//  ['0'-'9']+
//------------------------------------------------------------------------------
static Node* parceNum()
{
    double value = 0;
    while (isdigit(*cur)) 
    {
        value = value * 10 + (*cur - '0');
        ++cur;
    }
    return _NUM(value);
}

#undef FUNC_LIST