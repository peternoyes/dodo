#include "game.h"

void fullscreenImage(unsigned char* image) {
	unsigned int i = 0;
	for (; i < 1024; ++i) {
		VIDEO_MEM[i] = image[i];
	}
}

void setTiles(unsigned char* tiles) {
	_tiles = tiles;
}

unsigned char getPixel(unsigned char x, unsigned char y) {
	return (VIDEO_MEM[x + (y/8)*128] >> (y%8)) & 0x1;
}

void drawPlayfield(void) {
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