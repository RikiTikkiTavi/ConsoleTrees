#ifndef CONSOLETREES_TYPES_H
#define CONSOLETREES_TYPES_H

typedef struct ct_node *ct_tree;
typedef struct ct_node {
    void *value_ptr;
    ct_tree left;
    ct_tree right;
} ct_node;

typedef struct vertex_params{
    int step_v_l;
    int v_s;
    int v_s_l;
    int v_s_r;
    int n_u;
    int m_edge;
    int j;
} vertex_params;

typedef struct ct_list_el *ct_list;
typedef struct ct_list_el {
    ct_tree t_node;
    vertex_params *params;
    ct_list next;

} ct_list_el;

typedef struct ct_layer_params {
    int layer_i;
    int n_vertex;
} ct_layer_params;

typedef struct ct_layer_object *ct_layer_ptr;
typedef struct ct_layer_object {
    ct_layer_params *params;
    ct_list vertices;
    ct_layer_ptr next;
    ct_layer_ptr prev;
} ct_layer_object;

#endif //CONSOLETREES_TYPES_H
