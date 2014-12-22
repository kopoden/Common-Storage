#include "parse'n'tree.h"

//=================================================================================
Token* GlobalTokenSeq = NULL;
FILE* logs = NULL;
FILE* Asm = NULL;
//=================================================================================
//=================================================================================

int main(int argc, char* argv[]) {

    /*if (argv[1] == NULL) {

        printf("INPUT SOURCE FILE\n");

        return NULL_POINTER;

    }*/
//=================================================================================
//========================== READ SOURCE FILE =====================================
//=================================================================================
    FILE* source = fopen("source.txt", "r");

    Asm = fopen("res.txt", "w");

    logs = fopen("logs.txt", "w");

    fseek(source, 0, SEEK_END);

    int FileLength = 0;

    FileLength = ftell(source);

    fseek(source, 0, SEEK_SET);

    char* code = (char*) calloc (FileLength, sizeof(char));

    fread(code, sizeof(char), FileLength, source);
//=================================================================================
//========================= DIVIDE CODE INTO TOKENS ===============================
//=================================================================================

    Token* TokenSeq = NULL;

    int NumOfTokens = 0;

    DivideIntoTokens(code, &TokenSeq, &NumOfTokens);

    TokensDump(TokenSeq, NumOfTokens);

    GlobalTokenSeq = TokenSeq;

    node* expression = NULL;

    MakeExpressionTree(&expression);

    tree_dump(expression);

    TranslateToAsm(expression);

    fclose(Asm);
    fclose(logs);

    return 0;
}
