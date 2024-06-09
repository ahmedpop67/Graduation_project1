 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#ifndef HAL_PWM_DCMOTOR_PWM_DCMOTOR_CONF_H_
#define HAL_PWM_DCMOTOR_PWM_DCMOTOR_CONF_H_


// first motor
/*option
 	 	 1-MOTOR1_TIMER1
 	 	 2-MOTOR1_TIMER2
 	 	 3-MOTOR1_TIMER3
 	 	 4-MOTOR1_TIMER4
 */
/*option
         1-MOTOR1_CHANNAL1
         1-MOTOR1_CHANNAL2
         1-MOTOR1_CHANNAL3
         1-MOTOR1_CHANNAL4
 */

#define MOTOR1_FirstTimerType                  MOTOR1_TIMER2
#define MOTOR1_FirstChannelNumber              MOTOR1_CHANNAL3
//#define MOTOR1_SecondTimerType               MOTOR1_TIMER1
//#define MOTOR1_SecondChannelNumber           MOTOR1_CHANNAL2


#define MOTOR1_PORT            GPIO_PORTA

#define MOTOR1_PINR            GPIO_PIN3
#define MOTOR1_PINL            GPIO_PIN4


//second motor
/*option
 	 	 1-MOTOR2_TIMER1
 	 	 2-MOTOR2_TIMER2
 	 	 3-MOTOR2_TIMER3
 	 	 4-MOTOR2_TIMER4
 */
/*option
         1-MOTOR2_CHANNAL1
         1-MOTOR2_CHANNAL2
         1-MOTOR2_CHANNAL3
         1-MOTOR2_CHANNAL4
 */

#define MOTOR2_FirstTimerType                  MOTOR2_TIMER3
#define MOTOR2_FirstChannelNumber              MOTOR2_CHANNAL2
//#define MOTOR2_SecondTimerType               MOTOR2_TIMER3
//#define MOTOR2_SecondChannelNumber           MOTOR2_CHANNAL2

#define MOTOR2_PORT            GPIO_PORTA

#define MOTOR2_PINR            GPIO_PIN5
#define MOTOR2_PINL            GPIO_PIN6

#endif /* HAL_PWM_DCMOTOR_PWM_DCMOTOR_CONF_H_ */
