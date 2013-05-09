/*****************************  (C) Quickfilter Technologies, Inc.  *************************//*!

  @file  Platform.c

  Abstracts a variety of operations that are specific to the way this platform circuit
  is designed.

  $Id: Platform.c 121 2006-07-24 20:17:09Z jhopson $

  *******************************************************************************************

  @formats
      - C
      - Doxygen (comment markup to produce HTML docs)

  @dependencies
      - Operating System:  none
      - Toolset:           IAR MSP
      - Platform:          TI MSP-TS430PZ100 with QF4A512
      - CPU Architecture:  MSP-430
      - CPU Variant:       '449
      - Device:            GPIO config of this platform
      - CPU byte order:    n/a

  @notes
    -# Note that these are not MSP430 GPIO control functions per se.  These functions
       put the GPIO control in the context of their use on this MSP430/QF4A512 platform.
          @verbatim
          +-------------+------------------------------------------+
          |             |             Application Code             |         This file
          |  Standard   +------------------------------------------+       -------------
          |      C      |   SPI-based Quickfilter Device Driver    |
          |  Libraries  +------------------------------------------+ <--- provides part of
          |             |  SPI Hardware Abstraction Library (HAL)  |          this API
          +-------------+------------------------------------------+
          @endverbatim

       This library *only* manipulates SPI hardware and its interrupt control registers, and
       calls a few Standard C library functions.  It doesn't call any other libraries.

  @references
     -# "QF4A512 4-Channel Programmable Signal Converter", Rev C3, Apr 06, Quickfilter
        Technologies, Inc., www.quickfiltertech.com/files/QF4A512revC3.pdf
     -# "TI MSP430x4xx Family User's Guide", SLAU056, Version E, Texas Instruments,
            focus.ti.com/lit/ug/slau056e/slau056e.pdf
     -# IAR Embedded Workbench Help, Version 3.40.2.3, www.iar.de
     -# "doxygen", Version 1.4.6, Dimitri van Heesch, doxygen.org

*///*********************************************************************************************


#include  "Project.h"
#include  "Platform.h"

#ifndef __DRDY_INT_USED
#include "switcher.h"
#else
#include "vector_mapper.h"
#endif

#include "delays.h"

/************************************************************************************************
    L o c a l   C o n s t a n t s ,   M a c r o s   a n d   T y p e s
 ************************************************************************************************/


/************************************************************************************************
    L o c a l   V a r i a b l e s
 ************************************************************************************************/

///  Callback function for the DRDY active ISR
static FuncPtr DrdyCallbackFunc = 0;
static unsigned char tHandle_PF = 0;
static volatile Bool DrdyInterruptEnabled = false;
static volatile Bool daum = false;
static volatile Bool running = true;

/************************************************************************************************
    L o c a l   F u n c t i o n   P r o t o t y p e s
 ************************************************************************************************/

//void  InitClocking( void );
//__interrupt void  TimerA0Isr( void );
//__interrupt void  DrdyIsr( void );


/******************************************************************************************
 ******************************************************************************************
 ********                                                                          ********
 ********                   P u b l i c   F u n c t i o n s                        ********
 ********                                                                          ********
 ******************************************************************************************
 ******************************************************************************************/

#ifndef __DRDY_INT_USED
static void DrdyIsr(unsigned char tid, void* msg);
#else
static void DrdyIsr(void);
#endif

void QFPlat_EnableTilt(void) {

}

void QFPlat_DisableTilt(void) {

}

void QFPlat_PowerDownBase(void) {
    LATA &= 0xFE;
}

void QFPlat_PowerUpBase(void) {
    LATA |= 0x01;
}

void QFPlat_Sleep(void) {
    //can peripheral off
    canSleep();
    //can transceiver off
    //QfPlat_ToggleActivityLED();
    //switchover
    //T0CONbits.TMR0ON = 0;	// tick off

    //IPR1bits.TMR1IP = 0;		//low priority for timer1 overflow
    //PIR1bits.TMR1IF = 0;		//clear int flag
    //PIE1bits.TMR1IE = 1;		//enable interrupt
    //T1CONbits.RD16 = 1;			//16bit counter
    //T1CONbits.TMR1CS = 0;		//timer1 clock source is internal clock
    //T1CONbits.T1CKPS1 = 1;		// prescaler at 1/8
    //T1CONbits.T1CKPS0 = 1;
    //T1CONbits.TMR1ON = 1;		//Enable timer1

    //OSCCON |= 0x80;			// idle mode (peripherals are up and running)
    //OSCCONbits.SCS1 = 1;	// internal oscillator
    //OSCCONbits.SCS0 = 0;
    //OSCCONbits.IRCF2 = 0;	// internal oscillator is set at 125khz
    //OSCCONbits.IRCF1 = 0;
    //OSCCONbits.IRCF0 = 1;

    //put cpu asleep
    Sleep();
    //resumed
    // external oscillator on
    //OSCCONbits.SCS1 = 0;
    //OSCCONbits.SCS0 = 0;
    //while (OSCCONbits.OSTS == 0);	// wait for clock stabilization
    // tick on
    //T0CONbits.TMR0ON = 1;
    // turn off the timer to wakeup the MCU periodically
    //T1CONbits.TMR1
}

/********************************************************************************************//*!

  @summary  Initialize platform-specific elements

*//*********************************************************************************************/

void QfPlat_Init(void) {
    //    WDTCTL = WDTPW + WDTHOLD;             //  Disable watchdog timer

    // set the internal clock freq at 31kHz
    OSCCON &= 0x8F;
    // set internal osciallator as a system clock
    //OSCCON |= 0x02;
    // low-freq clock source select: usually 0x80 for internal clock source and 0x00 for external
    OSCTUNE = 0x00;
    //  Verify the byte order of the platform and
    //  give a warning if it isn't little endian.
#if  defined(Debug)
    UInt16 ByteOrderTestValue = 1;
    Byte * ByteOrderTestArray = (Byte *) & ByteOrderTestValue;
    Assert(ByteOrderTestArray[0] == 1);
#endif


    //InitClocking();                //  Setup clocks

    //    InitTestPointPort();

    //clear reset (pull it up)
    LATCbits.LATC0 = 1;
    TRISCbits.TRISC0 = 0;

    ClearBit(LATB, 0x10); //  Clear Valid Activity Indicator
    ClearBit(TRISB, 0x10); //  pin and set to an output

    ClearBit(LATA, 0x10); // CAN led setup
    ClearBit(TRISA, 0x10);

    SetBit(LATC, 0x04); //  Initialize /CS for QF4A512 on SPI0
    ClearBit(TRISC, 0x04);

    ClearBit(TRISB, 0x01); //  Set DRDY to an output

    // set up tilt sensor select bit (not selected)
    LATCbits.LATC1 = 1;
    TRISCbits.TRISC1 = 0;

#ifndef __DRDY_INT_USED
    tHandle_PF = registerTask(&DrdyIsr, 0, (unsigned short) 0, -1);
#else
    set_HIV_func2(&DrdyIsr);
    INTCON2bits.INTEDG0 = 1; //rising edge
#endif
    //  Global interrupt enable
    //    __enable_interrupt();
}


/********************************************************************************************//*!

  @summary  Initialize the device clocking.  ACLK runs off of the 32.768 KHz crystal.  MCLK
            runs off the DCO and supplies the CPU with 8MHz.  SMCLK runs the peripherals
            (SPI and timer) at 8MHz.

  - The DCO clock is generated internally and calibrated from the 32kHz crystal.

  - ACLK is brought out on pin P1.5 (82), MCLK is brought out out on pin P1.1 (86), SMCLK
    is brought out on P1.4 (83).

  - The 32kHz crystal connects between pins XIN and XOUT.  Nothing is connected to XT2IN/XT2OUT.

  - Be sure not to let the DCO go above the max frequency of the device (8MHz, in this case).

  - The Modulator is off (SCFQ_M in SCFQCTL), so the frequency will be as constant as possible.

  - The value written to the SCFQCTL register is automatically incremented by one. In other
    words, to achieve a frequency-multiplication factor of 32, 31 should be written into the
    lower seven bits of SCFQCTL.

*//*********************************************************************************************/

/*
void  InitClocking( void )
{

    FLL_CTL0 = _1010_0000;
            //  |||| ||||
            //  |||| |||+----- DCOF    - clear any existing fault condition
            //  |||| ||+------ LFOF    -           "
            //  |||| |+------- XT10F   -           "
            //  |||| +-------- XT20F   -           "
            //  ||++---------- XCAPxPF - 8pF capacitance on XIN/XOUT
            //  |+------------ XTS_FLL - low-frequency mode
            //  +------------- DCOPLUS - use divided fDCO output


    FLL_CTL1 = _0010_0000;
            //  |||| ||||
            //  |||| ||++----- FLL_DIV  - No ACLK division on P1.5
            //  |||| |+------- SELS     - SMCLK sourced by FLL
            //  |||+-+-------- SELM     - MCLK sourced by FLL
            //  ||+----------- XT2OFF   - no secondary clock input. turn oscillator off
            //  |+------------ SMCLKOFF - turn (leave) SMCLK on
            //  +------------- (unused)


    SCFI0   = _0101_0000;
           //  |||| ||||
           //  |||| ||++----- MODx (LSBs) - TI guy doesn't know what these are for!
           //  |||| ||                      seems to work at 0.
           //  ||++-++------- FN_x  - DCO range from 2.8 to 26.6 MHz
           //  ++------------ FLLDx - add additional x2


    SCFQCTL = _1111_1000;
           //  |||| ||||
           //  |+++-++++----- N    - Feedback loop divisor (120d)
           //  +------------- SCFQ_M  - turn modulator off


    SetBitsUsingMask( P1DIR, _0011_0010 );    //  Set P1.1, P1.4 and P1.5 as outputs
    SetBitsUsingMask( P1SEL, _0011_0010 );    //  Set P1.1, P1.4 and P1.5 as clock out
}
 */


/********************************************************************************************//*!

  @summary  Activate chip select for the QF4A512 attached to SPI0.

  @notes
    -# Warning!  QF4A512 logic requires DRDY to be high before taking /CS low in Run mode.
                 DRDY will remain low in Configure mode.

*//*********************************************************************************************/

void QfPlat_ActivateQF4A512ChipSelect(void) {
    ClearBit(LATC, 0x04);
}


/********************************************************************************************//*!

  @summary  Deactivate chip select for the QF4A512 attached to SPI0.

  @notes
    -# /CS has to be low for at least four SYS_CLK (not SCLK) during each SPI bus cycle.
       If /CS is de-asserted too soon, DRDY might not be cleared in time for the next
       cycle.  Although this would rarely be an issue, this code checks to be sure DRDY
       is high before de-selecting /CS.

*//*********************************************************************************************/

void QfPlat_DeactivateQF4A512ChipSelect(void) {
    SetBit(LATC, 0x04);
}


/********************************************************************************************//*!

  @summary  Set the direction of the DRDY pin for the QF4A512 connected to USART0.

*//*********************************************************************************************/

void QfPlat_SetSpi0DrdyDirection(Bool Direction) {
    if (Direction == Input) {
        SetBit(TRISB, 0x01);
    } else {
        ClearBit(TRISB, 0x01);
    }
}


/********************************************************************************************//*!

  @summary  Set the state of the DRDY pin for the QF4A512 connected to USART0.

*//*********************************************************************************************/

void QfPlat_SetSpi0DrdyState(Bool State) {
    if (State == Active) {
        SetBit(LATB, 0x01);
    } else {
        ClearBit(LATB, 0x01);
    }
}


/********************************************************************************************//*!

  @summary  Gets the state of the DRDY pin.

  @notes
    -# DRDY is on pin 1.0.

*//*********************************************************************************************/

Bool QfPlat_IsDrdyPinActive(void) {
    if (PORTB & 0x01) {
        return true;
    }
    return false;
}


/********************************************************************************************//*!

  @summary  Configure interrupts from the DRDY pin.

*//*********************************************************************************************/

inline
void QfPlat_ConfigureDrdyInterrupt(FuncPtr Handler) {
    DrdyCallbackFunc = Handler;

    //ClearBit( P1SEL, DRDY_BIT );    //  DRDY pin is a GPIO only (no special functionality)
    SetBit(TRISB, 0x01); //  Set DRDY to an input
    //ClearBit( P1IES, DRDY_BIT );    //  DRDY interrupt occurs on rising edge
    //ClearBit( P1IFG, DRDY_BIT );    //  Reset the DRDY bit interrupt flag
}


/********************************************************************************************//*!

  @summary  Enable interrupts from the DRDY pin.

*//*********************************************************************************************/

inline
void QfPlat_EnableDrdyInterrupts(void) {
    //  Only transitions, not static levels, cause interrupts.  Be sure to set flag
    //  if DRDY is already active.
#ifndef __DRDY_INT_USED
    DrdyInterruptEnabled = true;
#else
    if (QfPlat_IsDrdyPinActive()) {
        //  Call function using pointer supplied in call to QfPlat_EnableDrdyInterrupts()
        DrdyCallbackFunc();
    }
    INTCONbits.INT0IF = 0;
    INTCONbits.INT0IE = 1;
#endif	
    //SetBit( P1IE, DRDY_BIT );      //  Enable interrupts on DRDY pin
}

/********************************************************************************************//*!

  @summary  Disable interrupts from the DRDY pin.

*//*********************************************************************************************/

inline
void QfPlat_DisableDrdyInterrupts(void) {
#ifndef __DRDY_INT_USED
    //ClearBit( P1IE, DRDY_BIT );      //  Disable interrupts on DRDY pin
    DrdyInterruptEnabled = false;
#else
    INTCONbits.INT0IE = 0;
#endif
}

/********************************************************************************************//*!

  @summary  Toggle the state of the Activity LED on the platform.

*//*********************************************************************************************/

//#pragma  inline

void QfPlat_ToggleActivityLED(void) {
    ToggleBit(LATB, 0x10);
}

void YEB_ToggleCanLED(void) {
    ToggleBit(LATA, 0x10);
}

void YEB_CanLED_ON(void) {
    SetBit(LATA, 0x10);
}

void YEB_CanLED_OFF(void) {
    ClearBit(LATA, 0x10);
}

///  The number of TimerA ticks in one millisecond using SMCLK
//#define  TimerA0TicksPerMillisecond   0x1F98

///  Count of milliseconds until wakeup from low power mode.  Used by QfPlat_Delay
//static volatile UInt16  MillisecondsUntilWakeup;


/********************************************************************************************//*!

  @summary  Delay the specified number of milliseconds

  @param[in]  Milliseconds   Number of milliseconds to delay

  @notes
    -# The accuracy of the delay isn't very important, but try to err on the side of waiting
       too long.
    -# Be sure no other interrupts will occur during the wait time.

*//*********************************************************************************************/

void QfPlat_DelayMs(const UInt16 Milliseconds) {

    //    MillisecondsUntilWakeup = Milliseconds;

    //    CCTL0  =  CCIE;                        //  CCR0 interrupt enabled
    //    CCR0  +=  TimerA0TicksPerMillisecond;  //  Add Offset to CCR0

    //    TACTL = TASSEL_2 +                     //  Use SMCLK,
    //            MC_2;                          //  Count up countinuously.  Match with compare
    //  latch (TBCL0)

    //    __low_power_mode_0();                  //  Conserve power while waiting
    unsigned char i;

    for (i = 0; i < 16; ++i) {
        Delay10KTCYx(10);
    }
}


/******************************************************************************************
 ******************************************************************************************
 ********                                                                          ********
 ********                  U t i l i t y   F u n c t i o n s                       ********
 ********                                                                          ********
 ******************************************************************************************
 ******************************************************************************************/



/******************************************************************************************
 ******************************************************************************************
 ********                                                                          ********
 ********             L o c a l   ( S t a t i c )   F u n c t i o n s              ********
 ********                                                                          ********
 ******************************************************************************************
 ******************************************************************************************/





/******************************************************************************************
 ******************************************************************************************
 ********                                                                          ********
 ********            I n t e r r u p t   S e r v i c e   R o u t i n e s           ********
 ********                                                                          ********
 ******************************************************************************************
 ******************************************************************************************/


//  Suppress  "Warning[Pa082]: undefined behavior: the order of volatile accesses is
//  undefined in this statement..." that occurs below.  The order is unimportant here.

//#pragma  diag_suppress = Pa082



/********************************************************************************************//*!

  @summary  Timer A0 interrupt service routine.

  @notes
    - Services QfPlat_DelayMs()

*//*********************************************************************************************/
/*
#pragma  vector = TIMERA0_VECTOR

__interrupt void  TimerA0Isr( void )
{
    SetTestPoint( TimerA0IsrTestPoint );


    if (--MillisecondsUntilWakeup == 0)
    {
        TACTL = 0;                              //  Disable TimerA0 interrupt, and turn
                                                //  timer off to save power.
        __low_power_mode_off_on_exit();
    }
    else
    {
        CCR0  +=  TimerA0TicksPerMillisecond;   //  Add delay for next millisecond
    }


    ClearTestPoint( TimerA0IsrTestPoint );
}
 */



/********************************************************************************************//*!

  @summary  Interrupt service routine to handle transitions on the DRDY pin.

  @notes
    - The port interrupt flag has to be explicitly cleared.

    - This function is called during an interrupt service routine.  Be sure to keep
      it as short as possible and only manipulate things that are appropriate to this context.

*//*********************************************************************************************/

void enable_daum(void) {
    daum = true;
}

void disable_daum(void) {
    daum = false;
}

//#pragma  vector = PORT1_VECTOR

#ifndef __DRDY_INT_USED

void DrdyIsr(unsigned char tid, void* msg) {
    //SetTestPoint( Spi0DrdyIsrTestPoint );

    //  Be sure DRDY bit is the one that trigerred the interrupt
    //Assert( IsBitSet( P1IN, DRDY_BIT ) );
    //AssertNonNull( DrdyCallbackFunc );

    //  Reset the DRDY bit interrupt flag
    //ClearBit( P1IFG, DRDY_BIT );
    if (running == true) {
        if (DrdyInterruptEnabled == true) {
            if (PORTB & 0x01) {
                //  Call function using pointer supplied in call to QfPlat_EnableDrdyInterrupts()
                DrdyCallbackFunc();
            }
        } else {
            if (daum == true) {
                SSPBUF = 0;
            }
        }
    }
    //else
    //{
    //	DrdyInterruptHandled = false;
    //}
    //ClearTestPoint( Spi0DrdyIsrTestPoint );
}
#else

void DrdyIsr(void) {
    if (running == true) {
        if (INTCONbits.INT0IF) {
            DrdyCallbackFunc();
            INTCONbits.INT0IF = 0;
        }
    }
}
#endif

Bool isRunning(void) {
    return running;
}

void runit(void) {
    running = true;
}

void stopit(void) {
    running = false;
}
