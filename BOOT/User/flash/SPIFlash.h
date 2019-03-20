/**************************Copyright (c)****************************
**                            
**                                      
**                                 
**
**--------------File Info-------------------------------------------
** File name:               SPIFlash.h
** Last modified Date:      2017-06-30
** Last Version:            0.9.0
** Descriptions:            SPI Flash驱动库函数头文件
**							
**------------------------------------------------------------------
** Created by:              chb
** Created date:            2017-06-30
** Version:                 0.9.0
** Descriptions:            SPI Flash驱动库函数头文件
**							
**------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*******************************************************************/
#ifndef _SPI_FLASH_H_
#define _SPI_FLASH_H_


/*******************************************************************
**  SPI Flash类型宏定义
*******************************************************************/
typedef enum {
    FLASH_MDL_UNKNOW = 0,                                           //  Flash类型不识别
    FLASH_SST25VF016,
    FLASH_SST25VF032,  
    FLASH_W25Q16,                                                   
    FLASH_W25Q32,                                                   
}FLASH_MDL_ENUM;


/*******************************************************************
** Function name:       SPIFlashInit  
** Descriptions:        SPI Flash初始化
** input parameters:    无
** output parameters:   无
** Returned value:      FLASH_MDL_ENUM      Flash类型
** Created Date:        2017-06-30
** Created by:          chb
**
** Modified by:
** Modified date:
*******************************************************************/
extern FLASH_MDL_ENUM    SPIFlashInit(void);


/*******************************************************************
** Function name:       SPIFlashRead  
** Descriptions:        SPI Flash读操作
** input parameters:    Addr    读数据起始地址
**                      pBuf    读取数据缓存
**                      RdLen   读取数据长度
** output parameters:   pBuf    读取数据缓存      
** Returned value:      无
** Created Date:        2017-06-30
** Created by:          chb
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    SPIFlashRead(u32 Addr, u8 *pBuf, u16 RdLen);


/*******************************************************************
** Function name:       SPIFlashWrite  
** Descriptions:        SPI Flash写操作
** input parameters:    Addr    写数据起始地址
**                      pBuf    写数据缓存
**                      RdLen   写数据长度
** output parameters:   无     
** Returned value:      无
** Created Date:        2017-06-30
** Created by:          chb
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    SPIFlashWrite(u32 Addr, u8 *pBuf, u16 WrLen);


/*******************************************************************
** Function name:       SPIFlashErase4K  
** Descriptions:        SPI Flash 4K擦除操作
** input parameters:    Addr    擦除起始地址
** output parameters:   无     
** Returned value:      无
** Created Date:        2017-06-30
** Created by:          chb
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    SPIFlashErase4K(u32 Addr);


/*******************************************************************
** Function name:       SPIFlashErase64K  
** Descriptions:        SPI Flash 64K擦除操作
** input parameters:    Addr    擦除起始地址
** output parameters:   无     
** Returned value:      无
** Created Date:        2017-06-30
** Created by:          chb
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    SPIFlashErase64K(u32 Addr);


/*******************************************************************
** Function name:       SPIFlashChipErase  
** Descriptions:        SPI Flash整片擦除操作
** input parameters:    无
** output parameters:   无     
** Returned value:      无
** Created Date:        2017-06-30
** Created by:          chb
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    SPIFlashChipErase(void);


/*******************************************************************
** Function name:       SPIFlashLibVersion  
** Descriptions:        获取SPI Flash库版本信息
** input parameters:    无
** output parameters:   无
** Returned value:      库版本信息字符串
** Created by:          chb
** Created Date:        2017-06-30
**
** Modified by:
** Modified date:
*******************************************************************/
extern char    *SPIFlashLibVersion(void);


#endif

