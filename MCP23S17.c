#include "MCP23S17.h"
#include "SPI.h"
#include "digital.h"
#include "delay.h"

const uint8_t GPIO_ADDR[] = {0x12, 0x13};
const uint8_t IODIR_ADDR[] = {0x00, 0x01};
const uint8_t GPPU_ADDR[] = {0x0C, 0x0D};

uint8_t mcp23S17_read_register(uint8_t addr)
{
	uint8_t ret;
	spi_ssel(LOW);		//Ativa barramento SPI
	spi_write(0x41);	//Endereçamento do dispositivo + Bit de leitura
	spi_write(addr);	//Escreve endereço do registrador
	ret = spi_read();	//Lê byte enviado pelo SPI
	spi_ssel(HIGH);		//Desativa barramento SPI
	return ret;
}

void mcp23S17_write_register(uint8_t addr, uint8_t word)
{
	spi_ssel(LOW);		//Ativa barramento SPI
	spi_write(0x40);	//Endereçamento do dispositivo + Bit de escrita
	spi_write(addr);	//Escreve endereço do registrador
	spi_write(word);	//Envia byte a ser escrito
	spi_ssel(HIGH);		//Desativa barramento SPI
}

void mcp23S17_pinMode(uint8_t gpio, uint8_t mode)
{
	uint8_t pin = gpio & 7;
	uint8_t port = (gpio >> 3) & 1;
	uint8_t port_read = mcp23S17_read_register(IODIR_ADDR[port]);
	if(mode == INPUT) port_read |= 1 << pin;
	else port_read &= ~(1 << pin);
	mcp23S17_write_register(IODIR_ADDR[port], port_read);
}

void mcp23S17_digitalWrite(uint8_t gpio, uint8_t level)
{
	uint8_t pin = gpio & 7;
	uint8_t port = (gpio >> 3) & 1;
	uint8_t port_read = mcp23S17_read_register(GPIO_ADDR[port]);
	if(level) port_read |= 1 << pin;
	else port_read &= ~(1 << pin);
	mcp23S17_write_register(GPIO_ADDR[port], port_read);
}

uint8_t mcp23S17_digitalRead(uint8_t gpio)
{
	uint8_t pin = gpio & 7;
	uint8_t port = (gpio >> 3) & 1;
	uint8_t port_read = mcp23S17_read_register(GPIO_ADDR[port]);
	return (port_read >> pin) & 1;
}

void mcp23S17_portPullup(uint8_t gpio, uint8_t state)
{
	uint8_t pin = gpio & 7;
	uint8_t port = (gpio >> 3) & 1;
	uint8_t port_read = mcp23S17_read_register(GPPU_ADDR[port]);
	if(state) port_read |= 1 << pin;
	else port_read &= ~(1 << pin);
	mcp23S17_write_register(GPPU_ADDR[port], port_read);
}