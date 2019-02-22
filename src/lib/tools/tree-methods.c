#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "tree-methods.h"
#include "../ConsoleTrees.h"

int ct_calc_tree_height(ct_tree t) {
    if (t == NULL)
        return 0;
    else {
        int lDepth = ct_calc_tree_height(t->left);
        int rDepth = ct_calc_tree_height(t->right);

        if (lDepth > rDepth)
            return (lDepth + 1);

        else return (rDepth + 1);
    }
}

ct_tree ct_create_rightist_tree(int *values, int values_q) {
    if(values==NULL){
        printf("l: %d ::: Error in ct_create_rightist_tree(...) ::: values array is NULL", __LINE__);
    }
    if(values_q<1){
        printf("l: %d ::: Error in ct_create_rightist_tree(...) ::: values_q < 1", __LINE__);
    }
    ct_tree root = ct_create_node(&(values[0]));
    ct_tree *right_ptr = &(root->right);
    for (int i = 1; i < values_q; i++) {
        *right_ptr = ct_create_node(&(values[i]));
        right_ptr = &((*right_ptr)->right);
    }
    return root;
}

ct_tree ct_create_random_single_child_tree(int values[], int values_q) {
    if(values==NULL){
        printf("l: %d ::: Error in ct_create_random_single_child_tree(...) ::: values array is NULL", __LINE__);
        return NULL;
    }
    if(values_q<1){
        printf("l: %d ::: Error in ct_create_random_single_child_tree(...) ::: values_q < 1", __LINE__);
        return NULL;
    }

    srand((unsigned int) time(NULL));

    ct_tree root = ct_create_node(&(values[0]));
    int dir = rand() % 2;
    ct_tree *ct_tree_ptr;
    if(dir==1){
        ct_tree_ptr = &(root->right);
    } else {
        ct_tree_ptr = &(root->left);
    }

    for (int i = 1; i < values_q; i++) {
        *ct_tree_ptr = ct_create_node(&(values[i]));
        dir = rand() % 2;
        if(dir==1){
            ct_tree_ptr = &((*ct_tree_ptr)->right);
        } else {
            ct_tree_ptr = &((*ct_tree_ptr)->left);
        }
    }
    return root;
}
