#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "tree.h"

void create_initial_configuration()
{
	int i = 0;
	int j = 0;

	for (i=0; i<5; i++)
	{
		for (j=0; j<4; j++)
		{
			if ( (i == 0 && (j == 1 || j == 2)) || (i == 1 && (j == 1 || j == 2))  )
			{
				current_board_config->matrix[i][j] = 'D'; // The maiden
			}
			else if ( (i == 4 && (j == 1 || j == 2)) )
			{
				current_board_config->matrix[i][j] = ' '; // Empty space
			}
			else
			{
				current_board_config->matrix[i][j] = 'I'; // Enemy
			}
		}
	}

}

void print_current_configuration()
{

	int i = 0;
	int j = 0;

	for (i=0; i<5; i++)
	{
		for (j=0; j<4; j++)
		{
			j != 3 ? printf("%c", current_board_config->matrix[i][j]) : printf("%c\n", current_board_config->matrix[i][j]);
		}

	}

}

void print_possibilities()
{

	int k = 0;

	main_tree_node *current = current_board_config;

	while (current_board_config->possibilities[k] != NULL)
	{
		current_board_config = current_board_config->possibilities[k];
		print_current_configuration();
		k++;
	}

	current_board_config = current;
	current = NULL;
	free(current);
}

void move()
{
	int i = 0;
	int j = 0;
	for (i=0; i<5; i++)
	{
		for (j=0; j<4; j++)
		{
			if (current_board_config->matrix[i][j] == ' ')
			{
				if (current_board_config->matrix[i][j-1] == 'I') /* Is the left neighbor from an empty space an enemy (I)?*/
				{
					/*Move enemy*/
					current_board_config->matrix[i][j] = 'I';
					current_board_config->matrix[i][j-1] = ' ';
					install_node_main_tree(current_board_config->matrix);

					/*Roolback to previous board configuration*/
					current_board_config->matrix[i][j] = ' ';
					current_board_config->matrix[i][j-1] = 'I';

				}
				if(current_board_config->matrix[i][j+1] == 'I') /* Is the right neighbor from an empty space an enemy (I)?*/
				{
					/*Move enemy*/
					current_board_config->matrix[i][j] = 'I';
					current_board_config->matrix[i][j+1] = ' ';
					install_node_main_tree(current_board_config->matrix);

					/*Roolback to previous board configuration*/
					current_board_config->matrix[i][j] = ' ';
					current_board_config->matrix[i][j+1] = 'I';
				}
			}
		}

	}

}

