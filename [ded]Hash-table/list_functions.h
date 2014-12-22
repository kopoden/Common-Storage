#ifndef _LIST_FUNCTIONS_H_INCL_
#define _LIST_FUNCTIONS_H_INCL_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum errors {
    OK,                 ///< Success.
    NULL_POINTER,       ///< Incorrect list, hash-table or FILE pointer.
    ERR_MEM,            ///< Impossible to allocate memory
    EMPTY,              ///< List is empty.
    NOT_EMPTY,          ///< All other states.
    ERR_ACCESS,         ///< Impossible to delete first element.
    SPOILT,             ///< List is not able to work.
    LAST_REACHED,       ///< -//-
    FIRST_REACHED,      ///< -//-
    NOT_FOUND,          ///< Can't found such a string.
    LEAK,               ///< There is a leak in a list.
    HASH_FUNCTION_ERROR ///< Hash returned by hash-function is incorrect.
};

typedef char* data_t;

struct element {    ///< Structure of element
    data_t data;    ///< Content
    element* nxt;   ///< Pointer to the next element
    element* prvs;  ///< Pointer to the prior element
};

struct List {
    element* ptr;           ///< pointer to the current element
    element* first;         ///< pointer to the first element of the list
    int num_of_elements;    ///< number of elements in a list
};

//============================================================================
/*! \fn    int list_ctor (List* L);
    \brief Constructor of doubly-linked list
*/
//============================================================================
int list_ctor (List* L);
//============================================================================

//============================================================================
/*! \fn    int inp_nxt (List* L, data_t data);
    \brief Insert new element right
*/
//============================================================================
int inp_nxt (List* L, data_t data);
//============================================================================

//============================================================================
/*! \fn    int inp_prvs (List* L, data_t data);
    \brief Insert new element left
*/
//============================================================================
int inp_prvs (List* L, data_t data);

//============================================================================
/*! \fn    int delete_cur (List* L);
    \brief Extract current element
*/
//============================================================================
int delete_cur (List* L);

//============================================================================
/*! \fn    int shft_ptr_nxt (List* L);
    \brief Shift pointer to the next element
*/
//============================================================================
int shft_ptr_nxt (List* L);

//============================================================================
/*! \fn    int shft_ptr_prvs (List* L);
    \brief Shift pointer to the previous element
*/
//============================================================================
int shft_ptr_prvs (List* L);

//============================================================================
/*! \fn    int shft_to_first (List* L);
    \brief Shift pointer to the beginning
*/
//============================================================================
int shft_to_first (List* L);

//============================================================================
/*! \fn    int check_empty (List* L);
    \brief Check if list is empty
*/
//============================================================================
int check_empty (List* L);

//============================================================================
/*! \fn    int check_ok (List* L);
    \brief Checks the validity of a list
*/
//============================================================================
int check_ok (List* L);

//============================================================================
/*! \fn    int list_dtor (List* L);
    \brief Destructor of doubly-linked list
*/
//============================================================================
int list_dtor (List* L);

//============================================================================
/*! \fn    void dumper (FILE* dump, List* L);
    \brief Outputs all available information about list
*/
//============================================================================
void dumper (FILE* dump, List* L);

//============================================================================
/*! \fn    int find_str (List* L);
    \brief Finds the same string in a list of strings.
*/
//============================================================================
int find_str (List* L, char* String);

#endif //_LIST_FUNCTIONS_H_INCL_
