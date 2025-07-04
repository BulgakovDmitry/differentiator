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

#define PRINT_OP(op, str)  case op: casePrintOperation(str); break

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
            PRINT_OP(OPERATION_ADD,   "+");
            PRINT_OP(OPERATION_SUB,   "-");
            PRINT_OP(OPERATION_MUL,   "*");
            PRINT_OP(OPERATION_DIV,   "/");
            PRINT_OP(OPERATION_POW,   "^");
            PRINT_OP(OPERATION_NEG,   "-");

            PRINT_OP(OPERATION_SQRT,  "sqrt");
            PRINT_OP(OPERATION_LN,    "ln");

            PRINT_OP(OPERATION_SIN,   "sin");
            PRINT_OP(OPERATION_COS,   "cos");
            PRINT_OP(OPERATION_TG,    "tg");
            PRINT_OP(OPERATION_CTG,   "ctg");

            PRINT_OP(OPERATION_ARCSIN,"arcsin");
            PRINT_OP(OPERATION_ARCCOS,"arccos");
            PRINT_OP(OPERATION_ARCTG, "arctg");
            PRINT_OP(OPERATION_ARCCTG,"arcctg");

            PRINT_OP(OPERATION_SH,    "sh");
            PRINT_OP(OPERATION_CH,    "ch");
            PRINT_OP(OPERATION_TH,    "th");
            PRINT_OP(OPERATION_CTH,   "cth");

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

#undef PRINT_OP

static void casePrintOperation(const char* operation)
{
    ASSERT(operation, "null operation", stderr);
    printf(MANG"%s"RESET, operation);
}