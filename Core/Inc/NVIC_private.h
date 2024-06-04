 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/
														
#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H


#define NVIC_BASE                0xE000E100

#define NVIC_ISER0            *((volatile u32*)(NVIC_BASE))
#define NVIC_ISER1            *((volatile u32*)(NVIC_BASE+0x004))
#define NVIC_ISER2            *((volatile u32*)(NVIC_BASE+0x008))
												  
#define NVIC_ICER0            *((volatile u32*)(NVIC_BASE+0x080))
#define NVIC_ICER1            *((volatile u32*)(NVIC_BASE+0x084))
#define NVIC_ICER2            *((volatile u32*)(NVIC_BASE+0x088))
												  
#define NVIC_ISPR0            *((volatile u32*)(NVIC_BASE+0x100))
#define NVIC_ISPR1            *((volatile u32*)(NVIC_BASE+0x104))
#define NVIC_ISPR2            *((volatile u32*)(NVIC_BASE+0x108))
												  
#define NVIC_ICPR0            *((volatile u32*)(NVIC_BASE+0x180))
#define NVIC_ICPR1            *((volatile u32*)(NVIC_BASE+0x184))
#define NVIC_ICPR2            *((volatile u32*)(NVIC_BASE+0x188))
												  
#define NVIC_IABR0            *((volatile u32*)(NVIC_BASE+0x200))
#define NVIC_IABR1            *((volatile u32*)(NVIC_BASE+0x204))
#define NVIC_IABR2            *((volatile u32*)(NVIC_BASE+0x208))

#define NVIC_IPR               (volatile u8  *(NVIC_BASE+0x300))

#define SCB_AIRCR             *((volatile u32*)(0xE000ED00+0x0C))



#define NVIC_GROUP4_SUP_0      0x05FA0300
#define NVIC_GROUP3_SUP_1      0x05FA0400
#define NVIC_GROUP2_SUP_2      0x05FA0500
#define NVIC_GROUP1_SUP_3      0x05FA0600
#define NVIC_GROUP0_SUP_4      0x05FA0700

#endif
