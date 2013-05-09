#include "command_hq.h"
#include <p18cxxx.h>
#include "task_uid_map.h"
#include "switcher.h"
#include "can_outgoing_queue.h"
//#include "LIS3LV02DQ.h"
#include "string.h"
//#include "jpeg_module.h"
#include "accel_handler.h"
#include "platform.h"
#include "can_parameter.h"

unsigned char tHandle_CHQ = 0;
//unsigned char canMode;
//unsigned short tempNum = 0;

unsigned char myID = 0x02;
const unsigned char broadcastID = 0xFF;

//BYTE myMask[] = {0x00, 0x00, 0xE0, 0x1F};
//BYTE myFilter1[] = {0x00, 0x00, 0x00, 0x01};	// 0x0008
//BYTE myFilter2[] = {0x00, 0x00, 0xE0, 0x1F};
//canPacket_t* sendMsg = NULL;


#if ECAN_INIT_MODE == ECAN_INIT_LOOPBACK
static void sendDummy(void);
#endif

void commandHandler(unsigned char tid, void* msg) {
    unsigned char data[CAN_MAX_DATA_LENGTH];
    //canPacket_t recvMsg;
    unsigned long id;
    unsigned char temp_data[8];
    unsigned char leng;
    unsigned char flag;
    canPacket_t* sendMsg = NULL;
    //unsigned short accelRead[3];
    unsigned char* temp;
    //unsigned int id;
    unsigned char com;

    while (ECANReceiveMessage(&id, temp_data, &leng, (ECAN_RX_MSG_FLAGS*) & flag)) {
        temp = (unsigned char*) (&id); // >> 21;
        com = (temp[2] >> 5); // & 0x07;
        com |= temp[3] << 3; // & 0xF8;

        if ((com == myID) || (com == 0xFF)) {
            com = temp[2] & 0x1F;
            switch (com) {
                case REQ_ACCEL_DATA:
                    uploadAccel(myID);
                    YEB_CanLED_OFF();
                    break;
                case START_ACCEL_UPLOAD:
                    startUpload(myID);
                    YEB_CanLED_OFF();
                    break;
                case STOP_ACCEL_UPLOAD:
                    stopUpload();
                    YEB_CanLED_OFF();
                    break;
                case TAKE_SNAP_SHOT:
                    //shoot(0);
                    break;
                case START_FETCHING_IMAGE:
                    //takeShot(recvMsg.ID);
                    break;
            }
        }
    }

    if (sendMsg = canGetOutgoingHead()) {
        if (ECANSendMessage(sendMsg->ID, sendMsg->data, sendMsg->dataLength, ECAN_TX_XTD_FRAME)) {
            canDecOutgoing();
            sendMsg = NULL;
            //sendDummy();
        }
    }
}

void deployCommandHQ(unsigned char id) {
    canPacket_t temp;
    unsigned long i;

    myID = id;
    //accelInit();
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 1;
    LATBbits.LATB2 = 1;
    INTCON2bits.RBPU = 0; //pull ups

    QfPlat_DelayMs(100);

    canParamInit(myID, broadcastID);
    initCanOutgoingQueue();

    initAccelHandler();

    tHandle_CHQ = registerTask(&commandHandler, TUID_COMMAND_HQ, (unsigned short) 0, -1);

#if ECAN_INIT_MODE == ECAN_INIT_LOOPBACK
    sendDummy();
#endif
}

#if ECAN_INIT_MODE == ECAN_INIT_LOOPBACK

static void sendDummy(void) {
    canPacket_t recvMsg;

    recvMsg.ID = 0x00000000;
    recvMsg.dataLength = 6;
    recvMsg.data[0] = 'A';
    recvMsg.data[1] = 'B';
    recvMsg.data[2] = 'C';
    recvMsg.data[3] = 'D';
    recvMsg.data[4] = 'E';
    recvMsg.data[5] = 'F';
    canEnqueueOutgoing(&recvMsg);
}
#endif
