#ifndef _API_H
#define _API_H

#define byte unsigned char

// Specify version compiled against. Semantic versioning enforcement takes place in CHECK_VERSION
#define MAJOR 1
#define MINOR 0
#define REVISION 1

#define SPI_WREN  0x06
#define SPI_WRDI  0x04
#define SPI_RDSR  0x05
#define SPI_WRSR  0x01
#define SPI_READ  0x03
#define SPI_WRIT  0x02
#define SPI_RDID  0x9F

#define DRAW_NOP 0x0
#define DRAW_OR  0x1
#define DRAW_AND 0x2
#define DRAW_XOR 0x4

#define DRAW_SPRITE(sprite, x, y, w, h, f, m) draw_sprite_proto(sprite, x, y, w, h, f, m, 0)
#define DISPLAY() display_proto(1)
#define CLEAR_SPRITE(x, y, w, h) clear_sprite_proto(x, y, w, h, 2)
#define SET_PIXEL(x, y, c) set_pixel_proto(x, y, c, 3)
#define DRAW_LINE(x0, y0, x1, y1, c) draw_line_proto(x0, y0, x1, y1, c, 4)
#define DELAY_MS(delay) delay_ms_proto(delay, 5)
#define LED_ON() led_on_proto(6)
#define LED_OFF() led_off_proto(7)
#define WAIT() wait_proto(8)
#define LOAD_MUSIC(music) load_music_proto(music, 9)
#define PLAY_EFFECT(effect) play_effect_proto(effect, 1, 10);
#define PLAY_EFFECT_ONCE(effect) play_effect_proto(effect, 0, 10)
#define SPI_ENABLE() spi_enable_proto(11)
#define SPI_DISABLE() spi_disable_proto(12)
#define SPI_WRITE(v) spi_write_proto(v, 13)
#define CLEAR() clear_proto(14)
#define COPY_BACKGROUND(data, x, y, w, h, dir) copy_background_proto(data, x, y, w, h, dir, 15)
#define DRAW_STRING(text) draw_string_proto(text, 16)
#define SET_CURSOR(row, col) set_cursor_proto(row, col, 17)
#define READ_BUTTONS() read_buttons_proto(18)
#define GET_PIXEL(x, y) get_pixel_proto(x, y, 19)
#define GET_VERSION(version) get_version_proto(version, 20);
#define CHECK_VERSION(major, minor, revision) check_version_proto(major, minor, revision, 21)

static void (*draw_sprite_proto)(byte*, byte, byte, byte, byte, byte, byte, byte);
static void (*display_proto)(byte);
static void (*clear_sprite_proto)(byte, byte, byte, byte, byte);
static void (*set_pixel_proto)(byte, byte, byte, byte);
static void (*draw_line_proto)(byte, byte, byte, byte, byte, byte);
static void (*delay_ms_proto)(byte, byte);
static void (*led_on_proto)(byte);
static void (*led_off_proto)(byte);
static void (*wait_proto)(byte);
static void (*load_music_proto)(byte*, byte);
static void (*play_effect_proto)(byte*, byte, byte);
static void (*spi_enable_proto)(byte);
static void (*spi_disable_proto)(byte);
static byte (*spi_write_proto)(byte, byte);
static void (*clear_proto)(byte);
static void (*copy_background_proto)(byte*, byte, byte, byte, byte, byte, byte);
static void (*draw_string_proto)(char*, byte);
static void (*set_cursor_proto)(byte, byte, byte);
static byte (*read_buttons_proto)(byte);
static byte (*get_pixel_proto)(byte, byte, byte);
static void (*get_version_proto)(byte*, byte);
static void (*check_version_proto)(byte, byte, byte, byte);


static unsigned char get_sp() {
	asm("lda #sp");
	return __A__;
}

void api_init() {
	byte* sp_ptr = (byte*)get_sp();
	__A__ = (byte)sp_ptr;
	asm("sta $0");

	draw_sprite_proto = (void (*)(byte*, byte, byte, byte, byte, byte, byte, byte))(*(int*)0xFFF8);
	display_proto = (void (*)(byte))(*(int*)0xFFF8);
	clear_sprite_proto = (void (*)(byte, byte, byte, byte, byte))(*(int*)0xFFF8);
	set_pixel_proto = (void (*)(byte, byte, byte, byte))(*(int*)0xFFF8);
	draw_line_proto = (void (*)(byte, byte, byte, byte, byte, byte))(*(int*)0xFFF8);
	delay_ms_proto = (void (*)(byte, byte))(*(int*)0xFFF8);
	led_on_proto = (void (*)(byte))(*(int*)0xFFF8);
	led_off_proto = (void (*)(byte))(*(int*)0xFFF8);
	wait_proto = (void (*)(byte))(*(int*)0xFFF8);
	load_music_proto = (void (*)(byte*, byte))(*(int*)0xFFF8);
	play_effect_proto = (void (*)(byte*, byte, byte))(*(int*)0xFFF8);
	spi_enable_proto = (void (*)(byte))(*(int*)0xFFF8);
	spi_disable_proto = (void (*)(byte))(*(int*)0xFFF8);
	spi_write_proto = (byte (*)(byte, byte))(*(int*)0xFFF8);
	clear_proto = (void (*)(byte))(*(int*)0xFFF8);
	copy_background_proto = (void (*)(byte*, byte, byte, byte, byte, byte, byte))(*(int*)0xFFF8);
	draw_string_proto = (void (*)(char*, byte))(*(int*)0xFFF8);
	set_cursor_proto = (void (*)(byte, byte, byte))(*(int*)0xFFF8);
	read_buttons_proto = (byte (*)(byte))(*(int*)0xFFF8);
	get_pixel_proto = (byte (*)(byte, byte, byte))(*(int*)0xFFF8);
	get_version_proto = (void (*)(byte*, byte))(*(int*)0xFFF8);
	check_version_proto = (void (*)(byte, byte, byte, byte))(*(int*)0xFFF8);

	CHECK_VERSION(MAJOR, MINOR, REVISION);	// This will spin forever if there is a version mismatch
}

#endif
