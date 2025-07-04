#include "texDump.hpp"

static void dumpTexBegin    (FILE* file);             
static void dumpTexTitlePage(FILE* file);
static void dumpTexEnd      (FILE* file);             

static void generateTexExpression(Node* node, FILE* file);
static void writeTexExpression   (Node* node, FILE* file, size_t count, const char* text);

static void printInfix(const Node* node, FILE* file, const char *texOp);
static void printFunc (const Node* node, FILE* file, const char* texName);
static void printFrac (const Node* node, FILE* file);
static void printPow  (const Node* node, FILE* file);
static void printSqrt (const Node* node, FILE* file);

void dumpTex(Node* root, Node* deriv, Node* rootSimpl, Node* derivSimpl, size_t countRoot, size_t countDeriv, FILE* tex)
{
    ASSERT(root,       "root = nullptr, impossible to write tex tree with null root",       stderr);
    ASSERT(deriv,      "deriv = nullptr, impossible to write tex tree with null root",      stderr);
    ASSERT(rootSimpl,  "rootSimpl = nullptr, impossible to write tex tree with null root",  stderr);
    ASSERT(derivSimpl, "derivSimpl = nullptr, impossible to write tex tree with null root", stderr);
    ASSERT(tex,        "texFile = nullptr, impossible to write in null file",               stderr);
    
    dumpTexBegin(tex);

    dumpTexTitlePage(tex);
    writeTexExpression(root, tex, 1, "The original form of the mathematical expression");
    writeTexExpression(rootSimpl, tex, countRoot, "The original form can be simplified");
    writeTexExpression(deriv, tex, 1, "We obtain the derivative");
    writeTexExpression(derivSimpl, tex, countDeriv, "The final form can be simplified");

    dumpTexEnd(tex);

    fflush(tex);

    const int ret = system("pdflatex -interaction=nonstopmode -halt-on-error "
                            "-output-directory=dumpLatex dumpTex.tex "
                            "> dumpLatex/dumpTex.log 2>&1");
    if (ret != 0)
        fprintf(stderr, "[dumpTex] pdflatex exited with code %d — see %s\n", ret, PDFLATEX_LOG);
}

static void dumpTexBegin(FILE* file)
{
    ASSERT(file, "file = nullptr, impossible to open", stderr);
    fputs(
        "\\documentclass[12pt, letterpaper, twoside]{article}\n"
        "\\usepackage[utf8]{inputenc}\n"
        "\\usepackage[russian]{babel}\n"
        "\\usepackage{xcolor}\n"
        "\\usepackage{tikz}\n"
        "\\definecolor{bgDark}{HTML}{0D1B2A}\n"
        "\\definecolor{accent}{HTML}{F95738}\n"
        "\\usepackage{geometry}\n"
        "\\geometry{margin=2.5cm}\n"
        "\\usepackage{graphicx}\n"
        "\\usepackage{lmodern}\n"
        "\\pagecolor{gray!3}\n"
        "\\pagecolor{bgDark}\n"
        "\\color{white}\n"
        "\\usetikzlibrary{calc}\n\n"
        "\\begin{document}\n",
        file);
}

static void dumpTexTitlePage (FILE* file)
{
    ASSERT(file, "file = nullptr, impossible to open", stderr);

    fputs(
        "\\begin{titlepage}\n"
        "  \\centering\n"
        "  \\vspace*{0.25\\textheight}\n"
        
        "  {\\fontsize{48}{60}\\bfseries\\color{accent}DIFFERENTIATOR\\\\}\n" 

        "  \\vspace{1.5em}\n" 
        "  {\\Large\\itshape Symbolic Derivation Engine}\\\\\n"

        "  \\vspace{2em}\n" 
        "  \\quad \\today\\\\\n"

        "  \\vfill\n" 
        "  \\begin{tikzpicture}[remember picture,overlay]\n"
        "    \\fill[accent] (current page.south west) rectangle ++(\\paperwidth,1.5cm);\n"
        "    \\node[font=\\bfseries\\LARGE, text=black, align=center]\n"
        "      at ([xshift=0.5\\paperwidth,yshift=0.75cm]current page.south west)\n"
        "      {Project author: Bulgakov Dmitry};\n"
        "  \\end{tikzpicture}\n"

        "\\end{titlepage}\n"
        "\\newpage\n\n",
        file);
}

static void dumpTexEnd(FILE* file)
{
    ASSERT(file, "file = nullptr, impossible to open", stderr);
    fputs("\\end{document}\n", file);
}

static void printInfix(const Node* node, FILE* file, const char* texOp)
{
    ASSERT(node,  "node = nullptr, impossible to write in tex",          stderr);
    ASSERT(file,  "file = nullptr, impossible to write in null file",    stderr);
    ASSERT(texOp, "texOp = nullptr, impossible to write this operation", stderr);

    fprintf(file, "(");                    
    generateTexExpression(node->left,  file);  
    fprintf(file, " %s ", texOp);          
    generateTexExpression(node->right, file);  
    fprintf(file, ")");                     
}

static void printFunc(const Node* node, FILE* file, const char* texName)
{
    ASSERT(node,    "node = nullptr, impossible to write in tex",       stderr);
    ASSERT(file,    "file = nullptr, impossible to write in null file", stderr);
    ASSERT(texName, "texName = nullptr, impossible to write this name", stderr);

    fprintf(file, "%s(", texName);          
    generateTexExpression(node->right, file);  
    fprintf(file, ")");                     
}

static void printFrac(const Node* node, FILE* file)
{
    ASSERT(node, "node = nullptr, impossible to write in tex",       stderr);
    ASSERT(file, "file = nullptr, impossible to write in null file", stderr);

    fprintf(file, "\\frac{");
    generateTexExpression(node->left,  file);
    fprintf(file, "}{");
    generateTexExpression(node->right, file);
    fprintf(file, "}");
}

static void printPow(const Node* node, FILE* file)
{
    ASSERT(node, "node = nullptr, impossible to write in tex",       stderr);
    ASSERT(file, "file = nullptr, impossible to write in null file", stderr);

    fprintf(file, "(");
    generateTexExpression(node->left,  file);
    fprintf(file, ")^{");
    generateTexExpression(node->right, file);
    fprintf(file, "}");
}

static void printSqrt(const Node* node, FILE* file)
{
    ASSERT(node, "node = nullptr, impossible to write in tex",       stderr);
    ASSERT(file, "file = nullptr, impossible to write in null file", stderr);

    fprintf(file, "\\sqrt{");
    generateTexExpression(node->right,  file);
    fprintf(file, "}");
}


static void generateTexExpression(Node* node, FILE* file)
{
    ASSERT(node, "node = nullptr, impossible to write tex",          stderr);
    ASSERT(file, "file = nullptr, impossible to write in null file", stderr);

    switch ((int)node->type)
    {
        case TYPE_OPERATION:
        {
            switch (node->value.op)
            {
                case OPERATION_ADD:     printInfix(node, file, "+");      break;
                case OPERATION_SUB:     printInfix(node, file, "-");      break;
                case OPERATION_MUL:     printInfix(node, file, "\\cdot"); break;

                case OPERATION_DIV:     printFrac(node, file);            break;
                case OPERATION_POW:     printPow (node, file);            break;
                case OPERATION_SQRT:    printSqrt(node, file);            break;

                case OPERATION_LN:      printFunc(node, file, "ln");      break;
                case OPERATION_NEG:     printFunc(node, file, "-");       break;  
                case OPERATION_SIN:     printFunc(node, file, "sin");     break;
                case OPERATION_COS:     printFunc(node, file, "cos");     break;
                case OPERATION_TG:      printFunc(node, file, "tg");      break;
                case OPERATION_CTG:     printFunc(node, file, "ctg");     break;
                case OPERATION_ARCSIN:  printFunc(node, file, "arcsin");  break;
                case OPERATION_ARCCOS:  printFunc(node, file, "arccos");  break;
                case OPERATION_ARCTG:   printFunc(node, file, "arctg");   break;
                case OPERATION_ARCCTG:  printFunc(node, file, "arcctg");  break;
                case OPERATION_SH:      printFunc(node, file, "sh");      break;
                case OPERATION_CH:      printFunc(node, file, "ch");      break;
                case OPERATION_TH:      printFunc(node, file, "th");      break;
                case OPERATION_CTH:     printFunc(node, file, "cth");     break;

                default:
                    fprintf(stderr, RED"ERROR: unknown op in generateTexExpression\n"RESET);
                    abort();
            }
                        
            break;
        }  
        case TYPE_NUMBER:
        {
            fprintf(file, "%lg", node->value.num);
            break;
        } 
        case TYPE_VARIABLE:
        {
            fprintf(file, "%c", node->value.var);
            break;
        }
        default: 
        {
            fprintf(stderr, RED"ERROR IN FUNCTION generateTex\n"RESET);
            abort();
        }
    }
}

static void writeTexExpression(Node* node, FILE* file, size_t count, const char* text)
{
    ASSERT(node, "node = nullptr, impossible to write tex",          stderr);
    ASSERT(file, "file = nullptr, impossible to write in null file", stderr);

    if (count != 0)
    {
        fprintf(file, "\\section{%s}\n", text);

        fprintf(file, "\t\\[");
        generateTexExpression(node, file);
        fprintf(file, "\\]\n");
    }
}

