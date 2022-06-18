#include "SPI.h"
#include "LPC17xx.h"
#define T_SPISCK 10000
#define PCSPI_bit 8
#define PCLK_SPI_bit 16
void spi_init()
{
    unsigned int PCLK = SystemCoreClock/4; // PCLK_SPI sera mantido em CCLK/4
    LPC_SC->PCONP |= 1 << PCSPI_bit; // Garantindo que o SPI esteja habilitado
    LPC_SC->PCLKSEL0 &= ~(3 << 16); // Garantindo que PCLK_SPI seja CCLK/4
    LPC_PINCON->PINSEL0 |= (3 << 30); // Seleção do modo do pino P0.15 para SCK
    LPC_PINCON->PINSEL1 |= 63; // Seleção do modo dos pinos P0.16, P0.17 e P0.18 para  SSEL/MISO/MOSI
    //ISER0 |= (1 << 13); //Habilitando interrupções para SPI
    uint8_t CR0 = PCLK/(T_SPISCK);
    if(!(CR0 % 2)) CR0++; //SPCCR0 deve ser um número par
    LPC_SPI->SPCCR = CR0;
    LPC_SPI->SPCR = 00000010000;
}

void spi_write(unsigned char data)
{
    LPC_SPI->SPDR = data;
    while(!((LPC_SPI->SPSR >> 7) & 1));
}

unsigned char spi_read()
{
    
}