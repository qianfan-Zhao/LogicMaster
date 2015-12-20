#include <stdio.h> /* for NULL */
#include <platform.h>

/* Left			   NucleoF303RE				   	 Right			
  *                                   15 PB8(SCL)
  *													          14 PB9(SDA)
  *                                   13 PA5(SCK)
  *                                   12 PA6(MISO)
  *               GPIO                11 PA7(MOSI)
  *           ------------>           10 PB6
  *                |------>            9 PC7
  *                |------>            8 PA9
  *------------------------------------------------
  *   ANALOG       |------>            7 PA8
  *                |------>            6 PB10
  * 16 A0 PA0 <----|------>            5 PB4
  * 17 A1 PA1 <----|------>            4 PB5
  * 18 A2 PA4 <----|------>            3 PB3 
  * 19 A3 PB0 <----|------>            2 PA10
  * 20 A4 PC1 <----|                   1 PA2(Tx)
  * 21 A5 PC0 <----|                   0 PA3(Rx)
  */
  
struct pininfo
{
	GPIO_TypeDef *GPIO;
	uint16_t GPIO_Pin;
};

const struct pininfo pininfo[]=
{
	{NULL,0},
	{NULL,0},
	{GPIOA,GPIO_Pin_10},
	{GPIOB,GPIO_Pin_3},
	{GPIOB,GPIO_Pin_5},
	{GPIOB,GPIO_Pin_4},
	{GPIOB,GPIO_Pin_10},
	{GPIOA,GPIO_Pin_8},
/*------------------*/
	{GPIOA,GPIO_Pin_9},
	{GPIOC,GPIO_Pin_7},
	{GPIOB,GPIO_Pin_6},
	{NULL,0},
	{NULL,0},
	{NULL,0},
	{NULL,0},
	{NULL,0},
/*------------------*/
	{GPIOA,GPIO_Pin_0},
	{GPIOA,GPIO_Pin_1},
	{GPIOA,GPIO_Pin_4},
	{GPIOB,GPIO_Pin_0},
	{GPIOC,GPIO_Pin_1},
	{GPIOC,GPIO_Pin_0},
};

#define pin2GPIO(pin) ( pininfo[pin].GPIO )
#define pin2pin(pin)	( pininfo[pin].GPIO_Pin)

/* enum in platform.h 
 *
 * enum {GPIO_INPUT,GPIO_OUTPUT,GPIO_ANALOG};
 * enum {GPIO_PULLNO,GPIO_PULLUP,GPIO_PULLDOWN};
 */
 
static const GPIOMode_TypeDef gpio_mode_buff[3] =
 {GPIO_Mode_IN,GPIO_Mode_OUT,GPIO_Mode_AN};
static const GPIOPuPd_TypeDef gpio_pupd_buff[3] =
 {GPIO_PuPd_NOPULL,GPIO_PuPd_UP,GPIO_PuPd_DOWN};
 

 
int gpio_mode(int pin,int mode,int pull)
{
	DECLARE_GPIO_INIT(ioIt,IN,PP,UP,3);
	
	if(!is_gpio_pin(pin) || !is_gpio_mode(mode) || !is_gpio_pull(pull) )
		return -1;
	ioIt.GPIO_Pin=pin2pin(pin);
	ioIt.GPIO_Mode=gpio_mode_buff[mode];
	ioIt.GPIO_PuPd=gpio_pupd_buff[pull];
	
	GPIO_Init(pin2GPIO(pin),&ioIt);
	return 0;
}

int gpio_write(int pin,int value)
{
	if(!is_gpio_pin(pin)) 
		return -1;
	if(value) pin2GPIO(pin)->BSRR = pin2pin(pin);
	else			pin2GPIO(pin)->BRR  = pin2pin(pin);
	return 0;
}

int gpio_read(int pin)
{
	if(!is_gpio_pin(pin)) 
		return -1;
	return GPIO_ReadInputDataBit(pin2GPIO(pin),pin2pin(pin));
}

int gpio_toggle(int pin)
{
	if(!is_gpio_pin(pin))
		return -1;
	pin2GPIO(pin)->ODR ^= pin2pin(pin);
	return 0;
}




