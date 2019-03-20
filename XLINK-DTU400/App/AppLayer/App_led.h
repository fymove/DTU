#ifndef _LED_H_
#define  _LED_H_

#ifndef  __INLED
#define  LED_EXTERN extern 
#else
#define  LED_EXTERN 
#endif

#include <stdint.h>
typedef  struct {
	uint32_t 	Flag: 1;			//电平翻转标志  1：高电平  0：低电平
	uint32_t     Ontime: 12; 			//(0~4s)  单位： ms
	uint32_t     Offtime: 12;            //(0~4s)  单位：ms
	uint32_t	    res: 7;			  //预留		
}LED_INDICATE;

typedef enum{
	INDICATE_VFD ,
	//INDICATE_METER,
	//INDICATE_FLOW,
	INDICATE_NUM
}ENUM_INDICATE;

LED_EXTERN	LED_INDICATE Led_indicate[INDICATE_NUM];


#define LED_INDICATE_VFD_ONTIME    100   //500MS
#define LED_INDICATE_VFD_OFFTIME   900

#define LED_INDICATE_METER_ONTIME  100
#define LED_INDICATE_METER_OFFTIME 900

#define LED_INDICATE_FLOW_ONTIME   250
#define LED_INDICATE_FLOW_OFFTIME  250

#define Display_CYCLE   2000  //每中状态指示2s

LED_EXTERN void  Led_Indicate_Init(void);

void    SysComLed(short Nms);
void    SysRunLed(short Nms);
void    LedOffSet(void);
void    LedOnSet(short OnNms, short OffNms, char Times);
void    Rs485ComLed(short Nms);

#endif
