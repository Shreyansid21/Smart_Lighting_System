#include <lpc21xx.h>
#include "typedef.h"

extern void delay_us(u32 us);
extern void delay_ms(u32 ms);
extern void delay_s(u32 s);

extern void lcd_data(u8 data);
extern void lcd_cmd(u8 cmd);
extern void lcd_init(void);

extern void lcd_bin(u16 n);
extern void lcd_hex(u32 n);
extern void lcd_oct(u32 n);
extern void lcd_integer(s32 num);
extern void lcd_float(f32 f,s32 ndp);

extern void lcd_string(s8 *ptr);
extern void lcd_display(s8 *str, u8 row, u8 col);

extern void lcd_cgram_init(void);

extern void adc_init(void);
extern u32 adc_read(u32 ch_num);
extern u16 mcp3204_adc_read(u8 ch_num);

extern void uart0_init(u32 baud);
extern void uart0_tx_char(u8 data);
extern void uart0_tx_string(s8 *ptr);

extern u8 uart0_rx_char(void);
extern void uart0_rx_string(s8 *ptr,s32 max_bytes);

extern void uart1_init(u32 baud);
extern void uart1_tx_char(u8 data);
extern void uart1_tx_string(s8 *ptr);

extern u8 uart1_rx_char(void);
extern void uart1_rx_string(s8 *ptr,s32 max_bytes);

extern void UART1_Tx_Integer(int number);

extern void i2c_init(void);
extern void i2c_byte_write_frame(u8 sa,u8 mr,u8 data);
extern u8 i2c_byte_read_frame(u8 sa,u8 mr);

extern void config_VIC(void);
extern void en_uart0_intr(void);

extern void config_VIC(void);
extern void en_uart1_intr(void);

extern void spi0_init(void);
extern u8 spi0(u8 data);
