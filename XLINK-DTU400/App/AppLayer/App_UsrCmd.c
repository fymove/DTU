#define _InUsrCmd
#include "app_usrcmd.h"
#include "includes.h"



char UsrCmdSet(char *pObj, char *pPara, char *pPara2)
{
    char ret = FALSE;
    
    if((NULL == pObj) || (NULL == pPara)) {
        return FALSE;
    }

    switch(my_atoi(pObj)) {
        case CMD_SET_ID:
            if(strlen(pPara) < DEV_ID_SIZE-2) {
                memset(GpSysPara->Dev.ID, 0, DEV_ID_SIZE);
                memcpy(GpSysPara->Dev.ID, ID_HEADER, ID_HEADER_LEN);
                strcpy(&GpSysPara->Dev.ID[ID_HEADER_LEN], pPara);
                ParaFat.Bits.SysPara = TRUE;
            }
            break;
        case CMD_SET_SERVER:
            break;
            
        default:
            break;
    }

    return ret;
}


char    UsrCmdQuery(char *pObj, char *pRsp)
{
    char ret = TRUE;
     
    if(NULL == pObj) {
        return FALSE;
    }

    switch(my_atoi(pObj)) {
        case CMD_QUERY_ALL:
            *pRsp = '\0';
        
            if(isGprsCon())
                memcpy(DebugCheck.GprsModel, "OK ", 3);
            else
                memcpy(DebugCheck.GprsModel, "ERR", 3);
            DebugMsg(DEBUG_NONE, "/**********************************************/\r\n");
            DebugMsg(DEBUG_NONE, "Device Model: %s\r\n", PRODUCT_MODLE);   
            DebugMsg(DEBUG_NONE, "Device ID   : %s\r\n", GpSysPara->Dev.ID);        
            DebugMsg(DEBUG_NONE, "App Version : %s.%s\r\n", APP_VERSION, ID_HEADER);                       
            DebugMsg(DEBUG_NONE, "Server Info : %s:%d\r\n", GpSysPara->Net.Domain, GpSysPara->Net.Port);
            DebugMsg(DEBUG_NONE, "Flash Model : %s   %s\r\n", DebugCheck.FlashModel, DebugCheck.FlashName);
            DebugMsg(DEBUG_NONE, "SIM Card    : %s\r\n", DebugCheck.SimCard);
            DebugMsg(DEBUG_NONE, "GPRS Signal : %d\r\n", DebugCheck.GprsSignal);
            DebugMsg(DEBUG_NONE, "GPRS Model  : %s\r\n", DebugCheck.GprsModel);
            DebugMsg(DEBUG_NONE, "Build Time  : %s %s\r\n", __DATE__, __TIME__); 
            DebugMsg(DEBUG_NONE, "/**********************************************/\r\n");
            break;
        case CMD_QUERY_ID:
            break;
           
        default:
            ret = FALSE;
            break;
    }
    
    return ret;
}

char    DebugFtpTest(char *pIp, char *pFile)
{
    FtpInfoInit(pIp, pFile);
    return TRUE;
}

char    UsrCmdCtrl(char *pObj, char *pPara, char *pPara2)
{
    char ret = TRUE;    
    
    if(NULL == pObj) {
        return FALSE;
    }

    switch(my_atoi(pObj)) {
        case CMD_CTRL_RESET:      
            RebootDelay(0);                                         //  重启
            break;
      case CMD_CTRL_UPDATE:
            DebugFtpTest(pPara, pPara2);
            break;            
        default:
            ret = FALSE;
            break;
    }

    return ret;
}


char    UsrCmdTest(char *pObj, char *pPara)
{
    char ret = TRUE;
    char bSet = my_atoi(pPara) ? TRUE : FALSE;
    
    if((NULL == pObj) || (NULL == pPara)) {
        return FALSE;
    }

    switch(my_atoi(pObj)) {
//        case CMD_TEST_RS485:      
//            UartTest.Flag = bSet;
//            break;
//        case CMD_TEST_DO:
//            IOOutputSet(DO_LOAD, bSet);
//            IOOutputSet(DO_MAIN, bSet);
//            IOOutputSet(DO_FAN, bSet);
//            break;
        default:
            ret = FALSE;
            break;
    }

    return ret;
}


char    UsrCmdDebug(char *pObj, char *pPara)
{
    char ret = TRUE;
    char bSet = (0 == my_atoi(pPara)) ? FALSE : TRUE;
    
    if((NULL == pObj) || (NULL == pPara)) {
        return FALSE;
    }

    switch(my_atoi(pObj)) {
        case CMD_DEBUG_EN:
            AppDebug.Bits.Enable = bSet;
            if(!bSet) {
                if(!CfgDelay.Bits.Flag) {
                    Task_VfdInit();                                 //  超过10s,退出是初始化控制器接口
                }
            }
            break;
//        case CMD_DEBUG_STACK:
//            AppDebug.Bits.TaskStack = bSet;
//            break;
        case CMD_DEBUG_AT:
            AppDebug.Bits.ATCmd = bSet;
            break;
        case CMD_DEBUG_GPRS_RX:
            AppDebug.Bits.GprsRcvData = bSet;
            break;
        case CMD_DEBUG_GPRS_TX:
            AppDebug.Bits.GprsSndData = bSet;
            break; 
//        case CMD_DEBUG_SMS_RX:
//            AppDebug.Bits.SMSRcvData = bSet;
//            break;   
//        case CMD_DEBUG_SMS_TX:
//            AppDebug.Bits.SMSSndData = bSet;
//            break; 
//        case CMD_DEBUG_EMAIL:
//            AppDebug.Bits.EmailInf = bSet;
//            break;   
//        case CMD_DEBUG_WDMST:
//            AppDebug.Bits.WindMaster = bSet;
//            break;  
//        case CMD_DEBUG_ADC:
//            AppDebug.Bits.Adc = bSet;
//            break;
//        case CMD_DEBUG_VFD:
//            AppDebug.Bits.Vfd = bSet;
//            break;    
//        case CMD_DEBUG_HMI_MODBUS:
//            AppDebug.Bits.HMIModbus = bSet;
//            break;
        default:
            ret = FALSE;
            break;
    }
    
    return ret;
}   


char    UsrCmdParse(char *pRd, char *pRsp)
{
    short i;
    char ret = FALSE;    
    char *pCmd, *pObj, *pPara, *pPara2;
    char RspTmp[30];
    
    i = 3;
    do {
        if('#' == *(pRd+i)) {   
            *(pRd+i) = 0;
            i = 0;
            break;
        }     
        i++;
    }while('\0' != *(pRd+i));
    if(0 != i) {
        sprintf(pRsp, "Format err\r\n");
        return FALSE;
    }     
    
    pRd = strtok(pRd, ",");                            
    if(0 != stricmp(pRd, "*RK")) {
        return FALSE;
    }
    
    pCmd = strtok(NULL, ",");      
    do {
        pObj = strtok(NULL, ",");   
        if(pObj == NULL) {         
            break;
        }
        
        pPara = strtok(NULL, ",");  
        if(pPara == NULL) {
            break;
        }
        
        pPara2 = strtok(NULL, ",");
        if(pPara2 == NULL) {
            break;
        }    
    } while(0);

    if(0 == stricmp(pCmd, USR_CMD_SET)) {
        ret = UsrCmdSet(pObj, pPara, pPara2);
        if(ret) {
            sprintf(pRsp, "*RK,%s,%s,OK\r\n",   pCmd, pObj);
        } else {
            sprintf(pRsp, "*RK,%s,%s,Err\r\n", pCmd, pObj);
        }       
    } else if(0 == stricmp(pCmd, USR_CMD_QUERY)) {
        ret = UsrCmdQuery(pObj, RspTmp);    
        if(ret) {
            sprintf(pRsp, "*RK,%s,%s,%s,OK\r\n", pCmd, pObj, RspTmp);
        } else {
            sprintf(pRsp, "*RK,%s,%s,Err\r\n", pCmd, pObj);
        }
    } else if(0 == stricmp(pCmd, USR_CMD_CTRL)) {
        ret = UsrCmdCtrl(pObj, pPara, pPara2);
        if(ret) {
            sprintf(pRsp, "*RK,%s,%s,OK\r\n", pCmd, pObj);
        } else {
            sprintf(pRsp, "*RK,%s,%s,Err\r\n", pCmd, pObj);
        }    
    } else if(0 == stricmp(pCmd, USR_CMD_TEST)) {
        ret = UsrCmdTest(pObj, pPara);
        if(ret) {
            sprintf(pRsp, "*RK,%s,%s,OK\r\n", pCmd, pObj);
        } else {
            sprintf(pRsp, "*RK,%s,%s,Err\r\n", pCmd, pObj);
        }
    } else if(0 == stricmp(pCmd, USR_CMD_DEBUG)) {
        ret = UsrCmdDebug(pObj, pPara);
        if(ret) {
            sprintf(pRsp, "*RK,%s,%s,OK\r\n", pCmd, pObj);
        } else {
            sprintf(pRsp, "*RK,%s,%s,Err\r\n", pCmd, pObj);
        }
    } else {
        sprintf(pRsp, "*RK,%s,unkonw\r\n", pCmd);
        ret = FALSE;
    }

    return ret;
}



