#include "akinator.h"

int main() {

//=====================================================
    FILE* data_base = fopen("data_base.txt", "r");
    FILE* logs = fopen("logs.txt", "w");
//===========PREPARATION===============================
    fprintf(logs, "===============TREE CREATION=============\n");

    node* tree = NULL;
    tree = grow_from_file(data_base, logs);

    node* ptr = tree;

    fprintf(logs, "============THE END OF CREATION==========\n");

//===========GAME PROCESS==============================
    char ans = 'Y';

    while (ans == 'Y' || ans == 'y') {

        game(ptr, logs);

        printf("Do you want to play again?\n   Y == YES;\n   N == NO\n");

        fflush(stdin);
        scanf("%c", &ans);

        printf("\n\n");

        ptr = tree;
    }

    ans = 'Y';

    printf("Do you want to save new records?\n   Y == YES;\n   N == NO\n");

    fflush(stdin);
    scanf("%c", &ans);

    printf("\n\n");

    if (ans == 'Y' || ans == 'y')
        save_data(data_base, tree, logs);

//===========ENDING====================================

    tree_dump(tree);

    tree_dtor(tree);

    fclose(data_base);
    fclose(logs);

    return 0;
}
