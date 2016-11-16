ASM_SOURCES = entry.s65 zeropage.s65 display.s65 util.s65 io.s65 api.s65 text.s65

all: flash_code firmware

FLASH_DIR = flash
.PHONY: flash_code
flash_code:
	$(MAKE) -C $(FLASH_DIR)	

# Compilation of assembler files
%.o: %.s65
	ca65 --cpu 6502 -D $(TARGET) -o $@ -l $(@:.o=.lst) $<

all: firmware

firmware: $(ASM_SOURCES:.s65=.o)
	cl65 -C firmware.cfg -m firmware.map -o $@ $^

clean:
	rm -f firmware *.s *.o *.lst *.map
	$(MAKE) -C $(FLASH_DIR) clean
