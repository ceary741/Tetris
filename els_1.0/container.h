#ifndef __CONTAINER_H__
#define __CONTAINER_H__

//container block kinds
#define CONK_WALL 0
#define CONK_BOTTOM 1
#define CONK_ROOF 2
#define CONK_BLOCK 3

//container size
#define CONS_X 12
#define CONS_Y 26

//position
#define CONP_BOTTOM 25
#define CONP_ROOF 4
#define CONP_LEFT 0
#define CONP_RIGHT 11

//
#define LINE_IS_FULL 1
#define LINE_NOT_FULL 0


typedef struct
{
	int block_color;
	char block_content_left;
	char block_content_right;
	int block_kind;

}container_block, *container_block_p;

void init_contain(void);

int check_line_full(void);

void destory_line(int row);

int container_is_full(void);

void destory_all(void);

int add_block(int block_color, char block_content_left, char block_content_right, int x, int y);

void auto_add_block(block *blo);
#endif


