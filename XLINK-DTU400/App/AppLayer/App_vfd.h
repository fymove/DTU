/*
  ******************************************************************************
  * @文件    vfd_com.h 
  * @描述    vfd_com模块头文件
  ******************************************************************************
*/ 


#ifndef __VFD_COM_H
#define __VFD_COM_H


#ifndef _InVfd
#define VfdExt  extern
#else
#define VfdExt  
#endif

#include "typedef.h"
#include "app_cfg.h"
#include "bsp.h"


#define MODBUS_MASTER   1
#define MODBUS_SLAVE    0

#define USART_TX_ON       0x0008    //开启串口发送
#define USART_TX_OFF      0xFFF7    //关闭串口发送
#define USART_RX_ON       0x0004    //开启串口接收
#define USART_RX_OFF      0xFFFB    //关闭串口接收


typedef enum {
//    VFD_OPT_NONE = 0,
    VFD_OPT_READ = 0,
    VFD_OPT_READ_WAIT,
    VFD_OPT_WRITE,
    VFD_OPT_WRITE_WAITE,    
}VFD_OPT_ENUM;



#define VFD_RCV_BUF_SIZE        100                                 //  变频器接收缓存大小,考虑变频器透传数据
#define VFD_SND_BUF_SIZE        100                                 //  变频器发送缓存大小


#define  RS485_COMOK_CNTS   5
#define  RS485_COMERR_CNTS  10

typedef void (*pFun)(void);

typedef struct {
    union {
        char Flag;
        struct {
            char bMaster: 1;                                        //  主从标识
            char SndFlg: 1;                                         //  Modbus发送标识
            char RcvFlg: 1;                                         //  Modbus接收标识
            char RxStart: 1;                                        //  开始接收标识
        }Bits;
    }Stat;

    UART_COM_ENUM UartNum;                                          //  Modbus串口号
    u8  Addr;                                                       //  Modbus站号

//    u8  SndStep;
    u8  SndSize;                                                    //  Modbus数据发送长度
    u8  SndCnt;
    char SndBuf[VFD_SND_BUF_SIZE];                                  //  Modbus数据发送缓存

    u8   RcvCnt;                                                    //  Modbus数据接收长度
    char RcvBuf[VFD_RCV_BUF_SIZE];                                  //  Modbus数据接收缓存
    
    u16 RcvTimer;                                                   //  接收计时器
    u16 CharOvTimer;                                                //  字符接收超时时间,单位ms
    u16 PrtlOvTimer;                                                //  协议接收超时时间,单位ms
    
//    u16 ComErrCnt;                                                  //  通信异常计数器

#if RS485_SEND_DELAY
    struct {
        u16 Flag: 1;
        u16 Timer: 15;
    }DelayToRcv;
#endif

    pFun pChgToSnd;
    pFun pChgToRcv;
//    pFun pWaitSndFinish;
}MODBUS_HOST_STRUCT;

typedef struct {
    struct {
        u8  bReadMainVfd: 1;                                        //  1:读主机变频器数据

//        u8 NeedRsp: 1;                                              //  需要应答
//        u8 RcvRsp: 1;                                               //  接收到应答
//        u8 RspRlt: 1;                                               //  应答结果
//        u8 RspTimeOut: 1;                                           //  应答超时
    }Bits;


    u16 ReadIndex;                                                  //  读变频索引
    u16 ReadAddr;                                                   //  读地址

    u8  WaitRspCmd;                                                 //  应答命令
    u16 WaitRspAddr;                                                //  应答地址
    u8  OptLen;

    float MainVolt;
    float FanVolt;

    u8 Step;
    u8 Retry; 
//    u16 MainFreq;                                                   //  主机变频器设置频率
//    u16 FanFreq;                                                    //  分机变频器设置频率
}VFD_CTRL_STRCUT;
VfdExt VFD_CTRL_STRCUT VfdCtrl;
VfdExt VFD_CTRL_STRCUT MeterCtrl;
VfdExt VFD_CTRL_STRCUT Meter2Ctrl;


typedef struct {
    struct {
        char OptFlg: 1;                                             //  服务器操作标识
        char RspFlg: 1;                                             //  终端应答标识
        
        char Read:  1;                                              //  1:读操作   0: 写操作        
        char Type:  4;                                              //  1:操作主机 0: 操作风机 :3/4/5 控制器写密码
        
        char Opting: 1;                                             //  命令发送中
    }Bits;

    u16 Addr;                                                       //  地址
    u16 Data;                                                       //  地址对应值
}SERVER_VFD_OPT_STRUCT;


#define EVENT_FLAG_MODBUS   0x0001                                  //  Modbus数据接收超时判断
#define EVENT_FLAG_VFD      0x0004

#define STATUS_UNKNOW			  255
#define STOP_STATE                 0                                //  停止状态
#define MACHINE_ALARM              1                                   //机器报警
#define JIAZAI_DELAY_RUN_STATE     2                                //  加载延时状态
#define JIA_ZAI_RUN_STATE          3                                //  加载运行状态
#define KONG_ZAI_RUN_STATE         4                                //  空载运行状态
#define KONG_JIU_STOP_STATE        5                                //  空久休眠状态
#define STOP_DELAY_RUN_STATE       6                                //  停机延时状态
#define RUN_STATE				   7
VfdExt char GbEventFlag;
VfdExt bool VfdInitFlag;

VfdExt char GbMeterEventFlag;
VfdExt char GbMeter2EventFlag;

VfdExt  bool bRemoteBoot;                                           //  远程开机操作
VfdExt  bool bRemoteStop;                                           //  远程停机操作

typedef enum {
    VFD_WRITE = 0,
    VFD_READ,
}VFD_OPT;

typedef enum {
    VFD_FAN = 0,
    VFD_MAIN,
}VFD_TYPE_ENUM;

typedef enum {
    VFD_USE_REMOTE = 0,
//    VFD_USE_LEARN,
    VFD_USE_PARASET,
    VFD_USE_LOCAL,
}VFD_USE_ENUM;


typedef union {
    char Flag;
    struct {
        char Remote: 1;                                             //  1: 远程操作
//      char Learn:  1;                                             //  1: 自学习
        char ParSet: 1;                                             //  1: 参数设置
        char Local:  1;                                             //  1: 自控

        char Main: 1;                                               //  0: 操作风机 1: 操作主机 
        char Read:  1;                                              //  1: 读操作   0: 写操作
    }Bits;
}WHO_USE_ENUM;

VfdExt  WHO_USE_ENUM VfdWhoUse; 
VfdExt  WHO_USE_ENUM MeterWhoUse; 
VfdExt  WHO_USE_ENUM Meter2WhoUse; 


typedef union {
    char Flag;
    struct {
        char RcvRsp: 1;                                               //  接收到应答
        char RspRlt: 1;                                               //  应答结果
        char RspTimeOut: 1;                                           //  应答超时
    }Bits;        
}OPT_RLT_ENUM;

VfdExt  OPT_RLT_ENUM VfdOptRlt;  
VfdExt  OPT_RLT_ENUM MeterOptRlt;  
VfdExt  OPT_RLT_ENUM Meter2OptRlt; 


VfdExt  u16 VfdOptAddr;
VfdExt  void    VfdSetWhoUse(VFD_USE_ENUM Who, char bRead, char bMain, u16 Addr); 

VfdExt  u8  MainVfd_Addr;
VfdExt  SERVER_VFD_OPT_STRUCT   SvrVfdOpt;
VfdExt  MODBUS_HOST_STRUCT  RS4850Modbus;

VfdExt MODBUS_HOST_STRUCT  *pVfd;

VfdExt  MODBUS_HOST_STRUCT  RS4851Modbus;
VfdExt MODBUS_HOST_STRUCT  *pMeter;

VfdExt  MODBUS_HOST_STRUCT  RS4852Modbus;
VfdExt MODBUS_HOST_STRUCT  *pMeter2;


VfdExt bool    ModbusRcvCrcChk(MODBUS_HOST_STRUCT *pMdBus);
VfdExt char    ModbusRcvFinish(MODBUS_HOST_STRUCT *pMdBus);


VfdExt char    ModbusSendNextChar(MODBUS_HOST_STRUCT *pMdBus);
VfdExt void    ModbusUartIsr(MODBUS_HOST_STRUCT *pMdBus, char dat);


VfdExt bool    IsModbusMaster(MODBUS_HOST_STRUCT *pMdBus);
VfdExt char    ModbusRcvTimeOut(MODBUS_HOST_STRUCT *pMdBus/*, char *pErrType*/);
VfdExt void    ModbusOvTmInit(MODBUS_HOST_STRUCT *pMdBus, u16 CharOvTimer, u16 PrtlOvTimer);
VfdExt void    ModbusAddrInit(MODBUS_HOST_STRUCT *pMdBus, bool bMaster, UART_COM_ENUM UartNum, char NodeAddr);
VfdExt void    ModbusFunInit(MODBUS_HOST_STRUCT *pMdBus, pFun pChgToSnd,/* pFun pWaitSndOver,*/ pFun pChgToRcv);

VfdExt  void    ModbusStartSend(MODBUS_HOST_STRUCT *pMdBus);
void    ModbusDelayToRcv(MODBUS_HOST_STRUCT *pMdBus, u16 Nms);

VfdExt  void    Task_VfdInit(void);
VfdExt  void    Task_VfdDeal(void);
VfdExt  void    Task_VfdComm(MODBUS_HOST_STRUCT *pMdBus, u16 Nms);
VfdExt  void    VfdWriteMoreRegPacket(MODBUS_HOST_STRUCT *pMdBus, u16 Addr, u16 RegNum,u8 DataLen, u8 *Data);
VfdExt  void     Vfd_Meter_Write_Data(uint32_t Data);
VfdExt  void    RS485ComInit(void);
void    Task_MeterInit(void);
void    Task_MeterComm(MODBUS_HOST_STRUCT *pMdBus, u16 Nms);
void    Task_MeterDeal(void);
void  SetMeterReadIndex(void);

void    Task_Meter2Init(void);
void    Task_Meter2Comm(MODBUS_HOST_STRUCT *pMdBus, u16 Nms);
void    Task_Meter2Deal(void);
u8 DriveCan_sendData(u8 *sendData);
void CanBus_ISR_Rx(CanRxMsg *uCanRxMsg);

#endif


/*********************************** 文件结束 *********************************/
