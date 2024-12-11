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
                CASE_OPERATION("+");     
            }
            case OPERATION_SUB:
            {
                CASE_OPERATION("-")                        
            }
            case OPERATION_MUL:
            {
                CASE_OPERATION("*")                         
            }
            case OPERATION_DIV:
            {
                CASE_OPERATION("/");
            }
            case OPERATION_POW:
            {
                CASE_OPERATION("^");
            }
            case OPERATION_LOG:
            {
                CASE_OPERATION("log");
            }
            case OPERATION_ROOT:
            {
                CASE_OPERATION("root");
            }
            case OPERATION_SIN:
            {
                CASE_OPERATION("sin");
            }
            case OPERATION_COS:
            {
                CASE_OPERATION("cos");
            }
            case OPERATION_LN:
            {
                CASE_OPERATION("ln");
            }
            case OPERATION_SQRT:
            {
                CASE_OPERATION("sqrt");
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
                CASE_PRINT_OPERATION("+");
            }
            case OPERATION_SUB:
            {
                CASE_PRINT_OPERATION("-");
            }
            case OPERATION_MUL:
            {
                CASE_PRINT_OPERATION("*");
            }
            case OPERATION_DIV:
            {
                CASE_PRINT_OPERATION("/");
            }
            case OPERATION_POW:
            {
                CASE_PRINT_OPERATION("^");
            }
            case OPERATION_LOG:
            {
                CASE_PRINT_OPERATION("log");
            }
            case OPERATION_ROOT:
            {
                CASE_PRINT_OPERATION("root");
            }
            case OPERATION_SIN:
            {
                CASE_PRINT_OPERATION("sin");
            }
            case OPERATION_COS:
            {
                CASE_PRINT_OPERATION("cos");
            }
            case OPERATION_LN:
            {
                CASE_PRINT_OPERATION("ln");
            }
            case OPERATION_SQRT:
            {
                CASE_PRINT_OPERATION("sqrt");
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