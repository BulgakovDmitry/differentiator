#include <stdio.h>
#include <myLib.hpp>
#include "../headers/tree.hpp"
#include "../headers/DSL.hpp"
#include "../headers/simplify.hpp"
#include "../headers/read.hpp"
#include "../headers/diff.hpp"
#include "../headers/graphDump.hpp"

extern const char* const HTML_FILE_NAME = "dump/htmlDumpFile"; //xdg-open /home/user/Desktop/differentiator/dump/htmlDumpFile
extern const char* const TEX_FILE_NAME  = "dump/texDumpFile";

int main()
{
    FILE* htmlFile = fopen(HTML_FILE_NAME, "w");
    ASSERT(htmlFile, "htmlFile = nullptr", stderr);

    FILE* texFile = fopen(TEX_FILE_NAME, "w");
    ASSERT(texFile, "texFile = nullptr", stderr);

    Node* root = _MUL(_NUM(5), _POW(_ADD(_VAR('x'), _NUM(1)), _NUM(2)));
        
    //Node* root = read();
    
    Node* deriv = diff(root);
    
    dumpGraphBegin(htmlFile);

    dumpGraph(root , "root" , htmlFile);   
    dumpGraph(deriv, "deriv", htmlFile);   

    dumpGraphEnd(htmlFile);
    //simplify(root);  // УПРАЩЕНИЕ ДЕРЕВА
    
    //dumpPrint(root); // КОНСОЛЬНЫЙ  dump
    //dumpTex  (root); // ТЕХОВСКИЙ   dump

    dtorTree(root);
    dtorTree(deriv);

    FCLOSE(htmlFile);
    FCLOSE(texFile);    
                    
    return 0;
}