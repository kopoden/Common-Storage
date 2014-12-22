#include "TokenTree.h"

//================================================================================
int delete_node(node* Node) {

    if (Node != NULL) {

        if (Node->info != NULL)
            free(Node->info->Value);

        free(Node->info);

        free(Node);
    }

    return OK;
};
//================================================================================
int node_cpy(node** NewNode, node* OldNode) {

    if (OldNode == NULL)
        return NULL_POINTER;

    *NewNode = (node*) calloc (1, sizeof(node));

    if (*NewNode == NULL)
        return ERR_MEM;

    (*NewNode)->info = (Token*) calloc (1, sizeof(Token));

    if ((*NewNode)->info == NULL)
        return ERR_MEM;

    if (OldNode->info->Value != NULL) {

        (*NewNode)->info->Value = (char*) calloc (100, sizeof(char));

        if ((*NewNode)->info->Value == NULL)
            return ERR_MEM;

        strcpy((*NewNode)->info->Value, OldNode->info->Value);
    }

    (*NewNode)->info->Oper = OldNode->info->Oper;
    (*NewNode)->info->Type = OldNode->info->Type;
    (*NewNode)->info->nValue = OldNode->info->nValue;


    (*NewNode)->left = OldNode->left;
    (*NewNode)->rght = OldNode->rght;
    (*NewNode)->mid = OldNode->mid;

    (*NewNode)->CurVal = OldNode->CurVal;

    return OK;

};
//================================================================================
int tree_cpy(node** NewTree, node* OldTree) {

    node_cpy(NewTree, OldTree);

    if (OldTree->left != NULL)

        tree_cpy(&((*NewTree)->left), OldTree->left);

    if (OldTree->mid != NULL)

        tree_cpy(&((*NewTree)->mid), OldTree->mid);

    if (OldTree->rght != NULL)

        tree_cpy(&((*NewTree)->rght), OldTree->rght);

    return OK;
}
//================================================================================
int create_new_leaf (node** new_leaf, const char* Val, double nVal, int TokenType, int Operation) {

    if (new_leaf == NULL)
        return ERR_MEM;

    if(*new_leaf != NULL)
        delete_node(*new_leaf);

    *new_leaf = (node*) calloc (1, sizeof(node));

    (*new_leaf)->info = (Token*) calloc (1, sizeof(Token));

    if (*new_leaf == NULL || (*new_leaf)->info == NULL)
        return ERR_MEM;

    if (Val != NULL) {

        (*new_leaf)->info->Value = (char*) calloc (100, sizeof(char));

        strcpy((*new_leaf)->info->Value, Val);

    }

    (*new_leaf)->info->Oper = Operation;
    (*new_leaf)->info->Type = TokenType;
    (*new_leaf)->info->nValue = nVal;

    (*new_leaf)->left = NULL;
    (*new_leaf)->rght = NULL;
    (*new_leaf)->mid = NULL;

    (*new_leaf)->CurVal = 0;


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
int add_mid (node* parent, node* descendent) {

    if ((parent == NULL) || (descendent == NULL))
        return NULL_POINTER;

    parent->mid = descendent;

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
    int check_mid = OK;

    if (cur_node->info == NULL)
        return NULL_DATA_FIELD;

    if (cur_node->left != NULL)
        check_left = tree_ok(cur_node->left);

    if (cur_node->rght != NULL)
        check_rght = tree_ok(cur_node->rght);

    if (cur_node->mid != NULL)
        check_rght = tree_ok(cur_node->mid);

    if (check_left != OK)
        return check_left;

    if (check_rght != OK)
        return check_rght;

    if (check_mid != OK)
        return check_mid;

    return OK;
}
//================================================================================

//================================================================================
void print_node (FILE* dump, node* cur_node, int leng) {

    for (int i = 0; i < leng; i++)
        fprintf(dump, " ");

    int new_leng = 0;

    if ((cur_node->left != NULL) || (cur_node->rght != NULL) || (cur_node->mid != NULL)) {

        if (cur_node->info->Type != NUM)
            new_leng = leng + fprintf(dump, "(%s %d %d\n", cur_node->info->Value, cur_node->info->Type, cur_node->info->Oper) - 1;
        else
            new_leng = leng + fprintf(dump, "(%lg %d %d\n", cur_node->info->nValue, cur_node->info->Type, cur_node->info->Oper) - 1;

    }

    else {

        if (cur_node->info->Type != NUM)
            new_leng = leng + fprintf(dump, "(%s %d %d", cur_node->info->Value, cur_node->info->Type, cur_node->info->Oper) - 1;
        else
            new_leng = leng + fprintf(dump, "(%lg %d %d", cur_node->info->nValue, cur_node->info->Type, cur_node->info->Oper) - 1;
    }

    if (cur_node->left != NULL)
        print_node(dump, cur_node->left, new_leng);

    if (cur_node->mid != NULL)
        print_node(dump, cur_node->mid, new_leng);

    if (cur_node->rght != NULL)
        print_node(dump, cur_node->rght, new_leng);

    if ((cur_node->left != NULL) || (cur_node->rght != NULL) || (cur_node->mid != NULL))
        for (int i = 0; i < leng; i++)
            fprintf(dump, " ");

    fprintf(dump, ")\n");

}
//================================================================================
int tree_dump (node* tree) {

    FILE* dump = fopen("dump.txt", "a");

    if (dump == NULL) {

        return DUMP_ERROR;
    }

    if (tree == NULL) {

        fprintf(dump, "Dump error. Tree pointer is NULL.\n");

        fclose(dump);

        return NULL_POINTER;
    }

    fprintf(dump, "\n\n====================TREE==DUMP==========================\n\n");

    print_node(dump, tree, 0);

    fclose(dump);

    return OK;
}
//================================================================================
int tree_dtor (node* tree) {

    if (tree == NULL) {

        return NULL_POINTER;
    }

    if (tree->left != NULL)
        tree_dtor(tree->left);

    if (tree->rght != NULL)
        tree_dtor(tree->rght);

    if (tree->mid != NULL)
        tree_dtor(tree->mid);

    delete_node(tree);

    return OK;
}
//================================================================================
