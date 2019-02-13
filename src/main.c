#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "lib/types.h"
#include "lib/utils/calculators.h"
#include "lib/utils/helpers.h"
#include "lib/visualization/helpers.visualization.h"

void append_childs(layer_ptr c_layer, list left, list right) {
    if (c_layer->next->vertices == NULL) {
        c_layer->next->vertices = left;
        c_layer->next->vertices->next = right;
    } else {
        list lastInNextLayer = c_layer->next->vertices;
        while (lastInNextLayer->next != NULL) {
            lastInNextLayer = lastInNextLayer->next;
        }
        lastInNextLayer->next = left;
        lastInNextLayer->next->next = right;
    }
}

layer_params *create_params(int n_vertex, int layer_i) {

    layer_params *params = malloc(sizeof(layer_params));
    if (params == NULL) {
        printf("\nl: %d ::: Memory allocation for params struct failed\n", __LINE__);
        return NULL;
    }
    params->layer_i = layer_i;
    params->n_vertex = n_vertex;

    return params;
}

layer_ptr create_layer(list vertices, layer_params *params, layer_ptr prev) {
    layer_ptr layer = malloc(sizeof(layer_object));
    if (layer == NULL) {
        printf("\nl: %d ::: Failed allocate memory for layer\n", __LINE__);
        return NULL;
    }
    layer->params = params;
    layer->vertices = vertices;
    layer->next = NULL;
    layer->prev = prev;
    return layer;
}

void delete_layers_object(layer_ptr layer_first) {
    layer_ptr layer_current = layer_first;
    layer_ptr next_layer;
    while (layer_current != NULL) {

        // Delete vertices list
        deleteList(layer_current->vertices);
        layer_current->vertices = NULL;

        // Delete params
        free(layer_current->params);
        layer_current->params = NULL;

        // Delete layer
        next_layer = layer_current->next;
        free(layer_current);

        layer_current = next_layer;
    }
}

list get_list_element(list l, int j) {
    int i = 0;
    list el = l;
    while (el != NULL) {
        if (i == j) break;
        el = l->next;
        i++;
    }
    return el;
}

int calc_first_v_step_v_l(list v_left, list v_right, list vertex) {
    return v_left->params->step_v_l +
           v_left->params->v_s +
           (v_right->params->step_v_l) / 2 -
           vertex->params->v_s_r;
}

int calc_v_step_v_l(list v_left, list v_right, list v_prev_right, list v_prev, list vertex) {
    return v_prev_right->params->step_v_l / 2 +
           v_prev_right->params->v_s +
           v_left->params->step_v_l +
           v_left->params->v_s +
           v_right->params->step_v_l / 2 -
           v_prev->params->v_s_r -
           vertex->params->v_s_l;
}

int calc_underlines_left(list vertex, list v_next) {
    if(vertex==NULL || v_next==NULL) {
        printf("l: %d ::: int calc_underlines_left(list vertex, list v_next) -> Params must not be NULL!", __LINE__);
        return 0;
    }
    return vertex->params->v_s_r + (v_next->params->step_v_l / 2) - 1;
}

int calc_underlines_right(list vertex) {
    if(vertex==NULL) {
        printf("l: %d ::: int calc_underlines_right(list vertex) -> Params must not be NULL!", __LINE__);
        return 0;
    }
    return vertex->params->v_s_l + (vertex->params->step_v_l / 2) - 1;
}

int calc_edge_margin(list vertex){
    return vertex->params->v_s_l + vertex->params->step_v_l;
}

int isEven(int n){
    if (n&1 == 0){
        return 1;
    }
    return 0;
}

void init_vertices_params(layer_ptr current_layer) {
    int j = 0;
    list vertex = current_layer->vertices;
    while (vertex != NULL) {

        vertex->params->j = j;
        list v_left = get_list_element(current_layer->next->vertices, 2 * j);
        list v_right = get_list_element(current_layer->next->vertices, 2 * j + 1);

        if (j == 0) {
            vertex->params->step_v_l = calc_first_v_step_v_l(v_left, v_right, vertex);
            if(current_layer->params->layer_i!=1) {
                list v_next = get_list_element(current_layer->vertices, j + 1);
                vertex->params->n_u = calc_underlines_left(vertex, v_next);
            }
        } else {

            list v_prev_right = get_list_element(current_layer->next->vertices, 2 * j - 1);
            list v_prev = get_list_element(current_layer->vertices, j - 1);

            vertex->params->step_v_l = calc_v_step_v_l(v_left, v_right, v_prev_right, v_prev, vertex);

            if(isEven(j)){
                list v_next = get_list_element(current_layer->vertices, j+1);
                vertex->params->n_u = calc_underlines_left(vertex, v_next);
            } else {
                vertex->params->n_u = calc_underlines_right(vertex);
            }

        }
        vertex->params->m_edge = calc_edge_margin(vertex);

        vertex = vertex->next;
        j++;
    }
}

layer_ptr init_layers_params(layer_ptr layer_first, int step_v0, int step_T0, int step_val, int n_u0) {

    // Get last layer
    layer_ptr last_layer = layer_first;
    while (last_layer->next != NULL) {
        last_layer = last_layer->next;
    }

    // Set params in last layer
    last_layer->params->step_v = step_v0;
    last_layer->params->step_t = step_T0;
    last_layer->params->step_val = step_val;
    last_layer->params->m_o = step_T0;
    last_layer->params->n_u = n_u0;
    last_layer->params->m_u = step_T0 + 1;

    // Init params of last layer vertices
    list last_layer_vertex = last_layer->vertices;
    int j = 0;
    while (last_layer_vertex != NULL) {
        last_layer_vertex->params->step_v_l = step_v0;
        last_layer_vertex->params->j = j;
        last_layer_vertex = last_layer_vertex->next;
        j++;
    }

    layer_ptr current_layer = last_layer->prev;

    while (current_layer != NULL) {

        // Iterate from back, so take i-1 params from next of the current layer

        // i-1 params
        int step_v_prev = current_layer->next->params->step_v;
        int step_t_prev = current_layer->next->params->step_t;
        int step_val_prev = current_layer->next->params->step_val;
        int m_o_prev = current_layer->next->params->m_o;

        // Step vertex
        current_layer->params->step_v = step_v_prev + step_t_prev + 2 * step_val_prev - 1;

        // Margin outer
        current_layer->params->m_o = step_val_prev + step_v_prev / 2 + m_o_prev;

        // Step trees
        current_layer->params->step_t = current_layer->params->step_v;

        // Number of underlines
        current_layer->params->n_u = current_layer->params->step_v / 2 - 1;

        // Margin of underlines
        current_layer->params->m_u = current_layer->params->m_o + 1;

        // Step value
        current_layer->params->step_val = step_val_prev;

        init_vertices_params(current_layer);

        current_layer = current_layer->prev;
    }

    return last_layer;

}

layer_ptr init_layers(tree t) {

    layer_ptr layer_first = create_layer(create_list_el(t), create_params(1, 1), NULL);

    int h_max = calc_tree_height(t);
    int layer_i = 1;
    layer_ptr c_layer = layer_first;

    // Create layers list with basic params
    for (; layer_i < h_max; layer_i++) {
        // Init next layer
        c_layer->next = create_layer
                (
                        NULL,
                        create_params(c_layer->params->n_vertex * 2, c_layer->params->layer_i + 1),
                        c_layer
                );

        list vertex = c_layer->vertices;

        // Create next layer
        while (vertex != NULL) {
            if (vertex->t_node == NULL) {
                // Emulated node
                append_childs(c_layer, create_list_el(NULL), create_list_el(NULL));
                vertex = vertex->next;
            } else {
                // Real node
                append_childs(c_layer, create_list_el(vertex->t_node->left), create_list_el(vertex->t_node->right));
                vertex = vertex->next;
            }
        }

        c_layer = c_layer->next;
        // c_layer is now last layer
    }

    return layer_first;
}

void visualize_tree(tree t, int step_v0, int step_T0, int step_val, int n_u0) {

    // Init layers_object
    layer_ptr layer_first = init_layers(t);
    layer_ptr layer_last = init_layers_params(layer_first, step_v0, step_T0, step_val, n_u0);

    layer_ptr layer_current = layer_first;

    // Print each layer
    for (; layer_current != NULL; layer_current = layer_current->next) {
        print_layer(layer_current);
    }

    delete_layers_object(layer_first);
    layer_first = NULL;
    layer_last = NULL;
}

int main() {
    int *arr = calloc(sizeof(int), 50);
    tree root = array_to_tree(arr, 50);
    visualize_tree(root, 5, 3, 1, 1);
    deleteTree(root);
    return 0;
}