#include "SPI.h"
#include "digital.h"
#include "LPC17xx.h"
#include "delay.h"
#define SPI_SSEL PIN(0,11)
#define SPI_SCLK PIN(0,15)
#define SPI_MOSI PIN(0,19)
#define SPI_MISO PIN(0,20)
#define SPI_DELAY 1
void spi_init()
{
	pinMode(SPI_SSEL, OUTPUT);			//SSEL - P0.11 - Amarelo
	pinMode(SPI_SCLK, OUTPUT);			//SCLK - P0.15 - Roxo
	pinMode(SPI_MOSI, OUTPUT);			//MOSI - P0.19 - Laranja
	pinMode(SPI_MISO, INPUT);			//MISO - P0.20 - Verde
	digitalWrite(SPI_SSEL, HIGH);		//SSEL - P0.11 - HIGH on init
	digitalWrite(SPI_SCLK, HIGH);		//SCLK - P0.15 - LOW on init
	digitalWrite(SPI_MOSI, LOW);		//MOSI - P0.19 - LOW on init

	/*
	* SPI opera no modo 1,1. De acordo com o datasheet do expansor
	* de portas, o CS deve ser alternado uma vez antes da primeira
	* comunicação com o MCP23S17 (Pg. 8 - Fig. 1-5)
	*/
	spi_ssel(LOW);
	delay_us(SPI_DELAY);
	spi_ssel(HIGH);
}

void spi_write(uint8_t data)
{
	for(int8_t bit = 7; bit >= 0; bit--)
	{
		digitalWrite(SPI_SCLK, LOW); //Iniciar SCLK em LOW / Preparar dados na borda de descida
		digitalWrite(SPI_MOSI, ((data >> bit) & 1)); //Enviar bit para o pino MOSI
		delay_us(SPI_DELAY); //Delay para garantir transição do pino MOSI
		digitalWrite(SPI_SCLK, HIGH); //SCLK em HIGH, dados serão lidos na borda de subida pelo slave
		delay_us(SPI_DELAY);
	}
}

uint8_t spi_read()
{
	uint8_t data = 0;
	for(int8_t bit = 7; bit >= 0; bit--)
	{
		/*
		* SCLK sempre estará em HIGH ao chamar essa rotina, logo
		* iniciar spi_read em LOW garantirá uma borda de descida,
		* permitindo que o slave carregue os dados antes da próxima borda de subida
		*/
		digitalWrite(SPI_SCLK, LOW);
		delay_us(SPI_DELAY);
		digitalWrite(SPI_SCLK, HIGH);
		delay_us(SPI_DELAY);
		data += digitalRead(SPI_MISO) << bit; //Dado deve ser recebido antes da próxima borda de descida
	}
	return data;
}

void spi_ssel(uint8_t state)
{
	digitalWrite(SPI_SSEL, state);
}