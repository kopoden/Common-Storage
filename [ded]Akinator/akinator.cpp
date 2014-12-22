#include "akinator.h"

//=======================================================================
//=======================================================================
void print_vert (FILE* data_base, node* vert, FILE* logs) {

    fprintf(data_base, "('%s'", vert->info);
    fprintf(logs, "ADD %s\n", vert->info);

    if (vert->left != NULL)
        print_vert(data_base, vert->left, logs);

    if (vert->rght != NULL)
        print_vert(data_base, vert->rght, logs);

    fprintf(data_base, ")");

}
//=======================================================================
int save_data (FILE* data_base, node* tree, FILE* logs) {

    fprintf(logs, "=========SAVING DATA...=========\n");

    fclose(data_base);

    FILE* new_data_base = fopen("data_base.txt", "w");

    if (tree == NULL)
        return OK;

    print_vert(new_data_base, tree, logs);

    fprintf(logs, "=========NEW DATA BASE HAS BEEN SUCCESSFULLY SAVED=========\n");

    return OK;
}
//=======================================================================
int game (node* cur_node, FILE* logs) {

    char ans = 'Y';

    while (cur_node->left != NULL || cur_node->rght != NULL) {

        printf("%s?\n", cur_node->info);

        fflush(stdin);
        ans = getchar();

        if (ans == 'Y' || ans == 'y')
            turn_left(&cur_node);


        if (ans == 'N' || ans == 'n') {

            if (cur_node->rght == NULL) {

                printf("\nI'm sorry, but I don't know the answer."
                       " Please, help me.\nWho is this person?"
                       " What particular quality has he?\n\nExample: Eminem; The_best_rap-singer_ever\n");

                node* NewNodeYes = NULL;
                node* NewNodeQuestion = NULL;

                char* quality = (char*) calloc (MAX_STRING_LENG, sizeof(char));
                char* name = (char*) calloc (MAX_STRING_LENG, sizeof(char));

                fflush(stdin);

                scanf("%[^;];%s", name, quality);

                create_new_leaf(&NewNodeYes, name);
                create_new_leaf(&NewNodeQuestion, quality);

                add_rght(cur_node, NewNodeQuestion);
                add_left(NewNodeQuestion, NewNodeYes);

                printf("\nThank you!\n");

                return OK;
            }

            turn_rght(&cur_node);
        }
    }

    ans = 'Y';
    printf("\nI'm sure, you mean %s!\nDo you?\n   Y == YES;\n   N == NO\n", cur_node->info);

    fflush(stdin);
    ans = getchar();

    if (ans == 'y' || ans == 'Y') {

        printf("\nHurray! I have never been wrong =)\n");
        return OK;
    }

    if (ans == 'n' || ans == 'N') {

        printf("\nI'm sorry, but I don't know the answer."
               " Please, help me.\nWho is this person?"
               " What particular quality has he?\n\nExample: Eminem; The_best_rap-singer_ever\n");

        node* NewNodeYes = NULL;
        node* NewNodeNo = NULL;

        char* quality = (char*) calloc (MAX_STRING_LENG, sizeof(char));
        char* name = (char*) calloc (MAX_STRING_LENG, sizeof(char));

        fflush(stdin);

        scanf("%[^;];%s", name, quality);

        create_new_leaf(&NewNodeYes, name);
        create_new_leaf(&NewNodeNo, cur_node->info);

        cur_node->info = quality;

        add_left(cur_node, NewNodeYes);
        add_rght(cur_node, NewNodeNo);

        printf("\nThank you!\n");

        return OK;
    }

    return OK;
}
//=======================================================================

