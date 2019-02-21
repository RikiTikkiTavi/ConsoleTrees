#include "../utils/types.h"

#ifndef CONSOLETREES_LOGICK_H
#define CONSOLETREES_LOGICK_H

void _init_n_u_vertices_params(list first_vertex);

void _init_vertices_params(layer_ptr current_layer);

void _init_last_layer_vertices_params(layer_ptr last_layer, int step_v0);

layer_ptr _init_layers_params(layer_ptr layer_first, int step_v0);

layer_ptr _init_layers(tree t, char *val_to_string(void *val));

/**
 * @description Visualizes tree
 * @param t - pointer on tree root
 * @param step_v0 - initial step between vertices
 * @param val_to_string - function to convert value of tree node to string
 */
void visualize_tree(tree t, int step_v0, char *val_to_string(void *val));

#endif //CONSOLETREES_LOGICK_H
