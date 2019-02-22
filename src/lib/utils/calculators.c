#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "calculators.h"

void _ct_count_vertices(ct_tree t, int *i) {
    if (t == NULL) return;
    *i = *i + 1;
    _ct_count_vertices(t->left, i);
    _ct_count_vertices(t->right, i);
}

int _ct_calc_first_edge_margin(ct_list vertex) {
    return vertex->params->v_s_l + vertex->params->step_v_l;
}

int _ct_calc_edge_margin(ct_list vertex, ct_list v_prev) {
    return vertex->params->v_s_l + vertex->params->step_v_l + v_prev->params->v_s_r;
}

int _ct_calc_underlines_right(ct_list vertex, ct_list v_prev) {
    if (vertex == NULL || v_prev == NULL) {
        printf("l: %d ::: int _ct_calc_underlines_right(ct_list vertex, ct_list v_prev) -> Params must not be NULL!", __LINE__);
        return 0;
    }
    return vertex->params->step_v_l +
           v_prev->params->v_s_r +
           vertex->params->v_s_l -
           v_prev->params->n_u -
           3;

}

int _ct_calc_underlines_left(ct_list vertex, ct_list v_next) {
    if (vertex == NULL || v_next == NULL) {
        printf("l: %d ::: int _ct_calc_underlines_left(ct_list vertex, ct_list v_next) -> Params must not be NULL!", __LINE__);
        return 0;
    }
    return vertex->params->v_s_r + (v_next->params->step_v_l - 1) / 2 - 1;
}

int _ct_calc_v_step_v_l(ct_list v_left, ct_list v_right, ct_list v_prev_right, ct_list v_prev, ct_list vertex) {
    return (v_prev_right->params->step_v_l) / 2 +
           v_prev_right->params->v_s +
           v_left->params->step_v_l +
           v_left->params->v_s +
           (v_right->params->step_v_l - 1) / 2 -
           v_prev->params->v_s_r -
           vertex->params->v_s_l;
}

int _ct_calc_first_v_step_v_l(ct_list v_left, ct_list v_right, ct_list vertex) {
    return v_left->params->step_v_l +
           v_left->params->v_s +
           (v_right->params->step_v_l - 1) / 2 -
           vertex->params->v_s_l;
}
