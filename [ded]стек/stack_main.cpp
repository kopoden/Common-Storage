#include <stdio.h>
#include <stdlib.h>

#include "stack_functions.h"

int main() {
    STACK_t numbers;

    dumper(&numbers); //TEST DUMP 1. OUT

    stack_ctor(&numbers);

    dumper(&numbers); //TEST DUMP 2. EMPTY

    push(&numbers, 1);
    insrt(&numbers, 0, 0.123);

    dumper(&numbers); //TEST DUMP 3. 0.123 1

    double value;
    printf("%d\n", pop(&numbers, &value));
    printf("%lg\n", value);

    printf("%d\n", pop(&numbers, &value));
    printf("%lg\n", value);

    stack_dtor(&numbers);

    dumper(&numbers); //FINAL TEST DUMP

    printf("%d", stack_ok(&numbers));
    return 0;
}
