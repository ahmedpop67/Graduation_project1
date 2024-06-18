 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#ifndef HAL_PWM_DCMOTOR_PWM_DCMOTOR_INIT_H_
#define HAL_PWM_DCMOTOR_PWM_DCMOTOR_INIT_H_

#include "PWM_DCmotor_private.h"
#include "PWM_DCmotor_conf.h"
#include "PWM_DCmotor_init.h"

#define MOTOR_1          1
#define MOTOR_2          2


void MOTOR_init (u8 A_u8MotorNum) ;
void MOTOR_CounterClockWise  (u8 A_u8MotorNum , u16 A_u8CaptureValue) ;
void MOTOR_ClockWise  (u8 A_u8MotorNum , u16 A_u8CaptureValue) ;
void MOTOR_Stop  (u8 A_u8MotorNum) ;
#endif /* HAL_PWM_DCMOTOR_PWM_DCMOTOR_INIT_H_ */
