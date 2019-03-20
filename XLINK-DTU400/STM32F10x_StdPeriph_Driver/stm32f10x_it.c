/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "includes.h"


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */

extern TIME_FLAG_UNION TimeFlag;

void    UartRcvTimeOut(void)
{   
    if(UartTimerOver(&UartTest.Uart1)) {
        UartTest.Buf[UartTest.Len] = 0;
        UartTest.Rcv.Bits.RS485_0 = TRUE;
        DebugUartRcvStat = FALSE;
    }    
}

void SysTick_Handler(void)
{   
    static u16 Nms = 0;

	SysTime_Updata(); //系统实时时间
	
    if(++Nms >= 500) {
        Nms = 0;
        TimeFlag.Bits.N500ms = TRUE;
        TimeFlag.Bits.N50ms  = TRUE;
        TimeFlag.Bits.N20ms  = TRUE;
        TimeFlag.Bits.N2ms  = TRUE;
    } else if(0 == (Nms % 50)) {
        TimeFlag.Bits.N50ms  = TRUE;
        TimeFlag.Bits.N20ms  = TRUE;
        TimeFlag.Bits.N2ms  = TRUE;
    } else if(0 == (Nms % 20)) {
        TimeFlag.Bits.N20ms  = TRUE;
        TimeFlag.Bits.N2ms  = TRUE;
    } else if(0 == (Nms % 2)) {
        TimeFlag.Bits.N2ms  = TRUE;
    }
    
//#if UART1_DMA_EN
//    if(RS4850RcvChg.Bits.Flag) {
//        if(++RS4850RcvChg.Bits.Timer >= 5) {
//            RS4850RcvChg.Val = 0;
//            RS4850Modbus.Stat.Bits.SndFlg = FALSE;
//            RS4850Modbus.Stat.Bits.RcvFlg = TRUE;
//            RS4850Modbus.RcvCnt = 0;
//            RS4850Modbus.RcvTimer = 0;
//            RS4850Modbus.pChgToRcv();
//        }
//    }
//#endif   

    if(CfgDelay.Bits.Flag || GbDtuEnterCfg || AppDebug.Bits.Enable) {        
        UartRcvTimeOut();    
    } else {
#if RS485_SEND_DELAY
        ModbusDelayToRcv(&RS4850Modbus, 1);
#endif
    }

    GbEventFlag = TRUE;
	GbMeterEventFlag = TRUE;
	GbMeter2EventFlag = TRUE;
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles USART1 global interrupt request.
  * @param  None
  * @retval None
  */
  
void    USART1_IRQHandler(void)
{
	char RcvChar;
	  
	if (SET == USART_GetITStatus(USART1, USART_IT_RXNE)) 
	{
        USART_ClearITPendingBit(USART1, USART_FLAG_RXNE);           /* Clear the USART Receive interrupt                   */	
        RcvChar = USART_ReceiveData(USART1);
		
        if(CfgDelay.Bits.Flag || GbDtuEnterCfg || AppDebug.Bits.Enable) 
		{
            if(UartFirstChar(&UartTest.Uart1)) 
			{
                UartTest.Len = 0;
                UartTest.Buf[UartTest.Len++] = RcvChar;
            } 
			else 
			{
                if(UartTest.Len < UART_TEST_BUF_SIZE) 
				{
                    UartTest.Buf[UartTest.Len++] = RcvChar;
                }
            }
            
            DebugUartRcvStat = TRUE;
        } 
		else 
		{
            ModbusUartIsr(&RS4850Modbus, RcvChar);
        }         
	}                   	  

    if (SET == USART_GetFlagStatus(USART1, USART_FLAG_TC)) 
	{
	    USART_ClearFlag(USART1, USART_FLAG_TC);
	    if(CfgDelay.Bits.Flag || GbDtuEnterCfg || AppDebug.Bits.Enable) 
		{
	        if(GbCfgCmd) 
			{
                ModbusSendNextChar(&RS4850Modbus);
            }
	    } 
		else 
		{
#if UART1_DMA_EN
            USART_ITConfig(USART1, USART_IT_TC, DISABLE);               //  关闭TC中断
            RS4850RcvChg.Bits.Timer = 0;
            RS4850RcvChg.Bits.Flag = TRUE;
#else
            ModbusSendNextChar(&RS4850Modbus);
#endif        
	    }
	} 
	
	if(SET == USART_GetFlagStatus(USART1, USART_FLAG_ORE)) 
	{
		USART_ClearFlag(USART1, USART_FLAG_ORE); 
		RcvChar = USART_ReceiveData(USART1);
	}

	if(SET == USART_GetFlagStatus(USART1, USART_FLAG_IDLE)) 
	{
		USART_ClearFlag(USART1, USART_FLAG_IDLE); 
		RcvChar = USART_ReceiveData(USART1);
	}
}

#if UART1_DMA_EN
void    DMA1_Channel4_IRQHandler(void)
{

    if(SET == DMA_GetFlagStatus(UART1_DMA_TX_TC)) {
        DMA_ClearFlag(UART1_DMA_TX_TC);
        DMA_Cmd(UART1_DMA_TX_CHL, DISABLE);
        USART_ITConfig(USART1, USART_IT_TC, ENABLE);                //  开启TC中断
    }
}
#endif


void USART2_IRQHandler(void)
{
	char RcvChar;
    
	if (SET == USART_GetITStatus(USART2, USART_IT_RXNE)) {
        USART_ClearITPendingBit(USART2, USART_FLAG_RXNE);           /* Clear the USART Receive interrupt                   */		  
        RcvChar = USART_ReceiveData(USART2);
        GprsUartIsr(RcvChar);
	}

    if(SET == USART_GetFlagStatus(USART2, USART_FLAG_TC)) {
	    USART_ClearFlag(USART2, USART_FLAG_TC);
#if UART2_DMA_EN
        USART_ITConfig(USART2, USART_IT_TC, DISABLE);               //  关闭TC中断
#endif
	} 
	
	if(SET == USART_GetFlagStatus(USART2, USART_FLAG_ORE)) {
		USART_ClearFlag(USART2, USART_FLAG_ORE); 
		RcvChar = USART_ReceiveData(USART2);
	}

	if(SET == USART_GetFlagStatus(USART2, USART_FLAG_IDLE)) {
		USART_ClearFlag(USART2, USART_FLAG_IDLE); 
		RcvChar = USART_ReceiveData(USART2);
	}
}

#if UART2_DMA_EN
void    DMA1_Channel7_IRQHandler(void)
{
    if(SET == DMA_GetFlagStatus(UART2_DMA_TX_TC)) {
        DMA_ClearFlag(UART2_DMA_TX_TC);
        DMA_Cmd(UART2_DMA_TX_CHL, DISABLE);
        USART_ITConfig(USART2, USART_IT_TC, ENABLE);                //  开启TC中断
    }
}
#endif
 
void    USART3_IRQHandler(void)
{
	char RcvChar;
	  
	if (SET == USART_GetITStatus(USART3, USART_IT_RXNE)) 
	{
        USART_ClearITPendingBit(USART3, USART_FLAG_RXNE);           /* Clear the USART Receive interrupt                   */	
        RcvChar = USART_ReceiveData(USART3);

        ModbusUartIsr(&RS4851Modbus, RcvChar);               
	}                   	  

    if (SET == USART_GetFlagStatus(USART3, USART_FLAG_TC)) 
	{
	    USART_ClearFlag(USART3, USART_FLAG_TC);	    
        ModbusSendNextChar(&RS4851Modbus);      
	} 
	
	if(SET == USART_GetFlagStatus(USART3, USART_FLAG_ORE)) 
	{
		USART_ClearFlag(USART3, USART_FLAG_ORE); 
		RcvChar = USART_ReceiveData(USART3);
	}

	if(SET == USART_GetFlagStatus(USART3, USART_FLAG_IDLE)) 
	{
		USART_ClearFlag(USART3, USART_FLAG_IDLE); 
		RcvChar = USART_ReceiveData(USART3);
	}
}




void    UART4_IRQHandler(void)
{
	char RcvChar;
	  
	if (SET == USART_GetITStatus(UART4, USART_IT_RXNE)) 
	{
        USART_ClearITPendingBit(UART4, USART_FLAG_RXNE);           /* Clear the USART Receive interrupt                   */	
        RcvChar = USART_ReceiveData(UART4);

        ModbusUartIsr(&RS4852Modbus, RcvChar);               
	}                   	  

    if (SET == USART_GetFlagStatus(UART4, USART_FLAG_TC)) 
	{
	    USART_ClearFlag(UART4, USART_FLAG_TC);	    
        ModbusSendNextChar(&RS4852Modbus);      
	} 
	
	if(SET == USART_GetFlagStatus(UART4, USART_FLAG_ORE)) 
	{
		USART_ClearFlag(UART4, USART_FLAG_ORE); 
		RcvChar = USART_ReceiveData(UART4);
	}

	if(SET == USART_GetFlagStatus(UART4, USART_FLAG_IDLE)) 
	{
		USART_ClearFlag(UART4, USART_FLAG_IDLE); 
		RcvChar = USART_ReceiveData(UART4);
	}
}



void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CanRxMsg  RxMsg;

	if(CAN_MessagePending(CAN1, CAN_FIFO0) != 0)
	{
		CAN_Receive(CAN1,CAN_FIFO0, &RxMsg);//释放了此消息所占用的邮箱
		CanBus_ISR_Rx(&RxMsg);
		
	//	CanBus_ISR_Rx(&RxMsg);//触发此资源
	}

	CAN1->RF0R |= 0x00000018;//清除中断标志位
}

void USB_HP_CAN_TX_IRQHandler(void)
{
	CAN1->TSR |= 0x000F0F0F;

	//CAN_ITConfig(CAN_IT_TME, DISABLE);
//	OS_awakenTask(CAN_SEND_TASK_ID);
	
}
void CAN_RX1_IRQHandler(void)
{
	CAN1->RF1R |= 0x00000018;
	CAN1->IER  &= 0xFFFFFF0F;
}


#if 0
void    USART3_IRQHandler(void)
{
	char RcvChar;
 
	if (SET == USART_GetITStatus(USART3, USART_IT_RXNE)) {
        USART_ClearITPendingBit(USART3, USART_FLAG_RXNE);               /* Clear the USART Receive interrupt                   */		  
        RcvChar = USART_ReceiveData(USART3);
        GprsUartIsr(RcvChar);
	}
    
    if(SET == USART_GetFlagStatus(USART3, USART_FLAG_TC)) {
	    USART_ClearFlag(USART3, USART_FLAG_TC);
#if UART3_DMA_EN
        USART_ITConfig(USART3, USART_IT_TC, DISABLE);               //  关闭TC中断
#endif        
	} 

	
	if(SET == USART_GetFlagStatus(USART3, USART_FLAG_ORE)) {
		USART_ClearFlag(USART3, USART_FLAG_ORE); 
		RcvChar = USART_ReceiveData(USART3);
	}

	if(SET == USART_GetFlagStatus(USART3, USART_FLAG_IDLE)) {
		USART_ClearFlag(USART3, USART_FLAG_IDLE); 
		RcvChar = USART_ReceiveData(USART3);
	}
}


#if UART3_DMA_EN
void    DMA1_Channel2_IRQHandler(void)
{
    
    if(SET == DMA_GetFlagStatus(UART3_DMA_TX_TC)) {
        DMA_ClearFlag(UART3_DMA_TX_TC);
        DMA_Cmd(UART3_DMA_TX_CHL, DISABLE);
        USART_ITConfig(USART3, USART_IT_TC, ENABLE);                //  开启TC中断
    }        
}
#endif




#endif

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
