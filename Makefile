OBJS := ./main.o
INCS := -I./
DEFS := -DUSE_STDPERIPH_DRIVER

default: all
name := LogicMaster

include platform/platform.mk
include stlib/stlib.mk
include lua/lua.mk
include common.mk

all:$(name).bin

burn:$(name).bin
	@st-flash write $< 0x08000000
	
clean:
	@rm -f $(name).bin $(name).elf $(OBJS)
	
$(name).bin:$(name).elf
	@arm-none-eabi-objcopy -O binary -S $< $@
$(name).elf:$(OBJS)
	@arm-none-eabi-gcc $(LFLAGS) $^ -Tstlib/flash.ld -o $@
	@arm-none-eabi-size $@
	
.PHONY: all burn clean


