#define    _InDebug
#include "app_debug.h"
#include "Includes.h"

#if USE_UART_DEBUG_INFO
static char DbgMsgstr[400] = {0};
static va_list argp; 
#endif

void    RS485SndDly(void)
{
    short i;

#if 0    
    for(i=0; i<2000; i++);                                          //  115200波特率延时
#else    
    for(i=0; i<20000; i++);                                         //  9600波特率延时
#endif    
}


void    DisableAllDebug(void)
{
    AppDebug.Flag = FALSE;
}

void    AppDebugInit(void)
{
#if USE_UART_DEBUG_INFO     
    AppDebug.Bits.Enable = FALSE;
//    AppDebug.Bits.Vfd = TRUE;
   
    AppDebug.Bits.ATCmd  = TRUE;
    AppDebug.Bits.GprsRcvData = TRUE;
    AppDebug.Bits.GprsSndData = TRUE;
//    AppDebug.Bits.TaskStack = TRUE;

//    if(NULL == pSemDebug) {
//        pSemDebug = OSSemCreate(1);
//        if(NULL == pSemDebug) {
//            Debug("[DEBUD] Create pSemDebug Fail\r\n");
//            while(1);
//        }
//    }
#endif    
}

#if USE_UART_DEBUG_INFO
#define DebugChgToSnd() RS485_0_SND_STATUS;
#define DebugChgToRcv() RS485_0_RCV_STATUS;
 void    Debug(char* pMsg)
{
    while(DebugUartRcvStat) {
        RS485SndDly();
        FeedDog();
    }     
    DebugChgToSnd();
    UartSendData(DebugUart, pMsg, strlen(pMsg));
    RS485SndDly();
    DebugChgToRcv();  
}

static  void DebugWithLen(char *pMsg,      int len)
{
	    while(DebugUartRcvStat) {
        RS485SndDly();
        FeedDog();
    }     
    DebugChgToSnd();
    UartSendData(DebugUart, pMsg, len);
    RS485SndDly();
    DebugChgToRcv();  
}
#endif


void 	DebugStrMsg(char *pHead, char * pStr, short len)
{
	#if USE_UART_DEBUG_INFO
   // short i;
	//u8 num, left;
	//char strData[1];

    
    if(AppDebug.Flag) {         
//        OSSemPend(pSemDebug, 0, &err);     
        Debug(pHead);
		DebugWithLen(pStr, len);
	#if 0
        for(i=1; i<=len; i++) {   
         	strData[0] = *pStr++;
            Debug(strData);
            
            if(0 == i % 60) {
                Debug("\r\n");
                FeedDog();
            }
        }
	#endif
        Debug("\r\n");
//        OSSemPost(pSemDebug);
    }   
#endif    
}
void    DebugHexMsg(char *pHead, char *pHex, short Len)
{
#if USE_UART_DEBUG_INFO
    short i;
    char HexData[5];
    
    if(AppDebug.Flag) {         
//        OSSemPend(pSemDebug, 0, &err);     
        Debug(pHead);
        for(i=1; i<=Len; i++) {   
            sprintf(HexData, "%02X ", *pHex++);
            HexData[4] = 0;
            Debug(HexData);
            
            if(0 == i % 40) {
                Debug("\r\n");
                FeedDog();
            }
        }
        Debug("\r\n");
//        OSSemPost(pSemDebug);
    }   
#endif    
}


void    DebugMsg(DEBUG_ENUM Type, char *msg, ...)
{
#if USE_UART_DEBUG_INFO    
//    INT8U err;

    if(!AppDebug.Bits.Enable) {
        return;
    }

    if((DEBUG_AT == Type) && (!AppDebug.Bits.ATCmd)) {
        return;
    }

    if((DEBUG_VFD == Type) && (!AppDebug.Bits.Vfd)) {
        return;
    }
    
//    OSSemPend(pSemDebug, 0, &err); 
    switch(Type) {
        case DEBUG_AT:           
            Debug("[GPRS] ");
            break;
        case DEBUG_GPRS:            
            Debug("[GPRS] ");
            break;
        case DEBUG_SMS:
            Debug("[SMS] ");
            break;    
        case DEBUG_PRO:
            Debug("[Pro] ");
            break;
//        case DEBUG_MONITOR:
//            Debug("[Monitor] ");
//            break;
        case DEBUG_UPGRADE:
            Debug("[Update] ");
            break;
        case DEBUG_YUE:
            Debug("[Money] ");
            break; 
//        case DEBUG_TASK:
//            Debug("[Task] ");
//            break;
//        case DEBUG_VFD:
//            Debug("[VFD] ");
//            break;
        case DEBUG_PARA:
            Debug("[Para] ");
            break;
		case DEBUG_SFUD:
			Debug("[SFUD] ");
            break;
//        case DEBUG_CTRL:
//            Debug("[CTRL] ");
//            break;
//        case DEBUG_HMI:
//            Debug("[HMI] ");
//            break;
//        case DEBUG_IO:
//            Debug("[IO] ");
//            break;
        default:
            break;
    }

    va_start(argp, msg);
    vsnprintf(DbgMsgstr, sizeof(DbgMsgstr), msg, argp);
    va_end(argp);        
    Debug(DbgMsgstr);
//    OSSemPost(pSemDebug);    
#endif    
}

void    RS485CfgResp(char *pBuf, int Len)
{
    memcpy(pVfd->SndBuf, pBuf, Len);
    pVfd->SndSize = Len;
    ModbusStartSend(pVfd);
//    while(DebugUartRcvStat) {
//        RS485SndDly();
//        FeedDog();
//    }     
//    DebugChgToSnd();
//    UartSendData(DebugUart, pBuf, Len);
//    RS485SndDly();
//    DebugChgToRcv();  
}

