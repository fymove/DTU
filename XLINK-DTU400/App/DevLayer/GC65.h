#ifndef _GC65_H_
#define    _GC65_H_

#ifndef _InGprs
#define    GprsExt    extern
#else
#define    GprsExt
#endif


#include "gprscfg.h"
#include "gc65_bsp.h"

//#include "ucos_ii.h"
#include "struct.h"


GprsExt char GprsRcvBuf[GPRS_RCV_PIPE_CNT][GPRS_RCV_PIPE_SIZ];
GprsExt char GprsSndBuf[GPRS_SND_PIPE_CNT][GPRS_SND_PIPE_SIZ];
GprsExt char ATRespBuf[AT_RESP_PIPE_CNT][AT_RESP_PIPE_SIZ];
GprsExt char ATSendBuf[AT_SEND_PIPE_CNT][AT_SEND_PIPE_SIZ];

//GprsExt void *pGprsRcv;
GprsExt void *pGprsSnd;
GprsExt void *pSMSRcv;
GprsExt void *pSMSSnd;
#ifdef USE_DTU_SND_PIPE
GprsExt void *pDtuSnd;
#endif
#ifdef USE_DTU_RCV_PIPE
GprsExt void *pDtuRcv;
#else
GprsExt char dtuDataRcvFlag;
#endif
GprsExt void *pATResp;
GprsExt void *pATSend;


//extern char *pToGprs;

#if GPRS_DATA_EN
typedef struct {
    char *APN;
    char *USR;
    char *PWD;
    u16 *pInterval;
    u16 *pPort;
    char *pDomain;    
}GC65_PARA_STRUCT;

#if URGEN_SND_Q_SIZE
GprsExt OS_EVENT *QEventUrgenSnd; 
GprsExt void    UrgenDataPost(char *pBuf, unsigned short Len);
#endif
GprsExt OS_EVENT *QEventGprsSnd; 
GprsExt OS_EVENT *pGprsRcv;
GprsExt char    gprsIsConnect(void);
#endif


#if GPRS_CSQ_EN
typedef struct {
    u8  Value;
    u16 TimeCnt;
    u16 MaxTime;
}GPRS_CSQ_STRUCT;
#endif

#if GPRS_LOC_EN
typedef struct {
    char lac[5];
    char ci[5];
}GPRS_LOC_STRUCT;
#endif

typedef struct {
    char lac[5];
    char ci[5];
    char csq;
}GPRS_MULT_LOC_STRUCT;


typedef enum {
    STANDARD_GSM_UNK = 0,
    STANDARD_GSM_YD,
    STANDARD_GSM_LT,
    STANDARD_GSM_DX    
}STANDARD_ENUM;

typedef enum {
    AT_None = 0,        //无                    0
    
    AT_PWR_CTRL,                        //    1
        AT_Power_off,       //关电等待    //    2
        AT_Power_off_wait,                //    3
        AT_Power_on,        //开电        //    4
        AT_Power_on_wait,                //    5
        AT_Switch_on,        //开机
        AT_Switch_on_Wait,                //    7
        AT_PWR_CTRL_ok,
        AT_PWR_CTRL_fail,                //    9
        
    AT_MDL_INIT,                        //    10
        AT_Init,
        AT_Init_Wait,                    //    12
        AT_Init_Ok,
        AT_Init_Fail,                    //    14
        
    AT_PROP_CHECK,    //    相关属性查询        //    15
        AT_QueryCGSN,                    //    16
        AT_QueryWaitCGSN,        
        AT_QueryCPIN,                    //    18
        AT_QueryWaitCPIN,
        AT_QueryCIMI,                    //    20
        AT_QueryWaitCIMI,        
        AT_QueryCCID,                    //    
        AT_QueryWaitCCID,
        AT_PROP_OK,                        //    
        AT_PROP_FAIL,
    
    AT_Station_Reg,                        //                                                            
        AT_QueryCREG,           //查询Reg
        AT_QueryWaitCREG,                //        
        AT_QueryCGREG,          //查询Greg
        AT_QueryWaitCGREG,              //    
        AT_Station_Reg_OK,
        AT_Station_Reg_Fail,            //    
    
    AT_PPP,                                //    
        AT_SetAPN,          //设置APN
        AT_SetAPNWait,      //等待APN成功    //    
        AT_StartTask,       //启动任务
        AT_StartTaskWait,   //启动任务等待
        AT_SetCIICR,        //启动场景
        AT_SetCIICRWait,    //等待场景激活,返回OK 激活    
        AT_GetIP,           //获取本地IP
        AT_GetIPWait,       //等待获取IP 成功
        AT_DNSCFG,
        AT_DNSCFGWait,
        AT_GetDNSIP,
        AT_GetDNSIPWait,
        AT_PPP_Fail,
        AT_PPP_OK,                        //                

    AT_PPP_CLOSE,                        //    
        AT_ClosePPP,
        AT_ClosePPPWait,                //  
        AT_QIDEACT,
        AT_QIDEACTWait,                 //  
        AT_PPPCloseFail,
        AT_PPPCloseOK,                  //  

    AT_CONNECT_SERVER,                    //    
        AT_ConnectTypeSet,
        AT_ConnectTypeWait,                //    
        AT_ConnectSvr,
        AT_SetConnect_Wait, //等待TCP连接成功        
        AT_ConnectFail,                    //    
        
    AT_Standby,                          //    56          
    
    AT_SendData,                        //    57
        AT_SetSendDATA,
        AT_Send_cmdwait,                //    59
        AT_WAIT_SERVER_RESP,
        AT_Send_DATA_Wait,
        AT_SendDataFail,                //    61
        
    AT_FILE_FTP_SEND,
        AT_FTP_IPGCNT,
        AT_FTP_IPGCNT_WAIT,
        AT_FTP_APN,
        AT_FTP_APN_WAIT,
        AT_FTP_USR,
        AT_FTP_USR_WAIT,
        AT_FTP_PWD,
        AT_FTP_PWD_WAIT,
        AT_FTP_OPEN,
        AT_FTP_OPEN_WAIT,
        AT_FTP_PATH,
        AT_FTP_PATH_WAIT,
        AT_FTP_SIZE,
        AT_FTP_SIZE_WAIT,
        AT_FTP_CFG,
        AT_FTP_CFG_WAIT,

        AT_SET_FLOW_CTRL,
        AT_SET_FLOW_CTRL_WAIT,
        AT_FTP_GET_RESULT,
        AT_CLR_FLOW_CTRL,
        AT_CLR_FLOW_CTRL_WAIT,
    
        AT_FTP_GET_FILE,
        AT_FTP_GET_FILE_WAIT,
        AT_FTP_GET_FILE_FINISH,
        AT_FTP_GETING,
        AT_FTP_FILE_CRC,
        AT_FTP_GET_FILE_OK,

        
        AT_FTP_DELETE,
        AT_FTP_DELETE_WAIT,
        AT_FIP_FILE_SIZE,
        AT_FTP_SEND_CMD,
        AT_FTP_SEND_CMD_WAIT,
        AT_FTP_SEND_DATA,
        AT_FTP_SEND_END,
        AT_FTP_SEND_END_WAIT,
        AT_FTP_CLOSE,
        AT_FTP_CLOSE_WAIT,
//        AT_FTP_EXIT_SEND,
//        AT_FTP_EXIT_SEND_WAIT,
        AT_FTP_SUCCESS_WAIT,
        AT_FTP_SUCCESS,
        AT_FTP_FAIL,        
        
   
    
    AT_SendAT,                            //    75
        AT_USER_AT_CMD,
        AT_USER_AT_CMD_WAIT,            //    77

    AT_CSQ,                                //    78
        AT_QueryCSQ,           //查询CSQ
        AT_QueryWaitCSQ,                //    80

    AT_REG,                                //    81  查询基站信息
        AT_QueryREG,           
        AT_QueryWaitREG,                //    83

    AT_HANG,                            //  84
        AT_ATH,
        AT_ATHWait,                     //  86
        AT_ATHOK_Wait,
        AT_ATHFail,                     //  88

    AT_CNUM,
        AT_CNUM_CMD,
        AT_CNUM_WAIT,
        AT_CNUM_FAIL,

    AT_DAIL,
        AT_DAIL_CMD,
        AT_DAIL_WAIT,
        AT_DAIL_WAIT_WAIT,
        AT_DAILIIND,
        AT_DAIL_HANG,
        AT_DAIL_HANG_WAIT,
        AT_DAIL_FAIL,                   //  100
    AT_POWEROFF,
        AT_POWER_DELAY,
        AT_POWER_OFF_EXIT,
        
        AT_SQIMode,
        AT_SQIModeWait,
        AT_SQITCFG,
        AT_SQITCFGWait,
        AT_QIFGCNT,
        AT_QIFGCNTWait,
                
    AT_TEST,
}AT_Model_Stage;

typedef union {
    int Flag;
    struct {
        int IMEI:      1;
        int CIMI:      1;            
        int IP:       1;
        int AT:       1;            
        int Money:    1;    
        int YECX_WAITING:  1;                                       //  余额查询中，等待查询应答短信
        int CloseGprs:1;                                            //  关闭GPRS
        int Connect:  1;                                            //  连接GPRS

        int CSQ:      1;
        int UART_CSQ: 1;                                          //  串口方式查询CSQ
        int GPRS_CSQ: 1;                                          //  GPRS方式查询CSQ
        int SMS_CSQ:  1;                                          //  短信方式查询CSQ            
        int REG:      1;
        int UART_REG: 1;
        int GPRS_REG: 1;
        int SMS_REG:  1;

        int CNUM:      1;
        int GPRS_CNUM: 1;
        int UART_CNUM: 1;
        int SMS_CNUM:   1;            
        int YECX:      1;
        int GPRS_YECX: 1;
        int UART_YECX: 1;            
        int SMS_YECX:  1;

        
        int ReAPN:    1;
        int ReAPNDly: 1;             
        int HANG:     1;
        int UART_HANG: 1;
        int DAIL:      1;
        int UART_DAIL: 1;
        int FTP_CONNECT: 1;
        int DNS: 1;
    }Bits;
}GPRS_REQULT_UNION;

typedef union {
    int Flag;
    struct {
        //标准结果码
        int OK:1;             //结果码
        int ERROR:1;          //结果码
        int NO_CARRIER:1;     //结果码
        int CONNECT:1;        //结果码
        int RING:1;           //结果码

        //自定义结果码
//        int SIM_OK:1;        //SIM卡准备好
        int CIMI:1;       //查询CIMI完成
        int CSQ_OK:1;       //查询信号
        int CREG_OK:1;          //GSM注册
        int CGREG_OK:1;         //GPRS注册
        int DNS_OK: 1;
        int PPP_OK:1;           //拨号成功
        int CON_SVR_OK:1;       //连上服务器

        int RD_IMEI_OK:1;        //读取IMEI号

        int GPRS_SEND_FINISH:1;
        int GPRS_SEND_RLST: 1;
        int SvrCnntRlst: 1;
        int DEACT_OK:1;
        int    Ready: 1;
        int SMS_OK: 1;
        int SMS_Restart: 1;
//        int CME_ERROR: 1;
        int CNUM_OK: 1;
	    int CCID_OK:1;
        int Close_OK: 1;
    } Bits;
}GPRS_RLST_UNION; 

typedef union {
    int Status;
    struct {
        //标准结果码
        int Ppp:1;          //  拨号上网状态，0:拨号未成功，1:拨号成功
        int Connect_1:1;    //  服务器连接状态，0:连接失败，1:成功
        int SIMOK:1;        //  SIM准备好
        int NoSIM: 1;       //  未插SIM卡
        int SIMErr: 1;
        int CREG: 1;                                                //  已注册基站

        int Roam:1;                                                 //  漫游
        int Ring: 1;
        int Standard:4;                                                //  0:未知1:移动    2:联通3:电信  

        //  状态码
        int CntClose: 1;                                            //  连接断开状态            

        int Dailing: 1;

        int DataSendOK: 1;
        int SMSing: 1;      //  1: 短信发送中  0: 未发短信

        int Ftping:1;      
    } Bits;
}GPRS_MODULE_UNION;

typedef enum {
    GC65_ERR_NONE = 0,     //  显示检测中
    GC65_ERR_AT,           //  模块通信异常     1
    GC65_ERR_NOSIM,        //  无SIM卡          2
    GC65_ERR_SIMERR,       //  SIM卡激活失败    3
    GC65_ERR_GSM,          //  无法连接基站     4
    GC65_ERR_GPRSNET,      //  无法连接GPRS网络 5
    GC65_ERR_PPP,          //  拨号失败         6
    GC65_ERR_CONNTCT_SVR,  //  连接服务器失败   7
    GC65_CONNECT_SVR_OK,   //  连接服务器成功   8
    GC65_OK,               //  设备通信正常     9

    //  前面的顺序不能改变,与触摸屏相关,过程事件的错误码添加在之后
    GC65_ERR_SVR_CLOSE,    //                   10
    GC65_ERR_SVR_NORESP,   //                   11
    GC65_ERR_PDP_DEACT,    //                   12
}GC65_ERR_ENUM;

#if GPRS_FTP_EN
typedef    union {
    u16 Flag;
    struct {
        u16 FTP_OPEN: 1;
        u16 FTP_PATH: 1;
        u16 FTP_SIZE: 1;
        u16 FTP_CFG: 1;
        u16 FTP_GETOVER: 1;
        u16 FTP_DELETE:  1;
        u16 FTP_CONNECT: 1;
        u16 FTP_SUCCESS: 1;
        u16 FTP_ERROR: 1;      
        u16 FTP_GET: 1;
    }Bits;
}FTP_RLST_UNION;

typedef struct {
    char Domain[32];                                                //  服务器信息
    u16  Port;
    char Usr[10];                                                   //  用户名
    char Pwd[16];                                                   //  密码
    char Path[10];                                                  //  路径
    char FileName[30];                                              //  文件名
    u32  FileSize;                                                  //  文件大小

    u32  FileCrc;                                                   //  文件CRC

    u32  CurGetSize;                                                //  当前获取字节数
    u32  AllGetSize;                                                //  所有获取字节数

    u32  BeginAddr;
    u32  WriteAddr;
    char FtpOK;
    u8  FileGetFinish;
//    u8  FileSizeOK;

    struct {
        u8  Ftping: 1;
        u8  Cancel: 1;
    }Bits;     
}FTP_INFO_STRUCT;
GprsExt FTP_INFO_STRUCT FtpInf;
#endif


//----------------GPRS模块连接服务器控制参数结构体---------------
typedef struct {   
#if GPRS_FTP_EN
    FTP_RLST_UNION    Rlst2;
    int FtpSizeVal;                                                 //  FTP GET SIZE Return value
    int FtpGetVal;
#endif        

    GPRS_REQULT_UNION Reqult;
    GPRS_RLST_UNION Rlst;
    GPRS_MODULE_UNION Module;
    
    char blTimeOut;
    int TmrMsCnt;
    int RetryCnt;  

    char CREG;
    char CGREG;
    char RingCnt;  
    
    char IP[16];
    char IMEI[16];
    char CIMI[16];
    char TelNum[15];
    char RingNum[15];
	char CCID[21];
    char NoRespCnt;                                                 //  模块无应答计次
    short ReAPNDelay;
    
    GC65_ERR_ENUM ErrCode;

    AT_Model_Stage MainState;
    AT_Model_Stage SubState;
    AT_Model_Stage ErrSubState;
    AT_Model_Stage WaitMainState;
    AT_Model_Stage WaitSubState;
    int    WaitRertyCnt;
#if GPRS_CSQ_EN    
    GPRS_CSQ_STRUCT CSQInf;
#endif    
#if GPRS_LOC_EN
    GPRS_LOC_STRUCT LocInf;
#endif  
    GPRS_MULT_LOC_STRUCT MultLoc[6];

#if GPRS_DATA_EN
    DELAY_TIMER DlyReConnect;
    DELAY_TIMER DlyRePPP;
    GC65_PARA_STRUCT Para;
#endif 
    u8 Connet_Fall_Num;
}GPRS_CTRL_STRUCT;

typedef struct {
    short Len;
    char  Buf[MDL_AT_RESP_LEN];
}AT_RESP_STRUCT;

typedef struct 
{
//    char Chnl;
    short Len;
    char  Buf[MAX_GPRS_BUF_SIZE];
}GPRS_RCV_BUF_STRUCT;

#define    PIPE_LEN_INFO_SIZE    2

#define MainState(mStag)        (GprsCtrlInfo.MainState = mStag)
#define    SubState(sStage)        (GprsCtrlInfo.SubState  = sStage)
#define    TransTo(mStag, sStage)    (GprsCtrlInfo.RetryCnt=0, MainState(mStag), SubState(sStage))
#define    RetryCntSet(Cnt)        (GprsCtrlInfo.RetryCnt = Cnt)
 
GprsExt OS_EVENT *QEventATResp;
GprsExt DTU_STATUS_INFO dtuStatus;
GprsExt GPRS_CTRL_STRUCT GprsCtrlInfo;

GprsExt void    GprsUartIsr(char dat);
GprsExt void    ATCmdParse(char *pCmd, unsigned short Len);

GprsExt void    GprsAppInit(void);
GprsExt void    TaskGC65(u16 cyc_ms);

GprsExt char    SendATCondition(void);
GprsExt void    GprsReConnect(void);
GprsExt void    DelayRePPP(u16 Nms);

GprsExt void    DelayReConnect(u16 Nms);

GprsExt void    GprsSndDataPost(char *pBuf, unsigned short Len, char Chnl);
GprsExt void    GprsSndDataFlush(void);
GprsExt void    FTPConnectRequestSet(void);
GprsExt u8  ModelIsFtping(void);
GprsExt char    FtpDataGetFlag(void);
GprsExt void GprsReadQeng(char* pBuf);
GprsExt u16 GetMultLoc(u8 Type,u8 Num);

#endif
