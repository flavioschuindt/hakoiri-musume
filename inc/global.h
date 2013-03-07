#ifndef GLOBAL_H
#define GLOBAL_H
/*
This header contains all the new type definitions and global variables
*/

#define ROW 5
#define COL 4
#define MATRIX_LEN ROW*COL+1

/* Main tree struct */
typedef struct main_tree_node
{
	char matrix[ROW][COL];
	struct main_tree_node* left; /*binary search*/
	struct main_tree_node* right; /*binary search*/
	int hash; /*binary search*/
	struct main_tree_node* possibilities[8];
}main_tree_node;

/*struct that represents a point in the board*/
typedef struct point
{
	int i;
	int j;
}point;

/*struct that represents a node in the path to the exit*/
typedef struct path_linked_list
{
	struct main_tree_node* board_config;
	struct path_linked_list* next;
	struct path_linked_list* previous;
}path_linked_list;

main_tree_node *current_board_config;
main_tree_node *head; /*binary search*/

path_linked_list *last;
path_linked_list *first;

int num_step;

#endif
