#include <stdlib.h>
#include <stdio.h>

#include "global.h"
#include "tree.h"
#include "matrix.h"

int main(int argc, char *argv[])
{
	
	if (create_initial_conditions() == -1)
	{
		printf("\nCOULD NOT ALLOCATE MEMORY. EXITING NOW!\n");
		exit(-1);
	}

	create_initial_configuration();
	printf("\n******* CURRENT CONFIGURATION *******\n");
	print_current_configuration();

	return 0;
}