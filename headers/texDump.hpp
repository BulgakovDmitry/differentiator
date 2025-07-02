#ifndef TEX_DUMP_HPP
#define TEX_DUMP_HPP

#include "tree.hpp"

const char* const DUMPTEX_FILE_NAME = "dumpLatex/dumpTex.tex";
const char* const TEX_DIR           = "dumpLatex";
const char* const PDFLATEX_LOG      = "dumpLatex/pdflatex.log";

void dumpTex(Node* root, Node* deriv, Node* rootSimpl, Node* derivSimpl, size_t countRoot, size_t counstDeriv);                

#endif