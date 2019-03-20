#ifndef    _APP_RTC_H_
#define    _APP_RTC_H_

#ifndef    _InPCF8563
#define RtcExt  extern
#else
#define    RtcExt  
#endif

#include "app_cfg.h"
#include "struct.h"

//#if USE_RTC_EN
#pragma pack(1)
typedef struct {
    signed char Year;
    signed char Month;
    signed char Day;
    signed char Hour;
    signed char Min;
    signed char Sec;
//    signed char Week;                                               //  0 ~ 6,0为星期天
}SYS_TIME_STRUCT;
#pragma pack()

RtcExt SYS_TIME_STRUCT SysTime;

RtcExt TIME_FLAG_UNION TimeFlag;

//RtcExt void InitRtc(void);
//RtcExt void GetRtcValue(SYS_TIME_STRUCT *pSysTime);
//RtcExt char SetRTCTime(SYS_TIME_STRUCT *pTime);
//#endif

typedef struct 
{
    u32  LastTime;    //最后更新的时间
}TIME_SYSTICK;



RtcExt char    ServerTimeSet(char *pBuf, SYS_TIME_STRUCT *pSysTime, u8 UpTime);

u8 LeapYear(u16 tmpYear);
RtcExt void RTC_GmtToBjTime(SYS_TIME_STRUCT * pGpsTime);

RtcExt void GprsReadNetTime(char* pBuf, SYS_TIME_STRUCT *pSysTime);
RtcExt void SysTime_Updata(void);
RtcExt u32 SysTime_Get(void);
u32 SysTime_Delay(TIME_SYSTICK * SysTime);
void SysTime_Fresh(TIME_SYSTICK * SysTime);
u16 YearDay(s16 yy,s8 mm,s8 dd);
RtcExt u32 ConverseTimeNum(SYS_TIME_STRUCT *tt);
RtcExt void GetRtctime(SYS_TIME_STRUCT *tt);
#endif

