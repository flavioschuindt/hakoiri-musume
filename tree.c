#include <stdlib.h>
#include <stdio.h>

#include "tree.h"
#include "matrix.h"

int create_initial_conditions()
{
	current_board_config = (main_tree_node*) malloc(sizeof(main_tree_node));
	if (current_board_config != NULL)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void insert_index_tree(struct main_tree_node **head, struct main_tree_node **new_node)
{
     

     if (*head == NULL)
     {
     	 *head = (main_tree_node*)malloc(sizeof(main_tree_node));
         *head = *new_node;
         (*head)->left = NULL;
         (*head)->right = NULL;
     }
     else
     {
         if((*new_node)->hash < (*head)->hash) 
              insert_index_tree(&(*head)->left, new_node);
         else  
              insert_index_tree(&(*head)->right, new_node);
     }
}

struct main_tree_node* binary_search_index_tree(struct main_tree_node **head, int hash)
{
  if (*head == NULL)
  {
    return NULL;
  }
  else
  {

      if ( hash < (*head)->hash) return binary_search_index_tree(&(*head)->left, hash);
      else if (hash > (*head)->hash) return binary_search_index_tree(&(*head)->right, hash);
      else return *head;
  }
}

int create_new_possibility_node(char matrix[][COL], main_tree_node **node_main_tree)
{
	int i;
	int j = 0;
	int k = 0;
	int already_exists = 0;
	int colision = 0;
	struct main_tree_node* found; 

	int  hs = hash(matrix);
	found = binary_search_index_tree(&head, hs);

	if (found != NULL)
	{
		/*check for colision, i.e, the matrix already exists or is a different matrix with the same hash (colision case)?*/
		for (j=0; j<ROW; j++)
		{
			for (k=0; k<COL; k++)
			{
				if (matrix[j][k] != found->matrix[j][k])
				{
					colision = 1;
					break;
				}
			}
		}
		already_exists = colision ? 0 : 1;
	}
	if (!already_exists) 
	{
		/*Install new possibility node*/
		for (i=0; i<8; i++)
		{
			if ((*node_main_tree)->possibilities[i] == NULL) /*Find the next possibility*/
			{
				(*node_main_tree)->possibilities[i] = (main_tree_node*)malloc(sizeof(main_tree_node));
				for (j=0; j<ROW; j++)
				{
					for (k=0; k<COL; k++)
					{
						(*node_main_tree)->possibilities[i]->matrix[j][k] = matrix[j][k];
					}
				}
				(*node_main_tree)->possibilities[i]->hash = hs;
				insert_index_tree(&head, &((*node_main_tree)->possibilities[i]));
				break;
			}
		}
	}	
	return 1;

}