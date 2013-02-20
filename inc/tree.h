#ifndef TREE_H
#define TREE_H

#include "global.h"

/*
All functions to manipulate trees
*/

int create_initial_conditions(); /*alloc all the pointers required and return 1 if successfull 
								 and -1 if was unable to create inital conditions*/
int install_node_main_tree(char matrix[][COL]); 

#endif