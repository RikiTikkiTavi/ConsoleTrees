#include <stdlib.h>
#include <stdio.h>
#include "calculators.h"
#include "helpers.h"

tree create_node(int value) {
    tree t = (tree) malloc(sizeof(node));
    if (t == NULL) {
        printf("\n[l:18] Memory allocation for node failed\n");
        return t;
    }
    t->value = value;
    return t;
}

list create_list_el(tree t_node) {
    list l = (list) malloc(sizeof(list_el));
    if (l == NULL) {
        printf("\nl: %d ::: Memory allocation for list failed\n", __LINE__);
        return l;
    }
    l->t_node = t_node;
    if (t_node == NULL) {
        l->params = create_vertex_params(1, 0, 0);
    } else {
        int v_s = calc_vertex_size(t_node->value);
        int v_s_l = (v_s - 1) / 2;
        int v_s_r = v_s - v_s_l - 1;
        l->params = create_vertex_params(v_s, v_s_l, v_s_r);
    }

    l->next = NULL;
    return l;
}

void deleteTree(tree t) {
    if (t == NULL) return;
    tree left = t->left;
    tree right = t->right;
    free(t);
    deleteTree(t->left);
    deleteTree(t->right);
}

void deleteList(list l) {
    list next;

    while (l != NULL) {
        next = l->next;
        free(l->params);
        l->params = NULL;
        free(l);
        l = next;
    }
}

vertex_params *create_vertex_params(int v_s, int v_s_l, int v_s_r) {
    vertex_params *params = malloc(sizeof(vertex_params));
    if (params == NULL) {
        printf("\nl: %d ::: Memory allocation for vertex params struct failed\n", __LINE__);
        return NULL;
    }
    params->v_s = v_s;
    params->v_s_l = v_s_l;
    params->v_s_r = v_s_r;

    return params;
}


void create_subtree(tree t, int arr[], int i, int arr_length) {
    if (t == NULL) return;
    int i_left = 2 * i + 1;
    int i_right = 2 * i + 2;
    t->left = i_left < arr_length ? create_node(arr[i_left]) : NULL;
    t->right = i_right < arr_length ? create_node(arr[i_right]) : NULL;

    create_subtree(t->left, arr, i_left, arr_length);
    create_subtree(t->right, arr, i_right, arr_length);
}

tree array_to_tree(int arr[], int arr_length) {
    if (arr_length == 0) return NULL;
    tree root = create_node(arr[0]);
    create_subtree(root, arr, 0, arr_length);
    return root;
}

void add_nodes_to_array(tree t, int arr[], int i) {
    if (t == NULL) return;
    arr[i] = t->value;
    add_nodes_to_array(t->left, arr, 2i + 1);
    add_nodes_to_array(t->right, arr, 2i + 2);
}

int *tree_to_array(tree t, int *arr_length) {
    *arr_length = 0;
    count_vertices(t, arr_length);
    int *arr = (int *) malloc(sizeof(int) * (*arr_length));
    if (arr == NULL) {
        printf("\n[l:66] Memory allocation for tree's array failed\n");
        return arr;
    };
    add_nodes_to_array(t, arr, 0);
    return arr;
}

int calc_vertex_size(int vertex) {
    if (vertex == 0) return 1;
    int size = vertex < 0 ? 1 : 0;
    while (vertex != 0) {
        vertex /= 10;
        size++;
    }
    return size;
}

void log_vertex(list vertex, list v_left, list v_right, list v_prev_right, list v_prev) {
    if (vertex->t_node != NULL)
        printf("Value: %d, Step: %d \n", vertex->t_node->value, vertex->params->step_v_l);
    if (v_left->t_node != NULL)
        printf("Left: %d, Step: %d \n", v_left->t_node->value, v_left->params->step_v_l);
    if (v_right->t_node != NULL)
        printf("Right: %d, Step: %d \n", v_right->t_node->value, v_right->params->step_v_l);
    if (v_prev_right->t_node != NULL)
        printf("Prev right: %d, Step: %d \n", v_prev_right->t_node->value, v_prev_right->params->step_v_l);
    if (v_prev->t_node != NULL)
        printf("Prev: %d, Step: %d \n", v_prev->t_node->value, v_prev->params->step_v_l);
    printf("------\n");
}

int isEven(int n) {
    if (n % 2 == 0) {
        return 1;
    }
    return 0;
}

list get_list_element(list l, int j) {
    int i = 0;
    while (l != NULL) {
        if (i == j) break;
        l = l->next;
        i++;
    }
    return l;
}

void _delete_layers_object(layer_ptr layer_first) {
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

layer_ptr _create_layer(list vertices, layer_params *params, layer_ptr prev) {
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

layer_params *_create_params(int n_vertex, int layer_i) {

    layer_params *params = malloc(sizeof(layer_params));
    if (params == NULL) {
        printf("\nl: %d ::: Memory allocation for params struct failed\n", __LINE__);
        return NULL;
    }
    params->layer_i = layer_i;
    params->n_vertex = n_vertex;

    return params;
}

void _append_childs(layer_ptr c_layer, list left, list right) {
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
