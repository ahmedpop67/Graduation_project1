
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "EXTI_interface.h"
#include "SPI_interface.h"
#include "UART_interface.h"
#include "Ultrasonic_init.h"
#include "PWM_DCmotor_init.h"
#include "APP.h"
#include "APP_config.h"


u8 G_u8_LimetedSpeed = 4;

/*declaration 4motors*/
//extern DCmotor_Type MOTOR_1 ;
//extern DCmotor_Type MOTOR_2 ;


typedef struct
{
	u8 Direction:4 ;
	u8 Speed    :3 ;
	u8 Flag     :2 ;
}My_Data;

/*declaration distance between my car and nearing car */
typedef struct
{
	u8 Distance_Forword ;
	u8 Distance_Back    ;
	u8 Distance_Left    ;
	u8 Distance_Right   ;
}Near_Distance;

typedef struct
{
	u8 Bump_detected:1;
	u8 Bump_distance  ;
}BUMP;

typedef struct
{
	u8 Sign_detected:1;
	u8 Sign_distance  ;
	u8 sign_type    :4;
}SIGN;

typedef struct
{
	u8 Person_detected:1;
	u8 Perdon_distance  ;
}PERSON;

typedef struct
{
	u8 Vehical_detected:1;
	u8 Vehical_distance;
}VEHICLE;

My_Data       G_xMy_Data       = {0,0,0};
Near_Distance G_xNear_Distance = {0,0,0,0};

u8 APP_G_u8DataFromUART;

<<<<<<< HEAD
u16 G_u8DataAfterProccing = 0 ;
u8 ProcessingFun (void)
{
	/*Mapping data from UART*/
	switch (APP_G_u8DataFromUART)
	{
	case 'F':
	case 'f':
		G_xMy_Data.Direction = Go ;
		break;
	case 'S':
	case 's':
		G_xMy_Data.Direction = Stop ;
		break;
	case 'I':
	case 'i':
		G_xMy_Data.Direction = Forward_Right ;
		break;
	case 'R':
	case 'r':
		G_xMy_Data.Direction = Right ;
		break;
	case 'J':
	case 'j':
		G_xMy_Data.Direction = Backward_Right ;
		break;
	case 'B':
	case 'b':
		G_xMy_Data.Direction = Back ;
		break;
	case 'U':
	case 'u':
		G_xMy_Data.Direction = Backward_Left ;
		break;
	case 'L':
	case 'l':
		G_xMy_Data.Direction = Left ;
		break;
	case 'G':
	case 'g':
		G_xMy_Data.Direction = Forward_Left ;
		break;
	case '1':
		G_xMy_Data.Speed = Speed1 ;
		break;
	case '2':
		G_xMy_Data.Speed = Speed2 ;
		break;
	case '3':
		G_xMy_Data.Speed = Speed3 ;
		break;
	case '4':
		G_xMy_Data.Speed = Speed4 ;
		break;
	case '5':
		G_xMy_Data.Speed = Speed5 ;
		break;
	case '6':
		G_xMy_Data.Speed = Speed6 ;
		break;
	case '7':
		G_xMy_Data.Speed = Speed7 ;
		break;
	}
=======
u16 G_u16DataAfterProccing = 0 ;
>>>>>>> a3f83467b01eb27b85baadafb2473b7ffbc4c518



void init_conf()
{
	RCC_voidInitSysClock();
	RCC_voidEnablePeripheral(RCC_APB2,GPIOA);
	RCC_voidEnablePeripheral(RCC_APB2,GPIOB);
	RCC_voidEnablePeripheral(RCC_APB2,GPIOC);
	RCC_voidEnablePeripheral(RCC_APB2,TIM1);
	RCC_voidEnablePeripheral(RCC_APB2,USART1);
	MSTK_voidInit();
	MOTOR_init(MOTOR_1);
	MOTOR_init(MOTOR_2);
	HUltrasonic_voidInit(ULTR_1);
	HUltrasonic_voidInit(ULTR_2);
	HUltrasonic_voidInit(ULTR_3);
	HUltrasonic_voidInit(ULTR_4);
	MUART1_voidSetCallBack(&APP_GET_UART_Command);
	MUART_voidEnable(UART1);
	MUART_u8ReceiveByteASynch(UART1);
}


int main()
{
	u16  L_u16Speed = 0;
	u8  L_u8Direction = 0 ;
	u8  L_u8Flag = 0;

	init_conf();

	while(1)
	{
		ProcessingFun();

		/*Encoding recived data and take Direction (second 3bits)*/
		L_u8Direction = G_u16DataAfterProccing & 0x0f ;
		/*Encoding recived data and take Speed (first 4bits)*/
		L_u16Speed = (G_u16DataAfterProccing >> 4) & 0x07 ;
		/*Encoding recived data and take Flag (last bit)*/
		L_u8Flag = G_u16DataAfterProccing >> 7 ;

		if (L_u8Direction == Stop)

				{
					MOTOR_Stop(MOTOR_1) ;
					MOTOR_Stop(MOTOR_2) ;
				}
		else
				{
					/*
					 * first speed  = 1 +  =
					 * second speed = 2 +  =
					 * third speed  = 3 +  =
					 */
					L_u16Speed = (0Xff<<G_xMy_Data.Speed) + 0xf0;

					if (L_u8Direction == Go)  //Forward direction
					{
						MOTOR_ClockWise(MOTOR_1 , L_u16Speed) ;
						MOTOR_ClockWise(MOTOR_2 , L_u16Speed) ;
					}
					else if (L_u8Direction == Back)  //Backward direction
					{
						MOTOR_CounterClockWise(MOTOR_1 , L_u16Speed) ;
						MOTOR_CounterClockWise(MOTOR_2 , L_u16Speed) ;
					}
					else if (L_u8Direction == Right)  //Right direction
					{
						MOTOR_Stop(MOTOR_1) ;
						MOTOR_ClockWise(MOTOR_2 , L_u16Speed) ;
					}
					else if (L_u8Direction == Left)  //Left direction
					{
						MOTOR_ClockWise(MOTOR_1 , L_u16Speed) ;
						MOTOR_Stop(MOTOR_2) ;
					}
					else if (L_u8Direction == Forward_Right)  //forward right
					{
						MOTOR_ClockWise(MOTOR_1 , 0xa) ;
						MOTOR_ClockWise(MOTOR_2 , 0xc) ;
					}
					else if (L_u8Direction == Forward_Left)  //forward left
					{
						MOTOR_ClockWise(MOTOR_1 , 0xa) ;
						MOTOR_ClockWise(MOTOR_2 , 0xc) ;
					}
					else if (L_u8Direction == Backward_Right)  //backward right
					{
						MOTOR_CounterClockWise(MOTOR_1 , 0xa) ;
						MOTOR_CounterClockWise(MOTOR_2 , 0xc) ;
					}
					else if (L_u8Direction == Backward_Left)  //backward left
					{
						MOTOR_CounterClockWise(MOTOR_1 , 0xa) ;
						MOTOR_CounterClockWise(MOTOR_2 , 0xc) ;
					}
				}
	}
    return 0;
}


void APP_voidCalcForword_Distance()
{
	G_xNear_Distance.Distance_Forword = HUltrasonic_f32CalcDistance(ULTR_1);
}
void APP_voidCalcBackword_Distance()
{
	G_xNear_Distance.Distance_Back = HUltrasonic_f32CalcDistance(ULTR_2);
}
void APP_voidCalcRight_Distance()
{
	G_xNear_Distance.Distance_Right = HUltrasonic_f32CalcDistance(ULTR_3);
}
void APP_voidCalcLeft_Distance()
{
	G_xNear_Distance.Distance_Left = HUltrasonic_f32CalcDistance(ULTR_1);
}


void APP_VoidStop()
{
	//direction = stop
	SET_BIT(G_u16DataAfterProccing , 0) ;
	SET_BIT(G_u16DataAfterProccing , 1) ;
	SET_BIT(G_u16DataAfterProccing , 2) ;
	CLR_BIT(G_u16DataAfterProccing , 3) ;
	/*flag = 3*/
	SET_BIT(G_u16DataAfterProccing , 6) ;
	SET_BIT(G_u16DataAfterProccing , 7) ;
	/*stop car + alarm*/
	G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;


}

void APP_voidGoTasks ()
{
	if (G_xNear_Distance.Distance_Forword  <= SO_SHORT_DISTANCE) // stop car
		{
		   //direction = stop
		    SET_BIT(G_u16DataAfterProccing , 0) ;
		    SET_BIT(G_u16DataAfterProccing , 1) ;
		    SET_BIT(G_u16DataAfterProccing , 2) ;
		    CLR_BIT(G_u16DataAfterProccing , 3) ;
		   /*flag = 3*/
			SET_BIT(G_u16DataAfterProccing , 6) ;
			SET_BIT(G_u16DataAfterProccing , 7) ;
			/*stop car + alarm*/
			G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
	else if (G_xNear_Distance.Distance_Forword <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
				if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
				{
					/*flag = 1*/
					SET_BIT(G_u16DataAfterProccing , 6) ;
					CLR_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
				}
				else
				{
					/*flag = 2*/
					CLR_BIT(G_u16DataAfterProccing , 6) ;
					SET_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_u8_LimetedSpeed << 4)) ;
				}
		}
	else //sefed case
		{
			/*flag = 0*/
			CLR_BIT(G_u16DataAfterProccing , 6) ;
			CLR_BIT(G_u16DataAfterProccing , 7) ;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
			if (speed_control_outomatic == Automatic_ON)
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (max_speed << 4)) ;
			else
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
		}
}
void APP_voidBackTasks ()
{
	if (G_xNear_Distance.Distance_Back  <= SO_SHORT_DISTANCE) // stop car
		{
		   //direction = stop
		    SET_BIT(G_u16DataAfterProccing , 0) ;
		    SET_BIT(G_u16DataAfterProccing , 1) ;
		    SET_BIT(G_u16DataAfterProccing , 2) ;
		    CLR_BIT(G_u16DataAfterProccing , 3) ;
		   /*flag = 3*/
			SET_BIT(G_u16DataAfterProccing , 6) ;
			SET_BIT(G_u16DataAfterProccing , 7) ;
			/*stop car + alarm*/
			G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
	else if (G_xNear_Distance.Distance_Back <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
				if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
				{
					/*flag = 1*/
					SET_BIT(G_u16DataAfterProccing , 6) ;
					CLR_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
				}
				else
				{
					/*flag = 2*/
					CLR_BIT(G_u16DataAfterProccing , 6) ;
					SET_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_u8_LimetedSpeed << 4)) ;
				}
		}
	else //sefed case
		{
			/*flag = 0*/
			CLR_BIT(G_u16DataAfterProccing , 6) ;
			CLR_BIT(G_u16DataAfterProccing , 7) ;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
			if (speed_control_outomatic == Automatic_ON)
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (max_speed << 4)) ;
			else
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
		}
}
void APP_voidBackward_RightTasks ()
{
	if (G_xNear_Distance.Distance_Left  <= SO_SHORT_DISTANCE) // stop car
		{
		   //direction = stop
		    SET_BIT(G_u16DataAfterProccing , 0) ;
		    SET_BIT(G_u16DataAfterProccing , 1) ;
		    SET_BIT(G_u16DataAfterProccing , 2) ;
		    CLR_BIT(G_u16DataAfterProccing , 3) ;
		   /*flag = 3*/
			SET_BIT(G_u16DataAfterProccing , 6) ;
			SET_BIT(G_u16DataAfterProccing , 7) ;
			/*stop car + alarm*/
			G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
	else if (G_xNear_Distance.Distance_Left <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
				if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
				{
					/*flag = 1*/
					SET_BIT(G_u16DataAfterProccing , 6) ;
					CLR_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
				}
				else
				{
					/*flag = 2*/
					CLR_BIT(G_u16DataAfterProccing , 6) ;
					SET_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_u8_LimetedSpeed << 4)) ;
				}
		}
	else //sefed case
		{
			/*flag = 0*/
			CLR_BIT(G_u16DataAfterProccing , 6) ;
			CLR_BIT(G_u16DataAfterProccing , 7) ;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
			if (speed_control_outomatic == Automatic_ON)
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (max_speed << 4)) ;
			else
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
		}
}
void APP_voidBackward_LEFTTasks ()
{
	if (G_xNear_Distance.Distance_Right  <= SO_SHORT_DISTANCE) // stop car
		{
		   //direction = stop
		    SET_BIT(G_u16DataAfterProccing , 0) ;
		    SET_BIT(G_u16DataAfterProccing , 1) ;
		    SET_BIT(G_u16DataAfterProccing , 2) ;
		    CLR_BIT(G_u16DataAfterProccing , 3) ;
		   /*flag = 3*/
			SET_BIT(G_u16DataAfterProccing , 6) ;
			SET_BIT(G_u16DataAfterProccing , 7) ;
			/*stop car + alarm*/
			G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
	else if (G_xNear_Distance.Distance_Right <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
				if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
				{
					/*flag = 1*/
					SET_BIT(G_u16DataAfterProccing , 6) ;
					CLR_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
				}
				else
				{
					/*flag = 2*/
					CLR_BIT(G_u16DataAfterProccing , 6) ;
					SET_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_u8_LimetedSpeed << 4)) ;
				}
		}
	else //sefed case
		{
			/*flag = 0*/
			CLR_BIT(G_u16DataAfterProccing , 6) ;
			CLR_BIT(G_u16DataAfterProccing , 7) ;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
			if (speed_control_outomatic == Automatic_ON)
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (max_speed << 4)) ;
			else
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
		}
}
void APP_voidRight_LeftTasks ()
{

}
void APP_voidForward_RightTasks ()
{
	if (G_xNear_Distance.Distance_Right  <= SO_SHORT_DISTANCE) // stop car
		{
		   //direction = stop
		    SET_BIT(G_u16DataAfterProccing , 0) ;
		    SET_BIT(G_u16DataAfterProccing , 1) ;
		    SET_BIT(G_u16DataAfterProccing , 2) ;
		    CLR_BIT(G_u16DataAfterProccing , 3) ;
		   /*flag = 3*/
			SET_BIT(G_u16DataAfterProccing , 6) ;
			SET_BIT(G_u16DataAfterProccing , 7) ;
			/*stop car + alarm*/
			G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
	else if (G_xNear_Distance.Distance_Right <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
				if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
				{
					/*flag = 1*/
					SET_BIT(G_u16DataAfterProccing , 6) ;
					CLR_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
				}
				else
				{
					/*flag = 2*/
					CLR_BIT(G_u16DataAfterProccing , 6) ;
					SET_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_u8_LimetedSpeed << 4)) ;
				}
		}
	else //sefed case
		{
			/*flag = 0*/
			CLR_BIT(G_u16DataAfterProccing , 6) ;
			CLR_BIT(G_u16DataAfterProccing , 7) ;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
			if (speed_control_outomatic == Automatic_ON)
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (max_speed << 4)) ;
			else
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
		}
}
void APP_voidForward_LeftTasks ()
{
	if (G_xNear_Distance.Distance_Left  <= SO_SHORT_DISTANCE) // stop car
		{
		   //direction = stop
		    SET_BIT(G_u16DataAfterProccing , 0) ;
		    SET_BIT(G_u16DataAfterProccing , 1) ;
		    SET_BIT(G_u16DataAfterProccing , 2) ;
		    CLR_BIT(G_u16DataAfterProccing , 3) ;
		   /*flag = 3*/
			SET_BIT(G_u16DataAfterProccing , 6) ;
			SET_BIT(G_u16DataAfterProccing , 7) ;
			/*stop car + alarm*/
			G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
	else if (G_xNear_Distance.Distance_Left <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
				if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
				{
					/*flag = 1*/
					SET_BIT(G_u16DataAfterProccing , 6) ;
					CLR_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
				}
				else
				{
					/*flag = 2*/
					CLR_BIT(G_u16DataAfterProccing , 6) ;
					SET_BIT(G_u16DataAfterProccing , 7) ;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
					G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_u8_LimetedSpeed << 4)) ;
				}
		}
	else //sefed case
		{
			/*flag = 0*/
			CLR_BIT(G_u16DataAfterProccing , 6) ;
			CLR_BIT(G_u16DataAfterProccing , 7) ;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
			if (speed_control_outomatic == Automatic_ON)
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (max_speed << 4)) ;
			else
				G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
		}
}

void APP_voidLane_Change()
{


}

void APP_V2V_Connection()
{


}

void APP_GET_UART_Command()
{
	APP_G_u8DataFromUART = MUART_u8ReadDataRegister(UART1);
}

<<<<<<< HEAD

=======
////ahmed hassan and ayman saad

void ProcessingFun (void)
{
	/*Mapping data from UART*/
	switch (G_u8DataFromUART)
	{
	case 'F':
	case 'f':
		G_xMy_Data.Direction = Go ;
		break;
	case 'S':
	case 's':
		G_xMy_Data.Direction = Stop ;
		break;
	case 'I':
	case 'i':
		G_xMy_Data.Direction = Forward_Right ;
		break;
	case 'R':
	case 'r':
		G_xMy_Data.Direction = Right ;
		break;
	case 'J':
	case 'j':
		G_xMy_Data.Direction = Backward_Right ;
		break;
	case 'B':
	case 'b':
		G_xMy_Data.Direction = Back ;
		break;
	case 'U':
	case 'u':
		G_xMy_Data.Direction = Backward_Left ;
		break;
	case 'L':
	case 'l':
		G_xMy_Data.Direction = Left ;
		break;
	case 'G':
	case 'g':
		G_xMy_Data.Direction = Forward_Left ;
		break;
	case '1':
		G_xMy_Data.Speed = Speed1 ;
		break;
	case '2':
		G_xMy_Data.Speed = Speed2 ;
		break;
	case '3':
		G_xMy_Data.Speed = Speed3 ;
		break;
	case '4':
		G_xMy_Data.Speed = Speed4 ;
		break;
	case '5':
		G_xMy_Data.Speed = Speed5 ;
		break;
	case '6':
		G_xMy_Data.Speed = Speed6 ;
		break;
	case '7':
		G_xMy_Data.Speed = Speed7 ;
		break;
	}

	G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFFF0)) | G_xMy_Data.Direction) ;
	G_u16DataAfterProccing = ((G_u16DataAfterProccing & (0xFF8F)) | (G_xMy_Data.Speed << 4)) ;
	switch(G_xMy_Data.Direction){
	case Go:
		APP_voidGoTasks();
		break;
	case Stop:
		APP_VoidStop();
		break;
	case Back:
		APP_voidBackTasks();
		break;
	case Backward_Right:
		APP_voidBackward_RightTasks();
		break;
	case Backward_Left:
		APP_voidBackward_LEFTTasks();
		break;
	case Forward_Right:
		APP_voidForward_RightTasks();
		break;
	case Forward_Left:
		APP_voidForward_LeftTasks();
		break;
	case Right:
	case Left:
		APP_voidRight_LeftTasks();
		break;
	default:
		//do nothing
		break;
	}
	return;

}
>>>>>>> a3f83467b01eb27b85baadafb2473b7ffbc4c518


