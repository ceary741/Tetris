#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "block.h"
#include "container.h"
#include "painter.h"


void paint_block(block *blo)
{
	int rows;
	int columns;
	coor block_coor_scr[BLOCK_SIZE*BLOCK_SIZE];
	int block_num = 0;
	int i;
	char prt[256];

	for(rows = 0; rows < BLOCK_SIZE; rows++)
	{
		for(columns = 0; columns < BLOCK_SIZE; columns++)
		{
			if(IS_BLOCK(blo -> block_info[rows][columns]))
			{
				block_coor_scr[block_num].x = CONP_IN_SCR_X + columns + blo -> block_x - CENTER;
				block_coor_scr[block_num].y = CONP_IN_SCR_Y + rows    + blo -> block_y - CENTER;
				block_num++;
			}
		}
	}

	for(i = 0; i < block_num; i++)
	{
		sprintf(prt, "\033[%d;%dH\033[%dm[]\033[0m", block_coor_scr[i].y, block_coor_scr[i].x * 2, blo -> block_color);
		printf(prt);
	}
}

void paint_contain(void)
{
	char prt[512];
	int rows;
	int columns;
	for(rows = 4; rows < CONS_Y; rows++)
	{
		for(columns = 0; columns < CONS_X; columns++)
		{
			if(container[rows][columns] == NULL)
				continue;
			sprintf(prt, "\033[%d;%dH\033[%dm%c%c\033[0m", CONP_IN_SCR_Y + rows, (CONP_IN_SCR_X + columns)*2, container[rows][columns] -> block_color, container[rows][columns] -> block_content_left, container[rows][columns] -> block_content_right);
			printf(prt);
		}
	}		
	fflush(stdout);
}

struct termios* init_screen(void)
{
	struct termios new;
	struct termios *old;
	
	tcgetattr(0, &new);
	old = malloc(sizeof(struct termios));
	tcgetattr(0, old);
	new.c_lflag = new.c_lflag & ~(ICANON | ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &new);
	printf("\033[?25l");
	clear_screen();
	return old;
}

void clear_screen(void)
{
	printf("\033[2J");
}

void re_screen(struct termios* old)
{
	tcsetattr(0, TCSANOW, old);
	free(old);
	printf("\033[?25h");
	printf("\nGAME OVER!\n");
}






















