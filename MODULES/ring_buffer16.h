#ifndef RING_BUFFER16_H
#define RING_BUFFER16_H

#define RINGBUFFERSIZE 16
//
//
/* other */


typedef struct
{
  unsigned char head;
  unsigned char tail;
  unsigned int array[RINGBUFFERSIZE];

} RingBuffer16b_TypeDef;



#ifndef RING_BUFFER8_H
typedef enum {FALSE = 0, TRUE = 1} bool;
#endif

bool ringbuffer16b_isfull(RingBuffer16b_TypeDef *rb);
bool ringbuffer16b_isempty(RingBuffer16b_TypeDef *rb);
unsigned int ringbuffer16b_dequeue(RingBuffer16b_TypeDef *rb);
bool ringbuffer16b_enqueue(RingBuffer16b_TypeDef *rb, unsigned int bytedata);
void ringbuffer16b_flush(RingBuffer16b_TypeDef *rb);



#endif 