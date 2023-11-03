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

   if((delay++ % 500) == 0)
   {
      CAPTURE_TOGGLE();   
   }
}

#define MIN_STOP 10
#define MAX_STOP 90
#define MIN_TARGET 20
#define MAX_TARGET 40
 

void getcapturedata ( void)
{
  unsigned int distance_cm;
  static int avg_distance_cm = 0;
  

  
  if(ringbuffer16b_isempty(&capture_data_rb) == FALSE)
  {
    distance_cm = ringbuffer16b_dequeue(&capture_data_rb);
    avg_distance_cm = ((avg_distance_cm * 5) + (distance_cm * 5)) / 10;
    
    if( avg_distance_cm > MAX_STOP || avg_distance_cm < MIN_STOP)
      ringbuffer8b_enqueue(&drive_cmd_data, DRIVE_COMMAND_STOP);
    else if(avg_distance_cm >= MIN_TARGET && avg_distance_cm <= MAX_TARGET)
      ringbuffer8b_enqueue(&drive_cmd_data, DRIVE_COMMAND_STOP);
    else if(avg_distance_cm > MAX_TARGET)
      ringbuffer8b_enqueue(&drive_cmd_data, DRIVE_COMMAND_FORWARD);
    else if(avg_distance_cm < MIN_TARGET)
      ringbuffer8b_enqueue(&drive_cmd_data, DRIVE_COMMAND_REVERSE);
  }
}