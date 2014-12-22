#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <locale.h>

//==============================================================
/*!
 *     <i> ASSERT macros </i>
 *
 *     \brief This macros show error if condition is false \n
 *            <i> <u>This macros works if DEBUG defined!</i> </u>
 *            <b> Input :</b> Condition \n
 *            <b> Output:</b> Abort program or do nothing.
 *     \return                None
 *
 */
//==============================================================

#define DEBUG

#ifdef DEBUG
    #define ASSERT( cond )                           \
        do {                                         \
            if ( ! ( cond ) ) {                      \
                printf ( "FAIL %s in %s, %s ( %d )", \
                #cond, __PRETTY_FUNCTION__,          \
                __FILE__, __LINE__ );                \
                abort();                             \
            } \
        } while (0);
#else
    #define ASSERT( cond ) ;
#endif

//=============================================================
void write_to_file (char** text, const long int length, FILE* file_for_writing);
void free_mem (void* mem);
int compareAZ(const void* str1, const void* str2);
int compareZA(const void* str1, const void* str2);
long int count_lines (const char* buf, long int length);
void divide_into_lines (char* buf, long int length, char** text);
//===============================================================

//===============================================================
/*! void write_to_file (char** text, const long int length, FILE* file_for_writing);

    \brief Writes text to file.
*/
//===============================================================
void write_to_file (char** text, const long int length, FILE* file_for_writing) {

    for (long int i = 0; i < length; i++) {
        ASSERT((i >= 0) && (i < length));
        fprintf(file_for_writing, text[i]);
        fprintf(file_for_writing, "\n");
    }
}
//================================================================

//================================================================
/*! void free_mem (char* mem);

    \brief Clear buffer
*/
//===============================================================
void free_mem (void* mem) {
    free(mem);
    mem = 0;
}
//===============================================================

//===============================================================
/*! int compareAZ (const void* str1, const void* str2);

    \brief To sort lines from A to Z
*/
//===============================================================
int compareAZ (const void* str1, const void* str2) {

    long int i = 0;
    char** str11 = (char**) str1;
    char** str22 = (char**) str2;

    while ( ((*str11)[i] != 0) && ((*str22)[i] != 0) ) {
        if ((*str11)[i] < (*str22)[i]) return -1;
        if ((*str11)[i] > (*str22)[i]) return 1;
        i++;
    }

    return 0;
}
//==================================================================

//==================================================================
/*! int compareZA (const void* str1, const void* str2);

    \brief To sort lines from Z to A
*/
//==================================================================
int compareZA (const void* str1, const void* str2) {

    long int i = 0;
    char** str11 = (char**) str1;
    char** str22 = (char**) str2;

    while ( ((*str11)[i] != 0) && ((*str22)[i] != 0) ) {
        if ((*str11)[i] > (*str22)[i]) return -1;
        if ((*str11)[i] < (*str22)[i]) return 1;
        i++;
    }

    return 0;
}
//==================================================================

//==================================================================
/*! long int count_lines (const char* buf, long int length);

    \brief Counts number of lines is txt file.
*/
//==================================================================
long int count_lines (const char* buf, long int length) {

    long int am_of_lines = 0;

    for (long int i = 0; i < length; i++) {
        ASSERT((i >= 0) && (i < length));
        if (buf[i] == '\n')
            am_of_lines++;
    }

    return am_of_lines;

}
//==================================================================

//==================================================================
/*! void divide_into_lines (char* buf, long int length, char** text);

    \brief Divides buffer into lines.
*/
//====================================================================
void divide_into_lines (char* buf, long int length, char** text) {

    long int line = 0;
    text[0] = buf;
    ASSERT(text[0] != 0);

    for (long int i = 0; i < length; i++) {
        ASSERT((i >= 0) && (i < length));
        if (buf[i] == '\n') {
            line++;
            buf[i] = 0;
            if  (i+1 < length) {
                text[line] = &buf[i+1];
                ASSERT(text[line] != 0);
            }
        }
    }

}

//============MAIN==================================================
/*! int main();

    \brief Transform Pushkin's poem into the list of lines, sorted in A->Z or Z->A order
*/
//==================================================================
int main() {
//============Open file===========================
    FILE* input = fopen("onegin.txt", "r");
    FILE* outputAZ = fopen("oneginAZ.txt", "w");
    FILE* outputZA = fopen("oneginZA.txt", "w");
//================================================

//==============Enable Russian Language===========
    setlocale(LC_CTYPE, "russian");
//================================================

//==============Read text to buffer===============
    long int length_of_file = filelength(fileno(input));

    char* buffer = (char*) calloc (length_of_file + 1, sizeof(*buffer));
    ASSERT(buffer != 0);

    fread(buffer, sizeof(*buffer), length_of_file, input);

    long int num_of_lines = count_lines(buffer, length_of_file);

    char** text = (char**) calloc (num_of_lines + 1, sizeof(*text));
    ASSERT(text != 0);

//===============divide buffer into lines=======================================

    divide_into_lines(buffer, length_of_file, text);

//===============Sort from A to Z and write to outputAZ==========================

    qsort(text, num_of_lines, sizeof(char*), compareAZ);
    write_to_file(text, num_of_lines, outputAZ);

//===============Sort from Z to A and write to outputZA==========================

    qsort(text, num_of_lines, sizeof(char*), compareZA);
    write_to_file(text, num_of_lines, outputZA);

//============Free memory=========================

    free_mem(buffer);
    free_mem(text);

//============Close files=========================

    fclose(input);
    input = NULL;

    fclose(outputAZ);
    outputAZ = NULL;

    fclose(outputZA);
    outputZA = NULL;

    return 0;
}

//first------------------------------------------------------------
    while (fscanf(Source, "%s", line) != 0) {
        //lable
        printf("%s - line\n", line);
        if (line[0] == ':') {

            int name = -1;
            scanf(line, ":%d", &name);
            printf("%d - label\n", name);

            if ((name < 0) || (name > 9))
                return WRONG;

            LableTable[name] = adress;

        }
        else {
        //not lable
            bool exist = false;
            int i = 0;
            for (i = 0; i < NUM_OF_COMMANDS; i++)
                if (strcmp((const char*) line, CommandTable[i].Name) == 0) {
                    printf("%d - I\n", i);
                    if ((i == PUSH) || (i == POP)) {
                        int reg = -1;
                        printf("%d - I\n", i);
                        fscanf(Source, " reg%d", &reg);
                        printf("%d - reg1\n", reg);

                        if ((reg >= 0) && (reg <= 31))
                            exist = true;
                    }

                    if ((i > POP) && (i < JAE)) {
                            printf("%d - I\n", i);
                            exist = true;
                    }

                    if (i >= JAE) {
                        printf("%d - I\n", i);
                        int label = 0;
                        sscanf(line, "%d", &label);

                        if ((label >= 0) && (label <= 9))
                            exist = true;
                    }

                    break;
                }

            if (exist == true) {
                adress = adress + CommandTable[i].Arg;
                printf("%d - ADRESS\n", adress);
            }
            else
                return WRONG;
        }

        for (int i = 0; i < MAX_COMMAND_LENGTH; i++) {
            line[i] = 0;
            cmd[i] = 0;
        }
    }
long offset = 0;
fseek(Source, offset, 0);
//Second-----------------------------------------------------------
    while (fscanf(Source, "%s", line) != 0) {
        if (line[0] != ':') {
        //not lable
            printf("%s - line sec\n", line);
            bool exist = false;
            int i = 0;
            for (i = 0; i < NUM_OF_COMMANDS; i++)
                if (strcmp((const char*) line, CommandTable[i].Name) == 0) {

                    if ((i == PUSH) || (i == POP)) {
                        int reg = -1;
                        sscanf(line, "reg%d", &reg);

                        if ((reg >= 0) && (reg <= 31)) {
                            exist = true;
                            fprintf(Asm, "%d%d", i, reg);
                            break;
                        }
                    }

                    if ((i > POP) && (i < JAE)) {
                            fprintf(Asm, "%d", i);
                            exist = true;
                            break;
                    }

                    if (i >= JAE) {
                        int label = 0;
                        sscanf(line, "%d", &label);

                        if ((label >= 0) && (label <= 9) && (LableTable[label] != -1)) {
                            fprintf(Asm, "%d%d", i, LableTable[label]);
                            exist = true;
                            break;
                        }
                    }
                }

            if (exist == false)
                return WRONG;
        }

        for (int i = 0; i < MAX_COMMAND_LENGTH; i++) {
            line[i] = 0;
            cmd[i] = 0;
        }
    }
