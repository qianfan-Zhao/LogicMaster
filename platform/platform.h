#ifndef platform_h
#define platform_h

#include "stm32f30x.h"
#include "stm32f30x_adc.h"
#include "stm32f30x_rcc.h"
#include "stm32f30x_spi.h"
#include "stm32f30x_i2c.h"
#include "stm32f30x_tim.h"
#include "stm32f30x_gpio.h"
#include "stm32f30x_usart.h"

#include "boardconfig.h"

/* serial communication functions */
int __io_putchar(int );
int __io_getchar(void);
int __io_puts(const char *);
char *__io_gets(char *,int);

/* platform gpio functions */
enum {GPIO_INPUT,GPIO_OUTPUT,GPIO_ANALOG};
enum {GPIO_PULLNO,GPIO_PULLUP,GPIO_PULLDOWN};
#define is_gpio_mode(mode) ( ((mode)>=GPIO_INPUT)&&((mode)<=GPIO_ANALOG) )
#define is_gpio_pull(pull) ( ((pull)>=GPIO_PULLNO)&&((pull)<=GPIO_PULLDOWN) )

/* if param 'pin' isn't a really pin,this function will return -1. 
 * else return 0 except gpio_read 
 * (gpio_read will return the pin's actual value).
 */
int gpio_mode(int pin,int mode,int pull);
int gpio_write(int pin,int value);
int gpio_read(int pin);
int gpio_toggle(int pin);

/* decalre a GPIO_InitTypeDef valible. named as 'name'
 *  mode can be 'IN' ,'OUT', 'AF', 'AN'
 *  ppod can be 'PP' or 'OD'
 *  updown can be 'UP','DOWN'
 *  speed can from 1 to 3
 */
#define DECLARE_GPIO_INIT(name,mode,ppod,updown,speed) \
	GPIO_InitTypeDef name ={ \
			.GPIO_Pin=0, \
			.GPIO_Mode=GPIO_Mode_##mode, \
			.GPIO_OType=GPIO_OType_##ppod,\
			.GPIO_PuPd=GPIO_PuPd_##updown,\
			.GPIO_Speed=GPIO_Speed_Level_##speed,\
	};

#define DECLARE_USART_INIT(name,baud) \
		USART_InitTypeDef name ={ \
				.USART_BaudRate=baud, \
				.USART_HardwareFlowControl=USART_HardwareFlowControl_None,\
				.USART_Mode=USART_Mode_Rx|USART_Mode_Tx,\
				.USART_Parity=USART_Parity_No, \
				.USART_StopBits=USART_StopBits_1,\
				.USART_WordLength=USART_WordLength_8b,\
		};



#endif


