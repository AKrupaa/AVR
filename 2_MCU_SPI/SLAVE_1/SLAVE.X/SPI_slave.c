/*
 * File:   SPI_slave.c
 * Author: Arkadiusz
 *
 * Created on 23 listopada 2019, 20:21
 */

#include <xc.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "LM35.h"
#include "SPI_utilities.h"

// -----------------------------------------------------------------------------

int main() {
    
    SPI_SlaveInit();
    ADCinit();
    sei();
    
    unsigned char temperature;
    
	while(1) {
        temperature = Get_Temperature();
        SPI_SendByte(temperature);
    }
    
    return 0;
}



/*
 //Function to send and receive data for both master and slave

unsigned char spi_tranceiver (unsigned char data)
{
    // Load data into the buffer
    SPDR = data;
 
    //Wait until transmission complete
    while(!(SPSR & (1<<SPIF)));   // Return received data

  return(SPDR);
}
 */