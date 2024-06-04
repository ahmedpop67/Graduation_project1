 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "STK_interface.h"
#include "GPIO_interface.h"
#include "Ultrasonic_init.h"
#include "Ultrasonic_config.h"
#include "Ultrasonic_private.h"


u8 HUltrasonic_f32CalcDistance (u8 Ultra_Num)
{
	u32 L_u32TicksNumber = 0   ;
	u8 L_f32Distance    = 0.0 ;
	switch(Ultra_Num)
	{
	case 1:

		/*trig pulse to trigger pin
		 * 3us low
		 * 10us high
		 * then low
		 */
		GPIO_voidSetPinValue (Ultrasonic1_TrigPort,Ultrasonic1_TrigPin, GPIO_LOW ) ;
		MSTK_voidSetBusyWait(TIME_FOR_LOW_PULSE) ;
		GPIO_voidSetPinValue (Ultrasonic1_TrigPort,Ultrasonic1_TrigPin, GPIO_HIGH) ;
		MSTK_voidSetBusyWait(TIME_FOR_HIGH_PULSE) ;
		GPIO_voidSetPinValue (Ultrasonic1_TrigPort,Ultrasonic1_TrigPin, GPIO_LOW ) ;

		/*wait for generate 8 pulses (40KHZ)*/
		MSTK_voidSetBusyWait(TIME_FOR_EIGHT_PULSES) ;

		/*wait until generating rising edge for echo pin*/
      		while (GPIO_GetPinValue( Ultrasonic1_EchoPort, Ultrasonic1_EchoPin) == GPIO_LOW) ;

		while (GPIO_GetPinValue( Ultrasonic1_EchoPort, Ultrasonic1_EchoPin) == GPIO_HIGH)
		{
			/*each iteration take 4.9 us*/
			L_u32TicksNumber ++ ;
			MSTK_voidSetBusyWait(2) ;
		}
		L_f32Distance = (L_u32TicksNumber + 0.0f)*TIME_OF_EACH_ITERATION_IN_MICRO*SPEED_OF_SIGNAL_CM_PER_U ;
		L_f32Distance = L_f32Distance / 2 ;

		/*initialize L_u32TicksNumber for next read*/
		L_u32TicksNumber = 0 ;
		return L_f32Distance ;
		break;
	case 2:

		/*trig pulse to trigger pin
		 * 3us low
		 * 10us high
		 * then low
		 */
		GPIO_voidSetPinValue (Ultrasonic2_TrigPort,Ultrasonic2_TrigPin, GPIO_LOW ) ;
		MSTK_voidSetBusyWait(TIME_FOR_LOW_PULSE) ;
		GPIO_voidSetPinValue (Ultrasonic2_TrigPort,Ultrasonic2_TrigPin, GPIO_HIGH) ;
		MSTK_voidSetBusyWait(TIME_FOR_HIGH_PULSE) ;
		GPIO_voidSetPinValue (Ultrasonic2_TrigPort,Ultrasonic2_TrigPin, GPIO_LOW ) ;

		/*wait for generate 8 pulses (40KHZ)*/
		MSTK_voidSetBusyWait(TIME_FOR_EIGHT_PULSES) ;

		/*wait until generating rising edge for echo pin*/
		while (GPIO_GetPinValue( Ultrasonic2_EchoPort, Ultrasonic2_EchoPin) == GPIO_LOW) ;

		while (GPIO_GetPinValue( Ultrasonic2_EchoPort, Ultrasonic2_EchoPin) == GPIO_HIGH)
		{
			/*each iteration take 4.9 us*/
			L_u32TicksNumber ++ ;
			MSTK_voidSetBusyWait(2) ;
		}
		L_f32Distance = (L_u32TicksNumber + 0.0f)*TIME_OF_EACH_ITERATION_IN_MICRO*SPEED_OF_SIGNAL_CM_PER_U ;
		L_f32Distance = L_f32Distance / 2 ;

		/*initialize L_u32TicksNumber for next read*/
		L_u32TicksNumber = 0 ;
		return L_f32Distance ;
		break;
	case 3:
		/*trig pulse to trigger pin
		 * 3us low
		 * 10us high
		 * then low
		 */
		GPIO_voidSetPinValue (Ultrasonic3_TrigPort,Ultrasonic3_TrigPin, GPIO_LOW ) ;
		MSTK_voidSetBusyWait(TIME_FOR_LOW_PULSE) ;
		GPIO_voidSetPinValue (Ultrasonic3_TrigPort,Ultrasonic3_TrigPin, GPIO_HIGH) ;
		MSTK_voidSetBusyWait(TIME_FOR_HIGH_PULSE) ;
		GPIO_voidSetPinValue (Ultrasonic3_TrigPort,Ultrasonic3_TrigPin, GPIO_LOW ) ;

		/*wait for generate 8 pulses (40KHZ)*/
		MSTK_voidSetBusyWait(TIME_FOR_EIGHT_PULSES) ;

		/*wait until generating rising edge for echo pin*/
		while (GPIO_GetPinValue( Ultrasonic3_EchoPort, Ultrasonic3_EchoPin) == GPIO_LOW) ;

		while (GPIO_GetPinValue( Ultrasonic3_EchoPort, Ultrasonic3_EchoPin) == GPIO_HIGH)
		{
			/*each iteration take 4.9 us*/
			L_u32TicksNumber ++ ;
			MSTK_voidSetBusyWait(2) ;
		}
		L_f32Distance = (L_u32TicksNumber + 0.0f)*TIME_OF_EACH_ITERATION_IN_MICRO*SPEED_OF_SIGNAL_CM_PER_U ;
		L_f32Distance = L_f32Distance / 2 ;

		/*initialize L_u32TicksNumber for next read*/
		L_u32TicksNumber = 0 ;
		return L_f32Distance ;
		break;
	}
	return 0;
}


void HUltrasonic_voidInit (u8 Ultra_Num)
{
	switch(Ultra_Num)
	{
	case 1:
		/*initialize Trig pin from GPIO*/
		GPIO_voidSetPinMode(Ultrasonic1_TrigPort,Ultrasonic1_TrigPin,GPIO_OUTPUT_2M_PP);
		//MGPIO_voidSetPinOutputType(Ultrasonic1_TrigPort, Ultrasonic1_TrigPin, GPIO_OTYPE_PUSHPULL);
		/*initialize Echo pin from GPIO*/
		GPIO_voidSetPinMode(Ultrasonic1_EchoPort,Ultrasonic1_EchoPin,GPIO_INPUT_PU_PD);
		GPIO_voidSetPinValue(Ultrasonic1_EchoPort, Ultrasonic1_EchoPin, GPIO_INPUT_PD);
		break;
	case 2:
		/*initialize Trig pin from GPIO*/
		GPIO_voidSetPinMode(Ultrasonic2_TrigPort,Ultrasonic2_TrigPin,GPIO_OUTPUT_2M_PP);
		//MGPIO_voidSetPinOutputType(Ultrasonic2_TrigPort, Ultrasonic2_TrigPin, GPIO_OTYPE_PUSHPULL);
		/*initialize Echo pin from GPIO*/
		GPIO_voidSetPinMode(Ultrasonic2_EchoPort,Ultrasonic2_EchoPin,GPIO_INPUT_PU_PD);
		GPIO_voidSetPinValue(Ultrasonic2_EchoPort, Ultrasonic2_EchoPin, GPIO_INPUT_PD);
		break;
	case 3:
		/*initialize Trig pin from GPIO*/
		GPIO_voidSetPinMode(Ultrasonic3_TrigPort,Ultrasonic3_TrigPin,GPIO_OUTPUT_2M_PP);
		//MGPIO_voidSetPinOutputType(Ultrasonic3_TrigPort, Ultrasonic3_TrigPin, GPIO_OTYPE_PUSHPULL);
		/*initialize Echo pin from GPIO*/
		GPIO_voidSetPinMode(Ultrasonic3_EchoPort,Ultrasonic3_EchoPin,GPIO_INPUT_PU_PD);
		GPIO_voidSetPinValue(Ultrasonic3_EchoPort, Ultrasonic3_EchoPin, GPIO_INPUT_PD);
		break;
	case 4:
		/*initialize Trig pin from GPIO*/
		GPIO_voidSetPinMode(Ultrasonic4_TrigPort,Ultrasonic4_TrigPin,GPIO_OUTPUT_2M_PP);
		//MGPIO_voidSetPinOutputType(Ultrasonic3_TrigPort, Ultrasonic3_TrigPin, GPIO_OTYPE_PUSHPULL);
		/*initialize Echo pin from GPIO*/
		GPIO_voidSetPinMode(Ultrasonic4_EchoPort,Ultrasonic4_EchoPin,GPIO_INPUT_PU_PD);
		GPIO_voidSetPinValue(Ultrasonic4_EchoPort, Ultrasonic4_EchoPin, GPIO_INPUT_PD);
		break;
	}
	/*initialize systick timer*/
	MSTK_voidInit() ;
}
