#include <stdio.h>
#include <stdlib.h>
#include "led.h"
#include "util.h"
#include "display.h"

#define VIDEO_MEM ((unsigned char *) 0x3c00)

#define _BV(bit) (1 << (bit))

static unsigned char const _tiles[16] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,			// 0
					  		 			  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA };	// 8

static unsigned char const _playfield[128] = { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
											   8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
										       8, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 8,
											   8, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 8,
											   8, 0, 0, 0, 0, 0, 8, 8, 8, 0, 0, 0, 0, 0, 0, 8,
											   8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
											   8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 
											   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };

void setPixel(unsigned char x, unsigned char y, unsigned char c) {
	if (c == 1) 
    	VIDEO_MEM[x + (y/8)*128] |= _BV((y%8));  
  	else
    	VIDEO_MEM[x + (y/8)*128] &= ~_BV((y%8));
}

unsigned char getPixel(unsigned char x, unsigned char y) {
	return (VIDEO_MEM[x + (y/8)*128] >> (y%8)) & 0x1;
}

void drawPlayfield() {
	unsigned char i, p, l = 0;
	unsigned char* vmem = VIDEO_MEM;
	
	for (i = 0; i < 128; ++i) {
		p = _playfield[i];
		l = p + 8;
		for (; p < l; ++p) {
			*vmem = _tiles[p];
			vmem++;
		}
	}
}

int main() {
	drawPlayfield();
	display();

	for (;;) { }

	return 0;
}