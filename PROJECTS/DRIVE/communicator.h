#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "..\..\MODULES\ring_buffer8.h"

// PUBLIC FUNCTION PROTOTYPES
unsigned int module1SupportFunction(unsigned int);
void MessageReceiver( void );
void SendMessage(unsigned char* message, unsigned char numbytes);

// PUBLIC GLOBAL/STATIC DATA
extern RingBuffer8b_TypeDef payload_data;


// PUBLIC DEFINITIONS
















#endif