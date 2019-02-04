#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct node *tree;
typedef struct node {
    int value;
    tree left;
    tree right;
} node;

typedef struct list_el *list;
typedef struct list_el {
    tree t_node;
    list next;
} list_el;

typedef struct layers {
    list currentLayer;
    list nextLayer;
} layers;

typedef struct layer_params {
    int step_v;
    int step_t;
    int step_val;
    int m_o;
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
        free(l);
        l = next;
    }
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

void count_vertices(tree t, int *i) {
    if (t == NULL) return;
    *i = *i + 1;
    count_vertices(t->left, i);
    count_vertices(t->right, i);
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

char *build_margin(int margin) {
    char *margin_string = (char *) malloc(sizeof(char) * margin + 1);
    if (margin_string == NULL) {
        printf("\n[l: %d] Memory allocation for margin failed\n", __LINE__);
        return margin_string;
    }
    margin_string[margin] = '\0';
    for (int i = 0; i < margin; i++) {
        margin_string[i] = ' ';
    }
    return margin_string;
}

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


int prom(tree t) {
    tree ct = t;
    int p = 0;
    while (ct != NULL) {
        if (ct->left != NULL) ct = ct->left;
        else ct = ct->right;
        p++;
    }
    return p;
}

int calc_tree_height(tree t) {
    if (t == NULL)
        return 0;
    else {
        int lDepth = calc_tree_height(t->left);
        int rDepth = calc_tree_height(t->right);

        if (lDepth > rDepth)
            return (lDepth + 1);

        else return (rDepth + 1);
    }
}

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

void print_vertex_row(list vertices, struct layer_params *params) {

    // Print outer margin
    print_margin(params->m_o);

    int i = 0;

    // Print vertices values
    for (list vertex = vertices; vertex != NULL; vertex = vertex->next) {

        // Print vertex value
        if (vertex->t_node != NULL) printf("%d", vertex->t_node->value);
        else printf(" ");

        // Print step between vertices or between trees
        if (i) print_margin(params->step_t);
        else print_margin(params->step_v);

        i = !i;
    }
}

void print_edge_x_row(list vertices, struct layer_params *params) {

    // Print margin underlines
    print_margin(params->m_u);

    int isSecond = 0;

    for (list vertex = vertices; vertex != NULL; vertex = vertex->next) {

        if (vertex->t_node != NULL) {
            if(isSecond){
                printf(" \\");
                print_underlines(params->n_u);
            } else {
                print_underlines(params->n_u);
                printf("/");
            }
        }
        if(isSecond) print_margin(params->step_t+2);

        isSecond = !isSecond;

    }


}

void print_edge_y_row(list vertices, struct layer_params *params) {

    // Print outer margin
    print_margin(params->m_o);

    int i = 0;

    // Print |
    for (list vertex = vertices; vertex != NULL; vertex = vertex->next) {

        // Print |
        if (vertex->t_node != NULL) printf("|");
        else printf(" ");

        // Print step between vertices or between trees
        if (i) print_margin(params->step_t);
        else print_margin(params->step_v);

        i = !i;
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
    int *arr = calloc(sizeof(int), 25);

    tree root = array_to_tree(arr, 25);
    visualize_tree(root, 5, 3, 1, 1);
    deleteTree(root);
    return 0;
}