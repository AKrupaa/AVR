#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
    #define F_CPU 20000000UL
#include <util/delay.h>
#include "SPI_utilities.h"
#include "HD44780.h"
#include "ftoa.h"

    #define VREF 5

static inline void SPI_Set_SS() {
	PORTB |= (1<<PB2);
}

static inline void SPI_Reset_SS() {
	PORTB &= ~(1<<PB2);
}

// -----------------------------------------------------------------------------

int main() {
   LCD_Initialize();
   SPI_Master_Init();
   LCD_Home();
   sei();
   
   	float Vin;
	char String_Value_Of_Temperature[5];
    char foo[] = "Temperatura";
    char foo1[] = "wynosi ";
    unsigned char ADC_r;
   
	while(1) {
        SPI_Reset_SS();
        
        ADC_r = SPI_TransferByte(0x01);
        
        SPI_Set_SS();
        
        Vin = ( (float)ADC_r * (float)VREF ) / (float)256;
        Vin = Vin / 10.0 * 1000.0;  //wzór na uzyskanie warto?ci w *C    Vin / 10 * 1000
        LCD_Home();
        ftoa(Vin, String_Value_Of_Temperature, 2);
        LCD_WriteText(foo);
        LCD_GoTo(0,1);
        LCD_WriteText(foo1);
        LCD_WriteText(String_Value_Of_Temperature);
        LCD_WriteData(0b11011111);
        LCD_WriteData(0b01000011);
	}
    
    return 0;
}
