#include <stdlib.h>
#include "../types.h"
#include "calculators.h"

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

void count_vertices(tree t, int *i) {
    if (t == NULL) return;
    *i = *i + 1;
    count_vertices(t->left, i);
    count_vertices(t->right, i);
}
