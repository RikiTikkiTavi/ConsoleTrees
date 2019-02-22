//
// Created by egor on 2/17/19.
//

#ifndef CONSOLETREES_TREE_METHODS_H
#define CONSOLETREES_TREE_METHODS_H

#include "../utils/types.h"

/**
 * @description Calculates tree height
 * @param t Pointer on tree
 * @return integer tree height
 */
int ct_calc_tree_height(ct_tree t);

ct_tree ct_create_rightist_tree(int values[], int values_q);

ct_tree ct_create_random_single_child_tree(int values[], int values_q);

#endif //CONSOLETREES_TREE_METHODS_H
