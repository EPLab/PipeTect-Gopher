#ifndef __canOutgoingQueue_H
#define __canOutgoingQueue_H

#include "can_packet.h"

#pragma udata CAN_OUT_MEM
#define CAN_OUTGOING_QUEUE_SIZE 8

extern void initCanOutgoingQueue(void);
#ifdef __CIR_USED__
extern unsigned char canEnqueueOutgoing(canPacket_t* msg);
#else
extern unsigned char canEnqueueOutgoing(unsigned char id, 
								 unsigned char* data, 
								 unsigned char length);
#endif
extern canPacket_t* canDequeueOutgoing(void);
extern canPacket_t* canGetOutgoingHead(void);
extern unsigned char canDecOutgoing(void);

#endif
