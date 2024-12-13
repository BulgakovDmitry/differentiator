#include <stdio.h>
#include <myLib.h>
#include "tree.h"
#include "DSL.h"
#include "simplify.h"
#include "read.h"
#include "diff.h"

int main()
{
    //Node* root = _POW(_VAR('j'), _NUM(0.5));
    //Node* root = _SIN(_VAR('j'));

    //Node* root = _POW(_POW(_POW(_POW(_POW(_VAR('q'), _VAR('q')), _VAR('q')), _VAR('q')), _VAR('q')), _VAR('q'));

    Node* root = read();
    
    root = diff(root);

    simplify(root);  // УПРАЩЕНИЕ ДЕРЕВА
    
    dumpGraph(root); // ГРАФИЧЕСКИЙ dump
    dumpPrint(root); // КОНСОЛЬНЫЙ  dump
    dumpTex  (root); // ТЕХОВСКИЙ   dump

    dtorTree(root);
    SUCCESS;
    return 0;
}