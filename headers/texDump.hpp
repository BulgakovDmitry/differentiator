#ifndef TEX_DUMP_HPP
#define TEX_DUMP_HPP

#include "tree.hpp"

const char* const PDFLATEX_LOG  = "dumpLatex/pdflatex.log";
const char* const TEX_FILE_NAME = "dumpLatex/dumpTex.tex"; 

void dumpTex(Node* root, Node* deriv, Node* rootSimpl, Node* derivSimpl, size_t countRoot, size_t countDeriv, FILE* tex);                

#endif