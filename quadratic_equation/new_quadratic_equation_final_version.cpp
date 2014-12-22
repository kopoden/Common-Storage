/*! @mainpage

This program solves [linear](https://en.wikipedia.org/wiki/Linear_equation) and [quadratic equations](https://en.wikipedia.org/wiki/Quadratic_equation).

<H1>Short Guide</H1>

<hr>

<H2>The First Step</H2>

<H3>Warning!</H3>

<b><i> If you enter a letter, program will ask to repeat the input of the last coefficient.</i></b>

Firstly, you will be asked to enter the coefficients of the equation.

<b>Input format </b>:

A = ValueA <br>
B = ValueB <br>
C = ValueC <br>

A, B, C are [the rational numbers](https://en.wikipedia.org/wiki/Rational_number).

<hr>

<H3>The Result</H3>

At the result the program can show you three types of messages:

1. The equation has no solutions.
2. The equation has an infinite number of solutions.
3. You will see the only solution or two roots.

<hr>

<H3>Reusing</H3>
Finally, program will ask you about one more equation.

- If you want to close program write: 0
- If you want to solve one more equation write: 1
- If you want to continue and to clear the screen, write: 2

<hr>

<H3>Contacts</H3>

If you have some offers or complaints and want to share with me
you can use these [contacts](https://github.com/kopoden/iLab-local/wiki/Contacts).

<hr>

<H4>Thank you for reading this short description. Enjoy using.</H4>

*/


/*! @file "new_quadratic_equation.cpp"
    @brief File of main program.
*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "library_quadratic_equation.h"


//////////////////////////////////////////////////////////////
#ifdef DEBUG
#define ASSERT( cond ) if ( ! ( cond ) ) { \
    printf ( "FAIL %s in %s, %s ( %d )", \
    #cond, __PRETTY_FUNCTION__, \
    __FILE__, __LINE__ ); \
    abort(); \
}
#else
#define ASSERT( cond ) ;
#endif

///////////////////MAIN FUNCTION///////////////////////////

int main() {

    // It's vital to set array's sizes
    int const MAX_DEGREE = 2;

    // Defines if it's neccessary to finish or continue program, to input coefficients.
    int restart_or_finish = CONTINUE;

    double coef[MAX_DEGREE + 1] = {}, // Array of coefficients
           ans[MAX_DEGREE] = {};      // Array of roots

    while (restart_or_finish != FINISH) {

        if (restart_or_finish == CLEAR_AND_CONTINUE)
            clear_console();

        printf("%s\n", "Please, enter coefficients.");

        int num_of_entered = 0; // amount of correctly entered values

        while (num_of_entered < MAX_DEGREE + 1) {

            ASSERT(((MAX_DEGREE - num_of_entered) >= 0) && ((MAX_DEGREE - num_of_entered) <= MAX_DEGREE)) ;

            int check_input = input_data(coef, MAX_DEGREE - num_of_entered);
            if (check_input == CORRECT)
                num_of_entered++;
        }

        ASSERT (MAX_DEGREE >= 2);

        int num_of_solutions = solve_equation (coef, ans);
        output_res(num_of_solutions, ans);


        restart_or_finish = restart();

        while (restart_or_finish == INCORRECT_FORMAT)
            restart_or_finish = restart();

    }

    return 0;
}
