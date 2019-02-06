#ifndef CONSOLETREES_HELPERS_H
#define CONSOLETREES_HELPERS_H

#include "../types.h"

tree create_node(int value);

list create_list_el(tree t_node);

void deleteTree(tree t);

void deleteList(list l);

void create_subtree(tree t, int arr[], int i, int arr_length);

tree array_to_tree(int arr[], int arr_length);

void add_nodes_to_array(tree t, int arr[], int i);

int *tree_to_array(tree t, int *arr_length);

#endif //CONSOLETREES_HELPERS_H
