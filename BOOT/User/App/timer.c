#include "typedef.h"
#include "stm32f10x.h"
#include "timer.h"

TIMER_FLAG_UNION   TimeFlag;



/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */

void    Milliseconds(void)
{
    static u32 sys_tick = 0;

    sys_tick++;

    if(sys_tick >= 1000) {
        sys_tick = 0;
        TimeFlag.Bits.T1s = TRUE;        
    }    
}

#if 0

// 初始化协议用定时器
void    init_All_timer(void)
{
    sys_tick = 0;
    all_timer.timer_Heartbeat = 0;
}


BOOLEAN IsLeapYear(INT8U ucYear)
{
    INT16U  usYear = ucYear + 2000;                                 //  2000年

    if((0 == (usYear % 400)) ||                                         //  能被400整除，一定是闰年
      ((0 == (usYear % 4)) && (0 != (usYear % 100))))                   //  能被4整除，但不能被100整除，一定是闰年
    {
        return TRUE;
    }

    return FALSE;
}

INT8U MaxDateofMonth(INT8U Month, INT8U Year)
{
    INT8U ucMaxDate = 30;
    
    switch(Month)                                                       //  日更新
    {
        case 1:
        case 3:
        case 5:
        case 7:                                                         //  大月
        case 8:
        case 10:
        case 12:
            ucMaxDate = 31;
            break;

        case 4:
        case 6:
        case 9:
        case 11:                                                        //  小月
            ucMaxDate = 30;
            break;

        case 2:
            if(IsLeapYear(Year))                                         //  闰年
            {
                ucMaxDate = 29;
            }
            else
            {
                ucMaxDate = 28;
            }
            break;

        default:
            break;
    }

    return ucMaxDate;
}


void    Task_SoftRTCTimer(void)
{
    INT8U   ucMaxDate = 0;

    if(++RTCSystemTime.Time.Sec >= 60)                                  //  秒更新
    {
        RTCSystemTime.Time.Sec = 0;
        if(++RTCSystemTime.Time.Min >= 60)                               //  分更新
        {
            RTCSystemTime.Time.Min = 0;
            if(++RTCSystemTime.Time.Hour >= 24)                          //  时更新
            {
                RTCSystemTime.Time.Hour = 0;

                ucMaxDate = MaxDateofMonth(RTCSystemTime.Date.Month, RTCSystemTime.Date.Year);
                if(++RTCSystemTime.Date.Date > ucMaxDate)                //  月更新
                {
                    RTCSystemTime.Date.Date = 1;
                    if(++RTCSystemTime.Date.Month > 12)                  //  年更新
                    {
                        RTCSystemTime.Date.Month = 1;
                        RTCSystemTime.Date.Year++;
                    }
                }
            }
        }
    }
}



void TIMER3_Init(void)
{  
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;  

    TIM_TimeBaseStructure.TIM_Period = 20;  //1ms
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_PrescalerConfig(TIM3, 3599, TIM_PSCReloadMode_Immediate);// 20kHZ

    TIM_ClearFlag(TIM3, TIM_IT_Update);
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    TIM_Cmd(TIM3, DISABLE);
}


void TIM3_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM3, TIM_FLAG_Update) != RESET)
    {       
//        Task_LedScan();
        TIM_ClearFlag(TIM3, TIM_FLAG_Update);
    }
}
#if 0
void    DispSystemCurrTime(void)
{
    sprintf((char *)GucDebugOutBuf, "Curr System time is: %02d/%02d/%04d, %02d:%02d:%02d.%03d\r\n",
            RTCSystemTime.Date.Date, RTCSystemTime.Date.Month, RTCSystemTime.Date.Year + 2000,
            RTCSystemTime.Time.Hour, RTCSystemTime.Time.Min, RTCSystemTime.Time.Sec, GusMilliseconds);
    SendConsoleStr(GucDebugOutBuf);
}

int isLeapYear(int year)
{
	if(((year % 400) == 0) || (((year % 4) == 0) && ((year % 100) != 0)))
	{
		return 1;
	}
	return 0;
}

#if 0
char NotLeapNum[] = {0, 0, 3, 3, 6, 1, 4, 0, 3, 5, 0, 3, 5};
char IsLeapNum[] =  {0, 0, 3, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};

INT8U Calweekday(void)
{
    int ret;
    int year, month, day;

    year = RTCSystemTime.Date.Year + 2000;
    month = RTCSystemTime.Date.Month;
    day = RTCSystemTime.Date.Date;

    ret = year;
    ret += year / 4;
    ret += year / 400;
    ret -= year / 100;
    ret -= isLeapYear(year) + 1;
    if(isLeapYear(year))
    {
        ret += IsLeapNum[month];
    }
    else
    {
        ret += NotLeapNum[month];
    }
    ret += day;
    return(ret % 7);
}
#else
struct YMD
{
	unsigned int Year;
	char Month;
	char Day;

}Date;

char MonthDay[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int HowDay(struct YMD *Dt)
{
	int mm;
	int ret = 0;
    
    
    
    
	for(mm=0;mm<Dt->Month;mm++)
	{
		ret += MonthDay[mm];
	}
	if(Dt->Month>=3)
	{
		ret += isLeapYear(Dt->Year);
	}
	ret += Dt->Day;
	return ret;
}

INT8U Calweekday()
{
	int ret;
    struct YMD Dt;
    
    Dt.Year = RTCSystemTime.Date.Year + 2000;
    Dt.Month = RTCSystemTime.Date.Month;
    Dt.Day = RTCSystemTime.Date.Date;
   
    ret = (Dt.Year - 1);
	ret += (Dt.Year - 1) / 4;
	ret -= (Dt.Year - 1) / 100;
	ret += (Dt.Year - 1) / 400;
	ret += HowDay(&Dt);
	return(ret % 7);
}
#endif

void    TimeAdd(RQ_STRUCT *pCurTime, INT8U AddMin)
{
    INT8U ucMaxDate;
    
    pCurTime->Time.Min += (AddMin % 60);
    if(pCurTime->Time.Min >= 60)
    {
        pCurTime->Time.Min -= 60;
        pCurTime->Time.Hour++;
    }

    pCurTime->Time.Hour += (AddMin / 60);
    if(pCurTime->Time.Hour >= 24)
    {
        pCurTime->Time.Hour -= 24;
        pCurTime->Date.Date++;
        ucMaxDate = MaxDateofMonth(pCurTime->Date.Month, pCurTime->Date.Year);
        if(pCurTime->Date.Date > ucMaxDate)                             //  月更新
        {
            pCurTime->Date.Date = 1;
            if(++pCurTime->Date.Month > 12)                             //  年更新
            {
                pCurTime->Date.Month = 1;
                pCurTime->Date.Year++;
            }
        }
    }    
}
#endif

#endif
