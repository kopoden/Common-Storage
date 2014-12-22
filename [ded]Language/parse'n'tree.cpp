#define NUMBER_OF_COMMANDS 17

#include "parse'n'tree.h"
//==========================================================================
extern Token* GlobalTokenSeq;
extern FILE* logs;
extern FILE* Asm;
int GlobalLabel = 0;
//==========================================================================
const char* FunctionTable[NUMBER_OF_COMMANDS] = {
    "+",
    "-",
    "*",
    "/",
    ":=",
    "out<<",
    "in>>",
    "begin",
    "end",
    "if",
    "while",
    "<",
    ">",
    "<=",
    ">=",
    "!=",
    "=="
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
        while (*String == ' ' || *String == '\n' || *String == '\r') String++;

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

            prevToken = NUM;

            continue;
        }
        //+-*/^
        if (sscanf(String, "%[+*/^-:=]", s) > 0) {

            shift = strlen(s);

            for (int i = 0; i < NUMBER_OF_COMMANDS; i++)

                if (strcmp(s, FunctionTable[i]) == 0) {

                    CurToken.Value = (char*) calloc (shift, sizeof(char));

                    strcpy(CurToken.Value, s);

                    CurToken.Type = FUN;

                    CurToken.Oper = i;

                    newLeng++;

                    String += shift;
                }

                prevToken = FUN;

                continue;
        }
        //
        if (sscanf(String, "%[a-zA-Z0-9<>]", s) > 0) {

            shift = strlen(s);

            int match = 0;

            for (int i = 0; i < NUMBER_OF_COMMANDS; i++)

                if (strcmp(s, FunctionTable[i]) == 0) {

                    CurToken.Value = (char*) calloc (shift, sizeof(char));

                    strcpy(CurToken.Value, s);

                    CurToken.Type = FUN;

                    CurToken.Oper = i;

                    newLeng++;

                    match = 1;

                    String += shift;

                    prevToken = FUN;

                    continue;
                }

            if (match == 0) {

                CurToken.Value = (char*) calloc (shift + 1, sizeof(char));

                strcpy(CurToken.Value, s);

                CurToken.Type = VAR;

                CurToken.Oper = NONE;

                newLeng++;

                String += shift;

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
int MakeExpressionTree(node** Expression) {

    create_new_leaf(Expression, "BEGIN", 0, ROOT, NONE);

    add_left(*Expression, GetBeg());

    return OK;
};
//===================================================================================
#define GTS GlobalTokenSeq
//===================================================================================
node* GetBeg() {

    node* New1 = GetInp();

    if (GTS->Type == FUN && GTS->Oper == BEG) {

        node* New2 = NULL;

        create_new_leaf(&New2, "begin", 0, FUN, BEG);

        GTS++;

        New2->mid = GetBeg();

        return New2;
    }

    return New1;
};
//==============================================================================================================
node* GetInp() {

    node* New1 = GetOut();

    if (GTS->Type == FUN && GTS->Oper == INP) {

        node* New2 = NULL;

        create_new_leaf(&New2, "in>>", 0, FUN, INP);

        GTS++;

        New2->left = GetVar();
        New2->rght = GetInp();

        return New2;
    }

    return New1;

};
//==============================================================================================================
node* GetOut() {

    node* New1 = GetIf();

    if (GTS->Type == FUN && GTS->Oper == OUT) {

        node* New2 = NULL;

        create_new_leaf(&New2, "out<<", 0, FUN, OUT);

        GTS++;

        New2->left = GetVar();
        New2->rght = GetOut();

        return New2;
    }

    return New1;

};
//==============================================================================================================
node* GetIf () {

    node* New1 = GetWhile();

    if (GTS->Type == FUN && GTS->Oper == IF) {

        node* New2 = NULL;

        create_new_leaf(&New2, "if", 0, FUN, IF);

        GTS++;

        New2->left = GetLES();
        New2->mid = GetBeg();
        New2->rght = GetIf();

        return New2;
    }

    return New1;
}
//===================================================================================
node* GetWhile () {

    node* New1 = GetAsg();

    if (GTS->Type == FUN && GTS->Oper == WHILE) {

        node* New2 = NULL;

        create_new_leaf(&New2, "while", 0, FUN, WHILE);

        GTS++;

        New2->left = GetLES();
        New2->mid = GetBeg();
        New2->rght = GetIf();

        return New2;
    }

    return New1;
}
//===================================================================================
node* GetAsg () {

    node* New1 = GetLES();

    if (GTS->Type == FUN && GTS->Oper == ASG) {

        node* New2 = NULL;

        create_new_leaf(&New2, ":=", 0, FUN, ASG);

        GTS++;

        New2->left = New1;
        New2->mid = GetAdd();
        New2->rght = GetAsg();

        return New2;
    }

    return New1;
}
//==============================================================================================================
node* GetLES() {

    node* New1 = GetMOR();

    if (GTS->Type == FUN && GTS->Oper == LES) {

        node* New2 = NULL;

        create_new_leaf(&New2, "<", 0, FUN, LES);

        GTS++;

        New2->left = New1;
        New2->rght = GetVar();

        return New2;
    }

    return New1;
};
//==============================================================================================================
node* GetMOR() {

    node* New1 = GetLOE();

    if (GTS->Type == FUN && GTS->Oper == MOR) {

        node* New2 = NULL;

        create_new_leaf(&New2, ">", 0, FUN, MOR);

        GTS++;

        New2->left = New1;
        New2->rght = GetVar();

        return New2;
    }

    return New1;
};
//==============================================================================================================
node* GetLOE() {

    node* New1 = GetMOE();

    if (GTS->Type == FUN && GTS->Oper == LOE) {

        node* New2 = NULL;

        create_new_leaf(&New2, "<=", 0, FUN, LOE);

        GTS++;

        New2->left = New1;
        New2->rght = GetVar();

        return New2;
    }

    return New1;
};
//==============================================================================================================
node* GetMOE() {

    node* New1 = GetNOE();

    if (GTS->Type == FUN && GTS->Oper == MOE) {

        node* New2 = NULL;

        create_new_leaf(&New2, ">=", 0, FUN, MOE);

        GTS++;

        New2->left = New1;
        New2->rght = GetVar();

        return New2;
    }

    return New1;
};
//==============================================================================================================
node* GetNOE() {

    node* New1 = GetEQU();

    if (GTS->Type == FUN && GTS->Oper == NOE) {

        node* New2 = NULL;

        create_new_leaf(&New2, "!=", 0, FUN, NOE);

        GTS++;

        New2->left = New1;
        New2->rght = GetVar();

        return New2;
    }

    return New1;
};
//==============================================================================================================
node* GetEQU() {

    node* New1 = GetAdd();

    if (GTS->Type == FUN && GTS->Oper == EQU) {

        node* New2 = NULL;

        create_new_leaf(&New2, "==", 0, FUN, EQU);

        GTS++;

        New2->left = New1;
        New2->rght = GetVar();

        return New2;
    }

    return New1;

};
//==============================================================================================================
node* GetAdd() {

    node* New1 = GetSub();

    if (GTS->Type == FUN && GTS->Oper == ADD) {

        GTS++;

        node* New2 = NULL;

        create_new_leaf(&New2, "+", 0, FUN, ADD);

        New2->left = New1;
        New2->rght = GetAdd();

        return New2;

    }

    return New1;
};
//==============================================================================
node* GetSub() {

    node* New1 = GetDiv();

    if (GTS->Type == FUN && GTS->Oper == SUB) {

        GTS++;

        node* New2 = NULL;

        create_new_leaf(&New2, "-", 0, FUN, SUB);

        New2->left = New1;

        New2->rght = GetSub();

        return New2;

    }

    return New1;
};
//==============================================================================
node* GetDiv() {

    node* New1 = GetMul();

    if (GTS->Type == FUN && GTS->Oper == DIV) {

        GTS++;

        node* New2 = NULL;

        create_new_leaf(&New2, "/", 0, FUN, DIV);

        New2->left = New1;

        New2->rght = GetDiv();

        return New2;

    }

    return New1;

};
//==============================================================================
node* GetMul() {

    node* New1 = GetBracket();

    if (GTS->Type == FUN && GTS->Oper == MUL) {

        GTS++;

        node* New2 = NULL;

        create_new_leaf(&New2, "*", 0, FUN, MUL);

        New2->left = New1;

        New2->rght = GetMul();

        return New2;

    }

    return New1;

};
//==============================================================================
node* GetBracket() {

    node* val = NULL;

    if (GTS->Type != OBRACKET) {

        val = GetVar();

        return val;

    }
    else {

        GTS++;

        val = GetAdd();
    }

    return val;

};
//==============================================================================
node* GetVar() {

    if (GTS == NULL)
        return NULL;

    node* num = NULL;

    if (GTS->Type == NUM ) {

        create_new_leaf(&num, NULL, GTS->nValue, NUM, NONE);

        GTS++;

        return num;

    }

    if (GTS->Type == VAR ) {

        create_new_leaf(&num, GTS->Value, 0, VAR, NONE);

        GTS++;

    }

    return num;
};
//==============================================================================
int TranslateToAsm (node* Node) {

    if (Node != NULL)

        switch (Node->info->Type) {

        case ROOT:

            TranslateToAsm(Node->left);

            break;

        case NUM:

            fprintf(Asm, "%lg\n", Node->info->nValue);

            break;

        case VAR:

            fprintf(Asm, "%s\n", Node->info->Value);

            break;

        case FUN:

            switch (Node->info->Oper) {

                case ADD:

                    if ((Node->left->info->Type == NUM || Node->left->info->Type == VAR) && \
                        (Node->rght->info->Type == NUM || Node->rght->info->Type == VAR)) {

                        fprintf(Asm, "push ");

                        TranslateToAsm(Node->left);

                        fprintf(Asm, "push ");

                        TranslateToAsm(Node->rght);

                        fprintf(Asm, "add\n");

                    }
                    else {
                        TranslateToAsm(Node->left);

                        TranslateToAsm(Node->rght);

                        fprintf(Asm, "add\n");
                    }

                    break;

                case SUB:

                    if ((Node->left->info->Type == NUM || Node->left->info->Type == VAR) && \
                        (Node->rght->info->Type == NUM || Node->rght->info->Type == VAR)) {

                        fprintf(Asm, "push ");

                        TranslateToAsm(Node->left);

                        fprintf(Asm, "push ");

                        TranslateToAsm(Node->rght);

                        fprintf(Asm, "sub\n");
                    }
                    else {
                        TranslateToAsm(Node->left);

                        TranslateToAsm(Node->rght);

                        fprintf(Asm, "sub\n");
                    }

                    break;

                case MUL:

                    if ((Node->left->info->Type == NUM || Node->left->info->Type == VAR) && \
                        (Node->rght->info->Type == NUM || Node->rght->info->Type == VAR)) {

                        fprintf(Asm, "push ");

                        TranslateToAsm(Node->left);

                        fprintf(Asm, "push ");

                        TranslateToAsm(Node->rght);

                        fprintf(Asm, "mul\n");
                    }
                    else {
                        TranslateToAsm(Node->left);

                        TranslateToAsm(Node->rght);

                        fprintf(Asm, "mul\n");
                    }

                    break;

                case DIV:

                    if ((Node->left->info->Type == NUM || Node->left->info->Type == VAR) && \
                        (Node->rght->info->Type == NUM || Node->rght->info->Type == VAR)) {

                        fprintf(Asm, "push ");

                        TranslateToAsm(Node->left);

                        fprintf(Asm, "push ");

                        TranslateToAsm(Node->rght);

                        fprintf(Asm, "div\n");
                    }
                    else {
                        TranslateToAsm(Node->left);

                        TranslateToAsm(Node->rght);

                        fprintf(Asm, "div\n");
                    }

                    break;

                case ASG:

                    TranslateToAsm(Node->mid);

                    fprintf(Asm, "pop ");

                    TranslateToAsm(Node->left);

                    TranslateToAsm(Node->rght);

                    break;

                case OUT:

                    fprintf(Asm, "push ");

                    TranslateToAsm(Node->left);

                    fprintf(Asm, "out/n");

                    TranslateToAsm(Node->rght);

                    break;

                case INP:

                    fprintf(Asm, "in\n");

                    fprintf(Asm, "pop ");

                    TranslateToAsm(Node->left);

                    TranslateToAsm(Node->rght);

                    break;

                case BEG:

                    TranslateToAsm(Node->mid);

                    break;

                case IF:
                    break;

                case WHILE:
                    break;

                case LES:
                    break;

                case MOR:
                    break;

                case LOE:
                    break;

                case MOE:
                    break;

                case NOE:
                    break;

                case EQU:
                    break;

                default:
                    break;
            }

            break;

        default:
            break;
        }

    return OK;
}
//==============================================================================
