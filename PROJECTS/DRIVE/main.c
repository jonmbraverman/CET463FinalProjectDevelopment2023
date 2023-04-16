#include <msp430g2553.h>
#include "..\..\MODULES\hal.h"
#include "communicator.h"
#include "drive.h"
#include "tests.h"

/*     MSP430G2553 FOR G2 LAUNCHPAD   ******************************************************************
;
;       P2      7 6 5 4 3 2 1 0
;               | | | | | | | | 
;               | | | | | | | 0-
;               | | | | | | 1---PWM (T1-OUT1)  MOTOR 1
;               | | | | | 2-----DIR            MOTOR 1       
;               | | | | 3-------DIR            MOTOR 2
;               | | | 4---------PWM (T1-OUT2)  MOTOR 2
;               | | 5-----------
;               | 6-------------
;               7---------------XTAL OUT
;
;
;      P1       7 6 5 4 3 2 1 0
;               | | | | | | | | 
;               | | | | | | | 0-LED
;               | | | | | | 1---UARTA0 (RX)
;               | | | | | 2-----UARTA0 (TX)
;               | | | | 3-------PB
;               | | | 4---------ENCODER         MOTOR 1 CHA
;               | | 5-----------ENCODER         MOTOR 1 CHB
;               | 6-------------ENCODER         MOTOR 2 CHA
;               7---------------ENCODER         MOTOR 2 CHB
****************************************************************************** */


void main( void )
{
    // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1 = CALBC1_8MHZ;                       // Set DCO to 8MHz
  DCOCTL =  CALDCO_8MHZ; 

  configGPIO_UI();
  configGPIO_MOTOR_CONTROL();
  confifGPIO_ENCODER();
  //configGPIO_CAPTURE_TESTER();
  configTIMERA0_10msTick();
  configTIMERA1_PWM();
  //configTIMERA1_CAPTURE();
  configUSCI_A0();
  _BIS_SR(GIE);                 // Enable interrupt
  
  
  while(1)
  {
   
    MessageReceiver();
    
    driveStateMachine(DRIVE_MODE_TEST_POSITION);
   
    testeventdata();
    testserialdata();
    
  }
}





