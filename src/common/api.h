#ifndef _API_H
#define _API_H

#define byte unsigned char

#define SPI_WREN  0x06
#define SPI_WRDI  0x04
#define SPI_RDSR  0x05
#define SPI_WRSR  0x01
#define SPI_READ  0x03
#define SPI_WRIT  0x02
#define SPI_RDID  0x9F

#define DRAW_SPRITE(sprite, x, y, w, h, f) draw_sprite_proto(sprite, x, y, w, h, f, 0)
#define DISPLAY() display_proto(1)
#define CLEAR_SPRITE(x, y, w, h) clear_sprite_proto(x, y, w, h, 2)
#define SET_PIXEL(x, y, c) set_pixel_proto(x, y, c, 3)
#define DRAW_LINE(x0, y0, x1, y1, c) draw_line_proto(x0, y0, x1, y1, c, 4)
#define DELAY_MS(delay) delay_ms_proto(delay, 5)
#define LED_ON() led_on_proto(6)
#define LED_OFF() led_off_proto(7)
#define WAIT() wait_proto(8)
#define LOAD_MUSIC(music) load_music_proto(music, 9)
#define PLAY_EFFECT(effect) play_effect_proto(effect, 10)
#define SPI_ENABLE() spi_enable_proto(11)
#define SPI_DISABLE() spi_disable_proto(12)
#define SPI_WRITE(v) spi_write_proto(v, 13)
#define CLEAR() clear_proto(14)

static void (*draw_sprite_proto)(byte*, byte, byte, byte, byte, byte, byte);
static void (*display_proto)(byte);
static void (*clear_sprite_proto)(byte, byte, byte, byte, byte);
static void (*set_pixel_proto)(byte, byte, byte, byte);
static void (*draw_line_proto)(byte, byte, byte, byte, byte, byte);
static void (*delay_ms_proto)(byte, byte);
static void (*led_on_proto)(byte);
static void (*led_off_proto)(byte);
static void (*wait_proto)(byte);
static void (*load_music_proto)(byte*, byte);
static void (*play_effect_proto)(byte*, byte);
static void (*spi_enable_proto)(byte);
static void (*spi_disable_proto)(byte);
static byte (*spi_write_proto)(byte, byte);
static void (*clear_proto)(byte);


static unsigned char get_sp() {
	asm("lda #sp");
	return __A__;
}

void api_init() {
	byte* sp_ptr = (byte*)get_sp();
	__A__ = (byte)sp_ptr;
	asm("sta $0");

	draw_sprite_proto = (void (*)(byte*, byte, byte, byte, byte, byte, byte))(*(int*)0xFFF8);
	display_proto = (void (*)(byte))(*(int*)0xFFF8);
	clear_sprite_proto = (void (*)(byte, byte, byte, byte, byte))(*(int*)0xFFF8);
	set_pixel_proto = (void (*)(byte, byte, byte, byte))(*(int*)0xFFF8);
	draw_line_proto = (void (*)(byte, byte, byte, byte, byte, byte))(*(int*)0xFFF8);
	delay_ms_proto = (void (*)(byte, byte))(*(int*)0xFFF8);
	led_on_proto = (void (*)(byte))(*(int*)0xFFF8);
	led_off_proto = (void (*)(byte))(*(int*)0xFFF8);
	wait_proto = (void (*)(byte))(*(int*)0xFFF8);
	load_music_proto = (void (*)(byte*, byte))(*(int*)0xFFF8);
	play_effect_proto = (void (*)(byte*, byte))(*(int*)0xFFF8);
	spi_enable_proto = (void (*)(byte))(*(int*)0xFFF8);
	spi_disable_proto = (void (*)(byte))(*(int*)0xFFF8);
	spi_write_proto = (byte (*)(byte, byte))(*(int*)0xFFF8);
	clear_proto = (void (*)(byte))(*(int*)0xFFF8);
}

/*
void getSpiDevice(unsigned char* manufacturer, unsigned char* density, unsigned char* product) {
	SPI_ENABLE();
	SPI_WRITE(SPI_RDID);
	//*manufacturer = spi_write(0);
	SPI_WRITE_R(0, (*manufacturer));
	SPI_WRITE(0);
	//*density = spi_write(0);
	//*product = spi_write(0);
	SPI_WRITE_R(0, (*density));
	SPI_WRITE_R(0, (*product));
	SPI_DISABLE();
}

unsigned char spiRead(unsigned int a) {
	unsigned char v;
	SPI_ENABLE();
	SPI_WRITE(SPI_READ);
	SPI_WRITE(((unsigned char)(a >> 8)));
	SPI_WRITE(((unsigned char)(a & 0xFF)));
	//v = spi_write(0);
	SPI_WRITE_R(0, v);
	SPI_DISABLE();
	return v;
}

void spiWriteEnable(unsigned char e) {
	SPI_ENABLE();
	if (e == 1) {
		SPI_WRITE(SPI_WREN);
	} else {
		SPI_WRITE(SPI_WRDI);
	}
	SPI_DISABLE();
}

void spiWrite(unsigned int a, unsigned char v) {
	SPI_ENABLE();
	SPI_WRITE(SPI_WRIT);
	SPI_WRITE(((byte)(a >> 8)));
	SPI_WRITE(((byte)(a & 0xFF)));
	SPI_WRITE(v);
	SPI_DISABLE();
}*/

#endif
