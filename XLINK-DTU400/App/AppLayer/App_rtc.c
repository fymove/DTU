/******************************************************************************************* 
  文件名:      
  作者:               版本:                    日期: 
  描述:    ( 用于详细说明此程序文件完成的主要功能，与其他模块 
                   或函数的接口，输出值、取值范围、含义及参数间的控 
                   制、顺序、独立或依赖等关系 )
                   
  其他:    ( 其它内容的说明 )
  主要函数列表:  (每条记录应包括函数名及功能简要说明 )
    1. .... 

  修改历史:        
    1. 日期: 
       作者: 
       修改记录: 
    2. ... 
*********************************************************************************************/ 
#define    _InPCF8563

#include "app_rtc.h"
#include "typedef.h"
#include "string.h"

#if USE_RTC_EN


#if USE_RTC_PCF8563
#include  <ucos_ii.h>
#include "bsp.h"
#include "comm.h"

static OS_EVENT *I2CMutex;
char    WeekDay;




#define SEC_ADD     0x02                                            //  秒地址
#define MIN_ADD     0x03                                            //  分地址
#define HOUR_ADD    0x04                                            //  时地址
#define DAY_ADD     0x05                                            //  日地址
#define WEEK_ADD    0x06                                            //  周地址
#define MONTH_ADD   0x07                                            //  月地址
#define YEAR_ADD    0x08                                            //  年地址
#define read_ADD    0xA3                                            //  读数据
#define write_ADD   0xA2                                            //  写数据
#define Alarm_Time 10 //±¨?ˉê±??????  μ￥??·??ó￡¨óDD§·??§1~59￡?

void I2C_delay(void)
{    
   INT8U i=100; //这里可以优化速度    ，经测试最低到5还能写入
   while(i) 
   { 
     i--; 
   } 
}


void InitRtc(void)
{
//    INT8U err;

    I2CMutex = OSSemCreate(1);                /* uC/OS-II */
    if(I2CMutex == 0)
    {
        RTCDebugMsg("Create Mutex error\r\n");
    }
}

void I2CMutexPend(void)
{
    INT8U err;

    OSSemPend(I2CMutex, 0, &err);            /* uC/OS-II */    
}

void I2CMutexPost(void)
{
    OSSemPost(I2CMutex);            /* uC/OS-II */    
}



void RTC_I2C_RTC_Configuration(void)
{
#if 0
   I2C_InitTypeDef  I2C_InitStructure;
   GPIO_InitTypeDef  GPIO_InitStructure; 

   RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);

   /* Configure I2C1 pins: PB8->SCL and PB9->SDA */
//   GPIO_PinRemapConfig(GPIO_Remap_I2C1,ENABLE);
   GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
   GPIO_Init(GPIOB, &GPIO_InitStructure);
        
   I2C_DeInit(I2C1);
   I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
   I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
   I2C_InitStructure.I2C_OwnAddress1 = 0x30;
   I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
   I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
   I2C_InitStructure.I2C_ClockSpeed = 100000;
      
   I2C_Init(I2C1, &I2C_InitStructure);
     I2C_Cmd(I2C1, ENABLE);
   I2C_AcknowledgeConfig(I2C1, ENABLE);
   #endif

   
}

BOOLEAN RTC_I2C_Start(void)
{
    RTC_SDA_H;
    RTC_SCL_H;
    I2C_delay();
    if(!RTC_SDA_read)return FALSE;    //SDA线为低电平则总线忙,退出
    RTC_SDA_L;
    I2C_delay();
    if(RTC_SDA_read) return FALSE;    //SDA线为高电平则总线出错,退出
    RTC_SDA_L;
    I2C_delay();
    return TRUE;
}

void RTC_I2C_SendByte(INT8U SendByte) //数据从高位到低位//
{
    INT8U i=8;
    while(i--)
    {
        RTC_SCL_L;
        I2C_delay();

        if(SendByte&0x80)
            RTC_SDA_H;  
        else 
            RTC_SDA_L;   
        
        SendByte<<=1;
        I2C_delay();
        RTC_SCL_H;
        I2C_delay();
    }
    RTC_SCL_L;
}

BOOLEAN RTC_I2C_WaitAck(void)      //返回为:=1有ACK,=0无ACK
{
    RTC_SCL_L;
    I2C_delay();
    RTC_SDA_H;            
    I2C_delay();
    RTC_SCL_H;
    I2C_delay();
    if(RTC_SDA_read)
    {
        RTC_SCL_L;
        return FALSE;
    }
    
    RTC_SCL_L;
    return TRUE;
}

void RTC_I2C_Stop(void)
{
    RTC_SCL_L;
    I2C_delay();
    RTC_SDA_L;
    I2C_delay();
    RTC_SCL_H;
    I2C_delay();
    RTC_SDA_H;
    I2C_delay();
}

INT8U RTC_I2C_ReceiveByte(void)  //数据从高位到低位//
{ 
    INT8U i=8;
    INT8U ReceiveByte=0;

    RTC_SDA_H;                
    while(i--)
    {
        ReceiveByte<<=1;      
        RTC_SCL_L;
        I2C_delay();
        RTC_SCL_H;
        I2C_delay();    
        if(RTC_SDA_read)
        {
            ReceiveByte|=0x01;
        }
    }
    RTC_SCL_L;
    return ReceiveByte;
}



void RTC_I2C_NoAck(void)
{    
    RTC_SCL_L;
    I2C_delay();
    RTC_SDA_H;
    I2C_delay();
    RTC_SCL_H;
    I2C_delay();
    RTC_SCL_L;
    I2C_delay();
}

void RTC_I2C_Ack(void)
{    
    RTC_SCL_L;
    I2C_delay();
    RTC_SDA_L;
    I2C_delay();
    RTC_SCL_H;
    I2C_delay();
    RTC_SCL_L;
    I2C_delay();
}


//读出1串数据         存放读出数据  待读出长度      待读出地址       器件类型(24c16或SD2403)    
BOOLEAN RTC_I2C_ReadByte(INT8U* pBuffer,   INT8U length,     INT16U ReadAddress,  INT8U DeviceAddress,INT16U timeout)
{
    if(!RTC_I2C_Start())return FALSE;
    
    RTC_I2C_SendByte(DeviceAddress&0xFE);//设置器件地址 
    if(!RTC_I2C_WaitAck()){RTC_I2C_Stop(); return FALSE;}
    
    RTC_I2C_SendByte(ReadAddress);//设置低起始地址 
    RTC_I2C_WaitAck();
    
    if(!RTC_I2C_Start())return FALSE;

    RTC_I2C_SendByte(DeviceAddress|0x01);//设置读地址      
    RTC_I2C_WaitAck();

    while(length)
    {
        *pBuffer = RTC_I2C_ReceiveByte();
        
        if(length == 1)
            RTC_I2C_NoAck();
        else
            RTC_I2C_Ack(); 
        
        pBuffer++;
        length--;
    }
    RTC_I2C_Stop();
    return TRUE;
}


char I2C_RTC_ReadBUF(I2C_TypeDef *I2Cx,uint8_t addr,uint8_t *buf,uint16_t num)
{
//    CPU_SR         cpu_sr;
    if(num==0)
        return 1;
#if 0    
//    OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */

    while(I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
        
    I2C_AcknowledgeConfig(I2Cx, ENABLE);
    I2C_GenerateSTART(I2Cx, ENABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2Cx,  write_ADD, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    I2C_SendData(I2Cx, addr);
    while (!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    I2C_GenerateSTART(I2Cx, ENABLE);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

    I2C_Send7bitAddress(I2Cx, read_ADD, I2C_Direction_Receiver);
    while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
//    OS_EXIT_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
    while (num)
    {
        if(num==1)
        {
            I2C_AcknowledgeConfig(I2Cx, DISABLE);
            I2C_GenerateSTOP(I2Cx, ENABLE);
        }
//        OS_ENTER_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
        while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */
        *buf = I2C_ReceiveData(I2Cx);
//        OS_EXIT_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
        buf++;
        /* Decrement the read bytes counter */
        num--;
    }

    I2C_AcknowledgeConfig(I2Cx, ENABLE);

//    OS_EXIT_CRITICAL();                         /* Tell uC/OS-II that we are starting an ISR          */
#endif
//    RTC_I2C_ReadByte(buf,num,addr,read_ADD,3000);

    I2CMutexPend();

    if(!RTC_I2C_Start())
    {
        I2CMutexPost();
        return FALSE;
    }
    
    RTC_I2C_SendByte(read_ADD&0xFE);//设置器件地址 
    if(!RTC_I2C_WaitAck())
    {
        RTC_I2C_Stop(); 
        I2CMutexPost();
        return FALSE;
    }
    
    RTC_I2C_SendByte(addr);//设置低起始地址 
    RTC_I2C_WaitAck();
    
    if(!RTC_I2C_Start())
    {
        I2CMutexPost();
        return FALSE;
    }

    RTC_I2C_SendByte(read_ADD|0x01);//设置读地址      
    RTC_I2C_WaitAck();

    while(num)
    {
        *buf = RTC_I2C_ReceiveByte();
        
        if(num == 1)
            RTC_I2C_NoAck();
        else
            RTC_I2C_Ack(); 
        
        buf++;
        num--;
    }
    RTC_I2C_Stop();
    I2CMutexPost();
    return 0;
}    

char I2C_RTC_WriteBUFF(uint8_t I2C_Addr,uint8_t addr,char*buff ,char bufflen)
{
//    char i;
#if 0    
    while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));
    I2C_AcknowledgeConfig(I2C1, ENABLE);
      I2C_GenerateSTART(I2C1, ENABLE);
        
     while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)); 
    
     I2C_Send7bitAddress(I2C1,  I2C_Addr, I2C_Direction_Transmitter);

        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
        
      I2C_SendData(I2Cx, addr);

    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    for(i=bufflen;i>0;i--)
    {
          I2C_SendData(I2Cx, *buff++); 
          while(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }
      I2C_GenerateSTOP(I2Cx, ENABLE);
#endif

    if(!RTC_I2C_Start())return FALSE;

    RTC_I2C_SendByte(I2C_Addr & 0xFE);//设置器件地址 
    if(!RTC_I2C_WaitAck()){RTC_I2C_Stop(); return FALSE;}

//    RTC_I2C_SendByte((WriteAddress & 0x1F00)>>8);   //设置高起始地址      
//    RTC_I2C_WaitAck();    

    RTC_I2C_SendByte(addr);        
    RTC_I2C_WaitAck();    

    while(bufflen--)
    {
        RTC_I2C_SendByte(* buff);
        RTC_I2C_WaitAck();
        buff++;
    }
    RTC_I2C_Stop();
    return 0;
}


void SetDefaultTime(void)
{
    SYS_TIME_STRUCT time;

    time.Sec   = 0x00;
    time.Min   = 0x00;
    time.Hour  = 0x00;
    time.Day   = 0x30;
    time.Month = 0x08;
    time.Year  = 0x15;

    SetRTCTime(&time);
}

void GetRtcValue(SYS_TIME_STRUCT *pSysTime)
{
     
     uint8_t buf[7],i=0;
    SYS_TIME_STRUCT time;
    BOOLEAN setdefault = 0;
    static INT16U setdeftime = 0;

    if(0 == I2C_RTC_ReadBUF(I2C1,SEC_ADD,buf,7)) {
         i=0;
        buf[0]=buf[0]&0x7F;//sec
        buf[1]=buf[1]&0x7F;//min
        buf[2]=buf[2]&0x3F;//hour
        buf[3]=buf[3]&0x3F;//day
        buf[4]=buf[4]&0x07;//week
        buf[5]=buf[5]&0x1F;//month
        
         time.Sec =buf[i++];
        time.Min =buf[i++];
        time.Hour =buf[i++];
        time.Day =buf[i++];
        WeekDay=buf[i++];
        time.Month =buf[i++];
        time.Year =buf[i++];

        for(i=0;i<6;i++) {
//            if(buf[i]%16 > 9)  //非法时间
//            {
//                setdefault = 1;
//            }

            switch(i)
            {
                case 0:
                case 1:
                    if(buf[i] > 0x60)
                    {
                        setdefault = 1;
                    }
                    break;
                case 2:
                    if(buf[i] > 0x24)
                    {
                        setdefault = 1;
                    }
                    break;
                case 3:
                    if(buf[i] > 0x31)
                    {
                        setdefault = 1;
                    }
                    break;
                case 4:
                    if(buf[i] > 0x6)
                    {
                        setdefault = 1;
                    }
                    break;
                case 5:
                    if(buf[i] > 0x12)
                    {
                        setdefault = 1;
                    }
                    break;
                default:
                    break;
                    

            }
            if(setdefault == 1)
            {
                break;
            }
        }

        if(setdefault==1)
        {
            if(setdeftime++ >3)
            {
                SetDefaultTime();
                setdeftime = 0;
            }
            return;
        }
        else
        {
            setdeftime = 0;
        }

        *pSysTime = time;        
     }
 }

int isLeapYear(int year)
{
    if(((year%400) == 0) || (((year%4) == 0) && ((year%100) != 0)))
    {
        return 1;
    }
    return 0;
}
const   char NotLeapNum[] = {0,0,3,3,6,1,4,0,3,5,0,3,5};
const   char IsLeapNum[] =  {0,0,3,4,0,2,5,0,3,6,1,4,6};

int Calweekday(int year, int month, int day)
{
    int ret;
    
    ret = year;
    ret += year/4;
    ret += year/400;
    ret -= year/100;
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


char    SetRTCTime(SYS_TIME_STRUCT *pTime)
{
    char buff[7],erro=0;
    
    buff[0]=pTime->Sec;
    buff[1]=pTime->Min;
    buff[2]=pTime->Hour;
    buff[3]=pTime->Day;
    buff[4]=Calweekday(2000+BcdToDec8U(pTime->Year), BcdToDec8U(pTime->Month), BcdToDec8U(pTime->Day));
    buff[5]=pTime->Month;
    buff[6]=pTime->Year;
    erro+=I2C_RTC_WriteBUFF(write_ADD, SEC_ADD, buff, 7);
    return(erro);
}
#else 
#if 0
void InitRtc(void)
{
    SysTime.Year  = 15;
    SysTime.Month = 10;
    SysTime.Day   = 10;
    SysTime.Hour  = 0;
    SysTime.Min   = 0;
    SysTime.Sec   = 0;
}


char    SetRTCTime(SYS_TIME_STRUCT *pTime)
{
    SysTime = *pTime;
    
    return TRUE;
}

void    GetRtcValue(SYS_TIME_STRUCT *pSysTime)
{
     *pSysTime = SysTime;
}

char IsLeapYear(INT8U ucYear)
{
    u16 usYear = ucYear + 2000;                                     //  2000年

    if((0 == (usYear % 400)) ||                                     //  能被400整除
      ((0 == (usYear % 4)) && (0 != (usYear % 100)))) {             //  能被4整除，但不能被100整除
        return TRUE;
    }

    return FALSE;
}

INT8U MaxDateofMonth(INT8U Month, INT8U Year)
{
    u8  ucMaxDate = 30;

    switch(Month) {
        case 1:
        case 3:
        case 5:
        case 7:                                                     //  大月
        case 8:
        case 10:
        case 12:
            ucMaxDate = 31;
            break;

        case 4:
        case 6:
        case 9:
        case 11:                                                    //  小月
            ucMaxDate = 30;
            break;

        case 2:
            ucMaxDate = IsLeapYear(Year) ? 29 : 28;                 //  闰年            
            break;

        default:
            break;
    }

    return ucMaxDate;
}

void    SysTimeSoftRun(void)
{
    unsigned char ucMaxDate;

    if(!TimeFlag.Bits.TimeChkOK) {
        return;
    }
    
    if(++SysTime.Sec >= 60) {
        SysTime.Sec = 0;
//        TimeFlag.Bits.MinChange = TRUE;
        if(++SysTime.Min >= 60) {
            SysTime.Min = 0;
            if(++SysTime.Hour >= 24) {
                SysTime.Hour = 0;

                ucMaxDate = MaxDateofMonth(SysTime.Month, SysTime.Year);
                if(++SysTime.Day > ucMaxDate) {
                    SysTime.Day = 1;
                    if(++SysTime.Month > 12) {
                        SysTime.Month = 1;
                        SysTime.Year++;
                    }
                }

//                if(++SysTime.Week > 6) {
//                    SysTime.Week = 0;
//                }
            }
        }
    }
}
#endif
#endif
#endif


static u32 gTime_realSysCount;
static u32 gTime_RtcTime;
const u8 Table[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};



char ServerTimeSet(char *pBuf, SYS_TIME_STRUCT *pSysTime, u8 UpTime)
{
    u32 Temp;
    
    if(19 != strlen(pBuf)) {
        return FALSE;
    }

    if(('-' != pBuf[4])  || ('-' != pBuf[7])  || (' ' != pBuf[10]) ||
       (':' != pBuf[13]) || (':' != pBuf[16]) ) {
        return FALSE;
    }

    pSysTime->Year  = (pBuf[2]  & 0x0f) * 10 + (pBuf[3]  & 0x0f);
    pSysTime->Month = (pBuf[5]  & 0x0f) * 10 + (pBuf[6]  & 0x0f);
    pSysTime->Day   = (pBuf[8]  & 0x0f) * 10 + (pBuf[9]  & 0x0f);
    pSysTime->Hour  = (pBuf[11]  & 0x0f) * 10 + (pBuf[12] & 0x0f);
    pSysTime->Min   = (pBuf[14] & 0x0f) * 10 + (pBuf[15] & 0x0f);
    pSysTime->Sec   = (pBuf[17] & 0x0f) * 10 + (pBuf[18] & 0x0f);
//    pSysTime->Week  = (pBuf[18] & 0x0f);

    TimeFlag.Bits.TimeChkOK = TRUE;
    
    Temp = ConverseTimeNum(pSysTime);    //更新realSysTime 计时
    
    if(UpTime)    //上线第一次注册直接更新
    {
        gTime_RtcTime = Temp;
    }
    else if(gTime_RtcTime > Temp)            //误差超过10秒则更新
    {
        if((gTime_RtcTime - Temp) > 10)
                gTime_RtcTime = Temp;
    }
    else
    {
        if((Temp - gTime_RtcTime ) > 10)
                gTime_RtcTime = Temp;
    }
    
    return TRUE;
}

u8 LeapYear(u16 tmpYear)
{
   u16 year;
   
   year = tmpYear+ 2000;
   if((((year%4) == 0)&&((year%100)!=0))||((year%400)==0)) 
   {
      return (1);
   }
   
   return 0;
}



void RTC_GmtToBjTime(SYS_TIME_STRUCT * pGpsTime)
{
   SYS_TIME_STRUCT tmpTime;
   u8 DAY;
   
   tmpTime.Year = pGpsTime->Year;
   tmpTime.Month = pGpsTime->Month;
   tmpTime.Day = pGpsTime->Day;
   tmpTime.Hour = pGpsTime->Hour;
   
   tmpTime.Hour +=  8; 
   
   if(tmpTime.Hour >= 24)
   {
      tmpTime.Hour = tmpTime.Hour%24;
      tmpTime.Day  = tmpTime.Day+1;
      
      DAY  = Table[tmpTime.Month];
      
      if(LeapYear(tmpTime.Year)&&(tmpTime.Month == 2))
      {
         DAY = 29;
      }
      
      if(tmpTime.Day > DAY )
      {
         tmpTime.Day = 1;
         tmpTime.Month = tmpTime.Month+1;
         if(tmpTime.Month == 13)
         {
            tmpTime.Month = 1;
            tmpTime.Year  = tmpTime.Year + 1;
         }
      } 
   }
   
   
   pGpsTime->Year  = tmpTime.Year;
   pGpsTime->Month = tmpTime.Month; 
   pGpsTime->Day   = tmpTime.Day; 
   pGpsTime->Hour  = tmpTime.Hour;
 
  
}

void GprsReadNetTime(char* pBuf, SYS_TIME_STRUCT *pSysTime)
{
    SYS_TIME_STRUCT NetTime;
    u8 i = 0;
    
    
    while((*pBuf != '"')&&(i <= 10))
    {
            pBuf++;
            i++;
    }

    if(i <= 10)
    {
        NetTime.Year  = (pBuf[1]  & 0x0f) * 10 + (pBuf[2]  & 0x0f);
        NetTime.Month = (pBuf[4]  & 0x0f) * 10 + (pBuf[5]  & 0x0f);
        NetTime.Day   = (pBuf[7]  & 0x0f) * 10 + (pBuf[8]  & 0x0f);
        NetTime.Hour  = (pBuf[10] & 0x0f) * 10 + (pBuf[11] & 0x0f);
        NetTime.Min   = (pBuf[13] & 0x0f) * 10 + (pBuf[14] & 0x0f);
        NetTime.Sec   = (pBuf[16] & 0x0f) * 10 + (pBuf[17] & 0x0f);
        
        RTC_GmtToBjTime(&NetTime);    
        *pSysTime = NetTime;
        gTime_RtcTime = ConverseTimeNum(pSysTime);    //更新realSysTime 计时
    }    
}



void SysTime_Updata(void)
{
    static u16 SysMsCount = 0;
    
    gTime_realSysCount++;
    if(SysMsCount++ >= 1000)
    {
        SysMsCount = 0;
        gTime_RtcTime++;
    }
}

u32 SysTime_Get(void)
{
    return gTime_realSysCount;
}

u32 SysTime_Delay(TIME_SYSTICK * SysTime)
{
    u32 tmpTime1, tmpTime2;

    if(SysTime == NULL) {
        return(0);
    }

    tmpTime1 = SysTime_Get();
    tmpTime2 = SysTime->LastTime;
    
    return((u32)(tmpTime1 - tmpTime2));
}

void SysTime_Fresh(TIME_SYSTICK * SysTime)
{    
    if(SysTime == NULL) {
        
        return;
    }

    SysTime->LastTime = SysTime_Get();
}

#define START_YEAR  2010
#define END_YEAR    2070
#define YEAR_SECOND 0x1E13380
#define DAY_SECOND    0x15180
#define HOUR_SECOND    0xE10
#define MIN_SECOND    60

u16 YearDay(s16 yy,s8 mm,s8 dd)
{
    u8 i;
    u16 TotalDay = 0;
    u8 MonTab[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    for(i = 1; i < mm; i++)
      {
           TotalDay += MonTab[i];
      }
    TotalDay += dd;
    if((LeapYear(yy) == 1)&&(mm > 2))
        TotalDay++;
        return TotalDay;
}


u32 ConverseTimeNum(SYS_TIME_STRUCT *tt)
{
    s16 i;
    s16 year;
    u32 TotalDay;
    u32 TotalSec;

    TotalDay = 0;
    TotalSec = 0;
    year = tt->Year + 2000;

    if((year >= START_YEAR)&&(year <= END_YEAR))    
    {
        for(i = START_YEAR; i < year; i++)    
        {
             TotalDay += (365+LeapYear(i));
        }
        TotalDay += YearDay(year, tt->Month, tt->Day);    
        TotalSec = (TotalDay-1)*DAY_SECOND + tt->Hour*HOUR_SECOND+ tt->Min*60 + tt->Sec;    
    }

    return TotalSec;
    
}

void GetRtctime(SYS_TIME_STRUCT *tt)
{
    s16 i;
    u32 sum ;
    u32 temp;
    u32 counter1 = 0;
    u8 const MonTab[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    u32 counter = gTime_RtcTime;
    
    if((counter > 0xB473500) && (counter < 0xBC191380))  /* 大于2016，小于2070*/
    {
        sum = 0;
        temp = 0;
        for(i=START_YEAR; sum<=counter;i++)   
        {
              sum += (LeapYear(i)*DAY_SECOND + YEAR_SECOND);
              if(sum <= counter)
              {
                  temp= sum;
              }
        }
        tt->Year = (i-1)-2000;   

        /* get the month */
        counter1= counter - temp; 
        sum = 0;
        temp = 0;
        for(i=1; sum<=counter1;i++)
        {
             sum += MonTab[i]*DAY_SECOND;
             if((2 == i)&&(LeapYear(tt->Year)))
             {
                sum +=  DAY_SECOND;  
             }
             if(sum <= counter1)
             {
                temp = sum;
             }
        }
        tt->Month = (i-1);

        /* get the day */
        counter1 = counter1 - temp;
        sum = 0;
        temp = 0;
        for(i=1; sum <= counter1; i++)
            {
                sum += DAY_SECOND;
                if(sum <= counter1)
                {
                    temp = sum;
                }
           }
        tt->Day = (i-1);

        /* get the hour */
        counter1 = counter1 - temp; 
        sum = 0;
        temp = 0;
        for(i=0; sum <= counter1; i++)
        {
            sum += HOUR_SECOND;
            if(sum <= counter1)
            {
               temp = sum;
            }
        }
        tt->Hour = (i-1);

        counter1 = counter1 - temp;
        sum = 0;
        temp = 0;
        for(i=0; sum <= counter1; i++)
        {
            sum += MIN_SECOND;
            if(sum <= counter1)
            {
                temp = sum;
            }
        }
        tt->Min = (i-1);
        
        tt->Sec = counter1 - temp; 
    }    
    
}
