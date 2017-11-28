#include <16F887.h>
#device ICD=true
#device ADC=10
 
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
 
#use delay(internal=8000000,clock_out)
 
//#use rs232( baud=9600, parity=N, xmit=PIN_C6, rcv=PIN_C7, bits=8, ERRORS)
 
#use RS232 (DEBUGGER)
 
#use  I2C(master, sda=PIN_C4, scl= PIN_C3)

