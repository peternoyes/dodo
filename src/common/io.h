#ifndef _LED_H
#define _LED_H

extern void __fastcall__ led_on(void);
extern void __fastcall__ led_off(void);
extern void __fastcall__ wait(void);
extern void __fastcall__ load_music(unsigned char* music);
extern void __fastcall__ play_effect(unsigned char* effect);

#endif
