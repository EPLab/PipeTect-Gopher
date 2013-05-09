/*****************************  (C) Quickfilter Technologies, Inc.  *************************//*!

  @file  Qf4a512-access.h

  Raw data transfer functions and device mode control of QF4A512 (Small model).

  $Id: Qf4a512-access.h 120 2006-07-19 16:11:20Z jhopson $

  *******************************************************************************************

  @notes
    -#  The structures in this file must be packed (no space between elements).   The 'pack(1)'
        pragma is for the IAR compiler, but it shoul be benign with other compilers.

*///*********************************************************************************************


#if !defined(QF4A512_ACCESS_H_INCLUDED)                //  Inclusion control
#    define  QF4A512_ACCESS_H_INCLUDED



#include  "Project.h"


///  Number of channels in a QF4A512 device
#define  QF4A512_NUM_CHANNELS    4


///  Maximum number of FIR coefficients in each channel
#define  QF4A512_NUM_FIR_COEFFICIENTS_PER_CHANNEL    256


///  Number of bytes in each FIR filter coefficient.
#define  QF4A512_NUM_BYTES_PER_FIR_COEFFICIENT     3


///  Maximum of G & H coefficients in each channel
#define  QF4A512_NUM_GH_COEFFICIENTS_PER_CHANNEL    64



/********************************************************************************************//*!

  @summary  Channel and FIR configuration for one individual channel.

  - Below is the memory map for the channel configuration area.
       @par
       @verbatim
         +----------------------------------------+ 00EA
         |             E2h   (reserved)    (8)    |     <-- note less reserved space
         |  Channel    E1h   Maintenance   (1)    |         on Channel 4
         |     4       C2h   Configuration (31)   |
         |             C0h   Run & Status  (2)    |
         +----------------------------------------+ 00C0
         |             B2h   (reserved)    (14)   |
         |  Channel    B1h   Maintenance   (1)    |
         |     3       92h   Configuration (31)   |
         |             90h   Run & Status  (2)    |
         +----------------------------------------+ 0090
         |             82h   (reserved)    (14)   |
         |  Channel    81h   Maintenance   (1)    |
         |     2       62h   Configuration (31)   |
         |             60h   Run & Status  (2)    |
         +----------------------------------------+ 0060
         |             52h   (reserved)    (14)   |
         |  Channel    51h   Maintenance   (1)    |
         |     1       32h   Configuration (31)   |
         |             30h   Run & Status  (2)    |
         +----------------------------------------+ 0030
       @endverbatim


  - This structure must be packed because some two-byte registers are at odd addresses.

*//*********************************************************************************************/

//#pragma pack(1)

typedef struct {               //   Offset          Description
                               //   ------          -----------
    Byte    CH1_PGA;           ///<  Offset +0h.     Control Register. Enable FIR operation, set PGA gain.
    Byte    CH1_STAT;          ///<  Offset +1h.     Channel Status

    Byte    CH1_CFG;           ///<  Offset +2h.     Channel configuration
    UInt16  AREC_1_GAIN;       ///<  Offset +3/4h.   AREC gain control
    UInt16  CHPC_1_DIV;        ///<  Offset +5/6h.   Chopper period setting
    UInt16  CIC_1_R;           ///<  Offset +7/8h.   CIC decimation, R value
    Byte    CIC_1_R_H;         ///<  Offset +9h.     CIC decimation, R value
    Byte    CIC_1_SHIFT;       ///<  Offset +Ah.     CIC shift

    Byte    FIR_0_0_CTRL;      ///<  Offset +Bh.     FIR Control, filter 0
    Byte    FIR_0_0_NMIN_F1;   ///<  Offset +Ch.     Minimum storage address for f1
    Byte    FIR_0_0_NMAX_F1;   ///<  Offset +Dh.     Maximum storage address for f1
    Byte    FIR_0_0_CMIN_F1;   ///<  Offset +Eh.     Minimum coefficient storage address for f1
    Byte    FIR_0_0_CMAX_F1;   ///<  Offset +Fh.     Maximum coefficient storage address for f1
    Byte    FIR_0_0_NMIN_F2;   ///<  Offset +10h.    Minimum storage address for f2
    Byte    FIR_0_0_NMAX_F2;   ///<  Offset +11h.    Maximum storage address for f2
    Byte    FIR_0_0_CMIN_F2;   ///<  Offset +12h.    Minimum coefficient storage address for f2
    Byte    FIR_0_0_CMAX_F2;   ///<  Offset +13h.    Maximum coefficient storage address for f2

    Byte    FIR_0_1_CTRL;      ///<  Offset +14h.    FIR Control, filter 1
    UInt16  FIR_0_1_NMIN_F1;   ///<  Offset +15/16h. Minimum storage address for f1
    UInt16  FIR_0_1_NMAX_F1;   ///<  Offset +17/18h. Maximum storage address for f1
    Byte    FIR_0_1_CMIN_F1;   ///<  Offset +19h.    Minimum coefficient storage address for f1
    Byte    FIR_0_1_CMAX_F1;   ///<  Offset +1Ah.    Maximum coefficient storage address for f1
    UInt16  FIR_0_1_NMIN_F2;   ///<  Offset +1B/1Ch. Minimum storage address for f2
    UInt16  FIR_0_1_NMAX_F2;   ///<  Offset +1D/1Eh. Maximum storage address for f2
    Byte    FIR_0_1_CMIN_F2;   ///<  Offset +1Fh.    Minimum coefficient storage address for f2
    Byte    FIR_0_1_CMAX_F2;   ///<  Offset +20h.    Maximum coefficient storage address for f2

    Byte    CH1_SRST;          ///<  Offset +21h.  Channel soft reset

}  qf4a512_ChannelConfigRegs;

//#pragma pack()




/********************************************************************************************//*!

  @summary  Represents all registers in the QF4A512 device.

  - Below is the memory map for the entire device.

       @par
       @verbatim
        +----------------------------------------+ 00F0
        |          Die Rev & Calibration         |
        +----------------------------------------+ 00EA
        |             E2h   (reserved)    (8)    |     <-- note less reserved space
        |  Channel    E1h   Maintenance   (1)    |         on Channel 4
        |     4       C2h   Configuration (31)   |
        |             C0h   Run & Status  (2)    |
        +----------------------------------------+ 00C0
        |             B2h   (reserved)    (14)   |
        |  Channel    B1h   Maintenance   (1)    |
        |     3       92h   Configuration (31)   |
        |             90h   Run & Status  (2)    |
        +----------------------------------------+ 0090
        |             82h   (reserved)    (14)   |
        |  Channel    81h   Maintenance   (1)    |
        |     2       62h   Configuration (31)   |
        |             60h   Run & Status  (2)    |
        +----------------------------------------+ 0060
        |             52h   (reserved)    (14)   |
        |  Channel    51h   Maintenance   (1)    |
        |     1       32h   Configuration (31)   |
        |             30h   Run & Status  (2)    |
        +----------------------------------------+ 0030
        |           Global Maintenance           |
        +----------------------------------------+ 001D
        |          Global Configuration          |
        +----------------------------------------+ 0011
        |              Run & Status              |
        +----------------------------------------+ 0009
        |             EEPROM Startup             |
        +----------------------------------------+ 0005
        |               High Level               |
        +----------------------------------------+ 0000
       @endverbatim


  - Below is an alternate view of the memory map showing runtime visibility,
    by mode, and the EEPROM space.

       @par
       @verbatim
                                    Registers

                        ...    +------------------+ 3FFF
                        .      |      Unused      |
                        .      +------------------+ 2400
                        .      |   Filter Data    |                         EEPROM
                        .      |                  |
          Visibility    .      +------------------+ 1000                +------------+ FFF
          ----------    .      |      Unused      |                     | User Space |
                        .      +------------------+ 0F00  . . . . . . . +------------+ F00
          Configure .....      |      Filter      |                     |            |
            Mode        .      |   Coefficients   |         One-to-One  |            |
                        .      |                  |          Mapping    |            |
                      __.__    +------------------+ 0100                +------------+
            Run    __|  .      | Control & Status |         <========>  |            |
            Mode     |  .      |    Registers     |                     |            |
        (write only) |__.__    +------------------+ 0000  . . . . . . . +------------+ 000
       @endverbatim


  - This structure must be packed because some two-byte registers are at odd addresses.

*//*********************************************************************************************/


//#pragma pack(1)
                             //   Addr       Description
typedef struct {             //   ----       -----------

    ///  High-level configuration registers

    Byte  GLBL_SW;           ///<  Addr 0h.  Dummy RAM register.  For testing device reads & writes
    Byte  GLBL_ID;           ///<  Addr 1h.  Chip ID Including Revision Number
    Byte  FULL_SRST;         ///<  Addr 2h.  Activates all soft resets
    Byte  GLBL_CH_CTRL;      ///<  Addr 3h.  Reset, Enable or Power Down each channel
    Byte  RUN_MODE;          ///<  Addr 4h.  Set chip in Run or Configure Mode


    ///  EEPROM Startup

    Byte  EE_TRANS;          ///<  Addr 5h.   Control data transfers to/from EEPROM
    Byte  EE_COPY;           ///<  Addr 6h.   Control full transfers to/from EEPROM
    Byte  STARTUP;           ///<  Addr 7h.   Set startup configuration, rate for EEPROM clock
    Byte  INIT_COUNT;        ///<  Addr 8h.   Initialization delay counter


    ///  Run & Status

    Byte  ENABLE_0;          ///<  Addr 9h.   Enable ADC and system clock per channel
    Byte  ENABLE_1;          ///<  Addr Ah.   Enable AAF per channel, ADC operation mode
    Byte  ENABLE_2;          ///<  Addr Bh.   Designate active channels
    Byte  PLL_SIF_STAT;      ///<  Addr Ch.   PLL lock, SIF address out of range
    Byte  EE_VAL;            ///<  Addr Dh.   EEPROM status register value
    Byte  EE_STATUS;         ///<  Addr Eh.   EEPROM transfer status flags
    Byte  ADC_STATUS_0;      ///<  Addr Fh.   ADC out of range, per channel
    Byte  ADC_STATUS_1;      ///<  Addr 10h.  ADC out of range, high or low, per channel


    ///  Global Configuration

    Byte    PLL_CTRL_0;      ///<  Addr 11h.     PLL Pre-divider, frequency range.
    Byte    PLL_CTRL_1;      ///<  Addr 12h.     PLL loop divider.
    Byte    ADC_CLK_RATE;    ///<  Addr 13h.     Clock rate for ADC, CRC and AREC.
    Byte    SYS_CLK_CTRL;    ///<  Addr 14h.     System Clock control.
    Byte    SPI_CTRL;        ///<  Addr 15h.     Set single-, multi-channel mode
    Byte    SPI_MON;         ///<  Addr 16h.     Monitor internal data transfers
    UInt16  EE_STADDR;       ///<  Addr 17/18h.  EE start address for block transfers (byte0)
    UInt16  SIF_STADDR;      ///<  Addr 19/1Ah.  Chip start address for block transfers (byte0)
    UInt16  END_ADDR;        ///<  Addr 1B/1Ch.  Ending address for block transfers (byte0)


    ///  Global Maintenance

    Byte  SCRATCH[ 8 ];      ///<  Addr 1Dh-24h.  RAM registers.  Available for any runtime use.
    Byte  SU_UNLOCK;         ///<  Addr 25h.      Lock bit for test/maintenance (factory use only)
    Byte  GLBL_SRST;         ///<  Addr 26h.      Global soft resets
    Byte  ADC_CTRL;          ///<  Addr 27h.      ADC control.
    Byte  AREC_CTRL;         ///<  Addr 28h.      AREC control.
    Byte  pad1[ 7 ];


    //  Array of channel configuration information.  (Note - there's no padding after Chan4

    qf4a512_ChannelConfigRegs  Channel1Config;    ///<  Addr 30h.   Channel 1 configuration
                         Byte  pad2[ 14 ];
    qf4a512_ChannelConfigRegs  Channel2Config;    ///<  Addr 60h.   Channel 2 configuration
                         Byte  pad3[ 14 ];
    qf4a512_ChannelConfigRegs  Channel3Config;    ///<  Addr 90h.   Channel 3 configuration
                         Byte  pad4[ 14 ];
    qf4a512_ChannelConfigRegs  Channel4Config;    ///<  Addr C0h.   Channel 4 configuration
                         Byte  pad5[ 8 ];


    //  A few registers are tucked in the 'dead' space after Channel 4
    //  configuration.  Most of them are factory test, so they aren't
    //  included here.

    Byte  DIE_REV;                                ///<  Addr EAh.  Revision of the silicon die
    Byte  pad6[ 21 ];


    ///  Array of G & H filter coefficients for each channel.

    UInt16  GHCoefficients[ QF4A512_NUM_CHANNELS ]
                          [ QF4A512_NUM_GH_COEFFICIENTS_PER_CHANNEL ];


    ///  Array of FIR coefficients for each channel.  Since the coefficients are 3 bytes
    ///  in length, and there is no 3-byte type in most C compilers, coefficients
    ///  are treated as three byte arrays (hence the third dimension below).

    Byte  FirCoefficients[ QF4A512_NUM_CHANNELS ]
                         [ QF4A512_NUM_FIR_COEFFICIENTS_PER_CHANNEL ]
                         [ QF4A512_NUM_BYTES_PER_FIR_COEFFICIENT ];


}  qf4a512_GlobalRegisters;

//#pragma pack()




///  Static value of the CHIP_ID register for a QF4A512
#define  QF4A512_CHIP_ID_NUMBER    0xA0

///  Minimum value of DIE_REV for compatibility with this module (may be higher)
#define  QF4A512_MINIMUM_DIE_REV_NUMBER    0xC1

///  Length of one full frame of data (from /CS low to /CS high again)
#define  QF4A512_LENGTH_OF_FULL_FRAME   (QF4A512_LENGTH_OF_SINGLE_CHAN_FRAME  * \
                                         QF4A512_NUM_CHANNELS_ENABLED)

///  Length of one frame of data from one channel.  A QF4A512 channel has a Flags byte and two data bytes.
#define  QF4A512_LENGTH_OF_SINGLE_CHAN_FRAME   3

///  Bit position, in the Flags byte of the Run mode data stream, of the bit indicating new data
#define  QF4A512_NEW_DATA_BIT   BIT4




///  Lowest address of the G & H filter coefficient memory
#define  QF4A512_MIN_GH_FILTER_COEFF_ADDRESS    \
            GetElementOffset( qf4a512_GlobalRegisters, GHCoefficients )


///  Lowest address of the User FIR filter coefficient memory
#define  QF4A512_MIN_FILTER_COEFF_ADDRESS    \
            GetElementOffset( qf4a512_GlobalRegisters, FirCoefficients )


///  Highest address of the filter coefficient memory
#define  QF4A512_MAX_FILTER_COEFF_ADDRESS     sizeof(qf4a512_GlobalRegisters)


///  Maximum address of EEPROM
#define  QF4A512_MAX_EEPROM_ADDRESS    0xfff


///  Maximum useful configuration address.  This address leaves out the filter coefficients
///  between 0x1000 and 0x2400, but none of the functions in this module access that area.
#define  QF4A512_MAX_REGISTER_ADDRESS     QF4A512_MAX_FILTER_COEFF_ADDRESS




///////////////////////////////////////////////////////////////////////////////////
//  Addresses of common registers within the QF4A512


///  Address of the Chip ID register
#define  QF4A512_GLBL_ID_ADDRESS     GetElementOffset( qf4a512_GlobalRegisters, GLBL_ID )

///  Address of the Chip ID register
#define  QF4A512_FULL_SRST_ADDRESS   GetElementOffset( qf4a512_GlobalRegisters, FULL_SRST )

///  Address of the Die Revision register
#define  QF4A512_RUN_MODE_ADDRESS    GetElementOffset( qf4a512_GlobalRegisters, RUN_MODE )

///  Address of the Die Revision register
#define  QF4A512_DIE_REV_ADDRESS     GetElementOffset( qf4a512_GlobalRegisters, DIE_REV )

///  Address of the SPI Control register
#define  QF4A512_SPI_CTRL_ADDRESS    GetElementOffset( qf4a512_GlobalRegisters, SPI_CTRL )




///  Configuration options for the QF4A512 port.
typedef enum  {

    SetIdleMode,
    SetRunMode,
    WriteConfigRegisters,
    ReadConfigRegisters,
    ReadEeprom,
    WriteEeprom

} qf4a512_ConfigRequest;




#ifdef __cplusplus
   extern "C"
{                            //  C++ source requires this linkage specification
#endif


void  qf4a512_Init( void );

void  qf4a512_DeInit( void );

Result  qf4a512_ReadSamples(
    const Handle   Device,
          UInt16   Buffer [][ QF4A512_NUM_CHANNELS_ENABLED ],
    const Byte    Length);

void  qf4a512_ReadConfigRegisters(
    const Handle  Device,
          Count   StartingAddr,
          Byte  * Buffer,
    const Count   Length);

Result  qf4a512_WriteConfigRegisters(
    const Handle  Device,
          Count   StartingAddr,
    const Byte  * Buffer,
    const Count   Length);

Result  qf4a512_ReadEeprom(
    const Handle  Device,
    const Count   StartingAddr,
          Byte  * Buffer,
    const Count   Length);

Result  qf4a512_WriteEeprom(
    const Handle  Device,
    const Count   StartingAddr,
    const Byte  * Buffer,
    const Count   Length);

Byte  qf4a512_ReadConfigByte(
    const  Handle  Device,
    const  Count   Address );

void  qf4a512_WriteConfigByte(
    const  Handle  Device,
    const  Count   Address,
    const  Byte    Value);

void  qf4a512_WriteEepromByte(
    const  Handle  Device,
    const  Count   Address,
    const  Byte    Value);

Byte  qf4a512_ReadEepromByte(
    const  Handle  Device,
    const  Count   Address);

void  qf4a512_ExitRunMode(
    const Handle  Device );

#ifndef __YEB_INTERRUPT__
extern void yebCallback(void);
extern Bool IsYebCallBackCalled(void);
#endif

#ifdef __cplusplus
}                                       //  End of C++ linkage specification
#endif


#endif
