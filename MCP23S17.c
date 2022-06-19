#include "MCP23S17.h"
#include "SPI.h"
#include "digital.h"
#include "delay.h"
void mcp23S17_init()
{
	mcp23S17_write_register(0x0A, 0x80); //IOCON.BANK = 1
}
uint8_t mcp23S17_read_register(uint8_t addr)
{

}
void mcp23S17_write_register(uint8_t addr, uint8_t word)
{
	spi_ssel(LOW);		//Ativa dispositivo SPI
	spi_write(0x40);	//Endereçamento do dispositivo + Bit de escrita
	spi_write(addr);	//Escreve endereço do registrador
	spi_write(word);	//Envia byte a ser escrito
	spi_ssel(HIGH);		//Desativa dispositivo SPI
}