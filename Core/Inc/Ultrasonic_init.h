 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#ifndef HAL_ULTRASONIC_ULTRASONIC_INIT_H_
#define HAL_ULTRASONIC_ULTRASONIC_INIT_H_


#define ULTR_1        1
#define ULTR_2        2
#define ULTR_3        3
#define ULTR_4        4

void HUltrasonic_voidInit (u8 Ultra_Num);

u8 HUltrasonic_f32CalcDistance (u8 Ultra_Num) ;

#endif /* HAL_ULTRASONIC_ULTRASONIC_INIT_H_ */
