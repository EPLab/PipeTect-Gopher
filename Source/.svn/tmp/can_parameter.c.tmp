#include "can_parameter.h"
#include "ECANPoll.h"
#include "vector_mapper.h"

//unsigned char myID = 0x01;
//unsigned char broadcastID = 0xFF;

//only sees 8bits
BYTE myMask[] = {0x00, 0x00, 0x00, 0x00}; //do not change
BYTE myFilter1[] = {0x00, 0x00, 0x00, 0x00}; //default 0x00
BYTE myFilter2[] = {0x00, 0x00, 0x00, 0x00}; //default 0x00

static void (*canWhenWakeUp_WB)(void) = 0;

static void canWhenWakeUp(void);

static void genFilter(BYTE* filter, BYTE value) {
    filter[3] = (value >> 3) & 0x1F;
    filter[2] = (value << 5) & 0xE0;
}

void canParamInit(unsigned char i_id, unsigned char b_id) {
    //myID = i_id;
    //broadcastID = b_id;
    genFilter(myFilter1, i_id); //setup myID;
    genFilter(myFilter2, b_id); //setup broadcastID;
    genFilter(myMask, 0xFF);
    ECANInitialize();
    ECANSetRXM0Value(*((unsigned long*) myMask), ECAN_MSG_XTD);
    ECANSetRXF0Value(*((unsigned long*) myFilter1), ECAN_MSG_XTD);
    ECANSetRXF1Value(*((unsigned long*) myFilter2), ECAN_MSG_XTD);
    ECANSetRXF2Value(*((unsigned long*) myFilter1), ECAN_MSG_XTD);
    ECANSetRXF3Value(*((unsigned long*) myFilter2), ECAN_MSG_XTD);
    ECANSetRXF4Value(*((unsigned long*) myFilter1), ECAN_MSG_XTD);
    ECANSetRXF5Value(*((unsigned long*) myFilter2), ECAN_MSG_XTD);
    ECANSetRXF6Value(*((unsigned long*) myFilter1), ECAN_MSG_XTD);
    ECANSetRXF7Value(*((unsigned long*) myFilter2), ECAN_MSG_XTD);
    ECANSetRXF8Value(*((unsigned long*) myFilter1), ECAN_MSG_XTD);
    ECANSetRXF9Value(*((unsigned long*) myFilter2), ECAN_MSG_XTD);
    ECANSetRXF10Value(*((unsigned long*) myFilter1), ECAN_MSG_XTD);
    ECANSetRXF11Value(*((unsigned long*) myFilter2), ECAN_MSG_XTD);
    ECANSetRXF12Value(*((unsigned long*) myFilter1), ECAN_MSG_XTD);
    ECANSetRXF13Value(*((unsigned long*) myFilter2), ECAN_MSG_XTD);
    ECANSetRXF14Value(*((unsigned long*) myFilter1), ECAN_MSG_XTD);
    ECANSetRXF15Value(*((unsigned long*) myFilter2), ECAN_MSG_XTD);
    ECANLinkRXF0F1ToBuffer(RXB0, RXB0);
    ECANLinkRXF2F3ToBuffer(RXB1, RXB1);
    ECANLinkRXF4F5ToBuffer(B0, B0);
    ECANLinkRXF6F7ToBuffer(B1, B1);
    ECANLinkRXF8F9ToBuffer(B2, B2);
    ECANLinkRXF10F11ToBuffer(B3, B3);
    ECANLinkRXF12F13ToBuffer(B4, B4);
    ECANLinkRXF14F15ToBuffer(B5, B5);
    ECANLinkRXF0Thru3ToMask(ECAN_RXM0, ECAN_RXM0, ECAN_RXM0, ECAN_RXM0);
    ECANLinkRXF4Thru7ToMask(ECAN_RXM0, ECAN_RXM0, ECAN_RXM0, ECAN_RXM0);
    ECANLinkRXF8Thru11ToMask(ECAN_RXM0, ECAN_RXM0, ECAN_RXM0, ECAN_RXM0);
    ECANLinkRXF12Thru15ToMask(ECAN_RXM0, ECAN_RXM0, ECAN_RXM0, ECAN_RXM0);
}

void canSleep(void) {
    IPR3bits.WAKIP = 0;
    PIR3bits.WAKIF = 0;
    PIE3bits.WAKIE = 1;
    set_LIV_func2(&canWhenWakeUp);
    // put CAN peripheral asleep
    ECANSetOperationMode(ECAN_OP_MODE_SLEEP);
}

void canRegisterWhenWakeUp_WB(void (*fp)(void)) {
    canWhenWakeUp_WB = fp;
}

void canWhenWakeUp(void) {
    if (PIR3bits.WAKIF) {
        PIE3bits.WAKIE = 0; //disable wake interrupt
        PIR3bits.WAKIF = 0;
        // now CAN mode is supposed to be NORMAL mode
        if (canWhenWakeUp_WB) {
            canWhenWakeUp_WB();
        }
    }
}
