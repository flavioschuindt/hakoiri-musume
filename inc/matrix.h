#ifndef MATRIX_H
#define MATRIX_H

#include "global.h"

/*
All functions to manipulate matrixes
*/

void create_initial_configuration(); /*Create the initial board configuration*/
void print_current_configuration(); /*Print the current board configuration*/
void move(); /*Move to available positions*/
void print_possibilities(); /*Print moving possibilities from current configuration*/

#endif