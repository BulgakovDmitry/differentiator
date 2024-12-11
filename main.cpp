#include <stdio.h>
#include "myLib.h"
#include "tree.h"
#include "DSL.h"
#include "simplify.h"
#include "read.h"
#include "diff.h"

int main()
{
    Node* root = _ADD(_MUL(_NUM(6), _VAR('x')), _LOG(_NUM(7), _VAR('x')));
    //Node* root = _POW(_POW(_POW(_POW(_POW(_VAR('q'), _VAR('q')), _VAR('q')), _VAR('q')), _VAR('q')), _VAR('q'));

    //Node* root = Read();
    
    root = diff(root);

    dumpGraph(root); // ГРАФИЧЕСКИЙ dump
    dumpPrint(root); // КОНСОЛЬНЫЙ  dump

    dtorTree(root);
    SUCCESS;
    return 0;
}

// УБРАЛ ENUM VARIABLES
// СДЕЛАЛ РЕК ЧИТАЛКУ
// СДЕЛАЛ ДОФИГА МАКРОСОВ
// НАУЧИЛ ДИФФЕРЕНЦИРОВАТЬ
// ВВЁЛ ФУНКЦИИ