#define _InGprs
#include "gc65.h"
#include "includes.h"

static char InitStep = 0;

static    char _gprsDealBuf[MAX_GPRS_BUF_SIZE+4];
extern DELAY_TIMER ParaUploadDelay;

//unsigned char   ATRespBufIdx;
//void           *QATRespBut[AT_RESP_Q_SIZE];
//AT_RESP_STRUCT  ATRespBuf[AT_RESP_Q_SIZE];

void    ATRespDataPost(char *pBuf, unsigned short Len)
{
//    INT8U   err;
//    OS_Q_DATA QStatus;
//    
//    if(OS_ERR_NONE != OSQQuery(QEventATResp, &QStatus)) {
//        DebugMsg(DEBUG_GPRS, "Query QEventATResp Fail\r\n");
//        return;
//    }
//    
//    if(QStatus.OSNMsgs >= QStatus.OSQSize) {        
//        DebugMsg(DEBUG_GPRS, "QEventATResp Msg Full\r\n");
//        OSQAccept(QEventATResp, &err);        
//    }
//        
//    ATRespBuf[ATRespBufIdx].Len = Len;
//    memcpy(ATRespBuf[ATRespBufIdx].Buf, pBuf, Len);    
//    OSQPost(QEventATResp, &ATRespBuf[ATRespBufIdx]);
//    if(++ATRespBufIdx >= AT_RESP_Q_SIZE) {
//        ATRespBufIdx = 0;
//    }
}

static void ATCmdSend(char* pCmd, int DelayMs)
{
    GprsCtrlInfo.TmrMsCnt = DelayMs;
    GprsCtrlInfo.blTimeOut = FALSE;
    GprsCtrlInfo.Rlst.Flag = 0;
    if(NULL == pCmd) {        
        return;
    }

    DebugMsg(DEBUG_AT, "%s\r\n", pCmd);
    GprsUartCmd(pCmd, strlen(pCmd));    
}

#if GPRS_DATA_EN
GPRS_RCV_BUF_STRUCT *pToGprs = (GPRS_RCV_BUF_STRUCT *)_gprsDealBuf;

//unsigned char GprsRcvBufIdx;
//void         *QGprsRcvBuf[GPRS_RCV_Q_SIZE];
//GPRS_RCV_BUF_STRUCT GprsRcvBuf[GPRS_RCV_Q_SIZE]; 

void    GprsRcvDataPost(char *pBuf, unsigned short Len, char Chnl)
{
//    INT8U   err;
//    OS_Q_DATA QStatus;
//    
//    if(OS_ERR_NONE != OSQQuery(QEventGprsRcv, &QStatus)) {
//        DebugMsg(DEBUG_GPRS, "Query QEventGprsRcv Fail\r\n");
//        return;
//    }
//    
//    if(QStatus.OSNMsgs >= QStatus.OSQSize) {        
//        DebugMsg(DEBUG_GPRS, "QEventGprsRcv Msg Full\r\n");
//        OSQAccept(QEventGprsRcv, &err);        
//    }

//    GprsRcvBuf[GprsRcvBufIdx].Chnl = Chnl;
//    GprsRcvBuf[GprsRcvBufIdx].Len  = Len;
//    memcpy(GprsRcvBuf[GprsRcvBufIdx].Buf, pBuf, Len);    
//    OSQPost(QEventGprsRcv, (void *)&GprsRcvBuf[GprsRcvBufIdx]);
//    if(++GprsRcvBufIdx >= GPRS_RCV_Q_SIZE) {
//        GprsRcvBufIdx = 0;
//    }
}


//typedef struct 
//{
//    short Len;
//    char  Buf[MAX_GPRS_BUF_SIZE];
//}GPRS_SND_BUF_STRUCT;

//unsigned char GprsSndBufIdx;
//void         *QGprsSndBuf[GPRS_SND_Q_SIZE]; 
//GPRS_RCV_BUF_STRUCT GprsSndBuf[GPRS_SND_Q_SIZE]; 

void    GprsSndDataPost(char *pBuf, unsigned short Len, char Chnl)
{
    pipeDataWrite(pGprsSnd, pBuf, Len);
//    INT8U   err;
//    OS_Q_DATA QStatus;
//    
//    if(OS_ERR_NONE != OSQQuery(QEventGprsSnd, &QStatus)) {
//        DebugMsg(DEBUG_GPRS, "uery QEventGprsSnd Fail\r\n");
//        return;
//    }
//    
//    if(QStatus.OSNMsgs >= QStatus.OSQSize) {        
//        DebugMsg(DEBUG_GPRS, "QEventGprsSnd Msg Full\r\n");
//        OSQAccept(QEventGprsSnd, &err);        
//    }

//    GprsSndBuf[GprsSndBufIdx].Chnl = Chnl;
//    GprsSndBuf[GprsSndBufIdx].Len = Len;
//    memcpy(GprsSndBuf[GprsSndBufIdx].Buf, pBuf, Len);    
//    OSQPost(QEventGprsSnd, (void *)&GprsSndBuf[GprsSndBufIdx]);
//    if(++GprsSndBufIdx >= GPRS_SND_Q_SIZE) {
//        GprsSndBufIdx = 0;
//    }
}


char    GprsSndDataAccept(GPRS_RCV_BUF_STRUCT *pBuf)
{
    if(pipeDataRead(pGprsSnd, (char *)pBuf, sizeof(pBuf->Buf))) {
        return TRUE;
    }

    return FALSE;
//    INT8U err;
//    GPRS_RCV_BUF_STRUCT *pRcv;
//    
//    pRcv = OSQAccept((OS_EVENT *)pQEvent, &err);
//    if(NULL != pRcv) {
//        pBuf->Chnl = pRcv->Chnl;
//        pBuf->Len = pRcv->Len;
//        memcpy(pBuf->Buf, pRcv->Buf, pRcv->Len);
//        return TRUE;
//    }

//    return FALSE;
}

void    GprsSndDataFlush(void)
{
//    OSQFlush(QEventGprsSnd);
    pipeFlush(pGprsSnd);
}

#if URGEN_SND_Q_SIZE
//typedef struct 
//{
//    short Len;
//    char  Buf[MAX_GPRS_BUF_SIZE];
//}URGEN_SND_BUF_STRUCT; 

//unsigned char UrgenSndBufIdx;
//void         *QUrgenSndBuf[URGEN_SND_Q_SIZE]; 
//URGEN_SND_BUF_STRUCT UrgenSndBuf[URGEN_SND_Q_SIZE]; 

void    UrgenDataPost(char *pBuf, unsigned short Len)
{
//    INT8U   err;
//    OS_Q_DATA QStatus;
//    
//    if(OS_ERR_NONE != OSQQuery(QEventUrgenSnd, &QStatus)) {
//        DebugMsg(DEBUG_GPRS, "Query QEventUrgenSnd Fail\r\n");
//        return;
//    }
//    
//    if(QStatus.OSNMsgs >= QStatus.OSQSize) {        
//        DebugMsg(DEBUG_GPRS, "QEventUrgenSnd Msg Full\r\n");
//        OSQAccept(QEventUrgenSnd, &err);        
//    }
//        
//    UrgenSndBuf[UrgenSndBufIdx].Len = Len;
//    memcpy(UrgenSndBuf[UrgenSndBufIdx].Buf, pBuf, Len);    
//    OSQPost(QEventUrgenSnd, (void *)&UrgenSndBuf[UrgenSndBufIdx]);
//    if(++UrgenSndBufIdx >= URGEN_SND_Q_SIZE) {
//        UrgenSndBufIdx = 0;
//    }
}
#endif

char    SendGprsCondition(void)
{
    if((GprsCtrlInfo.Module.Bits.Ppp)    && 
    (GprsCtrlInfo.Module.Bits.Connect_1) &&
    (AT_Standby == GprsCtrlInfo.MainState)) {
        return TRUE;
    }

    return FALSE;
}


static void    ATCmdCnntSvr(char CntIdx, PROTOCOL_ENUM bTcp, char *pIp, int Port, int TimeOut)
{    
    char CmdBuf[60];
    char Protocol[4] = "TCP";
    
    if(PROTOCOL_UDP == bTcp) {
        strcpy(Protocol, "UDP");
    }

    sprintf(CmdBuf, "AT+QIOPEN=%d,\"%s\",\"%s\",%d\r", CntIdx, Protocol, pIp, Port);
    ATCmdSend(CmdBuf, TimeOut);
}

char    gprsIsConnect(void)
{
    return GprsCtrlInfo.Module.Bits.Connect_1;
}

#endif



#if GPRS_DATA_EN
void    SendIPDATA(char *pData, short Len, int DelayMs)
{
//    char CtrlZ = 0x1a;

    if(NULL == pData) {        
        return;
    }

#if 1
    *(pData+Len) = 0x1a;
    GprsUartCmd(pData, Len+1);
#else
    GprsUartCmd(pData, Len);
    GprsUartCmd(&CtrlZ, 1);
#endif    
    GprsCtrlInfo.TmrMsCnt = DelayMs;
    GprsCtrlInfo.blTimeOut = FALSE;
    GprsCtrlInfo.Rlst.Flag = 0;    
}
#endif


char    SendATCondition(void)
{
    char flag = FALSE;

    switch(GprsCtrlInfo.MainState) {
        case AT_MDL_INIT:    
            if((AT_Init == GprsCtrlInfo.SubState) && (InitStep >= 4)) {
                flag = TRUE;
            }
            break;
        case AT_PROP_CHECK:
            switch(GprsCtrlInfo.SubState) {
                case AT_QueryCGSN:
                case AT_QueryCPIN:
                case AT_QueryCIMI:
                case AT_PROP_OK:
                    flag = TRUE;
                break;
                    default:
                break;
            }
            break;
        case AT_Station_Reg:
            switch(GprsCtrlInfo.SubState) {
                case AT_QueryCREG:
                case AT_QueryCGREG:
                    flag = TRUE;
                    break;
                default:
                    break;
            }
            break;
        case AT_PPP:
            switch(GprsCtrlInfo.SubState) {
                case AT_SetAPN:
                case AT_GetIP:
                case AT_StartTask:
                case AT_DNSCFG:
                case AT_GetDNSIP:
                    flag = TRUE;
                    break;
                case AT_SetCIICR:                                   //  重试过程中不能插入AT指令
                    if(0 == GprsCtrlInfo.RetryCnt) {                //  防止AT指令无应答后重启模块,导致不能统计错误码
                        flag = TRUE;
                    }
                    break;
                default:
                    break;
            }
            break;
        case AT_CONNECT_SERVER:
            switch(GprsCtrlInfo.SubState) {
                case AT_ConnectTypeSet:
                case AT_ConnectSvr:
                    flag = TRUE;
                    break;
                default:
                    break;
            }
            break;    
        case AT_Standby:
            flag = TRUE;
            break;        
        case AT_PPP_CLOSE:
            if(AT_ClosePPP == GprsCtrlInfo.SubState) {
                flag = TRUE;
            }
            break;
        default:
            break;
    }

    return flag;
}


void    GprsParaInit(void)
{
    GprsCtrlInfo.Para.APN = GpSysPara->Net.APN;
    GprsCtrlInfo.Para.USR = GpSysPara->Net.USR;
    GprsCtrlInfo.Para.PWD = GpSysPara->Net.PWD;
    GprsCtrlInfo.Para.pInterval = &GpSysPara->Net.Interval;      
    GprsCtrlInfo.Para.pPort     = &GpSysPara->Net.Port;
    GprsCtrlInfo.Para.pDomain   = GpSysPara->Net.Domain;
}

void    GprsAppInit(void)
{
    pipeCreate((char **)GprsRcvBuf, GPRS_RCV_PIPE_CNT, GPRS_RCV_PIPE_SIZ, &pGprsRcv);
    pipeCreate((char **)GprsSndBuf, GPRS_SND_PIPE_CNT, GPRS_SND_PIPE_SIZ, &pGprsSnd);
    pipeCreate((char **)ATRespBuf,  AT_RESP_PIPE_CNT, AT_RESP_PIPE_SIZ,   &pATResp);
//    pipeCreate((char **)ATSendBuf,  AT_SEND_PIPE_CNT, AT_SEND_PIPE_SIZ,   &pATSend);

    GprsParaInit();
    GPRSUartDMAInit();
}

char    QDataValid(OS_EVENT *pQEvent)
{
    return FALSE;
//    OS_Q_DATA QStatus;
//    
//    if(OS_ERR_NONE != OSQQuery(pQEvent, &QStatus)) {
//        DebugMsg(DEBUG_GPRS, "Query QEventStatus Fail\r\n");
//        return FALSE;
//    }

//    return (QStatus.OSNMsgs ? TRUE : FALSE);
}

char    QDataRead(OS_EVENT *pQEvent, char *pBuf)
{
//    INT8U err;
//    GPRS_RCV_BUF_STRUCT *pRcv;

//    pRcv = OSQAccept(pQEvent, &err);
//    if(NULL != pRcv) {
//        memcpy(pBuf, pRcv, pRcv->Len + 2);
//        return TRUE;
//    }

    return FALSE;
}







static unsigned short RcvTmpLen = 0;
static char ATCharRcvBuf[MAX_GPRS_BUF_SIZE];

unsigned int RemoveBlackatoi(char *pBuf)
{
    while(' ' != *pBuf++)
    {
        break;
    }

    return my_atoi(pBuf);
}

/*
 *    +RECEIVE: 1, 2
 *    +CMT: "18080010141",,"2014/11/30 16:10:51+32"
 */

void    GprsUartIsr(char dat)
{
    static char RcvStep = 0;    
#if GPRS_DATA_EN    
//    static char GprsChnl = 0;    
    static short RcvSize = 0;    
#endif    

//    USART1->DR = dat;           //  test

    switch(RcvStep) {
        case 0:
            RcvTmpLen = 0;
            ATCharRcvBuf[RcvTmpLen++] = dat;
            switch(dat) {
                case '^':
                case '+':
                    RcvStep = 10;
                    break;
                case '\n':
                    break;
                case '\r':
                    break;
                case '>':
                    RcvStep = 2;                    
                    break;
                default:
                    RcvStep++;
                    break;
            }        
            break;
        case 1:
            ATCharRcvBuf[RcvTmpLen++] = dat;
            if(('\n' == dat) || (RcvTmpLen >= MAX_GPRS_BUF_SIZE)) {                
                ATCharRcvBuf[RcvTmpLen-2] = 0;
                 RcvTmpLen-=1;
                if(RcvTmpLen > MDL_AT_RESP_LEN) {
                    RcvTmpLen = MDL_AT_RESP_LEN;
                }
                pipeDataWrite(pATResp, ATCharRcvBuf, RcvTmpLen);
                RcvStep = 0;   
            }
            break;
            
        case 2:
            ATCharRcvBuf[RcvTmpLen++] = dat;
            if(' ' == dat) {
                ATCharRcvBuf[RcvTmpLen++] = 0;
                pipeDataWrite(pATResp, ATCharRcvBuf, RcvTmpLen);
                RcvStep = 0;
            } else {
                RcvStep = 1;
            }
            break;

        //  +RECEIVE: 1, 57
        case 10:                    
            ATCharRcvBuf[RcvTmpLen++] = dat;
#if GPRS_DATA_EN
            if('R' == dat) {
                RcvStep++;
            } else 
#endif
            {
                RcvStep = 1;
            }
            break;

        /*
         *    +RECEIVE: 1, 2
         */
#if GPRS_DATA_EN
        case 11:
            ATCharRcvBuf[RcvTmpLen++] = dat;
            if('E' == dat) {
                RcvStep++;
            } else {
                RcvStep = 1;
            }
            break;

        case 12:
            ATCharRcvBuf[RcvTmpLen++] = dat;
            if('C' == dat) {
                RcvStep++;
            } else {
                RcvStep = 1;
            }
            break;

        case 13:
            ATCharRcvBuf[RcvTmpLen++] = dat;
            if('E' == dat) {
                RcvStep++;
            } else {
                RcvStep = 1;
            }
            break;    

        case 14:
            ATCharRcvBuf[RcvTmpLen++] = dat;
            if('I' == dat) {
                RcvStep++;
            } else {
                RcvStep = 1;
            }
            break;    

        case 15:
            ATCharRcvBuf[RcvTmpLen++] = dat;
            if('V' == dat) {
                RcvStep++;
            } else {
                RcvStep = 1;
            }
            break;    

        case 16:
            ATCharRcvBuf[RcvTmpLen++] = dat;
            if('E' == dat) {
                RcvStep++;
            } else {
                RcvStep = 1;
            }
            break;        

        case 17:                                                    //    +RECEIVE: 1, 2
            ATCharRcvBuf[RcvTmpLen++] = dat;
            if(':' == dat) {
                RcvTmpLen = 0;
                RcvStep++;
            } else {
                RcvStep = 1;
            }
            break;    

        case 18:
            if(',' == dat) {
                ATCharRcvBuf[RcvTmpLen] = 0;
//                GprsChnl = RemoveBlackatoi(ATCharRcvBuf);
                RemoveBlackatoi(ATCharRcvBuf);
                RcvTmpLen = 0;
                RcvStep++;
            } else if(RcvTmpLen < 3) {
                ATCharRcvBuf[RcvTmpLen++] = dat;
            } else {
                RcvStep = 0;
            }
            break;

        case 19:
            if('\r' == dat) {
                ATCharRcvBuf[RcvTmpLen] = 0;
                RcvSize = RemoveBlackatoi(ATCharRcvBuf);
                if(RcvSize > MAX_GPRS_BUF_SIZE) {
                    RcvStep = 0;
                } else {
                    RcvTmpLen = 0;
                    RcvStep++;
                }
            } else if(RcvTmpLen <= 5) {
                ATCharRcvBuf[RcvTmpLen++] = dat;
            } else {
                RcvStep = 0;
            }            
            break;

        case 20:
            RcvTmpLen = 0;
            RcvStep++;
            break;        

        case 21:
            ATCharRcvBuf[PIPE_LEN_INFO_SIZE+RcvTmpLen] = dat;
            RcvTmpLen++;
            if(RcvTmpLen >= RcvSize) {
                memcpy(ATCharRcvBuf, (char *)&RcvTmpLen, PIPE_LEN_INFO_SIZE);
                pipeDataWrite(pGprsRcv, ATCharRcvBuf, PIPE_LEN_INFO_SIZE + RcvTmpLen);
                RcvStep = 0;
            } 
            break;        
#endif            
            
        default:
            RcvStep = 0;
            break;
    }    
}

unsigned int ATstrToInt32U(char *str, char max)
{
    unsigned int ret = 0;

    while((*str<'0')||(*str>'9')) {
        str++;
    }

    while((max--)&&(*str>='0')&&(*str<='9')) {
        ret *= 10;
        ret += *str - '0';
        str++;
    }

    return ret;
}

void    GprsReAPN(void)
{
    if(GprsCtrlInfo.Module.Bits.Ppp || GprsCtrlInfo.Module.Bits.Connect_1) {
        GprsCtrlInfo.Reqult.Bits.CloseGprs = TRUE;  
        GprsCtrlInfo.Reqult.Bits.ReAPN = TRUE;
    }
}

void    GprsReConnect(void)
{
    if(GprsCtrlInfo.Module.Bits.Connect_1) {
        GprsCtrlInfo.Reqult.Bits.CloseGprs = TRUE;  
        GprsCtrlInfo.Reqult.Bits.ReAPN = TRUE;
    }
}


/*
 *  现处理应答命令如下
 *  OK
 *  ERROR
 *  +CPIN: READY
 *  +CPIN: NOT READY
 *  +CPIN: SIM PIN
 *  +CPIN: SIM PUK
 *  +CREG: 1,"1878","0873"
 *  +CME ERROR:10
 *  +CMT: "+8615021012496"," ","2010/09/25 17:25:01+32",145,4,0,241,"+8613800210500",145,27
 *  ALREAY CONNECT
 *  1, CONNECT OK
 *  1, CONNECT FAIL
 *  SEND OK             //  M35
 *  SEND FAIL           //  M35 
 *  1,SEND OK           //  GC65
 *  1,SEND FAIL         //  GC65
 *  1, CLOSE OK
 *  1, CLOSED        服务器主动断开
 *  +CSQ: 28,0
 *    DEACT OK
 *  >
 *  +CMGS: 247
 *  +CMS ERROR: 513
 *  +CNUM: "","14715236878",129,7,4
 *  +CLIP: "18080010141",161,"",,"",0
 *  NO CARRIER      对方挂机    
 *  NO ANSWER       无人接听
 *  CONNECT             //  发送邮件时，串口进入数据模式
 *  +QSMTPPUT: 0        //  邮件发送状态
 *  +QSMTPBODY: 33      //  邮件内容长度指示
 *  +QSMTPATT: 1024     //  邮件附件内容长度指示
// *  0,+PDP DEACT        //  不处理   
 */
void    ATCmdParse(char *pCmd, unsigned short Len)
{
    char cmpBuf[20];
    char offset;
    char* pPser = NULL;

//    *(pCmd + Len) = 0;
    DebugMsg(DEBUG_AT, "%s\r\n", pCmd);

    do {
        strcpy(cmpBuf, "OK");
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst.Bits.OK = TRUE;
            break;
        }

        strcpy(cmpBuf, "> ");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst.Bits.Ready = TRUE;
            break;
        }

        strcpy(cmpBuf, "ERROR");
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst.Bits.ERROR = TRUE;
            break;
        }

        strcpy(cmpBuf, "+CPIN:");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            if(0 == strncmp(&pCmd[offset], " READY", strlen(" READY"))) {
                GprsCtrlInfo.Module.Bits.SIMOK = TRUE;
                memcpy(DebugCheck.SimCard, "OK ", 3);
            } else if(0 == strncmp(&pCmd[offset], " NOT READY", strlen(" NOT READY"))) {
                GprsCtrlInfo.Module.Bits.SIMErr = TRUE;
                memcpy(DebugCheck.SimCard, "ERR", 3);
            } else if(0 == strncmp(&pCmd[offset], " SIM PIN", strlen(" SIM PIN"))) {
                
            } else if(0 == strncmp(&pCmd[offset], " SIM PUK", strlen(" SIM PUK"))) {
               
            }
            break;
        }

        strcpy(cmpBuf, "+CME ERROR:");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
//            GprsCtrlInfo.Rlst.Bits.CME_ERROR = TRUE;
            GprsCtrlInfo.Rlst.Bits.ERROR = TRUE;

            if(0 == strncmp(&pCmd[offset], " 10", strlen(" 10"))) {
                GprsCtrlInfo.Module.Bits.NoSIM = TRUE;
            }    
            break;
        }

        strcpy(cmpBuf, "+CREG:");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd,cmpBuf, strlen(cmpBuf))) {
            pPser = strtok(&pCmd[offset], ",");
            pPser = strtok(NULL, ",");
            if(NULL != pPser) {
                if((*pPser >= '0') && (*pPser <= '9')) {
                    GprsCtrlInfo.CREG = *pPser - '0';
//#if GPRS_LOC_EN
//                    pPser = strtok(NULL, ",");
//                    if(pPser) {                         //  基站信息
//                        if('"' == *pPser) {
//                            memcpy(GprsCtrlInfo.LocInf.lac, pPser+1, 4);
//                            GprsCtrlInfo.LocInf.lac[4] = 0;
//                        }

//                        pPser = strtok(NULL, ",");
//                        if(pPser) {
//                            if('"' == *pPser) {
//                                memcpy(GprsCtrlInfo.LocInf.ci, pPser+1, 4);
//                                GprsCtrlInfo.LocInf.ci[4] = 0;
//                            }
//                        }
//                    }
//                } else if('"' == *pPser) {
//                    memcpy(GprsCtrlInfo.LocInf.lac, pPser+1, 4);
//                    GprsCtrlInfo.LocInf.lac[4] = 0;

//                    pPser = strtok(NULL, ",");
//                    if(pPser) {
//                        if('"' == *pPser) {
//                            memcpy(GprsCtrlInfo.LocInf.ci, pPser+1, 4);
//                            GprsCtrlInfo.LocInf.ci[4] = 0;
//                        }
//                    }
//#endif 
                }          
            }
            GprsCtrlInfo.Rlst.Bits.CREG_OK = TRUE;
            break;
        }

        strcpy(cmpBuf,"+CGREG:");
        offset = strlen(cmpBuf);
        if(0==strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            pPser = strtok(&pCmd[offset], ",");
            pPser = strtok(NULL, ",");
            if(NULL != pPser) {
                GprsCtrlInfo.CGREG = (char)ATstrToInt32U(pPser, 3);
            }
            GprsCtrlInfo.Rlst.Bits.CGREG_OK = TRUE;
            break;
        }

        strcpy(cmpBuf,"+CNUM:");
        offset = strlen(cmpBuf);
        if(0==strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            pPser = strtok(&pCmd[offset], ",");
            pPser = strtok(NULL, ",");
            if(NULL != pPser) {                
                strcpy(GprsCtrlInfo.TelNum, &pPser[1]);
                GprsCtrlInfo.TelNum[strlen(GprsCtrlInfo.TelNum)-1] = 0;
                GprsCtrlInfo.Rlst.Bits.CNUM_OK = TRUE;
            }
            break;
        }
		
		 strcpy(cmpBuf,"+CCID:");
        offset = strlen(cmpBuf);
        if(0==strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            pPser = &pCmd[offset+2];
            if(NULL != pPser) {                
                strncpy(GprsCtrlInfo.CCID, pPser,20);
              //  GprsCtrlInfo.CCID[strlen(GprsCtrlInfo.CCID)] = 0;
                GprsCtrlInfo.Rlst.Bits.CCID_OK = TRUE;
            }
            break;
        }

#if GPRS_DATA_EN
        strcpy(cmpBuf,"ALREADY CONNECT");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {     
            GprsCtrlInfo.Rlst.Bits.SvrCnntRlst = TRUE;
            GprsCtrlInfo.Module.Bits.Connect_1 = TRUE;
            break;
        }

        strcpy(cmpBuf, "1, CONNECT OK");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst.Bits.SvrCnntRlst = TRUE;
            GprsCtrlInfo.Module.Bits.Connect_1 = TRUE;            
            break;
        }

        strcpy(cmpBuf,"1, CONNECT FAIL");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {    
            GprsCtrlInfo.Rlst.Bits.SvrCnntRlst = TRUE;
            GprsCtrlInfo.Module.Bits.Connect_1 = FALSE;    
//            if(GprsCtrlInfo.Connet_Fall_Num++ > 3)
//            {
//                strcpy(GpSysPara->Net.Domain, SERVER_DOMAIN);
//                GpSysPara->Net.Port = SERVER_PORT;
//                SetParaSaveFlag(NET_PARA_START_ADDR);                        
//                SysParaStorage();
//                DelayReConnect(100);
//            }
            break;
        }

        strcpy(cmpBuf,"SEND OK");
        offset = strlen(cmpBuf);
        if(0==strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst.Bits.GPRS_SEND_FINISH = TRUE;
            GprsCtrlInfo.Rlst.Bits.GPRS_SEND_RLST = TRUE;
            break;
        }


        strcpy(cmpBuf,"1,SEND OK");
        offset = strlen(cmpBuf);
        if(0==strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst.Bits.GPRS_SEND_FINISH = TRUE;
            GprsCtrlInfo.Rlst.Bits.GPRS_SEND_RLST = TRUE;
            break;
        }

        strcpy(cmpBuf,"SEND FAIL");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {            
            GprsCtrlInfo.Rlst.Bits.GPRS_SEND_FINISH = TRUE;
            GprsCtrlInfo.Rlst.Bits.GPRS_SEND_RLST = FALSE;
            break;
        }

        strcpy(cmpBuf,"1,SEND FAIL");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {            
            GprsCtrlInfo.Rlst.Bits.GPRS_SEND_FINISH = TRUE;
            GprsCtrlInfo.Rlst.Bits.GPRS_SEND_RLST = FALSE;
            break;
        }
        strcpy(cmpBuf,"1, CLOSE OK");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst.Bits.Close_OK = TRUE;
            GprsCtrlInfo.Module.Bits.Connect_1 = FALSE; 
            GprsCtrlInfo.Module.Bits.CntClose = TRUE; 
            break;
        }

        strcpy(cmpBuf,"1, CLOSED");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            if(GprsCtrlInfo.Module.Bits.Connect_1) {                    //  连接状态服务器主动断开!!!
                GprsCtrlInfo.Module.Bits.CntClose = TRUE;  
            }
            GprsCtrlInfo.Rlst.Bits.Close_OK = TRUE;
            GprsCtrlInfo.Module.Bits.Connect_1 = FALSE;                      
            break;
        }
#endif
#if GPRS_CSQ_EN
        strcpy(cmpBuf,"+CSQ:");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.CSQInf.Value = (unsigned char)ATstrToInt32U(&pCmd[offset],3);
            GprsCtrlInfo.Rlst.Bits.CSQ_OK = TRUE;
            DebugCheck.GprsSignal = GprsCtrlInfo.CSQInf.Value;
            break;
        }
#endif        

        strcpy(cmpBuf,"DEACT OK");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {            
            GprsCtrlInfo.Rlst.Bits.DEACT_OK = TRUE;
            GprsCtrlInfo.Module.Bits.Ppp = FALSE;
            break;
        }

        strcpy(cmpBuf,"+PDP DEACT");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {    
            GprsReAPN();
            GprsCtrlInfo.ErrCode = GC65_ERR_PDP_DEACT;
            RegTimerErrCode();
            GprsCtrlInfo.Module.Bits.Ppp = FALSE;
            break;
        }
        
        if((GprsCtrlInfo.Reqult.Bits.IMEI) && (15 == Len)) {
            GprsCtrlInfo.Reqult.Bits.IMEI = FALSE;            
            GprsCtrlInfo.Rlst.Bits.RD_IMEI_OK = TRUE;
            strcpy(GprsCtrlInfo.IMEI, pCmd);
            break;
        }

        if((GprsCtrlInfo.Reqult.Bits.CIMI) && (15 == Len)) {
            GprsCtrlInfo.Reqult.Bits.CIMI = FALSE; 
            GprsCtrlInfo.Rlst.Bits.CIMI = TRUE;
            strcpy(GprsCtrlInfo.CIMI, pCmd);
            break;
        }     

        if((GprsCtrlInfo.Reqult.Bits.IP) && (Len >= 7) && (Len <= 15)) {
            if(IsIp(pCmd)) {
                GprsCtrlInfo.Reqult.Bits.IP = FALSE;
                strcpy(GprsCtrlInfo.IP, pCmd);
                break;
            }
        }

        strcpy(cmpBuf,"+CLIP:");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) { 
            pPser = strtok(&pCmd[offset], "\"");
            pPser = strtok(NULL, "\"");
            if(NULL != pPser) {
                if(!GprsCtrlInfo.Module.Bits.Ring) {
                    GprsCtrlInfo.Module.Bits.Ring = TRUE;
                    strcpy(GprsCtrlInfo.RingNum, pPser);
                    GprsCtrlInfo.RingCnt = 0;
                    } else {
                    if(strcmp(GprsCtrlInfo.RingNum, pPser)) {
                        strcpy(GprsCtrlInfo.RingNum, pPser);
                        GprsCtrlInfo.RingCnt = 0;
                    } else {
                        if(++GprsCtrlInfo.RingCnt >= 3) {
                            GprsCtrlInfo.RingCnt = 0;
                            GprsCtrlInfo.Reqult.Bits.HANG = TRUE;
                        }
                    }
                }                
            }           
            break;
        }         

        
        strcpy(cmpBuf,"+CMS ERROR:");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {            
            GprsCtrlInfo.Rlst.Bits.ERROR = TRUE;
            break;
        }    

        strcpy(cmpBuf, "0,+PDP DEACT");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {            
            GprsReAPN();
            break;
        }
        strcpy(cmpBuf, "+QNITZ:");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {            
            GprsReadNetTime(pCmd, &SysTime);
            break;
        }
        
        strcpy(cmpBuf, "+QENG:");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {            
            GprsReadQeng(pCmd);
            break;
        }
#if GPRS_FTP_EN
        strcpy(cmpBuf, "+QFTPOPEN:0");
//        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst2.Bits.FTP_OPEN = TRUE;
            break;
        }

        strcpy(cmpBuf, "+QFTPSIZE:");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, offset)) {
            GprsCtrlInfo.Rlst2.Bits.FTP_SIZE = TRUE;
            GprsCtrlInfo.FtpSizeVal = my_atoi(&pCmd[offset]);
            break;
        }
         
        strcpy(cmpBuf, "+QFTPPATH:0");
//        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst2.Bits.FTP_PATH = TRUE;
            break;
        }
                
        strcpy(cmpBuf, "+QFTPCFG:0");
//        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst2.Bits.FTP_CFG = TRUE;
            break;
        }

        strcpy(cmpBuf, "CONNECT");
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst2.Bits.FTP_CONNECT  = TRUE;
            UpgradeFlagSet();            
            break;
        }

        strcpy(cmpBuf, "+QFTPGET:");
        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, offset)) {
            GprsCtrlInfo.Rlst2.Bits.FTP_GET = TRUE;
            GprsCtrlInfo.FtpGetVal = my_atoi(&pCmd[offset]);
            break;
        }        
        
        strcpy(cmpBuf, "+QFTPDELETE:0");
//        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst2.Bits.FTP_DELETE = TRUE;
            break;
        }

        strcpy(cmpBuf, "+QFTPPUT:-");
//        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst2.Bits.FTP_ERROR = TRUE;
            GprsCtrlInfo.Rlst.Bits.ERROR = TRUE;
            break;
        }
        
        strcpy(cmpBuf, "+QFTPPUT:");
//        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst2.Bits.FTP_SUCCESS = TRUE;
            break;
        }
        
        strcpy(cmpBuf, "+QFTPERROR:");
//        offset = strlen(cmpBuf);
        if(0 == strncmp(pCmd, cmpBuf, strlen(cmpBuf))) {
            GprsCtrlInfo.Rlst2.Bits.FTP_ERROR = TRUE;
            GprsCtrlInfo.Rlst.Bits.ERROR = TRUE;
            break;
        }

        if(GprsCtrlInfo.Reqult.Bits.DNS) {
            if((Len >= 7) && (Len <= 15)) {
                if(IsIp(pCmd)) {
                    GprsCtrlInfo.Rlst.Bits.DNS_OK = TRUE;
                    break;
                }
            }
        }
#endif
        DebugMsg(DEBUG_AT, "AT unknow\r\n");
    } while(0);
}





void    ATCmdSetAPN(char *pName, char *pUsr, char *pPwd)
{
    char CmdBuf[50];
    
    sprintf(CmdBuf, "AT+QICSGP=1,\"%s\",\"%s\",\"%s\"\r", pName, pUsr, pPwd);
    ATCmdSend(CmdBuf, 2000);
}






#define    IsOK()                (GprsCtrlInfo.Rlst.Bits.OK)
#define ClrOK()             (GprsCtrlInfo.Rlst.Bits.OK=FALSE)
#define    IsErr()                (GprsCtrlInfo.Rlst.Bits.ERROR)
#define ClrErr()            (GprsCtrlInfo.Rlst.Bits.ERROR=FALSE)
#define IsTimeOut()          (GprsCtrlInfo.blTimeOut)


void    InsertTo(AT_Model_Stage mStage, AT_Model_Stage sStage)
{
    GprsCtrlInfo.WaitRertyCnt = GprsCtrlInfo.RetryCnt;    
    RetryCntSet(0);

    GprsCtrlInfo.WaitMainState = GprsCtrlInfo.MainState;
    GprsCtrlInfo.WaitSubState  = GprsCtrlInfo.SubState;
    TransTo(mStage, sStage);
}

void    ReturnToInserStage(void)
{
    RetryCntSet(GprsCtrlInfo.WaitRertyCnt);
    MainState(GprsCtrlInfo.WaitMainState);
    SubState(GprsCtrlInfo.WaitSubState);
}





void    SetReset(unsigned int Nms)
{    
//    ResetCtrl.Delay = Nms;
//    ResetCtrl.bRequest = TRUE;
} 



void    DelayReConnect(u16 Nms)
{
    RegDelay = 0;
    GprsCtrlInfo.DlyReConnect.Bits.Flag = TRUE;
    GprsCtrlInfo.DlyReConnect.Bits.Timer = Nms;
}

void    DelayRePPP(u16 Nms)
{
    RegDelay = 0;
    GprsCtrlInfo.DlyRePPP.Bits.Flag = TRUE;
    GprsCtrlInfo.DlyRePPP.Bits.Timer = Nms;
}

//static SMS_INTERVAL_STRUCT SmsInv;
void    HaveDataSend(u16 cyc_ms)
{    
    if(0) {
        //  nothing
#if GPRS_DATA_EN                                                   //  GPRS数据发送

    } else if(PipeDataValid(pGprsSnd)) {
        if(AT_Standby == GprsCtrlInfo.MainState) {
               
            if(GprsSndDataAccept(pToGprs)) {
                InsertTo(AT_SendData, AT_SetSendDATA);
                LedOnSet(100, 100, 1);
                ClearHeartTimer();                                  //  有数据发送,清心跳计数
            
            }
        }    
#endif
#if GPRS_FTP_EN
    } else if(GprsCtrlInfo.Reqult.Bits.FTP_CONNECT) { 
        if((AT_Standby == GprsCtrlInfo.MainState) || (AT_TEST == GprsCtrlInfo.MainState)) {
            GprsCtrlInfo.Reqult.Bits.FTP_CONNECT = FALSE;
//            InsertTo(AT_FILE_FTP_SEND, AT_FTP_USR);
            InsertTo(AT_FILE_FTP_SEND, AT_FTP_IPGCNT);
            
        }
#endif        
#if GPRS_CSQ_EN
    } else if(GprsCtrlInfo.Reqult.Bits.CSQ) {
        if(SendATCondition()) {
            GprsCtrlInfo.Reqult.Bits.CSQ = FALSE;
            InsertTo(AT_CSQ, AT_QueryCSQ);
        }   
#endif
    } else if(GprsCtrlInfo.Reqult.Bits.HANG) {                      //  挂电话
        if(SendATCondition()) {
            GprsCtrlInfo.Reqult.Bits.HANG = FALSE;
            InsertTo(AT_HANG, AT_ATH);
        }
    }
}

void    GC65Timer(u16 Nms)
{
     if(GprsCtrlInfo.TmrMsCnt > Nms) {
        GprsCtrlInfo.TmrMsCnt -= Nms;
        GprsCtrlInfo.blTimeOut = FALSE;
    } else {
        GprsCtrlInfo.TmrMsCnt = 0;
        GprsCtrlInfo.blTimeOut = TRUE;
    }

#if GPRS_CSQ_EN
    GprsCtrlInfo.CSQInf.TimeCnt += Nms;
    if(GprsCtrlInfo.CSQInf.TimeCnt >= CSQ_CHECK_INTERVAL) {
        GprsCtrlInfo.CSQInf.TimeCnt = 0;
        GprsCtrlInfo.Reqult.Bits.CSQ = TRUE;        
    }
#endif
}



void    TaskGC65(u16 cyc_ms)
{
    char SIMType;
#if GPRS_DATA_EN    
    char TmpBuf[50];    
#endif  
   
#if GPRS_DATA_EN
    if(GprsCtrlInfo.Module.Bits.CntClose) {                         //  连接主动断开/被动断开的情况
        GprsCtrlInfo.Module.Bits.CntClose = FALSE;        
//        LedOnSet(0, 0, 0);                                          //  指示灯熄灭      
    }

    if(GprsCtrlInfo.Reqult.Bits.ReAPNDly) {
        if(GprsCtrlInfo.ReAPNDelay > cyc_ms) {
            GprsCtrlInfo.ReAPNDelay -= cyc_ms;
        } else {
            GprsCtrlInfo.ReAPNDelay = 0;
            GprsCtrlInfo.Reqult.Bits.ReAPNDly = FALSE;
            GprsReAPN();
        }                
    }

    if(GprsCtrlInfo.DlyRePPP.Bits.Flag) {
        if(GprsCtrlInfo.DlyRePPP.Bits.Timer > cyc_ms) {
            GprsCtrlInfo.DlyRePPP.Bits.Timer -= cyc_ms;
        } else {
            GprsCtrlInfo.DlyRePPP.Bits.Flag = 0;
            GprsCtrlInfo.DlyRePPP.Bits.Timer = 0;
            GprsReAPN();
        }
    }

    if(GprsCtrlInfo.DlyReConnect.Bits.Flag) {
        if(GprsCtrlInfo.DlyReConnect.Bits.Timer > cyc_ms) {
            GprsCtrlInfo.DlyReConnect.Bits.Timer -= cyc_ms;
        } else {
            GprsCtrlInfo.DlyReConnect.Bits.Flag = 0;
            GprsCtrlInfo.DlyReConnect.Bits.Timer = 0;
            GprsReConnect();
        }
    }
    
#endif    

    GC65Timer(cyc_ms);
    HaveDataSend(cyc_ms);

    if(GprsCtrlInfo.Module.Bits.SIMErr) {                           //  SIM被移除,重启模块
        GprsCtrlInfo.Module.Bits.SIMErr = FALSE;
        GprsCtrlInfo.ErrCode = GC65_ERR_SIMERR;
        RegTimerErrCode();
        DebugMsg(DEBUG_GPRS, "SIM Active Fail\r\n");
        TransTo(AT_None, AT_None);
    }
    
    switch(GprsCtrlInfo.MainState) {
        /*
         *  GPRS模块关机
         */
        case AT_None:          
//            LedOnSet(0, 0, 0);    
            SIMType = GprsCtrlInfo.Module.Bits.Standard;
            GprsCtrlInfo.Reqult.Flag = 0;
            GprsCtrlInfo.Module.Status = 0;
            GprsCtrlInfo.Module.Bits.Standard = SIMType;
            GprsCtrlInfo.WaitMainState = AT_None;
            GprsCtrlInfo.WaitSubState  = AT_None;
            strcpy(GprsCtrlInfo.IP, "0.0.0.0");
            RetryCntSet(0);
            GprsDMAReceiveDisable();
            TransTo(AT_PWR_CTRL, AT_Power_off);
            break;
            
        case AT_PWR_CTRL:
            switch(GprsCtrlInfo.SubState) {
                case AT_Power_off:
                    DebugMsg(DEBUG_GPRS, "Power ctrl\r\n");
                    GPRS_POWER_OFF();
                    GPRS_PWRKEY_HIGH();
                    ATCmdSend(NULL, 3000);                    
                    SubState(AT_Power_off_wait);
                    break;
                case AT_Power_off_wait:
                    if(IsTimeOut()) {
                        SubState(AT_Power_on);
                    }
                    break;
                case AT_Power_on:
                    GPRS_POWER_ON();
                    ATCmdSend(NULL, 500);
                    SubState(AT_Power_on_wait);
                    break;
                case AT_Power_on_wait:
                    if(IsTimeOut()) {
                        SubState(AT_Switch_on);
                    }
                    break;
                case AT_Switch_on:
                    GPRS_PWRKEY_LOW();        
                    ATCmdSend(NULL, 1500);
                    SubState(AT_Switch_on_Wait);
                    break;
                case AT_Switch_on_Wait:
                    if(IsTimeOut()) {
                        GPRS_PWRKEY_HIGH();
                        ATCmdSend(NULL, 3000);    
                        SubState(AT_PWR_CTRL_ok);   
                    }
                    break;
                case AT_PWR_CTRL_ok:
                    if(IsTimeOut()) {    
                        InitStep = 0;
                        RetryCntSet(0);
                        GprsCtrlInfo.NoRespCnt = 0;
                        DebugMsg(DEBUG_GPRS, "module init\r\n");
                        TransTo(AT_MDL_INIT, AT_Init);  
                    }
                    break;    
                case AT_PWR_CTRL_fail:
                    DebugMsg(DEBUG_GPRS, "Boot Fail\r\n");
                    TransTo(AT_None, AT_None);
                    break;
                default:
                    SubState(AT_Power_off);
                    break;
            }
            break;
            
        case AT_MDL_INIT:
            switch(GprsCtrlInfo.SubState) {
                case AT_Init:
                    if(GprsCtrlInfo.RetryCnt++ > 20) {
                        SubState(AT_Init_Fail);            
                        break;
                    }

                    switch(InitStep) {
                        case 0:                                
                            ATCmdSend("AT\r", 1500);
                            break;
                        case 1:
                            ATCmdSend("ATE0\r", 1500);
                            break;
                        case 2:
                            ATCmdSend("AT+IPR=115200\r", 1500);                     
                            break;
                        case 3:
                            ATCmdSetAPN(GprsCtrlInfo.Para.APN, GprsCtrlInfo.Para.USR, GprsCtrlInfo.Para.PWD);
                            break;
                        case 4:
                            ATCmdSend("AT+CREG=2\r", 1500);
                            break;                    
                        case 5:
                            ATCmdSend("AT+CGCLASS=\"B\"\r", 1500);
                            break;                    
                        case 6:
                            ATCmdSend("AT+QIMUX=1\r", 1500);
                            break; 
                        case 7:
                            ATCmdSend("AT+QNITZ=1\r", 1500);
                            break;
                        case 8:
                            ATCmdSend("AT+QENG=1,1\r", 1500);
                            break;
                        default:
                            InitStep = 0;
                            break;
                    }
                    SubState(AT_Init_Wait);
                    break;
                case AT_Init_Wait:
                    if(IsOK()) { 
                        SubState(AT_Init);
                        RetryCntSet(0);
                        if(++InitStep > 8) {                        
                            InitStep = 0;                            
                            SubState(AT_Init_Ok);
                        }                
                    } else if(IsErr()) {
                        ClrErr();                                   //  等待超时
                        GprsCtrlInfo.NoRespCnt = 0;                       
                    } else if(IsTimeOut()) { 
                        SubState(AT_Init);     
                        if(++GprsCtrlInfo.NoRespCnt > 5) {
                            SubState(AT_Init_Fail);
                        }
                    }
                    break;
                case AT_Init_Ok:
                    TransTo(AT_PROP_CHECK, AT_QueryCGSN);
                    DebugMsg(DEBUG_GPRS, "Module info\r\n");
                    break;    
                case AT_Init_Fail:
                    switch(InitStep) {
                        case 0:
                            GprsCtrlInfo.ErrCode = GC65_ERR_AT;
                            RegTimerErrCode();
                            DebugMsg(DEBUG_GPRS, "Module Error\r\n");
                            break;
                        default:
                            break;
                    }
                    TransTo(AT_None, AT_None); 
                    break;                
                default:
                    SubState(AT_Init);
                    break;
            }
            break;
        
        case AT_PROP_CHECK:
            switch(GprsCtrlInfo.SubState) {
                case AT_QueryCGSN:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {
                        SubState(AT_PROP_FAIL);
                    } else {
                        GprsCtrlInfo.Reqult.Bits.CIMI = TRUE;
                        ATCmdSend("AT+GSN\r", 2000);
                        SubState(AT_QueryWaitCGSN);
                    }
                    break;
                case AT_QueryWaitCGSN:
                    if((IsOK()) && (GprsCtrlInfo.Rlst.Bits.CIMI)) {
                        RetryCntSet(0);
                        SubState(AT_QueryCPIN);                
                    } else if(IsTimeOut()) {
                        SubState(AT_QueryCGSN);    
                    }
                    break;    
                case AT_QueryCPIN:
                    if(GprsCtrlInfo.RetryCnt++ > 15) {
                        if(GprsCtrlInfo.Module.Bits.NoSIM) {
                            GprsCtrlInfo.ErrCode = GC65_ERR_NOSIM;
                            RegTimerErrCode();
                            DebugMsg(DEBUG_GPRS, "NO SIM\r\n");
                        }                    
                        SubState(AT_PROP_FAIL);
                    } else {
                        if(!GprsCtrlInfo.Module.Bits.SIMOK) {
                            GprsCtrlInfo.Module.Bits.NoSIM = FALSE;
                            ATCmdSend("AT+CPIN?\r", 1000);                    
                            SubState(AT_QueryWaitCPIN);
                        } else {
                            SubState(AT_QueryCIMI);
                        }                        
                    }
                    break;
                case AT_QueryWaitCPIN:
                    if(IsOK() && GprsCtrlInfo.Module.Bits.SIMOK) {
                        RetryCntSet(0);
                        SubState(AT_QueryCIMI);
                    } else if(IsTimeOut()/* || IsErr()*/) {
                        SubState(AT_QueryCPIN);
                    }
                    break;
                    
                case AT_QueryCIMI:
                    if(GprsCtrlInfo.RetryCnt++ > 10) {
                        SubState(AT_PROP_FAIL);
                    } else {
                        GprsCtrlInfo.Reqult.Bits.IMEI = TRUE;
                        ATCmdSend("AT+CIMI\r", 1000);   
                        SubState(AT_QueryWaitCIMI);
                    }
                    break;
                case AT_QueryWaitCIMI:
                    if(IsOK() && GprsCtrlInfo.Rlst.Bits.RD_IMEI_OK) {
                        RetryCntSet(0);
                        switch(GprsCtrlInfo.IMEI[4]) {
                            case '0':
                            case '2':
                            case '7':
                            case '4':                               //  GC65模块返回,待确认
                                GprsCtrlInfo.Module.Bits.Standard = STANDARD_GSM_YD;
                                break;
                            case '1':
                            case '6':
                                GprsCtrlInfo.Module.Bits.Standard = STANDARD_GSM_LT;
                                break;
                            case '3':
                            case '5':
                                GprsCtrlInfo.Module.Bits.Standard = STANDARD_GSM_DX;
                                break;
                            default:
                                GprsCtrlInfo.Module.Bits.Standard = STANDARD_GSM_YD;
                                break;                            
                        }                    
                        
                     //   SubState(AT_PROP_OK);
                      SubState(AT_QueryCCID);                              //  查询卡号            
                    } else if(IsTimeOut()/* || IsErr()*/) {
                        SubState(AT_QueryCIMI);
                    }
                    break;
                    
              case AT_QueryCCID:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {   //  ????????,?????
                        SubState(AT_PROP_OK);
                    } else {                    
                        ATCmdSend("AT+CCID\r", 3000);
                        SubState(AT_QueryWaitCCID);
                    }
                    break;
                case AT_QueryWaitCCID:
                    if(IsOK()&& (GprsCtrlInfo.Rlst.Bits.CCID_OK)) {
                        SubState(AT_PROP_OK);
                    } else if(IsTimeOut()) {
                        SubState(AT_QueryCCID);
                    }
                    break;    
                case AT_PROP_OK:
                    GprsCtrlInfo.NoRespCnt = 0;
                    TransTo(AT_Station_Reg, AT_QueryCREG);
                    DebugMsg(DEBUG_GPRS, "Connect station\r\n");
                    break;
                case AT_PROP_FAIL:
                    TransTo(AT_None, AT_None);
                    break;
                default:
                    SubState(AT_QueryCGSN);
                    break;
            }        
            break;                    
        /*
         *  网络注册状态查询    
         */
        case AT_Station_Reg:     
            switch(GprsCtrlInfo.SubState) {
                case AT_QueryCREG:
                    if(GprsCtrlInfo.RetryCnt++ > 30) {    
                        GprsCtrlInfo.ErrSubState = AT_QueryCREG;
                        DebugMsg(DEBUG_GPRS, "REG Fail\r\n");
                        SubState(AT_Station_Reg_Fail);
                        break;
                    } else {
                        ATCmdSend("AT+CREG?\r", 2000);
                        SubState(AT_QueryWaitCREG);
                    }
                    break;
                case AT_QueryWaitCREG:
                    if(IsOK() && GprsCtrlInfo.Rlst.Bits.CREG_OK) {
                        switch(GprsCtrlInfo.CREG) {
                            case 1:                                     //  已注册本地
                            case 5:                                     //  已注册漫游   
                                RetryCntSet(0);
                                GprsCtrlInfo.NoRespCnt = 0;
                                GprsCtrlInfo.Module.Bits.CREG = TRUE;
                                GprsCtrlInfo.Module.Bits.Roam = GprsCtrlInfo.CREG==5? TRUE:FALSE;    
                                if(GC65_ERR_GSM == GprsCtrlInfo.ErrCode) {
                                    GprsCtrlInfo.ErrCode = GC65_ERR_NONE;
                                }
                                SubState(AT_QIFGCNT);
                                break;
                            default:      //  未注册
                                ClrOK();  //  等待超时
                                GprsCtrlInfo.NoRespCnt = 0;
                                break;
                        }
                    } else if(IsErr()) {
                        ClrErr();                                   //  等待超时
                        GprsCtrlInfo.NoRespCnt = 0;     
                    } else if(IsTimeOut()) {                        
                        SubState(AT_QueryCREG);
                        if(++GprsCtrlInfo.NoRespCnt > 5) {
                            GprsCtrlInfo.ErrSubState = AT_QueryCREG;
                            SubState(AT_Station_Reg_Fail);
                        }
                    }        
                    break;
                case AT_QIFGCNT:
                    if(GprsCtrlInfo.RetryCnt++ > 5) {    
                        GprsCtrlInfo.ErrSubState = AT_QueryCREG;
                        DebugMsg(DEBUG_GPRS, "REG Fail\r\n");
                        SubState(AT_Station_Reg_Fail);
                    } else {
                        ATCmdSend("AT+QIFGCNT=0\r", 2000);
                        SubState(AT_QIFGCNTWait);
                    }
                    break;
                case AT_QIFGCNTWait:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_QueryCGREG);
                    } else if(IsTimeOut() || IsErr()) {
                        SubState(AT_QIFGCNT);
                    }            
                    break;                
                /*
                 *  GPRS网络注册状态查询
                 */
                case AT_QueryCGREG:                                
                    if(GprsCtrlInfo.RetryCnt++ > 30) {
                        GprsCtrlInfo.ErrSubState = AT_QueryCGREG;
                        DebugMsg(DEBUG_GPRS, "CREG Fail\r\n");
                        SubState(AT_Station_Reg_Fail); 
                        break;
                    } else {
                        ATCmdSend("AT+CGREG?\r", 2000);
                        SubState(AT_QueryWaitCGREG);   
                    }
                    break;
                case AT_QueryWaitCGREG:
                    if(IsOK() && GprsCtrlInfo.Rlst.Bits.CGREG_OK) {
                        switch(GprsCtrlInfo.CGREG) {
                            case 1:                                     //  已注册本地
                            case 5:                                     //  已注册漫游
                                RetryCntSet(0);
                                GprsCtrlInfo.NoRespCnt = 0;                                
                                GprsCtrlInfo.Module.Bits.CREG = TRUE;
                                GprsCtrlInfo.Module.Bits.Roam = GprsCtrlInfo.CREG==5? TRUE:FALSE;
//                                TransTo(AT_PPP, AT_SetAPN);    
                                SubState(AT_SQITCFG);
                                if(GC65_ERR_GPRSNET == GprsCtrlInfo.ErrCode) {
                                    GprsCtrlInfo.ErrCode = GC65_ERR_NONE;
                                }
                                break;
                            default:                                    //  未注册
                                ClrOK();                            //  等待超时
                                GprsCtrlInfo.NoRespCnt = 0;
                                break;
                        }
                    } else if(IsErr()) {
                        ClrErr();                                   //  等待超时
                        GprsCtrlInfo.NoRespCnt = 0;     
                    } else if(IsTimeOut()) {
                        SubState(AT_QueryCGREG);                        
                        if(++GprsCtrlInfo.NoRespCnt > 5) {
                            GprsCtrlInfo.ErrSubState = AT_QueryCGREG;
                            SubState(AT_Station_Reg_Fail);
                        }
                    }
                    break;
                case AT_SQIMode:
                    if(GprsCtrlInfo.RetryCnt++ > 5) {
                        DebugMsg(DEBUG_GPRS, "QIMODE Fail\r\n");
                        SubState(AT_Station_Reg_Fail); 
                    } else {
                        ATCmdSend("AT+QIMODE=1\r", 2000);
                        SubState(AT_SQIModeWait);   
                    }
                    break;
                case AT_SQIModeWait:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_SQITCFG);
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_SQIMode);                        
                    }
                    break;
                case AT_SQITCFG:
                    if(GprsCtrlInfo.RetryCnt++ > 5) {
                        DebugMsg(DEBUG_GPRS, "QITCFG Fail\r\n");
                        SubState(AT_Station_Reg_Fail); 
                    } else {
                        ATCmdSend("AT+QITCFG=3,2,512,1\r", 2000);
                        SubState(AT_SQITCFGWait);   
                    }
                    break;
                case AT_SQITCFGWait:
                    if(IsOK()) {
                        RetryCntSet(0);
                        TransTo(AT_PPP, AT_StartTask);
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_SQITCFG);                        
                    }
                    break;
                case AT_Station_Reg_Fail:
                    if(AT_QueryCREG == GprsCtrlInfo.ErrSubState) {
                        GprsCtrlInfo.ErrCode = GC65_ERR_GSM;
                        RegTimerErrCode();
                    } else if(AT_QueryCGREG == GprsCtrlInfo.ErrSubState) {
                        GprsCtrlInfo.ErrCode = GC65_ERR_GPRSNET;
                        RegTimerErrCode();
                    }
                    TransTo(AT_None, AT_None);    
                    break;
                default:
                    SubState(AT_QueryCREG);
                    break;
            }            
            break;

        /*
         *  信号质量查询
         */ 
        case AT_CSQ:
            switch(GprsCtrlInfo.SubState) {
                case AT_QueryCSQ: 
                    //ATCmdSend("AT+CSQ\r", 2000);
                    //ATCmdSend("AT+QENG?\r", 2000);
                     if(ParaUploadDelay.Bits.Flag) 
                     {
                        ATCmdSend("AT+CSQ\r", 2000);
                        SubState(AT_QueryWaitCSQ); 
                     }
                     else
                     {
                         ATCmdSend("AT+QENG?\r", 5000);
                         SubState(AT_QueryWaitCSQ); 
                     }
                    break;
                case AT_QueryWaitCSQ:  
                    if(IsOK()) {  
                        ReturnToInserStage();
                    } else if(IsTimeOut()) {                        
                        TransTo(AT_None, AT_None);
                    }
                    break;
                default:
                    SubState(AT_QueryCSQ);
                    break;
            }
            break;  
        /*
         *  PPP拨号
         */ 
        case AT_PPP:
            switch(GprsCtrlInfo.SubState) {
                case AT_SetAPN:
                    if(GprsCtrlInfo.RetryCnt++ > 10) {
                        SubState(AT_PPP_Fail); 
                    } else {
                        ATCmdSetAPN(GprsCtrlInfo.Para.APN, GprsCtrlInfo.Para.USR, GprsCtrlInfo.Para.PWD);
                        SubState(AT_SetAPNWait); 
                    }
                    break;
                case AT_SetAPNWait:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_StartTask);
                    } else if(IsTimeOut() || IsErr()) {
                        SubState(AT_SetAPN);
                    }            
                    break;
                    
                case AT_StartTask:  
                    if(GprsCtrlInfo.RetryCnt++ > 3) {
                        SubState(AT_PPP_Fail); 
                    } else {
                        GprsCtrlInfo.Module.Bits.Ppp = FALSE;
                        ATCmdSend("AT+QIREGAPP\r", 1500); 
                        SubState(AT_StartTaskWait); 
                    }
                    break;

                case AT_StartTaskWait:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_SetCIICR);
                    } else if(IsTimeOut()/* || IsErr()*/) {
                        SubState(AT_StartTask);
                    }            
                    break;
                case AT_SetCIICR:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {
                        SubState(AT_PPP_Fail); 
                    } else {
                        ATCmdSend("AT+QIACT\r", 20000);
                        SubState(AT_SetCIICRWait); 
                    }
                    break;

                case AT_SetCIICRWait:                                          
                    if(IsOK()) {
                        RetryCntSet(0);
                        GprsCtrlInfo.Module.Bits.Ppp = TRUE;
                        SubState(AT_GetIP);
                    } else if(IsTimeOut() || IsErr()) {
                        SubState(AT_SetCIICR);
                    }  
                    break;

                case AT_GetIP:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {
                        SubState(AT_PPP_Fail); 
                    } else {
                        GprsCtrlInfo.Reqult.Bits.IP = TRUE;
                        ATCmdSend("AT+QILOCIP\r", 1000);
                        SubState(AT_GetIPWait); 
                    }
                    break;
                case AT_GetIPWait:
                    if(IsTimeOut()) {
                        RetryCntSet(0);
                        if(!IsErr()) {
#if GPRS_DATA_EN
                            if(!IsIp(GprsCtrlInfo.Para.pDomain)) {
                                SubState(AT_DNSCFG);                //  配置域名解析服务器
//                                SubState(AT_GetDNSIP);              //  域名解析      
                            } else {
                                TransTo(AT_CONNECT_SERVER, AT_ConnectTypeSet);  
                            }
#endif                            
                            if(GC65_ERR_PPP == GprsCtrlInfo.ErrCode) {
                                GprsCtrlInfo.ErrCode = GC65_ERR_NONE;
                            }
                        } else {
                            SubState(AT_GetIP); 
                        }
                    }            
                    break;
                case AT_DNSCFG:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {
                        SubState(AT_PPP_Fail); 
                    } else {
                        ATCmdSend("AT+QIDNSCFG=\"8.8.8.8\"\r", 1000);
                        SubState(AT_DNSCFGWait); 
                    }                    
                    break;
                case AT_DNSCFGWait:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_GetDNSIP); 
                    } else if(IsTimeOut() || IsErr()) {
                        SubState(AT_DNSCFG);
                    }      
                    break;
                case AT_GetDNSIP:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {
                        SubState(AT_PPP_Fail); 
                    } else {
                        sprintf(TmpBuf, "AT+QIDNSGIP=\"%s\"\r", GprsCtrlInfo.Para.pDomain);
                        GprsCtrlInfo.Reqult.Bits.DNS = TRUE;
                        ATCmdSend(TmpBuf, 5000);
                        SubState(AT_GetDNSIPWait); 
                    }
                    break;
                case AT_GetDNSIPWait:
                    if(GprsCtrlInfo.Rlst.Bits.DNS_OK) {
                        RetryCntSet(0);                            
                        TransTo(AT_CONNECT_SERVER, AT_ConnectTypeSet);  
                    } else if(IsTimeOut()) {
                        SubState(AT_GetDNSIP);
                    }
                    break;
                case AT_PPP_Fail:                
                    GprsCtrlInfo.ErrCode = GC65_ERR_PPP;
                    RegTimerErrCode();
                    DebugMsg(DEBUG_GPRS, "PPP Fail\r\n");
                    TransTo(AT_None, AT_None); 
                    break;
                default:
                    SubState(AT_SetAPN);
                    break;
            }
            break;
#if GPRS_DATA_EN
        case AT_CONNECT_SERVER:
            switch(GprsCtrlInfo.SubState) {
                case AT_ConnectTypeSet:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {
                        SubState(AT_ConnectFail); 
                    } else {
                        if(IsIp(GprsCtrlInfo.Para.pDomain)) {           //  IP方式
                            ATCmdSend("AT+QIDNSIP=0\r", 1000);
                        } else {                                        //  域名方式 
                            ATCmdSend("AT+QIDNSIP=1\r", 1000);
                        }
                        SubState(AT_ConnectTypeWait); 
                    }
                    break;

                case AT_ConnectTypeWait:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_ConnectSvr); 
                    } else if(IsTimeOut() || IsErr()) {
                        SubState(AT_ConnectTypeSet); 
                    }
                    break;

                case AT_ConnectSvr:
                    if(GprsCtrlInfo.RetryCnt++ > 5) {                        
                        SubState(AT_ConnectFail);  
                    } else {
                        GprsCtrlInfo.Module.Bits.Connect_1 = FALSE;
                        ATCmdCnntSvr(1, PROTOCOL_TCP, GprsCtrlInfo.Para.pDomain, *GprsCtrlInfo.Para.pPort, 20000);
                        SubState(AT_SetConnect_Wait); 
                    }            
                    break;

                case AT_SetConnect_Wait:
                    if(IsOK() && GprsCtrlInfo.Rlst.Bits.SvrCnntRlst) {
                        if(GprsCtrlInfo.Module.Bits.Connect_1) {
                            GprsCtrlInfo.ErrCode = GC65_CONNECT_SVR_OK;
                            RetryCntSet(0);        
                            TransTo(AT_Standby, AT_None); 
                        } else {
                            ATCmdSend(NULL, 5000);                  //  服务器连接失败,等待5s重连
                        }                                
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_ConnectSvr); 
                    }
                    break;       

                case AT_ConnectFail:
                    GprsCtrlInfo.ErrCode = GC65_ERR_CONNTCT_SVR;
                    RegTimerErrCode();
                    DebugMsg(DEBUG_GPRS, "Connect Server %s:%d Fail\r\n", GpSysPara->Net.Domain, GpSysPara->Net.Port);                    
                    TransTo(AT_None, AT_None); 
                    break;
                default:
                    SubState(AT_ConnectTypeSet);
                    break;
            }
            break;

        /***************************连接服务器成功等待状态*******************************/
        case AT_Standby: 
            if(GprsCtrlInfo.Reqult.Bits.CloseGprs) {                    //  请求重新连接服务器
                GprsCtrlInfo.Reqult.Bits.CloseGprs = FALSE;
                RetryCntSet(0);
                TransTo(AT_PPP_CLOSE, AT_ClosePPP);
                break;
            }                
            if(GprsCtrlInfo.Reqult.Bits.Connect) {
                GprsCtrlInfo.Reqult.Bits.Connect = FALSE;
                RetryCntSet(0);
                TransTo(AT_PPP, AT_SetAPN);
                break;
            }            
            if((!GprsCtrlInfo.Module.Bits.Connect_1) &&                 //  服务器主动断开
               (!dtuStatus.Bits.Idle)) {                   
                RetryCntSet(0);
                TransTo(AT_CONNECT_SERVER, AT_ConnectTypeSet);
                break;
            }    
            break; 

        case AT_SendData:
            switch(GprsCtrlInfo.SubState) {
                case AT_SetSendDATA:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {    
                        SubState(AT_SendDataFail); 
                    } else {
                        sprintf(TmpBuf, "AT+QISEND=1,%d\r", pToGprs->Len);                
                        ATCmdSend(TmpBuf, 2000); 
                        SubState(AT_Send_cmdwait);
                    }            
                    break;

                /****************************发送数据指令执行********************************************/
                case AT_Send_cmdwait:
                    if(GprsCtrlInfo.Rlst.Bits.Ready) {   
                        SendIPDATA(pToGprs->Buf, pToGprs->Len, 5000); 
                        SubState(AT_Send_DATA_Wait);
                    } else if(IsTimeOut() || IsErr()) {
                        SubState(AT_SetSendDATA);
                    }
                    break;

                /**************************发送数据等待返回信息**********************************************/
                case AT_Send_DATA_Wait:
                    if(GprsCtrlInfo.Rlst.Bits.GPRS_SEND_FINISH) {                        
                        if(GprsCtrlInfo.Rlst.Bits.GPRS_SEND_RLST) {
                            ReturnToInserStage();
                        } else {
                            SubState(AT_SetSendDATA);
                        }
                    } else if(IsTimeOut() || IsErr()) {
                        SubState(AT_SetSendDATA);
                    }
                    break;
                case AT_SendDataFail:
                    DebugMsg(DEBUG_GPRS, "Send Data Fail\r\n");
                    TransTo(AT_None, AT_None);
                    break;
                default:
                    SubState(AT_SetSendDATA);
                    break;
            }
            break;
#endif

#if GPRS_FTP_EN
        case AT_FILE_FTP_SEND:
            switch(GprsCtrlInfo.SubState) { 
                case AT_FTP_IPGCNT:
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_FAIL);
                        break;
                    }
                    FtpInf.FtpOK = FALSE;
                    GprsCtrlInfo.Module.Bits.Ftping = TRUE;
                    ATCmdSend("AT+QIFGCNT=0\r", 2000);
                    SubState(AT_FTP_IPGCNT_WAIT);
                    break;
                case AT_FTP_IPGCNT_WAIT:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_FTP_APN);
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_FTP_IPGCNT);
                    }
                    break;
                case AT_FTP_APN:
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_FAIL);
                        break;
                    }

                    sprintf(TmpBuf, "AT+QICSGP=1,\"%s\"\r", GprsCtrlInfo.Para.APN);
                    ATCmdSend(TmpBuf, 2000);
                    SubState(AT_FTP_APN_WAIT);
                    break;
                case AT_FTP_APN_WAIT:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_FTP_USR);
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_FTP_APN);
                    }
                    break;
                case AT_FTP_USR:
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_FAIL);
                        break;
                    }
                    FtpInf.FtpOK = FALSE;
                    GprsCtrlInfo.Module.Bits.Ftping = TRUE;

                    sprintf(TmpBuf, "AT+QFTPUSER=\"%s\"\r", FtpInf.Usr);
                    ATCmdSend(TmpBuf, 2000);
                    SubState(AT_FTP_USR_WAIT);
                    break;
                case AT_FTP_USR_WAIT:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_FTP_PWD);
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_FTP_USR);
                    }
                    break; 
                case AT_FTP_PWD:
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_FAIL);
                        break;
                    }
                    sprintf(TmpBuf, "AT+QFTPPASS=\"%s\"\r", FtpInf.Pwd);
                    ATCmdSend(TmpBuf, 2000);
                    SubState(AT_FTP_PWD_WAIT);
                    break;
                case AT_FTP_PWD_WAIT:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_FTP_OPEN);
                        break;
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_FTP_PWD);
                        break;
                    }
                    break;     
                case AT_FTP_OPEN:                    
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_FAIL);
                        break;
                    }
                    sprintf(TmpBuf, "AT+QFTPOPEN=\"%s\",%d\r", FtpInf.Domain, FtpInf.Port);
                    ATCmdSend(TmpBuf, 15000);
                    SubState(AT_FTP_OPEN_WAIT);
                    break;
                case AT_FTP_OPEN_WAIT:
                    if(IsOK() && GprsCtrlInfo.Rlst2.Bits.FTP_OPEN) {
                        RetryCntSet(0);
                        SubState(AT_FTP_CFG);
                        break;
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_FTP_OPEN);
                        break;
                    }
                    break; 
                case AT_FTP_CFG:
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_FAIL);
                        break;
                    }
                    ATCmdSend("AT+QFTPCFG=2,0\r", 1500);
                    SubState(AT_FTP_CFG_WAIT);
                    break;
                case AT_FTP_CFG_WAIT:
                    if(IsOK() && GprsCtrlInfo.Rlst2.Bits.FTP_CFG) {
                        RetryCntSet(0);
                        SubState(AT_FTP_PATH);
                        break;
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_FTP_CFG);
                        break;
                    }
                    break;   
                case AT_FTP_PATH:
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_FAIL);
                        break;
                    }
                    sprintf(TmpBuf, "AT+QFTPPATH=\"%s\"\r", FtpInf.Path);
                    ATCmdSend(TmpBuf, 2000);
                    SubState(AT_FTP_PATH_WAIT);
                    break;
                case AT_FTP_PATH_WAIT:
                    if(IsTimeOut()) {
                        if(IsOK() && GprsCtrlInfo.Rlst2.Bits.FTP_PATH) {
                            RetryCntSet(0);
                            SubState(AT_FTP_SIZE);
                        } else {
                            SubState(AT_FTP_PATH);
                        }
                    }                  
                    break;
                case AT_FTP_SIZE:
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_FAIL);
                        break;
                    }     
                    sprintf(TmpBuf, "AT+QFTPSIZE=\"%s\"\r", FtpInf.FileName);
                    ATCmdSend(TmpBuf, 2000);
                    SubState(AT_FTP_SIZE_WAIT);
                    break;
                case AT_FTP_SIZE_WAIT:
                    if(IsOK() && GprsCtrlInfo.Rlst2.Bits.FTP_SIZE) {
                        if(GprsCtrlInfo.FtpSizeVal < 0) {
                            DebugMsg(DEBUG_GPRS, "FTPSIZE Err %d\r\n", GprsCtrlInfo.FtpSizeVal);
                            SubState(AT_FTP_SIZE);
                            break;
                        }
                        FtpInf.FileSize = GprsCtrlInfo.FtpSizeVal;
                        RetryCntSet(0);
                        SubState(AT_SET_FLOW_CTRL);
                    }
                    else if(IsTimeOut()) {
                        SubState(AT_FTP_SIZE);
                    }
                    break;                   
               
                case AT_SET_FLOW_CTRL:
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_FAIL);
                        break;
                    }
                    ATCmdSend("AT+IFC=2,2\r", 1500);
                    SubState(AT_SET_FLOW_CTRL_WAIT);
                    break;
                case AT_SET_FLOW_CTRL_WAIT:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_FTP_GET_FILE);
                    }
                    else if(IsTimeOut() || IsErr()) {
                        SubState(AT_SET_FLOW_CTRL);
                    }
                    break;
                    
                case AT_FTP_GET_FILE:
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_FAIL);
                        break;
                    }
                    
                    sprintf(TmpBuf, "AT+QFTPGET=\"%s\"\r", FtpInf.FileName);
                    ATCmdSend(TmpBuf, 20000);                //  20s
                    SubState(AT_FTP_GET_FILE_WAIT);
                    break;
                case AT_FTP_GET_FILE_WAIT:
                    if(IsOK() && GprsCtrlInfo.Rlst2.Bits.FTP_CONNECT) {
                        RetryCntSet(0);
//                        ATCmdSend(NULL, 120000);             //  2min
                        SubState(AT_FTP_GET_FILE_FINISH);
                    } else if(GprsCtrlInfo.Rlst2.Bits.FTP_GET) {
                        DebugMsg(DEBUG_GPRS, "Ftp Get Err: %d\r\n", GprsCtrlInfo.FtpGetVal);
                        SubState(AT_FTP_GET_FILE);
                    } else if(IsErr() || IsTimeOut()){
                        SubState(AT_FTP_GET_FILE);
                    } 
                    break; 
                case AT_FTP_GET_FILE_FINISH:
                    if(FtpInf.FileGetFinish) {
                        FtpInf.FileGetFinish = FALSE;
                        DebugMsg(DEBUG_GPRS, "Ftp get %s size %d\r\n", FtpInf.FileName, FtpInf.FileSize);
                        ATCmdSend(NULL, 3000);
                        SubState(AT_FTP_GET_RESULT);
                    } else if(IsTimeOut()) {
                        DebugMsg(DEBUG_GPRS, "Ftp get file %s time out\r\n", FtpInf.FileName);
                        SubState(AT_FTP_FAIL);
                    }
                    break;
                case AT_FTP_GET_RESULT:
                    if(GprsCtrlInfo.Rlst2.Bits.FTP_GET) {
                        GprsCtrlInfo.Rlst2.Bits.FTP_GET = FALSE;                        
                        if(FtpInf.FileSize == GprsCtrlInfo.FtpGetVal) {
                            FtpInf.FtpOK = TRUE;
                            SubState(AT_FTP_SUCCESS);
                        }
                    } else if(IsTimeOut()) {
                        SubState(AT_FTP_FAIL);
                    }
                    break;
                case AT_FTP_SUCCESS:
                    DebugMsg(DEBUG_GPRS, "File get success\r\n");
                    SubState(AT_CLR_FLOW_CTRL);
                    break;
                    
                case AT_FTP_FAIL:
                    DebugMsg(DEBUG_GPRS, "FTP fail\r\n");
                    SubState(AT_CLR_FLOW_CTRL);
                    break;  
                    
                case AT_CLR_FLOW_CTRL:
                    if(GprsCtrlInfo.RetryCnt++ >= 3) {
                        SubState(AT_FTP_CLOSE);
                        break;
                    }
                    ATCmdSend("AT+IFC=0,0\r", 1500);
                    SubState(AT_CLR_FLOW_CTRL_WAIT);
                    break;
                case AT_CLR_FLOW_CTRL_WAIT:
                    if(IsOK()) {
                        RetryCntSet(0);
                        SubState(AT_FTP_CLOSE);
                    }
                    else if(IsTimeOut() || IsErr()) {
                        SubState(AT_CLR_FLOW_CTRL);
                    }
                    break;
                    
                case AT_FTP_CLOSE:
                    ATCmdSend("AT+QFTPCLOSE\r", 1000);
                    SubState(AT_FTP_CLOSE_WAIT);
                    break;
                case AT_FTP_CLOSE_WAIT:
                    if(IsOK() || IsTimeOut()) {
                        if(IsTimeOut()) {
                            DebugMsg(DEBUG_GPRS, "Ftp close timeout\r\n");
                        }
                        GprsCtrlInfo.Module.Bits.Ftping = FALSE;                    
                        ReturnToInserStage();
                    }
                    break;                    
                default:
                    SubState(AT_FTP_USR);
                    break;
            }
            break;
#endif

#if GPRS_DATA_EN
        case AT_PPP_CLOSE:
            switch(GprsCtrlInfo.SubState) {
                case AT_ClosePPP:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {
                        SubState(AT_PPPCloseFail); 
                    } else {
                        GprsCtrlInfo.Module.Bits.Connect_1 = FALSE; //  清标识
                        ATCmdSend("AT+QICLOSE=1\r", 2000);
                        SubState(AT_ClosePPPWait); 
                    }
                    break;
                    
                case AT_ClosePPPWait:
                    if(GprsCtrlInfo.Rlst.Bits.Close_OK) {
                        RetryCntSet(0);                        
                        if(GprsCtrlInfo.Reqult.Bits.ReAPN) {
                            SubState(AT_QIDEACT);
                        } else {                           
                            SubState(AT_PPPCloseOK); 
                        }
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_ClosePPP);
                    }
                    break;    
                case AT_QIDEACT:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {
                        SubState(AT_PPPCloseFail); 
                    } else {
                        ATCmdSend("AT+QIDEACT\r", 15000);
                        SubState(AT_QIDEACTWait); 
                    }
                    break;
                    
                case AT_QIDEACTWait:
                    if(GprsCtrlInfo.Rlst.Bits.DEACT_OK) {
                        RetryCntSet(0);    
                        SubState(AT_PPPCloseOK);
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_QIDEACT);
                    }
                    break;
                    
                case AT_PPPCloseFail:
                    TransTo(AT_None, AT_None);
                    break;
                case AT_PPPCloseOK:
                    if(GprsCtrlInfo.Reqult.Bits.ReAPN) {
                        GprsCtrlInfo.Reqult.Bits.ReAPN = FALSE;
                        GprsCtrlInfo.Reqult.Bits.Connect = TRUE;
                    }     
                    TransTo(AT_Standby, AT_None); 
                    break;
                default:
                    SubState(AT_ClosePPP);
                    break;
            }
            break;    
#endif    
//#if 0            
//        case AT_HANG:
//            switch(GprsCtrlInfo.SubState) {
//                case AT_ATH:
//                    if(GprsCtrlInfo.RetryCnt++ > 3) {
////                        SpecialCmdResp(RESP_HANG, "ERROR");
//                        DebugMsg(DEBUG_GPRS, "ATH Fail\r\n");
//                        SubState(AT_ATHFail); 
//                    } else {
//                        if(GprsCtrlInfo.Module.Bits.Ring || GprsCtrlInfo.Module.Bits.Dailing) {
//                            ATCmdSend("ATH\r", 1000);
//                            SubState(AT_ATHWait); 
//                        } else {
//                            SubState(AT_ATHOK_Wait); 
//                        }                        
//                    }
//                    break;
//                case AT_ATHWait:
//                    if(IsOK()) {                                                   
//                        ATCmdSend(NULL, 2000);
//                        GprsCtrlInfo.Module.Bits.Ring = FALSE;
//                        GprsCtrlInfo.Module.Bits.Dailing = FALSE;
//                        if(GprsCtrlInfo.Reqult.Bits.UART_DAIL || GprsCtrlInfo.Reqult.Bits.UART_HANG) {
////                                SpecialCmdResp(RESP_HANG, "OK");
//                            DebugMsg(DEBUG_GPRS, "ATH OK\r\n");
//                        }
//                        SubState(AT_ATHOK_Wait);                        
//                    } else if(IsErr() || IsTimeOut()) {
//                        SubState(AT_ATH);
//                    }
//                    break;
//                case AT_ATHOK_Wait:                    
//                    ReturnToInserStage();

//#if GPRS_DATA_EN                
//                    if(gprsIsConnect()) {
////                        GprsCtrlInfo.HeartTimer = MAX_HEART_INTERVAL * 1000;//立即发心跳  
//                    }
//#endif                    
//                    break;
//                case AT_ATHFail:
//                    TransTo(AT_None, AT_None);
//                    break;
//                default:
//                    GprsCtrlInfo.SubState = AT_ATH;
//                    break;
//            }
//            break;
//#endif
        case AT_CNUM:
             switch(GprsCtrlInfo.SubState) {
                case AT_CNUM_CMD:
                    if(GprsCtrlInfo.RetryCnt++ > 3) {
                        SubState(AT_CNUM_FAIL); 
                    } else {
                        memset(GprsCtrlInfo.TelNum, 0, sizeof(GprsCtrlInfo.TelNum));
                        ATCmdSend("AT+CNUM\r", 1000);
                        SubState(AT_CNUM_WAIT); 
                    }
                    break;
                case AT_CNUM_WAIT:                    
                    if(IsOK()) {    
                        if(0 != GprsCtrlInfo.TelNum[0]) {
//                            SpecialCmdResp(RESP_CNUM, GprsCtrlInfo.TelNum);
                            DebugMsg(DEBUG_GPRS, "TelNum %s\r\n", GprsCtrlInfo.TelNum);
                        } else {
//                            SpecialCmdResp(RESP_CNUM, NULL);
                        }                        
                        ReturnToInserStage();
                    } else if(IsErr() || IsTimeOut()) {
                        SubState(AT_CNUM_CMD);
                    }
                    break;
                case AT_CNUM_FAIL:
//                    SpecialCmdResp(RESP_CNUM, NULL);                    //  失败不重启模块
                    ReturnToInserStage();
                    break;    
                default:
                    GprsCtrlInfo.SubState = AT_CNUM_CMD;
                    break;
             }   
            break;
        case AT_POWEROFF:
            switch(GprsCtrlInfo.SubState) {
                case AT_POWER_DELAY:
                    ATCmdSend(NULL, 3000);
                    SubState(AT_POWER_OFF_EXIT);
                    break;
                case AT_POWER_OFF_EXIT:
                    if(IsTimeOut()) {
                        GPRS_POWER_OFF();                        
                        DebugMsg(DEBUG_GPRS, "Power off\r\n");
                        TransTo(AT_TEST, AT_None);
                    }
                    break;
                default:
                    SubState(AT_POWER_DELAY);
                    break;
            }            
            break;
            
        case AT_TEST:
            break;    
            
        default:
            TransTo(AT_None, AT_None);
            break;
    }  
}


void GprsReadQeng(char* pBuf)
{
    char *pPser =NULL;
    u8 i = 0, j = 0;
        
    while((*pBuf != ':')&&(i <= 10))
    {
            pBuf++;
            i++;
    }
    pBuf++;pBuf++;
    
    if(*pBuf == '0')
    {
        pPser = strtok(pBuf, ",");
        for(i=0; i<10; i++)
        {
            pPser = strtok(NULL, ",");
            switch(i)
            {
                case 0x02 : 
                {
                    if(((*pPser >= '0') && (*pPser <= '9') ) || ((*pPser >= 'a') && (*pPser <= 'f')))
                    {
                        memcpy(GprsCtrlInfo.MultLoc[0].lac, pPser, 4);
                        GprsCtrlInfo.MultLoc[0].lac[4] = 0;
                    }
                    break;
                }
                case 0x03 : 
                {
                    if(((*pPser >= '0') && (*pPser <= '9') ) || ((*pPser >= 'a') && (*pPser <= 'f')))
                    {
                        memcpy(GprsCtrlInfo.MultLoc[0].ci, pPser, 4);
                        GprsCtrlInfo.MultLoc[0].ci[4] = 0;
                    }
                    break;
                }
                case 0x06 : 
                {
                    if((*(pPser+1) >= '0') && (*(pPser+1)  <= '9') ) 
                    {
                        GprsCtrlInfo.MultLoc[0].csq = (unsigned char)ATstrToInt32U(pPser,4);
                    }
                    break;
                }
                default: break;
            }
        }
            
    }
    else if(*pBuf == '1')
    {
        pPser = strtok(pBuf, ",");
        for(i=1; i<6; i++)
        {            
            for(j=0; j<10; j++)
            {
                pPser = strtok(NULL, ",");
                if(NULL != pPser)
                switch(j)
                {
                    case 0x02 : 
                    {
                        if((*(pPser+1) >= '0') && (*(pPser+1)  <= '9') ) 
                        {
                            GprsCtrlInfo.MultLoc[i].csq = (unsigned char)ATstrToInt32U(pPser,4);
                        }
                        break;
                    }
                    case 0x08 : 
                    {
                        if(((*pPser >= '0') && (*pPser <= '9') ) || ((*pPser >= 'a') && (*pPser <= 'f')))
                        {
                            memcpy(GprsCtrlInfo.MultLoc[i].lac, pPser, 4);
                            GprsCtrlInfo.MultLoc[i].lac[4] = 0;
                        }
                        break;
                    }
                    case 0x09 : 
                    {
                        if(((*pPser >= '0') && (*pPser <= '9') ) || ((*pPser >= 'a') && (*pPser <= 'f')))
                        {
                            memcpy(GprsCtrlInfo.MultLoc[i].ci, pPser, 4);
                            GprsCtrlInfo.MultLoc[i].ci[4] = 0;
                        }
                        break;
                    }
                    
                    default: break;
                }
            }
        }
    }
    else
    {
        
    }
    
}



u16 GetMultLoc(u8 Type,u8 Num)
{
    u16 temp = 0;
    
    if((Type == 0x01) && (Num <=5))
    {
        temp = StringToHex(GprsCtrlInfo.MultLoc[Num].lac, 2);
    }
    else if((Type == 0x02) && (Num <=5) )
    {
        temp = StringToHex(GprsCtrlInfo.MultLoc[Num].ci, 2);
    }
    else if((Type == 0x03) && (Num <=5) )
    {
        if((GprsCtrlInfo.MultLoc[Num].csq > 50) && (GprsCtrlInfo.MultLoc[Num].csq < 114))
            temp = GprsCtrlInfo.MultLoc[Num].csq;
    }
    
    return temp;
}
