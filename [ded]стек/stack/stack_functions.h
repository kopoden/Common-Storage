extern int stack_errno;

enum constants {
    OK,                 ///< Successful action.
    ERR_MEM,            ///< There is no enough memory to allocate.
    OUT_OF_STACK,       ///< Counter point at the segment is out of stack
    EMPTY              ///< Stack is empty.
};
//==================================================================
/*! \struct STACK_t

    \param  stack_arr   Stack pointer
    \param  counter     Current number of elements in stack
*/
struct STACK_t {
    double* stack_arr; ///
    long int counter;
};

//==================================================================
/*! \fn     void dumper (STACK_t* new_stack);
    \brief  Output error information and output stack to file "dump.txt"
*/
void dumper (STACK_t* new_stack);
//==================================================================
//==================================================================
/*! \fn     int stack_ctor (STACK_t* new_stack);
    \brief  Creates new stack.
*/
int stack_ctor (STACK_t* new_stack);
//==================================================================

//==================================================================
/*! \fn     int push (STACK_t* Stack, double element);
    \brief  Pushes the value onto the stack.

    \param      Stack       Stack pointer
    \param      element     Value to be pushed
*/
int push (STACK_t* Stack, double element);
//==================================================================

//==================================================================
/*! \fn     int pop (STACK_t* Stack, double* value);
    \brief  Gets the number from the stack.

    \param      Stack       Stack pointer
*/
int pop (STACK_t* Stack, double* value);
//==================================================================

//==================================================================
/*! \fn     int insrt (STACK_t* Stack, long int position, double element);
    \brief  Puts the number in any part of the stack.

    \param      Stack       Stack pointer
    \param      position    Position to insert
    \param      element     Value to be pushed
*/
int insrt (STACK_t* Stack, long int position, double element);
//==================================================================

//==================================================================
/*! \fn     int stack_ok (STACK_t* Stack);
    \brief  Checks stack's validity.

    \param      Stack       Stack pointer
*/
int stack_ok (STACK_t* Stack);
//==================================================================

//==================================================================
/*! \fn     int stack_dtor(STACK_t* Stack);
    \brief  Erases the content of stack.

    \param      Stack       Stack pointer
*/
void stack_dtor(STACK_t* Stack);
