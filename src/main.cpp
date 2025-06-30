#include <stdio.h>
#include <myLib.hpp>
#include "../headers/tree.hpp"
#include "../headers/DSL.hpp"
#include "../headers/simplify.hpp"
#include "../headers/read.hpp"
#include "../headers/diff.hpp"
#include "../headers/graphDump.hpp"
#include "../headers/consoleDump.hpp"

extern const char* const HTML_FILE_NAME = "dump/htmlDumpFile"; //xdg-open /home/user/Desktop/differentiator/dump/htmlDumpFile
extern const char* const TEX_FILE_NAME  = "dump/texDumpFile";

int main()
{
    FILE* htmlFile = fopen(HTML_FILE_NAME, "w");
    ASSERT(htmlFile, "htmlFile = nullptr", stderr);

    FILE* texFile = fopen(TEX_FILE_NAME, "w");
    ASSERT(texFile, "texFile = nullptr", stderr);

    Node* root = _ADD(_MUL(_NUM(0), _VAR('x')), _POW(_ADD(_VAR('x'), _NUM(1)), _NUM(2)));
    Node* rootWithConstFolding = constFolding(copy(root));
    Node* rootOpt = optimization(copy(root));
    //Node* root = _MUL(_NUM(5), _VAR('x'));


    //Node* root = read();
    
    Node* deriv = diff(root);
    Node* derivWithConstFolding = constFolding(copy(deriv));
    Node* derivOpt = optimization(copy(deriv));
    
    dumpGraphBegin(htmlFile);
    
    dumpGraph(root , "root" , htmlFile);  
    dumpGraph(rootWithConstFolding , "rootWithConstFolding" , htmlFile);   
    dumpGraph(rootOpt , "rootOpt" , htmlFile);  

    dumpGraph(deriv, "deriv", htmlFile);  
    dumpGraph(derivWithConstFolding, "derivWithConstFolding", htmlFile);   
    dumpGraph(derivOpt, "derivOpt", htmlFile);  

    
    dumpGraphEnd(htmlFile);
    
    //dumpConsole(root, "root");
    //dumpConsole(deriv, "deriv");

    //simplify(root);  // УПРАЩЕНИЕ ДЕРЕВА
    
    //dumpTex  (root); // ТЕХОВСКИЙ   dump

    dtorTree(root);
    dtorTree(rootWithConstFolding);
    dtorTree(rootOpt);

    dtorTree(deriv);
    dtorTree(derivWithConstFolding);
    dtorTree(derivOpt);

    FCLOSE(htmlFile);
    FCLOSE(texFile);    
                    
    return 0;
}