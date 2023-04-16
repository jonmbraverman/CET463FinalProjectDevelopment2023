// // drive.h
#ifndef DRIVE_H
#define DRIVE_H

#include "..\..\MODULES\ring_buffer8.h"

// PUBLIC FUNCTION PROTOTYPES
void driveStateMachine( unsigned char );
bool driveCommandValid(unsigned char input);

// PUBLIC GLOBAL/STATIC DATA
extern RingBuffer8b_TypeDef drive_cmd_data;


// PUBLIC DEFINITIONS
#define DRIVE_MODE_NORMAL 0
#define DRIVE_MODE_TEST_CYCLE   1
#define DRIVE_MODE_TEST_POSITION   2






#endif