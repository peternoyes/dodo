#include "game.h"

void setTiles(unsigned char* tiles) {
	_tiles = tiles;
}

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