#include "header.h"
#define CS0 (1<<7)

u16 mcp3204_adc_read(u8 ch_num)
{
	u8 byteH=0, byteL=0, channel=0;
	u16 result=0;
	channel=ch_num<<6;
	IOCLR0=CS0;							//select slave
	spi0(0x06);
	byteH=spi0(channel);
	byteL=spi0(0x0);
	IOSET0=CS0;
	byteH&=0x0F;
	result=(byteH<<8) | byteL;
	return result;
}






	