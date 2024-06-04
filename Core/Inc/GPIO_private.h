 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/
 
#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#define GPIOA_BASE      0X40010800
#define GPIOB_BASE      0X40010C00
#define GPIOC_BASE      0X40011000
#define GPIOD_BASE      0X40011400
#define GPIOE_BASE      0X40011800
#define GPIOF_BASE      0X40011C00
#define GPIOG_BASE      0X40012000

typedef struct
{
	volatile u32 CRL;
	volatile u32 CRH;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 BRR;
	volatile u32 LCKR;
}GPIO_Typedef;

#define GPIOA         ((GPIO_Typedef*)(GPIOA_BASE))
#define GPIOB         ((GPIO_Typedef*)(GPIOB_BASE))
#define GPIOC         ((GPIO_Typedef*)(GPIOC_BASE))
#define GPIOD         ((GPIO_Typedef*)(GPIOD_BASE))
#define GPIOE         ((GPIO_Typedef*)(GPIOE_BASE))
#define GPIOF         ((GPIO_Typedef*)(GPIOF_BASE))
#define GPIOG         ((GPIO_Typedef*)(GPIOG_BASE))

#define GPIO_u8_INPUT_ANALOG             0
#define GPIO_u8_INPUT_FLOATING           4
#define GPIO_u8_INPUT_PU_PD              8

#define GPIO_u8_OUTPUT_10M_PP            1
#define GPIO_u8_OUTPUT_10M_OD            5
#define GPIO_u8_OUTPUT_10M_AF_PP         9
#define GPIO_u8_OUTPUT_10M_AF_OD         D

#define GPIO_u8_OUTPUT_2M_PP             2
#define GPIO_u8_OUTPUT_2M_OD             6
#define GPIO_u8_OUTPUT_2M_AF_PP          A
#define GPIO_u8_OUTPUT_2M_AF_OD          E

#define GPIO_u8_OUTPUT_50M_PP            3
#define GPIO_u8_OUTPUT_50M_OD            7
#define GPIO_u8_OUTPUT_50M_AF_PP         B
#define GPIO_u8_OUTPUT_50M_AF_OD         f

#define GPIO_u8_INPUT_PD                 0
#define GPIO_u8_INPUT_PU                 1
#define GPIO_u8_OUTPUT_Pull              0
#define GPIO_u8_OUTPUT_Push              1
#define GPIO_u8_OUTPUT_OD_LOW            0
#define GPIO_u8_OUTPUT_OD_FLOATING       1

#define concX(b7,b6,b5,b4,b3,b2,b1,b0)                                            concX_Help(b7,b6,b5,b4,b3,b2,b1,b0)
#define concX_Help(b7,b6,b5,b4,b3,b2,b1,b0)                                       0x##b7##b6##b5##b4##b3##b2##b1##b0

#define concB(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)              concB_Help(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)
#define concB_Help(b15,b14,b13,b12,b11,b10,b9,b8,b7,b6,b5,b4,b3,b2,b1,b0)         0b##b15##b14##b13##b12##b11##b10##b9##b8##b7##b6##b5##b4##b3##b2##b1##b0

#endif
