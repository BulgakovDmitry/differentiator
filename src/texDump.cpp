#include "texDump.hpp"

static void dumpTexBegin(FILE* file);             
static void dumpTexTitlePage (FILE* file);
static void dumpTexEnd(FILE* file);             

static void generateTexExpression(Node* node, FILE* file);
static void writeTexExpression(Node* node, FILE* file, size_t count, const char* text);

void dumpTex(Node* root, Node* deriv, Node* rootSimpl, Node* derivSimpl, size_t countRoot, size_t counstDeriv)
{
    ASSERT(root,       "root = nullptr",       stderr);
    ASSERT(deriv,      "deriv = nullptr",      stderr);
    ASSERT(rootSimpl,  "rootSimpl = nullptr",  stderr);
    ASSERT(derivSimpl, "derivSimpl = nullptr", stderr);

    FILE* dumpTexFile = fopen(DUMPTEX_FILE_NAME, "w");
    ASSERT(dumpTexFile, "dumpTexFile = nullptr, impossible to open", stderr);
    
    dumpTexBegin(dumpTexFile);
    dumpTexTitlePage(dumpTexFile);
    //тело функции
    writeTexExpression(root, dumpTexFile, 1, "The original form of the mathematical expression");
    writeTexExpression(rootSimpl, dumpTexFile, countRoot, "The original form can be simplified");

    writeTexExpression(deriv, dumpTexFile, 1, "We obtain the derivative");
    writeTexExpression(derivSimpl, dumpTexFile, counstDeriv, "The filna form can be simplified");
    //
    dumpTexEnd(dumpTexFile);

    FCLOSE(dumpTexFile);

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

static void generateTexExpression(Node* node, FILE* file)
{
    ASSERT(node, "node = nullptr, impossible to write tex", stderr);
    ASSERT(file, "file = nullptr, impossible to write tex", stderr);

    switch ((int)node->type)
    {
        case TYPE_OPERATION:
        {
            switch (node->value.op)
            {
                case OPERATION_ADD:
                {
                    fprintf(file, "(");
                    generateTexExpression(node->left, file);
                    fprintf(file, " + ");
                    generateTexExpression(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_SUB:
                {
                    fprintf(file, "(");
                    generateTexExpression(node->left, file);
                    fprintf(file, " - ");
                    generateTexExpression(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_MUL:
                {
                    fprintf(file, "(");
                    generateTexExpression(node->left, file);
                    fprintf(file, " \\cdot ");
                    generateTexExpression(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_DIV:
                {
                    fprintf(file, "\\frac{");
                    generateTexExpression(node->left, file);
                    fprintf(file, "}{");
                    generateTexExpression(node->right, file);
                    fprintf(file, "}");
                    break;
                }
                case OPERATION_LN:
                {
                    fprintf(file, "ln( ");
                    generateTexExpression(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_SIN:
                {
                    fprintf(file, "sin( ");
                    generateTexExpression(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_COS:
                {
                    fprintf(file, "cos( ");
                    generateTexExpression(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_TG:
                {
                    fprintf(file, "tg( ");
                    generateTexExpression(node->right, file);
                    fprintf(file, ")");
                    break;
                }
                case OPERATION_POW:
                {
                    fprintf(file, "(");
                    generateTexExpression(node->left, file);
                    fprintf(file, ")");

                    fprintf(file, "^{");
                    generateTexExpression(node->right, file);
                    fprintf(file, "}");
                    break;
                }
                default:
                {
                    printf(RED "ERROR IN FUNCTION generateTexExpression\n" RESET);\
                    abort();
                }
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
            printf(RED "ERROR IN FUNCTION generateTex (2)\n" RESET);
            abort();
        }
    }
}

static void writeTexExpression(Node* node, FILE* file, size_t count, const char* text)
{
    ASSERT(node, "node = nullptr, impossible to write tex", stderr);
    ASSERT(file, "file = nullptr, impossible to write tex", stderr);

    if (count != 0)
    {
        //fputs(text, file);
        fprintf(file, "\\section{%s}\n", text);

        fprintf(file, "\t\\[");
        generateTexExpression(node, file);
        fprintf(file, "\\]\n");
    }
}

