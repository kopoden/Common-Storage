#ifndef DIFFERENTIATOR_H_INCL
#define DIFFERENTIATOR_H_INCL

#include "TokenTree.h"

//=======================================================================================================
#define check( err_number )                                                                             \
    do {                                                                                                \
        switch (err_number) {                                                                           \
                                                                                                        \
            case OK:                                                                                    \
                                                                                                        \
                fprintf(logs,"function %s in function %s == OK\n", #err_number, __PRETTY_FUNCTION__);   \
                break;                                                                                  \
                                                                                                        \
            case DIFFERENTIATION_ERROR:                                                                 \
                                                                                                        \
                fprintf(logs,"function %s in function %s == DIFFERENTIATION_ERROR\n", #err_number, __PRETTY_FUNCTION__);   \
                return DIFFERENTIATION_ERROR;                                                           \
                                                                                                        \
                                                                                                        \
            case ERR_MEM:                                                                               \
                                                                                                        \
                fprintf(logs,"function %s in function %s == NOT ENOUGH MEMORY TO ALLOCATE\n", #err_number, __PRETTY_FUNCTION__);\
                return ERR_MEM;                                                                         \
                                                                                                        \
            case INVALID_TREE:                                                                          \
                                                                                                        \
                fprintf(logs,"function %s in function %s == INVALID TREE\n", #err_number, __PRETTY_FUNCTION__);                 \
                return INVALID_TREE;                                                                    \
                                                                                                        \
            case NULL_DATA_FIELD:                                                                       \
                                                                                                        \
                fprintf(logs,"function %s in function %s == NULL INFORMATION FIELD\n", #err_number, __PRETTY_FUNCTION__);       \
                return NULL_DATA_FIELD;                                                                 \
                                                                                                        \
            case SYNTAX_ERROR:                                                                          \
                                                                                                        \
                fprintf(logs,"function %s in function %s == SYNTAX ERROR\n", #err_number, __PRETTY_FUNCTION__);                 \
                return SYNTAX_ERROR;                                                                    \
                                                                                                        \
            case EMPTY_STRING:                                                                          \
                                                                                                        \
                fprintf(logs,"function %s in function %s == STRING IS EMPTY\n", #err_number, __PRETTY_FUNCTION__);              \
                return EMPTY_STRING;                                                                    \
                                                                                                        \
            case NULL_POINTER:                                                                          \
                                                                                                        \
                fprintf(logs,"function %s in function %s == INCORRECT POINTER TO SOMETHING\n", #err_number, __PRETTY_FUNCTION__);\
                return NULL_POINTER;                                                                    \
                                                                                                        \
            case INV_BRACKET_SEQ:                                                                       \
                                                                                                        \
                fprintf(logs,"function %s in function %s == INVALID BRACKET SEQUENCE\n", #err_number, __PRETTY_FUNCTION__);     \
                return INV_BRACKET_SEQ;                                                                 \
                                                                                                        \
            case DUMP_ERROR:                                                                            \
                                                                                                        \
                fprintf(logs,"function %s in function %s == CAN'T OPEN DUMP FILE\n", #err_number, __PRETTY_FUNCTION__);         \
                break;                                                                                  \
                                                                                                        \
            case UNKNOWN_TOKEN:                                                                         \
                                                                                                        \
                fprintf(logs,"function %s in function %s == UNKNOWN TOKEN\n", #err_number, __PRETTY_FUNCTION__);                \
                return UNKNOWN_TOKEN;                                                                   \
                                                                                                        \
            case UNKNOWN_SYMBOL:                                                                        \
                                                                                                        \
                fprintf(logs,"function %s in function %s == UNKNOWN SYMBOL IN ENTERED STRING\n", #err_number, __PRETTY_FUNCTION__);\
                return UNKNOWN_SYMBOL;                                                                  \
                                                                                                        \
            case LOG_FILE_ERROR:                                                                        \
                                                                                                        \
                printf("function %s in function %s == CAN'T OPEN OR REWRITE LOG FILE\n", #err_number, __PRETTY_FUNCTION__);     \
                return LOG_FILE_ERROR;                                                                  \
                                                                                                        \
            default:                                                                                    \
                fprintf(logs,"function %s in function %s == UNKNOWN ERROR\n", #err_number, __PRETTY_FUNCTION__);                \
                return UNKNOWN_ERROR;                                                                   \
        }                                                                                               \
    } while(0);                                                                                         \
//=======================================================================================================
extern Token* GlobalTokenSeq;
extern FILE* logs;
extern FILE* TeX;
//==============================================================================
int DivideIntoTokens (char* String, Token** TokenSequence, int* NumOfTokens);
//==============================================================================
int TokensDump (Token* TokenSequence, int NumOfTokens);
//==============================================================================
node* GetE();
//==============================================================================
node* GetSub();
//==============================================================================
node* GetDiv();
//==============================================================================
node* GetT();
//==============================================================================
node* GetDegree();
//==============================================================================
node* GetSin();
//==============================================================================
node* GetCos();
//==============================================================================
node* GetP();
//==============================================================================
node* GetN();
//==============================================================================
int MakeExpressionTree (node** expression);
//==============================================================================
node* Differentiation (node* expression);
//==============================================================================
int printHeader();
//==============================================================================
int printListOfLiterature();
//==============================================================================
int TexPrintNode(node* Node, int Previous);
//==============================================================================

#endif // DIFFERENTIATOR_H_INCL
