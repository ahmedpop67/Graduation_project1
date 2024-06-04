 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GPIO_interface.h"
#include "RCC_interface.h"
#include "NVIC_interface.h"
#include "UART_private.h"
#include "UART_configuration.h"
#include "UART_interface.h"

u8 G_u8DataFromUART = 0;
/*global array to store recived data from UART*/
u8 global_u8String[MAX_SIZE_DATA_BUFFER];

u8 local_u8_RX_Busyflag=0;

/*pointer to function for UART1 for call back*/
void (*MUSART1_CallBack)(void);

/*pointer to function for UART2 for call back*/
void (*MUSART2_CallBack)(void);

/*pointer to function for UART6 for call back*/
void (*MUSART3_CallBack)(void);


void MUART_voidInit(USART_InitType *A_InitStruct,USART_ClockInitTypeDef *A_xUART_ClockInitStruct,USART_t *A_xUART_Type)
{
	/* Configuration as HSI/2 --> 8 MHz */
	//RCC_voidInit();

	//MRCC_voidEnablePerephiralClock(RCC_AHB1, RCC_EN_GPIOA); /* Enable GPIOA from RCC */
	//MRCC_voidEnablePerephiralClock(RCC_AHB1, RCC_EN_GPIOB); /* Enable GPIOB from RCC */

	/* Enable selected UART from RCC */
	if (A_xUART_Type == UART1)
	{
		/*configer Tx1 as alt fun*/
		GPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN2 , GPIO_OUTPUT_10M_AF_PP) ;

		/*configer Rx1 as alt fun*/
		GPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN2 , GPIO_OUTPUT_10M_AF_PP) ;

		/*Enable interrupt of UART1 from NVIC*/
		NVIC_voidEnableInterrupt(37);
	}
	else if (A_xUART_Type == UART2)
	{
		/*configer Tx2 as alt fun*/
		GPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN2 , GPIO_OUTPUT_10M_AF_PP) ;

		/*configer Rx2 as alt fun*/
		GPIO_voidSetPinMode(GPIO_PORTA , GPIO_PIN2 , GPIO_OUTPUT_10M_AF_PP) ;

		/*Enable interrupt of UART2 from NVIC*/
		NVIC_voidEnableInterrupt(38);
	}

		 A_xUART_Type->BRR = UART_BRR_SAMPLING16(__PCLK__,A_InitStruct->BaudRate);

		 A_xUART_Type->CR1 = (A_InitStruct->Oversampling        << MUSART_CR1_OVER8_BIT ) |
    		            (A_InitStruct->HardwareFlowControl << MUSART_CR1_UE_BIT    ) |
    			        (A_InitStruct->DataWidth           << MUSART_CR1_M_BIT     ) |
    			        (A_InitStruct->Parity_Enable       << MUSART_CR1_PCE_BIT   ) |
    			        (A_InitStruct->Parity_Selection    << MUSART_CR1_PS_BIT    ) ;

    switch (A_InitStruct->TransferDirection)
    {
    case TX_ONLY:
    	 SET_BIT(A_xUART_Type->CR1, MUSART_CR1_TE_BIT);
    	 break;
    case RX_ONLY:
    	 SET_BIT(A_xUART_Type->CR1, MUSART_CR1_RE_BIT);
    	 break;
    case TX_RX:
    	 SET_BIT(A_xUART_Type->CR1, MUSART_CR1_TE_BIT);
    	 SET_BIT(A_xUART_Type->CR1, MUSART_CR1_RE_BIT);
    	 break;
    }
    A_xUART_Type->CR2 =   (A_InitStruct           ->StopBits          << MUSART_CR2_STOP_BIT  )  |
    				      (A_xUART_ClockInitStruct->ClockOutput       << MUSART_CR2_CLKEN_BIT )  |
    				      (A_xUART_ClockInitStruct->ClockPhase        << MUSART_CR2_CPHA_BIT  )  |
    				      (A_xUART_ClockInitStruct->ClockPolarity     << MUSART_CR2_CPOL_BIT  )  |
    				      (A_xUART_ClockInitStruct->LastBitClockPulse << MUSART_CR2_LBCL_BIT  )  ;

    A_xUART_Type->SR = 0;				    	          							             ;
}

void MUART_voidEnable( USART_t *A_xUART_Type)
{
	SET_BIT(A_xUART_Type->CR1,MUSART_CR1_UE_BIT);
}

void MUART_voidDisable( USART_t *A_xUART_Type)
{
	CLR_BIT(A_xUART_Type->CR1,MUSART_CR1_UE_BIT);
}

void MUART_voidTransmitByte ( USART_t *A_xUART_Type,u8 A_u8Byte)
{
	/*wait to TX be empty*/
	while (READ_BIT(A_xUART_Type->SR,MUSART_SR_TXE_BIT)==0);

	/*write data transfered into data register*/
	A_xUART_Type->DR= A_u8Byte;

	/*wait to complete transmition*/
	while (READ_BIT(A_xUART_Type->SR,MUSART_SR_TC_BIT)==0);

	/*clear complete transmition flag to be ready to new transmition*/
	CLR_BIT(A_xUART_Type->SR,MUSART_SR_TC_BIT);
}

void MUART_voidTransmitString ( USART_t *A_xUART_Type, u8 * A_ptru8String )
{
	u8 L_u8Iterator =0;
	while (A_ptru8String[L_u8Iterator] != '\0')
	{
		MUART_voidTransmitByte(A_xUART_Type, A_ptru8String[L_u8Iterator]);
		L_u8Iterator++;
	}
}

u8 MUART_u8ReceiveByteSynchNonBlocking (  USART_t *A_xUART_Type )
{
	u8  L_u8Data    = 0;
	u32 L_u8TimeOut = 0;
	while ((READ_BIT(A_xUART_Type->SR,MUSART_SR_RXNE_BIT)==0) && (L_u8TimeOut < THRESHOLD_VALUE) )
	{
		L_u8TimeOut++;
	}
	if (L_u8TimeOut==THRESHOLD_VALUE)
	{
		L_u8Data = 255;
	}
	else
	{
		L_u8Data = A_xUART_Type->DR;
	}
	return L_u8Data;
}

void MUART_u8ReceiveByteASynch (  USART_t *A_xUART_Type )
{
	if(local_u8_RX_Busyflag == 0)
	{
		local_u8_RX_Busyflag=1;
		SET_BIT(A_xUART_Type->CR1 , MUSART_CR1_RXNEIE_BIT);
	}
}

u8 * MUART_ptrReceiveStringSynchNonBlocking (  USART_t *A_xUART_Type )
{
	u8 L_u8Iterator = 0 ;
	u8 L_u8DataCome ;
	while( ( L_u8DataCome = MUART_u8ReceiveByteSynchNonBlocking(A_xUART_Type) ) != 13 )
	{
		global_u8String[ L_u8Iterator ] = L_u8DataCome ;
		L_u8Iterator++;
	}
	global_u8String[L_u8Iterator] = '\0';
	return ( global_u8String );
}

void MUART_RxIntSetStatus(USART_t *USARTx, u8 A_u8Status)
{
	switch (A_u8Status)
	{
	case ENABLE :  SET_BIT(USARTx->CR1 , MUSART_CR1_RXNEIE_BIT); break;
	case DISABLE:  CLR_BIT(USARTx->CR1 , MUSART_CR1_RXNEIE_BIT); break;
	}
}

void MUART_voidClearFlags(USART_t *USARTx)
{
	USARTx->SR = 0;
}

u8 MUART_u8ReadDataRegister(USART_t *USARTx)
{
	return USARTx -> DR;
}

void MUART1_voidSetCallBack( void (*ptr) (void) )
{

	MUSART1_CallBack =ptr;
}

void MUART2_voidSetCallBack( void (*ptr) (void) )
{
	MUSART2_CallBack = ptr;
}

void MUART6_voidSetCallBack( void (*ptr) (void) )
{
	MUSART3_CallBack = ptr;
}

/*IRQ of UART1*/
void USART1_IRQHandler(void)
{
    UART1->SR = 0;
    //G_u8DataFromUART = MUART_u8ReadDataRegister(UART1);
    local_u8_RX_Busyflag=0;
	if(MUSART1_CallBack!=NULL)
	{
		MUSART1_CallBack();
	}
}

/*IRQ of UART2*/
void USART2_IRQHandler(void)
{
	UART2->SR = 0;
	//G_u8DataFromUART = MUART_u8ReadDataRegister(UART2);
	local_u8_RX_Busyflag=0;
	if(MUSART2_CallBack!=NULL)
	{
		MUSART2_CallBack();
	}
}

