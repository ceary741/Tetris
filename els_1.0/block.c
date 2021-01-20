#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "block.h"

const int info_all[INFO_NUM][BLOCK_SIZE][BLOCK_SIZE] = 
{

	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{1, 1, 3, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 1, 0, 0, 0},
		{0, 1, 3, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 3, 0, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 3, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 3, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 3, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
	},
	{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 3, 0, 0},
		{0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0}
	},

};

void auto_set_block(block *blo, int flags)
{
	blo -> block_x = START_X;
	blo -> block_y = START_Y;
	
	if(flags & GET_COL)
	{
		srand(time(NULL));	
		blo -> block_color = AUTO_COL;
	}

	if(flags & GET_INFO)
	{
		set_block_info(NULL, blo);
		
		if(flags & GET_DIR)
		{
			block_change_direction(blo, rand() % DIR_NUM + 1);
		}

	}
		
}

void set_block_info(int **const block_info, block *blo)
{
	int rows;
	int columns;
	int kind = rand() % INFO_NUM;
	if(block_info == NULL)
	{
		for(rows = 0; rows < BLOCK_SIZE; rows++)
		{
			for(columns = 0; columns < BLOCK_SIZE; columns++)
			{
				blo -> block_info[rows][columns] = info_all[kind][rows][columns]; 
			}
		}
	}
	else
	{
		for(rows = 0; rows < BLOCK_SIZE; rows++)
		{
			for(columns = 0; columns < BLOCK_SIZE; columns++)
			{
				blo -> block_info[rows][columns] = block_info[rows][columns]; 
			}
		}
	}
}


void block_change_direction(block *blo, const int clockwise)
{
	block blo_cpy;
	int rows;
	int columns;
	int times;

	blo_cpy.block_x = blo -> block_x;
	blo_cpy.block_y = blo -> block_y;
	
	for(times = 0; times < clockwise % 3 + 1; times++)
	{
		for(rows = 0; rows < BLOCK_SIZE; rows++)
		{
			for(columns = 0; columns < BLOCK_SIZE; columns++)
				blo_cpy.block_info[rows][columns] = 0;
		}
		for(rows = 0; rows < BLOCK_SIZE; rows++)
		{
			for(columns = 0; columns < BLOCK_SIZE; columns++)
			{
				if(IS_BLOCK(blo -> block_info[rows][columns]))			
					blo_cpy.block_info[BLOCK_SIZE - 1 - columns][rows] |= BLOCK; 
			}
		}
		for(rows = 0; rows < BLOCK_SIZE; rows++)
		{
			for(columns = 0; columns < BLOCK_SIZE; columns++)
			{
				blo -> block_info[rows][columns] = blo_cpy.block_info[rows][columns]; 
			}
		}
		
	}
}







