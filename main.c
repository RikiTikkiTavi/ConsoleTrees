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
    int value;
    int isEmpty;
    list next;
    list prev;
} list_el;

typedef struct layers {
    list current;
    list next;
} layers;

const int INITIAL_MARGIN = 10;
char MARGIN_UNIT[] = " ";

tree create_node(int value) {
    tree t = (tree) malloc(sizeof(node));
    if (t == NULL) {
        printf("\n[l:18] Memory allocation for node failed\n");
        return t;
    }
    t->value = value;
    return t;
}

list create_list_el(int value, int isEmpty) {
    list l = (list) malloc(sizeof(list_el));
    if (l == NULL) {
        printf("\n[l:36] Memory allocation for list failed\n");
        return l;
    }
    l->value = value;
    l->isEmpty = isEmpty;
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

    while (l!=NULL) {
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

void handle_array_add(int value, int arr[], int i) {

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

void append_empty_childs(layers *c_layers){
    if(c_layers->next == NULL) {
        c_layers->next = create_list_el(0, 1);
        c_layers->next->next = create_list_el(0, 1);
    } else {
        c_layers->next->next = create_list_el(0, 1);
        c_layers->next->next = create_list_el(0, 1);
    }
}

void append_childs(layers *c_layers, )


void visualize_tree(tree t) {
    if(t==NULL){
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

    // Init list with root
    list layer_list_first = create_list_el(t->value, 0);

    // Init layers
    layers c_layer;
    c_layer.current = layer_list_first;


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while(1){
        list l_c = layer_list_first;
        while(l_c != NULL) {
            if(l_c->isEmpty){
                printf(" e ");
                append_empty_childs(&c_layer);
                l_c = l_c -> next;
            } else {
                printf(" %d ", l_c -> value);
                l_c = l_c -> next;
            }
        }
    }
#pragma clang diagnostic pop

}

int main() {
    int arr[7] = {1, 2, 3, 4, 5, 6, 7};
    tree root = array_to_tree(arr, 7);
    visualize_tree(root);
    deleteTree(root);
    return 0;
}