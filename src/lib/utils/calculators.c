#include <stdlib.h>
#include <stdio.h>
#include "types.h"
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

int _calc_first_edge_margin(list vertex) {
    return vertex->params->v_s_l + vertex->params->step_v_l;
}

int _calc_edge_margin(list vertex, list v_prev) {
    return vertex->params->v_s_l + vertex->params->step_v_l + v_prev->params->v_s_r;
}

int _calc_underlines_right(list vertex, list v_prev) {
    if (vertex == NULL || v_prev == NULL) {
        printf("l: %d ::: int _calc_underlines_right(list vertex, list v_prev) -> Params must not be NULL!", __LINE__);
        return 0;
    }
    return vertex->params->step_v_l +
           v_prev->params->v_s_r +
           vertex->params->v_s_l -
           v_prev->params->n_u -
           3;

}

int _calc_underlines_left(list vertex, list v_next) {
    if (vertex == NULL || v_next == NULL) {
        printf("l: %d ::: int _calc_underlines_left(list vertex, list v_next) -> Params must not be NULL!", __LINE__);
        return 0;
    }
    return vertex->params->v_s_r + (v_next->params->step_v_l - 1) / 2 - 1;
}

int _calc_v_step_v_l(list v_left, list v_right, list v_prev_right, list v_prev, list vertex) {
    return (v_prev_right->params->step_v_l) / 2 +
           v_prev_right->params->v_s +
           v_left->params->step_v_l +
           v_left->params->v_s +
           (v_right->params->step_v_l - 1) / 2 -
           v_prev->params->v_s_r -
           vertex->params->v_s_l;
}

int _calc_first_v_step_v_l(list v_left, list v_right, list vertex) {
    return v_left->params->step_v_l +
           v_left->params->v_s +
           (v_right->params->step_v_l - 1) / 2 -
           vertex->params->v_s_l;
}
