
#include "stm32f10x.h"
#include "bsp.h"
#include "timer.h"

#include "string.h"
#include "stdio.h"
#include <stdarg.h>

#if 1
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
   
    //  DO
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;	
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    
    GPIO_InitStructure.GPIO_Pin   = DOG_PIN;
    GPIO_Init(DOG_PORT, &GPIO_InitStructure);
    
//    GPIO_InitStructure.GPIO_Pin   = GLED_PIN;
//    GPIO_Init(GLED_PORT, &GPIO_InitStructure);  
//    
//    GPIO_InitStructure.GPIO_Pin   = RLED_PIN;
//    GPIO_Init(RLED_PORT, &GPIO_InitStructure);
//    GLED_ON();
//    LED_ON();
    
//    GPIO_ResetBits(DO_JQ1_PORT, DO_JQ1_PIN);
//    GPIO_InitStructure.GPIO_Pin   = DO_JQ2_PIN;
//    GPIO_Init(DO_JQ2_PORT, &GPIO_InitStructure);
//    GPIO_ResetBits(DO_JQ2_PORT, DO_JQ2_PIN);
//    GPIO_InitStructure.GPIO_Pin   = DO_JQ3_PIN;
//    GPIO_Init(DO_JQ3_PORT, &GPIO_InitStructure);	
//    GPIO_ResetBits(DO_JQ3_PORT, DO_JQ3_PIN);
//    GPIO_InitStructure.GPIO_Pin   = DO_JQ4_PIN;
//    GPIO_Init(DO_JQ4_PORT, &GPIO_InitStructure);
//    GPIO_ResetBits(DO_JQ4_PORT, DO_JQ4_PIN);
//    GPIO_InitStructure.GPIO_Pin   = DO_JQ5_PIN;
//    GPIO_Init(DO_JQ5_PORT, &GPIO_InitStructure);                //  ?????RS485_2_CTRL
//    GPIO_ResetBits(DO_JQ5_PORT, DO_JQ5_PIN);
//    GPIO_InitStructure.GPIO_Pin   = DO_JQ6_PIN;
//    GPIO_Init(DO_JQ6_PORT, &GPIO_InitStructure);               
//    GPIO_ResetBits(DO_JQ6_PORT, DO_JQ6_PIN);
//    GPIO_InitStructure.GPIO_Pin   = DO_JQ7_PIN;
//    GPIO_Init(DO_JQ7_PORT, &GPIO_InitStructure);                
//    GPIO_ResetBits(DO_JQ7_PORT, DO_JQ7_PIN);
//    GPIO_InitStructure.GPIO_Pin   = DO_JQ8_PIN;
//    GPIO_Init(DO_JQ8_PORT, &GPIO_InitStructure);                
//    GPIO_ResetBits(DO_JQ8_PORT, DO_JQ8_PIN);
    
    //  Other
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Pin  = GPRS_PWRKEY_PIN;
//    GPIO_Init(GPRS_PWRKEY_PORT, &GPIO_InitStructure);    
//    GPIO_InitStructure.GPIO_Pin  = GPRS_POWER_PIN;
//    GPIO_Init(GPRS_POWER_PORT, &GPIO_InitStructure);
//    GPIO_SetBits(GPRS_POWER_PORT, GPRS_POWER_PIN);
       
//    GPIO_InitStructure.GPIO_Pin   = ALM_LED_PIN;
//    GPIO_Init(ALM_LED_PORT, &GPIO_InitStructure);	
//    ALM_LED_OFF();
//    GPIO_InitStructure.GPIO_Pin  = RUN_LED_PIN;
//    GPIO_Init(RUN_LED_PORT, &GPIO_InitStructure);
//    RUN_LED_OFF();   
//     
//    GPIO_InitStructure.GPIO_Pin  = RS485_1_CTL_PIN;
//    GPIO_Init(RS485_1_CTL_PORT, &GPIO_InitStructure);	
}

#endif

static void systick_init(void) 
{ 
    RCC_ClocksTypeDef rcc_clocks; 
    RCC_GetClocksFreq(&rcc_clocks);        
    SysTick_Config(rcc_clocks.HCLK_Frequency / 1000);  
    NVIC_SetPriority(SysTick_IRQn, 15);
}
#if 0
void    InitUart(UART_COM_ENUM UartNum, int Baud)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    
    USART_InitStructure.USART_BaudRate = Baud;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;  
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                
    USART_InitStructure.USART_Parity = USART_Parity_No;                   
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   
            
    switch(UartNum)
    {
        case COM1:   
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
        
            USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
            
            GPIO_InitStructure.GPIO_Pin = UART1_TXD_PIN;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(UART1_TXD_PORT, &GPIO_InitStructure);
            GPIO_InitStructure.GPIO_Pin = UART1_RXD_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(UART1_RXD_PORT, &GPIO_InitStructure);

            USART_Init(USART1, &USART_InitStructure);         
            USART_ClearITPendingBit(USART1, USART_IT_RXNE);
            USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); 
            USART_Cmd(USART1, ENABLE);
            break;

        case COM2:        
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

            USART_ITConfig(USART2, USART_IT_RXNE, DISABLE); 
            
            GPIO_InitStructure.GPIO_Pin = UART2_TXD_PIN;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(UART2_TXD_PORT, &GPIO_InitStructure);            
            GPIO_InitStructure.GPIO_Pin = UART2_RXD_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(UART2_RXD_PORT, &GPIO_InitStructure);
                      
            USART_Init(USART2, &USART_InitStructure);            
            USART_ClearITPendingBit(USART2, USART_IT_RXNE);
            USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);             
            USART_Cmd(USART2, ENABLE);
            break;

        case COM3:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
        
            USART_ITConfig(USART3, USART_IT_RXNE, DISABLE); 
            
            GPIO_InitStructure.GPIO_Pin = UART3_TXD_PIN;
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
            GPIO_Init(UART3_TXD_PORT, &GPIO_InitStructure);

            GPIO_InitStructure.GPIO_Pin = UART3_RXD_PIN;
            GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
            GPIO_Init(UART3_RXD_PORT, &GPIO_InitStructure);
            USART_Init(USART3, &USART_InitStructure);            
            
            USART_ClearITPendingBit(USART3, USART_IT_RXNE);
            USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
            USART_Cmd(USART3, ENABLE);
            break;
        case COM4:
            USART_ITConfig(UART4, USART_IT_RXNE, DISABLE);
                        
            GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
            GPIO_InitStructure.GPIO_Pin   = UART4_TXD_PIN;
            GPIO_Init(UART4_TXD_PORT, &GPIO_InitStructure);            
            GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
            GPIO_InitStructure.GPIO_Pin   = UART4_RXD_PIN;
            GPIO_Init(UART4_RXD_PORT, &GPIO_InitStructure); 
            USART_Init(UART4, &USART_InitStructure);
        
            USART_Cmd(UART4, ENABLE);    
        default:
            break;
    }
}
#endif

void IWDG_init(void)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(IWDG_Prescaler_32);  
    IWDG_SetReload(1250 * 1.5);
    IWDG_ReloadCounter();
    IWDG_Enable();

    DBGMCU_Config(DBGMCU_IWDG_STOP, ENABLE);
}


/******************************************************************************
** 函数名称:
** 功能描述:
** 输　入: 无
** 输  出: 无
** 全局变量:
** 调用模块:
** 说明：
** 注意：
******************************************************************************/
void init_hw(void)
{
    systick_init();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA
                           | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC
                           | RCC_APB2Periph_AFIO , ENABLE);


    RCC_APB1PeriphClockCmd( RCC_APB1Periph_UART4, ENABLE);

    GPIO_Config();
//    InitUart(DebugUart,  115200); 
    IWDG_init();
}

void    wdg_feed(void)
{
    static char WdFlag = 0;
    IWDG_ReloadCounter();
    WdFlag ? DOG_HIGH() : DOG_LOW();
    WdFlag = !WdFlag;
}
#if 0
void    UartSendData(UART_COM_ENUM UartNum, char *pBuf, int Len)
{
    if((0 == pBuf) || (0 == Len)) {
        return;
    }
    
    switch(UartNum) {
        case COM1:
            while(Len--) {
                while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
                USART_SendData(USART1,*pBuf++);
            }
            break;

        case COM2:		
            while(Len--) {
                while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
                USART_SendData(USART2,*pBuf++);
            }
            break;

        case COM3:		
            while(Len--) {
                while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET){}
                USART_SendData(USART3, *pBuf++);
            }
            break;
        case COM4:	      
            while(Len--) {
                while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET){}
                USART_SendData(UART4, *pBuf++);
            }         
            break;       
        default:
            break;
    }
}
#endif
//#define DebugChgToSnd() RS485_1_SND_STATUS;
//#define DebugChgToRcv() RS485_1_RCV_STATUS;
//void    DebugMsg(char *msg, ...)
//{    
//    va_list argp; 
//    char MsgStr[60];
//    
//    va_start(argp, msg);
//    vsnprintf(MsgStr, 50, msg, argp);
//    va_end(argp);   
//       
//    DebugChgToSnd();
//    UartSendData(DebugUart, MsgStr, strlen(MsgStr));
//    RS485SndDly();
//    DebugChgToRcv();  
//}


