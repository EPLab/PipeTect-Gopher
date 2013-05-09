/*****************************  (C) Quickfilter Technologies, Inc.  *************************//*!

  @file  Project.h

  Project-specific defines and types.

  $Id: Project.h 122 2006-07-24 20:25:01Z jhopson $

   *****************************************************************************************

  @formats
      - C declarations (header)
      - Doxygen (comment markup to produce HTML docs)

*///*********************************************************************************************


#if !defined(PROJECT_H_INCLUDED)                 //   Inclusion control
#    define  PROJECT_H_INCLUDED


//  Suppress  "Warning[Pa039]: use of address of unaligned structure member..." occurs
//  because the structures in Qf4a512-access.h are (by necessity) misaligned.

//#pragma  diag_suppress = Pa039


///  The inline keyword isn't supported in the IAR C compiler (it is in the C++ compiler)
#define  inline


#define  QF4A512_NUM_CHANNELS_ENABLED  4
#define QF4A512_NUM_SAMPLES (QF4A512_NUM_CHANNELS_ENABLED * 3)

#include  "common.h"
#include <p18cxxx.h>
#include  <stdlib.h>
#include  "Msp430-Types.h"
//#include  <assert.h>


#endif   //  PROJECT_H_INCLUDED

