#include "types.h"

#ifndef CONSOLETREES_CALCULATORS_H
#define CONSOLETREES_CALCULATORS_H

void _count_vertices(tree t, int *i);

int _calc_first_v_step_v_l(list v_left, list v_right, list vertex);

int _calc_v_step_v_l(list v_left, list v_right, list v_prev_right, list v_prev, list vertex);

int _calc_underlines_left(list vertex, list v_next);

int _calc_underlines_right(list vertex, list v_prev);

int _calc_edge_margin(list vertex, list v_prev);

int _calc_first_edge_margin(list vertex);

#endif //CONSOLETREES_CALCULATORS_H
