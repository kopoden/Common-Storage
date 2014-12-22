#include "hash_table.h"

//=================================================================
#define make_log( err_code )                                                                  \
do {                                                                                            \
                                                                                                \
    switch (err_code) {                                                                         \
                                                                                                \
        case OK:                                                                                \
                                                                                                \
            fprintf(logs, "%s == OK\n", __PRETTY_FUNCTION__);                             \
            break;                                                                              \
                                                                                                \
        case ERR_MEM:                                                                           \
                                                                                                \
            fprintf(logs, "%s == MEMORY ALLOCATION ERROR OCCURED\n", __PRETTY_FUNCTION__);\
            break;                                                                              \
                                                                                                \
        case ERR_ACCESS:                                                                        \
                                                                                                \
            fprintf(logs, "%s == CAN'T DELETE THE FIRST ELEMENT\n", __PRETTY_FUNCTION__); \
            break;                                                                              \
                                                                                                \
        case SPOILT:                                                                            \
                                                                                                \
            fprintf(logs, "%s == LIST HAS BEEN SPOILT. INFORMATION IS NOT AVAILABLE.\n", __PRETTY_FUNCTION__);\
            break;                                                                                      \
                                                                                                        \
        case LAST_REACHED:                                                                              \
                                                                                                        \
            fprintf(logs, "%s == ATTEMPT TO STEP OVER THE LAST ELEMENT\n", __PRETTY_FUNCTION__);  \
            break;                                                                                      \
                                                                                                        \
        case FIRST_REACHED:                                                                             \
                                                                                                        \
            fprintf(logs, "%s == ATTEMPT TO STEP OVER THE FIRST ELEMENT \n", __PRETTY_FUNCTION__);\
            break;                                                                                      \
                                                                                                        \
        case LEAK:                                                                                      \
                                                                                                        \
            fprintf(logs, "%s == THERE IS A DATA LEAK\n", __PRETTY_FUNCTION__);                         \
            break;                                                                                      \
                                                                                                        \
        case HASH_FUNCTION_ERROR:                                                                       \
                                                                                                        \
            fprintf(logs, "%s == INCORRECT HASH. CHECK HASH-FUNCTION.\n", __PRETTY_FUNCTION__);         \
            break;                                                                                      \
                                                                                                        \
        case NULL_POINTER:                                                                              \
                                                                                                        \
            fprintf(logs, "%s == INCORRECT LIST, HASH TABLE OR FILE POINTER.\n", __PRETTY_FUNCTION__);                           \
            break;                                                                                      \
                                                                                                        \
        default:                                                                                        \
                                                                                                        \
            fprintf(logs, "%s == UNKNOWN ERROR TYPE\n", __PRETTY_FUNCTION__);                           \
            break;                                                                                      \
                                                                                                        \
    }                                                                                                   \
} while (0);                                                                                            \
//=================================================================
FILE* logs = NULL; //Global
//=================================================================

int HT_ctor (List* HT) {

    if (HT == NULL) {

        make_log(NULL_POINTER);

        return NULL_POINTER;
    }

    for (int i = 0; i < SIZE_OF_HASH_TABLE; i++)

        if (list_ctor(&HT[i]) != OK) {

            make_log(ERR_MEM);
            return ERR_MEM;

        }

    make_log(OK);

    return OK;
}
//=================================================================
int make_buffer (FILE* input, char** buffer, long int* leng) {

    *leng = filelength(fileno(input));

    *buffer = (char*) calloc (*leng + 1, sizeof(char));

    if (*buffer == NULL) {

        make_log(ERR_MEM);

        return ERR_MEM;

    }

    if (input == NULL) {

        make_log(NULL_POINTER);

        fprintf(logs, "CAN'T OPEN INPUT FILE");

        return NULL_POINTER;

    }

    fread(*buffer, sizeof(char), *leng, input);

    make_log(OK);

    return OK;
}
//=================================================================
int make_words_array (char*** words, char* buffer, long int length_of_file, int* num_of_words) {

    if (buffer == NULL) {

        make_log(NULL_POINTER);

        return NULL_POINTER;
    }

    //count words
    *num_of_words = 0;

    int i = 0;

    while (i < length_of_file) {
                            //a-ÿ, a-z                                      A-ß, A-Z
        while (!((buffer[i] >= 'à' && buffer[i] <= 'ÿ') || (buffer[i] >= 'À' && buffer[i] <= 'ß') || \
                 (buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z')) && \
                 (i < length_of_file))
            i++;

        if (i >= length_of_file)
            break;

        (*num_of_words)++;
                            //a-ÿ, a-z                                      A-ß, A-Z
        while (((buffer[i] >= 'à' && buffer[i] <= 'ÿ') || (buffer[i] >= 'À' && buffer[i] <= 'ß') || \
                (buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z')) && \
                (i < length_of_file))
            i++;
    }
    //Divide text into words
    *words = (char**) calloc (*num_of_words, sizeof(char*));

    if (*words == NULL && num_of_words != 0) {

        make_log(ERR_MEM);
        return ERR_MEM;

    }

    i = 0;
    int word_num = 0;

    while (i < length_of_file) {
                            //a-ÿ, a-z                                      A-ß, A-Z
        while (!((buffer[i] >= 'à' && buffer[i] <= 'ÿ') || (buffer[i] >= 'À' && buffer[i] <= 'ß') || \
                 (buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z')) && \
                 (i < length_of_file))
            i++;

        if (i >= length_of_file)
            break;

        (*words)[word_num] = &buffer[i];

        word_num++;
                            //a-ÿ, a-z                                      A-ß, A-Z
        while (((buffer[i] >= 'à' && buffer[i] <= 'ÿ') || (buffer[i] >= 'À' && buffer[i] <= 'ß') || \
                (buffer[i] >= 'a' && buffer[i] <= 'z') || (buffer[i] >= 'A' && buffer[i] <= 'Z')) && \
                (i < length_of_file))
            i++;
        buffer[i] = 0;

    }

    make_log(OK);

    return OK;
}
//=================================================================
int HT_filling (char** words, int num_of_words, List* HT, int hf (char*)) {

    if (words == NULL) {

        make_log(NULL_POINTER);

        return NULL_POINTER;
    }

    int check = HT_ok(HT);

    if (check != OK) {

        make_log(check);
        return check;

    }

    //Fill the table.
    for (int i = 0; i < num_of_words; i++) {

        int pos = 0;

        pos = hf(words[i]) % SIZE_OF_HASH_TABLE;

        if (pos < 0) {

            return HASH_FUNCTION_ERROR;

            make_log(HASH_FUNCTION_ERROR);

        }

        if (find_str(&HT[pos], words[i]) == OK)
            continue;

        int check = inp_nxt(&HT[pos], words[i]);

        if (check != OK) {

            make_log(check);
            return check;

        }
    }

    make_log(OK);

    return OK;
}
//=================================================================
int HT_ok (List* HT) {

    if (HT == NULL) {

        make_log(NULL_POINTER);

        return NULL_POINTER;

    }

    for (int i = 0; i < SIZE_OF_HASH_TABLE; i++) {

        int check = check_ok(&HT[i]);

        if (check != OK) {

            make_log(check);

            return check;

        }
    }

    make_log(OK);

    return OK;
}
//=================================================================
int HT_dtor (List* HT) {

    if (HT == NULL) {

        make_log(NULL_POINTER);
        return NULL_POINTER;

    }

    for (int i = 0; i < SIZE_OF_HASH_TABLE; i++) {

        int check = list_dtor(&HT[i]);

        if (check != OK)
            return check;
    }

    make_log(OK);

    return OK;
}
//=================================================================
void HT_dumper (FILE* dump, List* HT) {

    if (dump == NULL) {

        make_log(NULL_POINTER);

        fprintf(logs, "CAN'T OPEN DUMP FILE");

        return;

    }

    if (HT == NULL) {

        fprintf(dump, "LIST POINTER == NULL. DATA LOCATION IS UNKNOWN.\n");

        fprintf(logs, "DUMP. NULL POINTER.\n");

        return;

    }

    for (int i = 0; i < SIZE_OF_HASH_TABLE; i++) {

        fprintf(dump, "LIST NUMBER %d\n", i);

        dumper(dump, &HT[i]);

    }

    fprintf(logs, "DUMP HAS BEEN COMPLETED\n");

    return;
}
//=================================================================
int count_and_output (FILE* output, List* HT) {

    if (output == NULL) {

        make_log(NULL_POINTER);

        fprintf(logs, "CAN'T CREATE OUTPUT FILE");

        return NULL_POINTER;

    }

    int check = HT_ok(HT);

    if (check != OK) {

        make_log(check);
        return check;

    }

    for (int i = 0; i < SIZE_OF_HASH_TABLE; i++) {

        int sum = 0;
        shft_to_first(&HT[i]);

        while (HT[i].ptr->nxt != NULL) {

            sum++;
            shft_ptr_nxt(&HT[i]);
        }

        fprintf(output, "%d;%d\n", i, sum);
    }

    make_log(OK);

    return OK;
}
//==============================================================
