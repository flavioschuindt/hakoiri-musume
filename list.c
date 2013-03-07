#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "matrix.h"

void insert_config_on_path(path_linked_list **first, path_linked_list **last, path_linked_list **new_node)
{
	if (*first == NULL && *last == NULL)
	{
		*last = (path_linked_list*)malloc(sizeof(path_linked_list));
	    *last = *new_node;
	    *first = *new_node;
	    (*last)->next = NULL;
	    (*last)->previous = NULL;
	}
	else
	{
		(*new_node)->previous = (*last);
		(*new_node)->next = NULL;
		(*last)->next = *new_node;
		*last = *new_node;
	    
	}

}

void remove_last_config_on_path(path_linked_list **last)
{
	if (*last != NULL)
	{
		path_linked_list* previous;
		previous = (*last)->previous;
		if (previous != NULL) 
		{
			previous->next = NULL;
			free(*last);
			*last = previous;
		}
		else
		{
			free(*last);
			*last = NULL;
		}
	}	
}

void print_full_path_to_exit(path_linked_list **first)
{
	path_linked_list* p;
	p = *first;
	while (p != NULL)
	{
		print_configuration(p->board_config->matrix);
		printf("\n");
		p = p->next;
	}
}