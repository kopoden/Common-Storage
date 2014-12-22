#include <stdlib.h>
#include <stdio.h>

#include "stack_functions.h"

//===========================================================
int stack_ctor (STACK_t* new_stack) {

    new_stack->stack_arr = (data_t*) malloc (0 * sizeof(data_t)); // Empty stack

    if (new_stack->stack_arr == 0) { //Not enough memory to allocate
        free(new_stack->stack_arr);
        return ERR_MEM;
    }

    new_stack->counter = 0; // Empty stack. Counter points to the zero element
    new_stack->max_size = 0;

    return OK; // Stack constructed
}
//======================================================

//======================================================
int push (STACK_t* Stack, const char* String) {

    int check = stack_state(Stack);

    if (check == FULL)
        return FULL;

    if (check == OUT_OF_STACK)
        return OUT_OF_STACK;

    int i = 0;
    Stack->stack_arr[Stack->counter].last = -1;

    while (String[i] != 0) {
        if (i >= str_lng) return TOO_LONG;
        Stack->stack_arr[Stack->counter].String[i] = String[i];
        (Stack->stack_arr[Stack->counter].last)++;
        i++;
    }
    Stack->counter++;

    return OK;
}
//======================================================

//======================================================
int pop (STACK_t* Stack, char* String, int size_str) {

    int check = stack_state(Stack);

    if (check == EMPTY)
        return EMPTY;

    if (check == OUT_OF_STACK)
        return OUT_OF_STACK;

    if (size_str <= Stack->stack_arr[Stack->counter - 1].last)
        return TOO_SHORT;

    Stack->counter--;
    for (int i = 0; i <= Stack->stack_arr[Stack->counter].last; i++)
        String[i] = Stack->stack_arr[Stack->counter].String[i];


    return OK;
}
//======================================================
int stack_resize (STACK_t* Stack, long int Size) {

    int check = stack_state(Stack);
    if (check == OUT_OF_STACK)
        return OUT_OF_STACK;

    Stack->stack_arr = (data_t*) realloc (Stack->stack_arr, sizeof(data_t) * Size);

    if (Stack->stack_arr == 0 && Size != 0) {
        free(Stack->stack_arr);
        return ERR_MEM;
    }

    Stack->max_size = Size;

    return OK;
}
//======================================================
//======================================================
int insrt (STACK_t* Stack, long int position, const char* String) {

    if ((position < 0) && (position >= Stack->max_size))
        return OUT_OF_STACK;

    int check = stack_state(Stack);

    if (check == OUT_OF_STACK)
        return OUT_OF_STACK;

    if (check == FULL)
        return FULL;

    Stack->counter++;

    for (long int END = Stack->counter - 1; END > position; END--)
        Stack->stack_arr[END] = Stack->stack_arr[END - 1];

    int i = 0;
    Stack->stack_arr[Stack->counter].last = -1;

    while (String[i] != 0) {
        if (i >= str_lng) return TOO_LONG;
        Stack->stack_arr[Stack->counter - 1].String[i] = String[i];
        Stack->stack_arr[Stack->counter - 1].last++;
        i++;
    }

    return OK;
}
//======================================================

//======================================================
int stack_state (STACK_t* Stack) {

    if ((Stack->counter < 0) || (Stack->stack_arr == 0) || (Stack->counter > Stack->max_size))
        return OUT_OF_STACK; //Stack is spoiled (can't push and pop)

    if (Stack->counter == Stack->max_size)
        return FULL;

    if ((Stack->counter == 0) && (Stack->stack_arr > 0))
        return EMPTY;   //Stack is empty(can't pop, but still can push).

    return OK;      //Stack is fully workable.
}
//======================================================

//======================================================

int stack_dtor(STACK_t* Stack) {

    free(Stack->stack_arr);

    Stack->stack_arr = NULL;               // Spoil the stack to prevent future incorrect using.
    Stack->counter = 0;
    Stack->max_size = 0;
    return OK;
}
//=====================================================

