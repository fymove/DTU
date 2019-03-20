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
#include "string.h"
#include "stdlib.h"

#ifndef TRUE
#define    TRUE                1
#endif

#ifndef FALSE
#define    FALSE                0
#endif

#pragma pack(1)
typedef struct {
    char *pBuf;
//    unsigned short Len;
}PIPE_BUF_STRUCT;

typedef struct {
    struct {
        char Empty: 1;
        char Full: 1;
    }bits;

    unsigned char WriteIdx;
    unsigned char ReadIdx;
    unsigned char Cnt; 
    unsigned short Size;
    PIPE_BUF_STRUCT **pNode;
}PIPE_CTRL_STRUCT;
#pragma pack()

char     pipeCreate(char **pMem, unsigned char PipeCnt, unsigned short Size, void **pCtrl)
{
    unsigned char i;
    PIPE_CTRL_STRUCT **pCtl = (PIPE_CTRL_STRUCT **)pCtrl;

    if((NULL == pMem) || (0 == PipeCnt)) {
        return FALSE;
    }

    *pCtl = (PIPE_CTRL_STRUCT *)malloc(sizeof(PIPE_CTRL_STRUCT));
    if(NULL == *pCtl) {
        return FALSE;
    }

    (*pCtl)->pNode = (PIPE_BUF_STRUCT **)malloc(PipeCnt * sizeof(PIPE_BUF_STRUCT *));
    for(i=0; i<PipeCnt; i++) { 
        (*pCtl)->pNode[i] = (PIPE_BUF_STRUCT *)malloc(sizeof(PIPE_BUF_STRUCT)); 
        (*pCtl)->pNode[i]->pBuf = (char *)((int)pMem + i * Size); 
//        (*pCtl)->pNode[i]->Len = 0;
    }    

    (*pCtl)->bits.Empty = TRUE;
    (*pCtl)->bits.Full = FALSE;
    (*pCtl)->WriteIdx = 0;
    (*pCtl)->ReadIdx = 0;
    (*pCtl)->Cnt = PipeCnt;
    (*pCtl)->Size = Size;
    
    return TRUE;
}


char    pipeDataWrite(PIPE_CTRL_STRUCT *pCtrl, void *pBuf, unsigned short Len)
{
    PIPE_CTRL_STRUCT *pCtl = (PIPE_CTRL_STRUCT *)pCtrl;

    if((NULL == pCtrl) || (NULL == pBuf)) {
        return FALSE;
    }

    if(Len > pCtl->Size) {
        Len = pCtl->Size;
    }

    if(pCtl->bits.Full) {
        if(++pCtl->ReadIdx >= pCtl->Cnt) {
            pCtl->ReadIdx = 0;
        }
    }

    memcpy(pCtl->pNode[pCtl->WriteIdx]->pBuf, (char *)pBuf, Len);
//    pCtl->pNode[pCtl->WriteIdx]->Len = Len;
    if(++pCtl->WriteIdx >= pCtl->Cnt) {
        pCtl->WriteIdx = 0;
    }         

    if(pCtl->bits.Empty) {
        pCtl->bits.Empty = FALSE;
    }        

    if(pCtl->WriteIdx == pCtl->ReadIdx) {
        pCtl->bits.Full = TRUE;
    }  

    return TRUE;
}

char    pipeDataRead(PIPE_CTRL_STRUCT *pCtrl, void *pBuf, unsigned short Len)
{
    PIPE_CTRL_STRUCT *pCtl = (PIPE_CTRL_STRUCT *)pCtrl;

    if((NULL == pCtrl) || (NULL == pBuf)  || (pCtl->bits.Empty)) {
        return FALSE;
    }

    if(Len > pCtl->Size) {
        Len = pCtl->Size;
    }

    memcpy((char *)pBuf, pCtl->pNode[pCtl->ReadIdx]->pBuf, Len);
//    *pLen = pCtl->pNode[pCtl->ReadIdx]->Len; 
    if(++pCtl->ReadIdx >= pCtl->Cnt) {
        pCtl->ReadIdx = 0;
    }

    if(pCtl->bits.Full) {
       pCtl->bits.Full = FALSE; 
    }    
    
    if(pCtl->ReadIdx == pCtl->WriteIdx) {
        pCtl->bits.Empty = TRUE;        
    }

    return TRUE;
}

void    pipeFlush(void *pCtrl)
{       
    PIPE_CTRL_STRUCT *pCtl = (PIPE_CTRL_STRUCT *)pCtrl;

    if(pCtl) {
        pCtl->ReadIdx = 0;
        pCtl->WriteIdx = 0;
        pCtl->bits.Empty = TRUE;
        pCtl->bits.Full = FALSE;
    }
}

char    PipeDataValid(void *pCtrl)
{
    char ret = FALSE;

    if(!((PIPE_CTRL_STRUCT *)pCtrl)->bits.Empty) {
        ret = TRUE;
    }

    return ret;
}

