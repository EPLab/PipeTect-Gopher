/*****************************  (C) Quickfilter Technologies, Inc.  *************************//*!

  @file  Msp430-SPI.h

  Abstraction of MSP-430 SPI port for use with Quickfilter device drivers.

  $Id: Msp430-SPI.h 121 2006-07-24 20:17:09Z jhopson $

*///*********************************************************************************************


#if !defined(MSP_430_SPI_H_INCLUDED)                //        Inclusion control
#    define  MSP_430_SPI_H_INCLUDED



#include "Project.h"


///  Device handle for USART0.
#define  SPI0_HANDLE   0

///  Device handle for USART1.
#define  SPI1_HANDLE   1


///  Maximum allowable device number.  Device 0 is USART0 and device 1 is USART1.
#define  QF_SPI_MAX_DEVICE_NUMBER   0


///  Byte capacity of the local stream read buffers
#define  QF_SPI_SIZE_OF_SPI_READ_BUFFER   128


///  Standard type for function from receive ISR when a byte is received
typedef  Bool (* ReceiveCallback)(Byte);


///  Configuration options for the SPI port.
typedef enum  {
    ///  Reads are performed as requested.  No buffering
    ///  occurs between @ref QfSpi_Read read calls.
    SetUnbufferedReadMode,

    ///  SPI data is continuously buffered.  User must call @ref QfSpi_Read
    ///  at the rate at which data is filling up buffers.
    SetBufferedReadMode

}  QfSpi_ConfigRequest;



#ifdef __cplusplus
   extern "C"                             //  C++ source requires this linkage specification
{
#endif



void  QfSpi_Init( void );

void  QfSpi_DeInit( void );

void  QfSpi_Write(
    const Handle  Device,
    const Byte  * Buffer,
    const Count   Length);

Result  QfSpi_Read(
    const Handle  Device,
    Byte  * Buffer,
    const Count   Length);

Result  QfSpi_Configure(
    const Handle  Device,
    const QfSpi_ConfigRequest  Request,
    void  * Buffer,
    Count * Length);

Byte  QfSpi_ReadByte(
    const Handle  Device );

void  QfSpi_WriteByte(
    const  Handle  Device,
    const  Byte    Value);

void  QfSpi_WriteUInt16(
    const  Handle  Device,
           UInt16  Value);

void QfSpi_ResumeReceive(
    const  Handle  Device );

#ifndef __YEB_IMMEDIATE__
extern Bool getYeb(Byte length, void (*fp)(Byte* data, Byte leng));
#else
extern void getYebImmediate(Byte* data, Byte length);
#endif

#ifdef __cplusplus
}                                       //  End of C++ linkage specification
#endif


#endif

