#include "tree.h"

Node* newNode(Types type, value_t value, Node* left, Node* right)
{
    assert(type); 
    if (type >= NUMBER_OF_TYPES) assert(false);
    if (type == TYPE_OPERATION) 
    {
        if (value >= NUMBER_OF_OPERATION && value != OPERATION_NIL) 
        assert(false);
    }

    Node* node = (Node*)calloc(1, sizeof(Node));
    node->type = type;
    node->value = value;
    node->left = left;
    node->right = right;

    return node;
}

void dtorTree(Node* node)
{
    assert(node);

    if (node->left)  
    {
        dtorTree(node->left);
        node->left = NULL;
    }
    if (node->right) 
    {
        dtorTree(node->right);
        node->right = NULL;
    }    
    deleteNode(node);
}

void deleteNode(Node* node) 
{
    if (!node) 
    {
        printf(RED "The node is not deleted\n" RESET); 
        return;
    }

    node->type  = (Types)0;
    node->value = 0;
    
    assert(node->left == NULL);
    assert(node->right == NULL);

    FREE(node);
}

void dumpGraph(Node* node)   
{
    assert(node);
    const char* dumpFileName = "dumpTree.gv";
    FILE* dumpTreeFile = fopen(dumpFileName, "wb");
    assert(dumpTreeFile);

    fprintf(dumpTreeFile, "digraph\n");
    fprintf(dumpTreeFile, "{\n    ");
    fprintf(dumpTreeFile, "node [ style = filled, fontcolor=darkblue, fillcolor=peachpuff, color=\"#252A34\", penwidth = 2.5 ];\n    ");
    fprintf(dumpTreeFile, "bgcolor = \"lemonchiffon\";\n\n"); 

    dumpListNodes(node, dumpTreeFile);
    dumpConnectNodes(node, dumpTreeFile);
    
    fprintf(dumpTreeFile, "\n}\n");

    FCLOSE(dumpTreeFile);
    system("dot dumpTree.gv -Tpng -o graphTree.png");
}

void dumpPrint(Node* node)
{
    print(node);
    putchar('\n');
}

void dumpConnectNodes(Node* node, FILE* dumpTreeFile)
{
    assert(dumpTreeFile);
    if (!node) return;

    static int flag = 0;

    if (node->left)
    {
        fprintf(dumpTreeFile, "    node_%p -> node_%p ", node, node->left);
        dumpConnectNodes(node->left, dumpTreeFile);
    }

    if (node->right)
    {
        fprintf(dumpTreeFile, "    node_%p -> node_%p", node, node->right);
        dumpConnectNodes(node->right, dumpTreeFile);
    }

    if (flag) {fprintf(dumpTreeFile, ";"), flag++;}
}

void dumpListNodes(Node* node, FILE* dumpTreeFile)
{
    assert(dumpTreeFile);

    if(!node) return;

    if (node->type == TYPE_NUMBER)
    {
        fprintf(dumpTreeFile, "    node_%p [shape=Mrecord; style = filled; fillcolor = palegreen; color = \"#000000\"; fontcolor = \"#000000\";  label=\" {NUMBER ( %lg )| addr: %llX | type: %d| value: %lg | {left: %llX | right: %llX}} \"];\n",
                                    node, node->value, (size_t)node, node->type, node->value, (size_t)node->left, (size_t)node->right);                                                                                                   
    }
    if (node->type == TYPE_VARIABLE)
    {   
        fprintf(dumpTreeFile, "    node_%p [shape=Mrecord; style = filled; fillcolor = cornflowerblue; color = \"#000000\"; fontcolor = \"#000000\";  label=\" {VARIABLE ( %c )| addr: %llX | type: %d| value: %lg | {left: %llX | right: %llX}} \"];\n",
                                    node, (char)node->value, (size_t)node, node->type, node->value, (size_t)node->left, (size_t)node->right);                                                                                                                
    }
    if (node->type == TYPE_OPERATION)
    {
        switch ((int)node->value)
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

void dumpTex(Node* root)
{
    assert(root);
    FILE* dumpTexFile = fopen(DUMPTEX_FILE_NAME, "w");
    printHeadTex(dumpTexFile);
    
    fprintf(dumpTexFile, "$f=qwerty$\n");

    printfEndTex(dumpTexFile);
}

void printHeadTex(FILE* file)
{
    assert(file);
    fprintf(file, "\\documentclass[a4paper,12pt]{article}\n" 
                  "\\begin{document}\n");
}

void printfEndTex(FILE* file)
{
    assert(file);
    fprintf(file, "\\end{document}\n");
    FCLOSE(file);
    system("pdflatex -output-directory=dumpLatex dumpTex.tex");
}

void print(Node* node)
{
    assert(node);

    printf("%s( %s", BLUE, RESET);

    if (node->left)  print(node->left);
    //__INFIX_FORM____________________________________________________________________
    if (node->type == TYPE_OPERATION)
    {  
        switch ((int)node->value)
        {
            case OPERATION_ADD:
            {
                casePrintOperation(node, "+");
                break;
            }
            case OPERATION_SUB:
            {
                casePrintOperation(node, "-");
                break;
            }
            case OPERATION_MUL:
            {
                casePrintOperation(node, "*");
                break;
            }
            case OPERATION_DIV:
            {
                casePrintOperation(node, "/");
                break;
            }
            case OPERATION_POW:
            {
                casePrintOperation(node, "^");
                break;
            }
            case OPERATION_LOG:
            {
                casePrintOperation(node, "log");
                break;
            }
            case OPERATION_ROOT:
            {
                casePrintOperation(node, "root");
                break;
            }
            case OPERATION_SIN:
            {
                casePrintOperation(node, "sin");
                break;
            }
            case OPERATION_COS:
            {
                casePrintOperation(node, "cos");
                break;
            }
            case OPERATION_LN:
            {
                casePrintOperation(node, "ln");
                break;
            }
            case OPERATION_SQRT:
            {
                casePrintOperation(node, "sqrt");
                break;
            }
            default:
            {
                printf("%s problem with function print%s\n", RED, RESET);
                break;
            }
        }
    }
    else if (node->type == TYPE_VARIABLE)
    {
        printf("%s%c%s", YELLOW, (int)node->value, RESET);
    }
    else if (node->type == TYPE_NUMBER) printf("%s%lg%s", GREEN, node->value, RESET);
    else printf("%sERROR IN FUN PRINT%s\n", RED, RESET);
    //__INFIX_FORM_____________________________________________________________________
    if (node->right) print(node->right);
    
    printf("%s )%s", BLUE, RESET);
}

Node* copy(Node* node)
{
    if(!node) return NULL;
    Node* n = newNode(node->type, node->value, copy(node->left), copy(node->right));
    return n;
}

void caseOperation(Node* node, const char* operation, FILE* dumpTreeFile)
{
    assert(node);
    assert(operation);
    assert(dumpTreeFile);

    fprintf(dumpTreeFile, "node_%p [shape=Mrecord; style = filled; fillcolor=plum; color = \"#000000\"; fontcolor = \"#000000\";"
                          "label=\" {OPERATION ( %s ) | addr: %llX | type: %d | value: %lg | {left: %llX | right: %llX}} \"];\n", 
                                node, operation, (size_t)node, node->type, node->value, (size_t)node->left, (size_t)node->right
           );                                                                                                          
}

void casePrintOperation(Node* node, const char* operation)
{
    assert(node);
    assert(operation);
    printf(MANG "%s" RESET, operation);
}
