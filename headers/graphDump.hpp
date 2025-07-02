#ifndef GRAPH_DUMP_HPP
#define GRAPH_DUMP_HPP

#include "tree.hpp"

void dumpGraph(Node* root, Node* deriv, Node* rootSimpl, Node* derivSimpl, FILE* html);

const char* const HTML_FILE_NAME = "dumpGraph/htmlDumpFile.html";

const size_t MAX_NAME_FILE_LEN = 32;
const size_t EXTRA_SPACE       = 15;

const char* const ROOT_NAME        = "root";
const char* const ROOT_SIMPL_NAME  = "rootSimpl";
const char* const DERIV_NAME       = "deriv";
const char* const DERIV_SIMPL_NAME = "derivSimpl";

#endif