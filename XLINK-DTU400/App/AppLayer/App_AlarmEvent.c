#define _InAlmEvt
#include "app_alarmevent.h"
#include "includes.h"


//#define MIN_LACKWATER_ALM_EN            FALSE
//#define MIN_LACKWATER_ALM_MINUTE        3

//#define MIN_LACKPHASE_ALM_EN            FALSE
//#define MIN_LACKPHASE_ALM_MINUTE        3

//#define MIN_OVERMAXCURR_ALM_EN          FALSE
//#define MIN_OVERMAXCURR_ALM_MINUTE      3

//#define MIN_CURRIMBALANCE_ALM_EN        FALSE
//#define MIN_CURRIMBALANCE_ALM_MINUTE    3

//#define MIN_FANOVERMAXCURR_ALM_EN       FALSE
//#define MIN_FANOVERMAXCURR_ALM_MINUTE   3

//#define MIN_FANCURRIMBALANCE_ALM_EN     FALSE
//#define MIN_FANCURRIMBALANCE_ALM_MINUTE 3

//#define MIN_OVERMAXVOLT_ALM_EN          FALSE
//#define MIN_OVERMAXVOLT_ALM_MINUTE      3   

//#define MIN_OVERMINVOLT_ALM_EN          FALSE
//#define MIN_OVERMINVOLT_ALM_MINUTE      3

//#define MIN_OVERMAXPRES1_ALM_EN         FALSE
//#define MIN_OVERMAXPRES1_ALM_MINUTE     3

//#define MIN_OVERMAXTEMP1_ALM_EN         FALSE
//#define MIN_OVERMAXTEMP1_ALM_MINUTE     3

//#define MIN_OVERMINTEMP_ALM_EN          FALSE
//#define MIN_OVERMINTEMP_ALM_MINUTE      3

//#define MAIN_CURRENT_FAULT_ALM_EN       FALSE
//#define MAIN_CURRENT_FAULT_ALM_MINUTE   3

#define FAN_CURRENT_FAULT_ALM_EN        TRUE
#define FAN_CURRENT_FAULT_ALM_MINUTE    3


typedef union {
    u32 Flag;
    struct {
        u32 Flg: 1;                                                 //  过滤标识
        u32 Nms: 10;                                                //  毫秒计时
        u32 Sec: 6;                                                 //  秒计时
        u32 Min: 7;                                                 //  分计时,最大127分钟
        u32 MaxMin: 7;
        u32 Res:  1;
    }Bits;
}ALM_TIMER_UNION;

typedef struct {

#if FAN_CURRENT_FAULT_ALM_EN
    ALM_TIMER_UNION FanCurFault;
#endif

}ALM_INV_STRUCT;
static ALM_INV_STRUCT  AlmFltTimer;


static char    AlarmFilterTimeOver(ALM_TIMER_UNION *pAlmTimer, u16 Nms)
{
    if(pAlmTimer->Bits.Flg) 
    {
        if(pAlmTimer->Bits.Nms + Nms >= 1000) 
        {
            pAlmTimer->Bits.Nms = 0;
            if(++pAlmTimer->Bits.Sec >= 60) 
            {
                pAlmTimer->Bits.Sec = 0;
                if(++pAlmTimer->Bits.Min >= pAlmTimer->Bits.MaxMin) 
                {
                    pAlmTimer->Bits.Min = 0;
                    pAlmTimer->Bits.Flg = FALSE;
                    return TRUE;
                }
            }  
        } 
        else 
        {
            pAlmTimer->Bits.Nms += Nms;
        }
    }

    return FALSE;
}

void    AlarmFilterTimer(u16 Nms)
{

#if FAN_CURRENT_FAULT_ALM_EN
    if(AlarmFilterTimeOver(&AlmFltTimer.FanCurFault, Nms)) 
    {
        AlmMask.Alarm.Bits.FanCurrFault = TRUE;
    }
#endif
}

static u32 LastAlmFlg;                                          //  上一次报警状态
static u32 LastPreAlmFlg;                                       //  上一次预警状态
static u32 LastDevAlmFlg;                                       //  上一次预警状态


void    AlarmEventInit(void)
{
    /*
     *  需要上传的报警类型
     */
    memset((char *)&AlmMask, 0xff, sizeof(AlmMask));  
    AlmMask.AlmSnd.Flag = 0;
    AlmMask.AlmSnd.Bits.Reserved = TRUE;//  其它报警，除现有报警之外的未知具体报警，地址8 bit0
    AlmMask.AlmSnd.Bits.LackWater = TRUE;//  缺水报警
    AlmMask.AlmSnd.Bits.LackPhase = TRUE;    //缺相
    AlmMask.AlmSnd.Bits.PluseError = TRUE;    //相序错误
    
    AlmMask.AlmSnd.Bits.MainVfdAlarm = TRUE;   //  主机变频器报警
    AlmMask.AlmSnd.Bits.MainCurrFault = TRUE;  //  主机电流故障报警
    AlmMask.AlmSnd.Bits.CurrImbalance = TRUE;  //  主机电流不平衡
    
    AlmMask.AlmSnd.Bits.FanVfdAlarm = TRUE;    //  风机变频器报警  
    AlmMask.AlmSnd.Bits.FanCurrFault = TRUE;    //  风机电流故障报警
    AlmMask.AlmSnd.Bits.FanCurrImbalance = TRUE;    //  风机电流不平衡
    
    AlmMask.AlmSnd.Bits.OverMaxPres1 = TRUE;    //  压力超限报警
    AlmMask.AlmSnd.Bits.PresSen1Fault = TRUE;   //  压力传感器损坏报警
    AlmMask.AlmSnd.Bits.OverMaxTemp1 = TRUE;    //  温度超限报警
       
    AlmMask.AlmSnd.Bits.TempSen1Fault = TRUE;   //  温度传感器损坏报警
    AlmMask.AlmSnd.Bits.OverMinTemp = TRUE;     //  温度超低报警
    
    
    AlmMask.AlmSnd.Bits.TempImbalance = TRUE;   //  温度失调报警
    AlmMask.AlmSnd.Bits.OverMaxUsrHour = TRUE;  //  超过使用时限报警
    AlmMask.AlmSnd.Bits.SupplyVoltageOverMax = TRUE; // 电压超高报警
    AlmMask.AlmSnd.Bits.SupplyVoltageOverMin = TRUE; // 电压超低报警
    
    
//    AlmMask.AlmSnd.Bits.RS485CommErr = TRUE;    //  RS485与控制器的通信异常
//    AlmMask.AlmSnd.Bits.RS485MeterErr = TRUE;    //  RS485与电能表的通信异常
//    AlmMask.AlmSnd.Bits.RS485FlowErr = TRUE;    //  RS485与流量计的通信异常
// 
    memset((char *)&AlmStat,  0, sizeof(AlmStat));
    if(GpSysPara->Dev.Bits.AlmSaveFlg) {
        AlmStat.Alarm.Flag    =  GpAlmInfo->Alarm.Flag;
        AlmStat.PreAlarm.Flag =  GpAlmInfo->PreAlarm.Flag;
        
        AlmMask.Alarm.Flag    = ~GpAlmInfo->Alarm.Flag;
        AlmMask.PreAlarm.Flag = ~GpAlmInfo->PreAlarm.Flag;
    }
    LastAlmFlg    = AlmStat.Alarm.Flag;
    LastPreAlmFlg = AlmStat.PreAlarm.Flag;
    
    memset((char *)&SysEvent, 0, sizeof(SysEvent));

    /*
     *  相同报警间隔时间
     */
    memset((char *)&AlmFltTimer, 0, sizeof(AlmFltTimer));

#if FAN_CURRENT_FAULT_ALM_EN
    AlmFltTimer.FanCurFault.Bits.MaxMin  = FAN_CURRENT_FAULT_ALM_MINUTE;
#endif

//    AlmStat.Alarm.Bits.MainVfdAlarm = TRUE;
//    AlmStat.Alarm.Bits.FanVfdAlarm = TRUE;

//    AlmStat.DevAlarm.Bits.DevPowerOn = TRUE;
//    AlmStat.DevAlarm.Bits.DevStartUp = TRUE;
//    AlmStat.DevAlarm.Bits.DevShutDown = TRUE;
//    
//    AlmStat.DevAlarm.Bits.DevStop = TRUE;
//    AlmStat.DevAlarm.Bits.LoadingRun = TRUE;
//    AlmStat.DevAlarm.Bits.IdlerRun = TRUE;
//    AlmStat.DevAlarm.Bits.DevDormancy = TRUE;
//    AlmStat.DevAlarm.Bits.FanRun = TRUE;
//    AlmStat.DevAlarm.Bits.FanStop = TRUE;
}


/*
void    AlarmEventDeal(void)
{
    u32 ChgFlg;
    ALARM_FLAG_UNION NewAlm, DisAlm;
//    static RESET_TYPE_ENUM  LastResetType;                          //  上一次复位状态
//    static BOOT_TYPE_ENUM   LastBootType;                           //  上一次开机状态
//    static STOP_TYPE_ENUM   LastStopType;                           //  上一次停机状态
    
    if(LastAlmFlg != AlmStat.Alarm.Flag) {
        ChgFlg = AlmStat.Alarm.Flag ^ LastAlmFlg;                   //  变化位
        NewAlm.Flag = ChgFlg & AlmMask.Alarm.Flag;                  //  新产生的位
        DisAlm.Flag = ChgFlg ^ NewAlm.Flag;                         //  消失的位
                       
        if(NewAlm.Flag) 
        {                                           //  产生的新报警源 
            SysEvent.Alarm.Flag |= NewAlm.Flag & AlmMask.AlmSnd.Flag;//  上传报警事件
            if(SysEvent.Alarm.Flag) 
            {
                SysEvent.Flag.Bits.Alarm = TRUE;                    //  置报警标识
//                if(SysEvent.Alarm.Bits.MainVfdAlarm) {                      
//                    SysEvent.MainVfdAlmVal = AlmStat.MainVfdAlmVal; //  主机变频报警报警值
//                }
//                if(SysEvent.Alarm.Bits.FanVfdAlarm) {                   
//                    SysEvent.FanVfdAlmVal = AlmStat.FanVfdAlmVal;   //  风机变频报警值
//                }
            }            
            
            AlmMask.Alarm.Flag ^= NewAlm.Flag;                      //  屏蔽下次相同的报警

        } 
        
        if(DisAlm.Flag) 
        {                                           //  有报警源消失 
            SysEvent.Alarm.Flag &= ~DisAlm.Flag;                    //  事件未上传,报警源消失,清除报警事件 
            if((!SysEvent.Alarm.Flag) && (!SysEvent.PreAlarm.Flag)) 
            {
                SysEvent.Flag.Bits.Alarm = FALSE;
            }
            
            AlmMask.Alarm.Flag |= DisAlm.Flag;                      //  下次可产生报警事件
        }
    
        LastAlmFlg = AlmStat.Alarm.Flag;
        ParaFat.Bits.AlmInfo = TRUE;
    }

    if(LastPreAlmFlg != AlmStat.PreAlarm.Flag) 
    {
        ChgFlg = AlmStat.PreAlarm.Flag ^ LastPreAlmFlg;                
        NewAlm.Flag = ChgFlg & AlmMask.PreAlarm.Flag;                   
        DisAlm.Flag = ChgFlg ^ NewAlm.Flag;                                  
                       
        if(NewAlm.Flag)   
        {                                               
            SysEvent.PreAlarm.Flag |= NewAlm.Flag;  
            SysEvent.Flag.Bits.Alarm = TRUE;                        //  置报警标识           
            AlmMask.PreAlarm.Flag ^= NewAlm.Flag;                               
        } 
        
        if(DisAlm.Flag) 
        {                                                         
            AlmMask.PreAlarm.Flag |= DisAlm.Flag;

            SysEvent.PreAlarm.Flag &= ~DisAlm.Flag;                 //  事件未上传,预报警源消失,清除预警事件 
            if((!SysEvent.Alarm.Flag) && (!SysEvent.PreAlarm.Flag)) 
            {
                SysEvent.Flag.Bits.Alarm = FALSE;
            }
        }
    
        LastPreAlmFlg = AlmStat.PreAlarm.Flag;
        ParaFat.Bits.AlmInfo = TRUE;
    }  


    if(LastDevAlmFlg != AlmStat.DevAlarm.Flag) 
    {
        ChgFlg = AlmStat.DevAlarm.Flag ^ LastDevAlmFlg;                
        NewAlm.Flag = ChgFlg & AlmMask.DevAlarm.Flag;                   
        DisAlm.Flag = ChgFlg ^ NewAlm.Flag;                                  
                       
        if(NewAlm.Flag) 
        {                                               
            SysEvent.DevAlarm.Flag |= NewAlm.Flag;  
            SysEvent.Flag.Bits.Alarm = TRUE;                        //  置报警标识           
            AlmMask.DevAlarm.Flag ^= NewAlm.Flag;                               
        } 
        
        if(DisAlm.Flag) 
        {                                                         
            AlmMask.DevAlarm.Flag |= DisAlm.Flag;

            SysEvent.DevAlarm.Flag &= ~DisAlm.Flag;                 //  事件未上传,预报警源消失,清除预警事件 
            if((!SysEvent.Alarm.Flag) && (!SysEvent.PreAlarm.Flag)&& (!SysEvent.DevAlarm.Flag)) 
            {
                SysEvent.Flag.Bits.Alarm = FALSE;
            }
        }
    
        LastDevAlmFlg = AlmStat.DevAlarm.Flag;
        ParaFat.Bits.AlmInfo = TRUE;
    }  

    


    if(AlmStat.Flag.Bits.Boot) 
    {
        AlmStat.Flag.Bits.Boot = FALSE;
        if(AlmStat.BootType) 
        {            
            SysEvent.BootType = AlmStat.BootType;
            SysEvent.Flag.Bits.Boot = TRUE;
        }        
    }
    
    if(AlmStat.Flag.Bits.Stop) 
    {
        AlmStat.Flag.Bits.Stop = FALSE;
        if(AlmStat.StopType) 
        {
            SysEvent.Flag.Bits.Stop = TRUE;
            SysEvent.StopType = AlmStat.StopType;
        }
    }

    if(AlmStat.Flag.Bits.Reset) 
    {
        AlmStat.Flag.Bits.Reset = FALSE;
        if(AlmStat.ResetType) 
        {
            SysEvent.Flag.Bits.Reset = TRUE;
            SysEvent.ResetType = AlmStat.ResetType;
        }
    }
}


*/



void	AlarmEventDeal(void)
{
	u32 ChgFlg;
	u8  i;
	ALARM_FLAG_UNION NewAlm;
	ALARM_FLAG_UNION DisAlm;  
//	static u32 TmpLastAlmStat, TmpAlmstat;
	/* 机器停止1min 中后禁止上报数据 */
	//  if (STOP_STATE == GpSysStat->Share.RunState && ( 0 == StopFilterTimer) )
//	{
//		return ;
//	}  
	if(LastAlmFlg != AlmStat.Alarm.Flag) 
	{
//		TmpLastAlmStat  = LastAlmFlg;
//		TmpAlmstat = AlmStat.Alarm.Flag;
		ChgFlg = AlmStat.Alarm.Flag ^ LastAlmFlg;					//	变化位
		NewAlm.Flag = ChgFlg &  AlmStat.Alarm.Flag;					//	新产生的位
		DisAlm.Flag = ChgFlg ^ AlmStat.Alarm.Flag;					// 新消失的位
					   
		if(NewAlm.Flag) 
		{											//	产生的新报警源 
			SysEvent.Alarm.Flag |= NewAlm.Flag & AlmMask.AlmSnd.Flag;//  上传报警事件
			if(SysEvent.Alarm.Flag) 
			{


				for (i=0; i<32; i++)
				{
					if ((SysEvent.Alarm.Flag & (1<<i)) && AlmFilterTimer[i] == 0)
					SysEvent.Flag.Bits.Alarm = TRUE;					//	置报警标识
				}
				
			}			 
		} 

		if (DisAlm.Flag)
		{
				SysEvent.Alarm.Flag &= ~(DisAlm.Flag);
		}

		LastAlmFlg  = AlmStat.Alarm.Flag;
		ParaFat.Bits.AlmInfo = TRUE;
	}

	if(LastPreAlmFlg != AlmStat.PreAlarm.Flag) 
	  {
		  ChgFlg = AlmStat.PreAlarm.Flag ^ LastPreAlmFlg;				 
		  NewAlm.Flag = ChgFlg & AlmStat.PreAlarm.Flag; 				  
		  DisAlm.Flag = ChgFlg ^ AlmStat.PreAlarm.Flag;					// 新消失的位				   
						 
		  if(NewAlm.Flag)	
		  { 											  
			  SysEvent.PreAlarm.Flag |= NewAlm.Flag ;   
			  	for (i=0; i<2; i++)
				{
					if ((SysEvent.PreAlarm.Flag  & (1<<i)) && PreAlmFilterTimer[i] == 0)
					SysEvent.Flag.Bits.Alarm = TRUE;					//	置报警标识
				}
							  
		  }


		 if (DisAlm.Flag)
	  	{
	  		SysEvent.PreAlarm.Flag &= ~(DisAlm.Flag);
	  	}
		  
		  LastPreAlmFlg = AlmStat.PreAlarm.Flag;
		  ParaFat.Bits.AlmInfo = TRUE;
	  }  

	if(LastDevAlmFlg != AlmStat.DevAlarm.Flag) 
	  {
		  ChgFlg = AlmStat.DevAlarm.Flag ^ LastDevAlmFlg;				 
		  NewAlm.Flag = ChgFlg & AlmStat.DevAlarm.Flag; 				  
								   
						 
		  if(NewAlm.Flag) 
		  { 											  
			  SysEvent.DevAlarm.Flag |= NewAlm.Flag;  
			  SysEvent.Flag.Bits.Alarm = TRUE;						  //  置报警标识									  
		  } 
		  
	  
		  LastDevAlmFlg = AlmStat.DevAlarm.Flag;
		  ParaFat.Bits.AlmInfo = TRUE;
	  }  

	
    if(AlmStat.Flag.Bits.Boot) 
    {
        AlmStat.Flag.Bits.Boot = FALSE;
        if(AlmStat.BootType) 
        {            
            SysEvent.BootType = AlmStat.BootType;
            SysEvent.Flag.Bits.Boot = TRUE;
        }        
    }
    
    if(AlmStat.Flag.Bits.Stop) 
    {
        AlmStat.Flag.Bits.Stop = FALSE;
        if(AlmStat.StopType) 
        {
            SysEvent.Flag.Bits.Stop = TRUE;
            SysEvent.StopType = AlmStat.StopType;
        }
    }

    if(AlmStat.Flag.Bits.Reset) 
    {
        AlmStat.Flag.Bits.Reset = FALSE;
        if(AlmStat.ResetType) 
        {
            SysEvent.Flag.Bits.Reset = TRUE;
            SysEvent.ResetType = AlmStat.ResetType;
        }
    }
}

/* 报警、预警上报 频率控制
* 对应的定时器时间不为0，则不上报
*/
void Alarm_Filter_Deal(void )
{
	u16 i;
	//Alarm
	for (i=0; i<sizeof(AlmFilterTimer)/sizeof(AlmFilterTimer[0]); i++)
	{
		if (AlmFilterTimer[i] != 0)
		{
			AlmFilterTimer[i]--;
		}
	}

	// PreAlarm
	for (i=0; i<sizeof(PreAlmFilterTimer)/sizeof(PreAlmFilterTimer[0]); i++)
	{

		if (PreAlmFilterTimer[i] != 0)
		{
			PreAlmFilterTimer[i]--;
		}
	}
}


void Start_Stop_Filter(void)
{
	if (StartFilterTimer != 0)
	{
		StartFilterTimer--;
	}

	if (StopFilterTimer !=0)
	{
	
		StopFilterTimer--;
	}
}
/**
	@para  pbuf: 要追加报警附加信息的缓冲区
	@para  alm_bit: 产生报警的位
*/
//void PackAlarmInfo(char *pbuf,  int alm_bit)
//{
//	if (5 == i)
//	{
//		sprintf(&pBuf[strlen(pBuf)], "\"8305\":{\"2300\":\"%d\",\"46\":\"%d\",\"42\":\"%d\"},"
//        ,GpSysStat->VFD.MainVfd_Model, GpSysStat->VFD.MainVfd_AlarmValue, GpSysStat->Main.OutCurrent);            
//	}
//}


