#define __INLED
#include "app_led.h"
#include "includes.h"

typedef struct {
    short Flag:     1;
    short Sta:        1;
    short On:          1;
    short Off:         1;    
    short Times:     4;
    short OnDelay:  12; 
    short OffDelay: 12;
}LED_CTRL_INFO;

static LED_CTRL_INFO LedCtrl;


void    LedOnSet(short OnNms, short OffNms, char Times)
{    
    LedCtrl.Flag = TRUE;
    LedCtrl.On = TRUE;
    LedCtrl.Off = FALSE;
    LedCtrl.Times = Times;
    LedCtrl.OnDelay = (OnNms >= 4000) ? 4000 : OnNms;
    LedCtrl.OffDelay = (OffNms >= 4000) ? 4000 : OffNms;
}


void    LedOffSet(void)
{    
    LedCtrl.Flag = FALSE;
    LedCtrl.On = FALSE;
    LedCtrl.Off = TRUE;
    LedCtrl.Times = 0;
}


#if 0
void    SysComLed(short Nms)
{    
    char Deal = FALSE;    
    static short LedDelay = 0;
    static char  RegStat = TRUE;    

    if(LedCtrl.On) {
        LedCtrl.On = FALSE;
        LED_ON();        
        LedCtrl.Sta = TRUE;
        LedDelay = LedCtrl.OnDelay;
    } else if(LedCtrl.Off) {
        LedCtrl.Off = FALSE;
        LED_OFF();        
        LedCtrl.Sta = FALSE;
        LedDelay = LedCtrl.OffDelay;
    }    

    if(LedCtrl.Flag) 
    {        
        if(LedCtrl.Times) 
        {
            if(LedDelay >= Nms) 
            {
                LedDelay -= Nms;
                if(0 == LedDelay) 
                {    
                    Deal = TRUE;                    
                }
            } 
            else if(LedDelay) 
            {
                Deal = TRUE;
            } 

            if(Deal) 
            {
                if(LedCtrl.Sta) 
                {
                    LedCtrl.Off = TRUE;    
                } 
                else 
                {
                    LedCtrl.Times--;
                    if(LedCtrl.Times) 
                    {
                        LedCtrl.On = TRUE;
                    } 
                    else 
                    {
                        LedCtrl.Flag = FALSE;                    
                        if(RegStat) 
                        {
                            LED_OFF();
                        } 
                        else 
                        {
                            LED_ON();
                        }
                    }
                }
            }            
        }
    }    

    if(RegStat != IsReg()) 
    {
        RegStat = IsReg();
        if(RegStat) 
        {
            LED_OFF();
        } 
        else 
        {
            LED_ON();
        }
    }
}
#endif

void    SysComLed(short Nms)
{    
    static short LedDelay = 0;


    if(LedCtrl.On) 
    {
        LedCtrl.On    = FALSE;
        LED_ON();        
        LedDelay = 100;
        LedCtrl.Sta = TRUE;
    } 
    else if(LedCtrl.Off) 
    {    
        LedCtrl.Off = FALSE;
        LED_OFF();                
        LedDelay = 900;
        LedCtrl.Sta = FALSE;
    }    

    if(isGprsCon()) 
    {    
        if(LedDelay <= 0)
        {
            if(LedCtrl.Sta)
            {
                LedCtrl.On    = FALSE;
                LedCtrl.Off = TRUE;
            }
            else
            {
                LedCtrl.On    = TRUE;
                LedCtrl.Off = FALSE;
            }
        }
        else
        {
            LedDelay -= Nms;
        }        
    }
    else
    {
        LedCtrl.On    = TRUE;
    }            
}




DELAY_TIMER Led;
/*
void    SysRunLed(short Nms)
{    
    if(!VfdInitFlag) {
        return;
    }
    
    if(AlmStat.Alarm.Bits.RS485CommErr) {
        Led.Bits.Timer = 0;
        GLED_ON();
    } else {
        Led.Bits.Timer += Nms;
        if(Led.Bits.Flag) {
            GLED_ON();
            if(Led.Bits.Timer >= 50) {
                Led.Bits.Timer = 0;
                Led.Bits.Flag = FALSE;
            }
        } else {
            GLED_OFF();
            if(Led.Bits.Timer >= 900) {
                Led.Bits.Timer = 0;
                Led.Bits.Flag = TRUE;
            }
        }
    }
}
*/

static void Led_Indicate(ENUM_INDICATE      * step, short Nms)
{
	static int count = 0;
	int index = (int)(*step);
	#if 0
	cycle += Nms;

	
	if (cycle >= Display_CYCLE)
		{
			index++;
			cycle = 0;
			count = 0;
			*step = (ENUM_INDICATE)index;
			if (*step == INDICATE_NUM)
				*step = INDICATE_VFD;
			return;
		}
	#endif
	if (!(GpSysStat->Share.DTU_COMM_STATUS & (1<<index))) 
	{
		GLED_ON();
	}
	else
	{	
		count += Nms;
		if (Led_indicate[index].Flag)  
		{
			GLED_ON();
			if (count >= Led_indicate[index].Ontime)
			{
				Led_indicate[index].Flag = 0;
				count = 0;
			}
		}
		else
		{
			GLED_OFF();
			if(count >= Led_indicate[index].Offtime)
			{
				Led_indicate[index].Flag  = 1;
				count = 0;
			}
		}
	}
}
void Rs485ComLed(short Nms)
{

	static ENUM_INDICATE  led_step = INDICATE_VFD;

	if (GpSysStat->Share.DTU_COMM_STATUS ==0)
		{
			GLED_ON();
			return ;
		}
	switch (led_step)
		{
			case INDICATE_VFD:
			{	
				Led_Indicate(&led_step, Nms);
				break;
			}
			/*
			case INDICATE_METER:
			{
				Led_Indicate(&led_step, Nms);
				break;
			}
			case INDICATE_FLOW:
			{
				Led_Indicate(&led_step, Nms);
				break;
			}
			*/
			default:
				break;
			
		}	
}
void  Led_Indicate_Init(void)
{
	Led_indicate[INDICATE_VFD].Flag = 1;
	Led_indicate[INDICATE_VFD].Ontime = LED_INDICATE_VFD_ONTIME;
	Led_indicate[INDICATE_VFD].Offtime = LED_INDICATE_VFD_OFFTIME;
#if 0
	Led_indicate[INDICATE_METER].Flag = 1;
	Led_indicate[INDICATE_METER].Ontime = LED_INDICATE_METER_ONTIME;
	Led_indicate[INDICATE_METER].Offtime = LED_INDICATE_METER_OFFTIME;

	Led_indicate[INDICATE_FLOW].Flag = 1;
	Led_indicate[INDICATE_FLOW].Ontime = LED_INDICATE_FLOW_ONTIME;
	Led_indicate[INDICATE_FLOW].Offtime = LED_INDICATE_FLOW_OFFTIME;
#endif 
	GpSysStat->Share.DTU_COMM_STATUS = 0; 
	
	
}


