// encoder.c
#include "msp430G2553.h"
#include "hal.h"


unsigned int encoder_value[2] = {0xFFFF / 2, 0xFFFF / 2};


                                    // current state
                                   // 0  1  2  3
const signed int qei_value[4][4] = {{ 0,-1, 1, 0},
                                    { 1, 0, 0,-1},
                 /*laststate*/      {-1, 0, 0, 1}, 
                                    { 0, 1,-1, 0}};

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
  static unsigned char laststate[2] = {0,0};
  unsigned char state[2];


  if(P1IFG & (BIT4 | BIT5))
  {
    P1IFG &= ~(BIT4 | BIT5);                           // P1.4/P1.5 IFG cleared
    state[0] = P1IN >> 4;
    state[0] &= 0x03;
  
    setEdgesandClearFlags(0);
    encoder_value[0] += qei_value[laststate[0]][state[0]];
    laststate[0] = state[0];
  }
  
  
  if(P1IFG & (BIT6 | BIT7))
  {
    P1IFG &= ~(BIT6 | BIT7);                           // P1.4/P1.5 IFG cleared
    state[1] = P1IN >> 6;
    state[1] &= 0x03;
  
    setEdgesandClearFlags(1);
    encoder_value[1] += qei_value[laststate[1]][state[1]];
    laststate[1] = state[1];
  }
    
   
  
  
}
