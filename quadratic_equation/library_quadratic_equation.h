/*! @file "library_quadratic_equation.h"
    @brief Library Header.

    IT CONTAINS HEADERS OF AL FUNCTIONS, USING IN MAIN PROGRAM

    FUNCTIONS IN LIBRARY:

    clear_console();

    restart();

    input_data();

    solve_equation();

*/

/*! \enum results
    Contains all possible values returned by function solve_equation.
*/


enum results {
    NO_SOLUTIONS, ///< == solve_equation(), if there aren't any solutions.
    ONE_ROOT, ///< == solve_equation(), if there is the only root.
    TWO_ROOTS, ///< == solve_equation(), if there are two answers.
    INFINITE ///< == solve_equation(), if the number of answers is infinite.
    };

/*! \enum choice
    Contains all possible values returned by function restart.
*/
enum choice {
    FINISH, ///< == restart(), if user wants to close the program
    CONTINUE, ///< == restart(), if user wants to continue
    CLEAR_AND_CONTINUE, ///< == restart(), if user wants to clear the screen and continue
    INCORRECT_FORMAT ///< == restart(), if user used incorrect format.
    };

/*! \enum format
    Contains all possible values returned by function input_data.
*/

enum format {
    CORRECT, ///<  reports about correct input format.
    INCORRECT ///<  reports about incorrect input format.
    };

/*! @fn int input_data (double coef[], const int coeffNum)
    @brief Inputs coefficients and checks data

    @param coef    Array of coefficients
    @param coeffNum  Amount of coefficients

    RETURNS:

    <b> CORRECT </b> if data format is correct

    <b> INCORRECT </b>  if data format is wrong
*/

int input_data (double coef[], const int coeffNum );

/*! @fn int solve_equation (const double coef[], double ans[])
    @brief Find roots and the number of them

    @param coef  Array Of Coefficients
    @param ans    Array O fAnswers

   Function, solving equation of these types:
   <ol>
    <li> Ax^2 + Bx + C = 0
    <li> Bx + C = 0
   </ol>

   RETURNS THE NUMBER OF SOLUTIONS:

   <ol>
    <li> <b> NO_SOLUTIONS </b>
    <li> <b> ONE_ROOT     </b>
    <li> <b> TWO_ROOTS    </b>
    <li> <b> INFINITE     </b>
   </ol>
*/

int solve_equation (const double coef[], double ans[]);

/*! @fn void output_res(const int numberOfSolutions, const double ans[])
    @brief Shows result on the screen

    @param numberOfSolutions    Number of roots counted with function solve_equation.
    @param ans                ArrayOfAnswers
*/

void output_res (const int num_of_solutions, const double ans[]);

/*! @fn void clear_console()
    @brief Function, clearing the console window
*/

void clear_console();

/*! @fn int restart()
    @brief Function, asking user to restart or close program

    RETURNS:
    <ol>
     <li> <b> FINISH </b> (if user has entered '0')
     <li> <b> CONTINUE </b> (if user has entered '1')
     <li> <b> CLEAR_AND_CONTINUE </b> (if user has entered '2')
    </ol>

*/

int restart();


