#include "rules.h"

int main() {

    int error = OK;

    char* s = (char*) calloc (1000, sizeof(char));

    scanf("%s", s);

    printf("%lg", GetG0(&s));

    free(s);

    return 0;
}
