ASM_SOURCES = crt0.s65

# Compilation of assembler files
%.o: %.s65
	ca65 --cpu 6502 -o $@ -l $(@:.o=.lst) $<

all: flash

flash: $(ASM_SOURCES:.s65=.o)
	cl65 -C flash.cfg -m flash.map -o $@ $^

clean:
	rm -f flash *.s *.o *.lst *.map