#define _InDtuCfg
#include "app_dtucfg.h"
#include "includes.h"


char     dtuCfgDataCheck(char *pData, short Len)
{
    if(((char)CFG_DATA_HEAD_1 == *pData) &&
       ((char)CFG_DATA_HEAD_2 == *(pData+1)) &&
       ((char)CFG_DATA_END_1  == *(pData+Len-3)) &&
       ((char)CFG_DATA_END_2  == *(pData+Len-2)) &&
       ((char)CFG_DATA_END_3  == *(pData+Len-1))) {
        return TRUE;
       }
       
    return FALSE;
}

short    dtuCfgDataCrc(char *pData, short Len)
{
    short i;
    short Sum = 0;

    for(i=0; i<Len; i++) {
        Sum += *pData++;
    }

    return Sum;
}



short    dtuConfigResp(char Cmd, short Addr, char *pData, short DataLen, char *pResp)
{
    short Crc;
    char *pTmp = pResp;
    
    *pResp++ = CFG_DATA_HEAD_1;
    *pResp++ = CFG_DATA_HEAD_2;
    *pResp++ = 0x80 | Cmd;
    
    if(Addr) {
        *pResp++ = (Addr >> 8) & 0xff;
        *pResp++ = Addr & 0xff;
        *pResp++ = DataLen;
    }
    
    if(DataLen) {
        memcpy(pResp, pData, DataLen);
        pResp += DataLen;
    }
    Crc = dtuCfgDataCrc(pTmp+2, pResp - pTmp - 2);
    *pResp++ = (Crc >> 8) & 0xff;
    *pResp++ = Crc & 0xff;
    *pResp++ = CFG_DATA_END_1;
    *pResp++ = CFG_DATA_END_2;
    *pResp++ = CFG_DATA_END_3;    
    
    return  (pResp - pTmp);
}

unsigned int    BigEndConvert(char *p, char Len)
{
    unsigned short sTmp;
    unsigned int iTmp;    
    
    if(2 == Len) {
        sTmp = (*p << 8) | *(p+1);
        return (unsigned int)sTmp;
    } else if(4 == Len) {
        iTmp = (*p << 24) | (*(p+1) << 16) | (*(p+2) << 8) | *(p+3);
        return iTmp;
    }

    return FALSE;
}

char    dtuFactoryConfig(char *p, short CfgLen)
{    
    char CfgCmd;
    char WriteLen;
    char WriteErr = TRUE;
    short Crc;
    short RespLen = 0;
    unsigned short CfgAddr;
    unsigned short sTmp;
    unsigned int iTmp;
    char cTmp;
    char bExitCfg = FALSE;
    
    if(dtuCfgDataCheck(p, CfgLen)) {
        p += 2;
        CfgLen -= 5;
        Crc = (*(p+CfgLen-2) << 8) | *(p+CfgLen-1);
        if(Crc == dtuCfgDataCrc(p, CfgLen - 2)) {
            CfgCmd = *p++;            
            
            switch(CfgCmd) {
                case CFG_CMD_ENTER:
                    GbDtuEnterCfg = TRUE;
                    memset(&dtuTmpBuf[100], 0, 5);
                    RespLen = dtuConfigResp(CfgCmd, CFG_ADDR_NONE, &dtuTmpBuf[100], 5, dtuTmpBuf);                    
                    break;
                case CFG_CMD_EXIT:                    
                    bExitCfg = TRUE;                                //  退出配置
                    memset(&dtuTmpBuf[100], 0, 1);
                    RespLen = dtuConfigResp(CfgCmd, CFG_ADDR_NONE, &dtuTmpBuf[100], 1, dtuTmpBuf);    
                    break;
                default:
                    if(!GbDtuEnterCfg) {
                        break;
                    }
                    CfgAddr = (*p << 8) | *(p+1);
                    p += 2;                    
                
                    switch(CfgCmd) {
                        case CFG_CMD_READ:
                            switch(CfgAddr) {
                                /*
                                 *    联网参数相关查询
                                 */
                                case CFG_ADDR_USR:
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, GpSysPara->Net.USR, strlen(GpSysPara->Net.USR), dtuTmpBuf);    
                                    break;
                                case CFG_ADDR_PWD:
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, GpSysPara->Net.PWD, strlen(GpSysPara->Net.PWD), dtuTmpBuf);
                                    break;
                                case CFG_ADDR_APN:
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, GpSysPara->Net.APN, strlen(GpSysPara->Net.APN), dtuTmpBuf);
                                    break;
                                case CFG_ADDR_DOMAIN:
                                case CFG_ADDR_IP:
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, GpSysPara->Net.Domain, strlen(GpSysPara->Net.Domain), dtuTmpBuf);
                                    break;    
                                case CFG_ADDR_PORT:
                                    sTmp = BigEndConvert((char *)&GpSysPara->Net.Port, sizeof(GpSysPara->Net.Port));
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, (char *)&sTmp, sizeof(sTmp), dtuTmpBuf);
                                    break;    
                                case CFG_ADDR_CNT_TYPE:
                                    cTmp = CONT_TYPE_DOMAIN;
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, (char *)&cTmp, 1, dtuTmpBuf);
                                    break;        
                                case CFG_ADDR_PROTOCOL:
                                    cTmp = PROTOCOL_TCP;
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, (char *)&cTmp, 1, dtuTmpBuf);
                                    break;    
                                case CFG_ADDR_ID:
                                    //RespLen = dtuConfigResp(CfgCmd, CfgAddr, GpSysPara->Dev.ID, sizeof(GpSysPara->Dev.ID), dtuTmpBuf);
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, GpSysPara->Dev.ID, strlen(GpSysPara->Dev.ID), dtuTmpBuf);
                                    break;    
                                case CFG_ADDR_SIM:
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, "13800138000", 11, dtuTmpBuf);
                                    break;    
                                case CFG_ADDR_HEART:    
                                    iTmp = GpSysPara->Net.Interval;
                                    iTmp = BigEndConvert((char *)&iTmp, sizeof(iTmp));                                    
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, (char *)&iTmp, sizeof(iTmp), dtuTmpBuf);
                                    break;
                                case CFG_ADDR_TRANS_TYPE:
                                    sTmp = 0x0100;
                                    sTmp = BigEndConvert((char *)&sTmp, sizeof(sTmp));
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, (char *)&sTmp, sizeof(sTmp), dtuTmpBuf);
                                    break;    
                                case CFG_ADDR_REG_TYPE:
                                    cTmp = REG_FORM_HEX;
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, (char *)&cTmp, 1, dtuTmpBuf);
                                    break;    
                                case CFG_ADDR_REG_DATA:
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, "", 1, dtuTmpBuf);
                                    break;    
                                case CFG_ADDR_HEAT_DATA:
                                    RespLen = dtuConfigResp(CfgCmd, CfgAddr, "", 1, dtuTmpBuf);
                                    break;  
								case CFG_ADDR_BINDSTATUS:
									sTmp = GpSysPara->Dev.BindSatus;
									sTmp = BigEndConvert((char *)&sTmp, sizeof(sTmp));
									RespLen = dtuConfigResp(CfgCmd, CfgAddr, (char *)&sTmp, sizeof(sTmp), dtuTmpBuf);
									break;
                                default:
                                    break;
                            }
                            break;
                        case CFG_CMD_WRITE:
                            WriteLen = *p++;
                            switch(CfgAddr) {
                                /*
                                 *    联网参数相关设置
                                 */
                                case CFG_ADDR_USR:
                                    if(WriteLen < sizeof(GpSysPara->Net.USR)) {
                                        memset(GpSysPara->Net.USR, 0, sizeof(GpSysPara->Net.USR));
                                        memcpy(GpSysPara->Net.USR, p, WriteLen);
                                        WriteErr = FALSE;
                                    }
                                    break;
                                case CFG_ADDR_PWD:
                                    if(WriteLen < sizeof(GpSysPara->Net.PWD)) {
                                        memset(GpSysPara->Net.PWD, 0, sizeof(GpSysPara->Net.PWD));
                                        memcpy(GpSysPara->Net.PWD, p, WriteLen);
                                        WriteErr = FALSE;    
                                    }
                                    break;
                                case CFG_ADDR_APN:
                                    if(WriteLen < sizeof(GpSysPara->Net.APN)) {
                                        memset(GpSysPara->Net.APN, 0, sizeof(GpSysPara->Net.APN));
                                        memcpy(GpSysPara->Net.APN, p, WriteLen);
                                        WriteErr = FALSE;    
                                    }
                                    break;
                                case CFG_ADDR_DOMAIN:
                                    if(WriteLen < sizeof(GpSysPara->Net.Domain)) {
                                        memset(GpSysPara->Net.Domain, 0, sizeof(GpSysPara->Net.Domain));
                                        memcpy(GpSysPara->Net.Domain, p, WriteLen);
                                        WriteErr = FALSE;    
                                    }
                                    break;
                                case CFG_ADDR_IP:
                                    WriteErr = FALSE;    
                                    break;
                                case CFG_ADDR_PORT:
                                    if(WriteLen == sizeof(GpSysPara->Net.Port)) {
                                        GpSysPara->Net.Port = (*p << 8) | (*(p+1)) ;
                                        WriteErr = FALSE;    
                                    }
                                    break;    
                                case CFG_ADDR_CNT_TYPE:
                                    WriteErr = FALSE;    
                                    break;        
                                case CFG_ADDR_PROTOCOL:
                                    WriteErr = FALSE;    
                                    break;    
                                case CFG_ADDR_ID:
                                    if(WriteLen < DEV_ID_SIZE) {
                                        memset(GpSysPara->Dev.ID, 0, DEV_ID_SIZE);
                                        memcpy(&GpSysPara->Dev.ID[0], ID_HEADER, ID_HEADER_LEN);
                                        memcpy(&GpSysPara->Dev.ID[ID_HEADER_LEN], p, WriteLen);
                                        WriteErr = FALSE;    
                                    }
                                    break;    
                                case CFG_ADDR_SIM:
                                    WriteErr = FALSE;    
                                    break;    
                                case CFG_ADDR_HEART:
                                    if(WriteLen == 4) {                                        
                                        GpSysPara->Net.Interval = (*p << 24) | (*(p+1) << 16) | (*(p+2) << 8) | (*(p+3)) ;
                                        WriteErr = FALSE;    
                                    }
                                    break;
                                case CFG_ADDR_TRANS_TYPE:
                                    WriteErr = FALSE;    
                                    break;    
                                case CFG_ADDR_REG_TYPE:
                                    WriteErr = FALSE;    
                                    break;    
                                case CFG_ADDR_REG_DATA:
                                    WriteErr = FALSE;    
                                    break;    
                                case CFG_ADDR_HEAT_DATA:
                                    ParaFat.Bits.SysPara = TRUE;
                                    WriteErr = FALSE;    
                                    break;   
								case CFG_ADDR_BINDSTATUS:
									GpSysPara->Dev.BindSatus = *p<<8 | (*(p+1));
									ParaFat.Bits.SysPara = TRUE;
									 WriteErr = FALSE;  
									 break;
                                default:
                                    RespLen = 0;
                                    break;
                            }
                            
                            RespLen = dtuConfigResp(CfgCmd, CfgAddr, &WriteErr, 1, dtuTmpBuf);                            
                            break;
                        default:
                            break;
                    }                
                    break;
            }
        }            
    }
    
    if(RespLen) {
        RS485CfgResp(dtuTmpBuf, RespLen);
    }

    if(bExitCfg) {
        GbDtuEnterCfg = FALSE;
    }

    return bExitCfg;
}



