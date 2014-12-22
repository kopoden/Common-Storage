#include "list_functions.h"

int list_ctor (List* L) {

    L->first = (element*) calloc (1, sizeof(element));

    if (L->first == NULL) {
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

        return SPOILT;

    }

    if (L->first == NULL) {

        return SPOILT;

    }

    shft_to_first(L);
    int sum = 0;

    while (L->ptr->nxt != NULL) {

        sum++;
        shft_ptr_nxt(L);

        if ((L->ptr != L->first) && (L->ptr->prvs == NULL)) {

            return SPOILT;

        }
    }

    if (L->ptr->prvs == NULL && L->ptr != L->first) {

        return SPOILT;

    }


    if (sum < L->num_of_elements) {

        return LEAK;

    }

    return OK;
}
//============================================================================

//============================================================================
int list_dtor (List* L) {

    int check = check_ok(L);

    if (check != OK)
        return check;

    shft_to_first(L);

    while (L->ptr->nxt != NULL) {

        shft_ptr_nxt(L);

        free(L->ptr->prvs);

        L->ptr->prvs = NULL;

    }

    free(L->ptr);

    L->ptr = NULL;

    L->num_of_elements = 0;

    return OK;
}
//=============================================================================
void dumper (FILE* dump, List* L) {

    if (L == NULL || L->first == NULL) {

        fprintf(dump, "INCORRECT POINTER.DATA IS UNKNOWN\n");

        return;
    }

    shft_to_first(L);

    fprintf(dump, "FIRST ELEMENT ADRESS: 0x%p\nCURRENT ELEMENT ADRESS: %p\nNUMBER OF ELEMENTS: %d\n", \
            L->first, L->ptr, L->num_of_elements);

    while (L->ptr->nxt != NULL) {

        shft_ptr_nxt(L);

        fprintf(dump, "%s -- 0x%p\n", L->ptr->data, L->ptr);

    }

    fprintf(dump,"\n\n");

    return;
}
//==============================================================================
int find_str (List* L, char* String) {

    shft_to_first(L);

    while (L->ptr->nxt != NULL) {

        shft_ptr_nxt(L);

        if (strcmp(String, L->ptr->data) == 0)
            return OK; //There is an equal string in the list
    }

    return NOT_FOUND;
}
