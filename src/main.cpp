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

int main()
{
    FILE* htmlFile = fopen(HTML_FILE_NAME, "w");
    ASSERT(htmlFile, "htmlFile = nullptr", stderr);

    FILE* texFile = fopen(TEX_FILE_NAME, "w=");
    ASSERT(texFile, "texFile = nullptr", stderr);

    Node* root = _ADD(_MUL(_NUM(0), _VAR('x')), _POW(_ADD(_VAR('x'), _NUM(1)), _NUM(2)));
    //Node* root = _MUL(_NUM(5), _VAR('x'));
    //Node* root = _MUL(_VAR('x'), _LN(_VAR('x')));
    //Node* root = _POW(_VAR('x'), _VAR('x'));
    //Node* root = read();
    //Node* root = _ADD(_VAR('x'), _MUL(_NUM(3), _SIN(_VAR('x'))));

    size_t countRoot = 0;
    Node* rootSimpl = simplify(copy(root), &countRoot);
    
    Node* deriv = diff(rootSimpl);
    
    size_t countDeriv = 0;
    Node* derivSimpl = simplify(copy(deriv), &countDeriv);
    
    dumpGraph(root, deriv, rootSimpl, derivSimpl, htmlFile);
    dumpTex(root, deriv, rootSimpl, derivSimpl, countRoot, countDeriv, texFile);
    
    //dumpConsole(root, "root");
    //dumpConsole(deriv, "deriv");
    
    dtorTree(root);
    dtorTree(rootSimpl);
    dtorTree(deriv);
    dtorTree(derivSimpl);

    FCLOSE(htmlFile);
    FCLOSE(texFile);    
    

    return 0;
}