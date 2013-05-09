#ifndef __CIRCULAR_QUEUE_H
#define __CIRCULAR_QUEUE_H

typedef struct cirQueue{
	void* itemArray;
	unsigned char queueSize;
	unsigned char numItems;
	unsigned char itemSize;
	unsigned char checkIn;
	unsigned char checkOut;
} cirQueue_t;

extern void initCirQueue(cirQueue_t* q, void* itemArrayPt,
						 unsigned char numItems, unsigned char itemSize);
extern unsigned char cirEnqueue(cirQueue_t* q, void* item);
extern void* cirDequeue(cirQueue_t* q);
extern void* cirGetHead(cirQueue_t* q);
extern unsigned char cirDecrement(cirQueue_t* q);
extern unsigned char cirGetNumItems(cirQueue_t* q);
extern void cirClearQueue(cirQueue_t* q);

#endif
