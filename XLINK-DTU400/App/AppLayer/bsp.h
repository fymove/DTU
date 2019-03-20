#ifndef _BSP_H_  
#define _BSP_H_ 

#include  <stdarg.h>
#include  <string.h>
#include  <stdlib.h>
#include  <ctype.h>
#include  <math.h>
#include <stdio.h>
#include "stm32f10x_conf.h" 
#include "stm32f10x.h"

typedef enum {
    COM1 = 0,
    COM2,
    COM3,
    COM4,
    COM5,
    COM6
}UART_COM_ENUM;  

#define UART1_DMA_EN        0
#define UART2_DMA_EN        1


#define RS4850Uart          COM1
#define GPRSUart            COM2  
#define RS4851Uart          COM3 
#define RS4852Uart          COM4 


#define DebugUart           RS4850Uart
#define VfdUart             RS4850Uart

#ifdef  F103RCT6
#define NEW_PCB_VER         0 
#else
#define NEW_PCB_VER         1    
#endif

#define UART1_TXD_PORT      GPIOA
#define UART1_TXD_PIN       GPIO_Pin_9

#define UART1_RXD_PORT      GPIOA
#define UART1_RXD_PIN       GPIO_Pin_10


#define UART1_DMA_TX_CHL    DMA1_Channel4
#define UART1_DMA_TX_TC     DMA1_FLAG_TC4 
#define UART1_DMA_TX_ADDR   (USART1_BASE+0x0004)

#define UART2_TXD_PORT      GPIOA
#define UART2_TXD_PIN       GPIO_Pin_2

#define UART2_RXD_PORT      GPIOA
#define UART2_RXD_PIN       GPIO_Pin_3


#define UART2_DMA_TX_CHL    DMA1_Channel7
#define UART2_DMA_TX_TC     DMA1_FLAG_TC7 
#define UART2_DMA_TX_ADDR   (USART2_BASE+0x0004)

#define UART3_TXD_PORT      GPIOB
#define UART3_TXD_PIN       GPIO_Pin_10

#define UART3_RXD_PORT      GPIOB
#define UART3_RXD_PIN       GPIO_Pin_11

#define UART4_TXD_PORT      GPIOC
#define UART4_TXD_PIN       GPIO_Pin_10

#define UART4_RXD_PORT      GPIOC
#define UART4_RXD_PIN       GPIO_Pin_11



#define GPRS_POWER_PORT     GPIOB               
#define GPRS_POWER_PIN      GPIO_Pin_9

#define    GPRS_PWRKEY_PORT    GPIOB
#define    GPRS_PWRKEY_PIN     GPIO_Pin_8

#define    GPRS_RTS_PORT        GPIOA
#define    GPRS_RTS_PIN        GPIO_Pin_1


#define SST25V_SCK_PORT     GPIOA
#define SST25V_SCK_PIN      GPIO_Pin_5

#define SST25V_MISO_PORT    GPIOA
#define SST25V_MISO_PIN     GPIO_Pin_6

#define SST25V_MOSI_PORT    GPIOA
#define SST25V_MOSI_PIN     GPIO_Pin_7

//#if NEW_PCB_VER
#define SST25V_CS_PORT      GPIOB
#define SST25V_CS_PIN       GPIO_Pin_0

#define SST25V_WP_PORT      GPIOC
#define SST25V_WP_PIN       GPIO_Pin_4

//#else
//#define SST25V_CS_PORT      GPIOC
//#define SST25V_CS_PIN       GPIO_Pin_4

//#define SST25V_WP_PORT      GPIOB
//#define SST25V_WP_PIN       GPIO_Pin_7
//#endif
#if 0
#define I2C_SDA_PORT        GPIOB
#define I2C_SDA_PIN         GPIO_Pin_11

#define I2C_SCK_PORT        GPIOB
#define I2C_SCK_PIN         GPIO_Pin_10

#define RTC_SCL_H           GPIO_SetBits(I2C_SCK_PORT, I2C_SCK_PIN)
#define RTC_SCL_L           GPIO_ResetBits(I2C_SCK_PORT, I2C_SCK_PIN)
#define RTC_SDA_H           GPIO_SetBits(I2C_SDA_PORT, I2C_SDA_PIN)
#define RTC_SDA_L           GPIO_ResetBits(I2C_SDA_PORT, I2C_SDA_PIN)
#define RTC_SCL_read        (GPIO_ReadInputDataBit(I2C_SCK_PORT, I2C_SCK_PIN)&0x01) 
#define RTC_SDA_read        (GPIO_ReadInputDataBit(I2C_SDA_PORT, I2C_SDA_PIN)&0x01) 

#define PCF8563_INT_PORT    GPIOC
#define PCF8563_INT_PIN     GPIO_Pin_8
          
#define KEY3_PORT           GPIOA
#define KEY3_PIN            GPIO_Pin_3

#define KEY2_PORT           GPIOA
#define KEY2_PIN            GPIO_Pin_4
#endif

//#define KEY1_PORT           GPIOC
//#define KEY1_PIN            GPIO_Pin_7

//#define KEY1_LED_PORT       GPIOC
//#define KEY1_LED_PIN        GPIO_Pin_8

//#define DO_JQ1_PORT         GPIOC
//#define DO_JQ1_PIN          GPIO_Pin_3

//#define DO_JQ2_PORT         GPIOC
//#define DO_JQ2_PIN          GPIO_Pin_2

//#define DO_JQ3_PORT         GPIOC
//#define DO_JQ3_PIN          GPIO_Pin_1

//#define DO_JQ4_PORT         GPIOC
//#define DO_JQ4_PIN          GPIO_Pin_0

#define RS485_0_CTL_PORT    GPIOB
#define RS485_0_CTL_PIN     GPIO_Pin_12


#define RS485_1_CTL_PORT    GPIOC
#define RS485_1_CTL_PIN     GPIO_Pin_5

#define RS485_2_CTL_PORT    GPIOC
#define RS485_2_CTL_PIN     GPIO_Pin_8

#ifdef XLINK
#define RS485_0_RCV_STATUS  GPIO_ResetBits(RS485_0_CTL_PORT, RS485_0_CTL_PIN)
#define RS485_0_SND_STATUS  GPIO_SetBits(RS485_0_CTL_PORT, RS485_0_CTL_PIN)

#define RS485_1_RCV_STATUS  GPIO_ResetBits(RS485_1_CTL_PORT, RS485_1_CTL_PIN)
#define RS485_1_SND_STATUS  GPIO_SetBits(RS485_1_CTL_PORT, RS485_1_CTL_PIN)

#define RS485_2_RCV_STATUS  GPIO_ResetBits(RS485_2_CTL_PORT, RS485_2_CTL_PIN)
#define RS485_2_SND_STATUS  GPIO_SetBits(RS485_2_CTL_PORT, RS485_2_CTL_PIN)


#else
#define RS485_0_RCV_STATUS  GPIO_SetBits(RS485_0_CTL_PORT, RS485_0_CTL_PIN)
#define RS485_0_SND_STATUS  GPIO_ResetBits(RS485_0_CTL_PORT, RS485_0_CTL_PIN)

#define RS485_1_RCV_STATUS  GPIO_SetBits(RS485_1_CTL_PORT, RS485_1_CTL_PIN)
#define RS485_1_SND_STATUS  GPIO_ResetBits(RS485_1_CTL_PORT, RS485_1_CTL_PIN)

#define RS485_2_RCV_STATUS  GPIO_SetBits(RS485_2_CTL_PORT, RS485_2_CTL_PIN)
#define RS485_2_SND_STATUS  GPIO_ResetBits(RS485_2_CTL_PORT, RS485_2_CTL_PIN)

#endif





#define DOG_PORT            GPIOA
#define DOG_PIN             GPIO_Pin_0
#define DOG_HIGH()          GPIO_SetBits(DOG_PORT, DOG_PIN)
#define DOG_LOW()           GPIO_ResetBits(DOG_PORT, DOG_PIN)


#define GLED_PORT           GPIOA
#define GLED_PIN            GPIO_Pin_15
#define    GLED_OFF()          GPIO_ResetBits(GLED_PORT, GLED_PIN)
#define    GLED_ON()           GPIO_SetBits(GLED_PORT, GLED_PIN)

#define RLED_PORT           GPIOA
#define RLED_PIN            GPIO_Pin_8
#define    LED_OFF()          GPIO_ResetBits(RLED_PORT, RLED_PIN)
#define    LED_ON()           GPIO_SetBits(RLED_PORT, RLED_PIN)


//Signal indicator
#define  	SIG_PORT   	GPIOC
#define 	SIG1_PIN 	GPIO_Pin_7
#define 	SIG2_PIN	GPIO_Pin_6
#define 	SIG3_PIN	GPIO_Pin_15

#define  NO_CSQ        GPIO_ResetBits(SIG_PORT, SIG1_PIN);GPIO_ResetBits(SIG_PORT, SIG2_PIN);GPIO_ResetBits(GPIOB, SIG3_PIN)
#define  LOW_CSQ     	GPIO_SetBits(SIG_PORT, SIG1_PIN);GPIO_ResetBits(SIG_PORT, SIG2_PIN);GPIO_ResetBits(GPIOB, SIG3_PIN)
#define  MEDIUM_CSQ 	GPIO_SetBits(SIG_PORT, SIG1_PIN);GPIO_SetBits(SIG_PORT, SIG2_PIN);GPIO_ResetBits(GPIOB, SIG3_PIN)
#define  HIGH_CSQ		GPIO_SetBits(SIG_PORT, SIG1_PIN);GPIO_SetBits(SIG_PORT, SIG2_PIN);GPIO_SetBits(GPIOB, SIG3_PIN)
extern void DisableUart(UART_COM_ENUM UartNum);
extern void InitUart(UART_COM_ENUM UartNum, int Baud);
extern void Init485Uart(int Baud);
extern void FeedDog(void);
extern void ResetCPU(void);
extern void HardWareInit(void);

#endif
