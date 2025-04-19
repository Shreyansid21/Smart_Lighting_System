#include "header.h"
#define RS (1<<17)					//P1.17
#define RW (1<<18)					//P1.18
#define EN (1<<19)					//P1.19
#define LCD4 0x00FE0000			//P1.20 P1.21 P1.22 P1.23

void lcd_data(u8 data)
{
	u32 temp;
	IOCLR1|=LCD4;
	temp=(data&0xF0)<<16;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;	
		delay_ms(2);
	IOCLR1=EN;
	
	IOCLR1|=LCD4;
	temp=(data&0x0F)<<20;
	IOSET1=temp;
	IOSET1=RS;
	IOCLR1=RW;
	IOSET1=EN;	
		delay_ms(2);
	IOCLR1=EN;
}

void lcd_cmd(u8 cmd)
{
	u32 temp;
	IOCLR1|=LCD4;
	temp=(cmd&0xF0)<<16;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;	
		delay_ms(2);
	IOCLR1=EN;
	
	IOCLR1|=LCD4;
	temp=(cmd&0x0F)<<20;
	IOSET1=temp;
	IOCLR1=RS;
	IOCLR1=RW;
	IOSET1=EN;	
		delay_ms(2);
	IOCLR1=EN;
}

void lcd_init(void)
{
	IODIR1|=LCD4;
	PINSEL2|=0;
	lcd_cmd(0x02);
	lcd_cmd(0x03);
	lcd_cmd(0x28);
	lcd_cmd(0x0C);
	lcd_cmd(0x01);
}

void lcd_string(s8 *ptr)
{
	while(*ptr!=0)
	{
		lcd_data(*ptr);
		ptr++;
		delay_ms(2);
	}
}

void lcd_integer(s32 num)
{
	s32 a[16],i=0;
	if(num==0)
		lcd_data('0');
	if(num<0)
	{
		lcd_data('-');
		num=-num;
	}
	while(num>0)
	{
		a[i]=num%10;
		num=num/10;
		i++;
	}
	for(--i;i>=0;i--)
	{
		lcd_data(a[i]+48);
	}
}

void lcd_float(f32 f,s32 ndp)
{
	s32 i,j;
	if(f<0.0)
	{
		lcd_data('-');
		f=-f;
	}
	i=f;
	lcd_integer(i);
	lcd_data('.');
	for(j=0;j<ndp;j++)
	{
		f=(f-i)*10;
		i=f;
		lcd_data(i+48);
	}
}

void lcd_bin(u16 n)
{
	s8 bit=15;
	while(bit>=0)
	{
	lcd_data(((n>>bit)&1)+48);
	bit--;
	}
}

void lcd_hex(u32 n)
{
	s32 i=0,nibble;
	u8 a[8];
	lcd_string((s8*)"0x");
	if(n==0)
		lcd_data('0');
	else
	{
		while(n)
		{
		nibble=n%16;
		nibble=(nibble>9)?((nibble-10)+'A'):(nibble+48);
		a[i++]=nibble;
		n/=16;
		}
		for(--i;i>=0;i--)
		{
		lcd_data(a[i]);
		}
	}
}

void lcd_oct(u32 n)
{
	u8 a[15];
	s32 i=0,x;
	if(n==0)
		lcd_data('0');
	else
	{
		while(n)
		{
		x=n%8;
		a[i++]=x+48;
		n/=8;
		}
		for(--i;i>=0;i--)
		lcd_data(a[i]);
	}
}

u8 c[]={0x0e, 0x0e, 0x04, 0x04, 0x1f, 0x04, 0x0a, 0x0a}; 
void lcd_cgram_init(void)
{
	s32 i;
	lcd_cmd(0x40);
	for(i=0;i<=7;i++)
	{
		lcd_data(c[i]);
	}
}



