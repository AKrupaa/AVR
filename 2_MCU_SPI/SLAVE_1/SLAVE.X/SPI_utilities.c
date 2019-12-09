//Only for my purposes A.K.

#include <avr/io.h>
#include <avr/interrupt.h>

#include "SPI_utilities.h"

// global variables
volatile unsigned char spiTransferComplete;

// SPI interrupt service handler
ISR(SPI_STC_vect) {
	spiTransferComplete = TRUE;
}

void SPI_Master_Init() {
	PORTB |= (1<<PB5);  // Set SCK high
    DDRB |= (1<<PB5);   // Set SCK as output
    DDRB &= ~(1<<PB4);  // Set MISO as input
    DDRB |= (1<<PB3);   // Set MOSI as output
    DDRB |= (1<<PB2);   // Set ~SS as output
    
    SPCR = (1<<MSTR);   // Set SPI as master
    SPCR |= (1<<SPR0) | (1<<SPR1); // f = F_cpu / 16
    SPCR |= (1<<SPE);   // Enable SPI
    SPCR |= (1<<SPIE);  // Enable Interrupt
	SPSR; // Skasuj flag? SPIF
	spiTransferComplete = TRUE; // TRUE as 0, FALSE as -1
}

void SPI_SlaveInit(void) {
	// When the SPI is configured as a Slave, the Slave Select (SS) pin is always input.
	// Set MISO output, all others input
    
	DDRB |= (1<<PB4);   // Set MISO as output
    
    SPCR |= (1<<SPE);   // Enable SPI
    SPCR |= (1<<SPIE);  // Enable Interrupt

	SPSR; // Skasuj flag? SPIF
	spiTransferComplete = TRUE; // TRUE as 0, FALSE as -1
}


void SPI_SendByte(unsigned char data) {
    // send a byte over SPI and ignore reply
    while(!spiTransferComplete);
		spiTransferComplete = FALSE;
        SPDR = data;
}

unsigned char SPI_TransferByte(unsigned char data) {
    // send the given data
	spiTransferComplete = FALSE;
	SPDR = data;
	// wait for transfer to complete
	while(!spiTransferComplete);
    // return the received data
	return SPDR;
}