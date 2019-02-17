#ifndef CONSOLETREES_VISUALISATION_HELPERS_H
#define CONSOLETREES_VISUALISATION_HELPERS_H

#include "../utils/types.h"

void print_margin(int margin);

void print_underlines(int n);

void print_edge_y_row(list vertices, struct layer_params *params);

void print_edge_x_row(list vertices, struct layer_params *params);

void print_vertex_row(list vertices, struct layer_params *params);

void print_layer(layer_ptr layer);

#endif //CONSOLETREES_VISUALISATION_HELPERS_H
