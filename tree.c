#include <stdlib.h>
#include "tree.h"

int create_initial_conditions()
{

	head = (index_tree_node*) malloc(sizeof(index_tree_node));
	current_board_config = (main_tree_node*) malloc(sizeof(main_tree_node));

	if (head != NULL && current_board_config != NULL)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}