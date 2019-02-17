#include <stdio.h>
#include <stdlib.h>
#include "logick.visualization.h"
#include "../utils/types.h"
#include "../utils/helpers.h"
#include "../utils/calculators.h"
#include "helpers.visualization.h"
#include "../tools/tree-methods.h"

void _init_n_u_vertices_params(list first_vertex);

void _init_vertices_params(layer_ptr current_layer);

void _init_last_layer_vertices_params(layer_ptr last_layer, int step_v0);

layer_ptr _init_layers_params(layer_ptr layer_first, int step_v0);

layer_ptr _init_layers(tree t);

void visualize_tree(tree t, int step_v0) {

    if(t==NULL)
        return;

    if(step_v0 < 3){
        printf("\nl: %d ::: Error in visualize_tree(tree t, int step_v0) ::: step_v0 must be bigger then 3\n", __LINE__);
        return;
    }

    // Init layers_object
    layer_ptr layer_first = _init_layers(t);
    layer_ptr layer_last = _init_layers_params(layer_first, step_v0);

    layer_ptr layer_current = layer_first;

    // Print each layer
    for (; layer_current != NULL; layer_current = layer_current->next) {
        _print_layer(layer_current);
    }

    _delete_layers_object(layer_first);
    layer_first = NULL;
    layer_last = NULL;
}

layer_ptr _init_layers(tree t) {

    layer_ptr layer_first = _create_layer(create_list_el(t), _create_params(1, 1), NULL);

    int h_max = calc_tree_height(t);
    int layer_i = 1;
    layer_ptr c_layer = layer_first;

    // Create layers list with basic params
    for (; layer_i < h_max; layer_i++) {
        // Init next layer
        c_layer->next = _create_layer
                (
                        NULL,
                        _create_params(c_layer->params->n_vertex * 2, c_layer->params->layer_i + 1),
                        c_layer
                );

        list vertex = c_layer->vertices;

        // Create next layer
        while (vertex != NULL) {
            if (vertex->t_node == NULL) {
                // Emulated node
                _append_childs(c_layer, create_list_el(NULL), create_list_el(NULL));
            } else {
                // Real node
                _append_childs(c_layer, create_list_el(vertex->t_node->left), create_list_el(vertex->t_node->right));
            }
            vertex = vertex->next;
        }

        c_layer = c_layer->next;
        // c_layer is now last layer
    }

    return layer_first;
}

layer_ptr _init_layers_params(layer_ptr layer_first, int step_v0) {

    // Get last layer
    layer_ptr last_layer = layer_first;
    while (last_layer->next != NULL) {
        last_layer = last_layer->next;
    }

    _init_last_layer_vertices_params(last_layer, step_v0);

    layer_ptr current_layer = last_layer->prev;

    while (current_layer != NULL) {

        _init_vertices_params(current_layer);

        current_layer = current_layer->prev;
    }

    return last_layer;

}

void _init_last_layer_vertices_params(layer_ptr last_layer, int step_v0) {
    // Init params of last layer vertices
    list last_layer_vertex = last_layer->vertices;
    int j = 0;
    list v_prev = NULL;
    while (last_layer_vertex != NULL) {
        last_layer_vertex->params->step_v_l = step_v0;
        last_layer_vertex->params->j = j;

        // Init edge_y margin
        if (j == 0) {
            last_layer_vertex->params->m_edge = _calc_first_edge_margin(last_layer_vertex);
        } else {
            last_layer_vertex->params->m_edge = _calc_edge_margin(last_layer_vertex, v_prev);
        }

        v_prev = last_layer_vertex;
        last_layer_vertex = last_layer_vertex->next;
        j++;
    }
    _init_n_u_vertices_params(last_layer->vertices);
}

void _init_vertices_params(layer_ptr current_layer) {
    int j = 0;
    list vertex = current_layer->vertices;
    while (vertex != NULL) {

        // Set element number
        vertex->params->j = j;

        // Get left child
        list v_left = get_list_element(current_layer->next->vertices, 2 * j);
        // Get right child
        list v_right = get_list_element(current_layer->next->vertices, 2 * j + 1);

        // If element is first element in layer
        if (j == 0) {

            // Calculate left margin of current vertex
            vertex->params->step_v_l = _calc_first_v_step_v_l(v_left, v_right, vertex);

            // If current layer is not first
            if (current_layer->params->layer_i != 1) {

                // Calculate margin of edge_y
                vertex->params->m_edge = _calc_first_edge_margin(vertex);

            }
        } else {

            // Element is not first

            // Get right child of previous vertex
            list v_prev_right = get_list_element(current_layer->next->vertices, 2 * j - 1);
            // Get previous vertex
            list v_prev = get_list_element(current_layer->vertices, j - 1);

            // Calculate left margin of current vertex
            vertex->params->step_v_l = _calc_v_step_v_l(v_left, v_right, v_prev_right, v_prev, vertex);

            // Calculate margin of edge_y
            vertex->params->m_edge = _calc_edge_margin(vertex, v_prev);
        }

        // Go to next vertex
        vertex = vertex->next;
        j++;
    }

    // Calculate number of underlines for each vertex
    _init_n_u_vertices_params(current_layer->vertices);
}

void _init_n_u_vertices_params(list first_vertex) {
    // Handle 1 layer
    if (first_vertex->next == NULL) {
        first_vertex->params->n_u = 0;
        return;
    }
    list vertex = first_vertex;
    int j = 0;
    list v_prev = NULL;
    while (vertex != NULL) {
        if (isEven(j)) {
            vertex->params->n_u = _calc_underlines_left(vertex, vertex->next);
        } else {
            vertex->params->n_u = _calc_underlines_right(vertex, v_prev);
        }
        v_prev = vertex;
        vertex = vertex->next;
        j++;
    }
}
