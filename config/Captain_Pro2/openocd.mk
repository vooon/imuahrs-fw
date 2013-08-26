# -*- Makefile -*-

OPENOCD=openocd
OPENOCD_CONF=$(AHRS)/config/Captain_Pro2/openocd_captain2.cfg
OPENOCD_FLASH_BASE=0x08000000

program: $(AHRS)/build/$(PROJECT).bin
	$(OPENOCD) -f $(OPENOCD_CONF) \
		-c init \
		-c "reset halt" \
		-c "flash write_image erase $< $(OPENOCD_FLASH_BASE) bin" \
		-c "verify_image $< $(OPENOCD_FLASH_BASE) bin" \
		-c "reset run" \
		-c "shutdown"

