 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#ifndef HAL_PWM_DCMOTOR_PWM_DCMOTOR_PRIVATE_H_
#define HAL_PWM_DCMOTOR_PWM_DCMOTOR_PRIVATE_H_

typedef struct
{
	u8 FirstTimerType ;
	u8 FirstChannelNumber ;
	u8 SecondTimerType ;
	u8 SecondChannelNumber ;

}DCmotor_Type ;

#define MOTOR1_TIMER1          1
#define MOTOR1_TIMER2          2
#define MOTOR1_TIMER3          3
#define MOTOR1_TIMER4          4


#define MOTOR2_TIMER1          1
#define MOTOR2_TIMER2          2
#define MOTOR2_TIMER3          3
#define MOTOR2_TIMER4          4


#define MOTOR1_CHANNAL1        1
#define MOTOR1_CHANNAL2        2
#define MOTOR1_CHANNAL3        3
#define MOTOR1_CHANNAL4        4



#define MOTOR2_CHANNAL1        1
#define MOTOR2_CHANNAL2        2
#define MOTOR2_CHANNAL3        3
#define MOTOR2_CHANNAL4        4


#endif /* HAL_PWM_DCMOTOR_PWM_DCMOTOR_PRIVATE_H_ */
