#include "../headers/consoleDump.hpp"

static void casePrintOperation(const char* operation); 
static void print(Node* node);

void dumpConsole(Node* node, const char* prefix)
{
    ASSERT(node, "node = nullptr, impossible to print in consol tree with null root", stderr);
    ASSERT(prefix, "prefix = nullptr, impossible write null text on graph",           stderr);

    printf(RED"__________CONSOLE_DUMP_%s________________________________________\n"RESET, prefix);
    print(node);
    putchar('\n');
}

static void print(Node* node)
{
    ASSERT(node, "node = nullptr, impossible write null text on graph", stderr);

    printf("%s( %s", BLUE, RESET);

    if (node->left)  print(node->left);

    //__INFIX_FORM____________________________________________________________________

    if (node->type == TYPE_OPERATION)
    {  
        switch (node->value.op)
        {
            case OPERATION_ADD:
            {
                casePrintOperation("+");
                break;
            }
            case OPERATION_SUB:
            {
                casePrintOperation("-");
                break;
            }
            case OPERATION_MUL:
            {
                casePrintOperation("*");
                break;
            }
            case OPERATION_DIV:
            {
                casePrintOperation("/");
                break;
            }
            case OPERATION_POW:
            {
                casePrintOperation("^");
                break;
            }
            case OPERATION_NEG:
            {
                casePrintOperation("-");
                break;
            }
            case OPERATION_SQRT:
            {
                casePrintOperation("sqrt");
                break;
            }
            case OPERATION_SIN:
            {
                casePrintOperation("sin");
                break;
            }
            case OPERATION_COS:
            {
                casePrintOperation("cos");
                break;
            }
            case OPERATION_TG:
            {
                casePrintOperation("tg");
                break;
            }
            case OPERATION_CTG:
            {
                casePrintOperation("ctg");
                break;
            }
            case OPERATION_ARCSIN:
            {
                casePrintOperation("arcsin");
                break;
            }
            case OPERATION_ARCCOS:
            {
                casePrintOperation("arccos");
                break;
            }
            case OPERATION_ARCTG:
            {
                casePrintOperation("arctg");
                break;
            }
            case OPERATION_ARCCTG:
            {
                casePrintOperation("arcctg");
                break;
            }
            case OPERATION_SH:
            {
                casePrintOperation("sh");
                break;
            }
            case OPERATION_CH:
            {
                casePrintOperation("ch");
                break;
            }
            case OPERATION_TH:
            {
                casePrintOperation("th");
                break;
            }
            case OPERATION_CTH:
            {
                casePrintOperation("cth");
                break;
            }
            case OPERATION_LN:
            {
                casePrintOperation("ln");
                break;
            }
            default:
            {
                fprintf(stderr, RED"problem with function print\n"RESET);
                break;
            }
        }
    }
    else if (node->type == TYPE_VARIABLE)
        printf(YELLOW"%c"RESET, (int)node->value.var);
    else if (node->type == TYPE_NUMBER) 
        printf(GREEN"%lg"RESET, node->value.num);
    else 
        fprintf(stderr, RED"ERROR IN FUN PRINT, UNDEFINED TYPE\n"RESET);

    //__INFIX_FORM_____________________________________________________________________

    if (node->right) 
        print(node->right);
    
    printf(BLUE" )"RESET);
}

static void casePrintOperation(const char* operation)
{
    ASSERT(operation, "null operation", stderr);
    printf(MANG"%s"RESET, operation);
}