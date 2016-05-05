C_SOURCES = main.c
ASM_SOURCES = crt0.s65 zeropage.s65

# Compilation of C files
%.o: %.c
	cc65 --cpu 6502 -O -t none -o $(@:.o=.s) $<
	ca65 --cpu 6502 -o $@ -l $(@:.o=.lst) $(<:.c=.s)

# Compilation of assembler files
%.o: %.s65
	ca65 --cpu 6502 -o $@ -l $(@:.o=.lst) $<

all: fram.bin

fram.bin: $(ASM_SOURCES:.s65=.o) $(C_SOURCES:.c=.o)
	cl65 -C fram.cfg -m deadbeef.map -o $@ $^ ../common/dodo.lib

clean:
	rm -f fram.bin *.s *.o *.lst *.map
