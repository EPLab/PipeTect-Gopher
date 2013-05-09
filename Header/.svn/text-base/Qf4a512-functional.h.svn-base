/*****************************  (C) Quickfilter Technologies, Inc.  *************************//*!

  @file  Qf4a512-functional.h

  Implementation of high-level Qf4a512 features (Small model).

  $Id: Qf4a512-functional.h 122 2006-07-24 20:25:01Z jhopson $

*///*********************************************************************************************


#if !defined(QF4A512_FUNCTIONAL_H_INCLUDED)           //   Inclusion control
#    define  QF4A512_FUNCTIONAL_H_INCLUDED



#include "Project.h"


///  Each entry in the configuration register table, produced by the PC software, contains
///  an address/value pair.

typedef struct
{
    UInt16   Address;
    Byte     Value;

} qf4a512_ConfigTableEntry;


#ifdef __cplusplus
   extern "C"
{                               //  C++ source requires this linkage specification
#endif


Result  qf4a512_LoadImageRegisterTable(void);

Result  qf4a512_WriteImageRegisterTableToEeprom(
    const Handle Device,
    const unsigned short SizeOfTable,
    const qf4a512_ConfigTableEntry * Table);

void  qf4a512_ResetDevice( const Byte Device );

extern void QfPowerDown(void);
extern void QfSleep(void);
extern void QfStandBy(void);
extern void QfActivate(void);

#ifdef __cplusplus
}                                       //  End of C++ linkage specification
#endif


#endif
