/**************************Copyright (c)****************************
**                            
**                                      
**                                 
**
**--------------File Info-------------------------------------------
** File name:               crc32.c
** Last modified Date:      2017-07-03
** Last Version:            0.9.0
** Descriptions:            crc32算法头文件
**                            
**------------------------------------------------------------------
** Created by:              chb
** Created date:            2017-07-03
** Version:                 0.9.0
** Descriptions:            crc32算法头文件
**                            
**------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*******************************************************************/
#ifndef _CRC32_H_
#define _CRC32_H_


/*******************************************************************
** Function name:       CRC32CalcReset  
** Descriptions:        crc32计算复位
** input parameters:    无
** output parameters:   无
** Returned value:      无
** Created by:          chb
** Created Date:        2017-07-03
**
** Modified by:
** Modified date:
*******************************************************************/
extern void    CRC32CalcReset(void);


/*******************************************************************
** Function name:       CRC32Calc  
** Descriptions:        计算crc32
** input parameters:    pBuf            待crc32计算的数据缓存
**                      Len             待crc32计算的数据大小
** output parameters:   u32             计算出的crc32值
** Returned value:      无
** Created by:          chb
** Created Date:        2017-07-03
**
** Modified by:
** Modified date:
*******************************************************************/
extern u32     CRC32Calc(u8 *pBuf, u16 Len);


#endif

