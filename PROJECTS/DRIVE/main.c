#include <msp430g2553.h>
#include "..\..\MODULES\hal.h"
#include "communicator.h"
#include "drive.h"
#include "tests.h"

/*     MSP430G2553 FOR G2 LAUNCHPAD   ******************************************************************
;
;       P2      7 6 5 4 3 2 1 0
;               | | | | | | | | 
;               | | | | | | | *-
;               | | | | | | *---PWM (T1-OUT1) 
;               | | | | | *-----DIR
;               | | | | *-------DIR
;               | | | *---------PWM (T1-OUT2) 
;               | | *-----------
;               | *-------------
;               *---------------XTAL OUT
;
;
;      P1       7 6 5 4 3 2 1 0
;               | | | | | | | | 
;               | | | | | | | *-LED
;               | | | | | | *---UARTA0 (RX)
;               | | | | | *-----UARTA0 (TX)
;               | | | | *-------PB
;               | | | *---------
;               | | *-----------
;               | *-------------
;               *---------------
****************************************************************************** */


void main( void )
{
    // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1 = CALBC1_8MHZ;                       // Set DCO to 8MHz
  DCOCTL =  CALDCO_8MHZ; 

  configGPIO_UI();
  configGPIO_MOTOR_CONTROL();
  //configGPIO_CAPTURE_TESTER();
  configTIMERA0_10msTick();
  configTIMERA1_PWM();
  //configTIMERA1_CAPTURE();
  configUSCI_A0();
  _BIS_SR(GIE);                 // Enable interrupt
  
  
  while(1)
  {
   
    MessageReceiver();
    
    driveStateMachine(DRIVE_MODE_TEST);
   
    testeventdata();
    testserialdata();
    
  }
}





