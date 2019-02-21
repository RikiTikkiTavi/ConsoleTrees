#include "lib/ConsoleTrees.h"

int main() {

    int arr[31];
    tree root = array_to_tree(arr, 31);
    visualize_tree(root, 5);
    delete_tree(root);

    tree root_one = create_node(1);
    root_one->right = create_node(2);
    root_one->right->right = create_node(3);
    root_one->right->right->right = create_node(4);
    root_one->right->right->right->right = create_node(5);
    visualize_tree(root_one, 5);
    delete_tree(root_one);

    return 0;
}