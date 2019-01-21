#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct node *tree;
typedef struct node {
    int value;
    tree left;
    tree right;
} node;

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

void create_subtree(tree t, int arr[], int i, int arr_length) {
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
    if (arr_length < 1) return NULL;
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

void visualize_tree(int arr[], int arr_length) {
    int i = 0;
    while (i < arr_length) {
        if (i == 0) {
            printf("%s", build_margin(arr_length));
            printf("%d", arr[i]);
            i++;
        } else {
            int i_end = 2*i;
            printf("%s", build_margin(arr_length-i_end));
            while((i <= i_end) && (i<arr_length)) {
                printf("%d%s", arr[i], build_margin(3));
                i++;
            }
        }
        printf("\n");
    }
}

int main() {
    int arr[14] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    visualize_tree(arr, 14);
    return 0;
}