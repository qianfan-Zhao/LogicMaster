#include "platform.h"

void usart_mode_init(void)
{
	DECLARE_GPIO_INIT(ioIt,AF,PP,UP,3);
	ioIt.GPIO_Pin=USART_RX_PIN | USART_TX_PIN;
	DECLARE_USART_INIT(uIt,USART_BAUD);
	
	GPIO_Init(USART_GPIO,&ioIt);
	GPIO_PinAFConfig(USART_GPIO,USART_RX_SRC,USART_GPIO_AF);
	GPIO_PinAFConfig(USART_GPIO,USART_TX_SRC,USART_GPIO_AF);

	USART_ClkEn();
	USART_Init(USART,&uIt);
	USART_ClearFlag(USART,USART_FLAG_RXNE);
	USART_ClearFlag(USART,USART_FLAG_TXE);
	NVIC_EnableIRQ(USART_IRQn);
	USART_ITConfig(USART,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART,ENABLE);
}

void spi_mode_init(void)
{
	DECLARE_GPIO_INIT(ioIt,AF,PP,UP,3);
	ioIt.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_Init(GPIOA,&ioIt);/* CLK,MISO,MOSI */
	
	ioIt.GPIO_Mode=GPIO_Mode_OUT;
	ioIt.GPIO_Pin=GPIO_Pin_6;
	GPIO_Init(GPIOB,&ioIt);/* CS */
	spi_cshigh();
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_5);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_5);
	
	spi_init(SPI_MODE0,SPI_MSBFIRST,7);/* spi baud div 256 */
}

void init(void)
{
	RCC_AHBPeriphClockCmd(0xFFFFFFFF,ENABLE);
	RCC_APB1PeriphClockCmd(0xFFFFFFFF,ENABLE);
	RCC_APB2PeriphClockCmd(0xFFFFFFFF,ENABLE);
	
	usart_mode_init();
	spi_mode_init();
}








