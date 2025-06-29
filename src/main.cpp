#include <stdio.h>
#include <myLib.hpp>
#include "../headers/tree.hpp"
#include "../headers/DSL.hpp"
#include "../headers/simplify.hpp"
#include "../headers/read.hpp"
#include "../headers/diff.hpp"

int main()
{
    //Node* root = _ADD(_ADD(_LN(_NUM(3)), _COS(_NUM(3))), _TG(_VAR('x')));
    //Node* root = _TG(_VAR('x'));
    //Node* root = _D_ADD(_NUM(1), _VAR('x'));

    //Node* root = _MUL(_LN(_VAR('x')), _MUL(_NUM(10), _VAR('x')));
    //Node* root = _MUL(_POW(_NUM(3.1415), _NUM(2)), _POW(_NUM(2.71), _VAR('x')));
    Node* root = read();
    
    //root = diff(root);

    //simplify(root);  // УПРАЩЕНИЕ ДЕРЕВА
    
    //dumpGraph(root); // ГРАФИЧЕСКИЙ dump
    //dumpPrint(root); // КОНСОЛЬНЫЙ  dump
    //dumpTex  (root); // ТЕХОВСКИЙ   dump

    dtorTree(root);
    SUCCESS;
    return 0;
}