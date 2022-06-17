#include "SPI.h"
#include "LPC17xx.h"
#define T_SPISCK 1000000
void spi_init()
{
    unsigned int PCLK = SystemCoreClock/4; // PCLK_SPI sera mantido em CCLK/4
    PCONP |= 1 << 8; // Garantindo que o SPI esteja habilitado
    PCLKSEL0 &= ~(3 << 16); // Garantindo que PCLK_SPI seja CCLK/4
    PINSEL0 |= (3 << 30); // Seleção do modo do pino P0.15 para SCK
    PINSEL1 |= 63; // Seleção do modo dos pinos P0.16, P0.17 e P0.18 para  SSEL/MISO/MOSI
    //ISER0 |= (1 << 13); //Habilitando interrupções para SPI
    uint8_t CR0 = PCLK/(T_SPISCK);
    if(!(CR0 % 2)) CR0++; //SPCCR0 deve ser um número par
    SPCCR0 = CR0;
    S0SPCR = 0000 0 0 1 0 0 0 0;
}

void spi_write(unsigned char data)
{
    S0SPDR = data;
    while(!((S0SPSR >> 7) & 1));
}

unsigned char spi_read()
{
    
}