#ifndef HAL_H
#define HAL_H
/*******************************************************************************
****************************************************************************** */

//GPIO HARDWARE LOCATIONS

#define _M1PWM_BIT      0x02        //; BIT1
#define _M1DIR_BIT       0x04        //; BIT2
#define _M2DIR_BIT       0x08        //; BIT3
#define _M2PWM_BIT      0x10        //; BIT4
#define _STATUSLED_BIT  0x01
#define _PUSHBUTTON_BIT 0x08

// PWM VALUES
#define MTRDRIVE_PERIOD  511    // MOTOR DRIVE PERIOD - 1 
#define MTRDRIVE_OFF    ((0))

#define PB (_PUSHBUTTON_BIT & P1IN)
#define M1DIR_F (P2OUT |= _M1DIR_BIT)
#define M1DIR_R (P2OUT &= ~_M1DIR_BIT)
#define M2DIR_F (P2OUT |= _M2DIR_BIT)
#define M2DIR_R (P2OUT &= ~_M2DIR_BIT)


void configGPIO_UI( void );
void configGPIO_CAPTURE_TESTER( void );
void configGPIO_MOTOR_CONTROL( void );
void confifGPIO_ENCODER( void );
void setEdgesandClearFlags(unsigned char motor);
void configTIMERA0_10msTick( void );
void configTIMERA0_CAPTURE ( void );
void configTIMERA0CC1_CAPTURE (void);
void configTIMERA0_PWM( void );
void configTIMERA1_PWM( void );
void configTIMERA1_CAPTURE ( void );
void setP21DutyCycle ( unsigned int dutycycle );
void setP24DutyCycle ( unsigned int dutycycle );
void turnOnLED1 ( void );
void turnOffLED1 ( void );
void toggleLED1 ( void);
void configUSCI_A0 ( void );



#endif