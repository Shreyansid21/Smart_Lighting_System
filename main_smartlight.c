#include "header.h"
#define LED1 (1 << 16)
#define SW1	(1 << 14)
#define SW2 (1 << 15)
#define TEST (1 << 17)

int main()
{
	u16 ret, op;
	IODIR0=LED1 | SW1 | SW2;
	spi0_init();
	uart1_init(9600);
	lcd_init();
	delay_ms(500);
	uart1_tx_string("SPI0 ADC\r\nLIGHT INTENSITY\r\n");
	while(1)
	{
		ret=mcp3204_adc_read(2);
		op=(ret*100)/4095;
		if(SW2==1)
		{
			IOSET0 = LED1;
			if(SW1==1)
			{
				IOSET0=TEST;
				if(op>80) 
				{
					IOSET0 = LED1;
								uart1_tx_string("LOW LIGHT | LED ON\r\n");
								UART1_Tx_Integer(ret);
								uart1_tx_string("\r\n");
								UART1_Tx_Integer(op);
								uart1_tx_string("%\r\n\r\n");
								
								lcd_string("LIGHT INTENSITY");
								lcd_cmd(0xC0);
								lcd_integer(op);
								lcd_data(37);
								delay_ms(200);
								lcd_cmd(0x01);
				} 
				else 
				{
					IOCLR0 = LED1;
								uart1_tx_string("HIGH LIGHT | LED OFF\r\n");
								UART1_Tx_Integer(ret);
								uart1_tx_string("\r\n");
								UART1_Tx_Integer(op);
								uart1_tx_string("%\r\n\r\n");
					
								lcd_string("LIGHT INTENSITY");
								lcd_cmd(0xC0);
								lcd_integer(op);
								lcd_data(37);
								delay_ms(200);
								lcd_cmd(0x01);
				}
			}
			else
				IOCLR0=TEST;
		}
		else
			IOCLR0 = LED1;
		delay_ms(200);
	}
}


