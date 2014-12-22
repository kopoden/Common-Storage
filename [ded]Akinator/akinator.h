#ifndef _AKINATOR_H_INCL_
#define _AKINATOR_H_INCL_

#include "tree.h"

//=======================================================================
void print_vert (FILE* data_base, node* vert, FILE* logs);
//=======================================================================
int save_data (FILE* data_base, node* tree, FILE* logs);
//=======================================================================
int game (node* cur_node, FILE* logs);
//=======================================================================

#endif // _AKINATOR_H_INCL_
