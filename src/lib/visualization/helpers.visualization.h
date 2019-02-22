#ifndef CONSOLETREES_VISUALISATION_HELPERS_H
#define CONSOLETREES_VISUALISATION_HELPERS_H

#include "../utils/types.h"

void _ct_print_margin(int margin);

void _ct_print_underlines(int n);

void _ct_print_val(ct_tree t_node, char *val_to_string(void *val));

void _ct_print_edge_y_row(ct_list vertices);

void _ct_print_edge_x_row(ct_list vertices);

void _ct_print_vertex_row(ct_list vertices, char *val_to_string(void *val));

void _ct_print_layer(ct_layer_ptr layer, char *val_to_string(void *val));

#endif //CONSOLETREES_VISUALISATION_HELPERS_H
