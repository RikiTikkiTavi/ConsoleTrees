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

typedef enum layer_types {
    vertex,
    edge_x,
    edge_y
} layer_types;

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
        printf("\n[l:36] Memory allocation for list failed\n");
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
    int ileft = 2 * i + 1;
    int iright = 2 * i + 2;
    t->left = ileft < arr_length ? create_node(arr[ileft]) : NULL;
    t->right = iright < arr_length ? create_node(arr[iright]) : NULL;

    if (i + 1 < arr_length)
        create_subtree(t->left, arr, i + 1, arr_length);
    if (i + 2 < arr_length)
        create_subtree(t->right, arr, i + 2, arr_length);
    else
        return;
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
        printf("\n[l:79] Memory allocation for margin failed\n");
        return margin_string;
    }
    margin_string[margin] = '\0';
    for (int i = 0; i < margin; i++) {
        margin_string[i] = ' ';
    }
    return margin_string;
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

void append_childs(layers *c_layers, list left, list right) {
    if (c_layers->nextLayer == NULL) {
        c_layers->nextLayer = left;
        c_layers->nextLayer->next = right;
    } else {
        list lastInNextLayer = c_layers->nextLayer;
        while (lastInNextLayer->next != NULL) {
            lastInNextLayer = lastInNextLayer->next;
        }
        lastInNextLayer->next = left;
        lastInNextLayer->next->next = right;
    }
}

void print_vertex_layer(layers *c_layer, int m_o, int m_i, int m_v, int layer_length) {
    char *m_i_string = build_margin(2 * m_i);
    char *m_o_string = build_margin(m_o);
    char *m_v_string = build_margin(m_v);
    list c_n = c_layer->currentLayer;
    printf("m_i: %d;", m_i);
    printf("%s", m_o_string);
    for (int i = 1; i <= layer_length; i++) {
        if (c_n->t_node != NULL)
            printf("%d", c_n->t_node->value);
        else {
            printf(" ");
        }
        if (i * 2 == layer_length)
            printf("%s", m_i_string);
        else {
            printf("%s", m_v_string);
        }
        c_n = c_n->next;
    }
    printf("\n");

    free(m_i_string);
    free(m_o_string);
    free(m_v_string);
}

void print_layer(layers *c_layer, layer_types layer_type, int m_o, int m_i, int m_v, int layer_length) {
    switch (layer_type) {
        case vertex:
            print_vertex_layer(c_layer, m_o, m_i, m_v, layer_length);
            break;
        case edge_x:
            break; // TODO;
        case edge_y:
            break; // TODO;
    }
}


void visualize_tree(tree t) {
    if (t == NULL) {
        printf("\n Tree is empty! \n");
        return;
    }
    /*
     * 1) Calc max height: max_h
     * 2) Calc inner margin: m_i = 3*max_h
     * 3) Calc outer margin: m_o = 2*m_i
     * 4) Visualize each row using linked list
     * */
    int layer = 0;
    int max_h = calc_tree_height(t);
    int m_i = 3 * max_h;
    int m_o = 2 * m_i;
    int m_v = 5;

    // Init list with root
    list layer_list_first = create_list_el(t);

    // Init layers
    layers c_layer;
    c_layer.currentLayer = layer_list_first;
    c_layer.nextLayer = NULL;

    int layer_length = 1;
    int have_real_node = 1;

    while (have_real_node) {
        list l_c = c_layer.currentLayer;
        have_real_node = 0;

        // Create next layer
        while (l_c != NULL) {
            if (l_c->t_node == NULL) {
                // Emulated node
                append_childs(&c_layer, create_list_el(NULL), create_list_el(NULL));
                l_c = l_c->next;
            } else {
                // Real node
                append_childs(&c_layer, create_list_el(l_c->t_node->left), create_list_el(l_c->t_node->right));
                l_c = l_c->next;
                have_real_node = 1;
            }
        }

        // Print current layer
        print_layer(&c_layer, vertex, m_o, m_i, m_v, layer_length);

        // Count layer params
        layer_length *= 2;
        m_o -= 3;
        m_i -= 3;

        // Free currentLayer
        deleteList(c_layer.currentLayer);

        // Set nextLayer as currentLayer
        c_layer.currentLayer = c_layer.nextLayer;
        c_layer.nextLayer = NULL;
    }
    deleteList(c_layer.currentLayer);
    c_layer.currentLayer = NULL;
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};

    tree root = array_to_tree(arr, 5);
    visualize_tree(root);
    deleteTree(root);

    return 0;
}