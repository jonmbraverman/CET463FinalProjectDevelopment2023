#include <msp430g2553.h>
#include "..\..\MODULES\hal.h"
#include "communicator.h"
#include "drive.h"
#include "tests.h"

void main( void )
{
    // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  BCSCTL1 = CALBC1_8MHZ;                       // Set DCO to 8MHz
  DCOCTL =  CALDCO_8MHZ; 

  configGPIO_UI();
  configGPIO_CAPTURE_TESTER();
  configTIMERA0_10msTick();
  //configTIMERA1_PWM();
  configTIMERA1_CAPTURE();
  configUSCI_A0();
  _BIS_SR(GIE);                 // Enable interrupt
  
  
  while(1)
  {
   
    MessageReceiver();
    
    driveEventHandler(DRIVE_MODE_NORMAL);
   
    testeventdata();
    testserialdata();
    
  }
}





