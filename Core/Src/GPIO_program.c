 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  DATE  :  8/15/2023    **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/
 
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_private.h"
#include "GPIO_config.h"
#include "GPIO_interface.h"

void  GPIO_VoidInit()
{
	GPIOA->CRL=concX(GPIO_u8_PA7_INTIAL_MODE,GPIO_u8_PA6_INTIAL_MODE,GPIO_u8_PA5_INTIAL_MODE,GPIO_u8_PA4_INTIAL_MODE,
					 GPIO_u8_PA3_INTIAL_MODE,GPIO_u8_PA2_INTIAL_MODE,GPIO_u8_PA1_INTIAL_MODE,GPIO_u8_PA0_INTIAL_MODE);
					 
	GPIOA->CRH=concX(GPIO_u8_PA15_INTIAL_MODE,GPIO_u8_PA14_INTIAL_MODE,GPIO_u8_PA13_INTIAL_MODE,GPIO_u8_PA12_INTIAL_MODE,
					 GPIO_u8_PA11_INTIAL_MODE,GPIO_u8_PA10_INTIAL_MODE,GPIO_u8_PA9_INTIAL_MODE,GPIO_u8_PA8_INTIAL_MODE);
					 
	GPIOA->ODR=concB(GPIO_u8_PA15_INTIAL_VALUE,GPIO_u8_PA14_INTIAL_VALUE,GPIO_u8_PA13_INTIAL_VALUE,GPIO_u8_PA12_INTIAL_VALUE,
	                 GPIO_u8_PA11_INTIAL_VALUE,GPIO_u8_PA10_INTIAL_VALUE,GPIO_u8_PA9_INTIAL_VALUE,GPIO_u8_PA8_INTIAL_VALUE,
					 GPIO_u8_PA7_INTIAL_VALUE,GPIO_u8_PA6_INTIAL_VALUE,GPIO_u8_PA5_INTIAL_VALUE,GPIO_u8_PA4_INTIAL_VALUE,
					 GPIO_u8_PA3_INTIAL_VALUE,GPIO_u8_PA2_INTIAL_VALUE,GPIO_u8_PA1_INTIAL_VALUE,GPIO_u8_PA0_INTIAL_VALUE);
					
	GPIOB->CRL=concX(GPIO_u8_PB7_INTIAL_MODE,GPIO_u8_PB6_INTIAL_MODE,GPIO_u8_PB5_INTIAL_MODE,GPIO_u8_PB4_INTIAL_MODE,
					 GPIO_u8_PB3_INTIAL_MODE,GPIO_u8_PB2_INTIAL_MODE,GPIO_u8_PB1_INTIAL_MODE,GPIO_u8_PB0_INTIAL_MODE);
					 
	GPIOB->CRH=concX(GPIO_u8_PB15_INTIAL_MODE,GPIO_u8_PB14_INTIAL_MODE,GPIO_u8_PB13_INTIAL_MODE,GPIO_u8_PB12_INTIAL_MODE,
					 GPIO_u8_PB11_INTIAL_MODE,GPIO_u8_PB10_INTIAL_MODE,GPIO_u8_PB9_INTIAL_MODE,GPIO_u8_PB8_INTIAL_MODE);
					
	GPIOB->ODR=concB(GPIO_u8_PB15_INTIAL_VALUE,GPIO_u8_PB14_INTIAL_VALUE,GPIO_u8_PB13_INTIAL_VALUE,GPIO_u8_PB12_INTIAL_VALUE,
	                 GPIO_u8_PB11_INTIAL_VALUE,GPIO_u8_PB10_INTIAL_VALUE,GPIO_u8_PB9_INTIAL_VALUE,GPIO_u8_PB8_INTIAL_VALUE,
					 GPIO_u8_PB7_INTIAL_VALUE,GPIO_u8_PB6_INTIAL_VALUE,GPIO_u8_PB5_INTIAL_VALUE,GPIO_u8_PB4_INTIAL_VALUE,
					 GPIO_u8_PB3_INTIAL_VALUE,GPIO_u8_PB2_INTIAL_VALUE,GPIO_u8_PB1_INTIAL_VALUE,GPIO_u8_PB0_INTIAL_VALUE);

	GPIOC->CRL=concX(GPIO_u8_PC7_INTIAL_MODE,GPIO_u8_PC6_INTIAL_MODE,GPIO_u8_PC5_INTIAL_MODE,GPIO_u8_PC4_INTIAL_MODE,
					 GPIO_u8_PC3_INTIAL_MODE,GPIO_u8_PC2_INTIAL_MODE,GPIO_u8_PC1_INTIAL_MODE,GPIO_u8_PC0_INTIAL_MODE);
					 
	GPIOC->CRH=concX(GPIO_u8_PC15_INTIAL_MODE,GPIO_u8_PC14_INTIAL_MODE,GPIO_u8_PC13_INTIAL_MODE,GPIO_u8_PC12_INTIAL_MODE,
					 GPIO_u8_PC11_INTIAL_MODE,GPIO_u8_PC10_INTIAL_MODE,GPIO_u8_PC9_INTIAL_MODE,GPIO_u8_PC8_INTIAL_MODE);
						 
	GPIOC->ODR=concB(GPIO_u8_PC15_INTIAL_VALUE,GPIO_u8_PC14_INTIAL_VALUE,GPIO_u8_PC13_INTIAL_VALUE,GPIO_u8_PC12_INTIAL_VALUE,
	                GPIO_u8_PC11_INTIAL_VALUE,GPIO_u8_PC10_INTIAL_VALUE,GPIO_u8_PC9_INTIAL_VALUE,GPIO_u8_PC8_INTIAL_VALUE,
					GPIO_u8_PC7_INTIAL_VALUE,GPIO_u8_PC6_INTIAL_VALUE,GPIO_u8_PC5_INTIAL_VALUE,GPIO_u8_PC4_INTIAL_VALUE,
					GPIO_u8_PC3_INTIAL_VALUE,GPIO_u8_PC2_INTIAL_VALUE,GPIO_u8_PC1_INTIAL_VALUE,GPIO_u8_PC0_INTIAL_VALUE);
					
	GPIOD->CRL=concX(GPIO_u8_PD7_INTIAL_MODE,GPIO_u8_PD6_INTIAL_MODE,GPIO_u8_PD5_INTIAL_MODE,GPIO_u8_PD4_INTIAL_MODE,
					 GPIO_u8_PD3_INTIAL_MODE,GPIO_u8_PD2_INTIAL_MODE,GPIO_u8_PD1_INTIAL_MODE,GPIO_u8_PD0_INTIAL_MODE);
					 
	GPIOD->CRH=concX(GPIO_u8_PD15_INTIAL_MODE,GPIO_u8_PD14_INTIAL_MODE,GPIO_u8_PD13_INTIAL_MODE,GPIO_u8_PD12_INTIAL_MODE,
					 GPIO_u8_PD11_INTIAL_MODE,GPIO_u8_PD10_INTIAL_MODE,GPIO_u8_PD9_INTIAL_MODE,GPIO_u8_PD8_INTIAL_MODE);
	
					
	GPIOD->ODR=concB(GPIO_u8_PD15_INTIAL_VALUE,GPIO_u8_PD14_INTIAL_VALUE,GPIO_u8_PD13_INTIAL_VALUE,GPIO_u8_PD12_INTIAL_VALUE,
	                GPIO_u8_PD11_INTIAL_VALUE,GPIO_u8_PD10_INTIAL_VALUE,GPIO_u8_PD9_INTIAL_VALUE,GPIO_u8_PD8_INTIAL_VALUE,
					GPIO_u8_PD7_INTIAL_VALUE,GPIO_u8_PD6_INTIAL_VALUE,GPIO_u8_PD5_INTIAL_VALUE,GPIO_u8_PD4_INTIAL_VALUE,
					GPIO_u8_PD3_INTIAL_VALUE,GPIO_u8_PD2_INTIAL_VALUE,GPIO_u8_PD1_INTIAL_VALUE,GPIO_u8_PD0_INTIAL_VALUE);
					
	GPIOE->CRL=concX(GPIO_u8_PE7_INTIAL_MODE,GPIO_u8_PE6_INTIAL_MODE,GPIO_u8_PE5_INTIAL_MODE,GPIO_u8_PE4_INTIAL_MODE,
					 GPIO_u8_PE3_INTIAL_MODE,GPIO_u8_PE2_INTIAL_MODE,GPIO_u8_PE1_INTIAL_MODE,GPIO_u8_PE0_INTIAL_MODE);
					 
	GPIOE->CRH=concX(GPIO_u8_PE15_INTIAL_MODE,GPIO_u8_PE14_INTIAL_MODE,GPIO_u8_PE13_INTIAL_MODE,GPIO_u8_PE12_INTIAL_MODE,
					 GPIO_u8_PE11_INTIAL_MODE,GPIO_u8_PE10_INTIAL_MODE,GPIO_u8_PE9_INTIAL_MODE,GPIO_u8_PE8_INTIAL_MODE);
					
	GPIOE->ODR=concB(GPIO_u8_PE15_INTIAL_VALUE,GPIO_u8_PE14_INTIAL_VALUE,GPIO_u8_PE13_INTIAL_VALUE,GPIO_u8_PE12_INTIAL_VALUE,
	                GPIO_u8_PE11_INTIAL_VALUE,GPIO_u8_PE10_INTIAL_VALUE,GPIO_u8_PE9_INTIAL_VALUE,GPIO_u8_PE8_INTIAL_VALUE,
					GPIO_u8_PE7_INTIAL_VALUE,GPIO_u8_PE6_INTIAL_VALUE,GPIO_u8_PE5_INTIAL_VALUE,GPIO_u8_PE4_INTIAL_VALUE,
					GPIO_u8_PE3_INTIAL_VALUE,GPIO_u8_PE2_INTIAL_VALUE,GPIO_u8_PE1_INTIAL_VALUE,GPIO_u8_PE0_INTIAL_VALUE);
					
	GPIOF->CRL=concX(GPIO_u8_PF7_INTIAL_MODE,GPIO_u8_PF6_INTIAL_MODE,GPIO_u8_PF5_INTIAL_MODE,GPIO_u8_PF4_INTIAL_MODE,
					 GPIO_u8_PF3_INTIAL_MODE,GPIO_u8_PF2_INTIAL_MODE,GPIO_u8_PF1_INTIAL_MODE,GPIO_u8_PF0_INTIAL_MODE);
					 
	GPIOF->CRH=concX(GPIO_u8_PF15_INTIAL_MODE,GPIO_u8_PF14_INTIAL_MODE,GPIO_u8_PF13_INTIAL_MODE,GPIO_u8_PF12_INTIAL_MODE,
					 GPIO_u8_PF11_INTIAL_MODE,GPIO_u8_PF10_INTIAL_MODE,GPIO_u8_PF9_INTIAL_MODE,GPIO_u8_PF8_INTIAL_MODE);
	
					
	GPIOF->ODR=concB(GPIO_u8_PF15_INTIAL_VALUE,GPIO_u8_PF14_INTIAL_VALUE,GPIO_u8_PF13_INTIAL_VALUE,GPIO_u8_PF12_INTIAL_VALUE,
	                GPIO_u8_PF11_INTIAL_VALUE,GPIO_u8_PF10_INTIAL_VALUE,GPIO_u8_PF9_INTIAL_VALUE,GPIO_u8_PF8_INTIAL_VALUE,
					GPIO_u8_PF7_INTIAL_VALUE,GPIO_u8_PF6_INTIAL_VALUE,GPIO_u8_PF5_INTIAL_VALUE,GPIO_u8_PF4_INTIAL_VALUE,
					GPIO_u8_PF3_INTIAL_VALUE,GPIO_u8_PF2_INTIAL_VALUE,GPIO_u8_PF1_INTIAL_VALUE,GPIO_u8_PF0_INTIAL_VALUE);
				
	GPIOG->CRL=concX(GPIO_u8_PG7_INTIAL_MODE,GPIO_u8_PG6_INTIAL_MODE,GPIO_u8_PG5_INTIAL_MODE,GPIO_u8_PG4_INTIAL_MODE,
					 GPIO_u8_PG3_INTIAL_MODE,GPIO_u8_PG2_INTIAL_MODE,GPIO_u8_PG1_INTIAL_MODE,GPIO_u8_PG0_INTIAL_MODE);
					 
	GPIOG->CRH=concX(GPIO_u8_PG15_INTIAL_MODE,GPIO_u8_PG14_INTIAL_MODE,GPIO_u8_PG13_INTIAL_MODE,GPIO_u8_PG12_INTIAL_MODE,
					 GPIO_u8_PG11_INTIAL_MODE,GPIO_u8_PG10_INTIAL_MODE,GPIO_u8_PG9_INTIAL_MODE,GPIO_u8_PG8_INTIAL_MODE);
					
	GPIOG->ODR=concB(GPIO_u8_PG15_INTIAL_VALUE,GPIO_u8_PG14_INTIAL_VALUE,GPIO_u8_PG13_INTIAL_VALUE,GPIO_u8_PG12_INTIAL_VALUE,
	                GPIO_u8_PG11_INTIAL_VALUE,GPIO_u8_PG10_INTIAL_VALUE,GPIO_u8_PG9_INTIAL_VALUE,GPIO_u8_PG8_INTIAL_VALUE,
					GPIO_u8_PG7_INTIAL_VALUE,GPIO_u8_PG6_INTIAL_VALUE,GPIO_u8_PG5_INTIAL_VALUE,GPIO_u8_PG4_INTIAL_VALUE,
					GPIO_u8_PG3_INTIAL_VALUE,GPIO_u8_PG2_INTIAL_VALUE,GPIO_u8_PG1_INTIAL_VALUE,GPIO_u8_PG0_INTIAL_VALUE);
					
}
void  GPIO_VoidDeInit();

u8 GPIO_voidSetPinMode(u8 copy_u8portID,u8 copy_u8PinID,u8 copy_u8Mode)
{
	u8 lacal_u8ErrorState = STD_TYPE_OK;
	if(copy_u8portID <= GPIO_PORTG && copy_u8PinID <= GPIO_PIN15 && copy_u8Mode <= GPIO_OUTPUT_50M_AF_OD)
	{
		switch(copy_u8portID)
		{
			case GPIO_PORTA: 
				if(copy_u8PinID<=7)
				{
					SET_4BIT_Val(GPIOA->CRL,copy_u8PinID*4,copy_u8Mode);
				}
				else if(copy_u8PinID <=15)
				{
					copy_u8PinID-=8;
					SET_4BIT_Val(GPIOA->CRH,copy_u8PinID*4,copy_u8Mode);
				}
				break;
			case GPIO_PORTB: 
				if(copy_u8PinID<=7)
				{
					SET_4BIT_Val(GPIOB->CRL,copy_u8PinID*4,copy_u8Mode);
				}
				else if(copy_u8PinID <=15)
				{
					copy_u8PinID-=8;
					SET_4BIT_Val(GPIOB->CRH,copy_u8PinID*4,copy_u8Mode);
				}
				break;
			case GPIO_PORTC: 
				if(copy_u8PinID<=7)
				{
					SET_4BIT_Val(GPIOC->CRL,copy_u8PinID*4,copy_u8Mode);
				}
				else if(copy_u8PinID <=15)
				{
					copy_u8PinID-=8;
					SET_4BIT_Val(GPIOC->CRH,copy_u8PinID*4,copy_u8Mode);
				}
				break;
			case GPIO_PORTD: 
				if(copy_u8PinID<=7)
				{
					SET_4BIT_Val(GPIOD->CRL,copy_u8PinID*4,copy_u8Mode);
				}
				else if(copy_u8PinID <=15)
				{
					copy_u8PinID-=8;
					SET_4BIT_Val(GPIOD->CRH,copy_u8PinID*4,copy_u8Mode);
				}
				break;
			case GPIO_PORTE: 
				if(copy_u8PinID<=7)
				{
					SET_4BIT_Val(GPIOE->CRL,copy_u8PinID*4,copy_u8Mode);
				}
				else if(copy_u8PinID <=15)
				{
					copy_u8PinID-=8;
					SET_4BIT_Val(GPIOE->CRH,copy_u8PinID*4,copy_u8Mode);
				}
				break;
		    case GPIO_PORTF: 
				if(copy_u8PinID<=7)
				{
					SET_4BIT_Val(GPIOF->CRL,copy_u8PinID*4,copy_u8Mode);
				}
				else if(copy_u8PinID <=15)
				{
					copy_u8PinID-=8;
					SET_4BIT_Val(GPIOF->CRH,copy_u8PinID*4,copy_u8Mode);
				}
				break;
			case GPIO_PORTG: 
				if(copy_u8PinID<=7)
				{
					SET_4BIT_Val(GPIOG->CRL,copy_u8PinID*4,copy_u8Mode);
				}
				else if(copy_u8PinID <=15)
				{
					copy_u8PinID-=8;
					SET_4BIT_Val(GPIOG->CRH,copy_u8PinID*4,copy_u8Mode);
				}
				break;
		}
	}
	else 
		lacal_u8ErrorState = STD_TYPE_NOK;
	return lacal_u8ErrorState;
}


u8 GPIO_voidSetPinValue(u8 copy_u8portID,u8 copy_u8PinID,u8 copy_u8PinValue)
{
	u8 lacal_u8ErrorState = STD_TYPE_OK;
	if(copy_u8portID <= GPIO_PORTG && copy_u8PinID <= GPIO_PIN15 && (copy_u8PinValue == 1 || copy_u8PinValue ==0 ))
	{
		switch(copy_u8portID)
		{
			case GPIO_PORTA:
				switch(copy_u8PinValue){
				case 0:WRITE_BIT(GPIOA->BRR,copy_u8PinID);break;
				case 1:WRITE_BIT(GPIOA->BSRR,copy_u8PinID);break;}
				break;
			case GPIO_PORTB:
				switch(copy_u8PinValue){
				case 0:WRITE_BIT(GPIOB->BRR,copy_u8PinID);break;
				case 1:WRITE_BIT(GPIOB->BSRR,copy_u8PinID);break;}
				break;
			case GPIO_PORTC:
				switch(copy_u8PinValue){
				case 0:WRITE_BIT(GPIOC->BRR,copy_u8PinID);break;
				case 1:WRITE_BIT(GPIOC->BSRR,copy_u8PinID);break;}
				break;
			case GPIO_PORTD:
				switch(copy_u8PinValue){
				case 0:WRITE_BIT(GPIOD->BRR,copy_u8PinID);break;
				case 1:WRITE_BIT(GPIOD->BSRR,copy_u8PinID);break;}
				break;
			case GPIO_PORTE:
				switch(copy_u8PinValue){
				case 0:WRITE_BIT(GPIOE->BRR,copy_u8PinID);break;
				case 1:WRITE_BIT(GPIOE->BSRR,copy_u8PinID);break;}
				break;
			case GPIO_PORTF:
				switch(copy_u8PinValue){
				case 0:WRITE_BIT(GPIOF->BRR,copy_u8PinID);break;
				case 1:WRITE_BIT(GPIOF->BSRR,copy_u8PinID);break;}
				break;
			case GPIO_PORTG:
				switch(copy_u8PinValue){
				case 0:WRITE_BIT(GPIOG->BRR,copy_u8PinID);break;
				case 1:WRITE_BIT(GPIOG->BSRR,copy_u8PinID);break;}
				break;
		}
	}
    else 
		lacal_u8ErrorState = STD_TYPE_NOK;
	return lacal_u8ErrorState;
}

u8 GPIO_voidSetPortValue(u8 copy_u8portID,u16 copy_u16PortValue)
{
	u8 lacal_u8ErrorState = STD_TYPE_OK;
	if(copy_u8portID <= GPIO_PORTG)
	{
		switch(copy_u8portID)
		{
			case GPIO_PORTA:GPIOA->ODR=copy_u16PortValue;break;
			case GPIO_PORTB:GPIOB->ODR=copy_u16PortValue;break;
			case GPIO_PORTC:GPIOC->ODR=copy_u16PortValue;break;
			case GPIO_PORTD:GPIOD->ODR=copy_u16PortValue;break;
			case GPIO_PORTE:GPIOE->ODR=copy_u16PortValue;break;
			case GPIO_PORTF:GPIOF->ODR=copy_u16PortValue;break;
			case GPIO_PORTG:GPIOG->ODR=copy_u16PortValue;break;
		}             
	}
	else 
		lacal_u8ErrorState = STD_TYPE_NOK;
	return lacal_u8ErrorState;
}

u8 GPIO_GetPinValue(u8 copy_u8portID,u8 copy_u8PinID)
{
	//u8 lacal_u8ErrorState = STD_TYPE_OK;
	u8 Pin_Value=0;
	if(copy_u8portID <= GPIO_PORTG && copy_u8PinID <= GPIO_PIN15)
	{
		switch(copy_u8portID)
		{
			case GPIO_PORTA:  Pin_Value = GET_BIT(GPIOA->IDR,copy_u8PinID);break;
			case GPIO_PORTB:  Pin_Value = GET_BIT(GPIOB->IDR,copy_u8PinID);break;
			case GPIO_PORTC:  Pin_Value = GET_BIT(GPIOC->IDR,copy_u8PinID);break;
			case GPIO_PORTD:  Pin_Value = GET_BIT(GPIOD->IDR,copy_u8PinID);break;
			case GPIO_PORTE:  Pin_Value = GET_BIT(GPIOE->IDR,copy_u8PinID);break;
			case GPIO_PORTF:  Pin_Value = GET_BIT(GPIOF->IDR,copy_u8PinID);break;
			case GPIO_PORTG:  Pin_Value = GET_BIT(GPIOG->IDR,copy_u8PinID);break;
		}             
	}
		//else
		//lacal_u8ErrorState = STD_TYPE_NOK;
	return Pin_Value;
}
u8 GPIO_GetPortValue(u8 copy_u8portID,u16 * copy_u16ReturnPortValue)
{
	u8 lacal_u8ErrorState = STD_TYPE_OK;
	if(copy_u8portID <= GPIO_PORTG && copy_u16ReturnPortValue != NULL)
	{
		switch(copy_u8portID)
		{
			case GPIO_PORTA:*copy_u16ReturnPortValue = (u16)(GPIOA->IDR);break;
			case GPIO_PORTB:*copy_u16ReturnPortValue = (u16)(GPIOB->IDR);break;
			case GPIO_PORTC:*copy_u16ReturnPortValue = (u16)(GPIOC->IDR);break;
			case GPIO_PORTD:*copy_u16ReturnPortValue = (u16)(GPIOD->IDR);break;
			case GPIO_PORTE:*copy_u16ReturnPortValue = (u16)(GPIOE->IDR);break;
			case GPIO_PORTF:*copy_u16ReturnPortValue = (u16)(GPIOF->IDR);break;
			case GPIO_PORTG:*copy_u16ReturnPortValue = (u16)(GPIOG->IDR);break;
		}             
	}
	else 
		lacal_u8ErrorState = STD_TYPE_NOK;
	return lacal_u8ErrorState;
}

u8 GPIO_TogglePin(u8 copy_u8portID,u8 copy_u8PinID)
{
	u8 lacal_u8ErrorState = STD_TYPE_OK;
	if(copy_u8portID <= GPIO_PORTG && copy_u8PinID <= GPIO_PIN15)
	{
		switch(copy_u8portID)
		{
			case GPIO_PORTA:TOG_BIT(GPIOA->ODR,copy_u8PinID);break;
			case GPIO_PORTB:TOG_BIT(GPIOB->ODR,copy_u8PinID);break;
			case GPIO_PORTC:TOG_BIT(GPIOC->ODR,copy_u8PinID);break;
			case GPIO_PORTD:TOG_BIT(GPIOD->ODR,copy_u8PinID);break;
			case GPIO_PORTE:TOG_BIT(GPIOE->ODR,copy_u8PinID);break;
			case GPIO_PORTF:TOG_BIT(GPIOF->ODR,copy_u8PinID);break;
			case GPIO_PORTG:TOG_BIT(GPIOG->ODR,copy_u8PinID);break;
		}             
	}
	else 
		lacal_u8ErrorState = STD_TYPE_NOK;
	return lacal_u8ErrorState;
}

//u8 GPIO_Lockpin              (u8 copy_u8portID,u8 copy_u8PinID)
