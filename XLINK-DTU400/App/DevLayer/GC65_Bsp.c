#include "gc65_bsp.h"
#include "uart.h"

void    GprsUartCmd(char *pCmd, unsigned short Len)
{    
    UartSendData(GPRSUart, pCmd, Len);
}


#include "stm32f10x.h"
//#define UART3_DMA_RX_CHL    DMA1_Channel3
//#define UART3_DMA_RX_TC     DMA1_FLAG_TC3 
//#define UART3_DMA_RX_ADDR   (USART3_BASE+0x0004)
//#define UART3_DMA_RX_IQR    DMA1_Channel3_IRQn

#define UART2_DMA_RX_CHL    DMA1_Channel6
#define UART2_DMA_RX_TC     DMA1_FLAG_TC6
#define UART2_DMA_RX_ADDR   (USART2_BASE+0x0004)
#define UART2_DMA_RX_IQR    DMA1_Channel6_IRQn

#define GPRS_UART_DMA_RX_CHL    UART2_DMA_RX_CHL    
#define GPRS_UART_DMA_RX_TC     UART2_DMA_RX_TC
#define GPRS_UART_DMA_RX_ADDR   UART2_DMA_RX_ADDR
#define GPRS_UART_DMA_RX_IQR    UART2_DMA_RX_IQR
#define GPRS_UART_DMA_RCC       RCC_AHBPeriph_DMA1
#define GPRS_UARTX              USART2

u8 DMAUart2Buf[512+10];


void    GprsUART_SetDMAReceive(u8 *pSrc, u32 DesLen)
{
    u32 RegVal = ((DMA_Channel_TypeDef* )GPRS_UART_DMA_RX_CHL)->CCR;

    USART_ITConfig(GPRS_UARTX, USART_IT_RXNE, DISABLE);             
    USART_ClearITPendingBit(GPRS_UARTX, USART_IT_RXNE);
    
    DMA_Cmd(GPRS_UART_DMA_RX_CHL, DISABLE);   //停止DMA
    DMA_ClearFlag(GPRS_UART_DMA_RX_TC);     
    
    ((DMA_Channel_TypeDef* )GPRS_UART_DMA_RX_CHL)->CMAR  = (uint32_t)pSrc;
    ((DMA_Channel_TypeDef* )GPRS_UART_DMA_RX_CHL)->CNDTR = (uint32_t)DesLen;
//    ((DMA_Channel_TypeDef* )GPRS_UART_DMA_RX_CHL)->CCR = RegVal & (~DMA_CCR1_DIR) | DMA_CCR1_EN;

//    DMA1_Channel4->CNDTR = sizeof(TxBuffer1) / sizeof(TxBuffer1[0]);//重设传输长度
    DMA_Cmd(GPRS_UART_DMA_RX_CHL, ENABLE);    //启动DMA
}


void    GPRSUartDMAInit(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;

    RCC_AHBPeriphClockCmd(GPRS_UART_DMA_RCC, ENABLE);

    DMA_DeInit(GPRS_UART_DMA_RX_CHL);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&GPRS_UARTX->DR);
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_PeripheralInc =DMA_PeripheralInc_Disable;//外设地址不自增
    DMA_InitStructure.DMA_MemoryInc =DMA_MemoryInc_Enable;//内存地址自增
    DMA_InitStructure.DMA_PeripheralDataSize =DMA_PeripheralDataSize_Byte;//外设数据单位为1字节
    DMA_InitStructure.DMA_MemoryDataSize =DMA_MemoryDataSize_Byte;//内存数据单位为1字节
    DMA_InitStructure.DMA_Mode =DMA_Mode_Normal; 
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;

    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_Init(GPRS_UART_DMA_RX_CHL, &DMA_InitStructure); 
    DMA_Cmd(GPRS_UART_DMA_RX_CHL, DISABLE);

    DMA_ClearFlag(GPRS_UART_DMA_RX_TC);
    DMA_ITConfig(GPRS_UART_DMA_RX_CHL, DMA_IT_TC, ENABLE);
    USART_DMACmd(GPRS_UARTX, USART_DMAReq_Rx, ENABLE);    

    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;       //抢占
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;              //从
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                                        
    NVIC_InitStructure.NVIC_IRQChannel = GPRS_UART_DMA_RX_IQR;      //GPRS DMA接收
    NVIC_Init(&NVIC_InitStructure);
}

void    GprsUartDMAReceive(u16 GetSize)
{
    GprsUART_SetDMAReceive(DMAUart2Buf, GetSize);
    GPRS_ENABLE_RECEIVE();
}

void    GetGprsUartDMABuf(u8 **ppBuf)
{
    *ppBuf = DMAUart2Buf;
}

#include "struct.h"
#include "gc65.h"
void    DMA1_Channel6_IRQHandler(void)
{    
    if(SET == DMA_GetFlagStatus(GPRS_UART_DMA_RX_TC)) {
        GPRS_DISABLE_RECEIVE();
        DMA_Cmd(GPRS_UART_DMA_RX_CHL, DISABLE);
        GprsCtrlInfo.Rlst2.Bits.FTP_GETOVER = TRUE;
        DMA_ClearFlag(GPRS_UART_DMA_RX_TC);
    }        
}

void    GprsDMAReceiveDisable(void)
{
    GPRS_ENABLE_RECEIVE();
    DMA_Cmd(GPRS_UART_DMA_RX_CHL, DISABLE);

    USART_ITConfig(GPRS_UARTX, USART_IT_RXNE, ENABLE);             
    USART_ClearITPendingBit(GPRS_UARTX, USART_IT_RXNE);
}

