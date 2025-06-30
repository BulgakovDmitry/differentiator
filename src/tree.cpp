#include "../headers/tree.hpp"

Node* newNode(Types type, Value_t value, Node* left, Node* right)
{
    Node* node = (Node*)calloc(1, sizeof(Node));
    if (!node)
    {
        fprintf(stderr, RED"ERROR: Calloc returned nullptr in newNode()\n"RESET);
        return nullptr;
    }

    if (type >= NUMBER_OF_TYPES) 
    {
        fprintf(stderr, RED"ERROR: type >= NUMBER_OF_TYPES\n"RESET);
        return nullptr;
    }

    if (type == TYPE_OPERATION) 
    {
        if (value.op >= NUMBER_OF_OPERATION && value.op != OPERATION_NIL) 
            assert(false);
    }

    node->type  = type;
    node->value = value;
    node->left  = left;
    node->right = right;

    return node;
}

void dtorTree(Node* node)
{
    if (!node) 
    {
        fprintf(stderr, RED "node == nullptr\n" RESET); 
        return;
    }

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
        fprintf(stderr, RED "The node is not deleted\n" RESET); 
        return;
    }

    node->type  = (Types)0;
    node->value.num = 0;
    node->value.op = 0;
    node->value.var = 0;

    assert(node->left  == NULL);
    assert(node->right == NULL);

    FREE(node);
}

void dumpPrint(Node* node)
{
    print(node);
    putchar('\n');
}

void dumpTex(Node* root)
{
    assert(root);
    FILE* dumpTexFile = fopen(DUMPTEX_FILE_NAME, "w");
    printHeadTex(dumpTexFile);
    
    fprintf(dumpTexFile, "\\[");
    generateTex(root, dumpTexFile);
    fprintf(dumpTexFile, "\\]");

    printfEndTex(dumpTexFile);
}

void generateTex(Node* node, FILE* file)
{
    assert(node);
    assert(file);


    switch ((int)node->type)
    {
        case TYPE_OPERATION:
        {
            switch ((int)node->value.op)
            {
                case OPERATION_ADD:
                {
                    fprintf(file, "(");
                    generateTex(node->left, file);
                    fprintf(file, " + ");
                    generateTex(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_SUB:
                {
                    fprintf(file, "(");
                    generateTex(node->left, file);
                    fprintf(file, " - ");
                    generateTex(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_MUL:
                {
                    fprintf(file, "(");
                    generateTex(node->left, file);

                    fprintf(file, " \\cdot ");

                    generateTex(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_DIV:
                {
                    fprintf(file, "\\frac{");
                    generateTex(node->left, file);
                    fprintf(file, "}{");
                    generateTex(node->right, file);
                    fprintf(file, "}");
                    break;
                }
                case OPERATION_LN:
                {
                    fprintf(file, "ln( ");
                    generateTex(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_SIN:
                {
                    fprintf(file, "sin( ");
                    generateTex(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_COS:
                {
                    fprintf(file, "cos( ");
                    generateTex(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_TG:
                {
                    fprintf(file, "tg( ");
                    generateTex(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_POW:
                {
                    fprintf(file, "(");
                    generateTex(node->left, file);
                    fprintf(file, ")");

                    fprintf(file, "^{");
                    generateTex(node->right, file);
                    fprintf(file, "}");
                    break;
                }
                default:
                {
                    printf(RED "ERROR IN FUNCTION generateTex (1)\n" RESET);\
                    abort();
                }
            }
            break;
        }  
        case TYPE_NUMBER:
        {
            fprintf(file, "%lg", node->value);
            break;
        } 
        case TYPE_VARIABLE:
        {
            fprintf(file, "%c", (char)node->value.var);
            break;
        }
        default: 
        {
            printf(RED "ERROR IN FUNCTION generateTex (2)\n" RESET);\
            abort();
        }
    }
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
        switch ((int)node->value.op)
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
            case OPERATION_TG:
            {
                casePrintOperation(node, "tg");
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
        printf("%s%c%s", YELLOW, (int)node->value.var, RESET);
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

void casePrintOperation(Node* node, const char* operation)
{
    assert(node);
    assert(operation);
    printf(MANG "%s" RESET, operation);
}
