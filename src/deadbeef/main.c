#include <stdio.h>
#include <stdlib.h>
#include "../common/io.h"
#include "../common/util.h"
#include "../common/display.h"

#define VIDEO_MEM ((unsigned char *) 0x3c00)

#define _BV(bit) (1 << (bit))

#define SWAP(a, b) { unsigned char t = a; a = b; b = t;}

#define NORMAL 0
#define ABDUCTING 1
#define FALLING 2
#define LEFT 3
#define RIGHT  4

static unsigned char const _tiles[8] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

static unsigned char const _playfield[128] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static unsigned char const _saucer[16] = { 0x20, 0x70, 0x50, 0x78, 0x58, 0x78, 0xde, 0xf3, 0xf3, 0xde, 0x78, 0x58, 0x78, 0x50, 0x70, 0x20  };
static unsigned char const _cow[48] = { 0x00, 0x80, 0x70, 0xf8, 0x38, 0x18, 0xf8, 0xf8, 0x18, 0x18, 0x38, 0x70, 0xf0, 0x70, 0x20, 0xe6, 0xfe, 0xdc, 0xf4, 0x80, 0xf4, 0xdc, 0xfe, 0x06, 0x0c, 0x03, 0x00, 0xff, 0xfe, 0x0c, 0x1d, 0x0f, 0x1f, 0x07, 0x06, 0x06, 0x07, 0x06, 0xfc, 0xfc, 0x07, 0x07, 0x0d, 0x0f, 0x0d, 0x07, 0x07, 0x00 };
static unsigned char const _abduction1[48] = { 0x00, 0x00, 0xe0, 0xf0, 0x38, 0x1c, 0xfe, 0xfe, 0x1e, 0x1e, 0x3c, 0x78, 0xf8, 0x70, 0x20, 0xcc, 0xfc, 0xb8, 0xe8, 0x00, 0xe8, 0xb8, 0xfc, 0x0c, 0x00, 0x0c, 0x03, 0x7f, 0x7e, 0x0c, 0x1d, 0x0f, 0x1f, 0x07, 0x02, 0x02, 0x03, 0x06, 0x7c, 0x79, 0x07, 0x0f, 0x1b, 0x1f, 0x1b, 0x0f, 0x07, 0x00 };
static unsigned char const _abduction2[48] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0x3c, 0x1e, 0xff, 0xff, 0x1e, 0x98, 0x70, 0x20, 0xcc, 0xfc, 0xb8, 0xe0, 0xb8, 0xfc, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x3f, 0x3e, 0x0c, 0x1d, 0x0f, 0x07, 0x03, 0x06, 0x3c, 0x39, 0x07, 0x0f, 0x1b, 0x0f, 0x03, 0x00, 0x00, 0x00 };
static unsigned char const _abduction3[48] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xfc, 0x3e, 0x1f, 0xfe, 0x38, 0xec, 0xb8, 0xe0, 0xb8, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3f, 0x0e, 0x0c, 0x0d, 0x0c, 0x38, 0x0f, 0x1b, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static unsigned char const _abduction4[48] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0x1c, 0x76, 0x5c, 0xf0, 0x5c, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x0f, 0x06, 0x04, 0x07, 0x0d, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static unsigned char const _abduction5[48] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xcc, 0x3a, 0xac, 0xf8, 0xac, 0x3a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x03, 0x03, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static unsigned char const _abduction6[48] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x35, 0x5f, 0x35, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

static unsigned char const _walk1[48] = { 0x00, 0x80, 0x70, 0xf8, 0x38, 0x18, 0xf8, 0xf8, 0x18, 0x18, 0x38, 0x70, 0xf0, 0x70, 0x20, 0xe6, 0xfe, 0xdc, 0xf4, 0x80, 0xf4, 0xdc, 0xfe, 0x06, 0x0c, 0x03, 0x00, 0xff, 0xfe, 0x0c, 0x1d, 0x0f, 0x1f, 0x07, 0x06, 0x06, 0x07, 0xc6, 0xfc, 0x1c, 0x1f, 0x77, 0x6d, 0x0f, 0x0d, 0x07, 0x07, 0x00 };
static unsigned char const _walk2[48] = { 0x00, 0x80, 0x70, 0xf8, 0x38, 0x18, 0xf8, 0xf8, 0x18, 0x18, 0x38, 0x70, 0xf0, 0x70, 0x20, 0xe6, 0xfe, 0xdc, 0xf4, 0x80, 0xf4, 0xdc, 0xfe, 0x06, 0x0c, 0x03, 0xc0, 0xff, 0x3e, 0x1c, 0x7d, 0x6f, 0x1f, 0x07, 0x06, 0x06, 0x67, 0x66, 0x3c, 0xfc, 0xff, 0x07, 0x0d, 0x0f, 0x0d, 0x07, 0x07, 0x00 }; 
static unsigned char const _walk3[48] = { 0x00, 0x80, 0x70, 0xf8, 0x38, 0x18, 0xf8, 0xf8, 0x18, 0x18, 0x38, 0x70, 0xf0, 0x70, 0x20, 0xe6, 0xfe, 0xdc, 0xf4, 0x80, 0xf4, 0xdc, 0xfe, 0x06, 0x0c, 0x03, 0x60, 0x7f, 0x1e, 0xfc, 0xfd, 0x0f, 0x1f, 0x07, 0x06, 0x06, 0x07, 0x06, 0xfc, 0xfc, 0x07, 0x07, 0x0d, 0x0f, 0x0d, 0x07, 0x07, 0x00 };

static unsigned char _saucer_x = 56;	// (128 - 16) / 2
static unsigned char _saucer_y = 0;

static unsigned char _cow_x = 52;
static unsigned char _cow_y = 48;

static unsigned char _cowState = NORMAL;

void setPixel(unsigned char x, unsigned char y, unsigned char c) {
	if (c == 1) 
    	VIDEO_MEM[x + (y/8)*128] |= _BV((y%8));  
  	else
    	VIDEO_MEM[x + (y/8)*128] &= ~_BV((y%8));
}

unsigned char getPixel(unsigned char x, unsigned char y) {
	return (VIDEO_MEM[x + (y/8)*128] >> (y%8)) & 0x1;
}

void drawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char c) {
	unsigned char dx, dy;
	signed char ystep;
	int err;
	unsigned char steep = abs((signed char)y1-(signed char)y0) > abs((signed char)x1-(signed char)x0);
	
	if (steep) {
		SWAP(x0, y0);
		SWAP(x1, y1);
	}

	if (x0 > x1) {
		SWAP(x0, x1);
		SWAP(y0, y1);
	}

	dx = x1-x0;
	dy = (unsigned char)abs((signed char)y1-(signed char)y0);

	err = dx/2;

	if (y0 < y1) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x0<=x1; ++x0) {
		if (steep) {
			setPixel(y0, x0, c);
		} else {
			setPixel(x0, y0, c);
		}

		err -= dy;
		if (err < 0) {
			y0 += ystep;
			err += dx;
		}
	}
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

void clearSprite(unsigned char x, unsigned char y, unsigned char w, unsigned char h) {
	unsigned char p1 = y/8;
	unsigned char p2 = (y+h-1)/8;
	unsigned char i1 = x/8;
	unsigned char i2 = (x+w-1)/8;
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

void drawSprite(unsigned char* sprite, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char flip) {
	unsigned char p = y/8;
	unsigned char yoff = y%8;
	unsigned char yoff_inv = 8-yoff;
	unsigned char i = 0;
	unsigned char il = 0;
	unsigned char yp = 0;
	unsigned char last = 0;

	unsigned char* vmem = VIDEO_MEM; // + _char_x + (p*128);
	for (i = 0; i < p; ++i) {
		vmem += 128;
	}
	vmem += x;
	
	i = 0;
	for (yp = 0; yp < h; yp += 8) {
		il += w;
		last = 0;
		if (flip == 1) {
			for (i = 0; i < w; ++i) {
				if (yoff > 0 && yp > 0) {
					last = sprite[il - i - 1 - w] >> yoff_inv;
				}

				*vmem |= (sprite[il - i - 1] << yoff) + last;
				vmem++;
			}
		} else {
			for (; i < il; ++i) {
				if (yoff > 0 && yp > 0) {
					last = sprite[i - w] >> yoff_inv;
				}

				*vmem |= (sprite[i] << yoff) + last;
				vmem++;
			}
		}

		vmem += (128 - w);
	}

	// Go through last set of sprite data becasue it spills over into next page of VMEM
	if (yoff > 0) {
		if (flip == 1) {
			for (i = 0; i < w; ++i) {
				*vmem |= (sprite[il - i - 1] >> yoff_inv);
				++vmem;
			}
		} else {
			i -= w;
			for (; i < il; ++i) {
				*vmem |= (sprite[i] >> yoff_inv);
				++vmem;
			}
		}
	}
}

int main() {
	unsigned char* saucer = (unsigned char*)_saucer;
	unsigned char* cow[10] = { 
		(unsigned char*)_cow, 
		(unsigned char*)_abduction1,
		(unsigned char*)_abduction2, 
		(unsigned char*)_abduction3, 
		(unsigned char*)_abduction4, 
		(unsigned char*)_abduction5, 
		(unsigned char*)_abduction6,
		(unsigned char*)_walk1,
		(unsigned char*)_walk2,
		(unsigned char*)_walk3  };
	unsigned char keys = 0;
	unsigned char cowAnimation = 0;
	unsigned char frameCount = 0;
	unsigned char cowDir = 1;


	drawPlayfield();

	for (;;) {
		++frameCount;

		drawSprite(saucer, _saucer_x, _saucer_y, 16, 8, 0);
		drawSprite(cow[cowAnimation], _cow_x, _cow_y, 24, 16, cowDir);

		if (_cowState == ABDUCTING) {
			drawLine(_saucer_x + 6, _saucer_y + 8, _saucer_x + 6 - 16, 63, 1);
			drawLine(_saucer_x + 9, _saucer_y + 8, _saucer_x + 6 + 16, 63, 1);
		}

		display();

		clearSprite(_saucer_x, _saucer_y, 16, 8);
		clearSprite(_cow_x, _cow_y, 24, 16);

		if (_cowState == ABDUCTING) {
			unsigned char a = 7 - (_cow_y / 7);
			if (a > cowAnimation) {
				cowAnimation = a;
			} 
			_cow_y -= 3;
			if (_cow_x < (_saucer_x - 4)) {
				++_cow_x;
			} else if (_cow_x > (_saucer_x - 4)) {
				--_cow_x;
			}

			if (_cow_y < 8) {
				_cow_y = 48;
				_cow_x = 52;
				cowAnimation = 0;
				_cowState = NORMAL;
			}
		} else if (_cowState == FALLING) {
			_cow_y += 5;
			if (_cow_y > 48) {
				_cow_y = 48;
				_cowState = NORMAL;
			}
		} else if (_cowState == NORMAL) {
			if ((frameCount % 16) == 0) {
				_cowState = RIGHT;
				cowAnimation = 7;
				cowDir = 0;
			}
		} else if (_cowState == RIGHT) {
			_cow_x += 2;
			++cowAnimation;
			if (cowAnimation > 9) {
				cowAnimation = 7;
			}
			if (_cow_x > 104) {
				_cow_x = 104;
				_cowState = LEFT;
				cowDir = 1;
				cowAnimation = 7;
			}
		} else if (_cowState == LEFT) {
			_cow_x -= 2;
			++cowAnimation;
			if (cowAnimation > 9) {
				cowAnimation = 7;
			}
			if (_cow_x > 127) {
				_cow_x = 0;
				_cowState = RIGHT;
				cowDir = 0;
				cowAnimation = 7;
			} 
		}

		keys = *((unsigned char*)0x6001);
		if (_cowState != ABDUCTING) {
			if ((keys & 4) == 0) {
				_saucer_x -= 3;
			} 
			else if ((keys & 8) == 0) {
				_saucer_x += 3;
			}

			if (_saucer_x > 127) {	// Overflow
				_saucer_x = 0;
			}
			else if (_saucer_x > 112) {
				_saucer_x = 112;
			}
		}	

		if ((keys & 16) == 0) {
			_cowState = ABDUCTING;	
			if (cowAnimation >= 7) {	
				cowAnimation = 0;
			}
		} else {
			if (_cowState == ABDUCTING) {
				drawLine(_saucer_x + 6, _saucer_y + 8, _saucer_x + 6 - 16, 63, 0);
				drawLine(_saucer_x + 9, _saucer_y + 8, _saucer_x + 6 + 16, 63, 0);

				_cowState = FALLING;
			}	
		}

		led_on();
		wait();
		led_off();
	}

	return 0;
}