#include <stdlib.h>
#include <stdio.h>
#include "block.h"
#include "container.h"

const container_block con_wall = {PURPLE, '|', '|',  CONK_WALL};
const container_block con_bottom = {PURPLE, '-', '-', CONK_BOTTOM};
const container_block con_roof = {PURPLE, '-', '-', CONK_ROOF};

container_block * container[CONS_Y][CONS_X];

void init_contain(void)
{
	int rows;
	int columns;

	for(columns = CONP_LEFT; columns <= CONP_RIGHT; columns++)
	{
		container[CONP_ROOF][columns] = &con_roof;
		container[CONP_BOTTOM][columns] = &con_bottom;
	}
	for(rows = 0; rows <= CONP_BOTTOM; rows++)
	{
		container[rows][CONP_LEFT] = &con_wall;
		container[rows][CONP_RIGHT] = &con_wall;	
	}
}

int check_line_full(void)
{

//	puts("check");
	int rows;
	int columns;
	int isfull;

	for(rows = CONP_ROOF + 1; rows < CONP_BOTTOM; rows++)
	{	
		isfull = LINE_IS_FULL;
		for(columns = CONP_LEFT + 1; columns < CONP_RIGHT; columns++)
		{
			if(container[rows][columns] == NULL)
			{
				isfull = LINE_NOT_FULL;
				break;
			}
		}
		if(isfull)
			return rows;
	}	
	return 0;
}

void destory_line(int row)
{
//	printf("%d", row);
//	puts("des");
	int rows;
	int columns;
		
	for(rows = row; rows > CONP_ROOF + 1; rows-- )
	{
		if(rows == row)
		{
			for(columns = CONP_LEFT + 1; columns < CONP_RIGHT; columns++)
				free(container[rows][columns]);
		}
		for(columns = CONP_LEFT + 1; columns < CONP_RIGHT; columns++)
		{
			container[rows][columns] = container[rows-1][columns];
		}
	}
}

int container_is_full(void)
{
	int columns;
	int ret = 0;

	for(columns = CONP_LEFT + 1; columns < CONP_RIGHT; columns++)
	{
		if(container[CONP_ROOF + 1][columns] != NULL)
			ret = 1;
	}
	return ret;
}

void destory_all(void)
{
	int rows;
	int columns;
		
	for(rows = CONP_BOTTOM - 1; rows > CONP_ROOF; rows-- )
	{
		for(columns = CONP_LEFT + 1; columns < CONP_RIGHT; columns++)
		{
			free(container[rows][columns]);
			container[rows][columns] = NULL;
		}
	}

}
 
int add_block(int block_color, char block_content_left, char block_content_right, int x, int y)
{
	container_block_p new_block;
	new_block = malloc(sizeof(container_block));
	new_block -> block_color = block_color;
	new_block -> block_content_left = block_content_left;
	new_block -> block_content_right = block_content_right;
	new_block -> block_kind = CONK_BLOCK;
	if(container[y][x] == NULL)
	{
		container[y][x] = new_block;
		return 0;
	}
	free(new_block);
	return -1;
}

void auto_add_block(block *blo)
{
	int rows;
	int columns;
	coor block_coor_con[BLOCK_SIZE*BLOCK_SIZE];
	int block_num = 0;
	int i;

	for(rows = 0; rows < BLOCK_SIZE; rows++)
	{
		for(columns = 0; columns < BLOCK_SIZE; columns++)
		{
			if(IS_BLOCK(blo -> block_info[rows][columns]))
			{
				block_coor_con[block_num].x = columns + blo -> block_x - CENTER;
				block_coor_con[block_num].y = rows    + blo -> block_y - CENTER;
				block_num++;
			}
		}
	}

	for(i = 0; i < block_num; i++)
	{
		add_block(blo -> block_color, '[', ']', block_coor_con[i].x, block_coor_con[i].y);
	}
}














