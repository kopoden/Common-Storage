/*! \mainpage

THE LIST OF TASKS AND FUNCTION.

//////////////////////////////////////////////////////////////////////// \n
//Task C. 2008. Variant 1. \n
void deleting_spaces (); \n
//////////////////////////////////////////////////////////////////////// \n

//Task C. 2007. Variant 4. \n
void reverse_words (); \n
//////////////////////////////////////////////////////////////////////// \n

//Task C. 2008. Variant 4. \n
void sum_digits_on_diagonal_square_matrix (); \n
//////////////////////////////////////////////////////////////////////// \n

//Task C. 2007. Variant 9. \n
void add_to_binary_digits (); \n
//////////////////////////////////////////////////////////////////////// \n

//Task D. 2007. Variant 3. \n
int MIN (int elem1, int elem2); \n
void find_the_biggest_white_square(); \n
//////////////////////////////////////////////////////////////////////// \n

//Task C. 2008. Variant 9. \n
void delete_duplicates(); \n
//////////////////////////////////////////////////////////////////////// \n

//Task C. 2007. Variant 5. \n
void alphabetic_sort (char** names, int* marks, const int START, const int END); \n
void rating_sort (char** names, int* marks, const int START, const int END); \n
void sort_students(); \n
//////////////////////////////////////////////////////////////////////// \n

//Task C. 2008. Variant 7. \n
int digit_sum(int n); \n
void four_digit_numbers(); \n
//////////////////////////////////////////////////////////////////////// \n

//Task C. 2007. Variant 6. \n
void numbers_free_of_squares(); \n
//////////////////////////////////////////////////////////////////////// \n

*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <iostream>

/*!  ASSERT( cond )

     \b Works only if DEBUG is defined.

     \brief   This macros checks the condition in brackets.

     If it's false, program shows message about an error and finishes immediately.

*/

//#define DEBUG

#ifdef DEBUG
    #define ASSERT( cond )                       \
        if ( ! ( cond ) )                        \
        {                                        \
            printf ( "FAIL %s in %s, %s ( %d )", \
            #cond, __PRETTY_FUNCTION__,          \
            __FILE__, __LINE__ );                \
            abort();                             \
        }
#else
    #define ASSERT( cond ) ;
#endif

////////////////////////////////////////////////////////////////////////
//Task C. 2008. Variant 1.
void deleting_spaces ();
////////////////////////////////////////////////////////////////////////

//Task C. 2007. Variant 4.
void reverse_words ();
////////////////////////////////////////////////////////////////////////

//Task C. 2008. Variant 4.
void sum_digits_on_diagonal_square_matrix ();
////////////////////////////////////////////////////////////////////////

//Task C. 2007. Variant 9.
void add_to_binary_digits ();
////////////////////////////////////////////////////////////////////////

//Task D. 2007. Variant 3
int MIN (int elem1, int elem2);
void find_the_biggest_white_square();
////////////////////////////////////////////////////////////////////////

//Task C. 2008. Variant 9.
void delete_duplicates();
////////////////////////////////////////////////////////////////////////

//Task C. 2007. Variant 5.
void alphabetic_sort (struct data2* student, const int START, const int END);
void rating_sort (struct data2* student, int* marks, const int START, const int END);
void sort_students();
////////////////////////////////////////////////////////////////////////

//Task C. 2008. Variant 7.
int digit_sum(int n);
void four_digit_numbers();
////////////////////////////////////////////////////////////////////////

//Task C. 2007. Variant 6.
void numbers_free_of_squares();
////////////////////////////////////////////////////////////////////////



int main() {
    //find_the_biggest_white_square();
    //delete_duplicates();
    //sort_students();

    //deleting_spaces ();
    //reverse_words ();
    //sum_digits_on_diagonal_square_matrix ();
    //add_to_binary_digits ();

    //numbers_free_of_squares();
	//four_digit_numbers();

    return 0;
}


/*!  Task C. 2008. Variant 1.

    \fn      void deleting_spaces ();
    \brief   This function deletes excess spaces between words from inputting data.
*/

void deleting_spaces () {

    const int MAX_SIZE_TEXT = 100000;
    char* text = (char*) calloc (MAX_SIZE_TEXT, sizeof (*text));

    ASSERT(text);

    int text_length = -1;

    //Read text
    do {

        text_length++;
        ASSERT (text_length < MAX_SIZE_TEXT);
        text[text_length] = getchar();
    }
    while (text[text_length] != '\n');


    int i = 0;

    //Determinant space and print other symbols
    for (i = 0; i <= text_length; i++) {

        ASSERT (i < MAX_SIZE_TEXT && i >= 0);

        //Test on space, print symbol if no space
        if (text [i] != ' ')
            putchar(text[i]);

        else {

        //===== If read symbol is space, then print one space
            if ((i != 0) && (text[i - 1] != ' ') && ( i + 1 != text_length ))
                putchar(text[i]);
        }
    }

    free (text);
    text = NULL;

}


/*! Task C. 2007. Variant 4.

    \fn     void reverse_words ();
    \brief  This function reverses all words in inputting text.

 */


void reverse_words () {

    const int MAX_SIZE_WORD = 1000;
    char* word = (char*) calloc (MAX_SIZE_WORD, sizeof (*word));

    ASSERT(word);

    while (1) {
        int current_length_word = -1;

        //Read word
        do {

            current_length_word++;

            ASSERT ((current_length_word < MAX_SIZE_WORD) && (current_length_word >= 0));

            scanf ( "%c", &word[current_length_word] );

        } while ( (( word[current_length_word] >= 'a') && (word[current_length_word] <= 'z' )) || \
                  (( word[current_length_word] >= 'A') && (word[current_length_word] <= 'Z' )) );

        int i = 0;

        //Output reversed word
        for ( i = current_length_word - 1; i >= 0; i-- ) {

            ASSERT ( i < MAX_SIZE_WORD && i >= 0 );

            putchar(word[i]);
        }

        //Test on '\n' symbol and print other symbol
        if (word[current_length_word] == '\n')
            break;

        else
            putchar(word[current_length_word]);

    }

    free (word);
    word = NULL;

}


/*!  Task C. 2008. Variant 4.

    \fn     void sum_digits_on_diagonal_square_matrix ();
    \brief  This function sums all digits on diagonal squaring matrix.

*/

void sum_digits_on_diagonal_square_matrix () {

    int N = 0;

    // Read size of matrix and create array with address on string.
    scanf ( "%d", &N );
    int** Line = ( int** ) calloc ( N, sizeof ( **Line ) );

    ASSERT (Line);

    int i = 0;

    // Read content of matrix and create array column for every string.
    for ( i = 0; i < N;  i++ ) {

        ASSERT ( i < N && i >= 0 );

        Line[i] = ( int* ) calloc ( N, sizeof ( *Line[i] ) );

        ASSERT (Line[i]);

        int j = 0;

        for ( j = 0; j < N; j++ ) {

            ASSERT ( j < N && j >= 0 );

            scanf ( "%d", Line [i] + j );
        }
    }

    int* Sum = (int*) calloc ((2 * N - 1), sizeof (*Sum));

    ASSERT (Sum);

    int counter_sum = 0;

    //Sum elements on diagonal in first half of matrix.
    for ( i = N - 1; i >= 0; i-- ) {

        int j = 0;

        for ( j = 0; j <= N - i - 1; j++ ) {

            ASSERT ((i + j < N) && (i + j >= 0));
            ASSERT ((counter_sum < 2 * N - 1) && (counter_sum >= 0));

            Sum[counter_sum] += *( Line [i + j] + j);
        }
        counter_sum++;
    }

    //Sum elements on diagonal in second half of matrix
    for ( i = 1; i <= N - 1; i++ ) {

        int j = 0;

        for ( j = 0; j <= N - i - 1; j++ ) {

            ASSERT ( i + j < N && i + j >= 0 );
            ASSERT ( counter_sum < 2 * N - 1 && counter_sum >= 0 );

            Sum[counter_sum] += *( Line [j] + i + j);
        }

        counter_sum++;
    }

    //Output Sum
    for ( i = 0; i < counter_sum;  i++ ) {

        ASSERT ( i < 2 * N - 1 && i >= 0 );
        printf ( "%d ", Sum[i] );
    }

    //free all memory
    for ( i = 0; i < N;  i++ ) {

        ASSERT ( i < N && i >= 0 );
        free ( Line[i] );
        Line [i] = 0;
    }

    free (Line);
    Line = 0;

}

/*!  Task C. 2007. Variant 9.

    \fn void add_to_binary_digits ();
    \brief This function add two 1000 bit binary digits.

*/

/*! \fn swap_mass_elements (char* first_number, int i, char* second_number, int j);
    \brief Swaps two elements of numbers.

*/

void swap_mass_elements (char* first_number, int i, char* second_number, int j) {

    first_number[i] = second_number[i] + first_number[i];
    second_number[i] = first_number[i] - second_number[i];
    first_number[i] = first_number[i] - second_number[i];

}

/*! \fn sum_bits (char* first_number, char* second_number, int difference_shift_bits, int num_bit_1);
    \brief This function sums two binary numbers.

*/

void sum_bits (char* first_number, char* second_number, int difference_shift_bits, int num_bit_1) {

    const int zero_code_ASCII = 48;
    int memory_bit = 0;

    for (int i = num_bit_1 - 1; i >= 0; i-- ) {

        if ( i - difference_shift_bits > 0 )
            first_number[i] += second_number[i - difference_shift_bits] - zero_code_ASCII;

        if ( memory_bit == 1 ) {
            first_number[i] += memory_bit ;
            memory_bit = 0;
        }

        if  ( first_number[i] - zero_code_ASCII >= 2 ) {

            memory_bit = 1;
            if  ( first_number[i] - zero_code_ASCII == 2 )
                first_number[i] = zero_code_ASCII;

            else
                first_number[i] = zero_code_ASCII + 1;

        }
    }
}

/*! \fn sum_bits (char* first_number, char* second_number, int difference_shift_bits, int num_bit_1);
    \brief This function sums two binary digits.

*/


void add_to_binary_digits () {

    const int MAX_BITS = 1000;
    int difference_shift_bits = 0;

    //Read first number
    char* first_number  = ( char* ) calloc ( MAX_BITS, sizeof ( *first_number ) );
    int num_bit_1 = 0;

    do {
        num_bit_1++;
        ASSERT((num_bit_1 >= 0) && (num_bit_1 < MAX_BITS));
        scanf ( "%c", &first_number[num_bit_1] );
    }

    while (first_number[num_bit_1] != '\n');

    //Read second number
    char* second_number  = ( char* ) calloc ( MAX_BITS, sizeof ( *second_number ) );
    int number_bit_2 = 0;

    do {
        number_bit_2++;
        ASSERT((num_bit_2 >= 0) && (num_bit_2 < MAX_BITS));
        scanf ( "%c", &second_number[number_bit_2] );
    }

    while ( second_number[number_bit_2] != '\n' );

    int zero_code_ASCII = 48;
    int i = 0;

    first_number[0] = zero_code_ASCII;
    second_number[0] = zero_code_ASCII;

    //Define the greatest number
    if ( num_bit_1 >= number_bit_2 )
        difference_shift_bits = num_bit_1 - number_bit_2;

    else {

        difference_shift_bits = number_bit_2 - num_bit_1;
        //Swap two numbers
        for ( i = 0; i < number_bit_2; i++ ) {
            ASSERT((i >= 0) && (i < number_bit_2));
            swap_mass_elements(first_number, i, second_number, i);
        }

        //Swap lengths of two digits
        num_bit_1 = number_bit_2 + num_bit_1;
        number_bit_2 = num_bit_1 - number_bit_2;
        num_bit_1 = num_bit_1 - number_bit_2;
    }

    //Sum two bits
    sum_bits(first_number, second_number, difference_shift_bits, num_bit_1);

    //Output result
    int is_highest_bit = 0;
    //Ignore insignificant zeros
    while (first_number[is_highest_bit] == '0')
        is_highest_bit++;

    for (i = is_highest_bit; i < num_bit_1; i++) {
        ASSERT((i >= 0) && (i < num_bit_1));
        putchar(first_number[i]);
    }

    free (first_number);
    first_number = 0;

    free (second_number);
    second_number = 0;

}


/*!  Task D. 2007. Variant 3.

    \fn     void find_the_biggest_white_square();
    \brief  This function finds the size and coordinates of \n
            the biggest white square on a map.

*/

/*! \fn int MIN (int elem1, int elem2, int elem3);
    \brief Returns the smallest of three numbers.
*/
int MIN (int elem1, int elem2) {

    if (elem1 <= elem2)
        return elem1;

    return elem2;
}

/*! \struct data
    \brief Contains coordinates and size of  biggest square.

    \param SIZE
    \param X
    \param Y
*/
struct data {
    int SIZE;
    int X;
    int Y;
};


void find_the_biggest_white_square() {

    int N = 0;

    struct data ANSWER;
    ANSWER.SIZE = 0;
    ANSWER.X = 0;
    ANSWER.Y = 0;

    scanf("%d\n", &N);

    char** MAP = (char**) calloc (N, sizeof (char*));

    ASSERT(MAP);

    for (int i = 0; i < N; i++) {

        ASSERT((i < N) && (i >= 0));

        MAP[i] = (char*) calloc (N, sizeof(char*));

        ASSERT(MAP[i]);
    }

    int** MAP_OF_SIZES = (int**) calloc (N, sizeof (int*));

    ASSERT(MAP_OF_SIZES);

    for (int i = 0; i < N; i++) {

        ASSERT((i < N) && (i >= 0));

        MAP_OF_SIZES[i] = (int*) calloc (N, sizeof(int*));

        ASSERT( MAP_OF_SIZES[i]);
    }

    for (int y = 0; y < N; y++) {

        for (int x = 0; x < N; x++) {

           ASSERT((x < N) && (y < N) && (y >= 0) && (x >= 0));
           MAP[x][y] = getchar();
        }

        getchar();
    }

    for (int y = 0; y < N; y++) {

        for (int x = 0; x < N; x++) {

            ASSERT((x < N) && (y < N) && (y >= 0) && (x >= 0));

            if (MAP[x][y] == '#')
                MAP_OF_SIZES[x][y] = 0;

            if (((x == 0) || (y == 0)) && (MAP[x][y] == '.'))
                MAP_OF_SIZES[x][y] = 1;

            if ((x != 0) && (y != 0) && (MAP[x][y] == '.'))
                MAP_OF_SIZES[x][y] = 1 +
                    MIN (MAP_OF_SIZES[x - 1][y], MIN(MAP_OF_SIZES[x][y - 1], MAP_OF_SIZES[x - 1][y - 1]));

            if ((MAP_OF_SIZES[x][y] > ANSWER.SIZE) || \
               ((MAP_OF_SIZES[x][y] == ANSWER.SIZE) && (ANSWER.X > x))) {

                ANSWER.X = x;
                ANSWER.Y = y;
                ANSWER.SIZE = MAP_OF_SIZES[x][y];
            }
        }
    }
    // Clear memory
    for (int i = 0; i < N; i++) {

        ASSERT((i < N) &&  (i >= 0));
        free(MAP[i]);
    }

    free(MAP);
    MAP = NULL;

    for (int i = 0; i < N; i++) {

        ASSERT((i < N) && (i >= 0));
        free(MAP_OF_SIZES[i]);
    }

    free(MAP_OF_SIZES);
    MAP_OF_SIZES = 0;

    //Output size and coordinates.
    if (ANSWER.SIZE == 0)
        printf("%s", "There is no such square");

    if (ANSWER.SIZE != 0) {
        printf("%d\n", ANSWER.SIZE);
        printf("%d %d", ANSWER.X, ANSWER.Y);
    }

}


/*!  Task C. 2008. Variant 9.

    \fn     void delete_dublicates ();
    \brief  This function removes repeats of numbers from a sequence.
*/

void delete_duplicates () {

    const int MAX_NUM = 1000;

    int N = 0;
    scanf("%d\n", &N);

    // Allocation of memory
    // Stream - sequence
    int* stream = (int*) calloc (N, sizeof(int*));

    ASSERT(stream);

    // amount_of_nums it's an array contains information about
    // how many times each member of sequence was printed.
    int* amount_of_nums = (int*) calloc (MAX_NUM, sizeof(int*));

    ASSERT(amount_of_nums);

    //Entering of sequence
    for (int i = 0; i < N; i++)
        scanf("%d", &stream[i]);

    for (int i = 0; i < N; i++) {

        ASSERT((i >= 0) && (i < N));
        if (amount_of_nums[stream[i]] == 0) {

            putchar(stream[i]);
            amount_of_nums[stream[i]]++;
        }
    }

    free(stream);
    stream = 0;

    free(amount_of_nums);
    amount_of_nums = 0;

}


/*!  Task C. 2007. Variant 5.

    \fn     void sort_students();
    \brief  This function sort students according to their mark or names.
*/

struct data2 {
    char* name;
    int mark;
};

/*! \fn     void alphabetic_sort (data2* student, const int START, const int END);
    \brief  Sorts the list in alphabetical order.
*/

void alphabetic_sort (struct data2* student, const int START, const int END) {

    for (int i = START; i < END; i++)

        for (int j = i + 1; j <= END; j++) {

            if (strcmp(student[i].name, student[j].name) > 0) {

                char* p = student[i].name;
                student[i].name = student[j].name;
                student[j].name = p;

                int d = student[i].mark;
                student[i].mark = student[j].mark;
                student[j].mark = d;
            }
        }
}

/*! \fn     void rating_sort (data2* student, const int START, const int END);
    \brief  Sorts the list in a descending order according to the marks.
*/

void rating_sort (struct data2* student, const int START, const int END) {

    for (int i = START; i < END; i++) {

        ASSERT((i >= 0) && (i < N));
        for (int j = i + 1; j <= END; j++) {

            ASSERT((i >= 0) && (i < N));
            if (student[i].mark < student[j].mark) {

                char* p = student[i].name;
                student[i].name = student[j].name;
                student[j].name = p;

                int d = student[i].mark;
                student[i].mark = student[j].mark;
                student[j].mark = d;
            }
        }
    }
}

void sort_students() {

    const int MAX_WORD_LENGTH = 29;

    int N = 0;

    scanf("%d\n", &N);

    struct data2* student = (data2*) calloc (N, sizeof(data2));
    ASSERT(student);

    for (int i = 0; i < N; i++) {

        student[i].name = (char*) calloc (MAX_WORD_LENGTH, sizeof(char*));
        ASSERT(student[i].name);
    }

    for (int i = 0; i < N; i++) {

        ASSERT((i >= 0) && (i < N));
        for (int j = 0; scanf("%d", &student[i].mark) == 0; j++) {
            ASSERT((j >= 0) && (j < N));
            student[i].name[j] = getchar();
        }

    }

    alphabetic_sort(student, 0, N-1);
    printf("\n");//Divides input and output

    for (int i = 0; i < N; i++) {

        ASSERT((i >= 0) && (i < N));
        for (int j = 0; student[i].name[j] != 0; j++) {

            ASSERT((i >= 0) && (i < N));
            printf("%c", student[i].name[j]);
        }

        ASSERT((i >= 0) && (i < N));
        printf(" %d", student[i].mark);
        printf("\n");
    }

    printf("\n");
    rating_sort(student, 0, N-1);

    for (int i = 0; i < N; i++) {

        ASSERT((i >= 0) && (i < N));
        for (int j = 0; student[i].name[j] != 0; j++) {
            ASSERT((j >= 0) && (j < N));
            printf("%c", student[i].name[j]);
        }

        ASSERT((i >= 0) && (i < N));
        printf(" %d", student[i].mark);
        printf("\n");
    }

    for (int i = 0; i < N; i++) {
        ASSERT((i >= 0) && (i < N));
        free(student[i].name);
        student[i].name = 0;
    }

    free(student);
    student = 0;
}


/*!  Task C. 2008. Variant 7.
    \fn     void four_digit_numbers();
    \brief  Prints four-digit numbers with sum of digits equal to N
*/

/*! \fn     void inc_number(int* four_dig_number, int number_digit);
    \brief  Increases number
*/

void inc_number(int* four_dig_number, int number_digit) {

    number_digit -= 1;

    ASSERT ( number_digit >= 0 && number_digit < 4 );

    four_dig_number[number_digit]++;

    if ( four_dig_number[number_digit] == 10 ) {

        four_dig_number[number_digit] = 0;

        if ( number_digit != 0 )
            inc_number (four_dig_number, number_digit);
    }
}

/*! \fn     int digit_sum(int* four_dig_number);
    \brief  Calculate sum of digits
*/

int digit_sum(int* four_dig_number) {

	int sum = four_dig_number[0] + four_dig_number[1] + four_dig_number[2] + four_dig_number[3] ;

	return sum;
}


void four_digit_numbers() {
    const int NUM_OF_DIGITS = 4;
	const int first_number = 1000;
	const int last_number = 9999;
	int four_dig_number[NUM_OF_DIGITS] = {1, 0, 0, 0};

	int N = 0, c_digit = 0, counter = 0;

	scanf("%d", &N);

	for (c_digit = first_number; c_digit <= last_number; c_digit++) {

		  if (digit_sum(four_dig_number) == N) {

			  counter++;
			  printf("%d ", c_digit);
		  }

		  inc_number(four_dig_number, NUM_OF_DIGITS);
	  }
	printf("%d\n", counter);

}

/*!  Task C. 2007. Variant 6.
    \fn     void numbers_free_of_squares();
    \brief  Finds numbers which aren't divisible by full squares.
*/

void numbers_free_of_squares() {

	const int MAX_SIZE = 200;
	const int MAX_DIVIDER = 65536;// 2^16

	long int* a = (long int*) calloc (MAX_SIZE, sizeof(long int*));

	int n = 0; // number of values
	int i = 0;
	int j = 0;

	scanf("%d", &n);

	for (i = 0; i < n; ++i)
		scanf("%ld", a + i);

	for (i = 0; i < n; ++i) {

		for (j = 2; j < MAX_DIVIDER; ++j) {

			if (a[i] % (j * j) == 0)
				break;

			if (j == 65535)
				printf("%ld ", a[i]);

		}
	}

	free(a);
}
