#include "../headers/graphDump.hpp"
#include "../headers/simplify.hpp"

extern const char* const DUMP_FILE_GV   = "dumpGraph/dumpTree.gv";

static void dumpGraphSubTree(Node* node, const char* filePrefix, FILE* html);            
static void dumpGraphBegin  (FILE* html);
static void dumpGraphEnd    (FILE* html);

static void dumpConnectNodes(Node* node, FILE* dumpTreeFile);
static void dumpListNodes   (Node* node, FILE* dumpTreeFile);
static void caseOperation   (Node* node, const char* operation, FILE* dumpTreeFile);
 
void dumpGraph(Node* root, Node* deriv, Node* rootSimpl, Node* derivSimpl, FILE* html)
{
    ASSERT(root,       "root = nullptr",       stderr);
    ASSERT(deriv,      "deriv = nullptr",      stderr);
    ASSERT(rootSimpl,  "rootSimpl = nullptr",  stderr);
    ASSERT(derivSimpl, "derivSimpl = nullptr", stderr);
    ASSERT(html,       "html = nullptr",       stderr);


    dumpGraphBegin(html);

    dumpGraphSubTree(root,       ROOT_NAME,        html);         
    dumpGraphSubTree(rootSimpl,  ROOT_SIMPL_NAME,  html);                                    
    dumpGraphSubTree(deriv,      DERIV_NAME,       html);                   
    dumpGraphSubTree(derivSimpl, DERIV_SIMPL_NAME, html);         
                                                           
    dumpGraphEnd(html);
}

static void dumpGraphSubTree(Node* node, const char* filePrefix, FILE* html)
{
    ASSERT(node,       "node = nullptr",       stderr);
    ASSERT(filePrefix, "filePrefix = nullptr", stderr);
    ASSERT(html,       "html = nullptr",       stderr);

    char gvPath [MAX_NAME_FILE_LEN] = "";
    char pngPath[MAX_NAME_FILE_LEN] = "";

    snprintf(gvPath,  sizeof(gvPath),  "dumpGraph/%s.gv",  filePrefix);
    snprintf(pngPath, sizeof(pngPath), "dumpGraph/%s.png", filePrefix);

    FILE* gv = fopen(gvPath, "wb");
    ASSERT(gv, "dumpGraph fopen", stderr);

    fprintf(gv, "digraph G {\n");
    fprintf(gv, "    node [style=filled, fontcolor=darkblue,"
                " fillcolor=peachpuff, color=\"#252A34\", penwidth=2.5];\n");
    fprintf(gv, "    bgcolor=\"lemonchiffon\";\n\n");

    dumpListNodes(node, gv);
    dumpConnectNodes(node, gv);
    fprintf(gv, "}\n");

    FCLOSE(gv);

    char cmd[2 * MAX_NAME_FILE_LEN + EXTRA_SPACE] = "";
    snprintf(cmd, sizeof(cmd), "dot %s -Tpng -o %s", gvPath, pngPath);
    system(cmd);

    fprintf(html,
        "<div class=\"pair\">"
        "<img src=\"%s.png\" alt=\"%s\">"
        "<span>it's %s</span>"
        "</div>\n",
        filePrefix, filePrefix, filePrefix);
}

static void dumpGraphBegin(FILE* html)
{
    ASSERT(html, "html = nullptr", stderr);

    fprintf(html,
        "<!doctype html>\n<html><head><meta charset=\"utf-8\">"
        "<style>"
        " body        {background:#000; color:#eee; margin:0; padding:30px;"
        "              font-family:Arial,Helvetica,sans-serif;}"
        " .pair       {display:flex; align-items:center; gap:40px;"
        "              margin-bottom:50px;}"
        " .pair img   {width:600px; border:2px solid #555;}"
        " .pair span  {font:26px/1.3 Arial,sans-serif; font-weight:700;"
        "              color:#00ff5b; white-space:nowrap;}"
        "</style></head><body>\n");
}

static void dumpGraphEnd(FILE* html)
{
    ASSERT(html, "html = nullptr", stderr);
    fprintf(html, "</body></html>\n");
}

static void dumpConnectNodes(Node* node, FILE* dumpTreeFile)
{
    ASSERT(node, "node = nullptr", stderr);
    ASSERT(dumpTreeFile, "dumpTreeFile = nullptr", stderr);
    
    if (!node) return;
    
    if (node->left)  
    { 
        fprintf(dumpTreeFile, "    node_%p -> node_%p;\n", node, node->left);  
        dumpConnectNodes(node->left, dumpTreeFile); 
    }

    if (node->right) 
    { 
        fprintf(dumpTreeFile, "    node_%p -> node_%p;\n", node, node->right); 
        dumpConnectNodes(node->right, dumpTreeFile); 
    }
}

static void dumpListNodes(Node* node, FILE* dumpTreeFile)
{
    ASSERT(node, "node = nullptr", stderr);
    ASSERT(dumpTreeFile, "dumpTreeFile = nullptr", stderr);

    if(!node) return;

    if (node->type == TYPE_NUMBER)
    {
        fprintf(dumpTreeFile,
            "    node_%p [shape=Mrecord; style = filled; fillcolor = palegreen;"
            " color = \"#000000\"; fontcolor = \"#000000\";  label=\" "
            " {NUMBER ( %lg )| addr: %llX | type: %d| value: %lg | {left: %llX | right: %llX}} \"];\n",
                        node, node->value.num, (long long unsigned int)node, (int)node->type, node->value.num,
                        (long long unsigned int)node->left, (long long unsigned int)node->right);                                                                                                   
    }
    if (node->type == TYPE_VARIABLE)
    {   
        fprintf(dumpTreeFile,
            "    node_%p [shape=Mrecord; style = filled; fillcolor = cornflowerblue;"
            " color = \"#000000\"; fontcolor = \"#000000\";  label=\" "
            " {VARIABLE ( %c )| addr: %llX | type: %d| value: %c | {left: %llX | right: %llX}} \"];\n",
                        node, node->value.var, (long long unsigned int)node, (int)node->type, node->value.var, 
                        (long long unsigned int)node->left, (long long unsigned int)node->right);                                                                                                                
    }
    if (node->type == TYPE_OPERATION)
    {
        switch (node->value.op)
        {
            case OPERATION_ADD:
            {
                caseOperation(node, "+", dumpTreeFile);
                break;     
            }
            case OPERATION_SUB:
            {
                caseOperation(node, "-", dumpTreeFile);
                break;                   
            }
            case OPERATION_MUL:
            {
                caseOperation(node, "*", dumpTreeFile);
                break;                          
            }
            case OPERATION_DIV:
            {
                caseOperation(node, "/", dumpTreeFile);
                break;    
            }
            case OPERATION_POW:
            {
                caseOperation(node, "^", dumpTreeFile);
                break;    
            }
            case OPERATION_NEG:
            {
                caseOperation(node, "-", dumpTreeFile);
                break;
            }
            case OPERATION_SQRT:
            {
                caseOperation(node, "sqrt", dumpTreeFile);
                break;    
            }
            case OPERATION_SIN:
            {
                caseOperation(node, "sin", dumpTreeFile);
                break;    
            }
            case OPERATION_COS:
            {
                caseOperation(node, "cos", dumpTreeFile);
                break;    
            }
            case OPERATION_TG:
            {
                caseOperation(node, "tg", dumpTreeFile);
                break;    
            }
            case OPERATION_CTG:
            {
                caseOperation(node, "ctg", dumpTreeFile);
                break;  
            }
            case OPERATION_ARCSIN:
            {
                caseOperation(node, "arcsin", dumpTreeFile);
                break;  
            }
            case OPERATION_ARCCOS:
            {
                caseOperation(node, "arccos", dumpTreeFile);
                break;  
            }
            case OPERATION_ARCTG:
            {
                caseOperation(node, "arctg", dumpTreeFile);
                break;  
            }
            case OPERATION_ARCCTG:
            {
                caseOperation(node, "arctg", dumpTreeFile);
                break;  
            }
            case OPERATION_SH:
            {
                caseOperation(node, "sh", dumpTreeFile);
                break;  
            }
            case OPERATION_CH:
            {
                caseOperation(node, "ch", dumpTreeFile);
                break;  
            }
            case OPERATION_TH:
            {
                caseOperation(node, "th", dumpTreeFile);
                break;  
            }
            case OPERATION_CTH:
            {
                caseOperation(node, "cth", dumpTreeFile);
                break;  
            }
            case OPERATION_LN:
            {
                caseOperation(node, "ln", dumpTreeFile);
                break;    
            }
            default:
            {
                printf(RED "ERROR IN DUMP \n" RESET);
                break;
            }
        }                                                                                      
    }
    
    if (node->left)  dumpListNodes(node->left,  dumpTreeFile);
    if (node->right) dumpListNodes(node->right, dumpTreeFile);
}

static void caseOperation(Node* node, const char* operation, FILE* dumpTreeFile)
{
    ASSERT(node,         "node = nullptr",         stderr);
    ASSERT(operation,    "operation = nullptr",    stderr);
    ASSERT(dumpTreeFile, "dumpTreeFile = nullptr", stderr);

    fprintf(dumpTreeFile, 
        "node_%p [shape=Mrecord; style = filled; fillcolor=plum; color = \"#000000\"; fontcolor = \"#000000\";"
        "label=\" {OPERATION ( %s ) | addr: %llX | type: %d | value: %d | {left: %llX | right: %llX}} \"];\n", 
                node, operation, (long long unsigned int)node, node->type, node->value.op, 
                (long long unsigned int)node->left, (long long unsigned int)node->right);                                                                                                          
}