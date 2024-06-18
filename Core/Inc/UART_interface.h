/*
 * UART_interface.h
 *
 *  Created on: Feb 15, 2024
 *      Author: Ahmed Hassan
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


typedef enum
{
	Buffer_is_empty,
	Buffer_is_full,
	Buffer_is_success
}Buffer_state;

/**********************************************/
/* 			USART Register Structure 		  */
/**********************************************/
typedef struct{
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 BRR;
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 CR3;
	volatile u32 GTPR;
}USART_t;

/**********************************************/
/* 		The USART Structure Pointer 		  */
/**********************************************/
#define 	UART1 		((USART_t *)0x40013800)
#define 	UART2 		((USART_t *)0x40004400)

typedef struct
{
	u32 BaudRate;
	u8 DataWidth;
	u8 StopBits;
	u8 Parity_Enable;
	u8 Parity_Selection;
	u8 TransferDirection; // TX_ONLY  RX_ONLY  TX_RX
	u8 HardwareFlowControl;
	u8 Oversampling;
}USART_InitType;

typedef struct
{
	u8 ClockOutput;
	u8 ClockPolarity;
	u8 ClockPhase;
	u8 LastBitClockPulse;
}USART_ClockInitTypeDef;

typedef enum
{
  SUCCESS = 0U,
  ERROR = !SUCCESS
} ErrorStatus;

#define OVER_SAMPLING_16	0
#define OVER_SAMPLING_8 	1

#define TX_ONLY             0
#define RX_ONLY             1
#define TX_RX               2

#define EVEN_PARITY         0
#define ODD_PARITY          1

#define MODE_8BIT			0
#define MODE_9BIT			1

#define STOP_BIT_1			0
#define STOP_BIT_0_5		1
#define STOP_BIT_2			2
#define STOP_BIT_1_5		3

#define ENABLE				1
#define DISABLE				0

void MUART_voidInit(USART_InitType         *A_InitStruct      ,
		            USART_ClockInitTypeDef *A_ClockInitStruct ,
		            USART_t                *USARTx
					);

void MUART_voidEnable(USART_t *USARTx);

void MUART_voidTransmitByte (USART_t *USARTx,u8 A_u8Byte);

void MUART_voidTransmitString (USART_t *USARTx, u8 * A_ptru8String );

u8 MUART_u8ReceiveByteSynchNonBlocking ( USART_t *USARTx );

u8 * MUART_ptrReceiveStringSynchNonBlocking ( USART_t *USARTx );

void MUART_RxIntSetStatus(USART_t *USARTx, u8 A_u8Status) ;

void MUART_voidClearFlags(USART_t *USARTx) ;

u8 MUART_u8ReadDataRegister(USART_t *USARTx) ;

void MUART1_voidSetCallBack( Buffer_state (*ptr) (void) ) ;

void MUART2_voidSetCallBack( Buffer_state (*ptr) (void) ) ;

void MUART_u8ReceiveByteASynch (  USART_t *A_xUART_Type );

Buffer_state MUART_Buffer_Write();

Buffer_state MUART_ReadData(u8* A_u8PtrData);

void APP_Sort_Buffer();

Buffer_state MUART_WriteData(u8* A_u8PtrData);

ErrorStatus MUART_ErrorStatusTransmitData(USART_t *A_xUART_Type);


void MUART_voidCleanRxBuffer(u8 A_u8NewData);

#endif /* UART_INTERFACE_H_ */
