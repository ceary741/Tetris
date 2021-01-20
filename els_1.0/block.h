#ifndef __BLOCK_H__
#define __BLOCK_H__

//colors
#define RED 41
#define GREEN 42
#define YELLOW 43
#define BLUE 44
#define PURPLE 45
#define COL_NUM 5
#define AUTO_COL  (rand() % COL_NUM + 41)

//flags
#define GET_COL 1
#define GET_INFO 2
#define GET_DIR 4

//info
#define INFO_NUM 7
#define BLOCK_SIZE 5
#define CENTER 2
#define BLOCK 1
#define IS_CENTER(flags) (flags & CENTER)
#define IS_BLOCK(flags) (flags & BLOCK)

//position
#define START_X 6
#define START_Y 3

//direction
#define DIR_NUM 3

//extern int **container_info;
//extern block blo;

typedef struct
{
	int x;
	int y;
}coor;

typedef struct
{

	int block_info[BLOCK_SIZE][BLOCK_SIZE];
	int block_color;
	int block_x;
	int block_y;

} block;

void auto_set_block(block *blo, int flags);

void set_block_info(int **const block_info, block *blo);

void set_block_color(const int block_color, block *blo);

void block_go_left(block *blo);

void block_go_right(block *blo);

void block_go_down(block *blo);

void block_go_bottom(block *blo);

void block_change_direction(block *blo, const int clockwise);

#endif








