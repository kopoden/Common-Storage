#include <stdlib.h>
#include <stdio.h>

#include "stack_functions.h"

int stack_errno = OUT_OF_STACK;                                                                                                                                               \
//======================================================
void dumper (STACK_t* stack_to_dump) {

    FILE* dump = fopen("dump.txt", "a");
    fprintf(dump, "***********************************************************************\n");
    if ((stack_to_dump == 0) || (stack_to_dump->stack_arr == 0))
        stack_errno = OUT_OF_STACK;
    else
    if ((stack_to_dump->counter == 0) && (stack_to_dump->stack_arr != 0))
        stack_errno = EMPTY;
    switch (stack_errno) {
        case OK:
            fprintf(dump, "FUNCTION: %s\n STACK IS VALID\n FILE: %s  (line %d )\n",
                                   __PRETTY_FUNCTION__,
                                   __FILE__, __LINE__ );
            fprintf(dump, "DATA: ");
            for (long int i = 0; i < stack_to_dump->counter; i++)
                fprintf(dump, "%lg ", stack_to_dump->stack_arr[i]);
            fprintf(dump, "\n\n");
            break;
        case ERR_MEM:
            fprintf(dump, "FUNCTION: %s\n ERROR: NOT ENOUGH MEMORY TO ALLOCATE\n FILE: %s  (line %d )\n",
                                    __PRETTY_FUNCTION__,
                                   __FILE__, __LINE__ );
            fprintf(dump, "DATA: UNKNOWN\n\n");
            break;
        case OUT_OF_STACK:
            fprintf(dump, "FUNCTION: %s\n ERROR: POINTER IS OUT OF STACK\n FILE: %s  (line %d )\n",
                                    __PRETTY_FUNCTION__,
                                   __FILE__, __LINE__ );
            fprintf(dump, "DATA: UNKNOWN\n\n");
            break;
        case EMPTY:
            fprintf(dump, "FUNCTION: %s\n ERROR: STACK IS EMPTY. IMPOSSIBLE TO POP\n FILE: %s  (line %d )\n",
                                   __PRETTY_FUNCTION__,
                                   __FILE__, __LINE__ );
            fprintf(dump, "DATA: EMPTY\n\n");
            break;
        default:
            break;
    }

    fclose(dump);
    dump = 0;

    return;
}
//======================================================
int stack_ctor (STACK_t* new_stack) {

    stack_errno = OK;

    new_stack->stack_arr = (double*) calloc (0, sizeof(double)); // Empty stack
    new_stack->counter = 0; // Zero element

    if (new_stack->stack_arr == 0) { //Not enough memory to allocate
        free(new_stack->stack_arr);
        stack_errno = ERR_MEM;
        return ERR_MEM;
    }

    return OK;
}
//======================================================

//======================================================
int push (STACK_t* Stack, double element) {

    stack_errno = stack_ok(Stack);

    if (stack_errno == OUT_OF_STACK) {
        return OUT_OF_STACK;
    }

    Stack->counter++;
    double* buf = Stack->stack_arr;
    Stack->stack_arr = (double*) realloc (Stack->stack_arr, sizeof(double) * Stack->counter);

    if (Stack->stack_arr == 0) { //Lack of memory
        Stack->stack_arr = buf;
        Stack->counter--;
        stack_errno = ERR_MEM;
        return ERR_MEM;
    }
    Stack->stack_arr[Stack->counter - 1] = element;

    return OK;
}
//======================================================

//======================================================
int pop (STACK_t* Stack, double* value) {

    stack_errno = stack_ok(Stack);

    if (stack_errno != OK) {
        return stack_errno;
    }

    *value = Stack->stack_arr[Stack->counter - 1];
    Stack->counter--;
    double* buf = Stack->stack_arr;
    //Realloc frees the stack if gets zero size. So after the first push it has a minimal size of 1 element.
    if (Stack->counter == 0) {
        free(Stack->stack_arr);
        Stack->stack_arr = (double*) calloc (0, sizeof(double));
    }
    else
        Stack->stack_arr = (double*) realloc (Stack->stack_arr, sizeof(double) * Stack->counter);

    if (Stack->stack_arr == 0) {
        Stack->stack_arr = buf;
        Stack->counter++;
        stack_errno = OUT_OF_STACK;
        return OUT_OF_STACK;
    }

        return OK;
}
//======================================================

//======================================================
int insrt (STACK_t* Stack, long int position, double element) {

    stack_errno = stack_ok(Stack);

    if (stack_errno == OUT_OF_STACK) {
        return OUT_OF_STACK;
    }

    if ((position > Stack->counter) || (position < 0)) {
        stack_errno = OUT_OF_STACK; // Impossible to insert into these positions.
        return OUT_OF_STACK;
    }

    Stack->counter++;
    double* buf = Stack->stack_arr;
    Stack->stack_arr = (double*) realloc (Stack->stack_arr, sizeof(double) * Stack->counter);

    if (Stack->stack_arr == 0) {
        Stack->stack_arr = buf;
        Stack->counter--;
        stack_errno = ERR_MEM;
        return ERR_MEM;
    }

    for (long int END = Stack->counter - 1; END >= position; END--)
        Stack->stack_arr[END] = Stack->stack_arr[END - 1];

    Stack->stack_arr[position] = element;

    return OK;
}
//======================================================

//======================================================
int stack_ok (STACK_t* Stack) {

    if ((Stack->counter < 0) || (Stack->stack_arr == 0))
        return OUT_OF_STACK; //Stack is spoiled (can't push and pop)

    if ((Stack->counter == 0) && (Stack->stack_arr > 0))
        return EMPTY;   //Stack is empty(can't pop, but still can push).

        return OK;      //Stack is fully workable.
}
//======================================================

//======================================================

void stack_dtor(STACK_t* Stack) {

    free(Stack->stack_arr);

    Stack->stack_arr = NULL;               // Spoil the stack to prevent future incorrect using.
    Stack->counter = 0;     //

    return;
}
//=====================================================

