/****************************************Copyright (c)****************************************************
**                            
**                                      
**                                 
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               pipe.h
** Last modified Date:      2014-11-08
** Last Version:            1.0.0
** Descriptions:            用于不带系统的简易管道通信库函数
**                            管道最大数据块为255
**--------------------------------------------------------------------------------------------------------
** Created by:              Cuihongbin
** Created date:            2014-11-08
** Version:                 1.0.0
** Descriptions:            用于不带系统的简易管道通信库函数
**                            管道最大数据块为255
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#ifndef _PIPE_H_
#define    _PIPE_H_

char     pipeCreate(char **pMem, unsigned char PoolCnt, unsigned short Size, void **pCtl);
char    pipeDataWrite(void *pCtl, void *pBuf, unsigned short Len);
char    pipeDataRead(void *pCtl, void *pBuf, unsigned short Len);
void    pipeFlush(void *pCtl);
char    PipeDataValid(void *pCtrl);

#endif
