#include "../headers/consoleDump.hpp"

static void casePrintOperation(const char* operation); 
static void print(Node* node);

void dumpConsole(Node* node, const char* prefix)
{
    ASSERT(node, "node = nullptr", stderr);
    ASSERT(prefix, "prefix = nullptr", stderr);

    printf(RED"__________CONSOLE_DUMP_%s________________________________________\n"RESET, prefix);
    print(node);
    putchar('\n');
}

static void print(Node* node)
{
    ASSERT(node, "node = nullptr", stderr);

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
            case OPERATION_LOG:
            {
                casePrintOperation("log");
                break;
            }
            case OPERATION_ROOT:
            {
                casePrintOperation("root");
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
            case OPERATION_LN:
            {
                casePrintOperation("ln");
                break;
            }
            case OPERATION_SQRT:
            {
                casePrintOperation("sqrt");
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
    
    printf("%s )%s", BLUE, RESET);
}

static void casePrintOperation(const char* operation)
{
    ASSERT(operation, "null operation", stderr);
    printf(MANG"%s"RESET, operation);
}