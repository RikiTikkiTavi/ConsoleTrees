#ifndef CONSOLETREES_TYPES_H
#define CONSOLETREES_TYPES_H

typedef struct node *tree;
typedef struct node {
    int value;
    tree left;
    tree right;
} node;

typedef struct vertex_params{
    int step_v_l;
    int v_s;
    int v_s_l;
    int v_s_r;
    int n_u;
    int m_edge;
    int j;
} vertex_params;

typedef struct list_el *list;
typedef struct list_el {
    tree t_node;
    vertex_params *params;
    list next;

} list_el;

typedef struct layer_params {
    int step_v;
    int step_t;
    int step_val;
    int m_o; // Outer margin
    int n_u; // Quantity of underlines
    int m_u; // Margin of underlines
    int layer_i;
    int n_vertex;
} layer_params;

typedef enum row_types {
    VERTEX,
    EDGE_X,
    EDGE_Y
} row_types;

typedef struct layer_object *layer_ptr;
typedef struct layer_object {
    layer_params *params;
    list vertices;
    layer_ptr next;
    layer_ptr prev;
} layer_object;

#endif //CONSOLETREES_TYPES_H
