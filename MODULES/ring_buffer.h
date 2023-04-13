#define RINGBUFFERSIZE 16
//
//
/* other */


typedef struct
{
  unsigned char head;
  unsigned char tail;
  unsigned int array[RINGBUFFERSIZE];

} RingBuffer_TypeDef;




typedef enum {FALSE = 0, TRUE = 1} bool;

bool ringbuffer_isfull(RingBuffer_TypeDef *rb);
bool ringbuffer_isempty(RingBuffer_TypeDef *rb);
unsigned int ringbuffer_dequeue(RingBuffer_TypeDef *rb);
bool ringbuffer_enqueue(RingBuffer_TypeDef *rb, unsigned int bytedata);
void ringbuffer_flush(RingBuffer_TypeDef *rb);



