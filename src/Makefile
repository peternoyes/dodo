ASM_SOURCES = entry.s65 zeropage.s65 display.s65 util.s65 io.s65 api.s65 text.s65

all: flash_code firmware_kita firmware_kitb

FLASH_DIR = flash
.PHONY: flash_code
flash_code:
	$(MAKE) -C $(FLASH_DIR)	

# Compilation of assembler files
%_kita.o: %.s65
	ca65 --cpu 6502 -D KITA -o $@ -l $(@:.o=.lst) $<

%_kitb.o: %.s65
	ca65 --cpu 6502 -D KITB -o $@ -l $(@:.o=.lst) $<

firmware_kita: $(ASM_SOURCES:.s65=_kita.o)
	cl65 -C firmware.cfg -m firmware.map -o $@ $^

firmware_kitb: $(ASM_SOURCES:.s65=_kitb.o)
	cl65 -C firmware.cfg -m firmware.map -o $@ $^

clean:
	rm -f firmware_* *.s *.o *.lst *.map
	$(MAKE) -C $(FLASH_DIR) clean
