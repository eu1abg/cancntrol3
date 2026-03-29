#ifndef CAN_MCP_H
#define CAN_MCP_H

#include <SPI.h>
#include <mcp2515.h>

extern MCP2515 mcp2515;
extern struct can_frame canMsg;
extern struct can_frame canMsg1;
extern struct can_frame canMsg2;

void CAN_init();
void CAN_read();
















#endif