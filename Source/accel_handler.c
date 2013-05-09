#include "accel_handler.h"
#include "switcher.h"
#include "string.h"

///////////////////////////////////////////////////////////////////////////////
//  Quick Filter Associated
///////////////////////////////////////////////////////////////////////////////
#include  "Msp430-SPI.h"
#include  "Qf4a512-access.h"
#include  "Qf4a512-functional.h"
#include  "Project.h"
#include  "Platform.h"

#include "can_outgoing_queue.h"
#include "can_parameter.h"
//#include "spi.h"
#include "tilt.h"

//  Include table with device settings produced by the Quickfilter Pro software
//#include  "QFImageRegisterTable.h"

///  Buffer to hold the samples currently being processed
UInt16 Sample[ NUM_FRAMES_PER_SAMPLE_REQUEST ][ QF4A512_NUM_CHANNELS_ENABLED ];

///  Holds the peak value for each channel
Int16 Peaks[ QF4A512_NUM_CHANNELS_ENABLED ] = {0, 0, 0, 0};

volatile unsigned char seqNum = 0;
volatile unsigned char accelSampleHandle = 0;
volatile unsigned char targetID = 0;
//volatile unsigned char activate_now = 0;
//volatile unsigned char sleepHandle;

static void sample(unsigned char uid, void* msg);


//static void AccelWakeUpByCAN(void)
//{
//	activate_now = 1;
//}

//static void sleep_WB(unsigned char uid, void* msg)
//{
//	pauseTask(sleepHandle);
//	rewindCountTask(sleepHandle);
//	//IdleSelf();
//	canSleep();
//	//QfPowerDown();
//	//QFPlat_PowerDownBase();
//	//canRegisterWhenWakeUp_WB(&AccelWakeUpByCAN);
//	Sleep();
//}

void initAccelHandler(void) {
    //unsigned short temp = 0;

    //  Initialize the platform
    QfPlat_Init();

    //  Init QF4A512 and SPI hardware to which the QF4A512 is attached.
    qf4a512_Init();

    //  Load the table of settings and FIR coefficients from the Quickfilter Pro PC
    //  software.  (see header above for instructions on how to generate the table)

    //num = QF_IMAGE_REGISTER_TABLE_DIMENSION;

    qf4a512_LoadImageRegisterTable();

    //QfPowerDown();
    //QFPlat_PowerDownBase();

    //for endless sampling
    accelSampleHandle = registerTask(&sample, 0, (unsigned short) 0, -1);
    //sleepHandle = registerTask(&sleep_WB, 0, (unsigned short) 100, -1);

    //pauseTask(sleepHandle);
    //temp = adis16209_get_status();
    //temp = 0;
    //temp = adis16209_get_sample_rate();
    //temp = 0;
    //temp = adis16209_get_status();
    //temp = 0;
    //temp = adis16209_get_sample_rate();
    //temp = 0;

    //canRegisterWhenWakeUp_WB(&AccelWakeUpByCAN);
    //can peripheral off
    //canSleep();
    //can transceiver off
    //QfPlat_ToggleActivityLED();
    //put cpu asleep
    //Sleep();

    //QFPlat_Sleep();
}

UInt16* getCurrentSamples(void) {
    return Sample[0];
}

UInt16 getCurrentIndSample(unsigned char num) {
    return Sample[0][num];
}

void sample(unsigned char uid, void* msg) {
    Byte Frame;

    if (IsYebCallBackCalled()) {
        yebCallback();
    }
    //  Get a sample of data
    if (qf4a512_ReadSamples(SPI0_HANDLE, //  Device handle
                            Sample, //  Location to place the samples
                            NUM_FRAMES_PER_SAMPLE_REQUEST) == Success) //  Number of frames to read
    {
        //  Compare each channel's sample against the existing peak
        //  for that channel.  If higher, this sample is the new peak.
        /*
        for( Frame = 0;
                Frame < NUM_FRAMES_PER_SAMPLE_REQUEST;
         Frame++ )
        {
                Byte  Channel;
                for( Channel = 0;
                Channel < QF4A512_NUM_CHANNELS_ENABLED;
                Channel++ )
                {
                UInt16  Amplitude  =  Sample[ Frame ][ Channel ];	//abs omitted
                if (Amplitude > Peaks[ Channel ])
                {
                        Peaks[ Channel ]  =  Amplitude;
                }
                }
        }
         */

        if (targetID) {
            uploadAccel(targetID);
        }
        QfPlat_ToggleActivityLED();
        //Sleep();
    }

    //if (activate_now)
    //{
    //	activate_now = 0;
    //	resumeTask(sleepHandle);
    //}
}

// sequence numbers for sampled records

void uploadAccel(unsigned char id) {
#ifdef __CIR_USED__
    canPacket_t sendMsg;
    sendMsg.ID = id; //0x00000000;
    sendMsg.dataLength = 6;
    memcpy(&sendMsg.data[0], (void*) Sample, 6);
    YEB_CanLED_OFF();
    canEnqueueOutgoing(&sendMsg);
    YEB_CanLED_ON();
#else
    unsigned char buf[7];

    memcpy(buf, (void*) Sample, 6);
    buf[6] = seqNum++;
    YEB_CanLED_OFF();
    canEnqueueOutgoing(id, buf, 7);
    YEB_CanLED_ON();
#endif	
}

//if id = 0 stop;
//else start

void startUpload(unsigned char id) {
    //if (activate_now)
    //{
    //	activate_now = 0;
    //	QfActivate();
    //}
    targetID = id;
}

void stopUpload(void) {
    targetID = 0;
}
