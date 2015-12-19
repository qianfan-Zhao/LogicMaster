INCS += -Istlib -Istlib/cminc -Istlib/inc

OBJS += stlib/startup_stm32f30x.o stlib/system_stm32f30x.o
OBJS += stlib/src/stm32f30x_adc.o stlib/src/stm32f30x_dma.o \
			  stlib/src/stm32f30x_gpio.o stlib/src/stm32f30x_i2c.o \
			  stlib/src/stm32f30x_misc.o stlib/src/stm32f30x_rcc.o \
			  stlib/src/stm32f30x_spi.o stlib/src/stm32f30x_syscfg.o \
			  stlib/src/stm32f30x_tim.o stlib/src/stm32f30x_usart.o 

