#ifndef _API_H
#define _API_H

#define byte unsigned char

#define DRAW_SPRITE(sprite, x, y, w, h, f) SET_INDEX(0); draw_sprite_proto(sprite, x, y, w, h, f)
#define DISPLAY() SET_INDEX(1); display_proto()
#define CLEAR_SPRITE(x, y, w, h) SET_INDEX(2); clear_sprite_proto(x, y, w, h)
#define SET_PIXEL(x, y, c) SET_INDEX(3); set_pixel_proto(x, y, c)
#define DRAW_LINE(x0, y0, x1, y1, c) SET_INDEX(4); draw_line_proto(x0, y0, x1, y1, c)
#define DELAY_MS(delay) SET_INDEX(5); delay_ms_proto(delay)

#define SET_INDEX(i) __A__ = i; asm("sta $0");

static void (*draw_sprite_proto)(byte*, byte, byte, byte, byte, byte);
static void (*display_proto)(void);
static void (*clear_sprite_proto)(byte x, byte y, byte w, byte h);
static void (*set_pixel_proto)(byte x, byte y, byte c);
static void (*draw_line_proto)(byte x0, byte y0, byte x1, byte y1, byte c);
static void (*delay_ms_proto)(byte delay);

static unsigned char get_sp() {
	asm("lda #sp");
	return __A__;
}

void api_init() {
	byte* sp_ptr = (byte*)get_sp();
	__A__ = (byte)sp_ptr;
	asm("sta $1");

	draw_sprite_proto = (void (*)(byte*, byte, byte, byte, byte, byte))(*(int*)0xFFF8);
	display_proto = (void (*)(void))(*(int*)0xFFF8);
	clear_sprite_proto = (void (*)(byte x, byte y, byte w, byte h))(*(int*)0xFFF8);
	set_pixel_proto = (void (*)(byte x, byte y, byte c))(*(int*)0xFFF8);
	draw_line_proto = (void (*)(byte x0, byte y0, byte x1, byte y1, byte c))(*(int*)0xFFF8);
	delay_ms_proto = (void (*)(byte delay))(*(int*)0xFFF8);
}

//#define SWAP(a, b) { unsigned char t = a; a = b; b = t;}

/*
void drawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char c) {
	unsigned char dx, dy;
	signed char ystep;
	signed char err;
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

	if (steep) {
		for (; x0<=x1; ++x0) {
			SET_PIXEL(y0, x0, c);

			err -= dy;
			if (err < 0) {
				y0 += ystep;
				err += dx;
			}
		}
	} else {
		for (; x0<=x1; ++x0) {
			SET_PIXEL(x0, y0, c);

			err -= dy;
			if (err < 0) {
				y0 += ystep;
				err += dx;
			}
		}
	}
}*/

#endif
