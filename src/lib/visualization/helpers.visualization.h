#ifndef CONSOLETREES_VISUALISATION_HELPERS_H
#define CONSOLETREES_VISUALISATION_HELPERS_H

#include "../utils/types.h"

void _print_margin(int margin);

void _print_underlines(int n);

void _print_edge_y_row(list vertices, struct layer_params *params);

void _print_edge_x_row(list vertices, struct layer_params *params);

void _print_vertex_row(list vertices, struct layer_params *params);

void _print_layer(layer_ptr layer);

#endif //CONSOLETREES_VISUALISATION_HELPERS_H
