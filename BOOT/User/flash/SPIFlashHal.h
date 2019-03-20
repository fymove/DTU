/**************************Copyright (c)****************************
**                            
**                                      
**                                 
**
**--------------File Info-------------------------------------------
** File name:               SPIFlashHal.c
** Last modified Date:      2017-06-30
** Last Version:            0.9.0
** Descriptions:            SPI Flash硬件相关接口函数头文件
**							
**------------------------------------------------------------------
** Created by:              chb
** Created date:            2017-06-30
** Version:                 0.9.0
** Descriptions:            SPI Flash硬件相关接口函数头文件
**							
**------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*******************************************************************/
#ifndef _SPI_FLASH_HAL_H_
#define _SPI_FLASH_HAL_H_


/*******************************************************************
** Function name:       FlashHalInit  
** Descriptions:        SPI硬件接口初始化
** input parameters:    无
** output parameters:   无     
** Returned value:      无
** Created Date:        2017-06-30
** Created by:          chb
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    FlashHalInit(void);


/*******************************************************************
** Function name:       FlashSPISend  
** Descriptions:        SPI字节数据发送
** input parameters:    data            待发送的字节数据
** output parameters:   无     
** Returned value:      无
** Created Date:        2017-06-30
** Created by:          chb
**
** Modified by:
** Modified date:
*******************************************************************/
extern u8      FlashSPISend(u8 data);


/*******************************************************************
** Function name:       FlashSelect  
** Descriptions:        SPI片选控制
** input parameters:    bSet            SPI片选控制标识
** output parameters:   无     
** Returned value:      无
** Created Date:        2017-06-30
** Created by:          chb
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    FlashSelect(u8 bSet);

#endif


