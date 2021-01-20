#ifndef __PAINTER_H__
#define __PAINTER_H__

#define CONP_IN_SCR_X 9
#define CONP_IN_SCR_Y 5

extern container_block * container[CONS_Y][CONS_X];


void paint_block(block *blo);

void paint_contain(void);

void clear_screen(void);

struct termios* init_screen(void);

void re_screen(struct termios* old);

#endif
