#ifndef GLOBAL_H
#define GLOBAL_H
/*
This header contains all the new type definitions and global variables
*/

#define ROW 5
#define COL 4

 /* struct that represents the index tree */
typedef struct index_tree_node
{
	struct index_tree_node* left;
	struct index_tree_node* right;
	int hash;
}index_tree_node;

/* Main tree struct */
typedef struct main_tree_node
{
	char matrix[ROW][COL];
	struct main_tree_node* possibilities[8];
	int hs_table[8];
}main_tree_node;

/*struct that represents a point in the board*/
typedef struct point
{
	int i;
	int j;
}point;

main_tree_node *current_board_config;
index_tree_node *head;

#endif
