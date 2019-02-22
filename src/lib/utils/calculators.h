#include "types.h"

#ifndef CONSOLETREES_CALCULATORS_H
#define CONSOLETREES_CALCULATORS_H

void _ct_count_vertices(ct_tree t, int *i);

int _ct_calc_first_v_step_v_l(ct_list v_left, ct_list v_right, ct_list vertex);

int _ct_calc_v_step_v_l(ct_list v_left, ct_list v_right, ct_list v_prev_right, ct_list v_prev, ct_list vertex);

int _ct_calc_underlines_left(ct_list vertex, ct_list v_next);

int _ct_calc_underlines_right(ct_list vertex, ct_list v_prev);

int _ct_calc_edge_margin(ct_list vertex, ct_list v_prev);

int _ct_calc_first_edge_margin(ct_list vertex);

#endif //CONSOLETREES_CALCULATORS_H
