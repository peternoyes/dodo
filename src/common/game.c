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
			set_pixel(y0, x0, c);
		} else {
			set_pixel(x0, y0, c);
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
	/*
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
			if (v == 0) {
				for (; v < 8; ++v) {
					*vmem = 0;
					++vmem;
				}
			} else {
				l = v + 8;
				for (; v < l; ++v) {
					*vmem = _tiles[v];
					++vmem;
				}
			}
			++o;
		}
	}*/

	unsigned char p = y/8;
	unsigned char yoff = y%8;
	unsigned char i = 0;
	unsigned char* vmem = VIDEO_MEM + x + (p * 128);
	unsigned char* vmem2 = 0;
	unsigned char* vmem3 = 0;
	unsigned char ptot = 1;


	if (h > 8) {
		++ptot;
	}
	if (yoff > 0) {
		++ptot;
	}

	switch (ptot) {
		case 1:
			for (i = 0; i < w; ++i) {
				vmem[i] = 0;
			}
			break;
		case 2:
			vmem2 = vmem + 128;
			for (i = 0; i < w; ++i) {
				vmem[i] = 0;
				vmem2[i] = 0;
			}
			break;
		case 3:
			vmem2 = vmem + 128;
			vmem3 = vmem2 + 128;
			for (i = 0; i < w; ++i) {
				vmem[i] = 0;
				vmem2[i] = 0;
				vmem3[i] = 0;
			}
			break;
	}
}

void orSprite(unsigned char* sprite, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char flip) {
	unsigned char i = 0;
	unsigned char p = y/8;
	unsigned char yoff = y%8;
	unsigned char yoff_inv = 8-yoff;
	unsigned char limit = w;
	unsigned char flip_base = 0;
	unsigned char next = 0;
	unsigned char cur = 0;

	unsigned char* vmem = VIDEO_MEM + x + (p *128);
	unsigned char* vmem2 = 0;
	unsigned char* vmem3 = 0;


	if (yoff == 0) {
		if (flip == 0) {
			for (i = 0; i < limit; ++i) {
				vmem[i] |= sprite[i];
			}
			if (h > 8) {
				limit += w;
				vmem += (128 - w);
				for (i = w; i < limit; ++i) {
					vmem[i] |= sprite[i];
				}
			}
		} else {
			flip_base = limit - 1;
			for (i = 0; i < limit; ++i) {
				vmem[i] |= sprite[flip_base - i];
			}
			if (h > 8) {
				limit += w;
				flip_base = w + limit - 1;
				vmem += (128 - w);
				for (i = w; i < limit; ++i) {
					vmem[i] |= sprite[flip_base - i];
				}
			}
		}
	} else {
		vmem2 = vmem + 128;
		if (flip == 0) {
			if (h == 8) {
				for (i = 0; i < limit; ++i) {
					vmem[i] |= sprite[i] << yoff;
					vmem2[i] |= sprite[i] >> yoff_inv;
				}
			} else {
				vmem3 = vmem2 + 128;
				for (i = 0; i < limit; ++i) {
					vmem[i] |= sprite[i] << yoff;
					next = sprite[i + w];
					vmem2[i] |= ((sprite[i] >> yoff_inv) + (next << yoff));
					vmem3[i] |= next >> yoff_inv;
				}
			}
		} else {
			if (h == 8) {
				// TODO
			} else {
				vmem3 = vmem2 + 128;
				flip_base = limit - 1;
				for (i = 0; i < limit; ++i) {
					cur = sprite[flip_base - i];
					vmem[i] |= cur << yoff;
					next = sprite[flip_base - i + w];
					vmem2[i] |= ((cur >> yoff_inv) + (next << yoff));
					vmem3[i] |= next >> yoff_inv;
				}
			}
		}
	}
}

void drawSprite(unsigned char* sprite, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char flip) {
	unsigned char i = 0;
	unsigned char p = y/8;
	unsigned char yoff = y%8;
	unsigned char yoff_inv = 8-yoff;
	unsigned char limit = w;
	unsigned char flip_base = 0;
	unsigned char next = 0;
	unsigned char cur = 0;

	unsigned char* vmem = VIDEO_MEM + x + (p *128);
	unsigned char* vmem2 = 0;
	unsigned char* vmem3 = 0;


	if (yoff == 0) {
		if (flip == 0) {
			for (i = 0; i < limit; ++i) {
				vmem[i] = sprite[i];
			}
			if (h > 8) {
				limit += w;
				vmem += (128 - w);
				for (i = w; i < limit; ++i) {
					vmem[i] = sprite[i];
				}
			}
		} else {
			flip_base = limit - 1;
			for (i = 0; i < limit; ++i) {
				vmem[i] = sprite[flip_base - i];
			}
			if (h > 8) {
				limit += w;
				flip_base = w + limit - 1;
				vmem += (128 - w);
				for (i = w; i < limit; ++i) {
					vmem[i] = sprite[flip_base - i];
				}
			}
		}
	} else {
		vmem2 = vmem + 128;
		if (flip == 0) {
			if (h == 8) {
				for (i = 0; i < limit; ++i) {
					vmem[i] = sprite[i] << yoff;
					vmem2[i] = sprite[i] >> yoff_inv;
				}
			} else {
				vmem3 = vmem2 + 128;
				for (i = 0; i < limit; ++i) {
					vmem[i] = sprite[i] << yoff;
					next = sprite[i + w];
					vmem2[i] = ((sprite[i] >> yoff_inv) + (next << yoff));
					vmem3[i] = next >> yoff_inv;
				}
			}
		} else {
			if (h == 8) {
				// TODO
			} else {
				vmem3 = vmem2 + 128;
				flip_base = limit - 1;
				for (i = 0; i < limit; ++i) {
					cur = sprite[flip_base - i];
					vmem[i] = cur << yoff;
					next = sprite[flip_base - i + w];
					vmem2[i] = ((cur >> yoff_inv) + (next << yoff));
					vmem3[i] = next >> yoff_inv;
				}
			}
		}
	}

	/*
	unsigned char p = y/8;
	unsigned char yoff = y%8;
	unsigned char yoff_inv = 8-yoff;
	unsigned char vmem_offset = 128-w;
	unsigned char i = 0;
	unsigned char il = 0;
	unsigned char yp = 0;
	unsigned char last = 0;

	unsigned char* vmem = VIDEO_MEM + x + (p *128);

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

		vmem += vmem_offset;
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
	*/
}