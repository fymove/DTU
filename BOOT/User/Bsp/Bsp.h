#ifndef _BSP_H_
#define _BSP_H_

//#include "typedef.h"
//#include "stm32f10x.h"

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
#define UART3_DMA_EN        1


#define DebugUart          COM4


#define DO_JQ0_PORT         GPIOE
#define DO_JQ0_PIN          GPIO_Pin_4

#define DO_JQ1_PORT         GPIOE
#define DO_JQ1_PIN          GPIO_Pin_3

#define DO_JQ2_PORT         GPIOE
#define DO_JQ2_PIN          GPIO_Pin_2

#define DO_JQ3_PORT         GPIOE
#define DO_JQ3_PIN          GPIO_Pin_5

#define DO_JQ4_PORT         GPIOE
#define DO_JQ4_PIN          GPIO_Pin_6

#define DO_JQ5_PORT         GPIOD
#define DO_JQ5_PIN          GPIO_Pin_0

#define DO_JQ6_PORT         GPIOA
#define DO_JQ6_PIN          GPIO_Pin_12

#define DO_JQ7_PORT         GPIOA
#define DO_JQ7_PIN          GPIO_Pin_11

#define DO_JQ8_PORT         GPIOA
#define DO_JQ8_PIN          GPIO_Pin_8

#define GPRS_POWER_PORT     GPIOD          //GPRS??????  
#define GPRS_POWER_PIN      GPIO_Pin_13

#define	GPRS_PWRKEY_PORT    GPIOD          //GPRS???????
#define	GPRS_PWRKEY_PIN     GPIO_Pin_14


#define	ALM_LED_PORT        GPIOC
#define	ALM_LED_PIN         GPIO_Pin_3

#define RUN_LED_PORT        GPIOA
#define RUN_LED_PIN         GPIO_Pin_0

#define	RUN_LED_OFF()        GPIO_ResetBits(RUN_LED_PORT, RUN_LED_PIN)
#define	RUN_LED_ON()       GPIO_SetBits(RUN_LED_PORT, RUN_LED_PIN)

#define ALM_LED_OFF()        GPIO_ResetBits(ALM_LED_PORT, ALM_LED_PIN)
#define ALM_LED_ON()       GPIO_SetBits(ALM_LED_PORT, ALM_LED_PIN)

#define UART1_TXD_PORT      GPIOA
#define UART1_TXD_PIN       GPIO_Pin_9

#define UART1_RXD_PORT      GPIOA
#define UART1_RXD_PIN       GPIO_Pin_10

#define UART2_TXD_PORT      GPIOA
#define UART2_TXD_PIN       GPIO_Pin_2

#define UART2_RXD_PORT      GPIOA
#define UART2_RXD_PIN       GPIO_Pin_3

#define UART3_TXD_PORT      GPIOB
#define UART3_TXD_PIN       GPIO_Pin_10

#define UART3_RXD_PORT      GPIOB
#define UART3_RXD_PIN       GPIO_Pin_11

#define UART4_TXD_PORT      GPIOC
#define UART4_TXD_PIN       GPIO_Pin_10

#define UART4_RXD_PORT      GPIOC
#define UART4_RXD_PIN       GPIO_Pin_11

#define RS485_1_CTL_PORT    GPIOD
#define RS485_1_CTL_PIN     GPIO_Pin_1
#define RS485_1_RCV_STATUS  GPIO_SetBits(RS485_1_CTL_PORT, RS485_1_CTL_PIN)
#define RS485_1_SND_STATUS  GPIO_ResetBits(RS485_1_CTL_PORT, RS485_1_CTL_PIN)

#define GLED_PORT           GPIOA
#define GLED_PIN            GPIO_Pin_15
#define	GLED_OFF()          GPIO_ResetBits(GLED_PORT, GLED_PIN)
#define	GLED_ON()           GPIO_SetBits(GLED_PORT, GLED_PIN)

#define RLED_PORT           GPIOA
#define RLED_PIN            GPIO_Pin_8
#define	LED_OFF()          GPIO_ResetBits(RLED_PORT, RLED_PIN)
#define	LED_ON()           GPIO_SetBits(RLED_PORT, RLED_PIN)

#define DOG_PORT            GPIOA
#define DOG_PIN             GPIO_Pin_0
#define DOG_HIGH()          GPIO_SetBits(DOG_PORT, DOG_PIN)
#define DOG_LOW()           GPIO_ResetBits(DOG_PORT, DOG_PIN)

void    init_hw(void);
void    InitUart(UART_COM_ENUM UartNum, int baud);

void    watchdog_init(void);
void    DebugMsg(char *msg, ...);
void    wdg_feed(void);

void    LedRun(void);
#endif



