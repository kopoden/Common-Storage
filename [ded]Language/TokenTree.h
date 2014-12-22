#ifndef _TREE_H_INCL_
#define _TREE_H_INCL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//==========================================================================
enum Errors {

    UNKNOWN_ERROR,
    EMPTY_STRING,
    OK,
    ERR_MEM,
    NULL_POINTER,
    INVALID_TREE,
    NULL_DATA_FIELD,
    SYNTAX_ERROR,
    INV_BRACKET_SEQ,
    UNKNOWN_TOKEN,
    UNKNOWN_SYMBOL,
    LOG_FILE_ERROR,
    DUMP_ERROR,
    DIFFERENTIATION_ERROR,
    ERROR_IN_TREE_EXPRESSION

};
//==========================================================================
struct Token {

    char* Value;
    double nValue;
    int Type;
    int Oper;

};
//==========================================================================
enum Functions {

    NONE = -1,
    ADD,
    SUB,
    MUL,
    DIV,
    ASG,
    OUT,
    INP,
    BEG,
    END,
    IF,
    WHILE,
    LES,
    MOR,
    LOE,
    MOE,
    NOE,
    EQU

};
//==========================================================================
enum TokenTypes {

    ROOT,
    VAR,
    NUM,
    FUN,
    OBRACKET,
    CBRACKET

};
//==========================================================================
typedef Token data_t;
//==========================================================================
struct node {

    data_t* info;
    node* left;
    node* rght;
    node* mid;
    double CurVal;

};
//================================================================================
int delete_node(node* Node);
//================================================================================
int node_cpy(node** NewNode, node* OldNode);
//================================================================================
int tree_cpy(node** NewTree, node* OldTree);
//================================================================================
int create_new_leaf (node** new_leaf, const char* Val, double nVal, int TokenType, int Operation);
//================================================================================
int add_left (node* parent, node* descendent);
//================================================================================
int add_rght (node* parent, node* descendent);
//================================================================================
int turn_rght (node** tree);
//================================================================================
int turn_left (node** tree);
//================================================================================
int tree_ok (node* tree);
//================================================================================
int tree_dump (node* tree);
//================================================================================
int tree_dtor (node* tree);
//================================================================================
#endif // _TREE_H_INCL
