#include "lib/ConsoleTrees.h"
#include <stdlib.h>
#include <stdio.h>

int main() {

    for (int i = 0; i < 5; i++) {
        int *arr = calloc(sizeof(int), 31);
        tree root = array_to_tree(arr, 31);
        visualize_tree(root, 5, int_to_string);
        delete_tree(root);
        free(arr);
    }

    for (int i = 0; i<2; i++){
        tree root_one = create_node(1);
        root_one->right = create_node(2);
        root_one->right->right = create_node(3);
        root_one->right->right->right = create_node(4);
        root_one->right->right->right->right = create_node(5);
        visualize_tree(root_one, 5, int_to_string);;
        delete_tree(root_one);
    }

    return 0;
}