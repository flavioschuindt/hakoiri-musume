#include <stdio.h>
#include <string.h>

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
	current_board_config->hash = hash(current_board_config->matrix);
	insert_index_tree(&head, &(current_board_config));

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

void check_possible_enemy_movements(point empty_space, main_tree_node **node_main_tree)
{
	char matrix[ROW][COL];
	int i = empty_space.i;
	int j = empty_space.j;

	if ( ((j-1) >= 0 && (j-1) <= COL))
	{
		if ((*node_main_tree)->matrix[i][j-1] == 'I') /* Is the left neighbor from an empty space an enemy (I)?*/
		{
			/*Move enemy*/
			
			/*(*node_main_tree)->matrix[i][j] = 'I';
			(*node_main_tree)->matrix[i][j-1] = ' ';
			create_new_possibility_node((*node_main_tree)->matrix);*/

			/*Roolback to previous board configuration*/
			/*(*node_main_tree)->matrix[i][j] = ' ';
			(*node_main_tree)->matrix[i][j-1] = 'I';*/
			memcpy(matrix,(*node_main_tree)->matrix, ROW*COL*sizeof(char));
			matrix[i][j] = 'I';
			matrix[i][j-1] = ' ';
			create_new_possibility_node(matrix, node_main_tree);

		}
	}
	if( ((j+1) >= 0 && (j+1) <= COL) )
	{	
		if ((*node_main_tree)->matrix[i][j+1] == 'I') /* Is the right neighbor from an empty space an enemy (I)?*/
		{
			/*Move enemy*/
			/*(*node_main_tree)->matrix[i][j] = 'I';
			(*node_main_tree)->matrix[i][j+1] = ' ';
			create_new_possibility_node((*node_main_tree)->matrix);*/

			/*Roolback to previous board configuration*/
			/*(*node_main_tree)->matrix[i][j] = ' ';
			(*node_main_tree)->matrix[i][j+1] = 'I';*/
			memcpy(matrix,(*node_main_tree)->matrix, ROW*COL*sizeof(char));
			matrix[i][j] = 'I';
			matrix[i][j+1] = ' ';
			create_new_possibility_node(matrix, node_main_tree);

		}
	}
	if( ((i-1) >= 0 && (i-1) <= ROW) )
	{
		if ((*node_main_tree)->matrix[i-1][j] == 'I') /* Is the upstairs neighbor from an empty space an enemy (I)?*/
		{
			/*Move enemy*/
			/*(*node_main_tree)->matrix[i][j] = 'I';
			(*node_main_tree)->matrix[i-1][j] = ' ';
			create_new_possibility_node((*node_main_tree)->matrix);*/

			/*Roolback to previous board configuration*/
			/*(*node_main_tree)->matrix[i][j] = ' ';
			(*node_main_tree)->matrix[i-1][j] = 'I';*/
			memcpy(matrix,(*node_main_tree)->matrix, ROW*COL*sizeof(char));
			matrix[i][j] = 'I';
			matrix[i-1][j] = ' ';
			create_new_possibility_node(matrix, node_main_tree);
		}
	}
	if( ((i+1) >= 0 && (i+1) <= ROW) )
	{
		if ((*node_main_tree)->matrix[i+1][j] == 'I') /* Is the downstairs neighbor from an empty space an enemy (I)?*/
		{
			/*Move enemy*/
			/*(*node_main_tree)->matrix[i][j] = 'I';
			(*node_main_tree)->matrix[i+1][j] = ' ';
			create_new_possibility_node((*node_main_tree)->matrix);*/

			/*Roolback to previous board configuration*/
			/*(*node_main_tree)->matrix[i][j] = ' ';
			(*node_main_tree)->matrix[i+1][j] = 'I';*/
			memcpy(matrix,(*node_main_tree)->matrix, ROW*COL*sizeof(char));
			matrix[i][j] = 'I';
			matrix[i+1][j] = ' ';
			create_new_possibility_node(matrix, node_main_tree);
		}
	}
}

void check_possible_maiden_movements(point empty_space_1, point empty_space_2, main_tree_node **node_main_tree)
{

	char matrix[ROW][COL];

	if ( empty_space_1.i == empty_space_2.i) /*Two horizontal points*/
	{
		/* check if the maiden is up or down*/
		if ( ((empty_space_1.i-1) >=0) && ((empty_space_1.i-1) <= ROW) && ((empty_space_1.i-2) >=0) && ((empty_space_1.i-2) <= ROW)  ) 
		{
			if ( ((*node_main_tree)->matrix[empty_space_1.i-1][empty_space_1.j] == 'D' && 
				(*node_main_tree)->matrix[empty_space_2.i-1][empty_space_2.j] == 'D') ) //Up?
			{
				/*Move maiden*/
				
				/*(*node_main_tree)->matrix[empty_space_1.i][empty_space_1.j] = 'D';
				(*node_main_tree)->matrix[empty_space_2.i][empty_space_2.j] = 'D';
				(*node_main_tree)->matrix[empty_space_1.i-2][empty_space_1.j] = ' ';
				(*node_main_tree)->matrix[empty_space_2.i-2][empty_space_2.j] = ' ';

				create_new_possibility_node((*node_main_tree)->matrix);*/

				/*Roolback to previous board configuration*/
				/*(*node_main_tree)->matrix[empty_space_1.i-2][empty_space_1.j] = 'D';
				(*node_main_tree)->matrix[empty_space_2.i-2][empty_space_2.j] = 'D';
				(*node_main_tree)->matrix[empty_space_1.i][empty_space_1.j] = ' ';
				(*node_main_tree)->matrix[empty_space_2.i][empty_space_2.j] = ' ';*/

				memcpy(matrix,(*node_main_tree)->matrix, ROW*COL*sizeof(char));
				matrix[empty_space_1.i][empty_space_1.j] = 'D';
				matrix[empty_space_2.i][empty_space_2.j] = 'D';
				matrix[empty_space_1.i-2][empty_space_1.j] = ' ';
				matrix[empty_space_2.i-2][empty_space_2.j] = ' ';
				create_new_possibility_node(matrix, node_main_tree);
			}
		}
	}
}

void move(main_tree_node **node_main_tree)
{

	int i = 0;
	int j = 0;

	for (i=0; i<ROW; i++)
	{
		for (j=0; j<COL; j++)
		{
			/*Check enemy movements*/
			if ((*node_main_tree)->matrix[i][j] == ' ') 
			{
				point empty_space;
				empty_space.i = i;
				empty_space.j = j;
				check_possible_enemy_movements(empty_space, node_main_tree);
			}
			
			/*check maiden movements*/

			point empty_space_1, empty_space_2;
			
			if ( ((*node_main_tree)->matrix[i][j] == ' ' && (*node_main_tree)->matrix[i][j+1] == ' ') )
			{
				empty_space_1.i = i;
				empty_space_1.j = j;
				empty_space_2.i = i;
				empty_space_2.j = j+1;
				check_possible_maiden_movements(empty_space_1, empty_space_2, node_main_tree);
			}

			if ( ((*node_main_tree)->matrix[i][j] == ' ' && (*node_main_tree)->matrix[i][j-1] == ' ') )
			{
				empty_space_1.i = i;
				empty_space_1.j = j;
				empty_space_2.i = i;
				empty_space_2.j = j-1;
				check_possible_maiden_movements(empty_space_1, empty_space_2, node_main_tree);
			}

			if ( ((*node_main_tree)->matrix[i][j] == ' ' && (*node_main_tree)->matrix[i-1][j] == ' ') )
			{
				empty_space_1.i = i;
				empty_space_1.j = j;
				empty_space_2.i = i-1;
				empty_space_2.j = j;
				check_possible_maiden_movements(empty_space_1, empty_space_2, node_main_tree);
			}

			if ( ((*node_main_tree)->matrix[i][j] == ' ' && (*node_main_tree)->matrix[i+1][j] == ' ') )
			{
				empty_space_1.i = i;
				empty_space_1.j = j;
				empty_space_2.i = i+1;
				empty_space_2.j = j;
				check_possible_maiden_movements(empty_space_1, empty_space_2, node_main_tree);
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

void go_to_exit(main_tree_node **start_point)
{
	int i = 0;

	int teste = 0;

	if(*start_point != NULL)
	{
		if ((*start_point)->matrix[3][1] == 'D' && (*start_point)->matrix[3][2] == 'D' && 
			(*start_point)->matrix[4][1] == 'D' && (*start_point)->matrix[4][2] == 'D')
		{
			printf("SAIDA!");
			return;
		}
		else
		{
			move(start_point);
			/*printf("\n\nPRINTANDO AS POSSBILIDADES DO NOVO NO CALCULADO\n\n");
			for (i = 0; i < 8; i++)
			{
				if ((*start_point)->possibilities[i]->matrix != NULL)
				{
					print_configuration((*start_point)->possibilities[i]->matrix);
					printf("\n");
				}
			}
			printf("\n\nFIM DAS POSSIBILIDADES DO NO\n\n");*/
			for (i = 0; i < 8; i++)
			{
				if ((*start_point)->possibilities[i]->matrix != NULL)
				{
					//current_board_config = current_board_config->possibilities[i];
					/*print_configuration((*start_point)->possibilities[i]->matrix);
					printf("\n");
					teste = getchar();*/
					go_to_exit(&((*start_point)->possibilities[i]));
				}
			}
		}
	}
}

