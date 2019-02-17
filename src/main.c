#include "lib/ConsoleTrees.h"

int main() {
    int arr[30];
    tree root = array_to_tree(arr, 30);
    visualize_tree(root, 5);
    deleteTree(root);
    return 0;
}