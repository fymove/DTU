#define _InUart

#include "uart.h"
#include "typedef.h"
#include "stm32f10x_usart.h" 
#include "includes.h"

void    UartIntSendData(UART_COM_ENUM UartNum, char *pBuf, short Len)
{   
    switch(UartNum) {
        case COM1:
#if UART1_DMA_EN
            UartSendData(UartNum, pBuf, Len);
#else
            UartSendData(UartNum, pBuf, 1); 
#endif                        
            break;
            
        case COM2:        
#if UART2_DMA_EN
            UartSendData(UartNum, pBuf, Len);
#else
            UartSendData(UartNum, pBuf, 1); 
#endif 
            break;

        case COM3:    
#if UART3_DMA_EN
            UartSendData(UartNum, pBuf, Len);
#else
            UartSendData(UartNum, pBuf, 1); 
#endif
            break;
            
        case COM4:            
            USART_SendData(UART4, *pBuf);
            break;   
            
        case COM5:            
            USART_SendData(UART5, *pBuf);
            break;     

        default:
            break;
    }
}

#if UART3_DMA_EN
//static char DMAUart3Buf[50];
#endif
#if UART2_DMA_EN
static char DMAUart2Buf[MAX_GPRS_BUF_SIZE+30];
#endif
#if UART1_DMA_EN
//static char DMAUart1Buf[VFD_SND_BUF_SIZE];
#endif
void    UartSendData(UART_COM_ENUM UartNum, char *pBuf, int Len)
{
    if((NULL == pBuf) || (0 == Len)) {
        return;
    }
    
    switch(UartNum) {
        case COM1:
#if UART1_DMA_EN
            memcpy(DMAUart1Buf, pBuf, Len);
            ((DMA_Channel_TypeDef* )UART1_DMA_TX_CHL)->CMAR  = (uint32_t)DMAUart1Buf;
            ((DMA_Channel_TypeDef* )UART1_DMA_TX_CHL)->CNDTR = (uint32_t)Len;
            ((DMA_Channel_TypeDef* )UART1_DMA_TX_CHL)->CCR |= DMA_CCR1_EN;
#else
            while(Len--) {
                while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
                USART_SendData(USART1,*pBuf++);
                if(Len && (0 == (Len % 300))) {
                    FeedDog();
                }
            }
#endif            
            break;

        case COM2:        
#if UART2_DMA_EN      
            memcpy(DMAUart2Buf, pBuf, Len);     
            ((DMA_Channel_TypeDef* )UART2_DMA_TX_CHL)->CMAR  = (uint32_t)DMAUart2Buf;
            ((DMA_Channel_TypeDef* )UART2_DMA_TX_CHL)->CNDTR = (uint32_t)Len;
            ((DMA_Channel_TypeDef* )UART2_DMA_TX_CHL)->CCR |= DMA_CCR1_EN;
#else
            while(Len--) {
                while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET){}
                USART_SendData(USART2,*pBuf++);
            }
#endif            
            break;

        case COM3:        
#if UART3_DMA_EN
            memcpy(DMAUart3Buf, pBuf, Len);     
            ((DMA_Channel_TypeDef* )UART3_DMA_TX_CHL)->CMAR  = (uint32_t)DMAUart3Buf;
            ((DMA_Channel_TypeDef* )UART3_DMA_TX_CHL)->CNDTR = (uint32_t)Len;
            ((DMA_Channel_TypeDef* )UART3_DMA_TX_CHL)->CCR |= DMA_CCR1_EN;
#else        
            while(Len--) {
                while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET){}
                USART_SendData(USART3, *pBuf++);
            }
#endif            
            break;
            
        case COM4:    
#if UART4_DMA_EN
            ((DMA_Channel_TypeDef* )UART4_DMA_TX_CHL)->CMAR  = (uint32_t)pBuf;
            ((DMA_Channel_TypeDef* )UART4_DMA_TX_CHL)->CNDTR = (uint32_t)Len;
            ((DMA_Channel_TypeDef* )UART4_DMA_TX_CHL)->CCR |= DMA_CCR1_EN;
#else         
            while(Len--) {
                while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET){}
                USART_SendData(UART4, *pBuf++);
            }
#endif            
            break;   
            
        case COM5:            
            while(Len--) {
                while(USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET){}
                USART_SendData(UART5, *pBuf++);
            }
            break;     

        default:
            break;
    }
}


char    UartFirstChar(UART_TIMER *pUrtTim)
{
    char ret = FALSE;
    
    if(FALSE == pUrtTim->Flag) {
        pUrtTim->Flag = TRUE;
        ret = TRUE;        
    } 
    
    pUrtTim->Timer = 0; 
    return ret;
}

char    UartTimerOver(UART_TIMER *pUrtTim)
{
    if(pUrtTim->Flag) {
        if(++pUrtTim->Timer >= 10) {
            pUrtTim->Flag  = FALSE;
            pUrtTim->Timer = 0;
            return TRUE;
        }
    }

    return FALSE;
}

