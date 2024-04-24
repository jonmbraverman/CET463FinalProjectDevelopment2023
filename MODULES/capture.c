// capture.c 
#include "msp430.h"
#include "ring_buffer16.h"

RingBuffer16b_TypeDef capture_data_rb;   

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_CCR0_ISR(void)
{
static unsigned int lastTA1R = 0;
unsigned int duration;

  duration = TA1CCR0 - lastTA1R;
  lastTA1R = TA1CCR0;
  
  if((TA1CCTL0 & COV) == FALSE)
    ringbuffer16b_enqueue(&capture_data_rb, duration);
  else
    TA1CCTL0 &= ~COV;
}

#pragma vector=TIMER0_A1_VECTOR
__interrupt void TIMER0_A1_CCR1_ISR(void)
{
static unsigned int lastTA0R = 0;
unsigned int duration;
unsigned int distance;
static int ints = 0;

 
  if(TA0IV & 0x02)      // must read TA0IV to clear IFG.  This could also determine why we are here
    ints++;

  
  if(TA0CCTL1 & CCI)    // on the rising edge save the last time
  {
    lastTA0R = TA0CCR1;
  }
  else if((TA0CCTL1 & COV) == FALSE)    // on the falling edge and as long as we didn't miss get the duration
  {
    duration = TA0CCR1 - lastTA0R;
    distance = duration/58;  // convert to cm
    ringbuffer16b_enqueue(&capture_data_rb, distance);
  }
  else
    TA0CCTL1 &= ~COV;
}

void CAPTURE_TOGGLE(void)
{
  P2OUT ^= BIT6;
}






















