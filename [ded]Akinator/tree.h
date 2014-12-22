#ifndef _TREE_H_INCL_
#define _TREE_H_INCL_

#include <stdio.h>
#include <stdlib.h>

enum errors {
    OK = 0,
    ERR_MEM = 1,
    NULL_POINTER = 2,
    INVALID_TREE = 3,
    NULL_DATA_FIELD = 4

};

typedef char* data_t;
const int MAX_STRING_LENG = 100; //Max length of information in node->info

struct node {

    data_t info;
    node* left;
    node* rght;

};

//================================================================================
node* grow_from_file(FILE* base, FILE* logs);
//================================================================================
int create_new_leaf(node** new_leaf, char* String);
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
void tree_dump (node* tree);
//================================================================================
void tree_dtor (node* tree);
//================================================================================

#endif // _TREE_H_INCL
