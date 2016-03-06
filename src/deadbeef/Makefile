C_SOURCES = main.c ../common/game.c
ASM_SOURCES = ../common/crt0.s65 ../common/zeropage.s65 ../common/display.s65 ../common/util.s65 ../common/io.s65

# Compilation of C files
%.o: %.c
	cc65 --cpu 6502 -O -t none -o $(@:.o=.s) $<
	ca65 --cpu 6502 -o $@ -l $(@:.o=.lst) $(<:.c=.s)

# Compilation of assembler files
%.o: %.s65
	ca65 --cpu 6502 -o $@ -l $(@:.o=.lst) $<

all: firmware

firmware: $(ASM_SOURCES:.s65=.o) $(C_SOURCES:.c=.o)
	cl65 -C ../common/firmware.cfg -m firmware.map -o $@ $^ ../common/dodo.lib

clean:
	rm -f firmware *.s *.o *.lst *.map
