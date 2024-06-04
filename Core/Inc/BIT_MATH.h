 /*****************************************************************************/
 /***************************  NAME  :  ahmed hassan **************************/
 /***************************  VERSION :  1.0        **************************/
 /*****************************************************************************/

#ifndef SERVIES_BIT_MATH_H_
#define SERVIES_BIT_MATH_H_


#define WRITE_BIT(Reg,Bit)			        Reg=(1<<Bit)
#define SET_BIT(Reg,Bit)					(Reg|=(1<<Bit))
#define CLR_BIT(Reg,Bit)					(Reg&=(~(1<<Bit)))
#define GET_BIT(Reg,Bit)					((Reg>>Bit)&1)
#define TGL_BIT(Reg,Bit)					(Reg^=(1<<Bit))
#define TOG_BIT(VAR,BIT_NUM)                 VAR^=(1<<BIT_NUM)
#define RSHFT_REG(Reg,No)					(Reg>>=No)
#define LSHFT_REG(Reg,No)					(Reg<<=No)
#define CRSHFT_REG(Reg,No)					(Reg=(Reg>>No)|(Reg<<(sizeof(Reg)*8-No)))
#define CLSHFT_REG(Reg,No)					(Reg=(Reg<<No)|(Reg>>(sizeof(Reg)*8-No)))
#define ASSIGN_REG(Reg,Value)				(Reg=Value)
#define SET_REG(Reg)						(Reg=~0)
#define CLR_REG(Reg)						(Reg&=0)
#define TGL_REG(Reg)						(Reg=~Reg)
#define TGL_NO_ASSIGN(Reg,Bit)              ((Reg^(1<<Bit)))
#define READ_BIT(reg,bit)                   ( (reg & (1<<bit))) >>bit

#define WRITE_BIT_value(reg,bit,value) (reg=reg&~(1<<bit)|(value<<bit))


#define FLASH_BASE_ADDRESS           0x00000000
#define SRAM_BASE_ADDRESS            0x20000000
#define PERIPHERAL_BASE_ADDRESS      0x40000000
#define SRAM_BBR_BASE_ADDRESS        0x20000000
#define SRAM_BBA_BASE_ADDRESS        0x22000000
#define PERIPHERAL_BBR_BASE_ADDRESS  0x40000000
#define PERIPHERAL_BBA_BASE_ADDRESS  0x42000000

#define BIT_BAND(reg,bit)            *((vu32*)(PERIPHERAL_BBA_BASE_ADDRESS+(((vu32)reg-PERIPHERAL_BASE_ADDRESS)*32+(bit*4))))


#define SET_BIT_BAND(reg,bit)         BIT_BAND(reg,bit) = 1
#define CLR_BIT_BAND(reg,bit)         BIT_BAND(reg,bit) = 0


/* dealing with nibble (2 Bit) */
#define SET_2BIT_Val(VAR,START_BIT,_4BIT_VAL)       (VAR=((VAR & ~(0x3<<START_BIT))|(_4BIT_VAL<<START_BIT)))
#define SET_2BIT(VAR,START_BIT)                  SET_2BIT_Val(VAR,START_BIT,0X3)
#define CLR_2BIT(VAR,START_BIT)                  SET_2BIT_Val(VAR,START_BIT,0X0)
#define GET_2BIT(VAR,START_BIT)                  ((VAR&(0XF<<START_BIT))>>START_BIT)
#define TOG_2BIT(VAR,START_BIT)        	         SET_BIT(VAR,START_BIT,~SET_2BIT_Val(VAR,START_BIT))

/* dealing with nibble (3 Bit) */
#define SET_3BIT_Val(VAR,START_BIT,_3BIT_VAL)       (VAR=((VAR & ~(0x7<<START_BIT))|(_4BIT_VAL<<START_BIT)))
#define SET_3BIT(VAR,START_BIT)                  SET_3BIT_Val(VAR,START_BIT,0X7)
#define CLR_3BIT(VAR,START_BIT)                  SET_3BIT_Val(VAR,START_BIT,0X0)
#define GET_3BIT(VAR,START_BIT)                  ((VAR&(0XF<<START_BIT))>>START_BIT)
#define TOG_3BIT(VAR,START_BIT)        	         SET_BIT(VAR,START_BIT,~SET_3BIT_Val(VAR,START_BIT))

/* dealing wBITith nibble (4 Bit) */
#define SET_4BIT_Val(VAR,START_BIT,_4BIT_VAL)       (VAR=((VAR & ~(0xF<<START_BIT))|(_4BIT_VAL<<START_BIT)))
#define SET_4BIT(VAR,START_BIT)                  SET_4BIT_Val(VAR,START_BIT,0XF)
#define CLR_4BIT(VAR,START_BIT)                  SET_4BIT_Val(VAR,START_BIT,0X0)
#define GET_4BIT(VAR,START_BIT)                  ((VAR&(0XF<<START_BIT))>>START_BIT)
#define TOG_4BIT(VAR,START_BIT)        	         SET_BIT(VAR,START_BIT,~SET_4BIT_Val(VAR,START_BIT))

/* dealing with byte (8 Bit) */
#define SET_BYTE_Val(VAR,START_BIT,_8BIT_VAL)         (VAR=((VAR & ~(0xFF<<START_BIT))|(_8BIT_VAL<<START_BIT)))
#define SET_BYTE(VAR,START_BIT)                    SET_BYTE_Val(VAR,START_BIT,0XFF)
#define CLR_BYTE(VAR,START_BIT)                    SET_BYTE_Val(VAR,START_BIT,0X00)
#define GET_BYTE(VAR,START_BIT)                    ((VAR&(0XFF<<START_BIT))>>START_BIT)
#define TOG_BYTE(VAR,START_BIT)                    SET_BIT(VAR,START_BIT,~SET_BYTE_Val(VAR,START_BIT))



#define CONC(B7,B6,B5,B4,B3,B2,B1,B0)        CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)
#define CONC_HELP(B7,B6,B5,B4,B3,B2,B1,B0)   (0b##B7##B6##B5##B4##B3##B2##B1##B0)

#endif /* SERVIES_BIT_MATH_H_ */
