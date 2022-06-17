#ifndef SDE_MCP_INCLUDED
#define SDE_MCP_INCLUDED

void mcp23S17_init();
void mcp23S17_configura_pino(uint8_t pin, uint8_t mode);
void mcp23S17_escreve_pino(uint8_t pin, uint8_t level);
void mcp23S17_le_pino(uint8_t pin);

#endif