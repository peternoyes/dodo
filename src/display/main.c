#include <stdio.h>
#include <stdlib.h>
#include "led.h"
#include "util.h"
#include "display.h"

#define VIDEO_MEM ((unsigned char *) 0x3c00)

int main() {

	unsigned char x, y, c = 0;
	unsigned char col = 0;

	led_on();

	for (x = 0; x < 128; ++x) {
		for (y = 0; y < 8; ++y) {
			VIDEO_MEM[x + (y * 128)] = 0x00;
		}
	}

	for (y = 0; y < 8; ++y) {
		VIDEO_MEM[(y * 128)] = 0xFF;
	}

	display();
	
	for (;;) {		
		for (y = 0; y < 8; ++y) {
			VIDEO_MEM[col + (y * 128)] = 0x00;
		}

		++col;
		if (col == 128) {
			col = 0;
		}	

		for (y = 0; y < 8; ++y) {
			VIDEO_MEM[col + (y * 128)] = 0xFF;
		}

		display();			
	}

	return 0;
}