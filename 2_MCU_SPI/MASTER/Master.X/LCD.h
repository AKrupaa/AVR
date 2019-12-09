/* 
 * File:   LCD.h
 * Author: Arkadiusz
 *
 * Created on 24 listopada 2019, 12:52
 */

#ifndef LCD_H
#define	LCD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <avr/io.h>
#define LCD_ROWS 2
#define LCD_COLS 16

// RW na sta³e do masy

#define HD44780_RS C, 5
#define HD44780_E C, 4
#define HD44780_D4_PIN 3
#define HD44780_D4 C, 3
#define HD44780_D5_PIN 2
#define HD44780_D5 C, 2
#define HD44780_D6_PIN 1
#define HD44780_D6 C, 1
#define HD44780_D7_PIN 0
#define HD44780_D7 C, 0

#define SKLEJ(a,b)	a##b
//	przyklad:	SET(DDR, A, 0) |= (1<<(0)) czyli DDRA |= (1<<0);
#define SET_(REJESTR, KTORY, BIT) SKLEJ(REJESTR, KTORY) |= (1<<(BIT))
#define CLR_(REJESTR, KTORY, BIT) SKLEJ(REJESTR, KTORY) &= ~(1<<(BIT))
#define GET_(KTORY, BIT) SKLEJ(PIN, KTORY) & (1<<(BIT))

#define SET(REJESTR, ozaczenie_numer) SET_(REJESTR, ozaczenie_numer)
#define CLR(REJESTR, ozaczenie_numer) CLR_(REJESTR, ozaczenie_numer)

//spisane z dokumentacji https://www.sparkfun.com/datasheets/LCD/HD44780.pdf   24 strona

#define LCD_CLEAR					0x01
#define LCD_HOME					0x02
#define LCDC_ENTRY_MODE				0x04
	#define LCD_EM_SHIFT_CURSOR		    0x00
	#define LCD_EM_SHIFT_DISPLAY	 	0x01
	#define LCD_EM_LEFT		   			0x00
	#define LCD_EM_RIGHT				0x02
#define LCD_ONOFF					0x08
	#define LCD_DISP_ON				    0x04
	#define LCD_CURSOR_ON				0x02
	#define LCDC_CURSOR_OFF				0x00
	#define LCDC_BLINK_ON				0x01
	#define LCDC_BLINK_OFF				0x00
#define LCD_SHIFT					0x10
	#define LCDC_SHIFT_DISP				0x08
	#define LCDC_SHIFT_CURSOR			0x00
	#define LCDC_SHIFT_RIGHT			0x04
	#define LCDC_SHIFT_LEFT				0x00
#define LCD_FUNC					0x20
	#define LCD_8_BIT					0x10
	#define LCD_4_BIT					0x00
	#define LCDC_TWO_LINE				0x08
	#define LCDC_FONT_5x10				0x04
	#define LCDC_FONT_5x7				0x00
#define LCDC_SET_CGRAM				0x40
#define LCDC_SET_DDRAM				0x80

/*
DDRAM address
*/
#define LCD_LINE1 		0x00
#define LCD_LINE2 		0x40

void lcd_sendHalf(uint8_t data);
void lcd_write_byte(uint8_t data);
void lcd_write_cmd(uint8_t cmd);
void lcd_char(char data);

void lcd_pins_init(void);
//https://www.sparkfun.com/datasheets/LCD/HD44780.pdf 46strona - inicjalizacja dla 4-bit
void lcd_init(void);

//usawienia kursora - aby nie zmieniac czesci, ktora rzeczywiscie nie bedzie sie zmieniac tj. Temp(*C) = 
void lcd_locate(uint8_t x, uint8_t y);

void lcd_str(char *text);

#ifdef	__cplusplus
}
#endif

#endif	/* LCD_H */

