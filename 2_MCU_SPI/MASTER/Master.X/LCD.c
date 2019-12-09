#include "LCD.h"
#include <avr/io.h>
#define F_CPU 20000000UL
#include <util/delay.h>
#include <util/atomic.h>

/* 
The data transfer between the HD44780U and the MPU is completed after the 4-bit data has been transferred twice. 
As for the order of data transfer, the four high order bits (for 8-bit operation,DB4 to DB7) are transferred 
before the four low order bits (for 8-bit operation, DB0 to DB3).
*/
// https://www.sparkfun.com/datasheets/LCD/HD44780.pdf 22 strona wykresiki :)
void lcd_sendHalf(uint8_t data){
	SET(PORT, HD44780_E);
	
	//SET(PORT, HD44780_D7)
	//SET(PORT, C, 0) |= (1<<(0)) czyli:
	//PORTC |= (1<<0);
	
	PORTD |= ( (data & 0x08) << HD44780_D7_PIN );
	PORTD |= ( (data & 0x04) << HD44780_D6_PIN );
	PORTD |= ( (data & 0x02) << HD44780_D5_PIN );
	PORTD |= ( (data & 0x01) << HD44780_D4_PIN );
	
	CLR(PORT, HD44780_E);
}

void lcd_write_byte(uint8_t data){
	lcd_sendHalf(data>>4);
	lcd_sendHalf(data);
}

void lcd_write_cmd(uint8_t cmd){
	CLR(PORT, HD44780_RS);
	
	lcd_write_byte(cmd);
}

void lcd_char(char data){
	SET(PORT, HD44780_RS);
	
	lcd_write_byte(data);
}

void lcd_pins_init(void){
	SET(DDR, HD44780_RS);
	SET(DDR, HD44780_E);
	SET(DDR, HD44780_D4);
	SET(DDR, HD44780_D5);
	SET(DDR, HD44780_D6);
	SET(DDR, HD44780_D7);
}
	

// https://www.sparkfun.com/datasheets/LCD/HD44780.pdf 42 strona, również warto
//https://www.sparkfun.com/datasheets/LCD/HD44780.pdf 46 strona - inicjalizacja dla 4-bit
void lcd_init(void){
	lcd_pins_init();
	
	_delay_ms(15);
 
	CLR(PORT, HD44780_E);
	CLR(PORT, HD44780_RS);
 
	lcd_sendHalf(0x03);
	_delay_ms(4);
	_delay_us(100);
	lcd_sendHalf(0x03);
	_delay_us(100);
	lcd_sendHalf(0x03);
	_delay_us(100);
	lcd_sendHalf(0x02);
	_delay_us(100);
 
	//ustawienia
	lcd_write_cmd( LCD_FUNC | LCD_4_BIT | LCDC_TWO_LINE | LCDC_FONT_5x7);
	lcd_write_cmd( LCD_ONOFF | LCD_DISP_ON );
	lcd_write_cmd( LCD_CLEAR );
	_delay_ms(5);
	lcd_write_cmd( LCDC_ENTRY_MODE | LCD_EM_SHIFT_CURSOR | LCD_EM_RIGHT );
}


//usawienia kursora - aby nie zmieniac czesci, ktora rzeczywiscie nie bedzie sie zmieniac tj. Temp(*C) = 
void lcd_locate(uint8_t x, uint8_t y){
	switch(y){	//rzad - 0, 1?
	
		case 0:
			lcd_write_cmd( LCDC_SET_DDRAM | (LCD_LINE1 + x) );		//x oznacza, która pozycja (kolumna)
			break;
 
		case 1:
			lcd_write_cmd( LCDC_SET_DDRAM | (LCD_LINE2 + x) );
			break;
	}
}

void lcd_str(char *text){
	while(*text)
		lcd_char(*text++);
}