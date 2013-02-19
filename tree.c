#include <stdlib.h>
#include <stdio.h>
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

int install_node_main_tree(char matrix[][4])
{
	int i;
	int j = 0;
	int k = 0;

	for (i=0; i<8; i++)
	{
		if (current_board_config->possibilities[i] == NULL) /*Find the next possibility*/
		{
			current_board_config->possibilities[i] = (main_tree_node*)malloc(sizeof(main_tree_node));
			printf("\n\n\n\n");
			for (j=0; j<5; j++)
			{
				for (k=0; k<4; k++)
				{
					current_board_config->possibilities[i]->matrix[j][k] = matrix[j][k];
				}
			}
			break;
		}
	}

	return 1;

}