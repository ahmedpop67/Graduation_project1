 /*****************************************************************************/
 /***************************  NAME  :  ayman saad   **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#ifndef INC_APP_H_
#define INC_APP_H_

#define Automatic_ON       1
#define Automatic_OFF      0


#define V2V_ENABLE         1
#define V2V_DISABLE        0

#define max_speed          7


#define Go              0
#define Back            1
#define Right           2
#define Left            3
#define Forward_Right   4
#define Forward_Left    5
#define Backward_Right  6
#define Backward_Left   7
#define Stop            8

#define Speed1          1
#define Speed2          2
#define Speed3          3
#define Speed4          4
#define Speed5          5
#define Speed6          6
#define Speed7          7

void ProcessingFun (void);

void APP_voidCalcForword_Distance();
void APP_voidCalcBackword_Distance();
void APP_voidCalcRight_Distance();
void APP_voidCalcLeft_Distance();

void APP_VoidStop();
void APP_voidGoTasks () ;
void APP_voidBackTasks () ;
void APP_voidBackward_RightTasks () ;
void APP_voidBackward_LEFTTasks () ;
void APP_voidRight_LeftTasks () ;
void APP_voidForward_RightTasks () ;
void APP_voidForward_LeftTasks () ;
void APP_voidLane_Change();
void APP_V2V_Connection();
void APP_GET_UART_Command();

#endif /* INC_APP_H_ */
