#include "can_mcp.h"

MCP2515 mcp2515(15);
struct can_frame canMsg;
struct can_frame canMsg1;
struct can_frame canMsg2;

void CAN_init() {
    mcp2515.reset();
    mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
    mcp2515.setNormalMode();
}

void CAN_read() {
    if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
        // Можно оставить отображение на OLED, если нужно
    }
}