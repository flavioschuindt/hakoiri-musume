#ifndef GLOBAL_H
#define GLOBAL_H
/*
This header contains all the new type definitions and global variables
*/

#define ROW 5
#define COL 4

#define ANSWER_TO_LIFE_UNIVERSE_AND_EVERYTHING 42

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

main_tree_node *current_board_config;
main_tree_node *head; /*binary search*/

#endif
