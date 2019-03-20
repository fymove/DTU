#ifndef _APP_PROTOCOL_H_
#define _APP_PROTOCOL_H_

#ifndef _InPro
#define ProExt  extern
#else
#define ProExt
#endif

#include "struct.h"
#include "app_rtc.h"

#define GPRS_PRO_HEAD_FLAG          0x2A
#define GPRS_PRO_END_FLAG           0x23

#define GPRS_PRO_VERSION            0x01                                                        //通信协议版本

#define PRO_MSGHEAD_SIZE            17                              //  消息头长度
#define PRO_BEFOR_MSGBODY_SIZE      21                              //  消息体之前的长度
#define PRO_MSGEND_CRC_SIZE         3                               //  CRC和消息尾的长度
#define PRO_MIN_SIZE                (PRO_BEFOR_MSGBODY_SIZE+PRO_MSGEND_CRC_SIZE)
 
//#define TERMINAL_GENERAL_ACK        0x0001                          //  终端通用应答

#define PRO_CMD_MASK                0x7ff
 
#define TERMINAL_REG                0x001                          //  终端注册
#define TERMINAL_REQ_RESP           0x801

#define TERMINAL_HEART              0x002                          //  终端心跳
#define TERMINAL_HEART_RESP         0x802

#define TERMINAL_TIME_PARA          0x003
#define TERMINAL_TIME_PARA_RESP     0x803

#define TERMINAL_STATUS_UPLOAD      0x004                        //数据有更新变化则主动上传
#define TERMINAL_STATUS_RESP        0x804

#define SERVER_GET_DEV_DATA         0x805                          //  获取终端数据
#define SERVER_GET_DEV_DATA_RESP    0x005

#define SERVER_SET_PARA             0x806                          //  参数设置
#define SERVER_SET_PARA_RESP        0x006

#define TERMINAL_EVENT_UPLOAD       0x007                          //  事件上传
#define TERMINAL_EVENT_RESP         0x807 


#define SERVER_VFD_OPT              0x811
#define SERVER_VFD_RESP             0x011

#define SERVER_CONTROL              0x812
#define SERVER_CONTROL_RESP         0x012



#define SERVER_UPDATE_REQUEST       0x813                          //  升级请求
#define TERMINAL_UPDATE_RESP        0x013                          //  获取升级数据包
#define TERMINAL_UPDATE              0x050                             //  获取升级数据包

#define TERMINAL_UPDATE_Result      0x014                          //  获取升级数据包

#define SERVER_DOMAIN_CFG              0x815                          //服务器域名端口重定向


#define SERVER_MSG_PUSH        		0X816    //系统消息推送
#define SERVER_MSG_PUSH_RESP   		0X016    //系统消息推送应答

#define HEARTDAT_RSP 1                                                                                        //心跳应答标识，1：需要应答，0：不需要应答

typedef enum {
    ACK_SUCCESS = 0,                                                //  成功
    ACK_FAIL,                                                       //  失败
    ACK_NOT_SUPPORT,                                                //  不支持
}ACK_ENUM;



typedef enum {
    EVENT_TYPE_NONE = 0,
    EVENT_TYPE_ALARM,                                               //  报警事件
    EVENT_TYPE_BOOT,                                                //  开机事件
    EVENT_TYPE_STOP,                                                //  停机事件
    EVENT_TYPE_RESET,                                               //  复位事件
}EVENT_TYPE_ENUM;

typedef enum {
    TRANS_TYPE_NONE = 0,
    TRANS_TYPE_UPDATE = 01,                                         //  远程升级结果
    TRANS_TYPE_SMS_RLS,                                             //  短信发送结果
    TRANS_TYPE_MAINVFD,                                             //  主机变频透传数据              
    TRANS_TYPE_FANVFD,                                              //  风机变频透传数据
    TRANS_TYPE_ALMSMS,                                              //  报警短信
    TRANS_TYPE_YECX,                                                //  余额查询短信
    TRANS_TYPE_ALMCLR,                                              //  报警清除
}TRANS_TYPE_ENUM;


typedef union {
    char Flag;
    struct {
        char Alarm: 1;                                              //  报警标识
        char Boot:  1;                                              //  开机标识
        char Stop:  1;                                              //  停机标识
        char Reset: 1;                                              //  重启标识
//      char Heart: 1;                                                //  心跳
    }Bits;  
}SYS_EVENT_UNION;

#pragma pack(1)
typedef struct {
    SYS_EVENT_UNION   Flag;                                      
    ALARM_FLAG_UNION  Alarm;                                        //  报警类型
    PREALM_FLAG_UNION PreAlarm;                                     //  预警类型
    DEVALM_FLAG_UNION DevAlarm;                                     //  预警类型
    RESET_TYPE_ENUM ResetType;                                      //  复位类型
//    u16 MainVfdAlmVal;                                            //  主机变频报警值
//    u16 FanVfdAlmVal;                                             //  风机变频报警值
    BOOT_TYPE_ENUM  BootType;                                       //  开机类型
    STOP_TYPE_ENUM  StopType;                                       //  停机类型
//    SYS_TIME_STRUCT PwrDwnTime;                                   //  掉电时间  
    OTHERS_ALM_FLAG_UNION OthersAlarm;                      // 其它报警类型
}SYS_EVENT_STRUCT;

typedef struct {
    ALARM_FLAG_UNION  Alarm;                                        //  报警屏蔽字
    ALARM_FLAG_UNION  AlmSnd;                                       //  不上传的位置0
    PREALM_FLAG_UNION PreAlarm;                                     //  预警屏蔽字
    DEVALM_FLAG_UNION DevAlarm;                                     //  设备状态事件
}ALARM_MASK_STRUCT;

#pragma pack()


ProExt SYS_EVENT_STRUCT    AlmStat;                                 //  报警状态,控制器实时值
ProExt SYS_EVENT_STRUCT    SysEvent;                                //  事件标识         
ProExt ALARM_MASK_STRUCT   AlmMask;                                 //  报警屏蔽


typedef struct {
    bool Flag;
    u8  Cnt;
}SMS_CNT_STRUCT;
ProExt SMS_CNT_STRUCT  SMSStatistics;

typedef union {
    u32 Flag;
    struct {
        u32 Send:   1;
        u32 Resend: 1;                                             //  网络参数修改后参数重传
        u32 Index : 6;
        u32 Timer: 24;
    }Bits;
}PARA_UPLOAD_UNION;
ProExt PARA_UPLOAD_UNION ParaUpload;

typedef union{
	u32 val;
	struct {
		u32  Rs485comstatus:	1;   // 485通信状态改变
		u32  Rs485ErrCnts:		1;	// Rs485通信错误次数
		u32  MatainAlarmVal:	1;	// 保养事件报警值
		u32  MachineState:		1;	// 机器状态运行状态改变
		u32	 Reserved:			28; //预留
		}Bits;
}PARA_UPDATE_UNION;
ProExt  PARA_UPDATE_UNION ParaUpdate;

ProExt bool GbUpLoadAllPara;
ProExt DELAY_TIMER RebootTime;

typedef union
{
	u32 val;
	struct {
			u32 flag:1;
			u32  timer:31 ; 
		}Bits;
}SysTimer;


ProExt SysTimer  InitParaUp;
ProExt bool GbeInitParaSend;





ProExt void    ClearHeartTimer(void);
ProExt void    ProSendInit(void);
ProExt void    DevStatToSystem(void);
ProExt void    Task_SvrComm(void);
ProExt void    GPRSDataDeal(char *pBuf);
ProExt void    GprsProtocolSend(u16 Nms);
ProExt char    IsReg(void);
ProExt void    RebootDelay(u16 Nms);
ProExt void   Task_ProDeal(void);
ProExt void Task_ProSend(u16 Nms);
ProExt char    isGprsCon(void);

ProExt void JSON_RtcTimeGet(char *pBuf);
ProExt void  GetNULLData(char *pBuf, u16 *pLen);
ProExt u32 RegDelay;            //  注册间隔时间                                
//ProExt bool ServerCmd_RtcAndPs_Deal(char **pBuf);
ProExt bool ServerCmd_Head_Deal(char **pBuf, u8 SetTimeFlag);
ProExt void    SetParaSaveFlag(u16 Addr);
#endif

