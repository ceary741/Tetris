#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>

#include "block.h"
#include "container.h"
#include "painter.h"
#include "game.h"


struct termios* old;
block blo;

int main(void)
{
	char ctrl;
	init_contain();
	old = init_screen();
	struct itimerval itv;
	auto_set_block(&blo, GET_COL|GET_INFO|GET_DIR);
	paint_block(&blo);
	paint_contain();
		
	
	signal(SIGALRM, gamewhile);
	signal(SIGINT, gameover);

	itv.it_interval.tv_sec = 0;
	itv.it_interval.tv_usec = 500000;
	itv.it_value.tv_sec = 0;
	itv.it_value.tv_usec = 500000;
	setitimer(ITIMER_REAL, &itv, NULL);
	
	while(1)
	{
		ctrl = getchar();
		contral(ctrl);
	}
	getchar();
	exit(0);

}


void gamewhile(int s)
{
	int rows = 0;
	blo.block_y++;
	if(is_against(&blo))
	{	
		blo.block_y--;
		auto_add_block(&blo);
		while(1)
		{
			rows = check_line_full();
			if(rows == 0)
				break;
			destory_line(rows);
		}
		if(container_is_full())
			gameover(1);
		auto_set_block(&blo, GET_COL|GET_INFO|GET_DIR);
	}
	clear_screen();
	paint_block(&blo);
	paint_contain();

}

void gameover(int s)
{
	re_screen(old);	
	destory_all();
	signal(SIGALRM, NULL);
	exit(0);
}

int is_against(block *blo)
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
				block_coor_con[block_num].x = blo -> block_x + columns - CENTER;
				if(block_coor_con[block_num].x < 0 || block_coor_con[block_num].x > CONP_RIGHT)
					return 1;
				block_coor_con[block_num].y = blo -> block_y + rows - CENTER;
				if(block_coor_con[block_num].y < 0 || block_coor_con[block_num].y > CONP_BOTTOM)
					return 1;
				block_num++;
			}
		}
	}
	
	for(i = 0; i < block_num; i++)
	{
		if(container[block_coor_con[i].y][block_coor_con[i].x] != NULL && container[block_coor_con[i].y][block_coor_con[i].x] -> block_kind != CONK_ROOF)
			return 1;
	}
	return 0;
}

void contral(char ctrl)
{
	switch (ctrl)
	{
		case 'a':
			blo.block_x --;
			if(is_against(&blo))
			{
				blo.block_x++;
				break;
			}
			clear_screen();
			paint_block(&blo);
			paint_contain();
			break;
		case 'd':
			blo.block_x ++;
			if(is_against(&blo))
			{
				blo.block_x--;
				break;
			}
			clear_screen();
			paint_block(&blo);
			paint_contain();
			break;
		case 's':
			blo.block_y ++;
			if(is_against(&blo))
			{
				blo.block_y--;
				break;
			}
			clear_screen();
			paint_block(&blo);
			paint_contain();
			break;
		case 'f':
			block_change_direction(&blo, 0);
			if(is_against(&blo))
			{
				block_change_direction(&blo, 2);
				break;
			}
			clear_screen();
			paint_block(&blo);
			paint_contain();
			break;
		case 'q':
			gameover(1);
			break;	
	}

}









