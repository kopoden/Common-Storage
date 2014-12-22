#include "tree.h"

//================================================================================
node* grow_from_file (FILE* base, FILE* logs) {

    node* leaf = NULL;
    node* tree = NULL;

    char ch = 0;
    ch = getc(base);

    switch (ch) {

        case '(':

            create_new_leaf(&tree, NULL);
            tree->info = (char*) calloc (MAX_STRING_LENG, sizeof(char));

            fscanf(base, "'%[^']'", tree->info);
            fprintf(logs, "IN FUNCTION = %s\n", tree->info);

            leaf = grow_from_file(base, logs);

            if (leaf == NULL)
                return tree;

            fprintf(logs, "NEW LEFT LEAF %s OF %s\n", leaf->info, tree->info);
            add_left(tree, leaf);

            leaf = grow_from_file(base, logs);

            if (leaf == NULL)
                return tree;

            fprintf(logs, "NEW RIGHT LEAF %s OF %s\n", leaf->info, tree->info);
            add_rght(tree, leaf);

            ch = getc(base);

            if (ch == '(') {
                fprintf(logs, "ERROR, THIRD LEAF OF BINARY NODE\n");
                return NULL;
            }

            ungetc(ch, base);

            break;

        case ')':
            fprintf(logs, "DEADLOCK\n");
            return NULL;

        default:
            return NULL;
    }

    fprintf(logs, "EXIT FROM %s\n", tree->info);
    ch = getc(base);

    return tree;

}
//================================================================================
int create_new_leaf (node** new_leaf, char* String) {

    *new_leaf = (node*) calloc (1, sizeof(node));

    if (*new_leaf == NULL)
        return ERR_MEM;

    (*new_leaf)->info = String;
    (*new_leaf)->left = NULL;
    (*new_leaf)->rght = NULL;

    return OK;

}
//================================================================================
int add_rght (node* parent, node* descendent) {

    if ((parent == NULL) || (descendent == NULL))
        return NULL_POINTER;

    parent->rght = descendent;

    return OK;
}
//================================================================================
int add_left (node* parent, node* descendent) {

    if ((parent == NULL) || (descendent == NULL))
        return NULL_POINTER;

    parent->left = descendent;

    return OK;
}
//================================================================================
int turn_rght (node** ptr) {

    if ((*ptr) == NULL)
        return NULL_POINTER;

    if ((*ptr)->rght == NULL)
        return NULL_POINTER;

    (*ptr) = (*ptr)->rght;

    return OK;
}
//================================================================================
int turn_left (node** ptr) {

    if ((*ptr) == NULL)
        return NULL_POINTER;

    if ((*ptr)->left == NULL)
        return NULL_POINTER;

    (*ptr) = (*ptr)->left;

    return OK;
}
//================================================================================
int tree_ok (node* cur_node) {

    int check_left = OK;
    int check_rght = OK;

    if (cur_node->info == NULL)
        return NULL_DATA_FIELD;

    if (cur_node->left != NULL)
        check_left = tree_ok(cur_node->left);

    if (cur_node->rght != NULL)
        check_rght = tree_ok(cur_node->rght);

    if (check_left != OK)
        return check_left;

    if (check_rght != OK)
        return check_rght;

    return OK;
}
//================================================================================
void print_node (FILE* dump, node* cur_node, int leng) {

    for (int i = 0; i < leng; i++)
        fprintf(dump, " ");

    int new_leng = 0;

    if ((cur_node->left != NULL) || (cur_node->rght != NULL))
        new_leng = leng + fprintf(dump, "(%s\n", cur_node->info) - 1;

    else
        new_leng = leng + fprintf(dump, "(%s", cur_node->info) - 1;

    if (cur_node->left != NULL)
        print_node(dump, cur_node->left, new_leng);

    if (cur_node->rght != NULL)
        print_node(dump, cur_node->rght, new_leng);

    if ((cur_node->left != NULL) || (cur_node->rght != NULL))
        for (int i = 0; i < leng; i++)
            fprintf(dump, " ");

    fprintf(dump, ")\n");

}
//================================================================================
void tree_dump (node* tree) {

    FILE* dump = fopen("dump.txt", "w");

    if (tree == NULL) {

        fprintf(dump, "Dump error\n");
        fclose(dump);
        return;
    }

    print_node(dump, tree, 0);

    fclose(dump);
}
//================================================================================
void tree_dtor (node* tree) {

    if (tree == NULL) {
        tree_dump(tree);
        return;
    }

    if (tree->left != NULL)
        tree_dtor(tree->left);

    if (tree->rght != NULL)
        tree_dtor(tree->rght);

    free(tree->info);
    free(tree);

    return;
}
//================================================================================
