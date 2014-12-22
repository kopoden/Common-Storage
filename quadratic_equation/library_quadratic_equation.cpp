
/*! @file "library_quadratic_equation.cpp"
    @brief Library file.

    IT CONTAINS CODE OF ALL FUNCTIONS, USING IN MAIN PROGRAM

    FUNCTIONS IN LIBRARY:

    clear_console();

    restart();

    input_data();

    solve_equation();

*/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "library_quadratic_equation.h"

////////////////////////////////////////////////////////////

int input_data (double coef[], const int coeffNum ) {

    const int DEGREE = 2;

    char coefficient = 'A' - coeffNum + DEGREE;

    printf("%c = ", coefficient);
    fflush(stdin);

    if (scanf("%lg", &coef[coeffNum]) == 0 || getchar() != '\n') {


        printf("%s\n", "Please, enter a rational number.");

        return INCORRECT;
    }

    return CORRECT;
}

////////////////////////////////////////////////////////////

int solve_equation (const double coef[], double ans[]) {

    int num_of_x = 0; //number of answers
    double D = 0, sqrtD = 0; // discriminant and its square root

//  Linear equation
    if (coef[2] == 0) {

//       There aren't any solutions
        if ((coef[1] == 0) && (coef[0] != 0))
            num_of_x = NO_SOLUTIONS;

//       There is the only solution
        if (coef[1] != 0) {

            num_of_x = ONE_ROOT;

            ans[0] = (-coef[0]) / coef[1];

            if (coef[0] == 0) // '-0' --->'0'
                ans[0] = 0;
        }

//       All numbers.
        if ((coef[1] == 0) && (coef[0] == 0)) {
            num_of_x = INFINITE;
        }
    }
//   Quadratic equation
    if (coef[2] != 0) {
        D = (coef[1] * coef[1]) - (4 * coef[0] * coef[2]);

        if (D < 0) num_of_x = NO_SOLUTIONS;

        const double NEIGHBORHOOD_OF_ZERO = 0.000001;

        if ((D < NEIGHBORHOOD_OF_ZERO) && (D > -NEIGHBORHOOD_OF_ZERO)) {
            num_of_x = ONE_ROOT;

            ans[0] = (-coef[1]) / (2 * coef[2]);
        }

        if (D > 0) {
            num_of_x = TWO_ROOTS;
            sqrtD = sqrt(D);

            ans[0] = (-coef[1] + sqrtD) / (2 * coef[2]);
            ans[1] = (-coef[1] - sqrtD) / (2 * coef[2]);
        }

    }

    return num_of_x;
}

////////////////////////////////////////////////////////////

void output_res (const int num_of_solutions, const double ans[]) {

    switch (num_of_solutions) {

        case INFINITE:

            printf("%s", "The equation has an infinite number of solutions\n");
            break;

        case NO_SOLUTIONS:

            printf("The equation has no solutions\n");
            break;

        case ONE_ROOT:

            printf("x = %lg\n", ans[0]);
            break;

        case TWO_ROOTS:

            printf("x1 = %lg\n", ans[0]);
            printf("x2 = %lg\n", ans[1]);
            break;

        default:
            break;
    }
}

////////////////////////////////////////////////////////////

void clear_console() {

    for (int i = 0; i < 20; i++)
      printf("\n\n\n\n\n");
}

////////////////////////////////////////////////////////////
int restart() {

    printf("%s", "Do you want to solve one more equation ");
    printf("%s", "and clear the screen?\n");
    printf("%s", "0 - No\n");
    printf("%s", "1 - Yes\n");
    printf("%s", "2 - Yes, clear the screen, please.\n");

    int input_num = INCORRECT_FORMAT;
    fflush(stdin);

    if ((scanf("%d", &input_num) == 0) || (getchar() != '\n')) {
        printf("%s", "Please, enter 0, 1 or 2.\n");
        return INCORRECT_FORMAT;
    }

    return input_num;
}
