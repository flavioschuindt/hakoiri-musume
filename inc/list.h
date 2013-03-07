#ifndef LIST_H
#define LIST_H

#include "global.h"

/*
All functions to manipulate Lists
*/

void insert_config_on_path(path_linked_list **first, path_linked_list **last, path_linked_list **new_node);
void remove_last_config_on_path(path_linked_list **last);
void print_full_path_to_exit(path_linked_list **last);

#endif