#include "header.h"
#define CS0 (1<<7)
#define SPIF ((S0SPSR>>7)&1)

void spi0_init(void)
{
	PINSEL0|=0x1500;				//P0.4	SCK0	P0.5	MISO0	P0.6	MOSI0
	IODIR0|=CS0;						//P0.7	CS0
	IOSET0=CS0;							//CS0=1
	S0SPCR=0X20;						//CPOL=CPHA=0
	S0SPCCR=15;							//spi0_freq 1Mbps
}
	
u8 spi0(u8 data)
{
	S0SPDR=data;
	while(SPIF==0);
	return S0SPDR;
}












