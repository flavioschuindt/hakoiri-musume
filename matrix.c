#include "matrix.h"

#include <stdio.h>

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

