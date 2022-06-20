#ifndef SDE_MCP_INCLUDED
#define SDE_MCP_INCLUDED

#include <stdint.h>

#define MCP_A0 0x0
#define MCP_A1 0x1
#define MCP_A2 0x2
#define MCP_A3 0x3
#define MCP_A4 0x4
#define MCP_A5 0x5 
#define MCP_A6 0x6
#define MCP_A7 0x7
#define MCP_B0 0x8
#define MCP_B1 0x9
#define MCP_B2 0xA
#define MCP_B3 0xB
#define MCP_B4 0xC
#define MCP_B5 0xD
#define MCP_B6 0xE
#define MCP_B7 0xF

uint8_t mcp23S17_read_register(uint8_t addr);
void mcp23S17_write_register(uint8_t addr, uint8_t word);
void mcp23S17_pinMode(uint8_t gpio, uint8_t mode);
void mcp23S17_digitalWrite(uint8_t gpio, uint8_t level);
uint8_t mcp23S17_digitalRead(uint8_t gpio);

#endif