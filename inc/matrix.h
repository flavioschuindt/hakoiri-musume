#ifndef MATRIX_H
#define MATRIX_H

#include "global.h"

/*
All functions to manipulate matrixes
*/

void create_initial_configuration(); /*Create the initial board configuration*/
void print_configuration(char matrix[][COL]); /*Print a board configuration*/
void move(main_tree_node **node_main_tree); /*Move to available positions*/
void print_possibilities(); /*Print moving possibilities from current configuration*/
void check_possible_enemy_movements(point empty_space, main_tree_node **node_main_tree); /*check all the enemy movements on the board from current configuration*/
void check_possible_maiden_movements(point empty_space_1, point empty_space_2, main_tree_node **node_main_tree); /*check all the maiden movements on the board from current configuration*/
void go_to_exit(main_tree_node **start_point); /*Go to exit*/

int hash(char matrix[][COL]); /*calculate the matrix hash*/ 
unsigned int fnv_hash (const char *s); /*hash function*/

#endif