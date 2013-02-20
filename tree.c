#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "matrix.h"

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

int install_node_main_tree(char matrix[][COL])
{
	int i;
	int j = 0;
	int k = 0;
	int already_exists = 0;
	int colision = 0;

	int  hs = hash(matrix);

	for (i=0; i<8; i++)
	{
		if (current_board_config->hs_table[i] == hs)
		{
			/*check for colision, i.e, the matrix already exists or is a different matrix with the same hash (colision case)?*/
			for (j=0; j<ROW; j++)
			{
				if (colision) break;

				for (k=0; k<COL; k++)
				{
					if (matrix[j][k] != current_board_config->possibilities[i]->matrix[j][k])
					{
						colision = 1;
						break;
					}
				}

			}
			if (!colision)
			{
				already_exists = 1;
			}
		}
	}

	if (!already_exists)
	{

		for (i=0; i<8; i++)
		{
			if (current_board_config->possibilities[i] == NULL) /*Find the next possibility*/
			{
				current_board_config->possibilities[i] = (main_tree_node*)malloc(sizeof(main_tree_node));
				for (j=0; j<ROW; j++)
				{
					for (k=0; k<COL; k++)
					{
						current_board_config->possibilities[i]->matrix[j][k] = matrix[j][k];
					}
				}
				current_board_config->hs_table[i] = hs;
				break;
			}
		}
	}

	return 1;

}