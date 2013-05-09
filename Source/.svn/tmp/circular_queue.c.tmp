#include "circular_queue.h"
#include "string.h"

void initCirQueue(cirQueue_t* q, void* itemArrayPt, unsigned char numItems, unsigned char itemSize) {
    if (q && itemArrayPt) {
        q->itemArray = itemArrayPt;
        q->queueSize = numItems * itemSize;
        q->numItems = 0;
        q->itemSize = itemSize;
        q->checkIn = 0;
        q->checkOut = 0;
    }
}

unsigned char cirEnqueue(cirQueue_t* q, void* item) {
    if (q->numItems < q->queueSize) {
        memcpy((void*) (q->itemArray + q->checkIn), item, q->itemSize);
        q->checkIn += q->itemSize;
        if (q->checkIn >= q->queueSize) {
            q->checkIn = 0;
        }
        ++q->numItems;
        return 1;
    }
    return 0;
}

void* cirDequeue(cirQueue_t* q) {
    void* ret;

    if (q->numItems) {
        ret = q->itemArray + q->checkOut;
        q->checkOut += q->itemSize;
        if (q->checkOut >= q->queueSize) {
            q->checkOut = 0;
        }
        --q->numItems;
        return ret;
    }
    return NULL;
}

void* cirGetHead(cirQueue_t* q) {
    void* ret;

    if (q->numItems) {
        ret = q->itemArray + q->checkOut;
        return ret;
    }
    return NULL;
}

unsigned char cirDecrement(cirQueue_t* q) {
    if (q->numItems) {
        q->checkOut += q->itemSize;
        if (q->checkOut >= q->queueSize) {
            q->checkOut = 0;
        }
        --q->numItems;
        return 1;
    }
    return 0;
}

unsigned char cirGetNumItems(cirQueue_t* q) {
    return q->numItems;
}

void cirClearQueue(cirQueue_t* q) {
    q->checkIn = 0;
    q->checkOut = 0;
    q->numItems = 0;
}
