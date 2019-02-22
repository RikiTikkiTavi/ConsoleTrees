#include <stdio.h>
#include <stdlib.h>

#include "helpers.visualization.h"

void _ct_print_margin(int margin) {
    for (int i = 0; i < margin; i++) {
        printf(" ");
    }
}

void _ct_print_underlines(int n) {
    for (int i = 0; i < n; i++) {
        printf("_");
    }
}

void _ct_print_val(ct_tree t_node, char *(*val_to_string)(void *val)) {
    if (t_node == NULL) {
        printf(" ");
    } else {
        char *str_buffer = val_to_string(t_node->value_ptr);
        printf("%s", str_buffer);
        free(str_buffer);
    }
}

void _ct_print_vertex_row(ct_list vertices, char *val_to_string(void *val)) {

    for (ct_list vertex = vertices; vertex != NULL; vertex = vertex->next) {

        // Print vertex left margin
        _ct_print_margin(vertex->params->step_v_l);

        // Print vertex value_ptr
        _ct_print_val(vertex->t_node, val_to_string);

    }
}

void _ct_print_edge_x_row(ct_list vertices) {

    int is_second = 0;

    for (ct_list vertex = vertices; vertex != NULL; vertex = vertex->next) {

        if (vertex->t_node != NULL) {
            if (is_second) {
                printf(" \\");
                // Print Underlines
                _ct_print_underlines(vertex->params->n_u);
                _ct_print_margin(1);
                is_second = 0;
            } else {
                //Print margin of | + 1
                _ct_print_margin(vertex->params->m_edge + 1);
                //Print Underlines
                _ct_print_underlines(vertex->params->n_u);
                printf("/");
                is_second = 1;
            }
        } else {
            if (is_second) {
                // print " \" + empty underlines + 1
                _ct_print_margin(2 + vertex->params->n_u + 1);
                is_second = 0;
            } else {
                //Print margin of | + 1 + empty underlines + /
                _ct_print_margin(vertex->params->m_edge + 1 + vertex->params->n_u + 1);
                is_second = 1;
            }

        }
    }
}

void _ct_print_edge_y_row(ct_list vertices) {

    for (ct_list vertex = vertices; vertex != NULL; vertex = vertex->next) {

        //Print margin of |
        _ct_print_margin(vertex->params->m_edge);

        // Print |
        if (vertex->t_node != NULL) printf("|");
        else printf(" ");

    }
}

void _ct_print_layer(ct_layer_ptr layer, char *val_to_string(void *val)) {
    if (layer->params->layer_i == 1) {
        // Print only vertex row
        printf("\n");
        _ct_print_vertex_row(layer->vertices, val_to_string);
        printf("\n");

    } else {
        // Print all rows
        _ct_print_edge_x_row(layer->vertices);
        printf("\n");
        _ct_print_edge_y_row(layer->vertices);
        printf("\n");
        _ct_print_vertex_row(layer->vertices, val_to_string);
        printf("\n");
    }
}