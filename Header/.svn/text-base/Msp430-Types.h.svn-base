/*****************************  (C) Quickfilter Technologies, Inc.  *************************//*!

  @file  Msp430-Types.h

  Portable integral types of specific logical size for the MSP-430 microcontroller.

  $Id: Msp430-Types.h 122 2006-07-24 20:25:01Z jhopson $

  *******************************************************************************************

  @notes
    -# This portable C file implements the QF4A512 Library layer in the figure below.

    -# This file defines logical size, not necessarily the physical size, which is CPU
       implementation dependent.  Although it's not an issue for the MSP-430, some devices
       have chars that consume 2 bytes of space, but are logically only one byte.  The
       sizeof() operator returns the memory storage, not logical, size.

    -# Floating-point types are included by default.  If the system doesn't use floating
       point, define DONT_USE_FLOATING_POINT.

    -# Since pointers are particulaly error prone, those types have a 'p' prepended to
       point out that fact.  However, Hungarian notation is not generally used.

*///*********************************************************************************************


#if !defined(SIZED_TYPES_INCLUDED)           //  Inclusion control
#define      SIZED_TYPES_INCLUDED



//  Definitions of the most common types

typedef  void                          *pVoid;         ///<  Pointer to unspecified type
typedef  unsigned char       Bool,     *pBool;         ///<  8-bit boolean type
typedef  char                Char,     *pChar;         ///<  8-bit signed value or pointer to string
typedef  char                Int8,     *pInt8;         ///<  8-bit  signed value
typedef  short               Int16,    *pInt16;        ///<  16-bit signed value
typedef  long                Int32,    *pInt32;        ///<  32-bit signed value

typedef  unsigned char       Byte,     *pByte;         ///<  8-bit  unsigned value
typedef  unsigned char       UInt8,    *pUInt8;        ///<  8-bit  unsigned value
typedef  unsigned short      UInt16,   *pUInt16;       ///<  16-bit unsigned value
typedef  unsigned long       UInt32,   *pUInt32;       ///<  32-bit unsigned value
typedef  UInt16              Count,    *pCount;        ///<  Holds the size of the largest pos-
                                                       ///<  sible collection of items (array,
                                                       ///<  linked list, etc) used in the system.
typedef  Byte  Handle;


#if !defined( DONT_USE_FLOATING_POINT )

typedef  float               Float32,  *pFloat32;      ///<  32-bit single precision IEEE-754 floating point

#endif


//  Logical size of types defined above, in bytes.

#define  CHAR_LOGICAL_SIZE_IN_BYTES        1           ///<  Byte width of an 8-bit signed character

#define  CHAR_LOGICAL_SIZE        1                    ///<  Byte width of an 8-bit signed character
#define  INT8_LOGICAL_SIZE        1                    ///<  Byte width of an 8-bit signed integer
#define  INT16_LOGICAL_SIZE       2                    ///<  Byte width of a 16-bit signed integer
#define  INT32_LOGICAL_SIZE       4                    ///<  Byte width of a 32-bit signed integer

#define  BYTE_LOGICAL_SIZE        1                    ///<  Byte width of an 8-bit unsigned integer
#define  UINT8_LOGICAL_SIZE       1                    ///<  Byte width of an 8-bit unsigned integer
#define  UINT16_LOGICAL_SIZE      2                    ///<  Byte width of a 16-bit unsigned integer
#define  UINT32_LOGICAL_SIZE      4                    ///<  Byte width of a 32-bit unsigned integer
#define  COUNT_LOGICAL_SIZE      UINT32_LOGICAL_SIZE   ///<  Byte width of a count of a count of items

#if !defined( DONT_USE_FLOATING_POINT )

#define  FLOAT32_LOGICAL_SIZE     4                    ///<  Byte width of a 32-bit floating point value

#endif


//  Logical size of types defined above, in bits

#define  BOOL_LOGICAL_SIZE_IN_BITS         1           ///<  Number of bits in a boolean type (consumes 8 bits)
#define  CHAR_LOGICAL_SIZE_IN_BITS         8           ///<  Number of bits in an 8-bit signed character
#define  INT8_LOGICAL_SIZE_IN_BITS         8           ///<  Number of bits in an 8-bit signed integer
#define  INT16_LOGICAL_SIZE_IN_BITS       16           ///<  Number of bits in a 16-bit signed integer
#define  INT32_LOGICAL_SIZE_IN_BITS       32           ///<  Number of bits in a 32-bit signed integer

#define  BYTE_LOGICAL_SIZE_IN_BITS         8           ///<  Number of bits in an 8-bit unsigned integer
#define  UINT8_LOGICAL_SIZE_IN_BITS        8           ///<  Number of bits in an 8-bit unsigned integer
#define  UINT16_LOGICAL_SIZE_IN_BITS      16           ///<  Number of bits in a 16-bit unsigned integer
#define  UINT32_LOGICAL_SIZE_IN_BITS      32           ///<  Number of bits in a 32-bit unsigned integer
#define  COUNT_LOGICAL_SIZE_IN_BITS      UINT32_LOGICAL_SIZE_IN_BITS    ///<  Number of bits in a count of a count of items

#if !defined( DONT_USE_FLOATING_POINT )

#define  FLOAT32_LOGICAL_SIZE_IN_BITS     32           ///<  Number of bits in a 32-bit floating point value

#endif



//  Limits of the integer types defined in this file


#define  BOOL_MIN       0                              ///<  Minimum value an Int8 can represent
#define  BOOL_MAX       1                              ///<  Maximum value an Int8 can represent


#include  <limits.h>                                   ///<  Size of integral types in compiler libarary

#define  INT8_MIN       CHAR_MIN                       ///<  Minimum value an Int8 can represent
#define  INT8_MAX       CHAR_MAX                       ///<  Maximum value an Int8 can represent

#define  INT16_MIN      SHRT_MIN                       ///<  Minimum value an Int16 can represent
#define  INT16_MAX      SHRT_MAX                       ///<  Maximum value an Int16 can represent

#define  INT32_MIN      LONG_MIN                       ///<  Minimum value an Int32 can represent
#define  INT32_MAX      LONG_MAX                       ///<  Maximum value an Int32 can represent


#define  BYTE_MIN       0                              ///<  Minimum value a Byte can represent
#define  BYTE_MAX       UCHAR_MAX                      ///<  Maximum value a Byte can represent

#define  UINT8_MIN      0                              ///<  Minimum value an Uint8 can represent
#define  UINT8_MAX      UCHAR_MAX                      ///<  Maximum value an Uint8 can represent

#define  UINT16_MIN     0                              ///<  Minimum value an Uint16 can represent
#define  UINT16_MAX     UINT_MAX                       ///<  Maximum value an Uint16 can represent

#define  UINT32_MIN     0                              ///<  Minimum value an Uint32 can represent
#define  UINT32_MAX     ULONG_MAX                      ///<  Maximum value an Uint32 can represent

#define  SIZE_MIN       UINT32_MIN                     ///<  Minimum value a Size can represent
#define  SIZE_MAX       UINT32_MAX                     ///<  Maximum value a Size can represent




//  Limits of the floating point types defined in this file

#if !defined( DONT_USE_FLOATING_POINT )

#include  <float.h>                                    ///<  Size of floating point types

#define  FLOAT32_MIN            FLT_MIN                ///<  Minimum positive value a 32-bit float can represent
#define  FLOAT32_MAX            FLT_MAX                ///<  Maximum positive value a 32-bit float can represent
#define  FLOAT32_MIN_EXP        FLT_MIN_EXP            ///<  The minimal exponent of a floating point value expressed in base FLT_RADIX; smaller exponents are principally possible (up to -16383), but not supported in all math functions.
#define  FLOAT32_MAX_EXP        FLT_MAX_EXP            ///<  The maximal exponent of a floating point value expressed in base FLT_RADIX; greater exponents are principally possible (up to 16383), but not supported in all math functions
#define  FLOAT32_MIN_10_EXP     FLT_MIN_10_EXP         ///<  The minimal exponent of a floating point value expressed in base 10
#define  FLOAT32_MAX_10_EXP     FLT_MAX_10_EXP         ///<  The maximal exponent of a floating point value expressed in base 10
#define  FLOAT32_DIGIT          FLT_DIG                ///<  Number of significant digits in a 32-bit floating point number
#define  FLOAT32_RADIX          FLT_RADIX              ///<  The base used for representing the exponent
#define  FLOAT32_MIN_FRACTION   FLT_EPSILON            ///<  The smallest x for which 1.0+x != 1.0

#endif


#endif
