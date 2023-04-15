// TESTS.C
#include "..\..\MODULES\ring_buffer8.h"
#include "..\..\MODULES\serial.h"
#include "drive.h"
#include "communicator.h"


void testeventdata(void)
{
 static unsigned char tedata = 0;
 
 ringbuffer8b_enqueue(&drive_event_data, tedata);
 tedata ^= 1;
 
}

void testserialdata(void)
{
   static unsigned char tsdata = 0;
   
   ringbuffer8b_enqueue(&rx_data_rb, tsdata++);
}
