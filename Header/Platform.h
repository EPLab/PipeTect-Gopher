/*****************************  (C) Quickfilter Technologies, Inc.  *************************//*!

  @file  Platform.h

  Abstracts a variety of operations that are specific to the way this platform circuit
  is designed.

  $Id: Platform.h 121 2006-07-24 20:17:09Z jhopson $

*///*********************************************************************************************


#ifndef PLATFORM_H_INCLUDED                //   Inclusion control
#define PLATFORM_H_INCLUDED


#include  "Project.h"
#include  "Msp430-SPI.h"


//#define DRDY_BIT 0x01


#if  defined(Debug)

//  Three instrumentation bits are used during debug.
                                          //   name   pin  (on '449)
                                          //   ----   ---
#define  ActivityLED            BIT1      //   P5.1   12

#define  TimerA0IsrTestPoint    BIT4      //   P5.4   55
#define  Spi0DrdyIsrTestPoint   BIT5      //   P5.5   57
#define  Spi0ReadIsrTestPoint   BIT6      //   P5.6   58
#define  Spi0WriteIsrTestPoint  BIT7      //   P5.7   59


#define  InitTestPointPort()   { P5DIR |=  BIT1 | BIT4 | BIT5 | BIT6 | BIT7;  }

#define  SetTestPoint( a )     SetBit( P5OUT, a )
#define  ClearTestPoint( a )   ClearBit( P5OUT, a )
#define  ToggleTestPoint( a )  ToggleBit( P5OUT, a )
#define  IsTestPointSet( a )   IsBitSet( P5OUT, a )


#else


#define  InitTestPointPort()   ((void)0)
#define  SetTestPoint( a )     ((void)0)
#define  ClearTestPoint( a )   ((void)0)
#define  ToggleTestPoint( a )  ((void)0)
#define  IsTestPointSet( a )   ((void)0)

#endif



#ifdef __cplusplus
   extern "C" {                            //  C++ source requires this linkage specification
#endif



void  QfPlat_Init( void );
void  QfPlat_ActivateQF4A512ChipSelect( void );
void  QfPlat_DeactivateQF4A512ChipSelect( void );
void  QfPlat_SetSpi0DrdyDirection( Bool Direction );
void  QfPlat_SetSpi0DrdyState( Bool State );
void  QfPlat_DelayMs( const UInt16  Milliseconds );
Bool  QfPlat_IsDrdyPinActive( void );
void  QfPlat_ConfigureDrdyInterrupt( FuncPtr Handler );
void  QfPlat_EnableDrdyInterrupts( void );
void  QfPlat_DisableDrdyInterrupts( void );

void  QfPlat_ToggleActivityLED( void );	//let UI show that sampling in process


//YEB
extern void YEB_ToggleCanLED(void);		//can activity LED's
extern void YEB_CanLED_ON(void);
extern void YEB_CanLED_OFF(void);
extern Bool isRunning(void);
extern void runit(void);
extern void stopit(void);
extern void reserv2stop(void);
extern void QFPlat_PowerDownBase(void);
extern void QFPlat_PowerUpBase(void);

//#ifdef __YEB_INTERRUPT__
extern void enable_daum(void);		//let it automatically load a dummy to the SSPBUF to receive next byte
extern void disable_daum(void);		//forbid automatic dummy loading to SSPBUF
//#endif

#if  defined(Debug)
void QfAssertionFailed( const char *  Expression,   const char * FileName,   const int LineNum );
#endif



#ifdef __cplusplus
   }                                       //  End of C++ linkage specification
#endif


#endif

