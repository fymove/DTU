/**************************Copyright (c)****************************
**                            
**                                      
**                                 
**
**--------------File Info-------------------------------------------
** File name:               SPIFlashUsr.h
** Last modified Date:      2017-06-30
** Last Version:            0.9.0
** Descriptions:            SPI Flash驱动库用户接口函数头文件
**							
**------------------------------------------------------------------
** Created by:              chb
** Created date:            2017-06-30
** Version:                 0.9.0
** Descriptions:            兼容ucoss
**							
**------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*******************************************************************/
#ifndef _SPI_FLASH_USR_H_
#define _SPI_FLASH_USR_H_


/*******************************************************************
** Function name:       FlashLockCreate  
** Descriptions:        操作锁初始化
** input parameters:    无
** output parameters:   无
** Returned value:      无
** Created by:          chb
** Created Date:        2017-06-30
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    FlashLockCreate(void);


/*******************************************************************
** Function name:       FlashLockPend  
** Descriptions:        操作锁等待
** input parameters:    无
** output parameters:   无
** Returned value:      无
** Created by:          chb
** Created Date:        2017-06-30
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    FlashLockPend(void);


/*******************************************************************
** Function name:       FlashLockPost  
** Descriptions:        操作锁释放
** input parameters:    无
** output parameters:   无
** Returned value:      无
** Created by:          chb
** Created Date:        2017-06-30
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    FlashLockPost(void);


#endif

