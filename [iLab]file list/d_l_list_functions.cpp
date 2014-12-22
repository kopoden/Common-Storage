#include <stdio.h>
#include <stdlib.h>
#include "d_l_list_functions.h"


int list_ctor (List* L) {

    L->first = (element*) calloc (1, sizeof(element));

    if (L->first == NULL) {
        free(L->first);
        return ERR_MEM;
    }

    L->first->nxt = NULL;
    L->first->prvs = NULL;
    L->first->data = 0;
    L->num_of_elements = 0;

    L->ptr = L->first;

    return OK;
}
//============================================================================

//============================================================================
int inp_prvs (List* L, data_t value) {

    if (L->ptr == NULL)
        return SPOILT;

    if (L->ptr->prvs == NULL && L->ptr != L->first)
        return SPOILT;

    if (L->ptr->prvs != NULL) {

        element* buf = (element*) calloc (1, sizeof(element));

        if (buf == NULL) {
            free(buf);
            return ERR_MEM;
        }
        L->ptr->prvs->nxt = buf;
        buf->prvs = L->ptr->prvs;
        buf->nxt = L->ptr;
        L->ptr->prvs = buf;
    }
    else {

        element* buf = (element*) calloc (1, sizeof(element));

        if (buf == NULL) {
            free(buf);
            return ERR_MEM;
        }

        buf->prvs = NULL;
        buf->nxt = L->ptr;
        L->ptr->prvs = buf;
        L->first = buf;
    }
    //Assign value
    L->ptr->prvs->data = value;
    L->num_of_elements++;
    return OK;
}
//============================================================================

//============================================================================
int inp_nxt (List* L, data_t value) {

    if (L->ptr == NULL)
        return SPOILT;

    if (L->ptr->nxt != NULL) {

        element* buf = (element*) calloc (1, sizeof(element));

        if (buf == NULL) {
            free(buf);
            return ERR_MEM;
        }
        L->ptr->nxt->prvs = buf;
        buf->prvs = L->ptr;
        buf->nxt = L->ptr->nxt;
        L->ptr->nxt = buf;
    }
    else {
        element* buf = (element*) calloc (1, sizeof(element));

        if (buf == NULL) {
            free(buf);
            return ERR_MEM;
        }

        buf->nxt = NULL;
        buf->prvs = L->ptr;
        L->ptr->nxt = buf;
    }
    //Assign value
    L->ptr->nxt->data = value;
    L->num_of_elements++;
    return OK;
}
//============================================================================

//============================================================================
int delete_cur (List* L) {

    if (L->ptr == NULL)
        return SPOILT;

    if (L->ptr == L->first)
        return ERR_ACCESS;

    if (L->ptr->prvs == NULL)
        return SPOILT;

    if (L->ptr->nxt == NULL) {
        L->ptr->prvs->nxt = NULL;
    }
    else {
    L->ptr->nxt->prvs = L->ptr->prvs;
    L->ptr->prvs->nxt = L->ptr->nxt;
    }

    L->ptr = L->ptr->prvs;
    L->num_of_elements--;
    return OK;

}
//============================================================================

//============================================================================
int shft_ptr_nxt (List* L) {

    if (L->ptr == NULL)
        return SPOILT;

    if (L->ptr->nxt == NULL)
        return LAST_REACHED;

    L->ptr = L->ptr->nxt;
    return OK;
}
//============================================================================

//============================================================================
int shft_ptr_prvs (List* L) {

    if (L->ptr == L->first)
        return FIRST_REACHED;

    if (L->ptr == NULL || L->ptr->prvs == NULL)
        return SPOILT;

    L->ptr = L->ptr->prvs;
    return OK;
}
//============================================================================

//============================================================================
int shft_to_first (List* L) {

    if (L->first == NULL)
        return SPOILT;

    L->ptr = L->first;
    return OK;
}
//============================================================================

//============================================================================
int check_empty (List* L) {

    if (L->num_of_elements == 0)
        return EMPTY;

        return NOT_EMPTY;
}
//============================================================================

//============================================================================
int check_ok (List* L) {

    if (L == NULL) {
        printf("AN INCORRECT POINTER TO THE LIST\n");
        return SPOILT;
    }

    if (L->first == NULL) {
        printf("AN INCORRECT POINTER TO THE FIRST ELEMENT\n");
        return SPOILT;
    }

    shft_to_first(L);
    int sum = 0;

    while (L->ptr->nxt != NULL) {
        sum++;
        shft_ptr_nxt(L);
        if ((L->ptr != L->first) && (L->ptr->prvs == NULL)) {
            printf("LIST HAS DEFECTS IN IT'S STRUCTURE\n");
            return SPOILT;
        }
    }

    if (L->ptr->prvs == NULL) {
        printf("LIST HAS DEFECTS IN IT'S STRUCTURE\n");
        return SPOILT;
    }


    if (sum < L->num_of_elements) {
        printf("THERE IS A LEAK OF %d ELEMENTS\n", L->num_of_elements - sum);
        return LEAK;
    }
    printf("CHECK OK\n");
    return OK;
}
//============================================================================

//============================================================================
void list_dtor (List* L) {

    shft_to_first(L);

    while (L->ptr->nxt != NULL) {
        shft_ptr_nxt(L);
        free(L->ptr->prvs);
        L->ptr->prvs = NULL;
    }

    free(L->ptr);
    L->ptr = NULL;
    L->num_of_elements = 0;
    return;
}
//=============================================================================
void dumper (List* L) {

    printf("\n**********************LIST*DUMP*********************************\n");
    if (L == NULL || L->first == NULL) {
        printf("INCORRECT POINTER.DATA IS UNKNOWN");
        return;
    }

    shft_to_first(L);
    while (L->ptr->nxt != NULL) {
        shft_ptr_nxt(L);
        printf(" == %s\n", L->ptr->data);
    }
    printf("\n****************************************************************\n");
}
