// EXEMPLO DE UM Pisca Pisca que usa a Lampada do kit
// para compilar:  
//                    make
// para gravar na placa (usando o bootloader): 
//                   lpc21isp -control -bin main.bin /dev/ttyUSB0 115200 12000
//
// para gravar na placa (usando o JTAG)
//                   openocd -f lpc1768.cfg
// abrir outro shell
// telnet localhost 4444
// > reset halt
// > flash write_image erase main.bin 0x0 bin

#include <stdint.h>
#include <stdio.h>
#include "LPC17xx.h"
#include "digital.h"
#include "periodica.h"
#include "delay.h"
#include "seg.h"
#include "SPI.h"
#include "MCP23S17.h"
int main() 
{
  SystemInit();
  periodica_init();
  delay_init();
  seg_init( );
  spi_init();
  delay_ms(1000);

  mcp23S17_pinMode(MCP_A7, OUTPUT);
  mcp23S17_pinMode(MCP_A6, OUTPUT);
  mcp23S17_pinMode(MCP_A5, OUTPUT);
  mcp23S17_pinMode(MCP_A4, OUTPUT);
  mcp23S17_pinMode(MCP_A3, OUTPUT);
  mcp23S17_pinMode(MCP_A2, INPUT);
  mcp23S17_portPullup(MCP_A2, ON);

  uint8_t buttonPressed = 1, contador = 1, toggle = 1;
  while(1)
  {

    mcp23S17_digitalWrite(MCP_A3, (contador >> 4) & 1);
    mcp23S17_digitalWrite(MCP_A4, (contador >> 3) & 1);
    mcp23S17_digitalWrite(MCP_A5, (contador >> 2) & 1);
    mcp23S17_digitalWrite(MCP_A6, (contador >> 1) & 1);
    mcp23S17_digitalWrite(MCP_A7, (contador) & 1);
    uint8_t bit = mcp23S17_digitalRead(MCP_A2);
    seg_apresenta(contador);
    
    if(bit && buttonPressed)
    {
        buttonPressed = 0;
    }
    else if(!bit && !buttonPressed)
    {
        buttonPressed = 1;
        contador = 0;
        toggle = !toggle;
        contador = toggle;
    }
    if(toggle)
    {
      if(contador < 16) contador = (contador << 1);
      else contador = 1;
    }
    else
    {
      contador = (contador + 1) % 32;
    }
    delay_ms(100);
  }
}

