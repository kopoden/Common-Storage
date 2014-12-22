#include "optimizations.h"

//==============================================================================
#define N (*Node)
//==============================================================================
int O1 (node** Node) { //constants

    if (Node != NULL && N != NULL) {

        double res = 0;

        switch (N->info->Type) {

        case ROOT:

            O1(&N->left);

            break;

        case VAR:

            break;

        case NUM:

            break;

        case FUN:

            switch (N->info->Oper) {

                case ADD:

                    O1(&N->left);

                    O1(&N->rght);

                    res = 0;

                    if (N->left->info->Type == NUM && N->rght->info->Type == NUM) {

                        res = N->left->info->nValue + N->rght->info->nValue;

                        create_new_leaf(Node, NULL, res, NUM, NONE);

                    }

                    break;

                case SUB:

                    O1(&N->left);

                    O1(&N->rght);

                    res = 0;

                    if (N->left->info->Type == NUM && N->rght->info->Type == NUM) {

                        res = N->left->info->nValue - N->rght->info->nValue;

                        create_new_leaf(Node, NULL, res, NUM, NONE);

                    }

                    break;

                case MUL:

                    O1(&N->left);

                    O1(&N->rght);

                    res = 0;

                    if (N->left->info->Type == NUM && N->rght->info->Type == NUM) {

                        res = N->left->info->nValue * N->rght->info->nValue;

                        create_new_leaf(Node, NULL, res, NUM, NONE);
                    }

                    break;

                case DIV:

                    O1(&N->left);

                    O1(&N->rght);

                    res = 0;

                    if (N->left->info->Type == NUM \
                        && N->rght->info->Type == NUM\
                        && N->rght->info->nValue != 0) {

                        res = N->left->info->nValue / N->rght->info->nValue;

                        create_new_leaf(Node, NULL, res, NUM, NONE);
                    }

                    break;

                case DEG:

                    O1(&N->left);

                    O1(&N->rght);

                    if (N->left->info->Type == NUM && N->left->info->nValue == 0) {

                        create_new_leaf(Node, NULL, 0, NUM, NONE);

                        break;

                    }

                    if (N->rght->info->Type == NUM && N->rght->info->nValue == 0) {

                        create_new_leaf(Node, NULL, 1, NUM, NONE);

                    }

                    break;

                case SIN:

                    O1(&N->left);

                    if (N->left->info->Type == NUM) {

                        create_new_leaf(Node, NULL, sin((N->left->info->nValue)), NUM, NONE);

                    }

                    break;

                case COS:

                    O1(&N->left);

                    if (N->left->info->Type == NUM) {

                        create_new_leaf(Node, NULL, cos((N->left->info->nValue)), NUM, NONE);

                    }

                    break;

                default:

                   return UNKNOWN_ERROR;
            }

            break;

        default:

            return UNKNOWN_ERROR;

        }
    }
    return OK;
};
#define SetInfo(Address, type, Val, nVal, Operation)    \
do {                                                    \
        Address->info->Type = type;                     \
        Address->info->Value = Val;                     \
        Address->info->nValue = nVal;                   \
        Address->info->Oper = Operation;                \
} while(0);                                             \
//==============================================================================
int O2 (node** Node) { //Delete unmeaning elements

    if (N != NULL) {

        switch (N->info->Type) {

        case ROOT:

            O2(&N->left);

            break;

        case VAR:

            break;

        case NUM:

            break;

        case FUN:

            switch (N->info->Oper) {

                case ADD:

                    O2(&N->left);

                    O2(&N->rght);

                    if (N->left->info->Type == NUM && N->left->info->nValue == 0) {

                        node_cpy(Node, N->rght);

                        break;
                    }

                    if (N->rght->info->Type == NUM && N->rght->info->nValue == 0) {

                        node_cpy(Node, N->left);

                    }

                    break;

                case SUB:

                    O2(&N->left);

                    O2(&N->rght);

                    if (N->rght->info->Type == NUM && N->rght->info->nValue == 0) {

                        node_cpy(Node, N->left);

                    }

                    break;

                case MUL:

                    O2(&N->left);

                    O2(&N->rght);

                    if (N->left->info->Type == NUM && N->left->info->nValue == 1) {

                        node_cpy(Node, N->rght);

                        break;
                    }

                    if (N->rght->info->Type == NUM && N->rght->info->nValue == 1) {

                        node_cpy(Node, N->left);

                        break;

                    }

                    if ((N->left->info->Type == NUM && N->left->info->nValue == 0) || \
                        (N->rght->info->Type == NUM && N->rght->info->nValue == 0)) {

                        SetInfo(N, NUM, NULL, 0, NONE);

                        delete_node(N->left);
                        N->left = NULL;

                        delete_node(N->rght);
                        N->rght = NULL;

                    }

                    break;

                case DIV:

                    O2(&N->left);

                    O2(&N->rght);

                    if (N->rght->info->Type == NUM && N->rght->info->nValue == 1) {

                        node_cpy(Node, N->left);

                        break;

                    }

                    if ((N->left->info->Type == NUM && N->left->info->nValue == 0) && \
                        (N->rght->info->Type != NUM || N->rght->info->nValue != 0)) {

                        SetInfo(N, NUM, NULL, 0, NONE);

                        delete_node(N->left);
                        N->left = NULL;

                        delete_node(N->rght);
                        N->rght = NULL;
                    }

                    break;

                case DEG:

                    O2(&N->left);

                    O2(&N->rght);

                    break;

                case SIN:

                    O2(&N->left);

                    break;

                case COS:

                    O2(&N->left);

                    break;

                default:

                    break;
            }

            break;

        default:

            break;

        }
    }

    return OK;
};
//==============================================================================
