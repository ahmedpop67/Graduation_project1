 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  DATE  :  8/15/2023    **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/


#ifndef STK_INTERFACE_H
#define STK_INTERFACE_H


/* Apply Clock Choise From Configuration File
   Disable SysTick interrupt
   Disable SysTick 					*/

void MSTK_voidInit(void);
void MSTK_voidSetBusyWait( u32 Copy_u32Ticks );
void MSTK_voidSetIntervalSingle  ( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void MSTK_voidSetIntervalPeriodic( u32 Copy_u32Ticks, void (*Copy_ptr)(void) );
void MSTK_voidStopInterval(void);
u32  MSTK_u32GetElapsedTime(void);
u32  MSTK_u32GetRemainingTime(void);


#endif
