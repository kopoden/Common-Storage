#include <stdio.h>
#include <stdlib.h>

#include "stack_functions.h"

int main() {
    STACK_t numbers;

    dumper(&numbers); //TEST DUMP 1. OUT

    stack_ctor(&numbers); //CREAT STACK

    dumper(&numbers); //TEST DUMP 2. EMPTY

    push(&numbers, 1); //PUSH ELEMENTS
    //push(&numbers, 7.3);

    dumper(&numbers); //TEST DUMP 3. 1 7.3

    double value = -1;
    printf("%d\n", pop(&numbers, &value));
    printf("%lg\n", value);

    printf("%d\n", pop(&numbers, &value));
    printf("%lg\n", value);

    dumper(&numbers);

    stack_dtor(&numbers);

    dumper(&numbers); //FINAL TEST DUMP

    printf("%d //OUT_OF_STACK", stack_ok(&numbers));
    return 0;
}
