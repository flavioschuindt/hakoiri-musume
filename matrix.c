#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "tree.h"

void create_initial_configuration()
{
	int i = 0;
	int j = 0;

	for (i=0; i<ROW; i++)
	{
		for (j=0; j<COL; j++)
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
	current_board_config->matrix[2][1] = ' ';
	current_board_config->matrix[2][2] = ' ';

}

void print_configuration(char matrix[][COL])
{

	int i = 0;
	int j = 0;

	for (i=0; i<ROW; i++)
	{
		for (j=0; j<COL; j++)
		{
			j != 3 ? printf("%c", matrix[i][j]) : printf("%c\n", matrix[i][j]);
		}

	}

}

void print_possibilities()
{

	int k = 0;

	while (current_board_config->possibilities[k] != NULL)
	{
		print_configuration(current_board_config->possibilities[k]->matrix);
		printf("\n");
		k++;
	}
}

void check_possible_enemy_movements(point empty_space)
{
	int i = empty_space.i;
	int j = empty_space.j;

	if ( ((j-1) >= 0 && (j-1) <= COL))
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
	}
	if( ((j+1) >= 0 && (j+1) <= COL) )
	{
		if (current_board_config->matrix[i][j+1] == 'I') /* Is the right neighbor from an empty space an enemy (I)?*/
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
	if( ((i-1) >= 0 && (i-1) <= COL) )
	{
		if (current_board_config->matrix[i-1][j] == 'I') /* Is the upstairs neighbor from an empty space an enemy (I)?*/
		{
			/*Move enemy*/
			current_board_config->matrix[i][j] = 'I';
			current_board_config->matrix[i-1][j] = ' ';
			install_node_main_tree(current_board_config->matrix);

			/*Roolback to previous board configuration*/
			current_board_config->matrix[i][j] = ' ';
			current_board_config->matrix[i-1][j] = 'I';
		}
	}
	if( ((i+1) >= 0 && (i+1) <= COL) )
	{
		if (current_board_config->matrix[i+1][j] == 'I') /* Is the downstairs neighbor from an empty space an enemy (I)?*/
		{
			/*Move enemy*/
			current_board_config->matrix[i][j] = 'I';
			current_board_config->matrix[i+1][j] = ' ';
			install_node_main_tree(current_board_config->matrix);

			/*Roolback to previous board configuration*/
			current_board_config->matrix[i][j] = ' ';
			current_board_config->matrix[i+1][j] = 'I';
		}
	}
}

void check_possible_maiden_movements(point empty_space_1, point empty_space_2)
{

	if ( empty_space_1.i == empty_space_2.i) /*Two horizontal points*/
	{
		/* check if the maiden is up or down*/
		if ( (current_board_config->matrix[empty_space_1.i-1][empty_space_1.j] == 'D' && 
			current_board_config->matrix[empty_space_2.i-1][empty_space_2.j] == 'D') ) //Up?
		{
			/*Move maiden*/
			
			current_board_config->matrix[empty_space_1.i-1][empty_space_1.j] = ' ';
			current_board_config->matrix[empty_space_2.i-1][empty_space_2.j] = ' ';
			current_board_config->matrix[empty_space_1.i][empty_space_1.j] = 'D';
			current_board_config->matrix[empty_space_2.i][empty_space_2.j] = 'D';

			install_node_main_tree(current_board_config->matrix);

			/*Roolback to previous board configuration*/
			current_board_config->matrix[empty_space_1.i-1][empty_space_1.j] = 'D';
			current_board_config->matrix[empty_space_2.i-1][empty_space_2.j] = 'D';
			current_board_config->matrix[empty_space_1.i][empty_space_1.j] = ' ';
			current_board_config->matrix[empty_space_2.i][empty_space_2.j] = ' ';
		}
	}
}

void move()
{

	int i = 0;
	int j = 0;

	for (i=0; i<ROW; i++)
	{
		for (j=0; j<COL; j++)
		{
			/*Check enemy movements*/
			if (current_board_config->matrix[i][j] == ' ') 
			{
				point empty_space;
				empty_space.i = i;
				empty_space.j = j;
				check_possible_enemy_movements(empty_space);
			}
			
			/*check maiden movements*/

			point empty_space_1, empty_space_2;
			
			if ( (current_board_config->matrix[i][j] == ' ' && current_board_config->matrix[i][j+1] == ' ') )
			{
				empty_space_1.i = i;
				empty_space_1.j = j;
				empty_space_2.i = i;
				empty_space_2.j = j+1;
				check_possible_maiden_movements(empty_space_1, empty_space_2);
			}

			if ( (current_board_config->matrix[i][j] == ' ' && current_board_config->matrix[i][j-1] == ' ') )
			{
				empty_space_1.i = i;
				empty_space_1.j = j;
				empty_space_2.i = i;
				empty_space_2.j = j-1;
				check_possible_maiden_movements(empty_space_1, empty_space_2);
			}

			if ( (current_board_config->matrix[i][j] == ' ' && current_board_config->matrix[i-1][j] == ' ') )
			{
				empty_space_1.i = i;
				empty_space_1.j = j;
				empty_space_2.i = i-1;
				empty_space_2.j = j;
				check_possible_maiden_movements(empty_space_1, empty_space_2);
			}

			if ( (current_board_config->matrix[i][j] == ' ' && current_board_config->matrix[i+1][j] == ' ') )
			{
				empty_space_1.i = i;
				empty_space_1.j = j;
				empty_space_2.i = i+1;
				empty_space_2.j = j;
				check_possible_maiden_movements(empty_space_1, empty_space_2);
			}

		}

	}

}

int hash(char matrix[][COL])
{
	int i=0;
	int j=0;
	int sum=0;

	for (i=0; i<ROW; i++)
	{
		for (j=0; j<COL; j++)
		{
			sum+=atoi(&matrix[i][j]);
		}

	}

	return sum;

}

