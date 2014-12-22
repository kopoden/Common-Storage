#ifndef _RULES_H_INCL_
#define _RULES_H_INCL_

#include <math.h>
#include "tree.h"

extern int error;

enum calculation_errors {

    UNEXPECTED_SYMBOL = 5,
    UNKNOWN_SYMBOL = 6,
    INCORRECT_BRACKET_SEQUENCE = 7,
    NUMBER_EXPECTED = 8

};

//=============================================================
double GetG0 (char** s);   // the beginning and the end
double GetE (char** s);    // sum
double GetS (char** s);    // subtraction
double GetT (char** s);    // multiply
double GetD (char** s);    // divide
double GetZ (char** s);    // up to degree
double GetP (char** s);    // brackets
double GetL (char** s);    // double point
double GetN (char** s);    // read number
//=============================================================

#endif // _RULES_H_INCL_
