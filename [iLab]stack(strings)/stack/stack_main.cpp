#include <stdio.h>
#include <stdlib.h>

#include "stack_functions.h"

int main() {

    STACK_t strings;

    printf("%d - RES\n", stack_ctor(&strings));

    if (stack_resize(&strings, 1024 * 1024 * 10) == ERR_MEM) {
        printf("CAN'T ALLOCATE MEMORY\n");
    }
    else {
        printf("ALLOCATION SUCCESSFUL\n");

        for (long int i = 0; i < 1024 * 1024 * 10; i++) { // Test 2GB
            int check = push(&strings, "VALGRIND.TEST");

            if (check == FULL) {
                printf("STACK IS FULL\n");
                break;
            }

            if (check == TOO_LONG) {
                printf("STRING IS TOO LONG\n");
                break;
            }
        }
    }

    char* value = (char*) calloc (5, sizeof(char));

    int check = pop(&strings, value, 5);

    if (check == TOO_SHORT) {
        printf("STRING IS TOO SHORT\n");
    }

    printf("%s\n", value);

    stack_dtor(&strings);

    return 0;
}
