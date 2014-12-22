#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack_functions.h"

//===========================================================
STACK_t* stack_ctor ( void ) {

    STACK_t* new_stack = (STACK_t*) calloc (1, sizeof(STACK_t)); // Empty stack

    if (new_stack == 0) { //Not enough memory to allocate
        free(new_stack->stack_arr);
        return NULL;
    }
	new_stack->stack_arr = (data_t*) calloc (0, sizeof(data_t));

    new_stack->counter = 0; // Empty stack. Counter points to the zero element
    new_stack->max_size = 0;

    return new_stack; // Stack constructed
}
//======================================================

//======================================================
int push (STACK_t* Stack, data_t* Struct) {

    int check = stack_state(Stack);

    if (check == FULL)
        return FULL;

    if (check == OUT_OF_STACK)
        return OUT_OF_STACK;

    memcpy(&Stack->stack_arr[Stack->counter], Struct, sizeof(data_t));
    Stack->counter++;
    return OK;
}
//======================================================

//======================================================
data_t* pop (STACK_t* Stack) {

    int check = stack_state(Stack);

    if (check == EMPTY)
        return NULL;

    if (check == OUT_OF_STACK)
       return NULL;

    Stack->counter--;
    return &Stack->stack_arr[Stack->counter];
}
//======================================================
int stack_resize (STACK_t* Stack, int Size) {

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
int insrt (STACK_t* Stack, int position, data_t* Struct) {

    if ((position < 0) && (position >= Stack->max_size))
        return OUT_OF_STACK;

    int check = stack_state(Stack);

    if (check == OUT_OF_STACK)
        return OUT_OF_STACK;

    if (check == FULL)
        return FULL;

    Stack->counter++;

    for (int END = Stack->counter - 1; END > position; END--) {
        strcpy(Stack->stack_arr[END].String, Stack->stack_arr[END - 1].String);
        Stack->stack_arr[END].last = Stack->stack_arr[END - 1].last;
    }

    memcpy(&Stack->stack_arr[position], Struct, sizeof(data_t));

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

void stack_dtor(STACK_t* Stack) {

    free(Stack->stack_arr);
    Stack->stack_arr = NULL;

    free(Stack);
	Stack = NULL;

    return;
}
//=====================================================

