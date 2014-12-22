#include "differentiator.h"

#include <string.h>

//==========================================================================
#define NUMBER_OF_COMMANDS 12
//==========================================================================
const char* FunctionTable[NUMBER_OF_COMMANDS] = {
    "+",
    "-",
    "*",
    "/",
    "^",
    "sin",
    "cos",
    "tan",
    "log",
    "asin",
    "acos",
    "atan"
};
//==============================================================================
int DivideIntoTokens(char* String, Token** TokenSequence, int* NumOfTokens) {

    if (String == NULL) {

        return NULL_POINTER;
    }

    int leng = strlen(String);

    if (leng == 0)
        return EMPTY_STRING;

    int flag = 0;
    //Check brackets
    for (int i = 0; i < leng; i++) {

        if (flag < 0)
            return INV_BRACKET_SEQ;

        if (String[i] == '(')
            flag++;

        if (String[i] == ')')
            flag--;
    }

    if (flag != 0)
        return INV_BRACKET_SEQ;

    char* s = (char*) calloc (leng, sizeof(char));

    if (s == NULL) {

        return ERR_MEM;
    }

    *TokenSequence = (Token*) calloc (leng, sizeof(Token));

    if (*TokenSequence == NULL) {

        return ERR_MEM;
    }

    //Parsing
    int newLeng = 0;
    int shift = 0;
    int prevToken = 0;
    double Val = 0;
//==============================================================================
#define CurToken (*TokenSequence)[newLeng]
//==============================================================================
    while (*String != 0) {

        //Ignore spaces
        while (*String == ' ') String++;

        if (strlen(String) == 0 && newLeng == 0)
            return EMPTY_STRING;
        //Numbers

        if (sscanf(String, "%[0-9.]", s) > 0) {

            if (s == NULL)
                return NULL_POINTER;

            shift = strlen(s);

            CurToken.Type = NUM;

            CurToken.Oper = NONE;

            if (sscanf(s, "%lg", &Val) <= 0)
                return SYNTAX_ERROR;

            CurToken.nValue = Val;

            newLeng++;

            String += shift;

            if (prevToken == NUM || prevToken == VAR || prevToken == CBRACKET)
                return SYNTAX_ERROR;

            prevToken = NUM;

            continue;
        }
        //+-*/^
        if (sscanf(String, "%[+*/^-]", s) > 0) {

            shift = strlen(s);

            if (shift > 1)
                return UNKNOWN_TOKEN;

            for (int i = 0; i < SIN; i++)

                if (strcmp(s, FunctionTable[i]) == 0) {

                    CurToken.Value = (char*) calloc (shift, sizeof(char));

                    strcpy(CurToken.Value, s);

                    CurToken.Type = FUN;

                    CurToken.Oper = i;

                    newLeng++;

                    String += shift;
                }

                if (prevToken == FUN || prevToken == OBRACKET || prevToken == 0)
                    return SYNTAX_ERROR;

                prevToken = FUN;

                continue;
        }
        //
        if (sscanf(String, "%[a-zA-Z]", s) > 0) {

            shift = strlen(s);

            int match = 0;

            for (int i = SIN; i <= ATAN; i++)

                if (strcmp(s, FunctionTable[i]) == 0) {

                    CurToken.Value = (char*) calloc (shift, sizeof(char));

                    strcpy(CurToken.Value, s);

                    CurToken.Type = FUN;

                    CurToken.Oper = i;

                    newLeng++;

                    match = 1;

                    String += shift;

                    if (prevToken == VAR || prevToken == NUM || prevToken == CBRACKET)
                        return SYNTAX_ERROR;

                    prevToken = FUN;

                    continue;
                }

            if (match == 0) {

                CurToken.Value = (char*) calloc (shift, sizeof(char));

                strcpy(CurToken.Value, s);

                CurToken.Type = VAR;

                CurToken.Oper = NONE;

                newLeng++;

                String += shift;

                if (prevToken == VAR || prevToken == NUM || prevToken == CBRACKET)
                    return SYNTAX_ERROR;

                prevToken = VAR;
            }

            continue;
        }
        //

        if (*String == '(') {

            CurToken.Value = (char*) calloc (shift, sizeof(char));

            strcpy(CurToken.Value, "(");

            CurToken.Type = OBRACKET;

            CurToken.Oper = NONE;

            newLeng++;

            String += 1;

            if (prevToken == CBRACKET)
                return INV_BRACKET_SEQ;

            if (prevToken != FUN && prevToken != OBRACKET && prevToken != 0)
                    return SYNTAX_ERROR;

            prevToken = OBRACKET;

            continue;

        }

        if (*String == ')') {

            CurToken.Value = (char*) calloc (shift, sizeof(char));

            strcpy(CurToken.Value, ")");

            CurToken.Type = CBRACKET;

            CurToken.Oper = NONE;

            newLeng++;

            String += 1;

            if (prevToken == FUN || prevToken == OBRACKET || prevToken == 0)
                    return SYNTAX_ERROR;

            prevToken = CBRACKET;

            continue;
        }

    }

    *NumOfTokens = newLeng - 1;

    if (NumOfTokens <= 0)
        return EMPTY_STRING;

    free(s);
    s = NULL;

    return OK;
};
//==============================================================================
int TokensDump (Token* TokenSequence, int NumOfTokens) {

    FILE* dump = fopen("dump.txt", "a");

    if (dump == NULL)
        return DUMP_ERROR;

    fprintf(dump, "=================DUMP=TOKEN=SEQUENCE====================\n\n");

    for (int i = 0; i <= NumOfTokens; i++)

        switch (TokenSequence[i].Type) {

            case VAR:

                fprintf(dump, "VARIABLE: %s\n", TokenSequence[i].Value);

                break;

            case FUN:

                fprintf(dump, "FUNCTION: %s\n", TokenSequence[i].Value);

                break;

            case NUM:

                fprintf(dump, "NUMBER: %lg\n", TokenSequence[i].nValue);

                break;

            case OBRACKET:

                fprintf(dump, "BRACKET: %s\n", TokenSequence[i].Value);

                break;

            case CBRACKET:

                fprintf(dump, "BRACKET: %s\n", TokenSequence[i].Value);

                break;

            default:

                fprintf(dump, "UNKNOWN TYPE OF TOKEN == %s\n", TokenSequence[i].Value);

                break;
        }

    fclose(dump);

    return OK;
};
//==============================================================================
int MakeExpressionTree(node** Expression) {

    create_new_leaf(Expression, NULL, 0, ROOT, NONE);

    check(add_left(*Expression, GetE()));

    return OK;
};
//===================================================================================
#define check_p( err_number ) {                                                                   \
do {                                                                                \
    switch (err_number) {                                                           \
                                                                                    \
        case OK:                                                                    \
                                                                                    \
            fprintf(logs,"%s == OK\n", #err_number);                                \
            break;                                                                  \
                                                                                    \
        case ERR_MEM:                                                               \
                                                                                    \
            fprintf(logs,"%s == NOT ENOUGH MEMORY TO ALLOCATE\n", #err_number);     \
            return NULL;                                                            \
                                                                                    \
        case INVALID_TREE:                                                          \
                                                                                    \
            fprintf(logs,"%s == INVALID TREE\n", #err_number);                      \
            return NULL;                                                            \
                                                                                    \
        case NULL_DATA_FIELD:                                                       \
                                                                                    \
            fprintf(logs,"%s == NULL INFORMATION FIELD\n", #err_number);            \
            return NULL;                                                            \
                                                                                    \
                                                                                    \
        case EMPTY_STRING:                                                          \
                                                                                    \
            fprintf(logs,"%s == STRING IS EMPTY\n", #err_number);                   \
            return NULL;                                                            \
                                                                                    \
        case NULL_POINTER:                                                          \
                                                                                    \
            fprintf(logs,"%s == INCORRECT POINTER TO SOMETHING\n", #err_number);    \
            return NULL;                                                            \
                                                                                    \
        case UNKNOWN_TOKEN:                                                         \
                                                                                    \
            fprintf(logs,"%s == UNKNOWN TOKEN\n", #err_number);                     \
            return NULL;                                                            \
                                                                                    \
        case UNKNOWN_SYMBOL:                                                        \
                                                                                    \
            fprintf(logs,"%s == UNKNOWN SYMBOL IN ENTERED STRING\n", #err_number);  \
            return NULL;                                                            \
                                                                                    \
        default:                                                                    \
            fprintf(logs,"%s == UNKNOWN ERROR\n", #err_number);                     \
            return NULL;                                                            \
    }                                                                               \
} while(0); }                                                                       \
//===================================================================================
#define GTS GlobalTokenSeq
//===================================================================================
node* GetE() {

    node* val = GetSub();

    while (GTS->Type == FUN && GTS->Oper == ADD) {

        GTS++;

        node* add = NULL;

        check_p(create_new_leaf(&add, "+", 0, FUN, ADD));

        check_p(add_left(add, val));

        check_p(add_rght(add, GetE()));

        return add;

    }

    return val;
};
//==============================================================================
node* GetSub() {

    node* val = GetDiv();

    while (GTS->Type == FUN && GTS->Oper == SUB) {

        GTS++;

        node* sub = NULL;

        check_p(create_new_leaf(&sub, "-", 0, FUN, SUB));

        check_p(add_left(sub, val));

        check_p(add_rght(sub, GetSub()));

        return sub;

    }

    return val;
};
//==============================================================================
node* GetDiv() {

    node* val = GetT();

    while (GTS->Type == FUN && GTS->Oper == DIV) {

        GTS++;

        node* div = NULL;

        check_p(create_new_leaf(&div, "/", 0, FUN, DIV));

        check_p(add_left(div, val));

        check_p(add_rght(div, GetDiv()));

        return div;

    }

    return val;

};
//==============================================================================
node* GetT() {

    node* val = GetDegree();

    while (GTS->Type == FUN && GTS->Oper == MUL) {

        GTS++;

        node* mul = NULL;

        check_p(create_new_leaf(&mul, "*", 0, FUN, MUL));

        check_p(add_left(mul, val));

        check_p(add_rght(mul, GetT()));

        return mul;

    }

    return val;

};
//==============================================================================
node* GetDegree () {

    node* val = GetSin();

    while (GTS->Type == FUN && GTS->Oper == DEG) {

        GTS++;

        node* deg = NULL;

        check_p(create_new_leaf(&deg, "^", 0, FUN, DEG));

        check_p(add_left(deg, val));

        check_p(add_rght(deg, GetDegree()));

        return deg;

    }

    return val;

};
//==============================================================================
node* GetSin() {

    node* val = GetCos();

    while (GTS->Type == FUN && GTS->Oper == SIN) {

        GTS++;

        node* Sin = NULL;

        check_p(create_new_leaf(&Sin, "sin", 0, FUN, SIN));

        check_p(add_left(Sin, GetP()));

        return Sin;

    }

    return val;

}
//==============================================================================
node* GetCos() {

    node* val = GetP();

    while (GTS->Type == FUN && GTS->Oper == COS) {

        GTS++;

        node* Cos = NULL;

        check_p(create_new_leaf(&Cos, "cos", 0, FUN, COS));

        check_p(add_left(Cos, GetP()));

        return Cos;

    }

    return val;
};
//==============================================================================
node* GetP() {

    node* val = NULL;

    if (GTS->Type != OBRACKET) {

        val = GetN();

        return val;

    }
    else {

        GTS++;

        val = GetE();
    }

    GTS++;

    return val;

};
//==============================================================================
node* GetN() {

    if (GTS == NULL)
        return NULL;

    node* num = NULL;

    if (GTS->Type == NUM ) {

        check_p(create_new_leaf(&num, NULL, GTS->nValue, NUM, NONE));

        GTS++;

    }

    if (GTS->Type == VAR ) {

        check_p(create_new_leaf(&num, GTS->Value, 0, VAR, NONE));

        GTS++;

    }

    return num;
};
//==============================================================================
#define EI expression->info
#define EL expression->left
#define ER expression->rght
#define CNL create_new_leaf
#define NC node_cpy
#define L NewTree->left
#define R NewTree->rght
#define LL NewTree->left->left
#define LR NewTree->left->rght
#define RL NewTree->rght->left
#define RR NewTree->rght->rght
//==============================================================================
node* Differentiation (node* expression) {

    node* NewTree = NULL;

    if (expression == NULL)
        return NULL;

    if (EI == NULL)
        return NULL;

    switch (EI->Type) {

        case ROOT:

            check_p(NC(&NewTree, expression));

            check_p(NC(&L, Differentiation(EL)));

            break;

        case VAR:

            check_p(CNL(&NewTree, NULL, 1, NUM, NONE));

            break;

        case NUM:

            check_p(CNL(&NewTree, NULL, 0, NUM, NONE));

            break;

        case FUN:

            switch (EI->Oper) {

                case ADD:

                    check_p(CNL(&NewTree, "+", 0, FUN, ADD));

                    check_p(NC(&L, Differentiation(EL)));

                    check_p(NC(&R, Differentiation(ER)));

                    break;

                case SUB:

                    check_p(CNL(&NewTree, "-", 0, FUN, SUB));

                    check_p(NC(&L, Differentiation(EL)));

                    check_p(NC(&R, Differentiation(ER)));

                    break;

                case MUL:

                    check_p(CNL(&NewTree, "+", 0, FUN, ADD));

                    check_p(CNL(&L, "*", 0, FUN, MUL));

                    check_p(CNL(&R, "*", 0, FUN, MUL));

                    check_p(NC(&LL, Differentiation(EL)));
                    check_p(NC(&LR, ER));

                    check_p(NC(&RL, EL));
                    check_p(NC(&RR, Differentiation(ER)));

                    break;

                case DIV:

                    check_p(CNL(&NewTree, "/", 0, FUN, DIV));

                    check_p(CNL(&L, "-", 0, FUN, SUB));

                    check_p(CNL(&R, "^", 0, FUN, DEG));

                    check_p(CNL(&LL, "*", 0, FUN, MUL));

                    check_p(CNL(&LR, "*", 0, FUN, MUL));

                    check_p(NC(&LL->left, Differentiation(EL)));
                    check_p(NC(&LL->rght, ER));

                    check_p(NC(&LR->left, Differentiation(ER)));
                    check_p(NC(&LR->rght, EL));

                    check_p(NC(&RL, ER));
                    check_p(CNL(&RR, NULL, 2, NUM, NONE));

                    break;

                case DEG:

                    if (EL->info->Type == NUM && ER->info->Type == NUM) {

                        check_p(CNL(&NewTree, NULL, 0, FUN, NONE));

                        return NewTree;
                    }

                    if (ER->info->Type == VAR) {

                        return NULL;
                    }

                    check_p(CNL(&NewTree, "*", 0, FUN, MUL));

                    check_p(CNL(&L, "*", 0, FUN, MUL));

                    check_p(CNL(&R, "^", 0, FUN, DEG));

                    check_p(CNL(&RR, "-", 0, FUN, SUB));

                    check_p(NC(&LL, ER));

                    check_p(NC(&LR, Differentiation(EL)));

                    check_p(NC(&RL, EL));

                    check_p(NC(&RR->left, ER));

                    check_p(CNL(&RR->rght, NULL, 1, NUM, NONE));

                    break;

                case SIN:

                    check_p(CNL(&NewTree, "*", 0, FUN, MUL));

                    check_p(NC(&L, Differentiation(EL)));

                    check_p(CNL(&R, "cos", 0, FUN, COS));

                    check_p(NC(&RL, EL));

                    break;

                case COS:

                    check_p(CNL(&NewTree, "*", 0, FUN, MUL));

                    check_p(NC(&L, Differentiation(EL)));

                    check_p(CNL(&R, "-", 0, FUN, SUB));

                    check_p(CNL(&RL, NULL, 0, NUM, NONE));

                    check_p(CNL(&RR, "sin", 0, FUN, SIN));

                    check_p(NC(&RR->left, EL));

                    break;

                default:

                    return NULL;
            }

            break;

        default:

            return NULL;

    }

    return NewTree;
};
//====================================================================================
int printHeader () {

    if (TeX == NULL)
        return NULL_POINTER;

    //Header
    fprintf(TeX,    "\\documentclass{article}\n"
                    "\\usepackage{amsfonts,longtable,amssymb,amsmath}\n"
                    "\\begin{document}\n"
                    "\\begin{center}\n"
                    "\\huge{\\textbf{The Differential Of Some Function}}\n"
                    "\\end{center}\n"
                    "\\begin{flushright}\n"
                    "{\\textit{\\textbf{Work made by Koposov D. E.}}}\n\n"
                    "{\\textit{Moscow Institute Of Physics and Technologies}}\n"
                    "\\end{flushright}\n");
    return OK;

};
//====================================================================================
int printListOfLiterature () {

    if (TeX == NULL)
        return NULL_POINTER;

    //Header
    fprintf(TeX,    "\\Large{\n"
                    "{ \\textbf {References:} }\n\n"
                    "{1) \\textit {Kernighan B., Ritchie D.} The C Programming Language (second edition) }\n\n"

                    "{2) \\textit {Knuth D.E.} The Art of Computer Programming}\n\n"

                    "{3) \\textit {Lvovsky S.M.} Set and layout of the system\n"
                    "LATEX}\\end{document}\n");

    return OK;

};
//====================================================================================
int TexPrintNode (node* Node, int Previous) {

    if (Node != NULL) {

        switch (Node->info->Type) {

        case ROOT:

            check(TexPrintNode(Node->left, ROOT));

            break;

        case VAR:

            fprintf(TeX, "{%s}", Node->info->Value);

            break;

        case NUM:

            if (Node->info->nValue == 0 && Previous == SUB)
                break;

            fprintf(TeX, "{%lg}", Node->info->nValue);

            break;

        case FUN:

            switch (Node->info->Oper) {

                case ADD:

                    if (Previous == MUL || Previous == DEG || Previous == SUB)
                        fprintf(TeX, "{(");
                    else
                        fprintf(TeX, "{");

                    check(TexPrintNode(Node->left, ADD));

                    fprintf(TeX, "} + {");

                    check(TexPrintNode(Node->rght, ADD));

                    if (Previous == MUL || Previous == DEG || Previous == SUB)
                        fprintf(TeX, ")}");
                    else
                        fprintf(TeX, "}");

                    break;

                case SUB:

                    if (Previous == MUL || Previous == DEG || Previous == SUB)
                        fprintf(TeX, "{(");
                    else
                        fprintf(TeX, "{");

                    check(TexPrintNode(Node->left, SUB));

                    fprintf(TeX, "} - {");

                    check(TexPrintNode(Node->rght, SUB));

                    if (Previous == MUL || Previous == DEG || Previous == SUB)
                        fprintf(TeX, ")}");
                    else
                        fprintf(TeX, "}");

                    break;

                case MUL:

                    fprintf(TeX, "{");

                    check(TexPrintNode(Node->left, MUL));

                    fprintf(TeX, "}*{");

                    check(TexPrintNode(Node->rght, MUL));

                    fprintf(TeX, "}");

                    break;

                case DIV:

                    fprintf(TeX, "\\frac{");

                    check(TexPrintNode(Node->left, DIV));

                    fprintf(TeX, "}{");

                    check(TexPrintNode(Node->rght, DIV));

                    fprintf(TeX, "}");

                    break;

                case DEG:

                    fprintf(TeX, "{");

                    check(TexPrintNode(Node->left, DEG));

                    if (Node->rght->info->nValue == 1) {

                        fprintf(TeX, "}");

                        break;
                    }

                    fprintf(TeX, "}^{");

                    check(TexPrintNode(Node->rght, DEG));

                    fprintf(TeX, "}");

                    break;

                case SIN:

                    fprintf(TeX, "\\sin{(");

                    check(TexPrintNode(Node->left, SIN));

                    fprintf(TeX, ")}");

                    break;

                case COS:

                    fprintf(TeX, "\\cos{(");

                    check(TexPrintNode(Node->left, COS));

                    fprintf(TeX, ")}");

                    break;

                default:

                    return UNKNOWN_TOKEN;
            }

            break;

        default:

            return UNKNOWN_TOKEN;

        }
    }

    return OK;

};
//=================================================================================
