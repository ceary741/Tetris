#include <stdio.h>
#include <stdlib.h>
#include "block.h"
#include "painter.h"

int **container_info = NULL;
int **p = NULL;
int main(void)
{
	block blo;
	auto_set_block(&blo, GET_COL|GET_INFO|GET_DIR);
	printf("%d    %d    %d\n", blo.block_color, blo.block_x, blo.block_y);

	blo.block_x++;
	printf("%d    %d    %d\n", blo.block_color, blo.block_x, blo.block_y);
	blo.block_y++;
	printf("%d    %d    %d\n", blo.block_color, blo.block_x, blo.block_y);
	blo.block_x--;
	printf("%d    %d    %d\n", blo.block_color, blo.block_x, blo.block_y);
	block_change_direction(&blo, 1);
	printf("%d    %d    %d\n", blo.block_color, blo.block_x, blo.block_y);
	paint_block(&blo);	
	return 0;

}
