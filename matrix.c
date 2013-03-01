#include <stdio.h>

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

	while (k < 8)
	{
		if (current_board_config->possibilities[k]->matrix != NULL)
		{
			print_configuration(current_board_config->possibilities[k]->matrix);
			printf("\n");
		}
		else
		{
			break;
		}
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
	if( ((i-1) >= 0 && (i-1) <= ROW) )
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
	if( ((i+1) >= 0 && (i+1) <= ROW) )
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
		if ( ((empty_space_1.i-1) >=0) && ((empty_space_1.i-1) <= ROW) && ((empty_space_1.i-2) >=0) && ((empty_space_1.i-2) <= ROW)  ) 
		{
			if ( (current_board_config->matrix[empty_space_1.i-1][empty_space_1.j] == 'D' && 
				current_board_config->matrix[empty_space_2.i-1][empty_space_2.j] == 'D') ) //Up?
			{
				/*Move maiden*/
				
				current_board_config->matrix[empty_space_1.i][empty_space_1.j] = 'D';
				current_board_config->matrix[empty_space_2.i][empty_space_2.j] = 'D';
				current_board_config->matrix[empty_space_1.i-2][empty_space_1.j] = ' ';
				current_board_config->matrix[empty_space_2.i-2][empty_space_2.j] = ' ';

				install_node_main_tree(current_board_config->matrix);

				/*Roolback to previous board configuration*/
				current_board_config->matrix[empty_space_1.i-2][empty_space_1.j] = 'D';
				current_board_config->matrix[empty_space_2.i-2][empty_space_2.j] = 'D';
				current_board_config->matrix[empty_space_1.i][empty_space_1.j] = ' ';
				current_board_config->matrix[empty_space_2.i][empty_space_2.j] = ' ';
			}
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
			if (matrix[i][j] == 'D')
			{
				sum += i * j * ANSWER_TO_LIFE_UNIVERSE_AND_EVERYTHING;
			}
			else if (matrix[i][j] == 'I')
			{
				sum += i * j * 2 * ANSWER_TO_LIFE_UNIVERSE_AND_EVERYTHING;
			}
			else
			{
				sum += i * j * 3 * ANSWER_TO_LIFE_UNIVERSE_AND_EVERYTHING;
			}
			
		}

	}

	return sum;

}

void go_to_exit(main_tree_node *start_point)
{
	int i = 0;

	if(start_point != NULL)
	{
		if (start_point->matrix[3][1] == 'D' && start_point->matrix[3][2] == 'D' && 
			start_point->matrix[4][1] == 'D' && start_point->matrix[4][2] == 'D')
		{
			printf("SAIDA!");
		}
		else
		{
			move();
			for (i = 0; i < 8; i++)
			{
				if (current_board_config->possibilities[i]->matrix != NULL)
				{
					current_board_config = current_board_config->possibilities[i];
					//move();
					go_to_exit(current_board_config);
				}
			}
		}
	}
}

