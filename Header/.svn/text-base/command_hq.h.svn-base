#ifndef __COMMAND_HQ_H
#define __COMMAND_HO_H

// change Sensor ID here
#define MY_ID 0x02

typedef enum{
	REQ_ACCEL_DATA = 0,
	START_ACCEL_UPLOAD = 1,
	STOP_ACCEL_UPLOAD = 2,
	TAKE_SNAP_SHOT = 9,
	GET_IMAGE_SIZE = 10,
	START_FETCHING_IMAGE = 11,
	CONFIRM_END_OF_RECEPTION = 12,
	REQ_IMAGE_DATA_PACKET = 13
} comHQ_t;	

extern void deployCommandHQ(unsigned char id);

#endif
