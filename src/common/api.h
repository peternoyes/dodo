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

#define DRAW_SPRITE(sprite, x, y, w, h, f) SET_INDEX(0); draw_sprite_proto(sprite, x, y, w, h, f)
#define DISPLAY() SET_INDEX(1); display_proto()
#define CLEAR_SPRITE(x, y, w, h) SET_INDEX(2); clear_sprite_proto(x, y, w, h)
#define SET_PIXEL(x, y, c) SET_INDEX(3); set_pixel_proto(x, y, c)
#define DRAW_LINE(x0, y0, x1, y1, c) SET_INDEX(4); draw_line_proto(x0, y0, x1, y1, c)
#define DELAY_MS(delay) SET_INDEX(5); delay_ms_proto(delay)
#define LED_ON() SET_INDEX(6); led_on_proto()
#define LED_OFF() SET_INDEX(7); led_off_proto()
#define WAIT() SET_INDEX(8); wait_proto()
#define LOAD_MUSIC(music) SET_INDEX(9); load_music_proto(music)
#define PLAY_EFFECT(effect) SET_INDEX(10); play_effect_proto(effect)
#define SPI_ENABLE() SET_INDEX(11); spi_enable_proto()
#define SPI_DISABLE() SET_INDEX(12); spi_disable_proto()
#define SPI_WRITE(v) SET_INDEX(13); spi_write_proto(v)
#define SPI_WRITE_R(v, r) SET_INDEX(13); r = spi_write_proto(v)

#define SET_INDEX(i) __A__ = i; asm("sta $0");

static void (*draw_sprite_proto)(byte*, byte, byte, byte, byte, byte);
static void (*display_proto)(void);
static void (*clear_sprite_proto)(byte x, byte y, byte w, byte h);
static void (*set_pixel_proto)(byte x, byte y, byte c);
static void (*draw_line_proto)(byte x0, byte y0, byte x1, byte y1, byte c);
static void (*delay_ms_proto)(byte delay);
static void (*led_on_proto)(void);
static void (*led_off_proto)(void);
static void (*wait_proto)(void);
static void (*load_music_proto)(byte* music);
static void (*play_effect_proto)(byte* effect);
static void (*spi_enable_proto)(void);
static void (*spi_disable_proto)(void);
static byte (*spi_write_proto)(byte v);

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
	delay_ms_proto = (void (*)(byte))(*(int*)0xFFF8);
	led_on_proto = (void (*)(void))(*(int*)0xFFF8);
	led_off_proto = (void (*)(void))(*(int*)0xFFF8);
	wait_proto = (void (*)(void))(*(int*)0xFFF8);
	load_music_proto = (void (*)(byte*))(*(int*)0xFFF8);
	play_effect_proto = (void (*)(byte*))(*(int*)0xFFF8);
	spi_enable_proto = (void (*)(void))(*(int*)0xFFF8);
	spi_disable_proto = (void (*)(void))(*(int*)0xFFF8);
	spi_write_proto = (byte (*)(byte))(*(int*)0xFFF8);
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
