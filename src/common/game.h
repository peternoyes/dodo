#ifndef __GAME_H
#define __GAME_H

#include <stdio.h>
#include <stdlib.h>

#define VIDEO_MEM ((unsigned char *) 0x3c00)
#define _BV(bit) (1 << (bit))
#define SWAP(a, b) { unsigned char t = a; a = b; b = t;}


static unsigned char const _playfield[128] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static unsigned char* _tiles = 0;


void fullscreenImage(unsigned char* image);
void setTiles(unsigned char* tiles);
void setPixel(unsigned char x, unsigned char y, unsigned char c);
unsigned char getPixel(unsigned char x, unsigned char y);
void drawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char c);
void drawPlayfield(void);
void clearSprite(unsigned char x, unsigned char y, unsigned char w, unsigned char h);
void drawSprite(unsigned char* sprite, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char flip);

#endif											   