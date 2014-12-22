#include <stdio.h>
#include <stdlib.h>

#include "d_l_list_functions.h"

int main() {

    List L;
    list_ctor(&L);

    printf("%d\n", inp_nxt(&L, "Mama mila ramu"));

    printf("%s\n", L.ptr->nxt->data);

    for (int i = 0; i < 1024*10; i++) { //1GB
        if (inp_nxt(&L, "Papa mil ramu") == OK) printf("input OK\n");
    }
    printf("END INPUT\n");

    while (L.ptr->nxt != NULL)
        shft_ptr_nxt(&L);
    printf("POINTER SHIFTED\n");

    //for (int i = 0; i < 1024*10; i++) { //1GB
    //    if (delete_cur(&L) == OK) printf("delete OK\n");
    //    else {
    //        printf("ERROR\n");
    //        break;
    //    }
    //}

    check_ok(&L);
    dumper(&L);

    list_dtor(&L);

    return 0;
}
