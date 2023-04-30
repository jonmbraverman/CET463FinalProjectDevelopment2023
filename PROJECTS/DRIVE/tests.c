// TESTS.C
#include "..\..\MODULES\ring_buffer8.h"
#include "..\..\MODULES\ring_buffer16.h"
#include "..\..\MODULES\serial.h"
#include "..\..\MODULES\capture.h"
#include "drive.h"
#include "communicator.h"


void testeventdata(void)
{
 static unsigned char tedata = 0;
 
 ringbuffer8b_enqueue(&drive_cmd_data, tedata);
 tedata ^= 1;
 
}

void testserialdata(void)
{
   static unsigned char tsdata = 0;
   
   ringbuffer8b_enqueue(&rx_data_rb, tsdata++);
}

void testcapture(void)
{
   static unsigned int delay = 0;

   if((delay++ % 200) == 0)
   {
      CAPTURE_TOGGLE();   
   }
}

void getcapturedata ( void)
{
  unsigned int distance_cm;
  static int avg_distance_cm = 0;

  
  if(ringbuffer16b_isempty(&capture_data_rb) == FALSE)
  {
    distance_cm = ringbuffer16b_dequeue(&capture_data_rb);
    avg_distance_cm = ((avg_distance_cm * 5) + (distance_cm * 5)) / 10;
    
    if( avg_distance_cm > 90 || avg_distance_cm < 10)
      ringbuffer8b_enqueue(&drive_cmd_data, DRIVE_COMMAND_STOP);
    else if(avg_distance_cm >= 50 && avg_distance_cm <= 70)
      ringbuffer8b_enqueue(&drive_cmd_data, DRIVE_COMMAND_STOP);
    else if(avg_distance_cm > 70)
      ringbuffer8b_enqueue(&drive_cmd_data, DRIVE_COMMAND_FORWARD);
    else if(avg_distance_cm < 50)
      ringbuffer8b_enqueue(&drive_cmd_data, DRIVE_COMMAND_REVERSE);
  }
}