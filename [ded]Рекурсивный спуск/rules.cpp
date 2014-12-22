#include "rules.h"

//======================================================
double GetG0 (char** s) {

    double val = 0;

    printf("GetGo_IN\n");

    val = GetE(s);

    printf("GetGo_OUT\n");

    return val;
}
//======================================================
double GetE (char** s) {

    printf("GetE_IN\n");

    double val = GetS(s);

    while (**s == '+') {

        (*s)++;
        val = val + GetS(s);

    };

    printf("%lg || GetE_OUT\n", val);

    return val;
}
//======================================================
double GetS (char** s) {

    printf("GetS_IN\n");

    double val = GetT(s);

    while (**s == '-') {

        (*s)++;
        val = val - GetT(s);

    };

    printf("%lg || GetS_OUT\n", val);

    return val;
}
//======================================================
double GetT (char** s) {

    printf("GetT_IN\n");

    double val = GetD(s);

    while (**s == '*') {

        (*s)++;
        val = val * GetD(s);

    }

    printf("%lg || GetT_OUT\n", val);

    return val;
}
//======================================================
double GetD (char** s) {

    printf("GetD_IN\n");

    double val = GetZ(s);

    while (**s == '/') {

        (*s)++;
        val = val / GetZ(s);

    }

    printf("%lg || GetD_OUT\n", val);

    return val;
}
//======================================================
double GetZ (char** s) {

    printf("GetZ_IN\n");

    double val = GetP(s);

    while (**s == '^') {

        (*s)++;
        val = pow(val, GetP(s));

    }

    printf("%lg || GetZ_OUT\n", val);

    return val;
}
//======================================================
double GetP (char** s) {

    double val = 0;

    printf("GetP_IN\n");

    if (**s != '(') {

        val = GetL(s);

        printf("%lg || GetP_OUT\n", val);

        return val;

    }
    else {

        (*s)++;

        val = GetE(s);
    }

    (*s)++;
    printf("%lg || GetP_OUT\n", val);

    return val;
}
//======================================================
double GetL (char** s) {

    double integer = GetN(s);
    double rest = 0;
    double val = integer;

    if (**s == '.') {

        (*s)++;
        rest = GetN(s);

        while (rest > 1)
            rest = rest / 10;

        val = val + rest;
    }

    return val;
}
//======================================================
double GetN (char** s) {

    printf("GetN_IN\n");

    double val = 0;

    if ((**s) < '0' || (**s) > '9') {
            printf("%lg || GetN_OUT\n", val);
            return val;
    }

    do {

        val = val * 10 - 48 + (**s);
        (*s)++;;

    } while (**s >='0' && **s <='9');

    printf("%lg || GetN_OUT\n", val);

    return val;
}
//======================================================
