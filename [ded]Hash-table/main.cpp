#include "hash_func.h"

//==============================================
extern FILE* logs; //Global
//==============================================

int main () {

//===============OPEN LOG FILE==========================
    logs = fopen("logs.txt", "w");

    if (logs == NULL) {

        printf("CAN'T CREATE LOG FILE\n");

        return 0;

    }
//=====================CHOOSE MODE==========================
    setlocale(LC_CTYPE, "russian");

    int mode = 0;

    printf("Choose mode:\n1 -- return 1\n2 -- first ASCII\n3 -- length\n4 -- ASCII sum\n5 -- shifts\n");
    scanf("%d", &mode);

    if (mode <= 0 || mode >= 6) {

        printf("INCORRECT MODE\n");

        fprintf(logs, "INCORRECT MODE\n");

        return 0;

    }
//=============INITIALIZATION OF HASH TABLE===================
    FILE* input = fopen("onegin.txt", "r");
    FILE* dump = fopen("dump_list.txt", "w");

    if (SIZE_OF_HASH_TABLE > MAX_SIZE) {

        fprintf(logs, "SIZE OF HASH TABLE IS BIGGER THAN MAXIMAL AVAILABLE.\n");

        return ERR_MEM;

    }

    List hash_table[SIZE_OF_HASH_TABLE] = {};

    int check = HT_ctor(hash_table);

    if (check != OK) {

        fprintf(logs, "CHECK ERROR CODE\n");

        return check;
    }

//==================PREPATATION OF THE TEXT FILE===================
    char* buffer = NULL;

    long int leng_of_file = 0;

    check = make_buffer(input, &buffer, &leng_of_file);

    if (check != OK) {

        return check;
    }

    if (buffer == NULL) {

        fprintf(logs, "MEMORY ALLOCATION ERROR\n");

        return ERR_MEM;
    }

    char** words = NULL;

    int num_of_words = 0;

    check = make_words_array(&words, buffer, leng_of_file, &num_of_words);

    if (check != OK) {

        fprintf(logs, "CHECK ERROR CODE\n");

        return check;
    }

    if (words == NULL) {

        fprintf(logs, "MEMORY ALLOCATION ERROR\n");

        return ERR_MEM;
    }


    FILE* output = NULL;
//====================FILLING OF HASH TABLE=====================
    switch (mode) {

        case 1:

            output = fopen("f1.csv", "w");

            HT_filling(words, num_of_words, hash_table, f1);

            break;

        case 2:

            output = fopen("fASCII.csv", "w");

            HT_filling(words, num_of_words, hash_table, fACII);

            break;

        case 3:

            output = fopen("flength.csv", "w");

            HT_filling(words, num_of_words, hash_table, flenght);

            break;

        case 4:

            output = fopen("fsum.csv", "w");

            HT_filling(words, num_of_words, hash_table, fsum);

            break;

        case 5:

            output = fopen("fshifts.csv", "w");

            HT_filling(words, num_of_words, hash_table, fdifficult);

            break;

        default:

            printf("INCORRECT MODE\n");

            fprintf(logs, "INCORRECT MODE\n");

            return 0;
    }
//===========================================================
    HT_dumper(dump, hash_table);

    if (output == NULL) {

        fprintf(logs, "CAN'T CREATE OUTPUT FILE\n");

        return NULL_POINTER;
    }

    count_and_output(output, hash_table);

    HT_dtor(hash_table);

    fclose(input);
    fclose(output);
    fclose(logs);
    fclose(dump);

    free(buffer);
    buffer = NULL;

    free(words);
    words = NULL;

    return 0;
}
