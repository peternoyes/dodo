#include <stdio.h>
#include <stdlib.h>
#include "led.h"
#include "util.h"
#include "display.h"

#define VIDEO_MEM ((unsigned char *) 0x3c00)

#define _BV(bit) (1 << (bit))

static unsigned char const _tiles[24] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,			// 0
					  		 			  0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA, 0x55, 0xAA,
					  		 			  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };	// 8

static unsigned char const _playfield[128] = { 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
											   8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
										       8, 0, 0, 0, 0, 0, 16, 16, 16, 0, 0, 0, 0, 0, 0, 8,
											   8, 0, 0, 0, 0, 0, 16, 8, 16, 0, 0, 0, 0, 0, 0, 8,
											   8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
											   8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8,
											   8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 
											   8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 };

static unsigned char const _char1[16] = { 0x80, 0x4e, 0xdf, 0x3b, 0x3f, 0xda, 0x40, 0x80, 
										  0x83, 0xf0, 0x0d, 0x04, 0x04, 0x0d, 0xf0, 0x83 };

static unsigned char const _char2[16] = { 0x00, 0x8e, 0x5f, 0xbb, 0x3f, 0xda, 0x40, 0x20, 
										  0x40, 0xe3, 0xb0, 0x0d, 0x18, 0x13, 0x20, 0x30, };

static unsigned char const _char3[16] = { 0x00, 0x8e, 0xdf, 0x3b, 0x3f, 0x5a, 0x00, 0x00, 
										  0x30, 0x10, 0x11, 0x1d, 0x09, 0x15, 0xe1, 0x80 };										 

static unsigned char _char_x = 16;
static unsigned char _char_y = 40;

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

void clearSprite() {
	unsigned char p1 = _char_y/8;
	unsigned char p2 = (_char_y+15)/8;
	unsigned char i1 = _char_x/8;
	unsigned char i2 = (_char_x+7)/8;
	unsigned char p, i, l, o, v = 0;
	unsigned char* vmem = 0;

	for (p = p1; p <= p2; ++p) {
		o = (p * 16) + i1;
		vmem = VIDEO_MEM + (o * 8);
		for (i = i1; i <= i2; ++i) {
			v = _playfield[o];
			l = v + 8;
			for (; v < l; ++v) {
				*vmem = _tiles[v];
				++vmem;
			}
			++o;
		}
	}

}

void drawSprite(unsigned char* sprite) {
	unsigned char p = _char_y/8;
	unsigned char i = 0;

	unsigned char* vmem = VIDEO_MEM; // + _char_x + (p*128);
	for (i = 0; i < p; ++i) {
		vmem += 128;
	}
	vmem += _char_x;
	
	for (i = 0; i < 8; ++i) {
		*vmem = sprite[i];
		vmem++;
	}

	vmem += 120;

	for (i = 8; i < 16; ++i) {
		*vmem |= sprite[i];
		vmem++;
	}
}


int main() {
	unsigned char* sprite = (unsigned char*)_char2;

	drawPlayfield();

	for (;;) {
		drawSprite(sprite);
		display();

		clearSprite();

		_char_x += 3;

		if ((_char_x % 2) == 1) {
			sprite = (unsigned char*)_char3;
		}
		else {
			sprite = (unsigned char*)_char2;
		}

		if (_char_x > 104) {
			_char_x = 16;
		}

		delay_ms(255);

	}

	for (;;) { }

	return 0;
}