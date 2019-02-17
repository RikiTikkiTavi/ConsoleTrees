#include <stdio.h>
#include <stdlib.h>

#include "helpers.visualization.h"

void print_margin(int margin) {
    for (int i = 0; i < margin; i++) {
        printf(" ");
    }
}

void print_underlines(int n) {
    for (int i = 0; i < n; i++) {
        printf("_");
    }
}

void print_vertex_row(list vertices, struct layer_params *params) {

    for (list vertex = vertices; vertex != NULL; vertex = vertex->next) {

        // Print vertex left margin
        print_margin(vertex->params->step_v_l);

        // Print vertex value
        if (vertex->t_node != NULL) printf("%d", vertex->t_node->value);
        else printf(" ");
    }
}

void print_edge_x_row(list vertices, struct layer_params *params) {

    int is_second = 0;

    for (list vertex = vertices; vertex != NULL; vertex = vertex->next) {

        if (vertex->t_node != NULL) {
            if (is_second) {
                printf(" \\");
                // Print Underlines
                print_underlines(vertex->params->n_u);
                print_margin(1);
                is_second = 0;
            } else {
                //Print margin of | + 1
                print_margin(vertex->params->m_edge + 1);
                //Print Underlines
                print_underlines(vertex->params->n_u);
                printf("/");
                is_second = 1;
            }
        } else {
            if (is_second) {
                printf("  ");
                // Print Underlines
                print_margin(vertex->params->n_u);
                is_second = 0;
            } else {
                //Print margin of | + 1 and empty underlines
                print_margin(vertex->params->m_edge + 1 + vertex->params->n_u);
                printf(" ");
                is_second = 1;
            }

        }
    }
}

void print_edge_y_row(list vertices, struct layer_params *params) {

    for (list vertex = vertices; vertex != NULL; vertex = vertex->next) {

        //Print margin of |
        print_margin(vertex->params->m_edge);

        // Print |
        if (vertex->t_node != NULL) printf("|");
        else printf(" ");

    }
}

void print_layer(layer_ptr layer) {
    if (layer->params->layer_i == 1) {
        // Print only vertex row
        printf("\n");
        print_vertex_row(layer->vertices, layer->params);
        printf("\n");

    } else {
        // Print all rows
        print_edge_x_row(layer->vertices, layer->params);
        printf("\n");
        print_edge_y_row(layer->vertices, layer->params);
        printf("\n");
        print_vertex_row(layer->vertices, layer->params);
        printf("\n");
    }
}
