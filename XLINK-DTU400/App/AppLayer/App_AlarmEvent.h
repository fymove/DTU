#ifndef _ALARM_EVENT_H_
#define _ALARM_EVENT_H_

#ifndef _InAlmEvt
#define AlmEvtExt   extern
#else
#define AlmEvtExt
#endif


#include "struct.h"
#define  ALARM_FILTER_TIME   	10*60    // 10min
#define  PREALARM_FILTER_TIME 	10*60 
#define  Start_FILTER_TIME	    10
#define  STOP_FILTER_TIME		1*60 

AlmEvtExt 	 u16 AlmFilterTimer[24]; 
AlmEvtExt 	 u16 PreAlmFilterTimer[7]; 
AlmEvtExt    u16 StartFilterTimer;
AlmEvtExt    u16 StopFilterTimer;




AlmEvtExt void    AlarmEventInit(void);
AlmEvtExt void    AlarmEventDeal(void);
AlmEvtExt void    AlarmFilterTimer(unsigned short Nms);
AlmEvtExt void   Alarm_Filter_Deal(void );
AlmEvtExt void Start_Stop_Filter(void);

#endif
