#ifndef SDE_SPI_INCLUDED
#define SDE_SPI_INCLUDED

void spi_init();
void spi_write(unsigned char data);
unsigned char spi_read();

#endif