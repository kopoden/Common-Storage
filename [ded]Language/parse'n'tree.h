#ifndef PARSE_N_TREE_H_INCL
#define PARSE_N_TREE_H_INCL

#include "TokenTree.h"

//==============================================================================================================
int DivideIntoTokens(char* String, Token** TokenSequence, int* NumOfTokens);
//==============================================================================================================
int TokensDump (Token* TokenSequence, int NumOfTokens);
//==============================================================================================================
int MakeExpressionTree(node** Expression);
//==============================================================================================================
node* GetBeg();
//==============================================================================================================
node* GetInp();
//==============================================================================================================
node* GetOut();
//==============================================================================================================
node* GetIf();
//==============================================================================================================
node* GetWhile();
//==============================================================================================================
node* GetAsg();
//==============================================================================================================
node* GetLES();
//==============================================================================================================
node* GetMOR();
//==============================================================================================================
node* GetLOE();
//==============================================================================================================
node* GetMOE();
//==============================================================================================================
node* GetNOE();
//==============================================================================================================
node* GetEQU();
//==============================================================================================================
node* GetAdd();
//==============================================================================================================
node* GetSub();
//==============================================================================================================
node* GetDiv();
//==============================================================================================================
node* GetMul();
//==============================================================================================================
node* GetBracket();
//==============================================================================================================
node* GetVar();
//==============================================================================================================
int TranslateToAsm (node* Node);
//==============================================================================================================

#endif //PARSE'N'TREE_H_INCL
