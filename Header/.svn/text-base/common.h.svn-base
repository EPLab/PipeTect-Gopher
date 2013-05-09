/*****************************  (C) Quickfilter Technologies, Inc.  *************************//*!

  @file  Common.h

  Common defines and macros that are generally applicable to C/C++ files.

  $Id: Common.h 121 2006-07-24 20:17:09Z jhopson $

  *******************************************************************************************

  @formats
      - C preprocessor directives
      - Doxygen (comment markup to produce HTML docs)

  @dependencies
      - Operating System:  none
      - Toolset:           none
      - CPU byte order:    none

  @notes
    -# Do not put anything non-portable in this file.

*///*********************************************************************************************


#if !defined(COMMON_H_INCLUDED)
#define      COMMON_H_INCLUDED


///  Type for pointers to functions with no input parameters or return types.

typedef void(* FuncPtr)(void);



//////////////////////////////////////////////////////////////////////////////////////////
//
//  Header Dependencies
//


///  Standardized, extensible type representing the result of a function call.  Positive
///  numbers and zero represent success, negative numbers represent failure.

typedef enum {
    Success = 0, ///<  Zero and above is a success

    InternalError = -1, ///<  Internal software error in reporting module
    UnknownError = -2,
    UnrecoverableError = -3,
    Timeout = -4,

    DataOutOfRange = -10,
    SizeOutOfRange = -11,
    InvalidDataFormat = -12,
    InvalidSyntax = -13,
    InvalidParameter = -14,
    InvalidState = -15,

    BufferOverflow = -20,
    BufferUnderflow = -21,
    BufferEmpty = -22,

    InvalidAscii = -30,
    InvalidParity = -31,
    InvalidChecksum = -32,
    InvalidFraming = -33,
    InvalidProtocol = -34,

    MediaFull = -40,
    MediaEmpty = -41,
    MediaReadError = -42,
    MediaWriteError = -43,
    MediaFormatError = -44,
    InvalidMediaFormat = -45,

    ResourceBusy = -50,
    ResourceReset = -51,
    ResourceNotFound = -52,
    ResourceNotAvailable = -53,
    ResourceExhausted = -54,

    FeatureNotFound = -60,
    FeatureNotInstalled = -61,
    FeatureNotConfigured = -62,
    FeatureNotSupported = -63,
    FeatureNotImplemented = -64,

    InvalidInterrupt = -70,
    UnexpectedInterruptOccurred = -71,
    UndefinedInterruptOccurred = -72,

    InvalidUserAction = -80,
    InvalidKeySelection = -81

} Result;



//////////////////////////////////////////////////////////////////////////////////////////
//
//  Common values for BOOL type.
//
//  Notes
//    1. Technically BOOL is true if > 0 and false if =0.  Tests for 'true' should test
//       for non-zero, not 1.
//

#if  !defined(NO_COMMON_BOOL_MACROS)

#if !defined(false)
#define  false             0
#endif
#if !defined(true)
#define  true              1
#endif

#if !defined(False)
#define  False             0
#endif
#if !defined(True)
#define  True              1
#endif

#if !defined(No)
#define  No                0
#endif
#if !defined(Yes)
#define  Yes               1
#endif

#define  Off               0
#define  On                1

#define  Low               0
#define  High              1

#define  Clear             0
#define  Set               1

#define  Invalid           0
#define  Valid             1

#define  Inactive          0
#define  Active            1

#define  Disabled          0
#define  Enabled           1

#define  NotDone           0
#define  Done              1

#define  Short             0
#define  Long              1

#define  Input             0
#define  Output            1

#define  Inner             0
#define  Outer             1

#define  Minimize          0
#define  Maximize          1

#define  Unsuccessful      0
#define  Successful        1

#define  Incorrect         0
#define  Correct           1

#define  Bummer            0
#define  OkeeDokee         1

#endif



//////////////////////////////////////////////////////////////////////////////////////////
//
//  Non-printable ASCII codes.
//

#if  !defined(NO_NON_PRINTABLE_ASCII_MACROS)

#define  nul         0            ///<  ^@   null character
#define  soh      0x01            ///<  ^A   start of heading
#define  stx      0x02            ///<  ^B   start of text
#define  etx      0x03            ///<  ^C   end of text
#define  eot      0x04            ///<  ^D   end of transmission
#define  enq      0x05            ///<  ^E   enquire
#define  ack      0x06            ///<  ^F   acknowledge
#define  bel      0x07            ///<  ^G   ring bell
#define  bs       0x08            ///<  ^H   backspace
#define  ht       0x09            ///<  ^I   horizontal tab
#define  lf       0x0A            ///<  ^J   line feed
#define  vt       0x0B            ///<  ^K   vertical tab
#define  ff       0x0C            ///<  ^L   form feed
#define  cr       0x0D            ///<  ^M   carriage return
#define  so       0x0E            ///<  ^N   shift out
#define  si       0x0F            ///<  ^O   shift in
#define  dle      0x10            ///<  ^P   data link escape
#define  dc1      0x11            ///<  ^Q   device control 1/x-on
#define  dc2      0x12            ///<  ^R   device control 2
#define  dc3      0x13            ///<  ^S   device control 3/x-off
#define  dc4      0x14            ///<  ^T   device control 4
#define  nak      0x15            ///<  ^U   negative acknowledgement
#define  syn      0x16            ///<  ^V   synchronous idle
#define  etb      0x17            ///<  ^W   end of transmission block
#define  can      0x18            ///<  ^X   cancel
#define  em       0x19            ///<  ^Y   end of medium
#define  sub      0x1A            ///<  ^Z   substitute
#define  esc      0x1B            ///<  ^[   escape
#define  fs       0x1C            ///<  ^\   file separator
#define  gs       0x1D            ///<  ^]   group separator
#define  rs       0x1E            ///<  ^^   record separator
#define  us       0x1F            ///<  ^_   unit separator
#define  del      0x7f            ///<       delete character

#endif





//////////////////////////////////////////////////////////////////////////////////////////
//
//  Data extraction, combination and rotation macros.
//


///  Retun the lower 4 bits of a as a UInt8

#define  GetLoNibble(a)         (UInt8)((a)&0x0F)


///  Return second 4 bits a as a UInt8

#define  GetHiNibble(a)         (UInt8)((a)>>4)


///  Return lower byte of a as a UInt8

#define  GetLoByte(a)           (UInt8)((a)&0x00FF)


///  Return second byte of a as a UInt8

#define  GetHiByte(a)           (UInt8)((a)>>8)


///  Return lower word of a as a UInt16

#define  GetLoWord(a)           (UInt16)((a)&0xFFFF)


///  Return second word of a as a UInt16

#define  GetHiWord(a)           (UInt16)((a)>>16)


///  Set the lower byte of a UInt16, preserving the upper byte.
///  Existing contents in the lower word of a are lost.

#define  SetLoWord(a, b)        ((a)&0xff00)|(UInt16)(b))


///  Set the upper byte of a UInt16, preserving the lower byte
///  Existing contents in the upper word of a are lost.

#define  SetHiWord(a, b)        ((a)&0x00ff)|(UInt16)((b)<<8))


///  Rotate, not shift, a UInt8 to the left.  The MSB becomes the LSB.

#define  RotateByteLeft(a)      ((a)<<1)|(((a)&0x80)?1:0)


///  Rotate, not shift, a UInt8 to the right.  The LSB becomes the MSB.

#define  RotateByteRight(a)     ((a)>>1)|(((a)&0x01)?0x80:0)


///  Rotate, not shift, a UInt16 to the left.  The MSB becomes the LSB.

#define  RotateWordLeft(a)      ((a)<<1)|(((a)&0x8000)?1:0)


///  Rotate, not shift, a UInt16 to the right.  The LSB becomes the MSB.

#define  RotateWordRight(a)     ((a)>>1)|(((a)&1)?0x8000:0)


///  Create a UInt16 out of two UInt8 or INT8

#define  MakeUInt16(a,b)         (((UInt16)(a)<<8)|(UInt16)(b))


///  Create a UInt32 out of two UInt16 or INT16

#define  MakeUInt32(a,b)         (((UInt32)(a)<<16)|(UInt32)(b))


///  Add two pointers and create a void pointer

#define  AddPointers(a,b)        (void*)((Count)(a)+(Count)(b))


///  Subtract two pointers and create a void pointer

#define  SubtractPointers(a,b)   (void*)((Count)(a)-(Count)(b))


///  Swap upper and lower bytes (change endianness) in a 16-bit value

#define  SwapUInt16Bytes(a)     (((a)>>8) | ((a)<<8))


///  If the compiler doesn't define NULL, define it here

#if !defined(NULL)
#define  NULL  (void *)0
#endif




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Hardware register manipulation macros
//
//  Notes
//    1.  These macros treat registers as volatile.
//    2.  It is sometimes easier to view bit registers in binary form.  The binary
//        representation macros (below) can be used as follows.
//        8-bit registers -
//            //                     7654 3210
//            SetByte( UartCtrl1,  _0001_0100 );
//
//         Word-wide registers -
//            //                                1111 11
//            //                                5432 1098   7654 3210
//            SetWordFromBytes( UartCtrl1,  _0001_0111, _1111_1111 );
//            SetWordFromBytes( UartCtrl2,  _0001_0100, _0101_1010 );
//            SetWordFromBytes( UartCtrl3,  _0101_0011, _0111_1001 );
//


///  Returns a byte (UInt8) from a volatile hardware register given a pointer to that register.

#define  GetByte(ptr)          *((const volatile UInt8 *)(ptr))


///  Returns a word (UInt16) from a volatile hardware register given a pointer to that register.

#define  GetWord(ptr)          *((const volatile UInt16*)(ptr))


///  Returns a word (UInt32) from a volatile hardware register given a pointer to that register.

#define  GetLong(ptr)          *((const volatile UInt32*)(ptr))


///  Sets a byte (UInt8) volatile hardware register at the specified pointer location.

#define  SetByte(ptr,val)      *((volatile UInt8 *)(ptr))=(val)


///  Sets a byte (UInt16) volatile hardware register at the specified pointer location.

#define  SetWord(ptr,val)      *((volatile UInt16*)(ptr))=(val)


///  Sets a long (UInt32) volatile hardware register at the specified pointer location.

#define  SetLong(ptr,val)      *((volatile UInt32*)(ptr))=(val)


///  Sets a word (UInt16) volatile hardware register from two bytes (UInt8) at the specified pointer location.

#define  SetWordFromBytes(ptr,a,b)  *((volatile UInt16*)(ptr))=MakeUInt16(a,b)




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Bit manipulation macros
//
//  Notes
//    1.  These macros treat all memory locations as volatile.
//    2.  Use IS_BIT_SET() in conditionals.  For instance -
//
//            if( IS_BIT_SET( UartCtrl1, BIT5 ) ) ...
//
//    3.  SET_BIT_x() and CLEAR_BIT_x() perform a NON-ATOMIC read-modify-write.  If atomicity
//        is required, disable interrupts first.
//

#if  !defined(NO_COMMON_BIT_MACROS)

/*   Removed to eliminate conflict with same definitions in IAR header files -
#define  BIT0     0x01                ///< Specifies first bit in the bit macros
#define  BIT1     0x02                ///< Specifies second bit in the bit macros
#define  BIT2     0x04                ///< Specifies third bit in the bit macros
#define  BIT3     0x08                ///< Specifies fourth bit in the bit macros

#define  BIT4     0x10                ///< Specifies fifth bit in the bit macros
#define  BIT5     0x20                ///< Specifies sixth bit in the bit macros
#define  BIT6     0x40                ///< Specifies seventh bit in the bit macros
#define  BIT7     0x80                ///< Specifies eigth bit in the bit macros

#define  BIT8     0x0100              ///< Specifies ninth bit in the bit macros
#define  BIT9     0x0200              ///< Specifies tenth bit in the bit macros
 */
#define  BIT10    0x0400              ///< Specifies eleventh bit in the bit macros
#define  BIT11    0x0800              ///< Specifies twelth bit in the bit macros

#define  BIT12    0x1000              ///< Specifies thirteenth bit in the bit macros
#define  BIT13    0x2000              ///< Specifies fourteenth bit in the bit macros
#define  BIT14    0x4000              ///< Specifies fifteenth bit in the bit macros
#define  BIT15    0x8000              ///< Specifies sixteenth bit in the bit macros

#define  BIT16    0x00010000          ///< Specifies seventeenth bit in the bit macros
#define  BIT17    0x00020000          ///< Specifies eightteenth bit in the bit macros
#define  BIT18    0x00040000          ///< Specifies nineteenth bit in the bit macros
#define  BIT19    0x00080000          ///< Specifies twentieth bit in the bit macros

#define  BIT20    0x00100000          ///< Specifies twenty-first bit in the bit macros
#define  BIT21    0x00200000          ///< Specifies twenty-second bit in the bit macros
#define  BIT22    0x00400000          ///< Specifies twenty-third bit in the bit macros
#define  BIT23    0x00800000          ///< Specifies twenty-fourth bit in the bit macros

#define  BIT24    0x01000000          ///< Specifies twenty-fifth bit in the bit macros
#define  BIT25    0x02000000          ///< Specifies twenty-sixth bit in the bit macros
#define  BIT26    0x04000000          ///< Specifies twenty-seventh bit in the bit macros
#define  BIT27    0x08000000          ///< Specifies twenty-eighth bit in the bit macros

#define  BIT28    0x10000000          ///< Specifies twenty-ninth bit in the bit macros
#define  BIT29    0x20000000          ///< Specifies thirtieth bit in the bit macros
#define  BIT30    0x40000000          ///< Specifies thirty-first bit in the bit macros
#define  BIT31    0x80000000          ///< Specifies thirty-second bit in the bit macros


///  Returns true if bit is set, false otherwise.  Actually, true if any bits set in b are set in a.

#define  IsBitSet(a,b)    ((a)&(b) ? true : false)


///  Returns true if bit is clear, false otherwise.  Actually, true if any bits clear in b are set in a.

#define  IsBitClear(a,b)  ((a)&(b) ? false : true)


///  Sets the specified bit.  Actually, sets all the bits in a that are set in b .

#define  SetBit(a,b)      (a)|=(b)


///  Clears the specified bit.  Actually, clears all the bits in a that are set in b .

#define  ClearBit(a,b)    (a)&= ~(b)


///  Toggles the specified bit.  Actually, toggles all the bits in a that are set in b .

#define  ToggleBit(a,b)   (a)^=(b)



///  Applies the mask to value, then 'returns' true if any of those bits are set

#define  AreAnyMaskBitsSet(value, mask)    ((value)&(mask) ? true : false)


///  All bits that are set in mask are cleared in value

#define  ClearBitsUsingMask(value, mask)   (value)&= ~(mask)


///  All bits that are set in mask are set in value

#define  SetBitsUsingMask(value, mask)     (value)|=(mask)


///  All bits that are set in mask are toggled in value

#define  ToggleBitsUsingMask(value, mask)  (value)^=(mask)


#endif





//////////////////////////////////////////////////////////////////////////////////////////
//
//  Character and string macros.
//

#if  !defined(NO_COMMON_CHARACTER_MACROS)

#define  ASCII_MAX                 0x7F               ///<  Maximum ASCII VAlue
#define  WHITESPACE_CHARACTERS  " \t\r"               ///<  Define string containing the whitespace characters


///  Returns 0 if character is not ASCII, non-zero if ASCII

#define  IsAscii(chr)           ((chr)<= ASCII_MAX)


///  Returns 0 if character is not hexadecimal ASCII, otherwise non-zero

#define  IsHex(chr)             (((chr)>='0')&&((chr)<='9') ||\
                                 ((chr)>='a')&&((chr)<='f') ||\
                                 ((chr)>='A')&&((chr)<='F'))


///  Returns 0 if character is not ASCII whitespace, otherwise non-zero

#define  IsWhitespace(chr)      (((chr)==' ')||((chr)=='\t')||((chr)=='\n')) ? true:false



///  Converts a character to its uppercase value only if it is a lowercase value.

#define  ToLower(chr)           (chr)+(((chr)>=0x61)&&((chr)<=0x7A))?0x20:0


///  Converts a character to its lowercase value only if it is an uppercase value.

#define  ToUpper(chr)           (chr)-(((chr)>=0x61)&&((chr)<=0x7A))?0x20:0


#endif




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Array macros
//
//
//  Notes
//    1.  Note that 'array' must be an array name and not an expression.
//

#if  !defined(NO_COMMON_ARRAY_MACROS)


///  Get size, in bytes (INT8), of an array

#define  GetArraySize(array)           (sizeof(array))


///  Get the number of elements in an array

#define  GetArrayDimension(array)      (sizeof(array)/sizeof(array[0]))


///  Get a pointer to the end of an array

#define  GetEndOfArray(array)          ((void *)((Count)&array + sizeof(array)))


///  Get the index number of an element given a pointer to the array and a pointer to the item.

#define  GetIndexFromPtr(array,pitem)  (((pitem)-&array)/sizeof(array[0]))


#endif




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Structure macros.
//
//  Notes
//    1.  Note that 'str' and 'element' must be names and not expressions.
//

#if  !defined(NO_COMMON_STRUCTURE_MACROS)


///  Get the offset of a structure element, measured from the beginning of the structure

#define  GetElementOffset(str,element)   ((Count) (&((str *)0)->element))


///  Get the pointer to a structure element, given the beginning of the structure and the element name

#define  GetElementPtr(str,element)      AddPtr(&str, GetElementOffset(str,element))


#endif




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Assertion macros.
//

#if  !defined(NO_COMMON_ASSERTION_MACROS)

#if  !defined(DISABLE_COMMON_ASSERTION_MACROS)

///  Assert wrapper

#define  Assert(a)               assert(a)


///  Throw an assertion if a is non-NULL.

#define  AssertNull(a)           assert((a) == NULL)


///  Throw an assertion if a is NULL.

#define  AssertNonNull(a)        assert((a) != NULL)


///  Throw an assertion if a is below lo or abouve hi.

#define  AssertBounds(a,lo,hi)   assert(((a)<=hi) && ((a)>=lo))



///  'a' is a function call.  This asserts that the function returns a
///  non-negative value.  Note that this macro behaves differently from
///  other assertion macros because the function still exists, without
///  the return value check, in non-Debug builds.

#if  defined(Debug)
#define  Validate(a)    Assert( (a) >= 0 )
#else
#define  Validate(a)    a
#endif


#else

#define  Assert(a)               ((void) 0)
#define  AssertNull(a)           ((void) 0)
#define  AssertNonNull(a)        ((void) 0)
#define  AssertBounds(a,lo,hi)   ((void) 0)
#define  Validate(a)             a

#endif

#endif




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Miscellaneous macros.
//

#if  !defined(NO_COMMON_MISCELLANEOUS_MACROS)


///  Returns non-zero if val is even

#define  IsEven(val)               !((val)&0x01)


///  Returns non-zero if val is odd

#define  IsOdd(val)                ((val)&0x01)


///  Returns the higher of a and b

#define  GetHigherOf(a,b)          ((a)>(b))?(a):(b)


///  Returns the lower of a and b

#define  GetLowerOf(a,b)           ((a)<(b))?(a):(b)


///  Limits a's range to within lo and hi

#define  GetWithinRange(a,lo,hi) ((a)>(hi)?(hi):((a)<(lo)?(lo):(a)))


///  Wait for the expression to become true.  Warning - this does not block the task or
///  timeout.  Be sure expression will eventually become true.

#define  WaitFor(exp)              while(!(exp))


///  Create an infinite loop

#define  InfiniteLoop()            while(1)


///  Dummy value used to emphasize that the value doesn't matter

#define  DontCare      0x5a



#endif




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Time macros.
//

#define  MICROSECONDS_PER_MILLISECOND  1000
#define  MICROSECONDS_PER_SECOND       1000000
#define  MICROSECONDS_PER_MINUTE       60000000

#define  MILLISECONDS_PER_SECOND    1000
#define  MILLISECONDS_PER_MINUTE    60000
#define  MILLISECONDS_PER_HOUR      3600000

#define  SECONDS_PER_MINUTE         60
#define  SECONDS_PER_HOUR           3600
#define  SECONDS_PER_DAY            86400

#define  SECONDS_PER_NON_LEAP_YEAR  31536000
#define  SECONDS_PER_LEAP_YEAR      31622400


#define  HOURS_PER_DAY           24
#define  HOURS_PER_TWO_DAYS      48
#define  HOURS_PER_THREE_DAYS    72
#define  HOURS_PER_FOUR_DAYS     96
#define  HOURS_PER_FIVE_DAYS     120
#define  HOURS_PER_SIX_DAYS      144
#define  HOURS_PER_SEVEN_DAYS    168

#define  HOURS_PER_WEEK          168

#define  HOURS_PER_28_DAY_MONTH  672
#define  HOURS_PER_29_DAY_MONTH  696
#define  HOURS_PER_30_DAY_MONTH  720
#define  HOURS_PER_31_DAY_MONTH  744

#define  HOURS_PER_NON_LEAP_YEAR 8760
#define  HOURS_PER_LEAP_YEAR     8784


#define  DAYS_PER_WEEK             7

#define  DAY_OF_WEEK_MONDAY       0
#define  DAY_OF_WEEK_TUESDAY      1
#define  DAY_OF_WEEK_WEDNESDAY    2
#define  DAY_OF_WEEK_THURSDAY     3
#define  DAY_OF_WEEK_FRIDAY       4
#define  DAY_OF_WEEK_SATURDAY     5
#define  DAY_OF_WEEK_SUNDAY       6

#define  DAYS_IN_JANUARY           31
#define  DAYS_IN_NON_LEAP_FEBRUARY 28
#define  DAYS_IN_LEAP_FEBRUARY     29
#define  DAYS_IN_MARCH             31
#define  DAYS_IN_APRIL             30
#define  DAYS_IN_MAY               31
#define  DAYS_IN_JUNE              30
#define  DAYS_IN_JULY              31
#define  DAYS_IN_AUGUST            31
#define  DAYS_IN_SEPTEMBER         30
#define  DAYS_IN_OCTOBER           31
#define  DAYS_IN_NOVEMBER          30
#define  DAYS_IN_DECEMBER          31

#define  DAYS_PER_NON_LEAP_YEAR  365
#define  DAYS_PER_LEAP_YEAR      366


#define  MONTHS_PER_YEAR           12




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Spell out long numbers to clarify their meaning and avoid typos.

#if  !defined(NO_COMMON_LONG_NUMBER_DEFINES)


#define  TEN_THOUSAND               10000
#define  HUNDRED_THOUSAND          100000
#define  ONE_MILLION              1000000
#define  TEN_MILLION             10000000
#define  HUNDRED_MILLION        100000000


#define  _2TO_THE_4TH                  16
#define  _2TO_THE_5TH                  32
#define  _2TO_THE_6TH                  64
#define  _2TO_THE_7TH                 128
#define  _2TO_THE_8TH                 256
#define  _2TO_THE_9TH                 512
#define  _2TO_THE_10TH               1024
#define  _2TO_THE_11TH               2048
#define  _2TO_THE_12TH               4096
#define  _2TO_THE_13TH               8192
#define  _2TO_THE_14TH              16384
#define  _2TO_THE_15TH              32768
#define  _2TO_THE_16TH              65536
#define  _2TO_THE_17TH             131072
#define  _2TO_THE_18TH             262144
#define  _2TO_THE_19TH             524288
#define  _2TO_THE_20TH            1048576
#define  _2TO_THE_21ST            2097152
#define  _2TO_THE_22ND            4194304
#define  _2TO_THE_23RD            8388608
#define  _2TO_THE_24TH           16777216
#define  _2TO_THE_25TH           33554432
#define  _2TO_THE_26TH           67108864
#define  _2TO_THE_27TH          134217728
#define  _2TO_THE_28TH          268435456
#define  _2TO_THE_29TH          536870912
#define  _2TO_THE_30TH         1073741824
#define  _2TO_THE_31TH         2147483648
#define  _2TO_THE_32ND         4294967296


#define  ONE_K                            _2TO_THE_10TH
#define  TWO_K                            _2TO_THE_11TH
#define  FOUR_K                           _2TO_THE_12TH
#define  EIGHT_K                          _2TO_THE_13TH
#define  SIXTEEN_K                        _2TO_THE_14TH
#define  THIRTY_TWO_K                     _2TO_THE_15TH
#define  SIXTY_FOUR_K                     _2TO_THE_16TH
#define  HUNDRED_TWENTY_EIGHT_K           _2TO_THE_17TH
#define  TWO_HUNDRED_FIFTY_SIX_K          _2TO_THE_18TH
#define  FIVE_HUNDRED_TWELVE_K            _2TO_THE_19TH


#define  HALF_MEGABYTE                    _2TO_THE_19TH
#define  ONE_MEGABYTE                     _2TO_THE_20TH
#define  TWO_MEGABYTES                    _2TO_THE_21ST
#define  FOUR_MEGABYTES                   _2TO_THE_22ND
#define  EIGHT_MEGABYTES                  _2TO_THE_23RD
#define  SIXTEEN_MEGABYTES                _2TO_THE_24TH
#define  THIRTY_TWO_MEGABYTES             _2TO_THE_25TH
#define  SIXTY_FOUR_MEGABYTES             _2TO_THE_26TH
#define  HUNDRED_TWENTY_EIGHT_MEGABYTES   _2TO_THE_27TH
#define  TWO_HUNDRED_FIFTY_SIX_MEGABYTES  _2TO_THE_28TH

#define  HALF_GIGABYTE                    _2TO_THE_29TH
#define  ONE_GIGABYTES                    _2TO_THE_30TH
#define  FOUR_GIGABYTES                   _2TO_THE_32ND


#endif




//////////////////////////////////////////////////////////////////////////////////////////
//
//  Binary representations of byte-wide numbers.
//

#if  !defined(NO_COMMON_BINARY_NUMBER_VALUES)

#define  _0000_0000    0x00                      //  0x00 to 0x1F
#define  _0000_0001    0x01
#define  _0000_0010    0x02
#define  _0000_0011    0x03
#define  _0000_0100    0x04
#define  _0000_0101    0x05
#define  _0000_0110    0x06
#define  _0000_0111    0x07
#define  _0000_1000    0x08
#define  _0000_1001    0x09
#define  _0000_1010    0x0A
#define  _0000_1011    0x0B
#define  _0000_1100    0x0C
#define  _0000_1101    0x0D
#define  _0000_1110    0x0E
#define  _0000_1111    0x0F

#define  _0001_0000    0x10                      //  0x10 to 0x1F
#define  _0001_0001    0x11
#define  _0001_0010    0x12
#define  _0001_0011    0x13
#define  _0001_0100    0x14
#define  _0001_0101    0x15
#define  _0001_0110    0x16
#define  _0001_0111    0x17
#define  _0001_1000    0x18
#define  _0001_1001    0x19
#define  _0001_1010    0x1A
#define  _0001_1011    0x1B
#define  _0001_1100    0x1C
#define  _0001_1101    0x1D
#define  _0001_1110    0x1E
#define  _0001_1111    0x1F

#define  _0010_0000    0x20                      //  0x20 to 0x2F
#define  _0010_0001    0x21
#define  _0010_0010    0x22
#define  _0010_0011    0x23
#define  _0010_0100    0x24
#define  _0010_0101    0x25
#define  _0010_0110    0x26
#define  _0010_0111    0x27
#define  _0010_1000    0x28
#define  _0010_1001    0x29
#define  _0010_1010    0x2A
#define  _0010_1011    0x2B
#define  _0010_1100    0x2C
#define  _0010_1101    0x2D
#define  _0010_1110    0x2E
#define  _0010_1111    0x2F

#define  _0011_0000    0x30                      //  0x30 to 0x3F
#define  _0011_0001    0x31
#define  _0011_0010    0x32
#define  _0011_0011    0x33
#define  _0011_0100    0x34
#define  _0011_0101    0x35
#define  _0011_0110    0x36
#define  _0011_0111    0x37
#define  _0011_1000    0x38
#define  _0011_1001    0x39
#define  _0011_1010    0x3A
#define  _0011_1011    0x3B
#define  _0011_1100    0x3C
#define  _0011_1101    0x3D
#define  _0011_1110    0x3E
#define  _0011_1111    0x3F

#define  _0100_0000    0x40                      //  0x40 to 0x4F
#define  _0100_0001    0x41
#define  _0100_0010    0x42
#define  _0100_0011    0x43
#define  _0100_0100    0x44
#define  _0100_0101    0x45
#define  _0100_0110    0x46
#define  _0100_0111    0x47
#define  _0100_1000    0x48
#define  _0100_1001    0x49
#define  _0100_1010    0x4A
#define  _0100_1011    0x4B
#define  _0100_1100    0x4C
#define  _0100_1101    0x4D
#define  _0100_1110    0x4E
#define  _0100_1111    0x4F

#define  _0101_0000    0x50                      //  0x50 to 0x5F
#define  _0101_0001    0x51
#define  _0101_0010    0x52
#define  _0101_0011    0x53
#define  _0101_0100    0x54
#define  _0101_0101    0x55
#define  _0101_0110    0x56
#define  _0101_0111    0x57
#define  _0101_1000    0x58
#define  _0101_1001    0x59
#define  _0101_1010    0x5A
#define  _0101_1011    0x5B
#define  _0101_1100    0x5C
#define  _0101_1101    0x5D
#define  _0101_1110    0x5E
#define  _0101_1111    0x5F

#define  _0110_0000    0x60                      //  0x60 to 0x6F
#define  _0110_0001    0x61
#define  _0110_0010    0x62
#define  _0110_0011    0x63
#define  _0110_0100    0x64
#define  _0110_0101    0x65
#define  _0110_0110    0x66
#define  _0110_0111    0x67
#define  _0110_1000    0x68
#define  _0110_1001    0x69
#define  _0110_1010    0x6A
#define  _0110_1011    0x6B
#define  _0110_1100    0x6C
#define  _0110_1101    0x6D
#define  _0110_1110    0x6E
#define  _0110_1111    0x6F

#define  _0111_0000    0x70                      //  0x70 to 0x7F
#define  _0111_0001    0x71
#define  _0111_0010    0x72
#define  _0111_0011    0x73
#define  _0111_0100    0x74
#define  _0111_0101    0x75
#define  _0111_0110    0x76
#define  _0111_0111    0x77
#define  _0111_1000    0x78
#define  _0111_1001    0x79
#define  _0111_1010    0x7A
#define  _0111_1011    0x7B
#define  _0111_1100    0x7C
#define  _0111_1101    0x7D
#define  _0111_1110    0x7E
#define  _0111_1111    0x7F

#define  _1000_0000    0x80                      //  0x80 to 0x8F
#define  _1000_0001    0x81
#define  _1000_0010    0x82
#define  _1000_0011    0x83
#define  _1000_0100    0x84
#define  _1000_0101    0x85
#define  _1000_0110    0x86
#define  _1000_0111    0x87
#define  _1000_1000    0x88
#define  _1000_1001    0x89
#define  _1000_1010    0x8A
#define  _1000_1011    0x8B
#define  _1000_1100    0x8C
#define  _1000_1101    0x8D
#define  _1000_1110    0x8E
#define  _1000_1111    0x8F

#define  _1001_0000    0x90                      //  0x90 to 0x9F
#define  _1001_0001    0x91
#define  _1001_0010    0x92
#define  _1001_0011    0x93
#define  _1001_0100    0x94
#define  _1001_0101    0x95
#define  _1001_0110    0x96
#define  _1001_0111    0x97
#define  _1001_1000    0x98
#define  _1001_1001    0x99
#define  _1001_1010    0x9A
#define  _1001_1011    0x9B
#define  _1001_1100    0x9C
#define  _1001_1101    0x9D
#define  _1001_1110    0x9E
#define  _1001_1111    0x9F

#define  _1010_0000    0xA0                      //  0xA0 to 0xAF
#define  _1010_0001    0xA1
#define  _1010_0010    0xA2
#define  _1010_0011    0xA3
#define  _1010_0100    0xA4
#define  _1010_0101    0xA5
#define  _1010_0110    0xA6
#define  _1010_0111    0xA7
#define  _1010_1000    0xA8
#define  _1010_1001    0xA9
#define  _1010_1010    0xAA
#define  _1010_1011    0xAB
#define  _1010_1100    0xAC
#define  _1010_1101    0xAD
#define  _1010_1110    0xAE
#define  _1010_1111    0xAF

#define  _1011_0000    0xB0                      //  0xB0 to 0xBF
#define  _1011_0001    0xB1
#define  _1011_0010    0xB2
#define  _1011_0011    0xB3
#define  _1011_0100    0xB4
#define  _1011_0101    0xB5
#define  _1011_0110    0xB6
#define  _1011_0111    0xB7
#define  _1011_1000    0xB8
#define  _1011_1001    0xB9
#define  _1011_1010    0xBA
#define  _1011_1011    0xBB
#define  _1011_1100    0xBC
#define  _1011_1101    0xBD
#define  _1011_1110    0xBE
#define  _1011_1111    0xBF

#define  _1100_0000    0xC0                      //  0xC0 to 0xCF
#define  _1100_0001    0xC1
#define  _1100_0010    0xC2
#define  _1100_0011    0xC3
#define  _1100_0100    0xC4
#define  _1100_0101    0xC5
#define  _1100_0110    0xC6
#define  _1100_0111    0xC7
#define  _1100_1000    0xC8
#define  _1100_1001    0xC9
#define  _1100_1010    0xCA
#define  _1100_1011    0xCB
#define  _1100_1100    0xCC
#define  _1100_1101    0xCD
#define  _1100_1110    0xCE
#define  _1100_1111    0xCF

#define  _1101_0000    0xD0                      //  0xD0 to 0xDF
#define  _1101_0001    0xD1
#define  _1101_0010    0xD2
#define  _1101_0011    0xD3
#define  _1101_0100    0xD4
#define  _1101_0101    0xD5
#define  _1101_0110    0xD6
#define  _1101_0111    0xD7
#define  _1101_1000    0xD8
#define  _1101_1001    0xD9
#define  _1101_1010    0xDA
#define  _1101_1011    0xDB
#define  _1101_1100    0xDC
#define  _1101_1101    0xDD
#define  _1101_1110    0xDE
#define  _1101_1111    0xDF

#define  _1110_0000    0xE0                      //  0xE0 to 0xEF
#define  _1110_0001    0xE1
#define  _1110_0010    0xE2
#define  _1110_0011    0xE3
#define  _1110_0100    0xE4
#define  _1110_0101    0xE5
#define  _1110_0110    0xE6
#define  _1110_0111    0xE7
#define  _1110_1000    0xE8
#define  _1110_1001    0xE9
#define  _1110_1010    0xEA
#define  _1110_1011    0xEB
#define  _1110_1100    0xEC
#define  _1110_1101    0xED
#define  _1110_1110    0xEE
#define  _1110_1111    0xEF

#define  _1111_0000    0xF0                      //  0xF0 to 0xFF
#define  _1111_0001    0xF1
#define  _1111_0010    0xF2
#define  _1111_0011    0xF3
#define  _1111_0100    0xF4
#define  _1111_0101    0xF5
#define  _1111_0110    0xF6
#define  _1111_0111    0xF7
#define  _1111_1000    0xF8
#define  _1111_1001    0xF9
#define  _1111_1010    0xFA
#define  _1111_1011    0xFB
#define  _1111_1100    0xFC
#define  _1111_1101    0xFD
#define  _1111_1110    0xFE
#define  _1111_1111    0xFF

#endif


#endif   //  COMMON_DEFINES_INCLUDED
