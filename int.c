#include <im2.h>
#include <intrinsic.h>
#include <stdlib.h>
#include <string.h>
#include <z80.h>
#include "int.h"

uint16_t ticker;

uint8_t interrupt_1s_counter = 0;
uint16_t ticker_1s = 0;
uint8_t interrupt_1s;

uint8_t interrupt_500ms_counter = 0;
uint16_t ticker_500ms = 0;
uint8_t interrupt_500ms;

uint8_t interrupt_250ms_counter = 0;
uint16_t ticker_250ms = 0;
uint8_t interrupt_250ms;

uint8_t interrupt_100ms_counter = 0;
uint16_t ticker_100ms = 0;
uint8_t interrupt_100ms;

uint8_t interrupt_50ms_counter = 0;
uint16_t ticker_50ms = 0;
uint8_t interrupt_50ms;


IM2_DEFINE_ISR_8080(isr)
{
   ++ticker;

   if(++interrupt_1s_counter == 50) { // 1 second
      interrupt_1s_counter = 0;
      ++ticker_1s;
      interrupt_1s = 1;
   }
   if(++interrupt_500ms_counter == 25) { // .5 second
      interrupt_500ms_counter = 0;
      ++ticker_500ms;
      interrupt_500ms = 1;
   }
   if(++interrupt_250ms_counter == 13) { 
      interrupt_250ms_counter = 0;
      ++ticker_250ms;
      interrupt_250ms = 1;
   }
   if(++interrupt_100ms_counter == 10) {
      interrupt_100ms_counter = 0;
      ++ticker_100ms;
      interrupt_100ms = 1;
   }
   if(++interrupt_50ms_counter == 2) {
      interrupt_50ms_counter = 0;
      ++ticker_50ms;
      interrupt_50ms = 1;
   }
}

void setup_int(void)
{
   im2_init((void *)0xd000);
   memset((void *)0xd000, 0xd1, 257);
   
   z80_bpoke(0xd1d1, 0xc3);
   z80_wpoke(0xd1d2, (unsigned int)isr);
   intrinsic_ei();
}
