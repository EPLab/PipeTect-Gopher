/*****************************  (C) Quickfilter Technologies, Inc.  *************************//*!

  @file  Qf4a512-access.c

  Raw data transfer functions and device mode control of QF4A512 (Small model).

  $Id: Qf4a512-access.c 121 2006-07-24 20:17:09Z jhopson $

  *****************************************************************************************

  @formats
    - C
    - Doxygen (comment markup to produce HTML docs)

  @dependencies
    - Operating System:  none
    - Toolset:           none
    - Platform:          none
    - CPU Architecture:  none
    - CPU Variant:       none
    - Device:            SPI port attached to a QF4A512
    - CPU byte order:    little endian

  @notes
    -# This portable C file implements the QF4A512 Library layer in the figure below.
       @par
       @verbatim
          +-------------+------------------------------------------+          This file
          |             |             Application Code             |         ------------
          |             |                                          |
          |  Standard   |            +-----------------------------+
          |      C      |            |  QF4A512 Functional Driver  |
          |  Libraries  +------------+-----------------------------+ <--- presents this API
          |             |            QF4A512 Access Driver         |
          |             +------------------------------------------+ ---> & calls this API
          |             |  SPI Hardware Abstraction Library (HAL)  |     (& some standard C
          +-------------+------------------------------------------+      library functions)
       @endverbatim

       @par
       The API supports reading and writing configuration data, reading and writing the on-
       board EEPROM, and reading the Run mode data stream.  The QF4A512 Functional Driver
       uses this module to provide more context-specific functionality, such as power
       management and reset management.

       @par
       This code does not directly access any hardware.  It calls the layer below (HAL)
       to send and receive data to and from the QF4A512.  The HAL is non-portable.

    -# This module does not control which channels are enabled.

    -# This module's interface supports multiple devices, but only Device 0 (SPI0_HANDLE)
       is implemented at this time.

    -# The QF4A512 has three modes, Configure, Run and Eeprom.  This module attempts to make
       mode transitions transparent.  For example, calling @ref qf4a512_ReadConfigRegisters
       puts the device in Configure mode, if it's not there already.  However, explicit
       mode control is needed in one case, the transition out of Run mode.  If Run mode
       isn't explicitly exited, data will continue to be backup in the SPI buffer until it
       overruns.  When done with Run mode (i.e. making consecutive calls to
       qf4a512_ReadSamples), call @ref qf4a512_ExitRunMode.

    -# The EEPROM inside the QF4A512 is compatible with the ATMEL AT25320A.  The algorithms
       used to manage EEPROM are consistent with that device.  This module does not support
       the write protection mechanisms of the AT25320A.

    -# The QF4A512 control registers that are more than 8-bits are stored little endian
       (lowest byte first) when streamed in Autoincrement mode.  The Run mode data from the
       device is big endian.

  @references
     -# "QF4A512 4-Channel Programmable Signal Converter", Rev C3, Apr 06, Quickfilter
        Technologies, Inc., www.quickfiltertech.com/files/QF4A512revC3.pdf
     -# "SPI Serial EEPROMS", 3347J-SEEPR-10/05, Atmel Corp.,
        www.atmel.com/dyn/resources/prod_documents/doc3347.pdf
     -# "doxygen", Version 1.4.6, Dimitri van Heesch, doxygen.org

*///*********************************************************************************************


#include  "Project.h"
#include  "Platform.h"
#include  "Qf4a512-access.h"                       //  Self include

#ifdef __YEB_IMMEDIATE__
#include "spi.h"
#endif
/************************************************************************************************
    L o c a l   C o n s t a n t s ,   M a c r o s   a n d   T y p e s
 ************************************************************************************************/


///  Mask for the Channel ID bits in the Flags byte of Run time data
#define  CHANNEL_NUM_MASK   _0110_0000

///  Number of bits to right shift the Flags byte to put
///  the Channel ID field in the bit 0 position.
#define  CHANNEL_NUM_OFFSET   5

///  Number of output frames the Device 0 read buffer can hold
#define  FRAME_CAPACITY_OF_DEVICE0_READ_BUFFER    8


///////////////////////////////////////////////////////////////////////////////////
//  EEPROM Management


///  Number of bytes in one page of EEPROM memory
#define  QF4A512_EEPROM_PAGE_SIZE   32


//  EEPROM Instruction Codes

///  Instruction to enable EEPROM writing (WREN)
#define  QF4A512_EEPROM_WRITE_ENABLE_INSTRUCTION    6

///  Instruction to disable EEPROM writing (WRDI)
#define  QF4A512_EEPROM_WRITE_DISABLE_INSTRUCTION   4

///  Instruction to read the EEPROM status register (RDSR)
#define  QF4A512_EEPROM_READ_STATUS_REGISTER_INSTRUCTION    5

///  Instruction to write the EEPROM status register (WRSR)
#define  QF4A512_EEPROM_WRITE_STATUS_REGISTER_INSTRUCTION   1

///  Instruction to read the EEPROM memory (READ)
#define  QF4A512_EEPROM_READ_INSTRUCTION    3

///  Instruction to write the EEPROM memory (WRITE)
#define  QF4A512_EEPROM_WRITE_INSTRUCTION   2



//  EEPROM Status Register Bits

///  Busy Indicator bit in the EEPROM Status register  (RDY).
#define  QF4A512_EEPROM_STATUS_BUSY_BIT     0x01

///  Write enable bit in the EEPROM Status register  (WEN)
#define  QF4A512_EEPROM_STATUS_WRITE_ENABLE_BIT     BIT1

///  Block Protect Bit 0 in the EEPROM Status register  (BP0)
#define  QF4A512_EEPROM_STATUS_BLOCK_PROTECT_BIT0   BIT2

///  Busy Indicator Bit 1 in the EEPROM Status register  (BP1)
#define  QF4A512_EEPROM_STATUS_BLOCK_PROTECT_BIT1   BIT3

///  Write Protect Enable bit in the EEPROM Status register  (WPEN)
#define  QF4A512_EEPROM_STATUS_WRITE_PROTECT_BIT    BIT7




///  Operating modes for the QF4A512.

typedef enum {
    Uninitialized = 0,
    Run,
    Configure,
    Eeprom

} qf4a512_Mode;




/************************************************************************************************
    L o c a l   V a r i a b l e s
 ************************************************************************************************/


///  Current operating mode of the QF4A512
static qf4a512_Mode DeviceMode = Uninitialized;

///  Frame data buffer queue data in BufferedRead mode
static volatile UInt16 Device0ReadBuffer [ FRAME_CAPACITY_OF_DEVICE0_READ_BUFFER ]
[ QF4A512_NUM_CHANNELS_ENABLED ];

///  Location in @ref Device0ReadBuffer where next byte will be inserted
static volatile Byte Device0FrameInsertIndex;

///  Location in @ref Device0ReadBuffer where next byte will be retrieved
static volatile Byte Device0FrameExtractIndex;

///  Number of bytes in @ref Device0ReadBuffer
static volatile Byte Device0FrameCount;

///  Channel number within a frame
static volatile Byte Device0Channel;

///  Byte number within a sample  (3 bytes per sample - Flags + 2-byte sample)
static volatile Byte Device0ByteNum;

static volatile Bool yebCallCallBack = 0;

/************************************************************************************************
    L o c a l   F u n c t i o n   P r o t o t y p e s
 ************************************************************************************************/

static void PutQF4A512InConfigureMode(const Handle Device);
static void PutQF4A512InRunMode(const Handle Device);
static void PutQF4A512InEepromMode(const Handle Device);
static Byte GetEepromStatus(const Byte Device);
static Bool IsEepromReady(const Byte Device);
static Bool Device0BufferedReadCallback(Byte NewByte);
static void Device0DrdyCallback(void);



/******************************************************************************************
 ******************************************************************************************
 ********                                                                          ********
 ********                   P u b l i c   F u n c t i o n s                        ********
 ********                                                                          ********
 ******************************************************************************************
 ******************************************************************************************/


/********************************************************************************************//*!

  @summary  Initialize all QF4A512 devices before first use

  - Call this first, before calling any other functions in this module, typcially
    during system initialization.  Also use if the devices need to be re-initializd
    after a call to @ref qf4a512_DeInit().

  - No other initizlization is required.  Devices don't need to be individually opened.

  - This init leaves the QF4A512(s) in Configure mode, even if the AutoStart feature
    is enabled on the device.

  - Before initializing a QF4A512, this code needs to know whether the device is
    currently in Configure or Run mode (the interface is different in each mode).
    This is done with the DRDY pin.

    @par
    First, be sure DRDY is an input to the microcontroller.  Be sure /CS is high then
    wait at more than the longest Run mode frame time and check DRDY.  If it's low
    the device is in Configure mode.  If DRDY is high, the QF4A512 is in Run mode.

    @par
    Why do you have to wait if DRDY is low?  In Run mode DRDY is an output pin that
    will change state per the Run mode interface timing.  That timing dicates that
    DRDY go high when new data is ready (if /CS is high).  New data will always be
    ready every frame period, so DRDY will go high within that time if in Run mode.

*//*********************************************************************************************/

void qf4a512_Init(void) {
    Byte CurrentSpiCtrl;

    //  Sanity check device mode.
    //Assert( DeviceMode == Uninitialized );

    //  Initialize the SPI port(s) this module will use.
    QfSpi_Init();



    //  Detect existing device mode (See note above)

    QfPlat_SetSpi0DrdyDirection(Input);


    QfPlat_DelayMs(200 /*ms*/);


    if (QfPlat_IsDrdyPinActive() == true) {
        DeviceMode = Run;
        PutQF4A512InConfigureMode(SPI0_HANDLE);
    }
    else // Device is in Config mode
    {
        //  Config drives the DRDY pin as low output
        QfPlat_SetSpi0DrdyState(Low);
        QfPlat_SetSpi0DrdyDirection(Output);

        DeviceMode = Configure;


        //  To access coefficient memory in Configure mode, the SPI_CTRL[ ram_run_mode ]
        //  bit must be cleared so the coefficient area can synchronize to the SPI clock,
        //  not the internal clock (clk_sys).
        //
        //  Warning!  Be sure 'DeviceMode = Configure' before calling any qf4a512_...
        //            functions (as done below), or mayhem might ensue.

        CurrentSpiCtrl = qf4a512_ReadConfigByte(SPI0_HANDLE, QF4A512_SPI_CTRL_ADDRESS);

        SetBit(CurrentSpiCtrl, 0x01);
        qf4a512_WriteConfigByte(SPI0_HANDLE, QF4A512_SPI_CTRL_ADDRESS, CurrentSpiCtrl);
    }


    //  Sanity check the target device type.
    //Assert(qf4a512_ReadConfigByte( SPI0_HANDLE, QF4A512_GLBL_ID_ADDRESS )  ==  QF4A512_CHIP_ID_NUMBER   &&
    //       qf4a512_ReadConfigByte( SPI0_HANDLE, QF4A512_DIE_REV_ADDRESS )  >=  QF4A512_MINIMUM_DIE_REV_NUMBER);


    //  Set the autoincrement bit in SPI_CTRL so sequences > 1 byte can be sent/received.
    qf4a512_WriteConfigByte(SPI0_HANDLE, QF4A512_SPI_CTRL_ADDRESS, _0000_1000);


    // Verify that autoincrement got turned on
    //Assert( qf4a512_ReadConfigByte( SPI0_HANDLE, QF4A512_SPI_CTRL_ADDRESS )  &  _0000_1000 );
}





/********************************************************************************************//*!

  @summary  Deinitialize all QF4A512 devices after last use.


  - Do not call any functions other than @ref qf4a512_Init() after calling this function.

  - The device may be in any power state prior to entering this function.

  - Upon return, the device should consume the same or less power than the Sleep power state.

  - Devices don't need to be individually closed.

*//*********************************************************************************************/

void qf4a512_DeInit(void) {
    //  Sanity check device mode.
    //Assert( DeviceMode != Uninitialized );

    QfSpi_DeInit();

    DeviceMode = Uninitialized;
}




/********************************************************************************************//*!

  @summary  Reads 'Length' Run mode samples from the QF4A512 into 'Buffer'.

  @param[in]  Device    Device handle
  @param[out] Buffer    Receives frames of 16-bit sample data
  @param[in]  Length    Number of frames of data to read

  @return   Always Success, for now.


  - Warning!  This function only works when all channels are active and sampling at
    the same frequency.  If the channels have different sampling frequencies, this
    function provides no means of knowing which samples are valid for a given frame.
    (single-channel high-speed mode is not supported)

*//*********************************************************************************************/

Result qf4a512_ReadSamples(
        const Handle Device,
        UInt16 Buffer [][ QF4A512_NUM_CHANNELS_ENABLED ],
        const Byte Length) {
    //Count  Frame;
    //Count  Channel;
    Byte Frame;
    Byte Channel;
    Byte* temp;
    Byte* temp2;
    //  Sanity check input parameters
    //Assert( Device == SPI0_HANDLE);
    //AssertNonNull( Buffer );
    //Assert( Length > 0 );


    //  If not in Run mode, go there now
    if (DeviceMode != Run) {
        PutQF4A512InRunMode(Device);
    }

    if (Device0FrameCount >= Length) {

        for (Frame = 0;
                Frame < Length;
                Frame++) {
            //if( Device0FrameCount == 0 )
            {
                //  Use low power mode while waiting for the next frame.
                //__low_power_mode_0();
            }
            //  Store the received data in the Caller's buffer.
            for (Channel = 0;
                    Channel < QF4A512_NUM_CHANNELS_ENABLED;
                    Channel++) {
                Buffer[ Frame ][ Channel ] = Device0ReadBuffer[ Device0FrameExtractIndex ][ Channel ];
                //temp = (Byte*)(&Buffer[Frame] + (Channel << 1));
                //temp2 = (Byte*)(&Device0ReadBuffer[Device0FrameExtractIndex] + (Channel << 1));
                //*temp = *temp2;
                //*(temp + 1) = *(temp2 + 1);
            }
            //  Advance frame index to next position.  Wrap to the
            //  the beginning if it goes beyond the end.
            Device0FrameExtractIndex++;
            Device0FrameExtractIndex %= FRAME_CAPACITY_OF_DEVICE0_READ_BUFFER;

            //  Decrease the count of frames in Device0ReadBuffer
            --Device0FrameCount;
        }
        return Success;
    }
    return BufferUnderflow;
}




/********************************************************************************************//*!

  @summary  Read 'Length' configuration registers into 'Buffer' starting at 'StartingAddr'.

  @param[in]  Device       Device handle
  @param[in]  StartingAddr Register or EEPROM address at which to start writing data
  @param[out] Buffer       Pointer to data to be written
  @param[in]  Length       Number of bytes in WriteBuff to write

  @return   'Success' if configuration successful, otherwise a negative value error code.


  - The QF4A512 interface timing for reading configuration registers is as follows.
    All fields are msb first and '^'=stable on rising edge.

      @verbatim
                                 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3
             0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
      SCLK   ^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^...

      SDO    1 [------ StartingAddr -----] x x x x x x x x x x x x x x x x x x x x x x x x x...

      SDI    x x x x x x x x x x x x x x x x [  Buffer[0]  ] [  Buffer[1]  ] [  Buffer[2]  ]...
          _
      /CS  |________________________________________________________________________________...|

      /DRDY ________________________________________________________________________________...
      @endverbatim


*//*********************************************************************************************/

void qf4a512_ReadConfigRegisters(
        const Handle Device,
        Count StartingAddr,
        Byte * Buffer,
        const Count Length) {

    //  Sanity check input parameters
    //Assert( Device  ==  SPI0_HANDLE);
    //Assert( StartingAddr + Length  <=  QF4A512_MAX_REGISTER_ADDRESS );
    //AssertNonNull( Buffer );
    //Assert( Length  >  0 );


    //  Put device in Configure mode if not there already
    if (DeviceMode != Configure) {
        PutQF4A512InConfigureMode(Device);
    }


    //  Prepare address.
    StartingAddr <<= 1; //  Address is offset by 1
    SetBit(StartingAddr, 0x8000); //  1 in msb indicates read


    //  QF4A512 read configuration data frame
    QfPlat_ActivateQF4A512ChipSelect(); //  1. Activate /CS
    QfSpi_WriteUInt16(Device, StartingAddr); //  2. Send address
    QfSpi_Read(Device, Buffer, Length); //  3. Read the data
    QfPlat_DeactivateQF4A512ChipSelect(); //  4. Deactivate /CS
}




/********************************************************************************************//*!

  @summary  Write 'Length' configuration registers from 'Buffer' starting at 'StartingAddr'.

  @param[in]  Device       Device handle
  @param[in]  StartingAddr Register or EEPROM address at which to start writing data
  @param[in]  Buffer       Pointer to data to be written
  @param[in]  Length       Number of bytes in WriteBuff to write

  @return   'Success' if configuration successful, otherwise a negative value error code.


  - The QF4A512 interface timing for writing configuration registers is as follows.
    All fields are msb first and '^'=stable on rising edge.

     @verbatim
                                 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3
             0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
      SCLK   ^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^...

      SDO    0 [------ StartingAddr -----] x [  Buffer[0]  ] [  Buffer[1]  ] [  Buffer[2]  ]...

      SDI    x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x...
          _
      /CS  |________________________________________________________________________________...|

      /DRDY ________________________________________________________________________________...
      @endverbatim


*//*********************************************************************************************/

Result qf4a512_WriteConfigRegisters(
        const Handle Device,
        Count StartingAddr,
        const Byte * Buffer,
        const Count Length) {

    //  Sanity check input parameters
    //Assert( Device  ==  SPI0_HANDLE);
    //Assert( StartingAddr + Length  <=  QF4A512_MAX_REGISTER_ADDRESS );
    //AssertNonNull( Buffer );
    //Assert( Length  >  0 );

    //  Put device in Configure mode if not there already
    if (DeviceMode != Configure) {
        PutQF4A512InConfigureMode(Device);
    }


    //  Address to device is offset 1 bit to the left
    StartingAddr <<= 1;


    //  QF4A512 writeconfiguration data frame
    QfPlat_ActivateQF4A512ChipSelect(); //  1. Activate /CS
    QfSpi_WriteUInt16(Device, StartingAddr); //  2. Send address
    QfSpi_Write(Device, Buffer, Length); //  3. Write the data
    QfPlat_DeactivateQF4A512ChipSelect(); //  4. Deactivate /CS

    return Success;
}





/********************************************************************************************//*!

  @summary  Read 'Length' EEPROM bytes into 'Buffer' starting at 'StartingAddr'.

  @param[in]  Device       Device handle
  @param[in]  StartingAddr Register or EEPROM address at which to start writing data
  @param[out] Buffer       Pointer to data to be written
  @param[in]  Length       Number of bytes in WriteBuff to write

  @return   'Success' if configuration successful, otherwise a negative value error code.


  - The EEPROM read interface is as follows.  All fields are msb first and '^'=stable
    on rising edge.

      @verbatim
                                 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3
             0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
      SCLK   ^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^...

      SDO    0 0 0 0 x 0 1 1 [-------- StartingAddr -------] x x x x x x x x x x x x x x x x...

      SDI    x x x x x x x x x x x x x x x x x x x x x x x x [  Buffer[0]  ] [  Buffer[1]  ]...
          _
      /CS  |________________________________________________________________________________...|
            ________________________________________________________________________________
      /DRDY                                                                                 ...
      @endverbatim

  - The Address field of the EEPROM is in little endian byte order, which is opposite
    from the Configuration registers of the QF4A512.  However, this module handles the
    reversal (e.g. there's no need to alter StartingAddr).

*//*********************************************************************************************/

Result qf4a512_ReadEeprom(
        const Handle Device,
        const Count StartingAddr,
        Byte * Buffer,
        const Count Length) {

    //  Sanity check input parameters
    //Assert( Device == SPI0_HANDLE);
    //Assert( StartingAddr + Length  <=  QF4A512_MAX_EEPROM_ADDRESS );
    //AssertNonNull( Buffer );
    //Assert( Length > 0 );


    //  Put device in Configure mode if not there already
    if (DeviceMode != Eeprom) {
        PutQF4A512InEepromMode(Device);
    }


    //  Wait for EEPROM to be ready.
    WaitFor(IsEepromReady(Device) == true);


    //  Atmel AT25320A EEPROM read cycle
    QfPlat_ActivateQF4A512ChipSelect(); // 1. Activate /CS
    QfSpi_WriteByte(Device, QF4A512_EEPROM_READ_INSTRUCTION); // 2. Send the Read instruction
    QfSpi_WriteUInt16(Device, StartingAddr); // 3. Send the address

    QfSpi_Read(Device, Buffer, Length); // 4. Read the data
    QfPlat_DeactivateQF4A512ChipSelect(); // 5. Deactivate /CS

    return Success;
}




/********************************************************************************************//*!

  @summary  Write 'Length' EEPROM bytes from 'Buffer' starting at 'StartingAddr'.

  @param[in]  Device       Device handle
  @param[in]  StartingAddr Register or EEPROM address at which to start writing data
  @param[in]  Buffer       Pointer to data to be written
  @param[in]  Length       Number of bytes in WriteBuff to write

  @return   'Success' if configuration successful, otherwise a negative value error code.


  - The time between CS low and the first SCLK edge is not critical to the device.

  - Data received while performing this write is discarded.

  - EEPROM mode is distinct from Run mode.

  - This function is not aware of the means used by the lower-level HAL to access
    the QF4A512.  It may be interrupt-based, DMA-based or polled.

  - In the diagrams below all fields are msb first and '^'=stable on rising edge.

  - The interface timing for writing EEPROM is as follows.

      @verbatim
                                 1 1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3 3 3 3 3 3 3 3 3
             0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
      SCLK   ^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^...

      SDO    0 0 0 0 x 0 1 0 [-------  StartingAddr  ------] [  Buffer[0]  ] [  Buffer[1]  ]...

      SDI    x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x x...
          _                                                                                     _
      /CS  |________________________________________________________________________________...|
            ________________________________________________________________________________
      /DRDY                                                                                 ...
      @endverbatim

   - Although the time between CS low and the first SCLK edge is not critical, the
     low-to-high transition of the CS pin must occur during the SCK low-time immediately
     after clocking in the D0 (LSB) data bit.

   - After each data byte is received, the EEPROM is received, the five low-order
     address bits are internally incremented by one; the hig-order bits of the
     address will remain constant.  So, to write 32 bytes at a time, start on a
     32-byte boundary.

   - The EEPROM is automatically returned to the write disable state at the completion
     of a write cycle.

   - The Address field of the EEPROM is in little endian byte order, which is opposite
     from the Configuration registers of the QF4A512.  However, this module handles
     the reversal (e.g. there's no need to alter StartingAddr).

*//*********************************************************************************************/

Result qf4a512_WriteEeprom(
        const Handle Device,
        const Count StartingAddr,
        const Byte * Buffer,
        const Count Length) {

    ///  Offset from StartingAddress from which data will be written on current cycle.
    Count AddressOffset = 0;

    ///  EEPROM address to which data will be written on the current cycle
    Count CurrentAddress;

    Count NumRemainingBytes; ///<  Number of bytes still to be written
    Count BytesToWriteThisCycle; ///<  Number of bytes to write on the current cycle



    //  Sanity check input parameters
    //Assert( Device == SPI0_HANDLE);
    //Assert( StartingAddr + Length  <=  QF4A512_MAX_EEPROM_ADDRESS );
    //AssertNonNull( Buffer );
    //Assert( Length > 0 );


    //  Put device in Configure mode if not there already
    if (DeviceMode != Eeprom) {
        PutQF4A512InEepromMode(Device);
    }



    //  Wait for EEPROM to be ready.
    WaitFor(IsEepromReady(Device) == true);



    //  The EEPROM works on 32-byte pages, starting at 32-byte boundaries (e.g. the lower 5
    //  bits are zero).  Loop through as many pages as needed to write all the data, taking
    //  into account the odd sizes that may occur in the first and/or last pages.

    for (NumRemainingBytes = Length;
            NumRemainingBytes > 0;
            NumRemainingBytes -= BytesToWriteThisCycle) {

        CurrentAddress = StartingAddr + AddressOffset;


        //  If address doesn't fall on a page boundary, calculate the number of bytes from
        //  the address up to the next page boundary.  (note that this will only occur on
        //  the first write cycle).

        if (CurrentAddress % QF4A512_EEPROM_PAGE_SIZE > 0) {
            BytesToWriteThisCycle = QF4A512_EEPROM_PAGE_SIZE -
                    (CurrentAddress % QF4A512_EEPROM_PAGE_SIZE);


            //  Also look for the case where the data both starts
            //  and ends within the bounds of a single page.
            if (NumRemainingBytes < BytesToWriteThisCycle) {
                BytesToWriteThisCycle = NumRemainingBytes;
            }
        }

            //  If there is less than one full page of data remaining, the data count is the
            //  size of the write.  (note that this will only occur on the last write cycle).

        else if (NumRemainingBytes < QF4A512_EEPROM_PAGE_SIZE) {
            BytesToWriteThisCycle = NumRemainingBytes;
        }

            //  All writes other than the special cases above are one full page in length.
            //  (note that this can occur on any write cycle, including the first or last).
        else {
            BytesToWriteThisCycle = QF4A512_EEPROM_PAGE_SIZE;
        }



        //  Sanity check the parameters for this write cycle
        //Assert( CurrentAddress >= StartingAddr  &&
        //        CurrentAddress <  StartingAddr + Length );
        //Assert( BytesToWriteThisCycle  <=  QF4A512_EEPROM_PAGE_SIZE );
        //Assert( (GetEepromStatus( Device ) &  0x8c)  == 0 );  // Be sure write protection is off



        //  Atmel AT25320A EEPROM write cycle.
        //
        //     1. Activate /CS
        //     2. Enable writes with the WREN instruction.
        //     3. Deactivate /CS

        QfPlat_ActivateQF4A512ChipSelect();
        QfSpi_WriteByte(Device, QF4A512_EEPROM_WRITE_ENABLE_INSTRUCTION);
        QfPlat_DeactivateQF4A512ChipSelect();

        //Assert( (GetEepromStatus( Device ) & 2) == 2 );   // Double-check write enable


        //     4. Activate /CS
        //     5. Send the Write instruction
        //     6. Send the address
        //     7. Send the data
        //     8. Deactivate /CS

        QfPlat_ActivateQF4A512ChipSelect();
        QfSpi_WriteByte(Device, QF4A512_EEPROM_WRITE_INSTRUCTION);
        QfSpi_WriteUInt16(Device, CurrentAddress);
        QfSpi_Write(Device, Buffer + AddressOffset, BytesToWriteThisCycle);
        QfPlat_DeactivateQF4A512ChipSelect();


        //     9. Wait for Status register to indicate 'Ready'.

        WaitFor(IsEepromReady(Device) == true);


        //  Adjust the write address for the next cycle
        //AddressOffset  +=  BytesToWriteThisCycle;
    }
    return Success;
}




/******************************************************************************************
 ******************************************************************************************
 ********                                                                          ********
 ********                  U t i l i t y   F u n c t i o n s                       ********
 ********                                                                          ********
 ******************************************************************************************
 ******************************************************************************************/




/********************************************************************************************//*!

  @summary  Read a single byte from the QF4A512 Configuration space at 'Address'.

  @param[in]   Device    Device handle
  @param[in]   Address   Device address from which byte will be read

  @return   The byte that was read from the QF4A512.

*//*********************************************************************************************/

inline
Byte qf4a512_ReadConfigByte(
        const Handle Device,
        const Count Address) {
    Byte ConfigValue;

    //  Get the requested configuration byte
    qf4a512_ReadConfigRegisters(
            Device,
            Address,
            &ConfigValue,
            1);

    return ConfigValue;
}




/********************************************************************************************//*!

  @summary  Write a single byte 'Value' to the QF4A512 Configuration space at 'Address'.

  @param[in]   Device    Device handle
  @param[in]   Address   Device address from which byte will be read
  @param[in]   Value     Byte to write to Configuration register

*//*********************************************************************************************/

inline
void qf4a512_WriteConfigByte(
        const Handle Device,
        const Count Address,
        const Byte Value) {
    qf4a512_WriteConfigRegisters(
            Device,
            Address,
            &Value,
            1);
}




/********************************************************************************************//*!

  @summary  Read a single byte from the QF4A512 EEPROM at 'Address'.

  @param[in]   Device    Device handle
  @param[in]   Address   EEPROM address from which byte will be read

  @return   The byte that was read from the QF4A512 EEPROM.

*//*********************************************************************************************/

inline
Byte qf4a512_ReadEepromByte(
        const Handle Device,
        const Count Address) {
    Byte EepromValue;

    //  Get the requested EEPROM byte
    qf4a512_ReadEeprom(
            Device,
            Address,
            &EepromValue,
            1);

    return EepromValue;
}




/********************************************************************************************//*!

  @summary  Write a single byte to the QF4A512 EEPROM at 'Address'.

  @param[in]   Device    Device handle
  @param[in]   Address   EEPROM address to which byte will be written
  @param[in]   Value     Byte to write to Configuration register

*//*********************************************************************************************/

inline
void qf4a512_WriteEepromByte(
        const Handle Device,
        const Count Address,
        const Byte Value) {
    qf4a512_WriteEeprom(
            Device,
            Address,
            &Value,
            1);
}




/********************************************************************************************//*!

  @summary  Stop the continuous sampling of data in Run mode.

  @param[in]  Device  Device handle

  - If this function isn't called after Run mode is finished, the SPI read buffer will
    overflow.

*//*********************************************************************************************/

inline
void qf4a512_ExitRunMode(const Handle Device) {
    PutQF4A512InConfigureMode(Device);
}




/******************************************************************************************
 ******************************************************************************************
 ********                                                                          ********
 ********            L o c a l   ( S t a t i c )   F u n c t i o n s               ********
 ********                                                                          ********
 ******************************************************************************************
 ******************************************************************************************/




/********************************************************************************************//*!

  @summary  Put the specified QF4A512 in Run mode

  @param[in]  Device       Device handle

  - It's OK if the device is already in Run mode.

  - qf4a512_Init() calls this function before this driver is fully operational.  It assumes
    things are done in the manner below.  Check that interaction before changing this function.

*//*********************************************************************************************/

static void PutQF4A512InRunMode(const Handle Device) {
    unsigned char temp[10];
    //  Sanity check Device handle
    //Assert( Device == SPI0_HANDLE);

    if (DeviceMode == Run) {
        return;
    }
        //  Device has to be configured before Run mode.  If in
        //  Eeprom mode, setup for configuration first.
    else if (DeviceMode != Configure) {
        PutQF4A512InConfigureMode(Device);
    }


    //  The SPI_CTRL[ ram_run_mode ] bit must be cleared so the coefficient memory
    //  area can synchronize to the internal clock (clk_sys), not the SPI clock, in
    //  Run mode.
    //
    //  This also sets multi-channel mode, turns parity off, enables autoincrement,
    //  and sets Channel 1 as the fast channel (the one that drives DRDY)
    //  << configure mode >>
    qf4a512_WriteConfigByte(Device, QF4A512_SPI_CTRL_ADDRESS, _0000_1001);
    temp[0] = qf4a512_ReadConfigByte(Device, QF4A512_SPI_CTRL_ADDRESS);
    //  DRDY is an input in Run mode
    QfPlat_SetSpi0DrdyDirection(Input);

    //  Start Run mode
    qf4a512_WriteConfigByte(Device, QF4A512_RUN_MODE_ADDRESS, _0000_0001);

    //  From here on, until the device is put back in Configure or Eeprom mode, the
    //  QF4A512 interface operates differently.  See the QF4A512 datasheet.


    //  Initialize circular frame buffer parameters
    Device0FrameInsertIndex = 0;
    Device0FrameExtractIndex = 0;
    Device0FrameCount = 0;


    //////////////////////////////////////////////////
    // YEB OMITTED
    //////////////////////////////////////////////////
    //  Turn on buffering for the SPI port.  This sets up, but doesn't start data
    //  capture
#ifdef __YEB_INTERRUPT__
    QfSpi_Configure(
            Device,
            SetBufferedReadMode, //  Specify Run mode
            (void *) Device0BufferedReadCallback, //  Call this when each byte arrives
            0);
#endif

    //  Configure DRDY pin interrupts.  A low-to-high on DRDY will start data capture.
    QfPlat_ConfigureDrdyInterrupt(Device0DrdyCallback);

    //  Catch the next high transition of DRDY
    QfPlat_EnableDrdyInterrupts();

    DeviceMode = Run;
}




/********************************************************************************************//*!

  @summary  Put the specified QF4A512 in Configure mode

  @param[in]  Device   Device handle

  - It's OK if the device is already in Configure mode.

*//*********************************************************************************************/

void PutQF4A512InConfigureMode(const Handle Device) {
    Byte CurrentSpiCtrl;

    //  Sanity check Device handle
    //Assert( Device == SPI0_HANDLE);


    if (DeviceMode == Configure) {
        return;
    }
    else if (DeviceMode == Run) {
        ///  Send this to a device in Run mode to put it in Configure mode
        static const Byte ExitRunMode[] = {QF4A512_RUN_MODE_ADDRESS, 0, 0};

        QfPlat_DisableDrdyInterrupts();

        QfSpi_Configure(Device, SetUnbufferedReadMode, NULL, 0);

        //  Get device back to Configure mode

        QfPlat_ActivateQF4A512ChipSelect(); //  1. Activate /CS
        QfSpi_Write(Device, (Byte *) & ExitRunMode, 3); //  2. Send command data
        QfPlat_DeactivateQF4A512ChipSelect(); //  3. Deactivate /CS
    }


    //  This mode drives the DRDY pin as low output
    QfPlat_SetSpi0DrdyState(Low);
    QfPlat_SetSpi0DrdyDirection(Output);

    DeviceMode = Configure;


    //  To access coefficient memory in Configure mode, the SPI_CTRL[ ram_run_mode ]
    //  bit must be cleared so the coefficient area can synchronize to the SPI clock,
    //  not the internal clock (clk_sys).
    //
    //  Warning!  Be sure 'DeviceMode = Configure' before calling any qf4a512_...
    //            functions (as done below), or mayhem might ensue.

    CurrentSpiCtrl = qf4a512_ReadConfigByte(Device, QF4A512_SPI_CTRL_ADDRESS);

    SetBit(CurrentSpiCtrl, 0x01);
    qf4a512_WriteConfigByte(Device, QF4A512_SPI_CTRL_ADDRESS, CurrentSpiCtrl);

}




/********************************************************************************************//*!

  @summary  Put the specified QF4A512 in Eeprom mode

  @param[in]  Device   Device handle

  - It's OK if the device is already in Eeprom mode.

*//*********************************************************************************************/

static void PutQF4A512InEepromMode(const Handle Device) {

    //  Sanity check Device handle
    //Assert( Device == SPI0_HANDLE);

    if (DeviceMode == Eeprom) {
        return;
    }
        //  If device isn't in Configure mode, get it there first.
        //  From there, just set DRDY high to get to Eeprom mode.
    else if (DeviceMode != Configure) {
        PutQF4A512InConfigureMode(Device);
    }


    //  This mode drives the DRDY pin as low output
    QfPlat_SetSpi0DrdyState(High);

    DeviceMode = Eeprom;
}




/********************************************************************************************//*!

  @summary  Read the Status register of the specified QF4A512 device.

  @param[in]  Device   Device handle

  @return   Status byte of EEPROM device, verbatim

  - EEPROM read status register (RDSR) timing.

      @verbatim
                                    1 1 1 1 1 1
                0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5
      SCLK(o)   ^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^

      SDO(o)    0 0 0 0 x 1 0 1 x x x x x x x x

      SDI(i)   x__hi_impedance__[-- data 1 ---]
             _                                  _
      /CS(o)  |________________________________|
               ________________________________
      /DRDY(o)
      @endverbatim

*//*********************************************************************************************/

static Byte GetEepromStatus(const Byte Device) {
    Byte EepromStatus;

    //  Sanity check Device handle
    //Assert( Device == SPI0_HANDLE );

    //  EEPROM Read Status Byte frame

    QfPlat_ActivateQF4A512ChipSelect(); // 1. Activate /CS
    QfSpi_WriteByte(Device, // 2. Send Read Status Command
            QF4A512_EEPROM_READ_STATUS_REGISTER_INSTRUCTION);
    EepromStatus = QfSpi_ReadByte(Device); // 3. Read the Status byte
    QfPlat_DeactivateQF4A512ChipSelect(); // 4. Deactivate /CS

    return EepromStatus;
}




/********************************************************************************************//*!

  @summary  Checks the EEPROM Status register and returns true if the Ready bit is set

  @param[in]  Device   Device handle

  @return  True of the Ready bit is set in the Status register, false if not

*//*********************************************************************************************/

static Bool IsEepromReady(const Byte Device) {
    Byte EepromStatus;

    //  Sanity check Device handle
    //Assert( Device == SPI0_HANDLE);

    EepromStatus = GetEepromStatus(Device);

    return IsBitClear(EepromStatus, QF4A512_EEPROM_STATUS_BUSY_BIT);
}




/********************************************************************************************//*!

  @summary  Called when the DRDY pin goes high

  -  This function is called during an interrupt service routine.  Be sure to keep
     it short and only manipulate things that are appropriate to this context.
*//*********************************************************************************************/

static void Device0DrdyCallback(void) {
    Byte temp[3 * QF4A512_NUM_CHANNELS_ENABLED];

    //  Initialize frame buffer parameters
    Device0ByteNum = 1;
    Device0Channel = 0;

    //  Don't allow DRDY interrupts while reading SPI
    QfPlat_DisableDrdyInterrupts();

    //  Activate Chip Select  (/CS)
    QfPlat_ActivateQF4A512ChipSelect();

    //////////////////////////////////////////////////
    // YEB
    //////////////////////////////////////////////////
    //  SPI receive is already configured, it just needs to be resumed.

#ifdef __YEB_INTERRUPT__
    QfSpi_ResumeReceive(SPI0_HANDLE);
#else
#ifndef __YEB_IMMEDIATE__
    getYeb(3 * QF4A512_NUM_CHANNELS_ENABLED, yebCallback);
#else
    //getYebImmediate(temp, 3 * QF4A512_NUM_CHANNELS_ENABLED);
    if (DeviceMode == Run) {
        yebCallCallBack = 1;
        //yebCallback();
    }
#endif
#endif
}

#ifndef __YEB_INTERRUPT__

Bool IsYebCallBackCalled(void) {
    return yebCallCallBack;
}

void yebCallback(void) {
    //YEB
    //unsigned char i;
    //unsigned char* result;

    for (;;)//i = 0; i < QF4A512_NUM_CHANNELS_ENABLED; i += 3)
    {
        if (!Device0BufferedReadCallback(ReadSPI())) {
            break;
        }
    }
    yebCallCallBack = 0;
}
#endif

//  Suppress  "Warning[Pa082]: undefined behavior: the order of volatile accesses is
//  undefined in this statement..." that occurs below.  The order is unimportant here.

//#pragma  diag_suppress = Pa082




/********************************************************************************************//*!

  @summary  Called by the Device0 read ISR every time a byte is received (in Buffered mode).

  - This function is called during an interrupt service routine.  Be sure to keep
    it as short as possible and only manipulate things that are appropriate to this context.

  - Since the 16-bit runtime sample data comes out msb first, and QfSpi_Read() returns bytes
    in the order they are received, the samples in Data are in big endian byte order.  The
    MakeUInt16 macro hides the byte swapping, but be aware of that it does occur.

  - Note that the New bit, in the Flags byte, isn't checked because this function assumes
    all channels are sampling at the same frequency.  If DRDY goes high for the 'fastest'
    channel, the others must have new data too.

  - The time between CS low and the first SCLK edge is not critical to the device.

  - Run mode data comes out of the QF4A512 as a set of 3-byte frames, as shown below,
    with one frame for each active channel.  Note that every active channel produces
    a frame, even if the channels have dissimilar sampling rates and a channel has no
    new data (see the New Data bit).

    @verbatim
                                 1 1 1 1 1 1 1 1 1 1 2 2 2 2
             0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
      SCLK   ^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^-^...

      SDO    [-- address --] [--- data ----] x x x x x x x x

      SDI    0 1 2 3 [rsvd ] [-------- channel data -------]
             ^ ^ ^ ^
             | | | New Data
             | | Channel ID 0
             | Channel ID 1
             Odd Parity
          _                                                   _
      /CS  |_________________________________________________|

      /DRDY _________________________________________________...

    @endverbatim

*//*********************************************************************************************/
// YEB OMITTED
////////////////
//#ifdef __YEB_INTERRUPT__
volatile Byte HighByte;

static Bool Device0BufferedReadCallback(Byte NewByte) {
    ///  High byte of the current sample
    //static volatile Byte  HighByte;
    //  Handling varies depending on which byte is being processed

    switch (Device0ByteNum) {
        case 1: //  Flags byte (ignored)
            //  Verify the channel number in Flags corresponds with our value
            //Assert( (NewByte & CHANNEL_NUM_MASK) >> CHANNEL_NUM_OFFSET  ==  Device0Channel );

            //  Verify the New bit is set
            //Assert( IsBitSet( NewByte, QF4A512_NEW_DATA_BIT ) );

            Device0ByteNum = 2;
            break;

        case 2: //  High byte of sample (save for later)

            HighByte = NewByte;
            Device0ByteNum = 3;
            break;

        case 3: //  Low byte of sample
        {
            Device0ReadBuffer[ Device0FrameInsertIndex ][ Device0Channel ] = MakeUInt16(HighByte, NewByte);
            Device0ByteNum = 1;

            //  Advance sample count
            Device0Channel++;

            //  Perform extra processing at the end of the frame
            if (Device0Channel == QF4A512_NUM_CHANNELS_ENABLED) {
                //  Cycle /CS.  Note - /CS has to cycle between frames for
                //  new data to be latched into the output shift register.
                //  If not cycled, the existing samples will be repeated.
                QfPlat_DeactivateQF4A512ChipSelect();

                //  Advance frame index to next position.  Wrap to the
                //  the beginning if it goes beyond the end.
                Device0FrameInsertIndex++;
                Device0FrameInsertIndex %= FRAME_CAPACITY_OF_DEVICE0_READ_BUFFER;

                //  Increase the count of frames in Device0ReadBuffer
                Device0FrameCount++;

                //  Be sure buffer isn't being overflowed
                //Assert( Device0FrameCount  <  FRAME_CAPACITY_OF_DEVICE0_READ_BUFFER );

                //  Catch the next high transition of DRDY.
                QfPlat_EnableDrdyInterrupts();
                return false;
            }
        }
    }
    return true;
}
//#endif
