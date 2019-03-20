/**************************Copyright (c)****************************
**                            
**                                      
**                                 
**
**--------------File Info-------------------------------------------
** File name:               ST Flash.h
** Last modified Date:      2017-06-30
** Last Version:            0.9.0
** Descriptions:            ST MCU内部Flash驱动库函数头文件
**							
**------------------------------------------------------------------
** Created by:              chb
** Created date:            2017-06-30
** Version:                 0.9.0
** Descriptions:            ST MCU内部Flash驱动库函数头文件
**							
**------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*******************************************************************/
#ifndef _STM_FLASH_H_
#define _STM_FLASH_H_


/*******************************************************************
** Function name:       STFlashRead  
** Descriptions:        ST MCU内部flash读操作
** input parameters:    Addr        读数据起始地址
**                      pBuf        读数据缓存
**                      Len         读数据长度
** output parameters:   pBuf        读数据缓存
** Returned value:      无
** Created by:          chb
** Created Date:        2017-06-30
**
** Modified by:
** Modified date:
*******************************************************************/
void	STFlashRead(u32 Addr, u8 *pBuf, u16 Len);


/*******************************************************************
** Function name:       STFlashWrite  
** Descriptions:        ST MCU内部flash写操作
** input parameters:    Addr        写数据起始地址
**                      pBuf        写数据缓存
**                      Len         写数据长度
** output parameters:   无
** Returned value:      TRUE        成功
**                      FALSE       失败
** Created by:          chb
** Created Date:        2017-06-30
**
** Modified by:
** Modified date:
*******************************************************************/
u8  STFlashWrite(u32 Addr, u8 *pBuf, u16 Len);


/*******************************************************************
** Function name:       STFlashErase  
** Descriptions:        ST MCU内部flash擦除操作
** input parameters:    Addr        擦除起始地址
** output parameters:   无
** Returned value:      TRUE        成功
**                      FALSE       失败
** Created by:          chb
** Created Date:        2017-06-30
**
** Modified by:
** Modified date:
*******************************************************************/
u8  STFlashErase(u32 Addr);


#endif

