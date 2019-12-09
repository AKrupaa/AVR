#include <avr/io.h>
#include <avr\interrupt.h>
#include "LM35.h"

///*
// * slave (for testing)
// * ADC5 in USE!
// */
//

//
//
//
//
//	volatile float Vin;
//	volatile char tab[20];
//
//ISR(ADC_vect) {
//	Vin = ((float)ADC*(float)Vref)/(float)1024;
//	LCD_Home();
//	ftoa((float)Vin/10*1000, tab, 3);
//	LCD_WriteText(tab);
//}
//
///*
// * slave (for testing)
// * ADC5 in USE!
// */

volatile unsigned char ADC_Value;		//volatile bo u?ywamy zmiennej w przerwaniach i programie ;) - optymalizacja by to zignorowa?a

void ADCinit() {
    ADMUX = (1<<REFS0) | (0b0101) | (1<<ADLAR); //U?ywam ADC5
	ADCSRA = (1<<ADEN) | (1<<ADATE) | (1<<ADIE);
	ADCSRA |= (1<<ADSC);
}

//ISR_NOBLOCK __attribute__((interrupt)) => oznacza, ze nie bedzie wylaczalo SEI() na czas wykonywania przerwania od ADC, bo SPI stanowi priorytet
ISR(ADC_vect) {
	volatile unsigned char ADCaccumulator;
    
	ADCaccumulator = ADCH;
	ADC_Value = ADCaccumulator;
}

unsigned char Get_Temperature() {
    return ADC_Value;
}