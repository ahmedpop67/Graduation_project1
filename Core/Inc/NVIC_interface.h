 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/
														
#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H

void NVIC_voidEnableInterrupt(u8 copy_u8IntNumber);
void NVIC_voidDisableInterrupt(u8 copy_u8IntNumber);
void NVIC_voidSetPeningFlag(u8 copy_u8IntNumber);
void NVIC_voidClearPeningFlag(u8 copy_u8IntNumber);
u8 NVIC_voidGetActiveFlag(u8 copy_u8IntNumber);
void NVIC_voidSetPriority(u8 copy_u8IntID,u8 copy_u8Group_ID,u8 Sub_ID);

#endif
