#ifndef __GAME_H__
#define __GAME_H__

//extern container_block con_wall;
//extern container_block con_bottom;
//extern container_block con_roof;


extern container_block * container[CONS_Y][CONS_X];

void gamewhile(int s);

void gameover(int s);

int is_against(block *blo);

void contral(char ctrl);

#endif
