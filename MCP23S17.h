#ifndef SDE_MCP_INCLUDED
#define SDE_MCP_INCLUDED

#include <stdint.h>
#define OFF 0
#define ON 1

enum 
{
	MCP_A0, MCP_A1, MCP_A2, MCP_A3, MCP_A4, MCP_A5, MCP_A6, MCP_A7,
	MCP_B0, MCP_B1, MCP_B2, MCP_B3, MCP_B4, MCP_B5, MCP_B6, MCP_B7
};

uint8_t mcp23S17_read_register(uint8_t addr);
void mcp23S17_write_register(uint8_t addr, uint8_t word);
void mcp23S17_pinMode(uint8_t gpio, uint8_t mode);
void mcp23S17_digitalWrite(uint8_t gpio, uint8_t level);
uint8_t mcp23S17_digitalRead(uint8_t gpio);
void mcp23S17_portPullup(uint8_t gpio, uint8_t state);

#endif