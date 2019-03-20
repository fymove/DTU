#define _InPara
#include "app_para.h"
#include "includes.h"

char    crc8Cal(char* pBuf, short Len)
{
    short i;
    char Sum = 0;
    
    for(i=0; i<Len; i++) {
        Sum += pBuf[i];
    }

    return Sum;
}

static char _flashErase(int Addr)
{
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR | FLASH_FLAG_OPTERR); 
    if (FLASH_COMPLETE != FLASH_ErasePage(Addr)) {
        return FALSE;
    }
    FLASH_Lock(); 
    
    return TRUE;
}

char     _flashWrite(int Addr, char *pBuf, short Len)
{
    short i;
    short Cnt = (Len >> 2) + ((Len & 0x3) ? 1 : 0);    
    FLASH_Status stat;
    
    FLASH_Unlock();
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR | FLASH_FLAG_OPTERR); 
    for(i=0; i<Cnt; i++) {
        stat = FLASH_ProgramWord(Addr, *((uint32_t *)pBuf));
        if(FLASH_COMPLETE == stat) {
            Addr += 4;
            pBuf += 4;
        } else { 
            DebugMsg(DEBUG_PARA, "Flash Store Fail %d!!!!!!!!!!!\r\n", stat);
            return FALSE;
        }
    }

    FLASH_Lock(); 

    return TRUE;
}

void    _flashRead(int Addr, char *pBuf, short Len)
{
    short i = 0;
    short Cnt = Len >> 2;    
    uint32_t tmp;

    for(i=0; i<Cnt; i++) {
        *((uint32_t *)pBuf) = *(__IO uint32_t *)Addr;
        Addr += 4;
        pBuf += 4;
    }

    Cnt = Len & 0x3;
    if(Cnt) {
        tmp = *(__IO uint32_t *)Addr;
        for(i=0; i<Cnt; i++) {
            *pBuf++ = (tmp >> (i*8)) & 0xff;
        }
    }
}


void    DevParaDefault(PARA_TYPE_ENUM ParaType)
{   
    switch(ParaType) {
        case PARA_TYPE_SYS:
            memset((char *)SysParaBuf, 0, SYS_PARA_BUF_SIZE);                
            memcpy(GpSysPara->Dev.MachineSN, "0000000000", MAC_SN_SIZE);                            
            GpSysPara->Dev.MacYear  = 2017;        //机器生产日期，平台可修改        
            GpSysPara->Dev.MacMonth = 1;
            GpSysPara->Dev.MacDay   = 1;  
        
            memcpy(GpSysPara->Dev.ID, ID_HEADER, strlen(ID_HEADER));    
//            memcpy(GpSysPara->Dev.ID, "00", 2);    
            memcpy(&GpSysPara->Dev.ID[ID_HEADER_LEN], "000001", 6);    
            GpSysPara->Dev.DevYear  = 2017;        //终端设备生产日期，不可修改
            GpSysPara->Dev.DevMonth = 10;
            GpSysPara->Dev.DevDay   = 18;           
       //     memcpy(GpSysPara->Dev.PCBVer, PCB_VERSION, strlen(PCB_VERSION));
            memcpy(GpSysPara->Dev.AppVer, APP_VERSION, strlen(APP_VERSION));
            GpSysPara->Dev.Bits.AlmSaveFlg = TRUE;
            GpSysPara->Dev.Bits.PS = PS_MAM6080_6090;
        
            GpSysPara->Dev.PasswordAdrr[0] = 0xf000;  //控制器写数据密码地址
            GpSysPara->Dev.PasswordData[0] = 0xd6f0;  //控制器写数据密码值
        
            GpSysPara->Dev.PasswordAdrr[1] = 0xe000;
            GpSysPara->Dev.PasswordData[1] = 0xc5df;
            
            GpSysPara->Dev.PasswordAdrr[2] = 0xd000;
            GpSysPara->Dev.PasswordData[2] = 0xb4ce;
        
            GpSysPara->Dev.MeterNum = 1;
            GpSysPara->Dev.FlowNum  = 15;
            GpSysPara->Dev.BindSatus = 0;
            strcpy(GpSysPara->Net.Domain, SERVER_DOMAIN);
//            strcpy(GpSysPara->Net.APN, "CMNET");
            strcpy(GpSysPara->Net.APN, "CMMTM");
            strcpy(GpSysPara->Net.USR, "");
            strcpy(GpSysPara->Net.PWD, "");
            GpSysPara->Net.Port = SERVER_PORT;
            GpSysPara->Net.Interval = 120;                                     //  3min
            GpSysPara->Net.RealTime_Monitor = 0;
            DebugMsg(DEBUG_PARA, "SysPara Default\r\n");
            break;
        case PARA_TYPE_USR:
            memset((char *)UsrParaBuf, 0, USR_PARA_BUF_SIZE);
            GpUsrPara->Hour.MaxUseTime     = 0;           
            GpUsrPara->Hour.MaxOilFiltTime = 0;
            GpUsrPara->Hour.MaxOilSepaTime = 0;
            GpUsrPara->Hour.MaxGasFiltTime = 0; 
            GpUsrPara->Hour.MaxlubeTime    = 0;
            GpUsrPara->Hour.MaxGreaseTime  = 0;
            DebugMsg(DEBUG_PARA, "UsrPara Default\r\n");
            break;
        case PARA_TYPE_OHT:
            memset((char *)OthInfoBuf, 0, OTH_INFO_BUF_SIZE);    
            DebugMsg(DEBUG_PARA, "OthInfo Default\r\n");
            break;
        case PARA_TYPE_ALM:
            memset((char *)AlmInfoBuf, 0, ALM_INFO_BUF_SIZE);    
            DebugMsg(DEBUG_PARA, "AlmInfo Default\r\n");
            break;
        default:
            break;
    }
}

static SYS_PARA_BUF_STRUCT  TempPara;
static char DevParaRead(PARA_TYPE_ENUM ParaTyp)
{
    char bFind = FALSE;
    u16 *pRdCrc;
    u32 i, Num;
    u32 *pRdIdx, *pIndex;    
    u32 RdAddr, *pWrAddr;
    u32 ParaSize, BgnAddr, EndAddr;     
    void *pPara, *pRdPara = (void *)&TempPara;
   
    switch(ParaTyp) {
        case PARA_TYPE_SYS:        
            pPara    = GpSysPara;     
            pIndex   = &GpSysPara->Index; 
            pRdIdx   = &((SYS_PARA_BUF_STRUCT *)pRdPara)->Index;
            pRdCrc   = &((SYS_PARA_BUF_STRUCT *)pRdPara)->Crc;
            pWrAddr  = &ParaFat.SysParaAddr;
            BgnAddr  = SYS_PARA_FLASH_START_ADDR;
            EndAddr  = SYS_PARA_FLASH_END_ADDR;
            ParaSize = SYS_PARA_BUF_SIZE;
            break;
        case PARA_TYPE_USR:
            pPara    = GpUsrPara;     
            pIndex   = &GpUsrPara->Index; 
            pRdIdx   = &((USR_PARA_BUF_STRUCT *)pRdPara)->Index;
            pRdCrc   = &((USR_PARA_BUF_STRUCT *)pRdPara)->Crc;
            pWrAddr  = &ParaFat.UsrParaAddr;
            BgnAddr  = USR_PARA_FLASH_START_ADDR;
            EndAddr  = USR_PARA_FLASH_END_ADDR;
            ParaSize = USR_PARA_BUF_SIZE;
            break;
        case PARA_TYPE_ALM:        
            pPara    = GpAlmInfo;     
            pIndex   = &GpAlmInfo->Index; 
            pRdIdx   = &((ALM_INFO_BUF_STRUCT *)pRdPara)->Index;
            pRdCrc   = &((ALM_INFO_BUF_STRUCT *)pRdPara)->Crc;
            pWrAddr  = &ParaFat.AlmInfoAddr;
            BgnAddr  = ALM_INFO_FLASH_START_ADDR;
            EndAddr  = ALM_INFO_FLASH_END_ADDR;
            ParaSize = ALM_INFO_BUF_SIZE;
            break;                           
                     
        case PARA_TYPE_OHT:        
            pPara    = GpOthInfo;     
            pIndex   = &GpOthInfo->Index; 
            pRdIdx   = &((OTH_INFO_BUF_STRUCT *)pRdPara)->Index;
            pRdCrc   = &((OTH_INFO_BUF_STRUCT *)pRdPara)->Crc;
            pWrAddr  = &ParaFat.OthInfoAddr;
            BgnAddr  = OTH_INFO_FLASH_START_ADDR;
            EndAddr  = OHT_INFO_FLASH_END_ADDR;
            ParaSize = OTH_INFO_BUF_SIZE;
            break;            
            
        default:
            return FALSE;
    }

    Num = (EndAddr - BgnAddr) / ParaSize; 
    RdAddr = BgnAddr;
    for(i=0; i<Num; i++) {
        _flashRead(RdAddr, (char *)pRdPara, ParaSize);
        if(*pRdCrc == CRC16_1((char*)pRdPara, ParaSize-sizeof(GpSysPara->Crc))) {
            if(*pRdIdx > *pIndex) {
                bFind = TRUE;
                memcpy(pPara, pRdPara, ParaSize);
                *pWrAddr = RdAddr + ParaSize;
                if(*pWrAddr >= EndAddr) {
                    *pWrAddr = BgnAddr;
                }
            }
        } else {
            if(bFind && (0xffffffff == *pRdIdx)) {
                break;
            }
        }

        RdAddr += ParaSize;
    }

    return bFind;  
}

void    SysParaRead(void)
{        
    if(!DevParaRead(PARA_TYPE_SYS)) {
        DevParaDefault(PARA_TYPE_SYS);
        ParaFat.SysParaAddr = SYS_PARA_FLASH_START_ADDR;
        ParaFat.Bits.SysPara = TRUE;
    }
    if(!DevParaRead(PARA_TYPE_USR)) {
        DevParaDefault(PARA_TYPE_USR);
        ParaFat.UsrParaAddr = USR_PARA_FLASH_START_ADDR;
        ParaFat.Bits.UsrPara = TRUE;
    }

    if(!DevParaRead(PARA_TYPE_ALM)) {
        DevParaDefault(PARA_TYPE_ALM);
        ParaFat.AlmInfoAddr = ALM_INFO_FLASH_START_ADDR;
        ParaFat.Bits.AlmInfo = TRUE;
    }
    DebugMsg(DEBUG_PARA, "AlmInf    %04X\r\n", GpAlmInfo->Alarm.Flag);
    DebugMsg(DEBUG_PARA, "PreAlmInf %04X\r\n", GpAlmInfo->PreAlarm.Flag);

    if(!DevParaRead(PARA_TYPE_OHT)) {
        DevParaDefault(PARA_TYPE_OHT);
        ParaFat.OthInfoAddr = OTH_INFO_FLASH_START_ADDR;
        ParaFat.Bits.OthInfo = TRUE;
    }   

#ifdef  PARA_NOT_SAVE
    DevParaDefault(PARA_TYPE_SYS);
    DevParaDefault(PARA_TYPE_USR);
    DevParaDefault(PARA_TYPE_ALM);
    DevParaDefault(PARA_TYPE_OHT);
#endif  

//    memcpy(GpSysPara->Dev.PCBVer, PCB_VERSION, strlen(PCB_VERSION));
    memcpy(GpSysPara->Dev.AppVer, APP_VERSION, strlen(APP_VERSION));
//    memcpy(&GpSysPara->Dev.ID[ID_HEADER_LEN], "100036", 6);        //临时升级修改ID号
	
}



void DevParaWrite(PARA_TYPE_ENUM ParaTyp)
{            
    u16 *pCrc;
    u32 *pIndex;
    u32 *pWrAddr;    
    u32 BgnAddr, EndSize, ParaSize;
    void *pPara;
    
    switch(ParaTyp) {
        case PARA_TYPE_SYS:
            pPara    = GpSysPara;
            pCrc     = &GpSysPara->Crc;
            pIndex   = &GpSysPara->Index;            
            pWrAddr  = &ParaFat.SysParaAddr;  
            BgnAddr  = SYS_PARA_FLASH_START_ADDR;
            EndSize  = SYS_PARA_FLASH_END_ADDR;
            ParaSize = SYS_PARA_BUF_SIZE;
            break;
        case PARA_TYPE_USR:
            pPara    = GpUsrPara;
            pCrc     = &GpUsrPara->Crc;
            pIndex   = &GpUsrPara->Index;            
            pWrAddr  = &ParaFat.UsrParaAddr;  
            BgnAddr  = USR_PARA_FLASH_START_ADDR;
            EndSize  = USR_PARA_FLASH_END_ADDR;
            ParaSize = USR_PARA_BUF_SIZE;
            break; 
        case PARA_TYPE_ALM:
            pPara    = GpAlmInfo;
            pCrc     = &GpAlmInfo->Crc;
            pIndex   = &GpAlmInfo->Index;            
            pWrAddr  = &ParaFat.AlmInfoAddr;  
            BgnAddr  = ALM_INFO_FLASH_START_ADDR;
            EndSize  = ALM_INFO_FLASH_END_ADDR;
            ParaSize = ALM_INFO_BUF_SIZE;
            break;             
        case PARA_TYPE_OHT:
            pPara    = GpOthInfo;
            pCrc     = &GpOthInfo->Crc;
            pIndex   = &GpOthInfo->Index;            
            pWrAddr  = &ParaFat.OthInfoAddr;  
            BgnAddr  = OTH_INFO_FLASH_START_ADDR;
            EndSize  = OHT_INFO_FLASH_END_ADDR;
            ParaSize = OTH_INFO_BUF_SIZE;
            break;    
        default:
            return;
    }

    /*
     *  当前写地址在扇区起始位置,则擦除当前写地址对应的扇区
     *  当前写地址和下一写地址不在同一扇区,且下一写地址不在扇区起始地址,则擦除下一写地址对应的扇区
     */
    if(0 == SECTOR_OFFSET_ADDR(*pWrAddr)) {                        //  
        _flashErase(SECTOR_BEGIN_ADDR(*pWrAddr));
    } else if(SECTOR_BEGIN_ADDR(*pWrAddr) != SECTOR_BEGIN_ADDR(*pWrAddr+ParaSize)) {
        if(SECTOR_OFFSET_ADDR(*pWrAddr+ParaSize)) {
            _flashErase(SECTOR_BEGIN_ADDR(*pWrAddr+ParaSize));
        }
    }

    (*pIndex)++;
    (*pCrc) = CRC16_1((char *)pPara, ParaSize-sizeof(*pCrc));
    _flashWrite(*pWrAddr, (char *)pPara, ParaSize);
    (*pWrAddr) += ParaSize;
    if(((*pWrAddr) + ParaSize) >= EndSize) {
        (*pWrAddr) = BgnAddr;
    }
}

void    ParaBackRead(PARA_TYPE_ENUM ParaType)
{             
    u32 BgnAddr, EndSize, ParaSize;
    void *pPara;
    char *pRdBuf = (char *)&TempPara;
    u32 BkRdAddr;
    
    switch(ParaType) {
        case PARA_TYPE_SYS:
            pPara    = GpSysPara;
            BkRdAddr = ParaFat.SysParaAddr;  
            BgnAddr  = SYS_PARA_FLASH_START_ADDR;
            EndSize  = SYS_PARA_FLASH_END_ADDR;
            ParaSize = SYS_PARA_BUF_SIZE;            
            break;
        case PARA_TYPE_USR:
            pPara    = GpUsrPara;
            BkRdAddr = ParaFat.UsrParaAddr;  
            BgnAddr  = USR_PARA_FLASH_START_ADDR;
            EndSize  = USR_PARA_FLASH_END_ADDR;
            ParaSize = USR_PARA_BUF_SIZE;
            break;  
        case PARA_TYPE_ALM:
            pPara    = GpAlmInfo;
            BkRdAddr = ParaFat.AlmInfoAddr;  
            BgnAddr  = ALM_INFO_FLASH_START_ADDR;
            EndSize  = ALM_INFO_FLASH_END_ADDR;
            ParaSize = ALM_INFO_BUF_SIZE;
            break;    
        case PARA_TYPE_OHT:
            pPara    = GpOthInfo;
            BkRdAddr = ParaFat.OthInfoAddr;  
            BgnAddr  = OTH_INFO_FLASH_START_ADDR;
            EndSize  = OHT_INFO_FLASH_END_ADDR;
            ParaSize = OTH_INFO_BUF_SIZE;
            break;             
        default:
            break;
    }

    if(BkRdAddr != BgnAddr) {
        BkRdAddr -= ParaSize;
    } else {
        BkRdAddr = EndSize - ParaSize;
    }

#if 0                                                               
    _flashRead(BkRdAddr, (char *)pPara, ParaSize);    
#else                                                               //  test
    _flashRead(BkRdAddr, pRdBuf, ParaSize);
    if(memcmp((char *)pRdBuf, (char *)pPara, ParaSize)) {
        DebugMsg(DEBUG_PARA, "Write Para != Read Para\r\n");
        memcpy(pPara, pRdBuf, ParaSize);
        GpOthInfo->Error.ParaWrErrCnt++;
    }
#endif      
}


void    SysParaStorage()
{
#ifdef  PARA_NOT_SAVE
    return;
#endif
    if(ParaFat.Bits.SysPara) {
        ParaFat.Bits.SysPara = FALSE;
        DevParaWrite(PARA_TYPE_SYS);           
        DebugMsg(DEBUG_PARA, "Store SysPara\r\n");        
    }
    
    if(ParaFat.Bits.UsrPara) {
        ParaFat.Bits.UsrPara = FALSE;
        DevParaWrite(PARA_TYPE_USR);
        DebugMsg(DEBUG_PARA, "Store UsrPara\r\n");
    }    

    if(ParaFat.Bits.OthInfo) {
        ParaFat.Bits.OthInfo = FALSE;
        DevParaWrite(PARA_TYPE_OHT);
        DebugMsg(DEBUG_PARA, "Store OthInfo\r\n");
    }   

    if(ParaFat.Bits.AlmInfo) {
        if(GpSysPara->Dev.Bits.AlmSaveFlg && IsReg()) 
        {
            ParaFat.Bits.AlmInfo = FALSE;
            GpAlmInfo->Alarm.Flag = AlmStat.Alarm.Flag;
            GpAlmInfo->PreAlarm.Flag = AlmStat.PreAlarm.Flag;
            DevParaWrite(PARA_TYPE_ALM);
            DebugMsg(DEBUG_PARA, "Store AlmInfo    %04X\r\n", GpAlmInfo->Alarm.Flag);
            DebugMsg(DEBUG_PARA, "Store PreAlmInfo %04X\r\n", GpAlmInfo->PreAlarm.Flag);
        }    
    }    
}

void    SysVarInit(void)
{
    GpSysPara = (SYS_PARA_BUF_STRUCT *)&SysParaBuf;
    GpUsrPara = (USR_PARA_BUF_STRUCT *)&UsrParaBuf;
    GpAlmInfo = (ALM_INFO_BUF_STRUCT *)&AlmInfoBuf;    
    GpOthInfo = (OTH_INFO_BUF_STRUCT *)&OthInfoBuf;
    GpSysStat = (SYS_STAT_BUF_STRUCT *)&SysStatBuf;
	
}


char    FieldVarMaxLen(u16 BgnAddr, u16 EndAddr, u16 Addr, u16 *pMaxLen)
{
    char ret = FALSE;
    u16  VarCnt = 0;

    if((Addr >= BgnAddr) && (Addr <= EndAddr)) {
        VarCnt = EndAddr - Addr + 1;                                //  变量个数
        *pMaxLen = VarCnt << 1;                                     //  变量长度
        ret = TRUE;
    }

    return ret;
}

char    FieldValOffset(u16 BgnAddr, u16 EndAddr, u16 Addr, u16 *pOffset)
{
    char ret = FALSE;
    u16  VarCnt = 0;

    if((Addr >= BgnAddr) && (Addr <= EndAddr)) {
        VarCnt = Addr - BgnAddr;                                    //  变量个数
        *pOffset = VarCnt;                                          //  变量长度
        ret = TRUE;
    }

    return ret;
}


char    SpecAddrRead(u16 ReadAddr, char *pBuf, u16 *pLen, ADDR_TYPE_ENUM *pType)
{
    char Ret = TRUE;
    static u16 temp;
    
    *pLen = 2;
    *pType = ADDR_TYPE_OTHER;
    
    switch(ReadAddr)
    {
        case 150:
        {
            memcpy(pBuf, (char *)&GprsCtrlInfo.IMEI, 16);
            *pType = ADDR_TYPE_STRING;
            *pLen = 16;
            break;
        }
	    case 158:
        {
            memcpy(pBuf, (char *)&GprsCtrlInfo.CCID, 20);
            *pType = ADDR_TYPE_STRING;
            *pLen = 20;
            break;
        }
        case 300:
        {
            memcpy(pBuf, (char *)&GpSysStat->Share.AlmVal, 2);          //  一体机AlmStat.Alarm.Flag,4字节
            break;
        }
        case 302:
        {
            memcpy(pBuf, (char *)&GpSysStat->Share.PreAlmVal, 2);       //  一体机AlmStat.PreAlarm.Flag,4字节
            break;
        }
        
        case 166:
        case 168:
        case 170:
        case 172:
        case 174:
        case 176:
        {
            temp = GetMultLoc(0x01,(ReadAddr-166)/2);
            memcpy(pBuf, (char *)&temp, 2);
            break;
        }
        
        case 167:
        case 169:
        case 171:
        case 173:
        case 175:
        case 177:                                
        {
            temp = GetMultLoc(0x02,(ReadAddr-167)/2);
            memcpy(pBuf, (char *)&temp, 2);
            break;
        }
        
        case 178:
        case 179:
        case 180:
        case 181:
        case 182:
        case 183:                                
        {
            temp = GetMultLoc(0x03,(ReadAddr-178));
            memcpy(pBuf, (char *)&temp, 2);
            break;
        }
        
        default : Ret = FALSE; break;
    }
    

    return Ret;  
}

char    SysVarRead(u16 ReadAddr, char *pBuf, u16 *pLen, ADDR_TYPE_ENUM *pType)
{    
    char ret = FALSE; 
    u16 *pField;
    u16 OffsetAddr;
    u16 FieldEndAddr;
    u16 FieldStartAddr;    
    
    /*
     *  系统参数
     */
    if((ReadAddr >= DEV_PARA_START_ADDR) && (ReadAddr <= DEV_PARA_END_ADDR)) {
        FieldStartAddr = DEV_PARA_START_ADDR;
        FieldEndAddr = DEV_PARA_END_ADDR;
        pField = (u16 *)&GpSysPara->Dev;
        if( (2513 == ReadAddr) || (2518 == ReadAddr)||(2523 == ReadAddr) ) {
           *pLen = 10;
            *pType = ADDR_TYPE_STRING;
        } 
        else if(2500 == ReadAddr)
        {
            *pLen = 20;
            *pType = ADDR_TYPE_STRING;
        }
        else 
        {
            *pLen = 2;
            *pType = ADDR_TYPE_OTHER;
        }
    /*
     *  网络参数
     */
    } else if((ReadAddr >= NET_PARA_START_ADDR) && (ReadAddr <= NET_PARA_END_ADDR)) {
        FieldStartAddr = NET_PARA_START_ADDR;
        FieldEndAddr = NET_PARA_END_ADDR;
        pField = (u16 *)&GpSysPara->Net;
        if((2660 == ReadAddr) || (2661 == ReadAddr)|| (2662 == ReadAddr)) {
            *pLen = 2;
            *pType = ADDR_TYPE_OTHER;
        } else{
            *pLen = 30;
            *pType = ADDR_TYPE_STRING;
        } 
	
//    /*
//     *  最大时间
//     */        
//    }/*else if( (ReadAddr >= MAX_TIME_START_ADDR) && (ReadAddr <= MAX_TIME_END_ADDR)) {
//		if (GpSysPara->Dev.Bits.PS == PS_HC)
//		{
//			 memcpy(pBuf, (char *)&GpUsrPara->Hour.MaxUseTime, 2);
//			 return true;
//		}
//		if ((GpSysPara->Dev.Bits.PS ==111) )
//		return FALSE;
//        FieldStartAddr = MAX_TIME_START_ADDR;
//        FieldEndAddr = MAX_TIME_END_ADDR;
//        pField = (u16 *)&GpUsrPara->Hour; 
//        *pLen = (2100 == ReadAddr) ? 4 : 2;
//        *pType = ADDR_TYPE_OTHER;  
//    /*
//     *  运行时间
//     */
//     /*
//    } else if((ReadAddr >= RUN_HOUR_START_ADDR) && (ReadAddr <= RUN_HOUR_END_ADDR)) {
//        FieldStartAddr = RUN_HOUR_START_ADDR;
//        FieldEndAddr = RUN_HOUR_END_ADDR;
//        pField = (u16 *)&GpSysStat->Run; 
//      //  *pLen = ((2000 == ReadAddr) || (2002 == ReadAddr)) ? 4 : 2;
//      *pLen =  2;
//        *pType = ADDR_TYPE_OTHER;
//     */
    } else if(XYMeterVarRead(ReadAddr, pBuf, pLen, pType)) {
        return TRUE;            
    } else if(SpecAddrRead(ReadAddr, pBuf, pLen, pType)) {
        return TRUE;
    } else {
        *pLen = 2;
        *pType = ADDR_TYPE_OTHER;  
        ret = TRUE;
        switch(ReadAddr) {
            case 1:
                memcpy(pBuf, (char *)&GpSysStat->Share.Pressure1, 2);
                break;
            case 2:
                memcpy(pBuf, (char *)&GpSysStat->Share.Temprature1, 2);
                break;
            case 3:
                memcpy(pBuf, (char *)&GpSysStat->Share.CSQ, 2);
                break;     
            case 5:
                memcpy(pBuf, (char *)&GpSysStat->Share.MachineStat, 2);
                break;
            case 6:
                memcpy(pBuf, (char *)&GpSysStat->Main.A_Current, 2);
                break;     
            case 7:
                memcpy(pBuf, (char *)&GpSysStat->Main.B_Current, 2);
                break;     
            case 8:
                memcpy(pBuf, (char *)&GpSysStat->Main.C_Current, 2);
                break;         
            default:
                 ret = Plt3SysVarRead(ReadAddr, pBuf, pLen, pType);  
                if(ret == FALSE)
                {
                    ret = PltMam6080OtherVarRead(ReadAddr, pBuf, pLen, pType); //获取MAM6080其它参数
                }
                break;                    
        }  
           
        return ret;
    }

    if(FieldValOffset(FieldStartAddr, FieldEndAddr, ReadAddr, &OffsetAddr)) {
        memcpy(pBuf, (char *)(pField + OffsetAddr), *pLen);
        ret = TRUE;        
    }
    return ret;    
}

