#include "differentiator.h"
#include "optimizations.h"

#define MAX_STRING_LENG 1000
//===============================================================
Token* GlobalTokenSeq = NULL; // Global
FILE* logs = NULL;
FILE* TeX = NULL;
//===============================================================
int main() {

    logs = fopen("logs.txt", "w");

    if (logs == NULL) {

        printf("CAN'T CREATE OR REWRITE LOG FILE");

        return LOG_FILE_ERROR;
    }

    char* s = (char*) calloc (MAX_STRING_LENG, sizeof(char));

    if (s == NULL)
        check(ERR_MEM);

    gets(s);

    Token* TokenSequence = NULL;

    int NumOfTokens = 0;

    check(DivideIntoTokens(s, &TokenSequence, &NumOfTokens)); // Divide new string into tokens

    check(TokensDump(TokenSequence, NumOfTokens));

    node* expression = NULL;

    GlobalTokenSeq = TokenSequence;

    check(MakeExpressionTree(&expression));

    check(tree_dump(expression));

    node* derivative = NULL;

    derivative = Differentiation(expression);

    if (derivative == NULL)
        check(DIFFERENTIATION_ERROR);

    check(tree_dump(derivative));

    TeX = fopen("FinalDocument.tex", "w");

    check(printHeader());

    fprintf(TeX,    "\\Large{\n"
                    "{{ 1) Original function: }}\n"
                    "$$ f(x) = {");

    check(TexPrintNode(expression, ROOT));

    fprintf(TeX,    "} $$\n"
                    "{{ 2) Derivative: }}\n"
                    "$$ f'(x) = {");

    check(TexPrintNode(derivative, ROOT));

    fprintf(TeX,    "} $$\n");

    check(O1(&derivative)); // Makes the result more pleasant for human's eye

    fprintf(TeX,    "{{ 3) After the first optimization: }}\n"
                    "$$ f'(x) = {");

    check(TexPrintNode(derivative, ROOT));

    fprintf(TeX,    "} $$\n");

    check(O2(&derivative)); // Makes the result more pleasant for human's eye

    fprintf(TeX,    "{{ 4) This function has already been optimized twice: }}\n"
                    "$$ f'(x) = {");

    check(TexPrintNode(derivative, ROOT));

    fprintf(TeX,    "} $$\n");

    check(printListOfLiterature());

    free(s);
    s = NULL;

    //tree_dtor(derivative);
    derivative = NULL;

    //tree_dtor(expression);
    expression = NULL;

    fclose(TeX);

    return 0;
}
