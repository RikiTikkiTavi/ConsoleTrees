#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "calculators.h"
#include "helpers.h"

ct_tree ct_create_node(void *value_ptr) {
    ct_tree t = (ct_tree) malloc(sizeof(ct_node));
    if (t == NULL) {
        printf("\n[l:18] Memory allocation for ct_node failed\n");
        return t;
    }
    t->value_ptr = value_ptr;
    t->left = NULL;
    t->right = NULL;
    return t;
}

ct_list _ct_create_list_el(ct_tree t_node, char *val_to_string(void *val)) {
    ct_list l = (ct_list) malloc(sizeof(ct_list_el));
    if (l == NULL) {
        printf("\nl: %d ::: Memory allocation for ct_list failed\n", __LINE__);
        return l;
    }
    l->t_node = t_node;
    if (t_node == NULL) {
        l->params = _ct_create_vertex_params(1, 0, 0);
    } else {
        int v_s = _ct_calc_vertex_size(t_node->value_ptr, val_to_string);
        int v_s_l = (v_s - 1) / 2;
        int v_s_r = v_s - v_s_l - 1;
        l->params = _ct_create_vertex_params(v_s, v_s_l, v_s_r);
    }

    l->next = NULL;
    return l;
}

void ct_delete_tree(ct_tree t) {
    if (t == NULL) {
        return;
    };
    ct_tree left = t->left;
    ct_tree right = t->right;
    free(t);
    t->left = NULL;
    t->right = NULL;
    t = NULL;
    ct_delete_tree(left);
    ct_delete_tree(right);
}

void _ct_delete_list(ct_list l) {
    if (l == NULL) {
        printf("\nl: %d ::: Error in _ct_delete_list(ct_list l) ::: ct_list l must not be NULL\n", __LINE__);
    }
    ct_list next;

    while (l != NULL) {
        next = l->next;
        free(l->params);
        l->params = NULL;
        free(l);
        l = next;
    }
}

vertex_params *_ct_create_vertex_params(int v_s, int v_s_l, int v_s_r) {
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


void _ct_create_subtree(ct_tree t, int *arr, int i, int arr_length) {
    if (t == NULL) return;
    int i_left = 2 * i + 1;
    int i_right = 2 * i + 2;
    t->left = i_left < arr_length ? ct_create_node(&(arr[i_left])) : NULL;
    t->right = i_right < arr_length ? ct_create_node(&(arr[i_right])) : NULL;

    _ct_create_subtree(t->left, arr, i_left, arr_length);
    _ct_create_subtree(t->right, arr, i_right, arr_length);
}

ct_tree ct_array_to_tree(int *arr, int arr_length) {
    if (arr == NULL) {
        printf("\nl: %d ::: Error in ct_array_to_tree(int arr[], int arr_length) ::: arr must not be NULL\n", __LINE__);
        return NULL;
    }
    if (arr_length == 0) return NULL;
    ct_tree root = ct_create_node(&(arr[0]));
    _ct_create_subtree(root, arr, 0, arr_length);
    return root;
}

int _ct_calc_vertex_size(void *val, char *val_to_string(void *val)) {
    if (val == NULL) {
        printf("\nl: %d ::: _ct_calc_vertex_size(void *val, char *val_to_string(void *val)) value_ptr is NULL", __LINE__);
    }
    char* str_buffer = val_to_string(val);
    int str_length = (int) strlen(str_buffer);
    free(str_buffer);
    return str_length;
}

void _log_vertex(ct_list vertex, ct_list v_left, ct_list v_right, ct_list v_prev_right, ct_list v_prev) {
    if (vertex->t_node != NULL)
        printf("Value: %d, Step: %d \n", vertex->t_node->value_ptr, vertex->params->step_v_l);
    if (v_left->t_node != NULL)
        printf("Left: %d, Step: %d \n", v_left->t_node->value_ptr, v_left->params->step_v_l);
    if (v_right->t_node != NULL)
        printf("Right: %d, Step: %d \n", v_right->t_node->value_ptr, v_right->params->step_v_l);
    if (v_prev_right->t_node != NULL)
        printf("Prev right: %d, Step: %d \n", v_prev_right->t_node->value_ptr, v_prev_right->params->step_v_l);
    if (v_prev->t_node != NULL)
        printf("Prev: %d, Step: %d \n", v_prev->t_node->value_ptr, v_prev->params->step_v_l);
    printf("------\n");
}

int _ct_isEven(int n) {
    if (n % 2 == 0) {
        return 1;
    }
    return 0;
}

ct_list _ct_get_list_element(ct_list l, int j) {
    int i = 0;
    while (l != NULL) {
        if (i == j) break;
        l = l->next;
        i++;
    }
    return l;
}

void _ct_delete_layers_object(ct_layer_ptr layer_first) {
    ct_layer_ptr layer_current = layer_first;
    ct_layer_ptr next_layer;
    while (layer_current != NULL) {

        // Delete vertices ct_list
        _ct_delete_list(layer_current->vertices);
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

ct_layer_ptr _ct_create_layer(ct_list vertices, ct_layer_params *params, ct_layer_ptr prev) {
    ct_layer_ptr layer = malloc(sizeof(ct_layer_object));
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

ct_layer_params *_ct_create_params(int n_vertex, int layer_i) {

    ct_layer_params *params = malloc(sizeof(ct_layer_params));
    if (params == NULL) {
        printf("\nl: %d ::: Memory allocation for params struct failed\n", __LINE__);
        return NULL;
    }
    params->layer_i = layer_i;
    params->n_vertex = n_vertex;

    return params;
}

void _ct_append_childs(ct_layer_ptr c_layer, ct_list left, ct_list right) {
    if (c_layer->next->vertices == NULL) {
        c_layer->next->vertices = left;
        c_layer->next->vertices->next = right;
    } else {
        ct_list lastInNextLayer = c_layer->next->vertices;
        while (lastInNextLayer->next != NULL) {
            lastInNextLayer = lastInNextLayer->next;
        }
        lastInNextLayer->next = left;
        lastInNextLayer->next->next = right;
    }
}

char *ct_int_to_string(void *val) {
    if(val==NULL){
        printf("\nl: %d ::: Error in ct_int_to_string(void *val) ::: val is NULL\n", __LINE__);
        char *str_buffer = calloc(1, 15);
        sprintf(str_buffer, "%d", 0);
        return str_buffer;
    }
    char *str_buffer = calloc(1, 15);
    sprintf(str_buffer, "%d", (*(int *) val));
    return str_buffer;
}
