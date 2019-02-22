#include "lib/ConsoleTrees.h"
#include <stdlib.h>
#include <stdio.h>

void ex1(){
    int arr[31];
    ct_tree root = ct_array_to_tree(arr, 31);
    ct_visualize_tree(root, 5, ct_int_to_string);
    ct_delete_tree(root);
}

void ex2(){
    int values[5] = {1,2,3,4,5};
    ct_tree root = ct_create_rightist_tree(values, 5);
    ct_visualize_tree(root, 5, ct_int_to_string);
    ct_delete_tree(root);
}

void ex3(){
    int values[5];
    ct_tree root = ct_create_random_single_child_tree(values, 5);
    ct_visualize_tree(root, 5, ct_int_to_string);
    ct_delete_tree(root);
}

int main() {
    ex1();
    ex2();
    ex3();
    return 0;
}