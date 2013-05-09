#ifndef PACKET_H__
#define PACKET_H__

#define PKT_DATA_SIZE 30

//--------------------PACKET TYPE----------------------//
#define PKT_INI		0x01	//Start an image
#define	PKT_DATA	0x02	//Image data packet type
#define PKT_CMD		0x03

//------------------Data packet format-----------------//
typedef struct packet_format {
	unsigned char type;						//Packet type
	unsigned char reserved;
	unsigned char img_data[PKT_DATA_SIZE];
} packet_format_t;

#endif
