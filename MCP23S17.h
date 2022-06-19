#ifndef SDE_MCP_INCLUDED
#define SDE_MCP_INCLUDED

void mcp23S17_init();
uint8_t mcp23S17_read_register(uint8_t addr);
void mcp23S17_write_register(uint8_t addr, uint8_t word);

#endif