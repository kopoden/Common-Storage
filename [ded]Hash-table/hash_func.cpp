#include "hash_func.h"

//===============================================
int f1 (char* String) {

    return 1;
}
//===============================================
int fACII (char* String) {

    return (unsigned char) String[0];
}
//===============================================
int flenght (char* String) {

    return strlen(String);
}
//===============================================
int fsum (char* String) {

    int sum = 0;
    int i = 0;

    while (String[i] != 0) {
        sum = sum + (int) (unsigned char) String[i];
        i++;
    }

    return sum;
}
//===============================================
int fdifficult (char* String) {

    int leng = strlen(String);

    if (leng == 0)
        return 0;

    if (leng == 1)
        return (int) ((unsigned char) String[0]);
    int h = (int) ((unsigned char) String[0]);

    for (int i = 1; i < leng; i++)
        h = (h << 1) ^ (unsigned char) String[i];

    return h;
}
//===============================================
