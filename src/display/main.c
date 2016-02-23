#include <stdio.h>
#include <stdlib.h>
#include "led.h"
#include "util.h"
#include "display.h"

#define VIDEO_MEM ((unsigned char *) 0x3c00)

#define _BV(bit) (1 << (bit))

unsigned char* _scratch;

void setPixel(unsigned char x, unsigned char y, unsigned char c) {
	if (c == 1) 
    	_scratch[x+ (y/8)*128] |= _BV((y%8));  
  	else
    	_scratch[x+ (y/8)*128] &= ~_BV((y%8));
}

unsigned char getPixel(unsigned char x, unsigned char y) {
	return (VIDEO_MEM[x + (y/8)*128] >> (y%8)) & 0x1;
}

void copyScratch() {
	unsigned int i = 0;
	for (i = 0; i < 1024; ++i) {
		VIDEO_MEM[i] = _scratch[i];
	}
}

int main() {

	unsigned char x, y, xt, yt, c, col, n, x_min, x_plus, y_min, y_plus = 0;

	_scratch = malloc(1024);

	led_on();

	for (x = 0; x < 128; ++x) {
		for (y = 0; y < 8; ++y) {
			VIDEO_MEM[x + (y * 128)] = 0x00;
			_scratch[x + (y * 128)] = 0x00;
		}
	}

	setPixel(64, 31, 1);
	setPixel(65, 31, 1);
	setPixel(63, 32, 1);
	setPixel(64, 32, 1);
	setPixel(64, 33, 1);

	copyScratch();
	display();

	for (;;) {
		led_off();
		for (x = 1; x < 127; ++x) {
			for (y = 1; y < 63; ++y) {
				x_min = x - 1;
				x_plus = x + 1;
				y_min = y - 1;
				y_plus = y + 1;

				n = getPixel(x_min, y_min) + getPixel(x_min, y) + getPixel(x_min, y_plus) +
					getPixel(x, y_min) + getPixel(x, y_plus) + 
					getPixel(x_plus, y_min) + getPixel(x_plus, y) + getPixel(x_plus, y_plus);

				c = getPixel(x, y);
				if (c == 1 && n != 2 && n != 3) {
					setPixel(x, y, 0);
				}
				else if (c == 0 && n == 3) {
					setPixel(x, y, 1);
				}							
			}
		} 
		led_on();
		copyScratch();
		display();
	}

	return 0;
}