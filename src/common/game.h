#ifndef __GAME_H
#define __GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "io.h"

#define VIDEO_MEM ((unsigned char *) 0x3c00)
#define _BV(bit) (1 << (bit))

#define SPI_WREN  0x06
#define SPI_WRDI  0x04
#define SPI_RDSR  0x05
#define SPI_WRSR  0x01
#define SPI_READ  0x03
#define SPI_WRITE 0x02
#define SPI_RDID  0x9F



static unsigned char const _playfield[128] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
										       0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
											   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

static unsigned char* _tiles = 0;


void fullscreenImage(unsigned char* image);
void setTiles(unsigned char* tiles);
//void setPixel(unsigned char x, unsigned char y, unsigned char c);
unsigned char getPixel(unsigned char x, unsigned char y);
//void drawLine(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char c);
void drawPlayfield(void);
//void clearSprite(unsigned char x, unsigned char y, unsigned char w, unsigned char h);
//void orSprite(unsigned char* sprite, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char flip);
//void drawSprite(unsigned char* sprite, unsigned char x, unsigned char y, unsigned char w, unsigned char h, unsigned char flip);
void getSpiDevice(unsigned char* manufacturer, unsigned char* density, unsigned char* product);
unsigned char spiRead(unsigned int a);
void spiWriteEnable(unsigned char e);
void spiWrite(unsigned int a, unsigned char v);

#endif											   