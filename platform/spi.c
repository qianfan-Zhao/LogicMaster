#include "platform.h"

DECLARE_SPI_INIT(spiit,Low,1Edge,MSB);

static int _mode,_order,_bauddiv;
const uint16_t spi_cpol_buf[]=
	{SPI_CPOL_Low,SPI_CPOL_Low,SPI_CPOL_High,SPI_CPOL_High};
const uint16_t spi_cpha_buf[]=
	{SPI_CPHA_1Edge,SPI_CPHA_2Edge,SPI_CPHA_1Edge,SPI_CPHA_2Edge};
const uint16_t spi_order_buf[]={SPI_FirstBit_MSB,SPI_FirstBit_LSB};
const uint16_t spi_bauddiv_buf[]={
	SPI_BaudRatePrescaler_2,SPI_BaudRatePrescaler_4,SPI_BaudRatePrescaler_8,
	SPI_BaudRatePrescaler_16,SPI_BaudRatePrescaler_32,SPI_BaudRatePrescaler_64,
	SPI_BaudRatePrescaler_128,SPI_BaudRatePrescaler_256};
	
int spi_init(int mode,int order,int bauddiv)
{
	if(!is_spi_mode(mode)||!is_spi_order(order)||
		 !is_spi_bauddiv(bauddiv))
		return -1;
	
	_mode=mode;_order=order;_bauddiv=bauddiv;
	SPI_Cmd(SPI,DISABLE);
	spiit.SPI_CPOL=spi_cpol_buf[mode];
	spiit.SPI_CPHA=spi_cpha_buf[mode];
	spiit.SPI_FirstBit=spi_order_buf[order];
	spiit.SPI_BaudRatePrescaler=spi_bauddiv_buf[bauddiv];
	SPI_Init(SPI,&spiit);
	
	SPI_RxFIFOThresholdConfig(SPI, SPI_RxFIFOThreshold_QF);
	SPI_Cmd(SPI,ENABLE);
	
	return 0;
}

int spi_mode(int mode)
{
	if(!is_spi_mode(mode)) return -1;
		
	_mode=mode;
	SPI_Cmd(SPI,DISABLE);
	spiit.SPI_CPOL=spi_cpol_buf[mode];
	spiit.SPI_CPHA=spi_cpha_buf[mode];
	SPI_Init(SPI,&spiit);
	SPI_Cmd(SPI,ENABLE);
	
	return 0;
}

int spi_order(int order)
{
	if(!is_spi_order(order)) return -1;
	_order=order;
	SPI_Cmd(SPI,DISABLE);
	spiit.SPI_FirstBit=spi_order_buf[order];
	SPI_Init(SPI,&spiit);
	SPI_Cmd(SPI,ENABLE);
	return 0;
}

int spi_div(int bauddiv)
{
	if(!is_spi_bauddiv(bauddiv)) return -1;
	_bauddiv=bauddiv;
	SPI_Cmd(SPI,DISABLE);
	spiit.SPI_BaudRatePrescaler=spi_bauddiv_buf[bauddiv];
	SPI_Init(SPI,&spiit);
	SPI_Cmd(SPI,ENABLE);
	return 0;
}

/*
 * --------------------------------------------------------
 * 31  (ClockFreq)    4 | 3(KHz/MHz) | 2(order) | 1~0(mode)
 * --------------------------------------------------------
 * 3(KHz/MHz): 0=Hz,1=MHz
 * 2(Order):   SPI_MSBFIRST or SPI_LSBFIRST
 * --------------------------------------------------------
 */
int spi_info(void)
{
	int freq;
	int hz=0;/* default is KHz */
	int result=0;
	static const int divnum[]={2,4,8,16,32,64,128,256};
	
	freq=SystemCoreClock/divnum[_bauddiv];
	if(freq>1000000/* 1MHz */) {
		hz=1;/* type is MHz */
		freq /= 1000000;
	}
	result = ( (freq<<4)|(hz<<3)|(_order<<2)|(_mode<<0 ) );
	return result;
}

uint8_t spi_transfer(uint8_t data)
{
	while(!SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_TXE)) ;
	SPI_SendData8(SPI, data);
	
	while(!SPI_I2S_GetFlagStatus(SPI, SPI_I2S_FLAG_RXNE)) ;
	return SPI_ReceiveData8(SPI);
}



