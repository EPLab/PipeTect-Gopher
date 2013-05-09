#ifndef __CAN_PACKET_H
#define __CAN_PACKET_H

#include "ECANPoll.h"

#define CAN_MAX_DATA_LENGTH 8

typedef struct canPacket{
	unsigned char ID;
	unsigned char data[CAN_MAX_DATA_LENGTH];
	unsigned char dataLength;
	ECAN_RX_MSG_FLAGS msgFlags;
#if ECAN_CAPTURE_MODE_VAL == ECAN_CAPTURE_MODE_ENABLE
	unsigned long timeStamp;
#endif
} canPacket_t;

#endif
