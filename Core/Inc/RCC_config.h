 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/
														
#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/*options:  RCC_HSE_CRYSTAL
            RCC_HSE_RC
            RCC_HSI
            RCC_PLL
*/
#define RCC_CLOCK_TYPE     RCC_HSI

#if RCC_CLOCK_TYPE == RCC_PLL
/*chose from these ooptions
		    RCC_PLL_IN_HSI_DIV_2
		    RCC_PLL_IN_HSE_DIV_2
		    RCC_PLL_IN_HSE
*/
#define RCC_PLL_CLOCK   RCC_PLL_IN_HSI_DIV_2


/*RCC_PLL_MUL :
  options
        RCC_PLL_IN_MUL_2
        RCC_PLL_IN_MUL_3
        RCC_PLL_IN_MUL_4
        RCC_PLL_IN_MUL_5
        RCC_PLL_IN_MUL_6
        RCC_PLL_IN_MUL_7
        RCC_PLL_IN_MUL_8
        RCC_PLL_IN_MUL_9
        RCC_PLL_IN_MUL_10
        RCC_PLL_IN_MUL_11
        RCC_PLL_IN_MUL_12
        RCC_PLL_IN_MUL_13
        RCC_PLL_IN_MUL_14
        RCC_PLL_IN_MUL_15
        RCC_PLL_IN_MUL_16
*/
#define RCC_PLL_MUL      RCC_PLL_IN_MUL_4

#endif

/*AHP prescaler 
 options:
         RCC_AHP_DIV_1
         RCC_AHP_DIV_2
         RCC_AHP_DIV_4
         RCC_AHP_DIV_8
         RCC_AHP_DIV_16
         RCC_AHP_DIV_64
         RCC_AHP_DIV_128
         RCC_AHP_DIV_256
         RCC_AHP_DIV_512
*/
#define RCC_AHP_PRESCALER   RCC_AHP_DIV_1


/*APB1 prescaler 
 options:
         RCC_APB1_DIV_1
         RCC_APB1_DIV_2
         RCC_APB1_DIV_4
         RCC_APB1_DIV_8
         RCC_APB1_DIV_16
*/
#define RCC_APB1_PRESCALER   RCC_APB1_DIV_1


/*APB2 prescaler 
 options:
         RCC_APB2_DIV_1
         RCC_APB2_DIV_2
         RCC_APB2_DIV_4
         RCC_APB2_DIV_8
         RCC_APB2_DIV_16
*/
#define RCC_APB2_PRESCALER   RCC_APB2_DIV_1


#endif
