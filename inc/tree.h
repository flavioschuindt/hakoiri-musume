#ifndef TREE_H
#define TREE_H

#include "global.h"

/*
All functions to manipulate trees
*/

int create_initial_conditions(); /*alloc all the pointers required and return 1 if successfull 
								 and -1 if was unable to create inital conditions*/
int create_new_possibility_node(char matrix[][COL], main_tree_node **node_main_tree); 
void insert_index_tree(struct main_tree_node **head, struct main_tree_node **new_node);
struct main_tree_node* binary_search_index_tree(struct main_tree_node **head, int hash);

#endif