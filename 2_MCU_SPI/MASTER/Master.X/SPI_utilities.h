//Only for my purposes A.K.

#define FALSE	0
#define TRUE	-1

// SPI interface initializer as Master
void SPI_Master_Init();

// SPI interface initializer as Slave
void SPI_SlaveInit(void);


// SPI_SendByte(unsigned char data) waits until the SPI interface is ready
// and then sends a single byte over the SPI port.  This command
// does not receive anything.
void SPI_SendByte(unsigned char data);

// SPI_TransferByte(unsigned char data) waits until the SPI interface is ready
// and then sends a single byte over the SPI port.  The function also
// returns the byte that was received during transmission.
unsigned char SPI_TransferByte(unsigned char data);