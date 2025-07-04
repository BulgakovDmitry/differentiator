#include <stdio.h>
#include <myLib.hpp>
#include "../headers/tree.hpp"
#include "../headers/DSL.hpp"
#include "../headers/simplify.hpp"
#include "../headers/read.hpp"
#include "../headers/diff.hpp"
#include "../headers/graphDump.hpp"
#include "../headers/consoleDump.hpp"
#include "../headers/texDump.hpp"

extern const char* const HTML_FILE_NAME; //xdg-open /home/user/Desktop/differentiator/dumpGraph/htmlDumpFile.html
extern const char* const TEX_FILE_NAME;
extern const char* const EXPRESSION_FILE;

int main()
{
    FILE* htmlFile = fopen(HTML_FILE_NAME, "w");
    ASSERT(htmlFile, "htmlFile = nullptr", stderr);

    FILE* texFile = fopen(TEX_FILE_NAME, "w=");
    ASSERT(texFile, "texFile = nullptr", stderr);

    FILE* expressionFile = fopen(EXPRESSION_FILE, "rb");
    ASSERT(expressionFile, "expressionFile = nullptr, impossible to read the math expression", stderr);

    Node* root = readExpression(expressionFile);
    ASSERT(root, "root = nullptr, could not be read", stderr);

    size_t countRoot = 0;
    Node* rootSimpl = simplify(copy(root), &countRoot);
    
    Node* deriv = diff(rootSimpl);
    
    size_t countDeriv = 0;
    Node* derivSimpl = simplify(copy(deriv), &countDeriv);
    
    dumpGraph(root, deriv, rootSimpl, derivSimpl, htmlFile);
    dumpTex(root, deriv, rootSimpl, derivSimpl, countRoot, countDeriv, texFile);
    
    dumpConsole(root, "root");
    dumpConsole(derivSimpl, "derivSimpl");
    
    dtorTree(root);
    dtorTree(rootSimpl);
    dtorTree(deriv);
    dtorTree(derivSimpl);

    FCLOSE(htmlFile);
    FCLOSE(texFile);    
    FCLOSE(expressionFile);

    return 0;
}