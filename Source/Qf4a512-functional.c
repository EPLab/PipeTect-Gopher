/*****************************  (C) Quickfilter Technologies, Inc.  *************************//*!

  @file  Qf4a512-functional.c

  Implementation of high-level Qf4a512 features (Small model).

  $Id: Qf4a512-functional.c 121 2006-07-24 20:17:09Z jhopson $

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
      - Device:            QF4A512, SPI port + portable SPI API
      - CPU byte order:    little endian

    -# This portable C file implements the QF4A512 Library layer in the figure below.
            @verbatim
              +-------------+------------------------------------------+          This file
              |             |             Application Code             |         ------------
              |             |                                          |
              |  Standard   |            +-----------------------------+ <--- presents this API
              |      C      |            |  QF4A512 Functional Driver  |
              |  Libraries  +------------+-----------------------------+ ---> & calls this API
              |             |            QF4A512 Access Driver         |     (& some standard C
              |             +------------------------------------------+      library functions)
              |             |  SPI Hardware Abstraction Library (HAL)  |
              +-------------+------------------------------------------+
            @endverbatim

       This file is the front-line API for an applications programmer controlling a QF4A512.
       Although the lower level API (@ref Qf4a512-access.c) could be called directly from an
       application, it is intended that the functions in this file be used where possible.

       This code does not directly access any hardware.  It calls the access driver to send
       and receive data to and from the QF4A512.

    -# This code does not support device calibration.


  @references
     -# "QF4A512 4-Channel Programmable Signal Converter", Rev C3, Apr 06, Quickfilter
        Technologies, Inc., www.quickfiltertech.com/files/QF4A512revC3.pdf
     -# "SPI Serial EEPROMS", 3347J-SEEPR-10/05, Atmel Corp.,
        www.atmel.com/dyn/resources/prod_documents/doc3347.pdf
     -# "doxygen", Version 1.4.6, Dimitri van Heesch, doxygen.org

*///*********************************************************************************************


#include  "Project.h"
#include  "Platform.h"
#include  "Qf4a512-access.h"
#include  "Qf4a512-functional.h"                    //  Self include

#define __MULTI_SAMPLE_RATES_ENABLED
#ifdef __MULTI_SAMPLE_RATES_ENABLED
#include  "QFImageRegisterTable.h"
#else
#include "QF.h"
#endif

const rom unsigned char MASK_ARRAY[0x100] = {0xFF, 0xFF, 0x01, 0xFF, //0
    0x01, 0x07, 0x03, 0xFF,
    0xFF, 0xF3, 0x3F, 0xFF,
    0x02, 0xFF, 0xFF, 0x0F,

    0xFF, 0x7F, 0x3F, 0x07, //1
    0x17, 0x7F, 0x03, 0xFF,
    0x0F, 0xFF, 0x3F, 0xFF,
    0x3F, 0xFF, 0xFF, 0xFF,

    0xFF, 0xFF, 0xFF, 0xFF, //2
    0xFF, 0x01, 0x1F, 0x0F,
    0x0F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x13, 0xF7, 0xF7, 0x00, //3
    0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0xFF, 0xF7,
    0x7F, 0x7F, 0x3F, 0x3F,

    0x7F, 0x7F, 0x3F, 0x3F, //4
    0xF7, 0xFF, 0x01, 0x00,
    0x01, 0xFF, 0xFF, 0xFF,
    0x01, 0xFF, 0x01, 0xFF,

    0xFF, 0x1F, 0x00, 0x00, //5
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x13, 0xF7, 0xF7, 0x00, //6
    0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0xFF, 0xF7,
    0x7F, 0x7F, 0x3F, 0x3F,

    0x7F, 0x7F, 0x3F, 0x3F, //7
    0xF7, 0xFF, 0x01, 0x00,
    0x01, 0xFF, 0xFF, 0xFF,
    0x01, 0xFF, 0x01, 0xFF,

    0xFF, 0x1F, 0x00, 0x00, //8
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x13, 0xF7, 0xF7, 0x00, //9
    0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0xFF, 0xF7,
    0x7F, 0x7F, 0x3F, 0x3F,

    0x7F, 0x7F, 0x3F, 0x3F, //A
    0xF7, 0xFF, 0x01, 0x00,
    0x01, 0xFF, 0xFF, 0xFF,
    0x01, 0xFF, 0x01, 0xFF,

    0xFF, 0x1F, 0x00, 0x00, //B
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,

    0x13, 0xF7, 0xF7, 0x00, //C
    0xFF, 0x00, 0xFF, 0x00,
    0x00, 0xFF, 0xFF, 0xF7,
    0x7F, 0x7F, 0x3F, 0x3F,

    0x7F, 0x7F, 0x3F, 0x3F, //D
    0xF7, 0xFF, 0x01, 0x00,
    0x01, 0xFF, 0xFF, 0xFF,
    0x01, 0xFF, 0x01, 0xFF,

    0xFF, 0x1F, 0x00, 0x00, //E
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0x0F, 0x1F, 0xFF, 0xFF,

    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00};



/************************************************************************************************
    L o c a l   C o n s t a n t s ,   M a c r o s   a n d   T y p e s
 ************************************************************************************************/


/************************************************************************************************
    L o c a l   V a r i a b l e s
 ************************************************************************************************/


/************************************************************************************************
    L o c a l   F u n c t i o n   P r o t o t y p e s
 ************************************************************************************************/



/******************************************************************************************
 ******************************************************************************************
 ********                                                                          ********
 ********                   P u b l i c   F u n c t i o n s                        ********
 ********                                                                          ********
 ******************************************************************************************
 ******************************************************************************************/




/********************************************************************************************//*!

  @summary  Load a table of address/value pairs into the QF4A512 configuration registers.

  @param[in]   Device       Device handle
  @param[in]   Table        Pointer to array of qf4a512_ConfigTableEntry structures
  @param[in]   SizeOfTable  Dimension of the 'Table' array

  @return   'Success' if configuration successful, otherwise a negative value error code.


  - 'Table' is typically generated by the Quickfilter Pro PC design software.  Its name is
    QFImageRegisterTable.  The number of entries in that table is held in
    QF_IMAGE_REGISTER_TABLE_DIMENSION, so a typical call to this function would be

    @code
        qf4a512_WriteImageRegisterTableToEeprom(
            SPI0_HANDLE,
            (qf4a512_ConfigTableEntry *)QFImageRegisterTable,
            QF_IMAGE_REGISTER_TABLE_DIMENSION);
    @endcode

  - Writing the table one byte at a time, as this function does, is not very efficient, but
    the configuration table entries are address/data pairs, so optimzing the number of writes
    would consume memory and code space.  Hopefully, this function won't be called much, and
    when it is called, time will not be at a premium.

*//*********************************************************************************************/
unsigned char val;
unsigned char ttemp;

#ifdef __MULTI_SAMPLE_RATES_ENABLED
Result qf4a512_LoadImageRegisterTable(void) {
    unsigned char SampleRate = 1; //---> The parameter that determines which sample rate image will be used
    Count TableIndex;
    unsigned int addr = 0;
    //unsigned char val;
    //unsigned char temp;
    unsigned char mask;
    unsigned char count = 0;
    //unsigned char * SRptr = (unsigned char *)QFImageRegisterTable;

    //  Sanity check input parameters
    //Assert( Device == SPI0_HANDLE);
    //AssertNonNull( Table );
    //Assert( SizeOfTable > 0 );
    //  Write each register specified in the table


    for (TableIndex = 0; TableIndex < QFImageRegisterTableSize[SampleRate]; TableIndex++) {
        //Assert( Table[ TableIndex ].Address  <  QF4A512_MAX_FILTER_COEFF_ADDRESS );
        val = QFImageRegisterTable[TableIndex][SampleRate];
        //val = *(SRptr + (TableIndex * 3 ) +  SampleRate);

        qf4a512_WriteConfigByte(0, TableIndex, val);
        ttemp = qf4a512_ReadConfigByte(0, TableIndex);

        if (TableIndex > 0x100) {
            if (val != ttemp) {
                --TableIndex;
                ++count;
                if (count == 100) {
                    count = 0;
                    Reset();
                }
            } else {
                count = 0;
            }
        }
        /*
        else
        {
                mask = MASK_ARRAY[TableIndex];
                if ((temp & mask & val) != (val & mask))
                {
                        --TableIndex;
                        ++count;
                        if (count == 100)
                        {
                                Reset();
                        }
                }
                else
        {
                count = 0;
            }
        }
         */
        //  Verify coefficient writes in a Debug build.  Control area writes (0x0
        //  to 0x100) aren't verified because read only bits that differ with
        //  written data cause false errors during readback.

#if  defined(Debug)
        if (TableIndex >= QF4A512_MIN_GH_FILTER_COEFF_ADDRESS &&
                TableIndex <= QF4A512_MAX_FILTER_COEFF_ADDRESS) {
            //Assert( Table[ TableIndex ].Value  ==
            //        qf4a512_ReadConfigByte( Device, Table[ TableIndex ].Address ));
        }
#endif

    }
    return Success;
}

#else

Result  qf4a512_LoadImageRegisterTable(void)
{
    Count  TableIndex;
    unsigned int addr;
    unsigned char val;
    unsigned char temp;
    unsigned char mask;
    unsigned char count = 0;
    //  Sanity check input parameters
    //Assert( Device == SPI0_HANDLE);
    //AssertNonNull( Table );
    //Assert( SizeOfTable > 0 );
	
    //  Write each register specified in the table

    for( TableIndex = 0;
         TableIndex < QFImageRegisterTableSize;
         TableIndex++ )
    {
        //Assert( Table[ TableIndex ].Address  <  QF4A512_MAX_FILTER_COEFF_ADDRESS );
        ClrWdt();
        addr = QFImageRegisterTable[TableIndex].uiAddress;
        val = QFImageRegisterTable[TableIndex].ucValue;	
        qf4a512_WriteConfigByte(0, addr, val); 
        temp = qf4a512_ReadConfigByte( 0, addr );
        
		if (TableIndex > 0x100)
		{
		 	if (val != temp)
        	{
	    		--TableIndex;
	    		++count;
	    		if (count == 100)
	    		{
		    		Reset();
		    	}
	    	}
	    	else
	    	{
		    	count = 0;
		    }
	 	}
	 	/*
		else
	 	{
		 	mask = MASK_ARRAY[TableIndex];
			if ((temp & mask & val) != (val & mask))
			{
				--TableIndex;
				++count;
				if (count == 100)
				{
					Reset();
				}
			}
			else
	    	{
		    	count = 0;
		    }
		}
		*/		
        //  Verify coefficient writes in a Debug build.  Control area writes (0x0
        //  to 0x100) aren't verified because read only bits that differ with
        //  written data cause false errors during readback.

#if  defined(Debug)
        if( TableIndex  >=  QF4A512_MIN_GH_FILTER_COEFF_ADDRESS    &&
            TableIndex  <=  QF4A512_MAX_FILTER_COEFF_ADDRESS )
        {
            //Assert( Table[ TableIndex ].Value  ==
            //        qf4a512_ReadConfigByte( Device, Table[ TableIndex ].Address ));
        }
#endif

    }
    return Success;
}

#endif



/********************************************************************************************//*!

  @summary  Write 'Table' to the QF4A512 EEPROM.

  @param[in]   Device       Device handle
  @param[in]   Table        Pointer to array of qf4a512_ConfigTableEntry structures
  @param[in]   SizeOfTable  Dimension of the 'Table' array

  @return   'Success' if configuration successful, otherwise a negative value error code.


  - 'Table' is typically generated by the Quickfilter Pro PC design software.  Its name is
    QFImageRegisterTable.  The number of entries in that table is held in
    QF_IMAGE_REGISTER_TABLE_DIMENSION, so a typical call to this function would be

    @code
        qf4a512_WriteImageRegisterTableToEeprom(
            SPI0_HANDLE,
            (qf4a512_ConfigTableEntry *)QFImageRegisterTable,
            QF_IMAGE_REGISTER_TABLE_DIMENSION);
    @endcode

  - Writing the table one byte at a time, as this function does, is not very efficient, but
    the configuration table entries are address/data pairs, so optimzing the number of writes
    would consume memory and code space.  Hopefully, this function won't be called much, and
    when it is called, time will not be at a premium.

*//*********************************************************************************************/

inline
Result qf4a512_WriteImageRegisterTableToEeprom(
        const Handle Device,
        const unsigned short SizeOfTable,
        const qf4a512_ConfigTableEntry * Table) {
    Count TableIndex;


    //  Sanity check input parameters
    //Assert( Device == SPI0_HANDLE);
    //AssertNonNull( Table );
    //Assert( SizeOfTable > 0 );


    //  Write each register specified in the table

    for (TableIndex = 0;
            TableIndex < SizeOfTable;
            TableIndex++) {
        //val = *(SRptr + (TableIndex * 3 ) +  SampleRate);

        qf4a512_WriteEepromByte(
                Device,
                Table[ TableIndex ].Address,
                Table[ TableIndex ].Value);

        //  Verify writes in a Debug build.

        //Assert( Table[ TableIndex ].Value  ==
        //        qf4a512_ReadEepromByte( Device, Table[ TableIndex ].Address ));
    }


    return Success;
}




/********************************************************************************************//*!

  @summary  Software reset the specified QF4A512.

  @param[in]  Device       Device number.

  - After the device is reset, it may come up in either Configure or Run mode, depending on
    the programming of the EEPROM in the device.  This function does not address the
    possibility of coming up in Run mode.  It assumes the device will come up in Confugre
    mode.  If needed, qf4a512_Init() shows how to detect the mode after reset.

*//*********************************************************************************************/

inline
void qf4a512_ResetDevice(const Handle Device) {
    qf4a512_WriteConfigByte(Device, QF4A512_FULL_SRST_ADDRESS, 0x01);
}




#if  defined(NOT_IMPLEMENTED_YET)

/********************************************************************************************//*!

  @summary  NOT IMPLEMENTED YET - Configure the QF4A512 PLL-based clock.

  @param[in]   clockConfig  PLL configuration structure

  @return   'Success' if configuration successful, otherwise a negative value error code.

  - The master clock for the QF4A512 is produced by a crystal oscillator with a nominal frequency
    of 20MHz.  Alternatively the device can be fed with an external clock signal derived
    elsewhere.  The master clock is used as a reference for a phase-locked loop (PLL), from which
    clocks are derived to drive the FIR filters, the ADC and the analog front end.  The master
    clock is also divided down to provide a clock to be used for transfers to the on-chip EEPROM.

    @par
    @verbatim
                 . . . . . . . . . . . . . . . . . . . . .
                 .                          PLL          .
                 .               ____                    .
                 .  +------+    /    \     +-------+     .      +-------+
      20 MHz --+--->|  /a  |--->|diff|---->|  VCO  |---+----+-->|   /x  |---> SYS_CLK
               | .  +------+    \____/     +-------+   | .  |   +-------+     up to 200MHz
               | . PLL_CTRL_0      ^                   | .  |  SYS_CLK_CTRL
               | .  (a=1-64)       |                   | .  |    (x=1-64)
               | .                 |                   | .  |
               | .                 |       +-------+   | .  |   +-------+
               | .                 +-------|   /b  |<--+ .  +-->|   /y  |---> ADC_CLK
               | .                         +-------+     .      +-------+     up to 100MHz
               | .                         PLL_CTRL_1    .       ADC_CLK
               | .                         (b=1-64)      .       (y=2-16)
               | . . . . . . . . . . . . . . . . . . . . .
               |                                                +-------+
               +----------------------------------------------->|   /z  |---> EE_CLK
                                                                +-------+     up to 1.25MHz
                                                                 STARTUP
                                                                 (z=1-32)
    @endverbatim

  - The PLL clock frequency is determined by the input clock frequency


   the pre-divider value (M) and the divider value (N): PLL_CLK = f0 * N / M The default frequency
   for PLL_CLOCK is 200MHz. (f0 = 20MHz, M = 1, N= 10)  Operation of the PLL is possible in two
   frequency ranges: 20-100MHz and 100-300MHz.

*//*********************************************************************************************/

Result QfConfigureClock(
        const ClockConfig clockConfig) {
    //Assert(0);
}

#endif

/******************************************************************************************
 ******************************************************************************************
 ********                                                                          ********
 ********                  U t i l i t y   F u n c t i o n s                       ********
 ********                                                                          ********
 ******************************************************************************************
 ******************************************************************************************/

void QfPowerDown(void) {
    qf4a512_WriteConfigByte(SPI0_HANDLE, 0x09, _0000_0000);
    qf4a512_WriteConfigByte(SPI0_HANDLE, 0x0A, _0000_0000);
}

void QfSleep(void) {
    qf4a512_WriteConfigByte(SPI0_HANDLE, 0x09, _0000_0000);
    qf4a512_WriteConfigByte(SPI0_HANDLE, 0x0A, _0001_0000);
}

void QfStandBy(void) {
    qf4a512_WriteConfigByte(SPI0_HANDLE, 0x09, _0000_0000);
    qf4a512_WriteConfigByte(SPI0_HANDLE, 0x0A, _0010_0000);
}

void QfActivate(void) {
    qf4a512_WriteConfigByte(SPI0_HANDLE, 0x09, _1111_0011);
    qf4a512_WriteConfigByte(SPI0_HANDLE, 0x0A, _0011_1111);
}


/******************************************************************************************
 ******************************************************************************************
 ********                                                                          ********
 ********             L o c a l   ( S t a t i c )   F u n c t i o n s              ********
 ********                                                                          ********
 ******************************************************************************************
 ******************************************************************************************/
