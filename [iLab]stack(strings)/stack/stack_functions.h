enum constants {
    OK,                 ///< Successful action.
    EMPTY,              ///< Stack is empty.
    FULL,               ///< Stack is full.
    ERR_MEM,            ///< There is no enough memory to allocate.
    OUT_OF_STACK,       ///< Counter point at the segment is out of stack or pointer of stack array = 0.
    TOO_LONG,           ///< The string is too long to be pushed onto the stack.
    TOO_SHORT           ///< The string is too short to accept information from the stack.
};

//==================================================================
/*! \struct STACK_t

    \param  stack_arr   Stack pointer
    \param  counter     Current number of elements in stack
*/
#define str_lng 5

typedef struct {
    char String[str_lng];
    int last;
} data_t;

struct STACK_t {
    data_t* stack_arr; ///
    long int counter;
    long int max_size;
};
//==================================================================
/*! \fn     int stack_ctor (STACK_t* new_stack);
    \brief  Creates new stack.
*/
int stack_ctor (STACK_t* new_stack);
//==================================================================

//==================================================================
/*! \fn     int push (STACK_t* Stack, const char* String);
    \brief  Pushes the value onto the stack.

    \param      Stack       Stack pointer
    \param      value     Value to be pushed
*/
int push (STACK_t* Stack, const char* String);
//==================================================================

//==================================================================
/*! \fn     int pop (STACK_t* Stack, char* String, int size_str);
    \brief  Gets the number from the stack.

    \param      Stack       Stack pointer
*/
int pop (STACK_t* Stack, char* String, int size_str);
//==================================================================
//==================================================================
int stack_resize (STACK_t* Stack, long int SIZE);
//==================================================================
//==================================================================
/*! \fn     int insrt (STACK_t* Stack, long int position, const char* Sting);
    \brief  Puts the number in any part of the stack.

    \param      Stack       Stack pointer
    \param      position    Position to insert
    \param      Sting       Value to be pushed
*/
int insrt (STACK_t* Stack, long int position, const char* String);
//==================================================================

//==================================================================
/*! \fn     int stack_state (STACK_t* Stack);
    \brief  Checks stack's validity.

    \param      Stack       Stack pointer
*/
int stack_state (STACK_t* Stack);
//==================================================================

//==================================================================
/*! \fn     int stack_dtor(STACK_t* Stack);
    \brief  Erases the content of stack.

    \param      Stack       Stack pointer
*/
int stack_dtor(STACK_t* Stack);
