#ifndef _HASH_TABLE_H_INCL_
#define _HASH_TABLE_H_INCL_

#include <io.h>
#include <locale.h>

#include "list_functions.h"

//=================================================================
const int MAX_SIZE = 150000;
const int SIZE_OF_HASH_TABLE = 10093;
//=================================================================
//============================================================================
/*! \fn    int HT_ctor (List* HT);
    \brief Constructor of hash-table
*/
//============================================================================
int HT_ctor (List* HT);
//=================================================================
//============================================================================
/*! \fn    int HT_filling (char** words, List* HT, int hf (char*));
    \brief Fill the table with words from the text with a help of a specific hash-function
*/
//============================================================================
int HT_filling (char** words, int num_of_words, List* HT, int hf (char*));
//=================================================================
//============================================================================
/*! \fn    void HT_ok (List* HT);
    \brief Checks validity of a hash-table
*/
//============================================================================
int HT_ok (List* HT);
//=================================================================
//============================================================================
/*! \fn    int HT_dtor (List* HT);
    \brief Destructor of hash-table
*/
//============================================================================
int HT_dtor (List* HT);
//=================================================================
//============================================================================
/*! \fn    void HT_dumper (FILE* dump, List* HT);
    \brief Outputs all available information about hash-table
*/
//============================================================================
void HT_dumper (FILE* dump, List* HT);
//=================================================================
//============================================================================
/*! \fn    int count_and_output(FILE* output, List* HT);
    \brief Counts elements in a list and fill the ".csv" table.
*/
//============================================================================
int count_and_output(FILE* output, List* HT);
//=================================================================
int make_buffer(FILE* input, char** buffer, long int* leng);
//=================================================================
int make_words_array(char*** words, char* buffer, long int length_of_file, int* num_of_words);
//============================================================================
#endif // _HASH_TABLE_H_INCL
