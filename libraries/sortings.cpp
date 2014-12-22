#include <stdlib.h>
#include <stdio.h>

#define ASSERT( cond )                           \
        do {                                         \
            if ( ! ( cond ) ) {                      \
                printf ( "FAIL %s in %s, %s ( %d )", \
                #cond, __PRETTY_FUNCTION__,          \
                __FILE__, __LINE__ );                \
                abort();                             \
            } \
        } while (0);

//===============================================================
/*! void string_q_sort(char** text, long int Start, long int End);
    \brief Algorithm of quick sorting by the first letter in a line
*/
//==================================================================
void FLqSort(char** text, long int Start, long int End) {

    long int n_base = (Start + End)/2;
    char Char = text[n_base][0];
    long int L = Start;
    long int R = End;

    do {

        ASSERT((L >= Start) && (L <= End) && (R >= Start) && (R <= End));
        while (text[L][0] < Char) L++;
        while (text[R][0] > Char) R--;

        if (L <= R) {
            char* p = text[L];
            text[L] = text[R];
            text[R] = p;
            L++;
            R--;
        }

    } while (L <= R);

    if (R > Start) FLqSort(text, Start, R);
    if (L < End) FLqSort(text, L, End);

}
