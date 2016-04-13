C_SOURCES = main.c ../common/game.c
ASM_SOURCES = crt0.s65 zeropage.s65

# Compilation of C files
%.o: %.c
	cc65 --cpu 6502 -O -t none -o $(@:.o=.s) $<
	ca65 --cpu 6502 -o $@ -l $(@:.o=.lst) $(<:.c=.s)

# Compilation of assembler files
%.o: %.s65
	ca65 --cpu 6502 -o $@ -l $(@:.o=.lst) $<

all: deadbeef

deadbeef: $(ASM_SOURCES:.s65=.o) $(C_SOURCES:.c=.o)
	cl65 -C deadbeef.cfg -m deadbeef.map -o $@ $^ ../common/dodo.lib

clean:
	rm -f deadbeef *.s *.o *.lst *.map
