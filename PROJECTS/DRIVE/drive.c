// // drive.c 
#include "msp430.h"
#include "..\..\MODULES\ring_buffer8.h"
#include "drive.h"

RingBuffer8b_TypeDef drive_event_data;


unsigned int driveSupportFunction(unsigned int);

void driveEventHandler( unsigned char module1param )
{ 
  static unsigned int data1;
  unsigned int inputdata = 0;  // Assume this data actually comes from a ring buffer
  unsigned char inputevent;
  bool new_event = FALSE;
  
  
  if(ringbuffer8b_isempty(&drive_event_data) == FALSE)
  {
    inputevent = ringbuffer8b_dequeue(&drive_event_data);
    new_event = TRUE;
  }

  if(new_event)
  {
    switch(inputevent)
    {
    case 0:            
      data1 = driveSupportFunction(inputdata);  //
      break;
      
    }
      
    
  }
  
  
  
}


unsigned int driveSupportFunction(unsigned int input)
{
  return input * 2;
}