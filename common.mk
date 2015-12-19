CFLAGS += -mcpu=cortex-m4 -mthumb -Wall -std=gnu99
CFLAGS += -Wno-unused-variable #don't waring unused variable 
CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 #use hard float uint
CFLAGS += -nostartfiles
CFLAGS += -ffunction-sections -fdata-sections -Os
#CFLAGS += -g

LFLAGS += -mcpu=cortex-m4 -mthumb 
LFLAGS += -specs=nano.specs 
LFLAGS += -u_printf_float #Use this option if you want print float
LFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
LFLAGS += -Os -Wl,--gc-sections 
#LFLAGS += -Wl,-Map=flash_sram.map

%.o:%.S
	@echo cc: $<
	@arm-none-eabi-gcc $(CFLAGS) -c $< -o $@
%.o:%.c
	@echo cc: $<
	@arm-none-eabi-gcc $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@

