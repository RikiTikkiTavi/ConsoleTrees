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

int calc_vertex_size(int vertex);

vertex_params *create_vertex_params(int v_s, int v_s_l, int v_s_r);

void log_vertex(list vertex, list v_left, list v_right, list v_prev_right, list v_prev);

int isEven(int n);

list get_list_element(list l, int j);

void _append_childs(layer_ptr c_layer, list left, list right);

layer_params *_create_params(int n_vertex, int layer_i);

layer_ptr _create_layer(list vertices, layer_params *params, layer_ptr prev);

void _delete_layers_object(layer_ptr layer_first);

#endif //CONSOLETREES_HELPERS_H
