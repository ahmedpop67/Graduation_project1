
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "Timer_init.h"

#include "PWM_DCmotor_private.h"
#include "PWM_DCmotor_conf.h"
#include "PWM_DCmotor_init.h"
#include "GPIO_interface.h"


void MOTOR_init (u8 A_u8MotorNum)
{
	if (A_u8MotorNum>0)
	{
		switch(A_u8MotorNum)
		{
		case 1:
			MTimer_voidInit(MOTOR1_FirstTimerType);
			GPIO_voidSetPinMode(MOTOR1_PORT,MOTOR1_PINR,GPIO_OUTPUT_10M_PP);
		    GPIO_voidSetPinMode(MOTOR1_PORT,MOTOR1_PINL,GPIO_OUTPUT_10M_PP);
//			if (MOTOR1_FirstTimerType!=MOTOR1_SecondTimerType)
//			MTimer_voidInit(MOTOR1_SecondTimerType);
			break;
		case 2:
			MTimer_voidInit(MOTOR2_FirstTimerType);
			GPIO_voidSetPinMode(MOTOR2_PORT,MOTOR2_PINR,GPIO_OUTPUT_10M_PP);
			GPIO_voidSetPinMode(MOTOR2_PORT,MOTOR2_PINL,GPIO_OUTPUT_10M_PP);
//			MTimer_voidInit(MOTOR2_SecondTimerType);
			break;
		}
	}
}

void MOTOR_CounterClockWise  (u8 A_u8MotorNum , u16 A_u16CaptureValue )
{
	if (A_u8MotorNum >0 &&A_u8MotorNum < 3)
	{
		switch(A_u8MotorNum)
		{
		case 1:
			MTimer_voidPWM(MOTOR1_FirstTimerType,MOTOR1_FirstChannelNumber,A_u16CaptureValue);
			GPIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PINR, GPIO_HIGH);
			GPIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PINL, GPIO_LOW);

			//			MTimer_voidPWM(MOTOR1_FirstTimerType,MOTOR1_SecondChannelNumber,0);
			break;
		case 2:
			MTimer_voidPWM(MOTOR2_FirstTimerType,MOTOR2_FirstChannelNumber,A_u16CaptureValue);
			GPIO_voidSetPinValue(MOTOR1_PORT, MOTOR2_PINR, GPIO_HIGH);
			GPIO_voidSetPinValue(MOTOR1_PORT, MOTOR2_PINL, GPIO_LOW);
//			MTimer_voidPWM(MOTOR2_FirstTimerType,MOTOR2_SecondChannelNumber,0);
			break;
		}
	}
}

void MOTOR_ClockWise  (u8 A_u8MotorNum , u16 A_u16CaptureValue)
{
	if (A_u8MotorNum >0 &&A_u8MotorNum < 3)
	{
		switch(A_u8MotorNum)
		{
		case 1:
			MTimer_voidPWM(MOTOR1_FirstTimerType,MOTOR1_FirstChannelNumber,A_u16CaptureValue);
			GPIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PINR, GPIO_LOW);
			GPIO_voidSetPinValue(MOTOR1_PORT, MOTOR1_PINL, GPIO_HIGH);
//			MTimer_voidPWM(MOTOR1_FirstTimerType,MOTOR1_SecondChannelNumber,A_u16CaptureValue);
			break;
		case 2:
			MTimer_voidPWM(MOTOR1_FirstTimerType,MOTOR2_FirstChannelNumber,A_u16CaptureValue);
			GPIO_voidSetPinValue(MOTOR1_PORT, MOTOR2_PINR, GPIO_LOW);
			GPIO_voidSetPinValue(MOTOR1_PORT, MOTOR2_PINL, GPIO_HIGH);
//			MTimer_voidPWM(MOTOR1_FirstTimerType,MOTOR2_SecondChannelNumber,A_u16CaptureValue);
			break;
		}
	}
}

void MOTOR_Stop  (u8 A_u8MotorNum)
{
	if (A_u8MotorNum >0 &&A_u8MotorNum < 3)
	{
		switch(A_u8MotorNum)
		{
		case 1:
			MTimer_voidPWM(MOTOR1_FirstTimerType,MOTOR1_FirstChannelNumber,0);
//			MTimer_voidPWM(MOTOR1_FirstTimerType,MOTOR1_SecondChannelNumber,0);
			break;
		case 2:
			MTimer_voidPWM(MOTOR2_FirstTimerType,MOTOR2_FirstChannelNumber,0);
//			MTimer_voidPWM(MOTOR2_FirstTimerType,MOTOR2_SecondChannelNumber,0);
			break;
		}
	}
}
