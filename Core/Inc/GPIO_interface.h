 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

/*direction options
*/

/* macros for PortsID */
#define GPIO_PORTA           1
#define GPIO_PORTB           2
#define GPIO_PORTC           3
#define GPIO_PORTD           4
#define GPIO_PORTE           5
#define GPIO_PORTF           6
#define GPIO_PORTG           7

/* macros for PinsID */
#define GPIO_PIN0            0
#define GPIO_PIN1            1
#define GPIO_PIN2            2
#define GPIO_PIN3            3
#define GPIO_PIN4            4
#define GPIO_PIN5            5
#define GPIO_PIN6            6
#define GPIO_PIN7            7
#define GPIO_PIN8            8 
#define GPIO_PIN9            9 
#define GPIO_PIN10           10
#define GPIO_PIN11           11
#define GPIO_PIN12           12
#define GPIO_PIN13           13
#define GPIO_PIN14           14
#define GPIO_PIN15           15

/* macros for modes */
#define GPIO_INPUT_ANALOG              0b0000
#define GPIO_INPUT_FLOATING            0b0100
#define GPIO_INPUT_PU_PD               0b1000

#define GPIO_OUTPUT_10M_PP             0b0001
#define GPIO_OUTPUT_10M_OD             0b0101
#define GPIO_OUTPUT_10M_AF_PP          0b1001
#define GPIO_OUTPUT_10M_AF_OD          0b1101
									      
#define GPIO_OUTPUT_2M_PP              0b0010
#define GPIO_OUTPUT_2M_OD              0b0110
#define GPIO_OUTPUT_2M_AF_PP           0b1010
#define GPIO_OUTPUT_2M_AF_OD           0b1110
									      
#define GPIO_OUTPUT_50M_PP             0b0011
#define GPIO_OUTPUT_50M_OD             0b0111
#define GPIO_OUTPUT_50M_AF_PP          0b1011
#define GPIO_OUTPUT_50M_AF_OD          0b1111

/* macros for values */

//for input mode 
#define GPIO_INPUT_PD                 0
#define GPIO_INPUT_PU                 1

//for output mode 
#define GPIO_OUTPUT_Push              1
#define GPIO_OUTPUT_Pull              0
#define GPIO_OUTPUT_OD_LOW            0
#define GPIO_OUTPUT_OD_FLOATING       1

#define GPIO_LOW                      0
#define GPIO_HIGH                     1

void  GPIO_VoidInit();
void  GPIO_VoidDeInit();

u8 GPIO_voidSetPinMode       (u8 copy_u8portID,u8 copy_u8PinID,u8 copy_u8Mode);
u8 GPIO_voidSetPinValue      (u8 copy_u8portID,u8 copy_u8PinID,u8 copy_u8Value);
u8 GPIO_voidSetPortValue     (u8 copy_u8portID,u16 copy_u16PortValue);

u8 GPIO_GetPinValue          (u8 copy_u8portID,u8 copy_u8PinID);
u8 GPIO_GetPortValue         (u8 copy_u8portID,u16 * copy_u16ReturnPinValue);

u8 GPIO_TogglePin            (u8 copy_u8portID,u8 copy_u8PinID);

//u8 GPIO_Lockpin              (u8 copy_u8portID,u8 copy_u8PinID);


#endif
