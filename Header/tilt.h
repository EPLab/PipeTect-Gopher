#ifndef __TILT_H
#define __TILT_H

extern unsigned short adis16209_get_status(void);
extern void adis16209_get_accl(short* x, short* y);

#endif
