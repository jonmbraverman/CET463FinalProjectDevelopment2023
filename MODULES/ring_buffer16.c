
#include <msp430.h>
#include "ring_buffer16.h"

RingBuffer16b_TypeDef my_rb16b;


//                 h   
//array [?, , , , , ,]
//       0 1 2 3 4 5 
//       t
//              h t  
//array [?, , , , , ,]
//       0 1 2 3 4 5 
//       

/**
 *  Checks to see if the ringbuffer is full by examining the "position" of the head in relation to the tail
**/
bool ringbuffer16b_isfull(RingBuffer16b_TypeDef *rb)
{
unsigned char rb_head, rb_tail;

    rb_head = rb -> head;    // grab a "snap shot" of values so that changes made by irq won't affect below calc or eval
    rb_tail = rb -> tail;    // the irq will only create more space, so using "old" data won't be a problem for reliabality, just performance.

    if(rb_head == (RINGBUFFERSIZE - 1))
    {
      if(rb_tail == 0)
        return(TRUE);      
    }
    else if((rb_head + 1) == rb_tail)
      return(TRUE);
      
    return(FALSE);
    
} 

/**
 *  Checks to see if the ringbuffer is empty or if it has some data by checking to see if the head and tail are in the same position
//       h   
//array [?, , , , , ,]
//       0 1 2 3 4 5 
//       t
**/
bool ringbuffer16b_isempty(RingBuffer16b_TypeDef *rb)
{
  if(rb->head == rb->tail)
    return(TRUE);
  
  return(FALSE);
}


//                 h   
//array [9, , , , , ,]
//       0 1 2 3 4 5 
//         t

/**
 *  "gets" data from the ring buffer and adjusts the tail
**/
unsigned int ringbuffer16b_dequeue(RingBuffer16b_TypeDef *rb)
{
unsigned int retval;
 

  retval = rb->array[rb->tail++];
  
  if(rb->tail >= RINGBUFFERSIZE)
    rb->tail = 0;
  
  return(retval);
} 

//         h   
//array [9, , , , , ,]
//       0 1 2 3 4 5 
//       t

/**
 *  "puts" data into the ring buffer and adjusts the head
**/
bool ringbuffer16b_enqueue(RingBuffer16b_TypeDef *rb, unsigned int bytedata)
{ 
    // if buffer is not full read the receive data register and increment head pointer.
    if( ringbuffer16b_isfull(rb) == FALSE )
      rb->array[rb->head++] = bytedata;
    else
      return(FALSE);
    
    // If new tail index is outside of ring buffer memory space, reset to beginning. (WRAP)
    if(rb->head >= RINGBUFFERSIZE)
      rb->head = 0;

    return(TRUE);
}

/**
 *  "zero's" the ring buffer by setting the head and tail to zero
**/
void ringbuffer16b_flush(RingBuffer16b_TypeDef *rb)
{
 rb->head = 0;
 rb->tail = 0; 
}




