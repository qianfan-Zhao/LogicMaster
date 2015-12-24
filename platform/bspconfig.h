#ifndef bsp_config_h
#define bsp_config_h
	
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
  
enum {GPIO_A0=16,GPIO_A1,GPIO_A2,GPIO_A3,GPIO_A4,GPIO_A5};
#define is_gpio_pin(pin)   ( ((pin>=2)&&(pin<=10)) || \
													   ((pin>=GPIO_A0)&&(pin<=GPIO_A5)) )
#define is_analog_pin(pin) ( ((pin>=GPIO_A0)&&(pin<=GPIO_A5)) )
 
#define USART USART2
#define USART_GPIO GPIOA
#define USART_BAUD 115200
#define USART_RD_BUF_LEN 256
#define USART_GPIO_AF GPIO_AF_7
#define USART_RX_PIN GPIO_Pin_2
#define USART_TX_PIN GPIO_Pin_3
#define USART_RX_SRC GPIO_PinSource2
#define USART_TX_SRC GPIO_PinSource3
#define USART_IRQn   USART2_IRQn
#define USART_Handler() void USART2_IRQHandler(void)
#define USART_ClkEn() \
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE)
	
#define SPI SPI1
#define spi_cshigh() (GPIOB->BSRR = (1<<6) ) 
#define spi_cslow()  (GPIOB->BRR  = (1<<6) )


#endif

