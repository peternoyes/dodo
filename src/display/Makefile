C_SOURCES = main.c
ASM_SOURCES = crt0.s65 zeropage.s65 display.s65 util.s65 led.s65

# Compilation of C files
%.o: %.c
	cc65 --cpu 6502 -O -t none -o $(@:.o=.s) $<
	ca65 --cpu 6502 -o $@ -l $(@:.o=.lst) $(<:.c=.s)

# Compilation of assembler files
%.o: %.s65
	ca65 --cpu 6502 -o $@ -l $(@:.o=.lst) $<

all: firmware

firmware: $(ASM_SOURCES:.s65=.o) $(C_SOURCES:.c=.o)
	cl65 -C firmware.cfg -m firmware.map -o $@ $^ dodo.lib

clean:
	rm -f firmware *.s *.o *.lst *.map
