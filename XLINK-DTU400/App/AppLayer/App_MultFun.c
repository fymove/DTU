#define _InMult
#include "app_multfun.h"
#include <includes.h>


#define SYSTEM_MONEY_CHECK_INTERVAL 24
#define SYSTEM_PARA_UPLOAD_INTERVAL 24

#define MONEY_CHECK_INTERVAL_NS     (SYSTEM_MONEY_CHECK_INTERVAL * 3600-600)    //  24hour - 10min
#define PARA_UPLOAD_INTERVAL_NS     (SYSTEM_PARA_UPLOAD_INTERVAL * 3600)        //  24hour
#define DTU_COMM_ERROR_SAVE_NS     60// 3600                                        //  1hour



void    RegTimerInit(void)
{
    memset((char *)&BeforeReg, 0, sizeof(BeforeReg));
    BeforeReg.Cnt.Flag = TRUE;
}

void    RegTimerStop(void)
{
    BeforeReg.Cnt.Flag = FALSE;
}

void    RegTimerErrCode(void)
{    
    BeforeReg.Info.CSQ1 = BeforeReg.Info.CSQ2;
    BeforeReg.Info.CSQ2 = BeforeReg.Info.CSQ3;
    BeforeReg.Info.CSQ3 = GprsCtrlInfo.CSQInf.Value;
    
    BeforeReg.Info.ErrCode1 = BeforeReg.Info.ErrCode2;
    BeforeReg.Info.ErrCode2 = BeforeReg.Info.ErrCode3;
    BeforeReg.Info.ErrCode3 = GprsCtrlInfo.ErrCode;
}

void    RegTimerRun(void)
{
//    if(BeforeReg.Cnt.Flag) {
        if(++BeforeReg.Cnt.Sec >= 60) {
            BeforeReg.Cnt.Sec = 0;
            if(++BeforeReg.Cnt.Min >= 60) {
                BeforeReg.Cnt.Min = 0;
                if(++BeforeReg.Cnt.Hour >= 128) {
                    BeforeReg.Cnt.Hour = 128;
                }
            }
        }
//    }
}


void    rst_data_process(void)
{
    u16 ResetVal;
    RESET_TYPE_ENUM ResetType;

    ResetVal = (uint16_t)((RCC->CSR)>>16);
    RCC_ClearFlag();                                                //  清除复位标志

    if(ResetVal & 0x0800) {                                         //  上电复位          
        ResetType = RESET_TYPE_POWERON; 
        AlmStat.DevAlarm.Bits.DevPowerOn =TRUE;
    } else if(ResetVal & 0x2000) {                                  //  独立看门狗复位
        ResetType = RESET_TYPE_WDOG;
    } else if(ResetVal & 0x1000) {
        ResetType = RESET_TYPE_SOFT;    
    } else if(ResetVal & 0x0400) {                                  //  NRST引脚复位
        ResetType = RESET_TYPE_PIN;    
    } else {
        ResetType = RESET_TYPE_OTHER;                               //  其他复位
    }
        
    AlmStat.ResetType = ResetType;
    AlmStat.Flag.Bits.Reset = TRUE;
    DebugMsg(DEBUG_NONE, "[Reset] Type %d\r\n", ResetType);
}



static u32  CommTime = 0;
static u32  CommErrCnt, ParaErrCnt;

void    MultFunInit(void)
{
    rst_data_process();    
    RegTimerInit();
	Led_Indicate_Init();
	
    ParaUpload.Flag = 0;
    ParaUpload.Bits.Timer = 0;                //  参数立即上传
    MoneyCheckTimer = MONEY_CHECK_INTERVAL_NS - 3600;               //  上电1h后查询余额

    AlmDealDelay.Val = 0;
	InitParaUp.val = 0;
	GbeInitParaSend = 0;
    AlmDealDelay.Bits.Flag = TRUE;
    CfgDelay.Val = 0;
    CfgDelay.Bits.Flag = TRUE;  

	ParaUpdate.val = 0;  			// 参数变化状态字初始化

	GpSysStat->Share.MachineStat = STATUS_UNKNOW;  
	GpSysStat->Share.RunState = STATUS_UNKNOW;
	StartFilterTimer = 0;
	StopFilterTimer = 0;

	memset((char *)AlmFilterTimer, 0 ,sizeof(AlmFilterTimer));
	memset((char *)PreAlmFilterTimer, 0, sizeof(PreAlmFilterTimer));
	
    CommErrCnt = GpOthInfo->Error.RS485ErrCnt;
    ParaErrCnt = GpOthInfo->Error.ParaWrErrCnt;

   	if (GpSysPara->Dev.Bits.PS == PS_HC)
   	{
   		GpSysStat->VFD.MainVfd_Model = 2;
   		
		GpSysStat->VFD.FanVfd_Model = 1;
   	}
    
  // AlmStat.Alarm.Bits.RS485CommErr = TRUE;            //避免终端上电前，通信不正常闪烁
}

void    Task_MultFun_1s(void)
{
    if(RmtBootTimer.Bits.Flag) {
        if(++RmtBootTimer.Bits.Timer >= 10) {
            RmtBootTimer.Val = 0;
        }
    }

    if(RmtStopTimer.Bits.Flag) {
        if(++RmtStopTimer.Bits.Timer >= 10) {
            RmtStopTimer.Val = 0;
        }
    }

    if(++ParaUpload.Bits.Timer >= PARA_UPLOAD_INTERVAL_NS) {
        ParaUpload.Flag = 0;
        ParaUpload.Bits.Send  = TRUE;
    }

    if(++CommTime >= DTU_COMM_ERROR_SAVE_NS) {
        CommTime = 0;
        if((CommErrCnt != GpOthInfo->Error.RS485ErrCnt) || 
           (ParaErrCnt != GpOthInfo->Error.ParaWrErrCnt)) {
            CommErrCnt = GpOthInfo->Error.RS485ErrCnt;
            ParaErrCnt = GpOthInfo->Error.ParaWrErrCnt;
            ParaFat.Bits.OthInfo = TRUE;
			ParaUpdate.val |= 1<<1;
			GpSysStat->Share.UpdataParaFlag |= 0x0008;	   
        }
    }

    /*
     *  报警处理20s延时
     */
    if(AlmDealDelay.Bits.Flag) {
        AlmDealDelay.Bits.Timer++;
        if(AlmDealDelay.Bits.Timer >= 20) {             //  20s
            AlmDealDelay.Val = 0;
        }
    }

    /*
     *  终端配置10s延时
     */
    if(CfgDelay.Bits.Flag) {
        if(++CfgDelay.Bits.Timer >= 10) {               //  10s
            CfgDelay.Val = 0;
            if(!(AppDebug.Bits.Enable || GbDtuEnterCfg)) {          
                Task_VfdInit();                         //  非测试模式,初始化控制器通信接口
            }
        }
    }

//    SysTimeSoftRun();                                 //  不需要走时

    RegTimerRun();
	
	Alarm_Filter_Deal();
	Start_Stop_Filter();

    
}

