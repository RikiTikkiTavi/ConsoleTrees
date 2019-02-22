#include "../utils/types.h"

#ifndef CONSOLETREES_LOGICK_H
#define CONSOLETREES_LOGICK_H

void _ct_init_n_u_vertices_params(ct_list first_vertex);

void _ct_init_vertices_params(ct_layer_ptr current_layer);

void _ct_init_last_layer_vertices_params(ct_layer_ptr last_layer, int step_v0);

ct_layer_ptr _ct_init_layers_params(ct_layer_ptr layer_first, int step_v0);

ct_layer_ptr _ct_init_layers(ct_tree t, char *val_to_string(void *val));

/**
 * @description Visualizes tree
 * @param t - pointer on tree root
 * @param step_v0 - initial step between vertices
 * @param val_to_string - function to convert value of tree node to string
 */
void ct_visualize_tree(ct_tree t, int step_v0, char *val_to_string(void *val));

#endif //CONSOLETREES_LOGICK_H
