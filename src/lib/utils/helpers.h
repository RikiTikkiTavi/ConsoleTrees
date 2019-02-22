#ifndef CONSOLETREES_HELPERS_H
#define CONSOLETREES_HELPERS_H

#include "types.h"

/**
 * @description Creates tree node with node->value = value
 * @param value - integer
 * @return tree pointer
 */
ct_tree ct_create_node(void *value_ptr);

/**
 * @description Creates list element
 * @param t_node
 * @return list pointer
 */
ct_list ct_create_list_el(ct_tree t_node, char *val_to_string(void *val));

/**
 * @description Frees memory, where tree is allocated
 * @param t - tree pointer
 */
void ct_delete_tree(ct_tree t);

/**
 * @description Frees memory, where list is allocated
 * @param l
 */
void ct_delete_list(ct_list l);

void _ct_create_subtree(ct_tree t, int *arr, int i, int arr_length);

/**
 * @description Converts tree from array
 * @param arr - integer array
 * @param arr_length - length of array
 * @return pointer on tree root
 */
ct_tree ct_array_to_tree(int *arr, int arr_length);

int _ct_calc_vertex_size(void *val, char *val_to_string(void *val));

vertex_params *_ct_create_vertex_params(int v_s, int v_s_l, int v_s_r);

void _log_vertex(ct_list vertex, ct_list v_left, ct_list v_right, ct_list v_prev_right, ct_list v_prev);

int ct_isEven(int n);

/**
 * @description Gets j element of linked list l
 * @param l linked list
 * @param j
 * @return
 */
ct_list ct_get_list_element(ct_list l, int j);

void _ct_append_childs(ct_layer_ptr c_layer, ct_list left, ct_list right);

ct_layer_params *_ct_create_params(int n_vertex, int layer_i);

ct_layer_ptr _ct_create_layer(ct_list vertices, ct_layer_params *params, ct_layer_ptr prev);

void _ct_delete_layers_object(ct_layer_ptr layer_first);

char *ct_int_to_string(void *n);

#endif //CONSOLETREES_HELPERS_H
