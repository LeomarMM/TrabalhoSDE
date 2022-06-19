#ifndef SDE_SPI_INCLUDED
#define SDE_SPI_INCLUDED

#include <stdint.h>

void spi_init();
void spi_write(uint8_t data);
uint8_t spi_read();
void spi_ssel(uint8_t state);

#endif