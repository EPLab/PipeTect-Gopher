#include "can_outgoing_queue.h"
#include "circular_queue.h"

#ifdef __CIR_USED__
canPacket_t canOutgoingQueueItemArray[CAN_OUTGOING_QUEUE_SIZE];
cirQueue_t canOutgoingQueue;

void initCanOutgoingQueue(void) {
    initCirQueue((void*) &canOutgoingQueue,
            (void*) canOutgoingQueueItemArray,
            CAN_OUTGOING_QUEUE_SIZE,
            sizeof (canPacket_t));
}

unsigned char canEnqueueOutgoing(canPacket_t* msg) {
    return cirEnqueue(&canOutgoingQueue, (void*) msg);
}

canPacket_t* canGetOutgoingHead(void) {
    return (canPacket_t*) cirGetHead(&canOutgoingQueue);
}

unsigned char canDecOutgoing(void) {
    return cirDecrement(&canOutgoingQueue);
}

#else

#include "string.h"

canPacket_t canOutgoingQueueItemArray[CAN_OUTGOING_QUEUE_SIZE];
volatile unsigned char co_index_in;
volatile unsigned char co_index_out;
volatile unsigned char co_count;

void initCanOutgoingQueue(void) {
    co_index_in = 0;
    co_index_out = 0;
    co_count = 0;
}

unsigned char canEnqueueOutgoing(unsigned char id,
        unsigned char* data,
        unsigned char length) {
    if (co_count < CAN_OUTGOING_QUEUE_SIZE) {
        canOutgoingQueueItemArray[co_index_in].ID = id;
        canOutgoingQueueItemArray[co_index_in].dataLength = length;
        memcpy((void*) (canOutgoingQueueItemArray[co_index_in].data), (void*) data, length);
        ++co_index_in;
        ++co_count;
        co_index_in %= CAN_OUTGOING_QUEUE_SIZE;
        return 1;
    }
    return 0;
}

canPacket_t* canGetOutgoingHead(void) {
    if (co_count) {
        return &canOutgoingQueueItemArray[co_index_out];
    }
    return 0;
}

unsigned char canDecOutgoing(void) {
    if (co_count) {
        ++co_index_out;
        --co_count;
        co_index_out %= CAN_OUTGOING_QUEUE_SIZE;
    }
    return co_count;
}

#endif
