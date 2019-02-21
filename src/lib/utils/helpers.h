#ifndef CONSOLETREES_HELPERS_H
#define CONSOLETREES_HELPERS_H

#include "types.h"

/**
 * @description Creates tree node with node->value = value
 * @param value - integer
 * @return tree pointer
 */
tree create_node(int value);

/**
 * @description Creates list element
 * @param t_node
 * @return list pointer
 */
list create_list_el(tree t_node, char *val_to_string(void *val));

/**
 * @description Frees memory, where tree is allocated
 * @param t - tree pointer
 */
void delete_tree(tree t);

/**
 * @description Frees memory, where list is allocated
 * @param l
 */
void delete_list(list l);

void _create_subtree(tree t, int *arr, int i, int arr_length);

/**
 * @description Converts tree from array
 * @param arr - integer array
 * @param arr_length - length of array
 * @return pointer on tree root
 */
tree array_to_tree(int arr[], int arr_length);

void _add_nodes_to_array(tree t, int *arr, int k);

/**
 * @description Converts tree to array
 * @param t - pointer on tree
 * @param arr_length - length of array
 * @return pointer on tree
 */
int *tree_to_array(tree t, int *arr_length);

int _calc_vertex_size(void *val, char *val_to_string(void *val));

vertex_params *_create_vertex_params(int v_s, int v_s_l, int v_s_r);

void _log_vertex(list vertex, list v_left, list v_right, list v_prev_right, list v_prev);

int isEven(int n);

/**
 * @description Gets j element of linked list l
 * @param l linked list
 * @param j
 * @return
 */
list get_list_element(list l, int j);

void _append_childs(layer_ptr c_layer, list left, list right);

layer_params *_create_params(int n_vertex, int layer_i);

layer_ptr _create_layer(list vertices, layer_params *params, layer_ptr prev);

void _delete_layers_object(layer_ptr layer_first);

char *int_to_string(void *n);

#endif //CONSOLETREES_HELPERS_H
