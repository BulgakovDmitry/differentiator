#include "../headers/graphDump.hpp"

extern const char* const DUMP_FILE_GV   = "dump/dumpTree.gv";

void dumpGraph(Node* node, const char* filePrefix, FILE* html)
{
    char gvPath [MAX_NAME_FILE_LEN] = "";
    char pngPath[MAX_NAME_FILE_LEN] = "";

    snprintf(gvPath,  sizeof(gvPath),  "dump/%s.gv",  filePrefix);
    snprintf(pngPath, sizeof(pngPath), "dump/%s.png", filePrefix);

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

    char cmd[2 * MAX_NAME_FILE_LEN] = "";
    snprintf(cmd, sizeof(cmd), "dot %s -Tpng -o %s", gvPath, pngPath);
    system(cmd);

    fprintf(html,
        "<div class=\"pair\">"
        "<img src=\"%s.png\" alt=\"%s\">"
        "<span>это %s</span>"
        "</div>\n",
        filePrefix, filePrefix, filePrefix);
}

void dumpGraphBegin(FILE* html)
{
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

void dumpGraphEnd(FILE* html)
{
    fprintf(html, "</body></html>\n");
}

void dumpConnectNodes(Node* node, FILE* dumpTreeFile)
{
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

void dumpListNodes(Node* node, FILE* dumpTreeFile)
{
    assert(dumpTreeFile);

    if(!node) return;

    if (node->type == TYPE_NUMBER)
    {
        fprintf(dumpTreeFile,
            "    node_%p [shape=Mrecord; style = filled; fillcolor = palegreen;"
            " color = \"#000000\"; fontcolor = \"#000000\";  label=\" "
            " {NUMBER ( %lg )| addr: %llX | type: %d| value: %lg | {left: %llX | right: %llX}} \"];\n",
                        node, node->value.num, (size_t)node, node->type, node->value.num,
                        (size_t)node->left, (size_t)node->right);                                                                                                   
    }
    if (node->type == TYPE_VARIABLE)
    {   
        fprintf(dumpTreeFile,
            "    node_%p [shape=Mrecord; style = filled; fillcolor = cornflowerblue;"
            " color = \"#000000\"; fontcolor = \"#000000\";  label=\" "
            " {VARIABLE ( %c )| addr: %llX | type: %d| value: %lg | {left: %llX | right: %llX}} \"];\n",
                        node, (char)node->value.var, (size_t)node, node->type, node->value.var, 
                        (size_t)node->left, (size_t)node->right);                                                                                                                
    }
    if (node->type == TYPE_OPERATION)
    {
        switch ((int)node->value.op)
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
            case OPERATION_LOG:
            {
                caseOperation(node, "log", dumpTreeFile);
                break;    
            }
            case OPERATION_ROOT:
            {
                caseOperation(node, "root", dumpTreeFile);
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
            case OPERATION_LN:
            {
                caseOperation(node, "ln", dumpTreeFile);
                break;    
            }
            case OPERATION_SQRT:
            {
                caseOperation(node, "sqrt", dumpTreeFile);
                break;    
            }
            default:
            {
                printf(RED "ERROR IN DUMP \n" RESET);
                break;
            }
        }                                                                                      
    }
    
    if (node->left)  dumpListNodes(node->left, dumpTreeFile);
    if (node->right) dumpListNodes(node->right, dumpTreeFile);
}

void caseOperation(Node* node, const char* operation, FILE* dumpTreeFile)
{
    assert(node);
    assert(operation);
    assert(dumpTreeFile);

    fprintf(dumpTreeFile, 
        "node_%p [shape=Mrecord; style = filled; fillcolor=plum; color = \"#000000\"; fontcolor = \"#000000\";"
        "label=\" {OPERATION ( %s ) | addr: %llX | type: %d | value: %lg | {left: %llX | right: %llX}} \"];\n", 
                node, operation, (size_t)node, node->type, node->value.op, (size_t)node->left, (size_t)node->right);                                                                                                          
}