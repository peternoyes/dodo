#ifndef _DISPLAY_H
#define _DISPLAY_H

extern void __fastcall__ set_pixel(unsigned char x, unsigned char y, unsigned char c);
extern void __fastcall__ display(void);
extern void __fastcall__ draw_sprite(unsigned char* sprite, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char flip);
extern void __fastcall__ clear_sprite(unsigned char x, unsigned char y, unsigned char w, unsigned char h);

#endif
