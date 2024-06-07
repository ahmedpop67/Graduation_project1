 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#ifndef UART_CONFIGURATION_H_
#define UART_CONFIGURATION_H_



#define __BAUDRATE__ 9600
#define __PCLK__	 8000000

#define THRESHOLD_VALUE 500000

/*maximum size of data recived from UART*/
#define MAX_SIZE_DATA_BUFFER  200

/*maximum size of data Transmitted from UART*/
#define MAX_SIZE_TX_DATA_BUFFER  20

#define TIME_LIMIT      1000000

#endif /* UART_CONFIGURATION_H_ */
