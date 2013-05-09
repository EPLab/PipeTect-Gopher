#include <p18cxxx.h>
#include <usart.h>
#include "switcher.h"
//#include "accel_gateway.h"
#include "command_hq.h"
//#include "jpeg_module.h"
#include "platform.h"

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

#pragma config OSC = HS
//#pragma config FCMENB = OFF
#pragma config IESO = ON
#pragma config PWRT = OFF
//#pragma config BOR = BOACTIVE
//#pragma config BORV = 28
#pragma config WDT = ON
#pragma config WDTPS = 32768
#pragma config MCLRE = ON
#pragma config LPT1OSC = OFF
#pragma config PBADEN = ON
#pragma config DEBUG = ON
#pragma config XINST = OFF
#pragma config BBSIZ = 1024
#pragma config LVP = OFF
#pragma config STVREN = ON
#pragma config CP0 = OFF
#pragma config CP1 = OFF
#pragma config CP2 = OFF
#pragma config CP3 = OFF
#pragma config CPB = OFF
#pragma config CPD = OFF
#pragma config WRT0 = OFF
#pragma config WRT1 = OFF
#pragma config WRT2 = OFF
#pragma config WRT3 = OFF
#pragma config WRTB = OFF
#pragma config WRTC = OFF
#pragma config WRTD = OFF
#pragma config EBTR0 = OFF
#pragma config EBTR1 = OFF
#pragma config EBTR2 = OFF
#pragma config EBTR3 = OFF
#pragma config EBTRB = OFF

/*
void initUSART(void)
{
        BAUDCON |= 0x08;
			   
        OpenUSART( USART_TX_INT_OFF &
               USART_RX_INT_OFF & 
               USART_ASYNCH_MODE & 
               USART_EIGHT_BIT & 
               USART_CONT_RX & 
               USART_BRGH_HIGH, 
               0x01FE);				// Asynchronous, no int, 9600 BPS, 8, N, 1
}	

void send(unsigned char data)
{
        while(BusyUSART());
    WriteUSART(data);
}
 */

//void RunTimeInitialization(void);

void main(void) {
    //unsigned char id = MY_ID;
    //OSCCON = 0x78;
    //turn on the 3.3 reg and 1.8 reg
    QfPlat_DelayMs(100);

    //Turn on the power for the base
    LATAbits.LATA0 = 1;
    TRISAbits.TRISA0 = 0;

    ADCON1 |= 0x0F;
    ADCON1 |= 0x0F; // Default all pins to digital
    T1CON = 0x00;
    TRISBbits.TRISB0 = 0;
    LATBbits.LATB0 = 1;

    QfPlat_DelayMs(100);

    initSwitcher(0x01);

    deployCommandHQ(0x02);
    //RunTimeInitialization();
    //initJPEGModule();

    //WDTCONbits.SWDTEN = 1;

    //always place it at the end of main function
    Switcher();
}

/*void RunTimeInitialization(void)
{
        // Must be in Config mode to change many of settings.
        ECANSetOperationMode(ECAN_OP_MODE_CONFIG);
        // Select Mode 1
        ECANSetFunctionalMode(ECAN_MODE_1);
        // Make B0 as receiver.
        ECANSetBnTxRxMode(B0, ECAN_BUFFER_RX);
        // RXB0 will receive Standard messages only.
        ECANSetRxBnRxMode(RXB0, ECAN_RECEIVE_ALL_VALID);
        // B0 will receive Extended
        ECANSetBnRxMode(B0, ECAN_RECEIVE_ALL_VALID);
        // Link RXF0 to RXB0 and RXF1 to B0
        ECANLinkRXF0F1ToBuffer(RXB0, B0);
        ECANLinkRXF0Thru3ToMask(ECAN_RXM0,
        ECAN_RXM1,
        ECAN_RXM0,
        ECAN_RXM0);
        ECANSetRXF0Value(0, ECAN_MSG_STD);
        ECANSetRXF1Value(0, ECAN_MSG_XTD);
        ECANSetRXM0Value(0, ECAN_MSG_STD);
        ECANSetRXM1Value(0, ECAN_MSG_XTD);
        // Set 125kbps @ 25MHz
        ECANSetBaudRate(2, 4, 8, 8, 8);
        // Return to Normal mode to communicate.
        ECANSetOperationMode(ECAN_OP_MODE_NORMAL);
}*/
