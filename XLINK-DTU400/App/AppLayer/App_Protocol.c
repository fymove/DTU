#define _InPro
#include "app_protocol.h"
#include "includes.h"

extern bool g_b2mintues;
typedef enum
{
    NoneAck,
    bRegAck,
    RegAcked,
    bHeartAck,
    HeartAcked,
    bEvenAck,
    EventAcked,
    bSMSUploadAck,
    SMSUploadAcked,
    bSMSCntAck,
    SMSCntAcked,
    bGeneralAck,        //
    GeneralAcked,
    bTimeParaAck,
    TimeParaAcked,
    bTimeAdjust,
    TimeAdjusted,
    bUpdateAck,
    UpdateAcked,
    bStatusAck,
    StatusAcked

}PR_ACK_EN;

PR_ACK_EN Rsp = NoneAck;
PR_ACK_EN Ack = NoneAck;

typedef enum {
    PRO_STEP_START = 0,
    PRO_STEP_REG,
    PRO_STEP_SEND_DATA,
    PRO_STEP_TIME_PARA,
    PRO_STEP_HEART_INFO,
   	PRO_STEP_STATUS_UPLOAD, 
    PRO_STEP_VFD_INFO,
    PRO_STEP_EVENT_INFO,
    PRO_STEP_UPDATE,
    PRO_STEP_FAULT,             //失败
    PRO_STEP_DELAY,
}PRO_STEP_ENUM;

typedef struct {
    struct {
        char FirstRun: 1;
        char IsReg: 1;
//        char IsTimeChk: 1;
        char SrvGetPara: 1;
        char YecxFlag: 1;
    }Bits;

    PRO_STEP_ENUM Step;
    PRO_STEP_ENUM NextStep;
    u32 DevSerialNum;                                               //  终端流水号
    u32 SvrSerialNum;                                               //  服务器流水号
    u32 YecxSerialNum;
}PRO_SND_INFO;

PRO_SND_INFO ProSndInf;

char SendBuf[MAX_GPRS_BUF_SIZE];              
static u16 SendLen;         
DELAY_TIMER ParaUploadDelay;


u16 GB_GetMsgHead(u16 cmdCode, char *pBuf)
{    
    char *p = pBuf;
    
    *p++ = 0x30 | ((cmdCode >> 8) & 0xf);
    *p++ = 0x30 | ((cmdCode >> 4) & 0xf);
    *p++ = 0x30 | ((cmdCode >> 0) & 0xf);
    
    memcpy(p, GpSysPara->Dev.ID, DEV_ID_SIZE);
    p += DEV_ID_SIZE;

  //  if((TERMINAL_SMS_UPLOAD == cmdCode) && YecxSMS.Bits.UsrOpt) {        
  //      DWordToBuf(ProSndInf.YecxSerialNum, p);       
  //  } 
    //    else 
    //    {
        DWordToBuf(ProSndInf.DevSerialNum, p);
        ProSndInf.DevSerialNum++;
        if(0 == ProSndInf.DevSerialNum) {
            ProSndInf.DevSerialNum = 1;
        }
   // }
    p += 4;

    return p - pBuf;
}

u16 Packet(u16 cmdCode, char *pBuf, u16 sendLen)
{
    char *p = pBuf;
    char Len;
    u16 Crc16;

    memset(p, 0, PRO_BEFOR_MSGBODY_SIZE);

    *p++ = 0x2a;
        *p++ = GPRS_PRO_VERSION;
    WordToBuf(sendLen + PRO_MSGHEAD_SIZE + PRO_MSGEND_CRC_SIZE, p);
    p += 2;

    Len = GB_GetMsgHead(cmdCode, p);
    p += Len;

#if PRO_NOT_USE_CRC
    Crc16 = 0;
#else
    Crc16 = CRC16_1(pBuf, sendLen + PRO_BEFOR_MSGBODY_SIZE);    //  校验位从起始位开始
#endif
    p += sendLen;
    WordToBuf(Crc16, p);
    p += 2;

    *p++ = 0x23;

    return p - pBuf;
}

u16 GB_GetAckMsgHead(u16 cmdCode, char *pBuf)
{    
    char *p = pBuf;

//    WordToBuf(cmdCode, p);
//    p += 2;
    *p++ = 0x30 | ((cmdCode >> 8) & 0xf);
    *p++ = 0x30 | ((cmdCode >> 4) & 0xf);
    *p++ = 0x30 | ((cmdCode >> 0) & 0xf);

    memcpy(p, GpSysPara->Dev.ID, DEV_ID_SIZE);
    p += DEV_ID_SIZE;

    DWordToBuf(ProSndInf.SvrSerialNum, p);                          //  应答流水号         
    p += 4;

    return p - pBuf;
}

u16 AckPacket(u16 cmdCode, char *pBuf, u16 sendLen)
{
    char *p = pBuf;
    char Len;
    u16 Crc16;

    memset(p, 0, PRO_BEFOR_MSGBODY_SIZE);

    *p++ = 0x2a;
    *p++ = 0x01;//版本号

    WordToBuf(sendLen + PRO_MSGHEAD_SIZE + PRO_MSGEND_CRC_SIZE, p);
    p += 2;

    Len = GB_GetAckMsgHead(cmdCode, p);
    p += Len;
    
#if PRO_NOT_USE_CRC
    Crc16 = 0;
#else
    Crc16 = CRC16_1(pBuf, sendLen + PRO_BEFOR_MSGBODY_SIZE);    //  校验位从起始位开始
#endif
    p += sendLen;
    WordToBuf(Crc16, p);
    p += 2;

    *p++ = 0x23;

    return p - pBuf;
}

char    ProAckBuf[MAX_GPRS_BUF_SIZE];
char    GB_GeneralAck(u32 msgCount, u16 cmd, char ackValue)
{
    u16 Len;
//    char *pMsg = &ProAckBuf[PRO_BEFOR_MSGBODY_SIZE];
    char *pMsg = &ProAckBuf[PIPE_LEN_INFO_SIZE+PRO_BEFOR_MSGBODY_SIZE];
    JSON_ObjectBegin(pMsg);
    JSON_RtcTimeGet(pMsg);
    JSON_NumberValToObject(pMsg, "PS", GpSysPara->Dev.Bits.PS); 
    JSON_ObjectEnd(pMsg);
    
//    *pMsg = ackValue;                                                  //  应答消息体为空
    ProSndInf.SvrSerialNum = msgCount;
//    Len = AckPacket(cmd&PRO_CMD_MASK, ProAckBuf+PIPE_LEN_INFO_SIZE, 0);
    Len = AckPacket(cmd&PRO_CMD_MASK, ProAckBuf+PIPE_LEN_INFO_SIZE, strlen(pMsg));
    memcpy(ProAckBuf, (char *)&Len, PIPE_LEN_INFO_SIZE);
    GprsSndDataPost(ProAckBuf, PIPE_LEN_INFO_SIZE+Len, 1);
//    pipeDataWrite(pGprsSnd, ProAckBuf, Len);
    if(AppDebug.Bits.GprsSndData && AppDebug.Bits.Enable) 
    { 
   		#if DEBUG_USE_STR
		DebugStrMsg("[Pro] Respons: ", ProAckBuf+PIPE_LEN_INFO_SIZE+PRO_BEFOR_MSGBODY_SIZE, Len-PRO_MIN_SIZE);
		#else
        DebugHexMsg("[Pro] Respons: ", ProAckBuf+PIPE_LEN_INFO_SIZE, Len);
		#endif
    }
    
    return TRUE;
}


static void    ObjRespondToServer( u32 msgCount, u16 cmd, bool state )
{
	u16 Len;
    char * pMsg = &ProAckBuf[PIPE_LEN_INFO_SIZE+PRO_BEFOR_MSGBODY_SIZE];
    JSON_ObjectBegin(pMsg);
    JSON_RtcTimeGet(pMsg);
    JSON_NumberValToObject(pMsg, "PS", GpSysPara->Dev.Bits.PS);
	sprintf(&pMsg[strlen(pMsg)], "\"%s\":\"%d\",", "S", state);
	JSON_ObjectEnd(pMsg);
	ProSndInf.SvrSerialNum = msgCount;
    Len = AckPacket(cmd&PRO_CMD_MASK, ProAckBuf+PIPE_LEN_INFO_SIZE, strlen(pMsg));
    memcpy(ProAckBuf, (char *)&Len, PIPE_LEN_INFO_SIZE);
    GprsSndDataPost(ProAckBuf, PIPE_LEN_INFO_SIZE+Len, 1);
//    pipeDataWrite(pGprsSnd, ProAckBuf, Len);
    if(AppDebug.Bits.GprsSndData && AppDebug.Bits.Enable) 
    { 
    #if DEBUG_USE_STR
		DebugStrMsg("[Pro] Respons: ", ProAckBuf+PIPE_LEN_INFO_SIZE+PRO_BEFOR_MSGBODY_SIZE, Len-PRO_MIN_SIZE);
	#else
        DebugHexMsg("[Pro] Respons: ", ProAckBuf+PIPE_LEN_INFO_SIZE, Len);
	#endif
	}
}
static  int   OnlykeyVarRead(char *buf, u16 ReadAddr)	
{
	int ret = 1;
	switch (ReadAddr)
	{
		case 2901:  //触摸屏通信异常
			JSON_AddrNumberDataToObject(buf,2901, GpOthInfo->Error.RS485ErrCnt);
		break;
		case 2905: // 保养事件状态
			JSON_AddrNumberDataToObject(buf,2905,  GpSysStat->Share.MatainAlarm);
			break;
		default:
			ret = 0;
		break;
	}

	return  ret;
}	
void    ServerDataGetRespond(u32 msgCount, u16 cmd, JSON_ADDR_LIST_STRUCT *pList)
{ 
    ADDR_TYPE_ENUM AddrType;
    char VarBuf[50];
    u16 DataLen;
    u16 i, Addr;
    u32 Data;
    u16 Len;
    //double Data64;
    char *pMsg = &ProAckBuf[PIPE_LEN_INFO_SIZE+PRO_BEFOR_MSGBODY_SIZE];
    
    JSON_ObjectBegin(pMsg);
    JSON_RtcTimeGet(pMsg);
    JSON_NumberValToObject(pMsg, "PS", GpSysPara->Dev.Bits.PS);
    
    for(i=0; i<pList->Cnt; i++) {
        Addr = pList->List[i];     
      if(OnlykeyVarRead(pMsg, Addr))  //only key, no modbus addr;
     	 {
     	 	continue;
     	 }		
        if(SysVarRead(Addr, VarBuf, &DataLen, &AddrType)) 
        {
            switch(AddrType) 
            {
                case ADDR_TYPE_STRING:
                    VarBuf[DataLen] = 0;
                    JSON_AddrStringDataToObject(pMsg, Addr, VarBuf);
                    break; 
                case ADDR_TYPE_OTHER:
                 //  if(8 == DataLen)
                  //  {
                  //      Data64 = DevEightByteToDWord(VarBuf);
                  //      Data64 = Data64 / 100;
                 //       sprintf(&pMsg[strlen(pMsg)], "\"%d\":\"%.2f\",", Addr, Data64);
              //      }
					// fengyang  2018-4-10 10:35:08
					//else if((Addr >= 400 ) && (Addr <= 435 ) )
				 if((Addr >= 400 ) && (Addr <= 413 ))    // 电能表
					{
						Data = (2 == DataLen) ? DevTwoByteToWord(VarBuf) : DevFourByteToDWord(VarBuf);           			
						JSON_MeterDataToObject(pMsg, Addr, Data, VarBuf);
					}
					else if((Addr >= 420 ) && (Addr <= 435 ))   // 流量计
					{
						Data = (2 == DataLen) ? DevTwoByteToWord(VarBuf) : BufExchange(VarBuf);           			
						JSON_FlowDataToObject(pMsg, Addr, Data, VarBuf);
					}
                    else
                    {
                        Data = (2 == DataLen) ? DevTwoByteToWord(VarBuf) : DevFourByteToDWord(VarBuf);           
                        
                        if( (Addr >= 166) && (Addr <= 177)) {                               //  位置区号,小区ID                                             //  小区ID
                        //    sprintf(&pMsg[strlen(pMsg)], "\"%d\":\"%04X\",", Addr, Data);
                            sprintf(&pMsg[strlen(pMsg)], "\"%d\":\"%d\",", Addr, Data);                        
                    //    } else if((300 == Addr) || (302 == Addr)|| (304 == Addr)) {         //  报警值,预警值,保养值  
                    //        sprintf(&pMsg[strlen(pMsg)], "\"%d\":\"%04X\",", Addr, Data);   //  一体机8字节
                        } else if(JSON_AddrAndDataToObject(pMsg, Addr, Data, VarBuf) == FALSE)
                        {
                            sprintf(&pMsg[strlen(pMsg)], "\"%d\":\"%d\",", Addr, Data);
                        }             
                    }                    
                    break;
                default:
                    break;
            } 
        }
    }
    JSON_ObjectEnd(pMsg);

    ProSndInf.SvrSerialNum = msgCount;
    Len = AckPacket(cmd&PRO_CMD_MASK, ProAckBuf+PIPE_LEN_INFO_SIZE, strlen(pMsg));
    memcpy(ProAckBuf, (char *)&Len, PIPE_LEN_INFO_SIZE);
    GprsSndDataPost(ProAckBuf, PIPE_LEN_INFO_SIZE+Len, 1);
//    pipeDataWrite(pGprsSnd, ProAckBuf, Len);
    if(AppDebug.Bits.GprsSndData && AppDebug.Bits.Enable) 
    { 
    #if DEBUG_USE_STR
		DebugStrMsg("[Pro] Respons: ", ProAckBuf+PIPE_LEN_INFO_SIZE+PRO_BEFOR_MSGBODY_SIZE, Len-PRO_MIN_SIZE);
	#else
        DebugHexMsg("[Pro] Respons: ", ProAckBuf+PIPE_LEN_INFO_SIZE, Len);
	#endif
    }
//    return TRUE;
}


typedef struct {
    struct {
        char Enable: 1;                                             //  升级标识
        char Type: 7;                                               //  升级类型
    }Bits;

    u32 FileSize;                                                   //  文件大小
    u16 FileCrc;                                                    //  文件CRC
    char Ver[20];                                                   //  文件版本

    u32 FileAddr;                                                   //  获取文件地址偏移
}UPDATE_INFO_STRUCT;
static UPDATE_INFO_STRUCT Update;

char    isGprsCon(void)
{
    return  GprsCtrlInfo.Module.Bits.Connect_1;
}



void    SetParaSaveFlag(u16 Addr)
{
    if((Addr >= DEV_PARA_START_ADDR) && (Addr <= DEV_PARA_END_ADDR)) {
        ParaFat.Bits.SysPara = TRUE;
    } else if((Addr >= NET_PARA_START_ADDR) && (Addr <= NET_PARA_END_ADDR)) {
        ParaFat.Bits.SysPara = TRUE;
    } else if((Addr >= MAX_TIME_START_ADDR) && (Addr <= MAX_TIME_END_ADDR)) {
        ParaFat.Bits.UsrPara = TRUE;
    }      
}


bool    ServerParaSet(JSON_NODE_STRUCT *pNode, u16 *pAddr)
{
    bool IsString = FALSE;
    u8  StrLen;
    u16  WriteAddr, Len;
    u16 *pField;
    u16 OffsetAddr;
    u16 FieldEndAddr;
    u16 FieldStartAddr; 
    u32 uiData;
//    uint64_t Data64;

    if((!pNode) || (!pNode->pKey) || (!pNode->pVal)) {
        return FALSE;
    }
    
    if(!IsNumber(pNode->pKey)) {
        return FALSE;
    }
    
    WriteAddr = my_atoi(pNode->pKey); 
    *pAddr = WriteAddr;

    /*
     *  位变量
     */
    if((WriteAddr >= 8200) && (WriteAddr <= 8214)) 
    {     
    /*
     *  网络参数
     */
    } 
    else if((WriteAddr >= NET_PARA_START_ADDR) && (WriteAddr <= NET_PARA_END_ADDR)) 
    {
        Len = 2;
        if(2645 == WriteAddr) 
        {                                     //  域名
            Len = 30;
            IsString = TRUE;
            if(0 == stricmp(GpSysPara->Net.Domain, pNode->pVal)) 
            {
                return FALSE;
            }
            if(isGprsCon()) 
            {
                DelayReConnect(5000);                               //  重连服务器
            }
            GbUpLoadAllPara = TRUE;                                 //  重传所有参数
            ParaUpload.Bits.Resend = TRUE;                          //  重新上传参数
        } 
        else if(2660 == WriteAddr) 
        {                              //  端口
            uiData = my_atoi(pNode->pVal);
            if(GpSysPara->Net.Port == uiData) 
            {
                return FALSE;
            }
            if(isGprsCon()) 
            {
                DelayReConnect(5000);                               //  重连服务器
            }                              
            GbUpLoadAllPara = TRUE;                                 //  重传所有参数
            ParaUpload.Bits.Resend = TRUE;                          //  重新上传参数                        
        } 
        else if((2661 == WriteAddr)||(2662 == WriteAddr)) 
        {                              //  心跳           
        
        } 
        else 
        {
            if((2600 == WriteAddr) || (2615 == WriteAddr) || (2630 == WriteAddr)) 
            {
                if(isGprsCon()) 
                {
                    DelayReConnect(5000);                           //  修改APN参数,重连服务器,不重传参数
                }  
            }
        
            Len = 30;
            IsString = TRUE;
        }
        FieldStartAddr = NET_PARA_START_ADDR;
        FieldEndAddr = NET_PARA_END_ADDR; 
        pField = (u16 *)&GpSysPara->Net;  
    
    } 
    else if((WriteAddr >= DEV_PARA_START_ADDR) && (WriteAddr <= DEV_PARA_END_ADDR)) 
    {
        Len = 2;
      	if(2523 == WriteAddr) 
		{                                     					//éè±?±ào?
            Len = 20;
            IsString = TRUE;
					
				//pNode->pVal += 3;								//ì?1y?°??èy??×??ú
				memcpy(&GpSysPara->Dev.ID, pNode->pVal, 9); 	//?°èy??×?·??àμèê±DT??IDo?
				if(isGprsCon()) 
				{
                    DelayReConnect(5000);                       //??á?·t???÷
                    return TRUE;
                }
		}
        
    }
    else if((WriteAddr == 415) || (WriteAddr == 432)) //电表和流量计Modbus地址
    {
         uiData = my_atoi(pNode->pVal);
         if(WriteAddr == 415)
             GpSysPara->Dev.MeterNum = uiData;
         else
             GpSysPara->Dev.FlowNum = uiData; 
         
         return TRUE;
    }        
    else 
    {
        /*
         *  特有参数
         */
        switch(GpSysPara->Dev.Bits.PS) {
//            case PS_MAM_KY_G:
//            case PS_MAM_KY_C:
//            case PS_MAM260:
//            case PS_MAM260A:
//            case PS_MAM280:
//            case PS_MAM660_670_680:    
//            case PS_MAM860_870_880:
            case PS_MAM860C_880C:
//            case PS_MAM890: 
//                break;
            case PS_MAM6080_6090:
            case PS_MAM6080_1:
            case PS_MAM6090:
			case PS_MAM6070:
			case PS_HC:
                PltSysVarWriter(WriteAddr,(char *)pNode->pVal);
                break;
            #if MONITOR_METER_ON
            case PS_TYPE_XY_1942E:
                if(411 == WriteAddr)
                {
                    uiData = my_atoi(pNode->pVal);
                    Vfd_Meter_Write_Data(uiData);
                }
                break;
            #endif    
            default:
                break;
        }    
        return FALSE;
    }    

    if(FieldValOffset(FieldStartAddr, FieldEndAddr, WriteAddr, &OffsetAddr)) 
    {
        if(IsString) 
        {
            StrLen = strlen(pNode->pVal);
            if(StrLen < Len) 
            {
                StrLen++;
            }
            memcpy((char *)(pField + OffsetAddr), pNode->pVal, StrLen);                
        } 
        else 
        {    
            uiData = my_atoi(pNode->pVal);
            memcpy((char *)(pField + OffsetAddr), (char *)&uiData, Len); 
        }
    }    

    return TRUE;
}
#if 0
bool    ServerParaGet(JSON_NODE_STRUCT *pNode, u16 *pAddr)
{
    bool IsString = FALSE;
    u8  StrLen;
    u16  WriteAddr, Len;
    u16 *pField;
    u16 OffsetAddr;
    u16 FieldEndAddr;
    u16 FieldStartAddr; 
    u32 uiData;

    if((!pNode) || (!pNode->pKey) || (!pNode->pVal)) {
        return FALSE;
    }
    
    if(!IsNumber(pNode->pKey)) {
        return FALSE;
    }
    
    WriteAddr = my_atoi(pNode->pKey);  
    /*
     *  网络参数
     */
    if((WriteAddr >= NET_PARA_START_ADDR) && (WriteAddr <= NET_PARA_END_ADDR)) {
        if((2660 == WriteAddr) || (2661 == WriteAddr)) {
            Len = 2;
        } else if(2645 == WriteAddr) {
            Len = 30;
            IsString = TRUE;
        } else {
            Len = 10;
            IsString = TRUE;
        }
        FieldStartAddr = NET_PARA_START_ADDR;
        FieldEndAddr = NET_PARA_END_ADDR; 
        pField = (u16 *)&GpSysPara->Net;
    /*
     *  设备参数
     */
    } else if((2500 == WriteAddr) || (2505 == WriteAddr) || (2506 == WriteAddr) || (2507 == WriteAddr)) {
        if(2500 == WriteAddr) {
            Len = 10;
            IsString = TRUE;
        } else {
            Len = 2;
        }
        FieldStartAddr = DEV_PARA_START_ADDR;
        FieldEndAddr = DEV_PARA_END_ADDR; 
        pField = (u16 *)&GpSysPara->Dev;
    } else {
        /*
         *  特有参数
         */
//        switch(GpSysPara->Dev.Bits.PS) {
////            case PS_TYPE_PLT_MAM670:
////            case PS_TYPE_PLT_MAM680D:
////            case PS_TYPE_NO_ALM:
////                break;
//            case PS_TYPE_PLT_MAM6080:        
//            case PS_TYPE_PLT_MAM6090:                 
//                break;
//            default:
//                break;
//        }
        
        return FALSE;
    }   
            

    if(FieldValOffset(FieldStartAddr, FieldEndAddr, WriteAddr, &OffsetAddr)) {
        if(IsString) {
            StrLen = strlen(pNode->pVal);
            if(StrLen < Len) {
                StrLen++;
            }
            memcpy((char *)(pField + OffsetAddr), pNode->pVal, StrLen);                
        } else {    
            uiData = my_atoi(pNode->pVal);
            memcpy((char *)(pField + OffsetAddr), (char *)&uiData, Len); 
        }
    }

    return TRUE;
}
#endif

void    RebootDelay(u16 Nms)
{
    RebootTime.Bits.Flag  = TRUE;
    RebootTime.Bits.Timer = Nms;
}

bool ServerCmd_Head_Deal(char **pBuf, u8 SetTimeFlag)
{
    bool Err = TRUE;
    u8 PS;
    
    if(!JSON_IsObjectBegin(pBuf)) {
        return FALSE;
    }
    
    JSON_Extract(pBuf, &JsonNode);
    if(strncmp(JsonNode.pKey, "RTC", 3)) 
    {
        return FALSE;
    } 
    else
    {
        ServerTimeSet(JsonNode.pVal, &SysTime, SetTimeFlag);
    }
                
    JSON_Extract(pBuf, &JsonNode);
    if(strncmp(JsonNode.pKey, "PS", 2)) 
    {
        return FALSE;
    } 
    else 
    {
        PS = my_atoi(JsonNode.pVal);              
        if(PS != GpSysPara->Dev.Bits.PS) 
        {
            GpSysPara->Dev.Bits.PS = PS;
            ParaFat.Bits.SysPara = TRUE;    
            DelayReConnect(5000);                               //  重连服务器
        }             
    }
    
    return Err;
}


static  void SetBindStatus(u16 obj, u16 setval)
{
	u16 tmpstatus =GpSysPara->Dev.BindSatus;
	
	if (setval == 1)
	{
		tmpstatus |= (1<<(obj-1));
	}
	else if (setval == 0)
	{
		tmpstatus &= ~(1<<(obj-1));
	}

	if (tmpstatus != GpSysPara->Dev.BindSatus)
	{
		GpSysPara->Dev.BindSatus = tmpstatus;
		SetMeterReadIndex();
		ParaFat.Bits.SysPara = TRUE;
	}
}
void    ServerCmdDeal(u16 MsgCmd, u32 MsgCnt, char *pBuf, u16 Len)
{
//    int i;
    u16 OptAddr;
    u16 Data;
	u16 objct, msgtype, setval;
    JSON_ADDR_LIST_STRUCT *pAddrList;
    JSON_ARRAY_STRUCT *pArray = &JsonArrayBuf;
    u8 AddrCnt;
    u8 Type;
	
 //   u8 PS;

    DebugMsg(DEBUG_PRO, "Rcv Cmd %03X\r\n", MsgCmd);
    
    switch(MsgCmd) {
        /*
         *  服务器应答消息
         */
        case TERMINAL_REQ_RESP:
            if(ServerCmd_Head_Deal(&pBuf, 1) ==FALSE)
            {
                break;
            }        
                       
            JSON_AddrListExtract(&pBuf, &HeartAddrList);

            DebugMsg(DEBUG_PRO, "Heart Addr Num: %d\r\n", HeartAddrList.Cnt);  
            if(bRegAck == Rsp) {
                Rsp = RegAcked;
                ProSndInf.Bits.IsReg = TRUE;
				ParaUpdate.Bits.Rs485comstatus = TRUE;
				 InitParaUp.Bits.flag = TRUE;
				//GbRs485ComStat = 1; // 每次上线重新发送设备在线状态，防止服务器重启没有设备状态
            }
            break;
        case TERMINAL_HEART_RESP:
            if(bHeartAck == Rsp) {
                Rsp = HeartAcked;
            }
            if(ServerCmd_Head_Deal(&pBuf, 0) ==FALSE)
            {
                break;
            }                                                                    
                    
            if(!JSON_Extract(&pBuf, &JsonNode)) {
                break;
            }
            
            break;
        case TERMINAL_EVENT_RESP:
            if(bEvenAck == Rsp) {
                Rsp = EventAcked;
            }
            break;  

        case TERMINAL_TIME_PARA_RESP:
            if(bTimeParaAck == Rsp) {
                Rsp = TimeParaAcked;
            }
            
           if(ServerCmd_Head_Deal(&pBuf, 0) ==FALSE)
            {
                break;
            }                        
                        
            if(1 != ParaUpload.Bits.Index) {                        //  第一次解析RTC和余额
                break;
            }
                        
            if(!JSON_Extract(&pBuf, &JsonNode)) {
                break;
            }
            if(strncmp(JsonNode.pKey, "YE", 3)) {
                Data = my_atoi(JsonNode.pVal);
                
//                if(GpPwrTime->Data.Money != Data) {
//                    GpPwrTime->Data.Money = Data;
//                    DebugMsg(DEBUG_YUE, "%d\r\n", GpPwrTime->Data.Money);
//                }
            }            
            break;
            
        /*
         *  服务器主动下发消息
         */
        case SERVER_GET_DEV_DATA:
            pAddrList = (JSON_ADDR_LIST_STRUCT *)pBuf;
            if(ServerCmd_Head_Deal(&pBuf, 0) ==FALSE)
            {
                break;
            }
                                                    
            JSON_AddrListExtract(&pBuf, pAddrList);
            ServerDataGetRespond(MsgCnt, MsgCmd, pAddrList);
            
            break;   
        case SERVER_SET_PARA:          
            if(ServerCmd_Head_Deal(&pBuf, 0) ==FALSE)
            {
                break;
            }
                            
            pAddrList = (JSON_ADDR_LIST_STRUCT *)pBuf;
            AddrCnt = 0;
            while(JSON_Extract(&pBuf, &JsonNode)) {
                if(ServerParaSet(&JsonNode, &OptAddr)) {
                    SetParaSaveFlag(OptAddr);
                }
                pAddrList->List[AddrCnt++] = OptAddr;
            }
            pAddrList->Cnt = AddrCnt;
            SysParaStorage();
            ServerDataGetRespond(MsgCnt, MsgCmd, pAddrList);
                        
            break;
#if    SERVER_DOMAIN_ON        
        case SERVER_DOMAIN_CFG:          
            if(ServerCmd_Head_Deal(&pBuf, 0) ==FALSE)
            {
                break;
            }
                            
            if(!JSON_Extract(&pBuf, &JsonNode)) {
                break;
            }    
            if(strncmp(JsonNode.pKey, "ip", 2)) {
                break;
            }
            strcpy(GpSysPara->Net.Domain, JsonNode.pVal);
            

            if(!JSON_Extract(&pBuf, &JsonNode)) {
                break;
            }  
            if(strncmp(JsonNode.pKey, "port", 4)) {
                break;
            }
            GpSysPara->Net.Port = my_atoi(JsonNode.pVal);
                                    
            
            GbUpLoadAllPara = TRUE;                                 //    重传所有参数
            ParaUpload.Bits.Resend = TRUE;                            //    重新上传参数
                                
            SetParaSaveFlag(NET_PARA_START_ADDR);                        
            SysParaStorage();
            
            ServerDataGetRespond(MsgCnt, MsgCmd, NULL);
            
            if(isGprsCon()) 
            {
                DelayReConnect(100);                                //    重连服务器
            }            
            
            break;
#endif    

        case SERVER_VFD_OPT:
           if(ServerCmd_Head_Deal(&pBuf, 0) ==FALSE)
            {
                break;
            }
                        
            if(!JSON_Extract(&pBuf, &JsonNode)) {
                break;
            }    
            if(strncmp(JsonNode.pKey, "VT", 2)) {
                break;
            }
            if('1' == JsonNode.pVal[0]) 
            {
                Type = TRUE;
            } 
            else if('2' == JsonNode.pVal[0]) 
            {
                Type = FALSE;                          
            } 
            else if(('3' == JsonNode.pVal[0]) ||  ('4' == JsonNode.pVal[0]) ||('5' == JsonNode.pVal[0]))
            {
                pArray->Cnt = 0;
                if(JSON_ArrayExtract(&pBuf, "W", pArray, 2)) 
                {
                    if(2 == pArray->Cnt) 
                    {
                        SvrVfdOpt.Addr  = DevFourByteToU16((char *)pArray->ValAddr[0]);
                        SvrVfdOpt.Bits.Read = FALSE;
                        SvrVfdOpt.Bits.RspFlg = TRUE;
                        SvrVfdOpt.Bits.Type = JsonNode.pVal[0]-0x30;
                        
                        if(SvrVfdOpt.Addr == GpSysPara->Dev.PasswordAdrr[JsonNode.pVal[0]-0x33])
                        {
                            GpSysPara->Dev.PasswordData[JsonNode.pVal[0]-0x33] = DevFourByteToU16((char *)pArray->ValAddr[1]);
                            SvrVfdOpt.Data =GpSysPara->Dev.PasswordData[JsonNode.pVal[0]-0x33];                                                            
                        
                            SetParaSaveFlag(DEV_PARA_START_ADDR);                        
                            SysParaStorage();
                        }
                        else
                        {
                            SvrVfdOpt.Addr  = GpSysPara->Dev.PasswordAdrr[JsonNode.pVal[0]-0x33];
                            SvrVfdOpt.Data  = GpSysPara->Dev.PasswordData[JsonNode.pVal[0]-0x33];    
                        }
                    }                    
                }                
            } 
            else 
            {
                break;
            }

//            pArray->Cnt = 0;
//            if(JSON_ArrayExtract(&pBuf, "R", pArray, 2)) {
//                if(2 == pArray->Cnt) {
//                    SvrVfdOpt.Addr = my_atoi((char *)pArray->ValAddr[0]);
//                    SvrVfdOpt.Bits.Read = TRUE;
//                    SvrVfdOpt.Bits.Main = Type;
//                    SvrVfdOpt.Bits.OptFlg = TRUE;
//                    DebugMsg(DEBUG_PRO, "Read Vfd Addr: %d\r\n", SvrVfdOpt.Addr);
//                }
//                break;
//            } 

//            pArray->Cnt = 0;
//            if(JSON_ArrayExtract(&pBuf, "W", pArray, 2)) {
//                if(2 == pArray->Cnt) {
//                    SvrVfdOpt.Addr = my_atoi((char *)pArray->ValAddr[0]);
//                    SvrVfdOpt.Data = my_atoi((char *)pArray->ValAddr[1]);
//                    SvrVfdOpt.Bits.Read = FALSE;
//                    SvrVfdOpt.Bits.Main = Type;
//                    SvrVfdOpt.Bits.OptFlg = TRUE;
//                    DebugMsg(DEBUG_PRO, "Write Vfd Addr: %d Data: %d\r\n", SvrVfdOpt.Addr, SvrVfdOpt.Data);
//                }
//                break;
//            } 
            break;
                    
        case SERVER_CONTROL:
           if(ServerCmd_Head_Deal(&pBuf, 0) ==FALSE)
            {
                break;
            }
                            
            if(JSON_Extract(&pBuf, &JsonNode)) {
                if(strncmp(JsonNode.pKey, "CTL", 3)) {
                    break;
                }

                Type = TRUE;
                Data = my_atoi(JsonNode.pVal);
                switch(Data) {
                    case 1:                                     //  重启控制
                        RebootDelay(5000);
                        break;
                    case 2:                                     //  重连控制
                        DelayReConnect(5000);
                        break;
                    case 3:                                     //  远程开机操作
                        bRemoteBoot = TRUE;
                        break;
                    case 4:                                     //  远程停机操作
                        bRemoteStop = TRUE;
                        break;
                     case 5:                                     //  重连服务器
                        DelayReConnect(5000);                            
                        break;
                     case 6:                                     //  看门狗复位重启
                        while(1);
                    //    break;
                    default:
                        Type = FALSE;
                        break;
                }
                
                if(Type) 
                {
                    GB_GeneralAck(MsgCnt, MsgCmd, ACK_SUCCESS);    
                }
            } 
            
            break;
		case TERMINAL_STATUS_RESP:
			 if(bStatusAck == Rsp) {
                Rsp = StatusAcked;
            }
            break;  
		case  SERVER_MSG_PUSH:
			if(ServerCmd_Head_Deal(&pBuf, 0) ==FALSE)
            {
                break;
            }
			if (JSON_ExtractObjNode(&pBuf, &JsonObjNode))
			{
				objct = my_atoi(JsonObjNode.ptypeval);
				msgtype = my_atoi(JsonObjNode.pmtval);
				setval	= my_atoi(JsonObjNode.pstatusval);

				switch (msgtype)
				{
					case 1:   //绑定消息
						SetBindStatus(objct, setval);
						break;
					default:
						break;
				}
				ObjRespondToServer(MsgCnt, MsgCmd,TRUE); 
			}
			else
			{
				ObjRespondToServer(MsgCnt, MsgCmd,FALSE);
			}
			break;
        case SERVER_UPDATE_REQUEST:
           if(ServerCmd_Head_Deal(&pBuf, 0) ==FALSE)
            {
                break;
            }

            if(!JSON_Extract(&pBuf, &JsonNode)) {
                break;
            }    
            if(strncmp(JsonNode.pKey, "rule", 4)) {
                break;  
            }
            if(1 != atoi(JsonNode.pVal)) {
                break;
            }
            
            if(!JSON_Extract(&pBuf, &JsonNode)) {
                break;
            }    
            if(strncmp(JsonNode.pKey, "fv", 2)) {
                break;  
            }
            switch(UpgradeVersionInit(JsonNode.pVal)) {
                case 2:                                             //  升级取消
                    goto Loop;
                case 0:                                             //  解析失败
                    goto ERROR;
                default:                                            //  解析成功
                    break;
            }

            if(!JSON_Extract(&pBuf, &JsonNode)) {
                break;
            }    
            if(strncmp(JsonNode.pKey, "size", 4)) {
                break;  
            }
            UpgradeSizeInit(JsonNode.pVal);
        
            if(!JSON_Extract(&pBuf, &JsonNode)) {
                break;
            }    
            if(strncmp(JsonNode.pKey, "url", 3)) {
                break;  
            }
            if(!UpgradeServerInit(JsonNode.pVal)) {
                break;
            }
        
            if(!JSON_Extract(&pBuf, &JsonNode)) {
                break;
            }    
            if(strncmp(JsonNode.pKey, "user", 3)) {
                break;  
            }
            if(!UpgradeUsrInit(JsonNode.pVal)) {
                break;
            }
            FTPConnectRequestSet();
Loop:            
            GB_GeneralAck(MsgCnt, MsgCmd, ACK_SUCCESS);
ERROR:            
            break;
        default:            
            DebugMsg(DEBUG_PRO, "MsgCmd %02X unkonw\r\n", MsgCmd);
            GB_GeneralAck(MsgCnt, MsgCmd, ACK_NOT_SUPPORT);
            break;
    }
}


void    GPRSDataDeal(char *pBuf)
{
    char *p = pBuf;
    short Len, IDLen;
    char *pCurPacket, *pBody;
    u16   CurPktLen, BodyLen;
    char  DevID[DEV_ID_SIZE+1];
    u16   MsgCmd;                                                   //  命令
    u32   MsgCount;                                                 //  流水号
    u16   RcvCrc, CalcCrc;
     
    memcpy((char *)&Len, pBuf, PIPE_LEN_INFO_SIZE);
    pBuf[PIPE_LEN_INFO_SIZE+Len] = 0;                              //  防止接收字符串无结束符
    pBuf += PIPE_LEN_INFO_SIZE;

    
    if(AppDebug.Bits.GprsRcvData && AppDebug.Bits.Enable) {
        DebugMsg(DEBUG_PRO, "Rx from Srv %d", Len);
		#if DEBUG_USE_STR
			 DebugStrMsg("\r\n", pBuf+PRO_BEFOR_MSGBODY_SIZE, Len-PRO_MIN_SIZE);
		#else
       		 DebugHexMsg("\r\n", pBuf, Len);
		#endif
    }

    while(1) {
        if((Len < PRO_MIN_SIZE) || (Len > MAX_GPRS_BUF_SIZE)) {            
            DebugMsg(DEBUG_PRO, "RevLen Fault: %d\r\n", Len);
            break;
        }
        
        CurPktLen  = 0;
        pCurPacket = NULL;                
        while(Len) {            
            if(GPRS_PRO_HEAD_FLAG == *p) {
                pCurPacket = p;
                break;                
            }                    
            p++;
            Len--;
        }

        if(NULL == pCurPacket) {
            break;
        }

        //  跳过帧头
        p++;
        //  跳过版本号
        p++;
        //  帧长度               
        CurPktLen = NetTwoByteToWord(p);
        p += 2; 

        if(GPRS_PRO_END_FLAG != *(p+CurPktLen-1)) {
            DebugMsg(DEBUG_PRO, "End byte: %02X err\r\n", *(p+CurPktLen-1));
            Len -= (p - pCurPacket);
            continue;
        }

        //  消息ID
        MsgCmd = ((p[0] & 0xf) << 8) | ((p[1] & 0xf) << 4) | (p[2] & 0xf);
        p += 3; 

        //  设备ID
        DevID[DEV_ID_SIZE] = 0;
        memcpy(DevID, p, DEV_ID_SIZE);
        p += DEV_ID_SIZE;     
        IDLen = strlen(GpSysPara->Dev.ID);
        if(IDLen >= DEV_ID_SIZE) {
            IDLen = DEV_ID_SIZE;
        }
        if(memcmp(GpSysPara->Dev.ID, DevID, IDLen)) {
            DebugMsg(DEBUG_PRO, "Dev id %s err\r\n", DevID);
            p = pCurPacket + CurPktLen + 3;                 //  跳到下一帧起始         
            if(Len > (p - pCurPacket)) {
                Len -= (p - pCurPacket);
                DebugMsg(DEBUG_PRO, "Have %d bytes to deal\r\n", Len);
                continue;
            } else {
                Len = 0;
                break;                                              //  退出
            }  
        }

        //  消息流水号
        MsgCount = NetFourByteToDWord(p);
        p += 4; 

        //  消息体
        pBody = p;
        BodyLen = CurPktLen - PRO_MSGHEAD_SIZE - PRO_MSGEND_CRC_SIZE;   //  消息体长度
        p += BodyLen;

#if PRO_NOT_USE_CRC       
        RcvCrc = CalcCrc = 0;
#else
        RcvCrc  = NetTwoByteToWord(p);                
        CalcCrc = CRC16_1(pCurPacket, CurPktLen+(PRO_BEFOR_MSGBODY_SIZE-PRO_MSGHEAD_SIZE)-PRO_MSGEND_CRC_SIZE); //  从起始位开始
        *p = 0;                                                     //  JSON字符串结束
#endif        
        p += 3;                                                     //  跳到下一帧起始
        
        if(RcvCrc != CalcCrc) {
            DebugMsg(DEBUG_PRO, "Crc err %04X != %04X\r\n", RcvCrc, CalcCrc);
        } else {
            ServerCmdDeal(MsgCmd, MsgCount, pBody, BodyLen);
        }

        if(Len > (p - pCurPacket)) {
            Len -= (p - pCurPacket);
            DebugMsg(DEBUG_PRO, "Have %d bytes to deal\r\n", Len);
            FeedDog();
            continue;
        } else {
            Len = 0;
            break;                                                  //  退出
        } 
    } 
}



#define ProTrans(stat)  (ProSndInf.Step = stat, ProSndInf.NextStep = (PRO_STEP_ENUM)(stat+1))
#define JReset()        (ProSndInf.Step = PRO_STEP_START)
#define JFault()        (ProSndInf.Step = PRO_STEP_FAULT)

#define ProNextStat()   (ProSndInf.Step = ProSndInf.NextStep)



/*
 *  参数集状态值,一体机基值为0
 *      主机    风机    值
 *       工      工     1
 *       变      工     2
 *       变      变     3
 *      工变     工     4
 *      工变     变     5
 *  普乐特控制器基值为10
 *  二代控制器基值为20
 */


void    GetRegister(char *pBuf, u16 *pLen)
{
//    u8 PSVal = 0;   //GetParameterSet(0/*GpUsrPara->Bit.Bits.BothDrvEn*/, 1/*GpUsrPara->Bit.Bits.MainDrvType*/, 0);
     
    JSON_ObjectBegin(pBuf);    
    JSON_RtcTimeGet(pBuf);
    JSON_NumberValToObject(pBuf, "PS", GpSysPara->Dev.Bits.PS);
    JSON_NumberValToObject(pBuf, "SIM", GprsCtrlInfo.Module.Bits.Standard);
    JSON_NumberValToObject(pBuf, "type", SERVER_TYPE);
    JSON_ObjectEnd(pBuf);
    *pLen = strlen(pBuf);
}





void    GetEventInfo(char *pBuf, u16 *pLen)
{
    u8 i;
//    u16 Addr;
    char PwrOffTime[20];
    
    JSON_ObjectBegin(pBuf);
    JSON_RtcTimeGet(pBuf);
    JSON_NumberValToObject(pBuf, "PS", GpSysPara->Dev.Bits.PS);
    
    /*
     *  复位事件
     */ 
    if(SysEvent.Flag.Bits.Reset) 
    {
        SysEvent.Flag.Bits.Reset = FALSE;    
        sprintf(PwrOffTime, "%02d:%02d:%02d", BeforeReg.Cnt.Hour, BeforeReg.Cnt.Min, BeforeReg.Cnt.Sec);                        
        JSON_EventWithInfToObject(pBuf, 8500+SysEvent.ResetType-1, 0xffff, PwrOffTime);
    }

    /*
     *  开机事件
     */ 
    if(SysEvent.Flag.Bits.Boot) 
    {
        SysEvent.Flag.Bits.Boot = FALSE;
        JSON_EventNoInfToObject(pBuf, 8510+SysEvent.BootType-1);       
    }

    /*
     *  停机事件
     */ 
    if(SysEvent.Flag.Bits.Stop) 
    {
        SysEvent.Flag.Bits.Stop = FALSE;
        JSON_EventNoInfToObject(pBuf, 8530+SysEvent.StopType-1);       
    } 
	
    if(SysEvent.Flag.Bits.Alarm) 
    {
        SysEvent.Flag.Bits.Alarm = FALSE;        
      
        if(SysEvent.Alarm.Flag) /* *  报警事件*/
        {
      
            for(i=0; i<32; i++) 
            {
                if(SysEvent.Alarm.Flag & (1 << i)) 
                {
                	// 发送间隔时间未到，不发送，清除报警标志
              
					if (GpSysPara->Dev.Bits.PS != 111 &&GpSysPara->Dev.Bits.PS != 112 )
					{
					if (1 == i)  //缺水报警
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8301\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0);		
					}
					else if (2 == i)	// 输入缺相
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8302\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"212\":\"%d\",\"4\":\"%d\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0,
						GpSysStat->OtherData.OpenPhaseProVolt,GpSysStat->Share.PowerVolt);		
						
					}
					else if (3 == i) // 相序错误
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8303\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"211\":\"%d\",\"4\":\"%d\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0,
						GpSysStat->OtherData.PhaseProVolt,GpSysStat->Share.PowerVolt);		
					}
					else if (4 == i) // 主电机轴温超高
					{
						
						sprintf(&pBuf[strlen(pBuf)], "\"8304\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0);		
					}
					else if(5 == i)	//主机变频器故障
					{			
						sprintf(&pBuf[strlen(pBuf)], "\"8305\":{\"2300\":\"%d\",\"46\":\"%d\",\"42\":\"%.1f\"},"
						,GpSysStat->VFD.MainVfd_Model, GpSysStat->VFD.MainVfd_AlarmValue, GpSysStat->Main.OutCurrent/10.0);			
					}
					else if (7 == i) // 主机过流
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8307\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"6\":\"%.1f\",\"7\":\"%.1f\",\"8\":\"%.1f\",\"2326\":\"%.1f\",},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0, GpSysStat->Main.A_Current/10.0,
						GpSysStat->Main.B_Current/10.0,GpSysStat->Main.C_Current/10.0,GpSysStat->Main.RateCurrent/10.0);			
					}
					else if (8 == i) // 主机电流检测故障
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8308\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"6\":\"%.1f\",\"7\":\"%.1f\",\"8\":\"%.1f\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0, GpSysStat->Main.A_Current/10.0,
						GpSysStat->Main.B_Current/10.0,GpSysStat->Main.C_Current/10.0);
					}
					else if (9 == i) // 主机电流不平衡
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8309\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"6\":\"%.1f\",\"7\":\"%.1f\",\"8\":\"%.1f\",\"2327\":\"%d\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0, GpSysStat->Main.A_Current/10.0,
						GpSysStat->Main.B_Current/10.0,GpSysStat->Main.C_Current/10.0,GpSysStat->Share.UnblanceCurrent);
						
					}
					else if(10 == i) //风机变频器故障
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8310\":{\"2340\":\"%d\",\"76\":\"%d\",\"72\":\"%.1f\"},"
						,GpSysStat->VFD.FanVfd_Model, GpSysStat->VFD.FanVfd_AlarmValue, GpSysStat->Fan.OutCurrent/10.0);						
					}
					else if ( 12 == i) // 风机过流
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8312\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"9\":\"%.1f\",\"10\":\"%.1f\",\"11\":\"%.1f\",\"2366\":\"%.1f\",},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0, GpSysStat->Fan.A_Current/10.0,
						GpSysStat->Fan.B_Current/10.0,GpSysStat->Fan.C_Current/10.0,GpSysStat->Fan.RateCurrent/10.0);
					}
					else if (13 == i) // 风机电流检测故障
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8313\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"9\":\"%.1f\",\"10\":\"%.1f\",\"11\":\"%.1f\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0, GpSysStat->Fan.A_Current/10.0,
						GpSysStat->Fan.B_Current/10.0,GpSysStat->Fan.C_Current/10.0);
					}
					else if (14 == i) // 风机电流不平衡
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8314\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"9\":\"%.1f\",\"10\":\"%.1f\",\"11\":\"%.1f\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0, GpSysStat->Fan.A_Current/10.0,
						GpSysStat->Fan.B_Current/10.0,GpSysStat->Fan.C_Current/10.0);
					}
					else if (15 == i)  // 压力超限报警
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8315\":{\"1\":\"%.2f\",\"2110\":\"%.2f\",\"5\":\"%d\"},"
						,GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.StopPress/100.0,GpSysStat->Share.MachineStat);	
					}
					else if (16 == i) // 压力传感器故障
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8316\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0);				
					}
					else if (17 == i) // 温度超限停机报警
					{
						
						sprintf(&pBuf[strlen(pBuf)], "\"8317\":{\"2\":\"%.1f\",\"2116\":\"%.1f\",\"5\":\"%d\"},"
						,GpSysStat->Share.Temprature1/10.0, GpSysStat->Fan.AlmTemp/10.0,GpSysStat->Share.MachineStat);		
					}
					else if (18 == i) // 温度传感器故障
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8318\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0);				
					}
					else if (19 == i)  // 温度超低
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8319\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"2117\":\"%.1f\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0,GpSysStat->OtherData.LowTempProtect/10.0);				
						
					}
					else if (20 == i) // 压力温度失调
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8320\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0);				
					}
					else if (21 == i) // 超过使用时限
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8321\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"2000\":\"%d\",\"2002\":\"%d\",\"2100\":\"%d\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0,GpSysStat->Run.RunHour
						,GpSysStat->Run.LoadHour,GpUsrPara->Hour.MaxUseTime);				
					}
                    else if (22 == i) // 电源电压超高
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8322\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"4\":\"%d\",\"2128\":\"%d\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0,GpSysStat->Share.PowerVolt
						,GpSysStat->OtherData.VoltOvertop);	
					}
					else if (23 == i) // 电源电压超低
					{
						sprintf(&pBuf[strlen(pBuf)], "\"8323\":{\"5\":\"%d\",\"1\":\"%.2f\",\"2\":\"%.1f\",\"4\":\"%d\",\"2129\":\"%d\"},"
						,GpSysStat->Share.MachineStat, GpSysStat->Share.Pressure1/100.0, GpSysStat->Share.Temprature1/10.0,GpSysStat->Share.PowerVolt
						,GpSysStat->OtherData.VoltOverlow);	
					}
                    else if(0 == i) 
                    {
                        if(0x00000001== AlmStat.Alarm.Flag)   //只有其它报警时，才上报
                            JSON_EventNoInfToObject(pBuf, 8300);
                    }
                    else 
                    {
                        JSON_EventNoInfToObject(pBuf, 8300+i);
                    }
					}
					else 
					{

						 JSON_EventNoInfToObject(pBuf, 8300+i);
					}
					AlmFilterTimer[i] = ALARM_FILTER_TIME;   //重置间隔时间
                }
            }  
        SysEvent.Alarm.Flag = 0x0;
        }
        
        /* *  保养事件*/     
	/*
        if(SysEvent.PreAlarm.Flag & 0xffff) 
        {                       //  低16位
            for(i=0; i<16; i++) 
            {
                if(SysEvent.PreAlarm.Flag & (1 << i)) 
                {
                    JSON_EventNoInfToObject(pBuf, 8400+i);
                }
            }        
        }
	*/
        /*
         *  预警事件
         */ 

		if(SysEvent.PreAlarm.Flag) 
        {                          
            for(i=0; i<7; i++)
            {
        
                if(SysEvent.PreAlarm.Flag & (1 << i)) 
                {
                    if (i == 1)  //温度过高预警
            		{ 		
						sprintf(&pBuf[strlen(pBuf)], "\"8451\":{\"2\":\"%.1f\",\"2115\":\"%.1f\",\"5\":\"%d\"},"
						,GpSysStat->Share.Temprature1/10.0, GpSysStat->Fan.PreAlmTemp/10.0,GpSysStat->Share.MachineStat);		
            		}
            		else
            		{		
                    	JSON_EventNoInfToObject(pBuf, 8450+i);
                    }
					PreAlmFilterTimer[i] = PREALARM_FILTER_TIME;
                }
            }
            SysEvent.PreAlarm.Flag = 0;
        }
        
    }

     /*
     *    设备状态事件
     */
     /*
    if(SysEvent.DevAlarm.Flag) 
    {
        for(i=0; i<32; i++) 
        {
            if(SysEvent.DevAlarm.Flag & (1 << i)) 
            {                                                  
                JSON_EventNoInfToObject(pBuf, 8570+i);                                 
            }
        }  
        SysEvent.DevAlarm.Flag = 0x0;
    }
       */     

     /*
     * 其它事件
     */ 
     /*
     if(SysEvent.OthersAlarm.Flag) 
     {           
            for(i=0; i<32; i++) 
            {
                if(SysEvent.OthersAlarm.Flag & (1 << (i-16))) 
                {
                    JSON_EventNoInfToObject(pBuf, 8550+i);
                }
            }  
            SysEvent.OthersAlarm.Flag = 0;
       }
       */
    
   JSON_ObjectEnd(pBuf);
    *pLen = strlen(pBuf);    
}






void    GetHeartData(char *pBuf, u16 *pLen)
{
//    ADDR_TYPE_ENUM AddrType;
//    char VarBuf[50];
//    u16  DataLen;
 //   u16 i, Addr;
 //   u32 Data;
//    double Data64;
    u8  pstype = 0;

		switch (GpSysPara->Dev.Bits.PS )
		{
			case  PS_MAM6080_1:
			case  PS_MAM6090:
			case  PS_MAM6080_6090:
			case  PS_MAM6070:
				pstype  = CLASS_6080;
				break;
			case  PS_MAM860C_880C:
			case  PS_MAM860_870_880:
				pstype = CLASS_860;
				break;
			case PS_HC:
				pstype = CLASS_HC;
				break;
			default:
				break;
		}
    JSON_ObjectBegin(pBuf);
    JSON_RtcTimeGet(pBuf);
    JSON_NumberValToObject(pBuf, "PS", GpSysPara->Dev.Bits.PS);
    JSON_NumberValToObject(pBuf, "rsp", HEARTDAT_RSP);

//    #if 0
//    for(i=0; i<HeartAddrList.Cnt; i++) 
//    {
//        Addr = HeartAddrList.List[i];       
//        SysVarRead(Addr, VarBuf, &DataLen, &AddrType);
//        switch(AddrType) 
//        {
//            case ADDR_TYPE_STRING:
//                VarBuf[DataLen] = 0;
//               // JSON_AddrStringDataToObject(pBuf, Addr, VarBuf);
//                JSON_AddrAndDataToObject(pBuf, Addr, Data, VarBuf);
//                break;
//            case ADDR_TYPE_OTHER:
//                if(8 == DataLen)
//                {
//                    Data64 = DevEightByteToDWord(VarBuf);
//                    Data64 = Data64 / 100;
//                    sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.2f\",", Addr, Data64);
//                }
//                else
//                {
//                    Data = (2 == DataLen) ? DevTwoByteToWord(VarBuf) : DevFourByteToDWord(VarBuf);           
//             //   JSON_AddrNumberDataToObject(pBuf, Addr, Data);
//            //        JSON_AddrAndDataToObject(pBuf, Addr, Data, VarBuf);

//                     if(JSON_AddrAndDataToObject(pBuf, Addr, Data, VarBuf) == FALSE)
//                    {
//                        sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
//                    } 
//                }
//                break;
//            default:
//                break;
//        }           
//    }

//    #endif
    
    sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", 3, GpSysStat->Share.CSQ);
    sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", 5, GpSysStat->Share.MachineStat);
   JSON_AddrNumberDataToObject(pBuf, 2000, GpSysStat->Run.RunHour);	
				if (pstype == CLASS_6080 )
					{
						JSON_AddrNumberDataToObject(pBuf, 1998, GpSysStat->Run.RunMinute); 
					}

				JSON_AddrNumberDataToObject(pBuf, 2002, GpSysStat->Run.LoadHour);	
				if (pstype == CLASS_6080 )
					{
						JSON_AddrNumberDataToObject(pBuf, 1999, GpSysStat->Run.LoadMinute);
					}
			
	if (pstype ==  CLASS_HC)
	{
		
		JSON_AddrNumberDataToObject(pBuf, 33, GpSysStat->Run.CurrentRunHour); 
		JSON_AddrNumberDataToObject(pBuf, 34, GpSysStat->Run.CurrentRunMinute); 
	}

	
    JSON_ObjectEnd(pBuf);

    *pLen = strlen(pBuf);
}


void    GetVfdOptInfo(char *pBuf, u16 *pLen)
{
    JSON_ObjectBegin(pBuf); 
    JSON_RtcTimeGet(pBuf);
    JSON_NumberValToObject(pBuf, "PS", GpSysPara->Dev.Bits.PS);    
    JSON_NumberValToObject(pBuf, "VT", SvrVfdOpt.Bits.Type);    
    sprintf(&pBuf[strlen(pBuf)], "\"%s\":[\"%d\",\"%d\"],", SvrVfdOpt.Bits.Read ? "R" : "W", 
                                                            SvrVfdOpt.Addr, SvrVfdOpt.Data);
    JSON_ObjectEnd(pBuf);
    *pLen = strlen(pBuf);    
}



static void GetStatusUpData(char *pBuf, u16 *pLen)
{

		u8  pstype = 0;
	
		switch (GpSysPara->Dev.Bits.PS )
		{
			case  PS_MAM6080_1:
			case  PS_MAM6090:
			case  PS_MAM6080_6090:
			case  PS_MAM6070:
				pstype  = CLASS_6080;
				break;
			case  PS_MAM860C_880C:
				pstype = CLASS_860C;
				break;
			case  PS_MAM860_870_880:
				pstype = CLASS_860;
				break;
			default:
				break;
		}
		JSON_ObjectBegin(pBuf);
		JSON_RtcTimeGet(pBuf);
		JSON_NumberValToObject(pBuf, "PS", GpSysPara->Dev.Bits.PS);
		
		if(GpSysStat->Share.UpdataParaFlag & 0x0008)      //状态参数
		{
			GpSysStat->Share.UpdataParaFlag &= ~(1<<3);
			if (ParaUpdate.val & (1<<0))     //Rs485 通信状态改变
			{
				ParaUpdate.val &= ~(1<<0);
				sprintf(&pBuf[strlen(pBuf)], "\"9000\":\"%d\",",  GpSysStat->Share.DTU_COMM_STATUS);
			}

			
			if (ParaUpdate.val & (1<<1))
			{
				ParaUpdate.val &= ~(1<<1);
				sprintf(&pBuf[strlen(pBuf)], "\"2901\":\"%d\",",  GpOthInfo->Error.RS485ErrCnt);
			}

			if (ParaUpdate.val & (1<<2))
			{
				ParaUpdate.val &= ~(1<<2);
				sprintf(&pBuf[strlen(pBuf)], "\"2905\":\"%d\",",  GpSysStat->Share.MatainAlarm);
			}
			if (ParaUpdate.val & (1<<3))   // 机器状态改变
			{
				ParaUpdate.val &= ~(1<<3);
				JSON_AddrNumberDataToObject(pBuf, 5, GpSysStat->Share.MachineStat);	//参数有改变则在心跳数据中上传
			}
		}
		
		if(GpSysStat->Share.UpdataParaFlag & 0x0001)      //保养参数
		{
		    GpSysStat->Share.UpdataParaFlag &= 0xFFFE;
		    GetPlt1SpecPara(pstype, pBuf);
		}
	
		if(GpSysStat->Share.UpdataParaFlag & 0x0002)    //用户参数
		{
		    GpSysStat->Share.UpdataParaFlag &= 0xFFFD;
		    GetPlt2SpecPara(pBuf);
		}

		
		if(GpSysStat->Share.UpdataParaFlag & 0x0004)      //厂家参数
		{
		    GpSysStat->Share.UpdataParaFlag &= 0xFFFB;
		    GetPlt3SpecPara(pBuf);
		}
	    JSON_ObjectEnd(pBuf);
		*pLen = strlen(pBuf);  
}

char    GetUpdateData(char *pBuf, u16 *pLen)
{
    char *p = pBuf;
    u8  VerLen = strlen(Update.Ver);

    *p++ = VerLen;
    memcpy(p, Update.Ver, VerLen);
    p += VerLen;
    DWordToBuf(Update.FileAddr, p);
    p += 4;
    WordToBuf(512, p);
    p += 2;
    
    *pLen = p - pBuf;
    return TRUE;
}

void    ProSendInit(void)
{
    memset((char *)&ProSndInf, 0, sizeof(ProSndInf));
    ProSndInf.Step = PRO_STEP_START;
    ProSndInf.Bits.FirstRun = TRUE;
    ProSndInf.DevSerialNum = 1;
    GbUpLoadAllPara = TRUE;
}



typedef struct
{
    u16 Cmd;                                                        //  消息ID
    u16 Len;                                                        //  RAM数据指针，bBufEn为1时有效
    char *pBuf;                                                     //  RAM数据长度，bBufEn为1时有效
    u32 flashAddr;                                                  //  外部FLASH数据首地址，bFlashBufEn为1时有效
    u32 flashLenth;                                                 //  外部FLASH数据长度，bFlashBufEn为1时有效
    PR_ACK_EN ackType;                                              //  应答类型
    union
    {
        char flag;
        struct {
            char bEncryption: 1;                                    //  消息体加密标识，1:加密，0:未加密
            char bBufEn: 1;                                         //  RAM数据有效标识，1:有效，0:无效
            char bFlashBufEn: 1;                                    //  外部Flash数据有效标识，1:有效，0:无效
            char NeedResp: 1;                                       //  是否需要应答
            char rev: 4;
        } Bits;
    } info;
} PTL_DATA_SEND;


static PTL_DATA_SEND SendData;


PR_ACK_EN GetRsp(WORD cmdCode)
{
    PR_ACK_EN ack = NoneAck;

    switch(cmdCode) {
        case TERMINAL_REG:  
            ack = RegAcked;
            break;
        case TERMINAL_HEART:
            ack = HeartAcked;
            break;
        case TERMINAL_EVENT_UPLOAD:
            ack = EventAcked;
            break;
//        case TERMINAL_SMS_UPLOAD:
//            ack = SMSUploadAcked;
//            break;            
//        case TERMINAL_SMS_CNT:
//            ack = SMSCntAcked;
//            break;
        case TERMINAL_TIME_PARA:
            ack = TimeParaAcked;
            break;
		case TERMINAL_STATUS_UPLOAD:
			ack = StatusAcked;
			break;
//        case TERMINAL_UPDATE:
//            ack = UpdateAcked;
        default:
            break;
    }
    
    return ack;
}

void WaitRsp(WORD cmdCode)
{
    switch(cmdCode) {
        case TERMINAL_REG: 
            Rsp = bRegAck;
            break;
        case TERMINAL_HEART:
            Rsp = bHeartAck;
            break;
        case TERMINAL_EVENT_UPLOAD:
            Rsp = bEvenAck;
            break;
//        case TERMINAL_SMS_UPLOAD:
//            Rsp = bSMSUploadAck;
//            break;
//        case TERMINAL_SMS_CNT:
//            Rsp = bSMSCntAck;
//            break;
        case TERMINAL_TIME_PARA:
            Rsp = bTimeParaAck;
            break;
		case TERMINAL_STATUS_UPLOAD:
			Rsp = bStatusAck;
			break;
//        case TERMINAL_UPDATE:   
//            Rsp = bUpdateAck;
//            break;
        default:
            Rsp = NoneAck;
            break;
    }
}

PR_ACK_EN GetAckVaule(void)
{
    return Rsp;
}


typedef enum {
    psStart = 0,
    psSend,
    psAck,
}PRO_SEND_ENUM;


#define PPR_SEND_RETRY_NUM  2                                       //  重试2次
char    ProDataSend(PTL_DATA_SEND* pSndInf, char Nms, char *pRlt)
{
    static PRO_SEND_ENUM PtlSendState = psStart;
    static u16 WaitNms = 0;
    static char RetryCnt = 0;
    char bExitSend = FALSE;
    
    if(!isGprsCon()) {
        RetryCnt = 0;
        PtlSendState = psStart;
        *pRlt = FALSE;
        bExitSend = TRUE;
        return bExitSend;
    }

//    if(IsSMSSending()) {
//        return bExitSend;
//    }
    
    switch(PtlSendState) {
        case psStart:                   
            pSndInf->Len = Packet(pSndInf->Cmd, pSndInf->pBuf+PIPE_LEN_INFO_SIZE, pSndInf->Len);
            DebugMsg(DEBUG_PRO, "Tx To Srvc %d Bytes]\r\n", pSndInf->Len);            
            RetryCnt = 0;   
            PtlSendState = psSend;
        case psSend:
            memcpy(pSndInf->pBuf, (char *)&pSndInf->Len, PIPE_LEN_INFO_SIZE);
            GprsSndDataPost(pSndInf->pBuf, pSndInf->Len + PIPE_LEN_INFO_SIZE, 1);
//            pipeDataWrite(pGprsSnd, pSndInf->pBuf, pSndInf->Len);

			if(AppDebug.Bits.GprsSndData && AppDebug.Bits.Enable) {    
		#if DEBUG_USE_STR
					DebugStrMsg("SEND:", pSndInf->pBuf+PIPE_LEN_INFO_SIZE+PRO_BEFOR_MSGBODY_SIZE, pSndInf->Len- PRO_MIN_SIZE);
		#else
					DebugHexMsg("", pSndInf->pBuf+PIPE_LEN_INFO_SIZE, pSndInf->Len);
		#endif
			}

            if(pSndInf->info.Bits.NeedResp) {
                Ack = GetRsp(pSndInf->Cmd);
                WaitRsp(pSndInf->Cmd);
                WaitNms = 0;                  
                PtlSendState = psAck;
            } else {
                *pRlt = TRUE;
                bExitSend = TRUE; 
                PtlSendState = psStart;
            }           
            break;
        case psAck:
            WaitNms += Nms;
            if(GetAckVaule() == Ack) {                          //  收到应答                        
                *pRlt = TRUE;
                bExitSend = TRUE;
                PtlSendState = psStart;
            } else if(WaitNms >= 5000) {  //  5s                
                if(++RetryCnt > PPR_SEND_RETRY_NUM) { 
                    *pRlt = FALSE;
                    bExitSend = TRUE;
                    PtlSendState = psStart;
                    DebugMsg(DEBUG_PRO, "Server No Answer\r\n");
                } else {
                    PtlSendState = psSend;
                    DebugMsg(DEBUG_PRO, "Retry %d / %d\r\n", RetryCnt, PPR_SEND_RETRY_NUM);
                }                        
                break;
            }
            break;
        default:            
            *pRlt = FALSE;
            bExitSend = TRUE;
            PtlSendState = psStart;
            DebugMsg(DEBUG_PRO, "Send stat err\r\n");
            break;
    }

    return bExitSend;
}

const char CutLineHead[] = "\r\n/************************************";
const char CutLineEnd[]  = "*************************************/\r\n";


TIME_SYSTICK Heart_CycleMoment;

//static u32 HeartTime = 0;                                           //  心跳发送计时    
void    ClearHeartTimer(void)
{
    SysTime_Fresh(&Heart_CycleMoment);
//    HeartTime = 0;                                                  //  数据发送成功,清除心跳计时
}



void    Task_ProSend(u16 Nms)
{                                 
    static u32 StepDelay = 0;                                       //  流程延时时间
    static bool bSendHeart = FALSE; 
//  	static bool  bSendPara = FALSE;
    char bRlst = FALSE;
    char *pProBody = &SendBuf[PIPE_LEN_INFO_SIZE+PRO_BEFOR_MSGBODY_SIZE];

         
    if(RegDelay > Nms) {
        RegDelay -= Nms;
    } else {
        RegDelay = 0;
    }

//    if(ParaUploadDelay.Bits.Flag) {
//        ParaUploadDelay.Bits.Timer += Nms;        
//        if(ParaUploadDelay.Bits.Timer >= 1000) {
//            ParaUploadDelay.Val = 0;
//        }
//    }
	 if (InitParaUp.Bits.flag)
	 	{
	 		InitParaUp.Bits.timer += Nms;
			if (InitParaUp.Bits.timer >= 1000* 30)
			{
				ParaUpload.Bits.Send = TRUE;
				InitParaUp.val = 0;
			}
	 	}
	
    /*
     *  心跳数据
     */
    if(gprsIsConnect()) {
     //   HeartTime += Nms;
    //    if(HeartTime >= GpSysPara->Net.Interval*1000) 
        if(SysTime_Delay(&Heart_CycleMoment) >= (GpSysPara->Net.Interval)*1000)     
        {
            SysTime_Fresh(&Heart_CycleMoment);
        //    HeartTime = 0;
            bSendHeart = TRUE;
        }
		
        /*
        if((bSendPara == FALSE) && (SysTime_Delay(&Heart_CycleMoment) >= 60*1000))
        {
            bSendPara = TRUE;
        }
        */
    } 
    else 
    {
        SysTime_Fresh(&Heart_CycleMoment);
     //   HeartTime = 0;
    } 

    if(ModelIsFtping()) {
        return;
    }

    switch(ProSndInf.Step) {
        case PRO_STEP_START:
			//DebugMsg(DEBUG_NONE,"step_start\r\n");
			if(isGprsCon()) 
            {                   
                if(ProSndInf.Bits.IsReg) 
                {
               //     ProTrans(PRO_STEP_HEART_INFO);
                  ProTrans(PRO_STEP_TIME_PARA);
                } 
                else 
                {
                    ProTrans(PRO_STEP_REG);
                    if(ParaUpload.Bits.Resend) 
                    {
                        ParaUpload.Flag = 0;
                      ParaUpload.Bits.Send = TRUE;
                    }
                }
            } 
            else 
            {
                ProSndInf.Bits.IsReg = FALSE;
//                ProSndInf.Bits.IsTimeChk = FALSE;
            }
            break;            
      
        case PRO_STEP_REG:                                          //  注册             
		//DebugMsg(DEBUG_NONE,"step_reg\r\n");
			if((!ProSndInf.Bits.IsReg) && (0 == RegDelay)) 
            {  
                GetRegister(pProBody, &SendLen);  
                DebugMsg(DEBUG_NONE, "%s     Reg     %s", (char*)CutLineHead, (char*)CutLineEnd);
                                
                SendData.Cmd  = TERMINAL_REG;
                SendData.Len  = SendLen;
                SendData.pBuf = SendBuf;                
                SendData.info.flag = 0;
                SendData.info.Bits.bBufEn = 1;
                SendData.info.Bits.NeedResp = TRUE;

                ProTrans(PRO_STEP_SEND_DATA);
                break;
            } 
            else if(ProSndInf.Bits.IsReg) 
            {
             //   ProTrans(PRO_STEP_HEART_INFO);
                ProTrans(PRO_STEP_TIME_PARA);
			
    
            }
            break;
            
        case PRO_STEP_TIME_PARA:                                    //  参数上传
			//DebugMsg(DEBUG_NONE,"step_time_para\r\n");
			if(ParaUpload.Bits.Send) 
            {   
            
             
                GetPltAllPara(pProBody, &SendLen);
                DebugMsg(DEBUG_NONE, "%s Para Upload %s", (char*)CutLineHead, (char*)CutLineEnd);
                
                SendData.Cmd  = TERMINAL_TIME_PARA;                    
                SendData.Len  = SendLen;
                SendData.pBuf = SendBuf;
                SendData.info.flag = 0;
                SendData.info.Bits.NeedResp = TRUE;
                SendData.info.Bits.bBufEn = 1;
                
                ProTrans(PRO_STEP_SEND_DATA);
                break;
            } 
            ProTrans(PRO_STEP_HEART_INFO);
            break;
            
        case PRO_STEP_HEART_INFO:                                   //  心跳数据
		//DebugMsg(DEBUG_NONE,"step_heart_info\r\n");
			if(bSendHeart) 
            {
                bSendHeart = FALSE;

                GetHeartData(pProBody, &SendLen);
                DebugMsg(DEBUG_NONE, "%s    Heart    %s", (char*)CutLineHead, (char*)CutLineEnd);
                
                SendData.Cmd  = TERMINAL_HEART;                    
                SendData.Len  = SendLen;
                SendData.pBuf = SendBuf;
                SendData.info.flag = 0;
                SendData.info.Bits.NeedResp = TRUE;                                    
                SendData.info.Bits.bBufEn = 1;
                
                ProTrans(PRO_STEP_SEND_DATA);
                break;
            }
        //    ProTrans(PRO_STEP_TIME_PARA);
            ProTrans(PRO_STEP_STATUS_UPLOAD);
          //  JReset();
            break;  
                        
        
        case PRO_STEP_VFD_INFO:
			//DebugMsg(DEBUG_NONE,"step_vfd_info\r\n");
			if(SvrVfdOpt.Bits.RspFlg) {
                SvrVfdOpt.Bits.RspFlg = FALSE;
                GetVfdOptInfo(pProBody, &SendLen);  
                DebugMsg(DEBUG_NONE, "%s  Vfd Data   %s", (char*)CutLineHead, (char*)CutLineEnd);
                
                SendData.Cmd  = SERVER_VFD_RESP;                    
                SendData.Len  = SendLen;
                SendData.pBuf = SendBuf;
                SendData.info.flag = 0;
                SendData.info.Bits.NeedResp = FALSE;
                SendData.info.Bits.bBufEn = 1;
                
                ProTrans(PRO_STEP_SEND_DATA);
                break;
            }
            ProTrans(PRO_STEP_EVENT_INFO);
            break;
        case PRO_STEP_EVENT_INFO:                                   //  事件上传
		//DebugMsg(DEBUG_NONE,"step_event_info\r\n");
			if(SysEvent.Flag.Flag) {
                GetEventInfo(pProBody, &SendLen);
                SysEvent.Flag.Flag = 0;
                DebugMsg(DEBUG_NONE, "%s    Event    %s", (char*)CutLineHead, (char*)CutLineEnd);
                
                SendData.Cmd  = TERMINAL_EVENT_UPLOAD;                    
                SendData.Len  = SendLen;
                SendData.pBuf = SendBuf;
                SendData.info.flag = 0;
                SendData.info.Bits.NeedResp = TRUE;
                SendData.info.Bits.bBufEn = 1;
                
                ProTrans(PRO_STEP_SEND_DATA);
                break;
            }
         //   ProTrans(PRO_STEP_SMS_UPLOAD); 
                        ProTrans(PRO_STEP_UPDATE);
            break;
//#if 0                        
//        case PRO_STEP_SMS_UPLOAD:                                   //  运营商短信上传
//            if(OperatorSMS.Flag) {
//                OperatorSMS.Flag = FALSE;   
//                GetOperatorSMSInfo(pProBody, &SendLen); 
//                DebugMsg(DEBUG_NONE, "%s SMS Upload  %s", (char*)CutLineHead, (char*)CutLineEnd);
//                
//                SendData.Cmd  = TERMINAL_SMS_UPLOAD;                    
//                SendData.Len  = SendLen;
//                SendData.pBuf = SendBuf;
//                SendData.info.flag = 0;
//                SendData.info.Bits.NeedResp = TRUE;
//                SendData.info.Bits.bBufEn = 1;    
//                
//                ProTrans(PRO_STEP_SEND_DATA);
//                break;                
//            }
//            ProTrans(PRO_STEP_SMS_SEND_CNT);
//            break;

//        case PRO_STEP_SMS_SEND_CNT:                                 //  短信发送个数统计
//            if(SMSStatistics.Flag) {
//                SMSStatistics.Flag = FALSE;
//                GetSMSSuccessCntInfo(pProBody, &SendLen);
//                DebugMsg(DEBUG_NONE, "%s   SMS CNT   %s", (char*)CutLineHead, (char*)CutLineEnd);
//                
//                SendData.Cmd  = TERMINAL_SMS_CNT;                    
//                SendData.Len  = SendLen;
//                SendData.pBuf = SendBuf;
//                SendData.info.flag = 0;
//                SendData.info.Bits.NeedResp = TRUE;
//                SendData.info.Bits.bBufEn = 1;
//                
//                ProTrans(PRO_STEP_SEND_DATA);
//                break;                
//            }
//            ProTrans(PRO_STEP_UPDATE);
//            break;
//#endif                        
        case PRO_STEP_UPDATE:                                       //  获取升级文件
	//	DebugMsg(DEBUG_NONE,"step_update\r\n");
			if(Update.Bits.Enable) {
                GetUpdateData(pProBody, &SendLen);
                DebugMsg(DEBUG_NONE, "%s Update: %X / %X %s", (char*)CutLineHead, Update.FileAddr, Update.FileSize, (char*)CutLineEnd);
                
                SendData.Cmd  = TERMINAL_UPDATE;                    
                SendData.Len  = SendLen;
                SendData.pBuf = SendBuf;
                SendData.info.flag = 0;
                SendData.info.Bits.NeedResp = TRUE;
                SendData.info.Bits.bBufEn = 1;
                
                ProTrans(PRO_STEP_SEND_DATA); 
                break;
            }
          // ProTrans(PRO_STEP_STATUS_UPLOAD);
               JReset();
            break;
        case PRO_STEP_STATUS_UPLOAD:
		//	DebugMsg(DEBUG_NONE,"status_upload\r\n");
			if (GpSysStat->Share.UpdataParaFlag & 0x000f)
			{
				GetStatusUpData(pProBody, &SendLen);
				DebugMsg(DEBUG_NONE, "%s Status Upload %s", (char*)CutLineHead, Update.FileAddr, Update.FileSize, (char*)CutLineEnd);
                
				SendData.Cmd  = TERMINAL_STATUS_UPLOAD;                    
				SendData.Len  = SendLen;
				SendData.pBuf = SendBuf;
				SendData.info.flag = 0;
				SendData.info.Bits.NeedResp = TRUE;
				SendData.info.Bits.bBufEn = 1;

				ProTrans(PRO_STEP_SEND_DATA); 
				break;
			}
			ProTrans(PRO_STEP_VFD_INFO); 
			//JReset();
			break;
        case PRO_STEP_SEND_DATA:
			//	DebugMsg(DEBUG_NONE,"send_data\r\n");
            if(ProDataSend(&SendData, Nms, &bRlst)) {
                if(bRlst) 
                {
                    switch(SendData.Cmd) 
                    {
                        case TERMINAL_REG:
                            RegTimerStop();
                            if(ProSndInf.Bits.FirstRun) 
                            {
                                ProSndInf.Bits.FirstRun = FALSE;                    
                            }  
                            break;
                        case TERMINAL_TIME_PARA:
                            ParaUploadDelay.Bits.Flag = TRUE;
                            break;
                        default:
                            break;
                    }
                    ProNextStat();                                  //  继续上一状态的下一状态
                } else {
                    switch(SendData.Cmd) {
                        case TERMINAL_REG:
                            RegDelay = 1 * 60000;                   //  间隔1min
                            break;
                        default:
                            break;
                    }
                    ProTrans(PRO_STEP_FAULT);
                }
            }            
            break;
        case PRO_STEP_FAULT: 
			//	DebugMsg(DEBUG_NONE,"step_fault\r\n");
//            DebugMsg(DEBUG_NONE, "%s  Fault %s", (char*)CutLineHead, (char*)CutLineEnd);
            GprsReConnect();
            ProSndInf.Bits.IsReg = FALSE;                           //  防止重连后不重新鉴权和校时
//            ProSndInf.Bits.IsTimeChk = FALSE;
            GprsSndDataFlush();                                     //  清掉待发送的数据
            StepDelay = 3000;                                       //  延时3s,待GPRS连接标识清除,否则影响协议发送流程
            ProTrans(PRO_STEP_DELAY);
            break;
        case PRO_STEP_DELAY:  
		//		DebugMsg(DEBUG_NONE,"step_delay\r\n");
            if(StepDelay > Nms) {
                StepDelay -= Nms;
            } else {
                StepDelay = 0;                
                JReset();
            }  
            break;    
        default:
            JReset();
            break;
    }   
}

 
void    DevStatToSystem(void)
{
    u8 tmp = 0;
    
    if(ParaUploadDelay.Bits.Flag) 
    {
        GpSysStat->Share.CSQ = GprsCtrlInfo.CSQInf.Value;
        GpSysStat->Share.GPRSLac = StringToHex(GprsCtrlInfo.LocInf.lac, 2);
        GpSysStat->Share.GPRSCID = StringToHex(GprsCtrlInfo.LocInf.ci, 2);    
    }
    else
    {
        tmp = GetMultLoc(0x03,0);
        GpSysStat->Share.CSQ = (tmp==0) ? 0 : (113- tmp)/2; //GprsCtrlInfo.CSQInf.Value;
        GpSysStat->Share.GPRSLac = GetMultLoc(0x01,0);//StringToHex(GprsCtrlInfo.LocInf.lac, 2);
        GpSysStat->Share.GPRSCID = GetMultLoc(0x02,0);//StringToHex(GprsCtrlInfo.LocInf.ci, 2);
    }
    DebugCheck.GprsSignal = GpSysStat->Share.CSQ ;
 #ifdef XLINK
    if (GpSysStat->Share.CSQ > 23)
	{
		HIGH_CSQ;
	}
	else if (GpSysStat->Share.CSQ > 15)
	{
		MEDIUM_CSQ;
	}
	else if (GpSysStat->Share.CSQ > 7)
	{
		LOW_CSQ;
	}
	else 
	{
		NO_CSQ;
	} 
#endif
}



void Task_ProDeal(void)
{
    if(pipeDataRead(pATResp, dtuTmpBuf, sizeof(dtuTmpBuf))) {
        ATCmdParse(dtuTmpBuf, strlen(dtuTmpBuf));
    }    
    
#if GPRS_DATA_EN    
    if(pipeDataRead(pGprsRcv, dtuTmpBuf, sizeof(dtuTmpBuf))) {
        LedOnSet(100, 100, 1);
        GPRSDataDeal(dtuTmpBuf);        
    } 
#endif    
}


char    IsReg(void)
{
    return ProSndInf.Bits.IsReg;
}



void JSON_RtcTimeGet(char *pBuf)
{
    char Rtc_Buf[19]={0};
    
    SYS_TIME_STRUCT pSysTime;
    
    GetRtctime(&pSysTime);
    
    Rtc_Buf[0]=0x32;
    Rtc_Buf[1]=0x30;
    Rtc_Buf[2]=0x30+pSysTime.Year/10;
    Rtc_Buf[3]=0x30+pSysTime.Year%10;
    Rtc_Buf[4]='-';
        
    Rtc_Buf[5]=0x30+pSysTime.Month/10;
    Rtc_Buf[6]=0x30+pSysTime.Month%10;
    Rtc_Buf[7]='-';
        
    Rtc_Buf[8]=0x30+pSysTime.Day/10;
    Rtc_Buf[9]=0x30+pSysTime.Day%10;
    Rtc_Buf[10]=' ';

    Rtc_Buf[11]=0x30+pSysTime.Hour/10;
    Rtc_Buf[12]=0x30+pSysTime.Hour%10;
    Rtc_Buf[13]=':';

    Rtc_Buf[14]=0x30+pSysTime.Min/10;
    Rtc_Buf[15]=0x30+pSysTime.Min%10;
    Rtc_Buf[16]=':';

    Rtc_Buf[17]=0x30+pSysTime.Sec/10;
    Rtc_Buf[18]=0x30+pSysTime.Sec%10;

    JSON_StringValToObject(pBuf,"RTC", (char*)Rtc_Buf);
}

//void  GetNULLData(char *pBuf, u16 *pLen)
//{
//    JSON_ObjectBegin(pBuf);
//    JSON_RtcTimeGet(pBuf);
//    JSON_NumberValToObject(pBuf, "PS", GpSysPara->Dev.Bits.PS);    
//    JSON_ObjectEnd(pBuf);

//    *pLen = strlen(pBuf);
//}
