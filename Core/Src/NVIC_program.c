 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  DATE  :  8/30/2023    **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/
 
 #include "STD_TYPES.h"
 #include "BIT_MATH.h"
 
 #include "NVIC_interface.h"
 #include "NVIC_private.h"
 #include "NVIC_config.h"
 
void NVIC_voidEnableInterrupt(u8 copy_u8IntNumber)
{
	if(copy_u8IntNumber<31)
	{
		NVIC_ISER0=1<<copy_u8IntNumber;
	}
	else if(copy_u8IntNumber<63)
	{
		copy_u8IntNumber-=31;
		NVIC_ISER1=1<<copy_u8IntNumber;
	}
	else if(copy_u8IntNumber<95)
	{
		copy_u8IntNumber-=63;
		NVIC_ISER2=1<<copy_u8IntNumber;
	}
}
void NVIC_voidDisableInterrupt(u8 copy_u8IntNumber)
{
	if(copy_u8IntNumber<31)
	{
		NVIC_ICER0=1<<copy_u8IntNumber;
	}
	else if(copy_u8IntNumber<63)
	{
		copy_u8IntNumber-=31;
		NVIC_ICER1=1<<copy_u8IntNumber;
	}
	else if(copy_u8IntNumber<95)
	{
		copy_u8IntNumber-=63;
		NVIC_ICER2=1<<copy_u8IntNumber;
	}
}
void NVIC_voidSetPeningFlag(u8 copy_u8IntNumber)
{
	if(copy_u8IntNumber<31)
	{
		NVIC_ISPR0=1<<copy_u8IntNumber;
	}
	else if(copy_u8IntNumber<63)
	{
		copy_u8IntNumber-=31;
		NVIC_ISPR1=1<<copy_u8IntNumber;
	}
	else if(copy_u8IntNumber<95)
	{
		copy_u8IntNumber-=63;
		NVIC_ISPR2=1<<copy_u8IntNumber;
	}
}
void NVIC_voidClearPeningFlag(u8 copy_u8IntNumber)
{
	if(copy_u8IntNumber<31)
	{
		NVIC_ICPR0=1<<copy_u8IntNumber;
	}
	else if(copy_u8IntNumber<63)
	{
		copy_u8IntNumber-=31;
		NVIC_ICPR1=1<<copy_u8IntNumber;
	}
	else if(copy_u8IntNumber<95)
	{
		copy_u8IntNumber-=63;
		NVIC_ICPR2=1<<copy_u8IntNumber;
	}
}
u8 NVIC_voidGetActiveFlag(u8 copy_u8IntNumber)
{
	u8 local_Active_flag;
	if(copy_u8IntNumber<31)
	{
		local_Active_flag=GET_BIT(NVIC_IABR0,copy_u8IntNumber);
	}
	else if(copy_u8IntNumber<63)
	{
		copy_u8IntNumber-=31;
		local_Active_flag=GET_BIT(NVIC_IABR1,copy_u8IntNumber);
	}
	else if(copy_u8IntNumber<95)
	{
		copy_u8IntNumber-=63;
		local_Active_flag=GET_BIT(NVIC_IABR2,copy_u8IntNumber);
	}
	return local_Active_flag;
}
/*void NVIC_voidSetPriority(u8 copy_u8IntID,u8 copy_u8Group_ID,u8 copy_u8Sub_ID)
{
	if(copy_u8IntID<60)
	{
		SCB_AIRCR=NVIC_GROUP_SUB_DISTRIBTION;
		u8 local_NVIC_priority=copy_u8Sub_ID|(copy_u8Group_ID<<((NVIC_GROUP_SUB_DISTRIBTION-0x05FA0300)/256));
		NVIC_IPR[copy_u8IntID]=local_NVIC_priority<<4;
	}
}*/
