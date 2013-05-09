//Vector mapper
#include "vector_mapper.h"

void HIV_isr(void);
void LIV_isr(void);

void (*HIV_function)(void) = 0;
void (*HIV_func2)(void) = 0;
void (*LIV_function)(void) = 0;
void (*LIV_func2)(void) = 0;


extern void _startup(void); // See c018i.c in your C18 compiler dir

//#pragma code _RESET_INTERRUPT_VECTOR = 0x0000
//void _reset (void)
//{
//    _asm goto _startup _endasm
//}
//#pragma code

#pragma code _HIGH_INTERRUPT_VECTOR = 0x0008

void _high_ISR(void) {
    _asm goto HIV_isr _endasm
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x0018

void _low_ISR(void) {
    _asm goto LIV_isr _endasm
}
#pragma code

#pragma interrupt HIV_isr //High priority interrupt service routine

void HIV_isr(void) {
    if (HIV_function) {
        HIV_function();
    }
    if (HIV_func2) {
        HIV_func2();
    }
}

#pragma interrupt LIV_isr //Low priority interrupt service routine

void LIV_isr(void) {
    if (LIV_function) {
        LIV_function();
    }
    if (LIV_func2) {
        LIV_func2();
    }
}
#pragma code

void set_HIV_function(void (*fp)(void)) {
    HIV_function = fp;
}

void set_LIV_function(void (*fp)(void)) {
    LIV_function = fp;
}

void set_HIV_func2(void (*fp)(void)) {
    HIV_func2 = fp;
}

void set_LIV_func2(void (*fp)(void)) {
    LIV_func2 = fp;
}
