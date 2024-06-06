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
	u8 sign_type    :4;
	u8 Sign_distance  ;
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

u8 APP_G_u8DataFromUART = 0;

u8 APP_G_u8V2VTxData = 0;
u8 APP_G_u8V2VRxData = 0;



My_Data G_u16DataAfterProccing = {0,0,0};




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
	MUART1_voidSetCallBack(&MUART_Buffer_Write);
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

		/*Encoding received data and take Direction (second 3bits)*/
		L_u8Direction = G_u16DataAfterProccing.Direction;
		/*Encoding received data and take Speed (first 4bits)*/
		L_u16Speed = G_u16DataAfterProccing.Speed;
		/*Encoding received data and take Flag (last bit)*/
		L_u8Flag = G_u16DataAfterProccing.Flag;

		if (L_u8Direction == Stop){
			MOTOR_Stop(MOTOR_1) ;
			MOTOR_Stop(MOTOR_2) ;
		}else
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


void APP_Update_Distance()
{
	G_xNear_Distance.Distance_Forword = HUltrasonic_f32CalcDistance(ULTR_1);
	G_xNear_Distance.Distance_Back    = HUltrasonic_f32CalcDistance(ULTR_1);
	G_xNear_Distance.Distance_Right   = HUltrasonic_f32CalcDistance(ULTR_1);
	G_xNear_Distance.Distance_Left    = HUltrasonic_f32CalcDistance(ULTR_1);
}



void APP_VoidStop()
{
	//direction = stop
	G_u16DataAfterProccing.Direction = Stop;
	/*flag = 3*/
	G_u16DataAfterProccing.Flag = 3;
	/*stop car + alarm*/
//	G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
}

void APP_voidGoTasks ()
{
	if(G_u16DataAfterProccing.Direction = Go)
	{
		if (G_xNear_Distance.Distance_Forword  <= SO_SHORT_DISTANCE) // stop car
			{
				//direction = stop
				G_u16DataAfterProccing.Direction = Stop;
				/*flag = 3*/
				G_u16DataAfterProccing.Flag = 3;
				/*stop car + alarm*/
	//			G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
			}
		else if (G_xNear_Distance.Distance_Forword <= UN_SAFE_DISTANCE) //Un Safed Distance
			{
				if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
				{
					/*flag = 1*/
					G_u16DataAfterProccing.Flag = 1;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing.Direction = G_xMy_Data.Direction;
					G_u16DataAfterProccing.Speed = G_xMy_Data.Speed;
				}
				else
				{
					/*flag = 2*/
					G_u16DataAfterProccing.Flag = 2;
					/*send direction and speed without any change*/
					G_u16DataAfterProccing.Direction = G_xMy_Data.Direction;
					G_u16DataAfterProccing.Speed = G_xMy_Data.Speed;
				}
			}
		else //safe case
			{
				/*flag = 0*/
				G_u16DataAfterProccing.Flag = 0;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction;
				if (speed_control_Automatic == Automatic_ON)
					G_u16DataAfterProccing.Speed = max_speed;
				else
					G_u16DataAfterProccing.Speed = G_xMy_Data.Speed;
			}
	}
}
void APP_voidBackTasks ()
{
	if(G_u16DataAfterProccing.Direction = Back)
	{
		if (G_xNear_Distance.Distance_Back  <= SO_SHORT_DISTANCE) // stop car
		{
			//direction = stop
			G_u16DataAfterProccing.Direction = Stop;
			/*flag = 3*/
			G_u16DataAfterProccing.Flag = 3;
			/*stop car + alarm*/
	//		G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
		else if (G_xNear_Distance.Distance_Back <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
			if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
			{
				/*flag = 1*/
				G_u16DataAfterProccing.Flag = 1; ;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
				G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
			}
			else
			{
				/*flag = 2*/
				G_u16DataAfterProccing.Flag = 2;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
				G_u16DataAfterProccing.Speed = G_u8_LimetedSpeed ;
			}
		}
		else //sefed case
		{
			/*flag = 0*/
			G_u16DataAfterProccing.Flag = 0;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
			if (speed_control_Automatic == Automatic_ON)
				G_u16DataAfterProccing.Speed = max_speed;
			else
				G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
		}
	}
}
void APP_voidBackward_RightTasks ()
{
	if(G_u16DataAfterProccing.Direction = Backward_Right)
	{
		if (G_xNear_Distance.Distance_Left  <= SO_SHORT_DISTANCE) // stop car
		{
			//direction = stop
			G_u16DataAfterProccing.Direction = Stop;
			/*flag = 3*/
			G_u16DataAfterProccing.Flag = 3;
			/*stop car + alarm*/
	//		G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
		else if (G_xNear_Distance.Distance_Left <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
			if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
			{
				/*flag = 1*/
				G_u16DataAfterProccing.Flag = 1; ;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
				G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
			}
			else
			{
				/*flag = 2*/
				G_u16DataAfterProccing.Flag = 2;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
				G_u16DataAfterProccing.Speed = G_u8_LimetedSpeed ;
			}
		}
		else //sefed case
		{
			/*flag = 0*/
			G_u16DataAfterProccing.Flag = 0;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
			if (speed_control_Automatic == Automatic_ON)
				G_u16DataAfterProccing.Speed = max_speed;
			else
				G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
		}
	}
}
void APP_voidBackward_LEFTTasks ()
{
	if(G_u16DataAfterProccing.Direction = Backward_Left)
	{
		if (G_xNear_Distance.Distance_Right  <= SO_SHORT_DISTANCE) // stop car
		{
			//direction = stop
			G_u16DataAfterProccing.Direction = Stop;
			/*flag = 3*/
			G_u16DataAfterProccing.Flag = 3;
			/*stop car + alarm*/
	//		G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
		else if (G_xNear_Distance.Distance_Right <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
			if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
			{
				/*flag = 1*/
				G_u16DataAfterProccing.Flag = 1;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
				G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
			}
			else
			{
				/*flag = 2*/
				G_u16DataAfterProccing.Flag = 2;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
				G_u16DataAfterProccing.Speed = G_u8_LimetedSpeed ;
			}
		}
		else //sefed case
		{
			/*flag = 0*/
			G_u16DataAfterProccing.Flag = 0;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
			if (speed_control_Automatic == Automatic_ON)
				G_u16DataAfterProccing.Speed = max_speed;
			else
				G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
		}
	}
}
void APP_voidRight_LeftTasks ()
{

}
void APP_voidForward_RightTasks ()
{
	if(G_u16DataAfterProccing.Direction = Forward_Right)
	{
		if (G_xNear_Distance.Distance_Right  <= SO_SHORT_DISTANCE) // stop car
		{
			//direction = stop
			G_u16DataAfterProccing.Direction = Stop;
			/*flag = 3*/
			G_u16DataAfterProccing.Flag = 3;
			/*stop car + alarm*/
	//		G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
		else if (G_xNear_Distance.Distance_Right <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
			if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
			{
				/*flag = 1*/
				G_u16DataAfterProccing.Flag = 1;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
				G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
			}
			else
			{
				/*flag = 2*/
				G_u16DataAfterProccing.Flag = 2;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
				G_u16DataAfterProccing.Speed = G_u8_LimetedSpeed ;
			}
		}
		else //sefed case
		{
			/*flag = 0*/
			G_u16DataAfterProccing.Flag = 0;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
			if (speed_control_Automatic == Automatic_ON)
				G_u16DataAfterProccing.Speed = max_speed;
			else
				G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
		}
	}
}
void APP_voidForward_LeftTasks ()
{
	if(G_u16DataAfterProccing.Direction = Forward_Left)
	{
		if (G_xNear_Distance.Distance_Left  <= SO_SHORT_DISTANCE) // stop car
		{
			//direction = stop
			G_u16DataAfterProccing.Direction = Stop;
			/*flag = 3*/
			G_u16DataAfterProccing.Flag = 3;
			/*stop car + alarm*/
	//		G_u16DataAfterProccing = G_u16DataAfterProccing & 0xFF8F ;
		}
		else if (G_xNear_Distance.Distance_Left <= UN_SAFE_DISTANCE) //Un Safed Distance
		{
			if (G_xMy_Data.Speed <= G_u8_LimetedSpeed)
			{
				/*flag = 1*/
				G_u16DataAfterProccing.Flag = 1;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
				G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
			}
			else
			{
				/*flag = 2*/
				G_u16DataAfterProccing.Flag = 2;
				/*send direction and speed without any change*/
				G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
				G_u16DataAfterProccing.Speed = G_u8_LimetedSpeed;
			}
		}
		else //sefed case
		{
			/*flag = 0*/
			G_u16DataAfterProccing.Flag = 0;
			/*send direction and speed without any change*/
			G_u16DataAfterProccing.Direction = G_xMy_Data.Direction ;
			if (speed_control_Automatic == Automatic_ON)
				G_u16DataAfterProccing.Speed = max_speed;
			else
				G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
		}
	}
}

void APP_voidLane_Change()
{

}

void APP_V2V_Connection()
{
	// V2V connection is done using Bluetooth
	//This is a limitation that it has to be done with more flexible connection device
	// V2V connection has to be established at a certain trigger
	//the trigger of the V2V is mostly the raspberry pi massages
	//when V2V is triggered initiate blutooth connection
	if(!APP_G_u8V2VTxData){
		//TODO send UART massage to contact bluetooth device
		u8 L_u8Data = 0xC0;
		MUART_WriteData(&L_u8Data);
		//Send command that should be done with the connected device
		//TODO check massages between cars
		//note bluetooth massages are different from UART massages so there cane be duplicates.
		//massages need to include car ID
		//MSG 1 is ask front car to change Lane (used by emergency cars)
		//MSG 2 is probability of crash -> take measures
		//MSG 3 is parking
		//MSG 4 is changing to your lane
		//MSG 5 is overtake
		MUART_WriteData(&APP_G_u8V2VTxData);
	}

	if(!APP_G_u8V2VRxData){
		switch(APP_G_u8V2VRxData){
		case 1:
			//Try change lane
			break;
		case 2:
			//Check for dangers
			//take counter measures
			break;
		case 3:
			//ACK
			break;
		case 4:
			//See the car changing lane
			//take counter measures
			break;
		case 5:
			//see the care aver taking
			//get ack for successful lane change
			//decrease speed slightly for x seconds
			//send ACK for car to overtake
			//get ACK of successful overtaking
			break;
		default:
			//message not recognized
			break;
		}
	}

}

void UART_Task(){


	while(1){
		//process received massages
		//TODO send ACKs
		ProcessingFun();

		//send massages to Rasp
		MUART_ErrorStatusTransmitData(UART1);

		//delay_os
	}
}

void ProcessingFun (void)
{
	u8 L_u8Data = APP_G_u8DataFromUART>>4;
	/*Mapping data from UART*/
	//TODO Massage number for traking
	switch (APP_G_u8DataFromUART)
	{
	case 0x10: //forced stop
		G_xMy_Data.Direction = Stop ;
		//TODO make it forced
		break;
	case 0x20: //normal stop
		G_xMy_Data.Direction = Stop ;
		break;
	case 0x40: //turn left extremely
		G_xMy_Data.Direction = Left;
		break;
	case 0x48: //turn left normal (forward left)
		G_xMy_Data.Direction = Forward_Left;
		break;
	case 0x4c: //turn left slightly
		G_xMy_Data.Direction = Forward_Left;
		//TODO make it slight
		break;
	case 0x50: //turn Right extremely
		G_xMy_Data.Direction = Right;
		break;
	case 0x58: //turn Right normal (forward Right)
		G_xMy_Data.Direction = Forward_Right;
		break;
	case 0x5c: //turn Right slightly
		G_xMy_Data.Direction = Forward_Right;
		//TODO make it slight
		break;
	case 0x60: //Decrease speed greatly
		//TODO
		if(G_xMy_Data.Speed > 4){
			G_xMy_Data.Speed -= 4;
		}else{
			G_xMy_Data.Speed = Speed1;
		}
		break;
	case 0x68: //Decrease speed
		//TODO
		if(G_xMy_Data.Speed > 2){
			G_xMy_Data.Speed -= 2;
		}else{
			G_xMy_Data.Speed = Speed1;
		}
		break;
	case 0x6c: //Decrease speed lightly
		//TODO
		if(G_xMy_Data.Speed > 1){
			G_xMy_Data.Speed -= 1;
		}else{
			G_xMy_Data.Direction = Stop;
		}
		break;
	case 0x70: //Increase speed greatly
		//TODO
		if(G_xMy_Data.Speed+4 < 8){
			G_xMy_Data.Speed += 4;
		}else{
			G_xMy_Data.Speed = Speed7;
		}
		break;
	case 0x78: //Increase speed
		//TODO
		if(G_xMy_Data.Speed+2 < 8){
			G_xMy_Data.Speed += 2;
		}else{
			G_xMy_Data.Speed = Speed7;
		}
		break;
	case 0x7c: //Increase speed lightly
		//TODO
		if(G_xMy_Data.Speed != Speed7){
			G_xMy_Data.Speed += 1;
		}else{
			G_xMy_Data.Speed = Speed7;
		}
		break;
	case 0xe8:
		//TODO
		//sent Request by stm is invalid
		break;
	case 0xf0:
		//TODO
		//error in ACK(ACK sent is invalid)
		//retransmition (receive data)
		break;
	default:
		switch(L_u8Data){
		case 0x8:
			//TODO
			//There is a bump with distance
			//distance = APP_G_u8DataFromUART & 0xF

			break;
		case 0x9:
			//TODO
			//detected a sign
			//signCode = APP_G_u8DataFromUART & 0xF
			break;
		case 0xa:
			if(APP_G_u8DataFromUART &1){
				//Right lane
				//RL_distance = APP_G_u8DataFromUART&0xe
			}
			else{
				//left lane
				//LL_distance = APP_G_u8DataFromUART&0xe
			}
			break;
		case 0xb:
			if(APP_G_u8DataFromUART & 0x8){
				//extended distance
				//receive data as extended distance
			}
			else{
				//normal distance
				//distance = APP_G_u8DataFromUART &0x7
			}
			break;
		case 0xe:
			//request code x is valid
			//x = APP_G_u8DataFromUART & 0x7
			break;
		}

		break;
	}

	G_u16DataAfterProccing.Direction = G_xMy_Data.Direction;
	G_u16DataAfterProccing.Speed = G_xMy_Data.Speed ;
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
