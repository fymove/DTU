#ifndef _APP_PLT_H_
#define _APP_PLT_H_

#ifndef _InPlt
#define PltExt  extern
#else
#define PltExt
#endif

#define   MONITOR_METER_ON 1


#include "typedef.h"
#include "app_vfd.h"

typedef enum {
    PLT_PRESSURE = 0,                                               //0  ����ѹ��
    PLT_TEMPERATURE,                                                //1  �����¶�
    PLT_PWR_VOLT,                                                   //2  ��Դ��ѹ    
    PLT_STATUS_1,                                                   //3  ״̬1    
    PLT_CURRENT_A,                                                  //4  A�����
    PLT_CURRENT_B,                                                  //5  B�����
    PLT_CURRENT_C,                                                  //6  C�����
    PLT_FAN_CURRENTA,                                               //7  �������A
    PLT_FAN_CURRENTB,                                               //8  �������B
    PLT_FAN_CURRENTC,                                               //9  �������C
    
    PLT_MAIN_OUT_FREQ,                                              //10  �������Ƶ��
    PLT_MAIN_OUT_SPEED,                                             //11  ����ת��
    PLT_MAIN_OUT_CURR,                                              //12  �����������
    PLT_MAIN_OUT_VOLT,                                              //13  ���������ѹ
    PLT_MAIN_OUT_POWER,                                             //14  �����������
    
    PLT_FAN_OUT_FREQ,                                               //15  ������Ƶ��
    PLT_FAN_OUT_SPEED,                                              //16  ���ת��
    PLT_FAN_OUT_CURR,                                               //17  ����������
    PLT_FAN_OUT_VOLT,                                               //18  ��������ѹ
    PLT_FAN_OUT_POWER,                                              //19  ����������

    PLT_MAIN_POWER_CONSUME,                                         //20    �����õ� 
    PLT_MAIN_POWER_CONSUME_LOW,                                     //21    �����õ��λ 
    PLT_FAN_POWER_CONSUME,                                             //22    �����õ� 
    PLT_FAN_POWER_CONSUME_LOW,                                         //23    �����õ��λ          
    PLT_PFREQ_MAIN_POWER_CONSUME,                                     //24    �������õ� 
    PLT_PFREQ_MAIN_POWER_CONSUME_LOW,                                 //25    �������õ��λ  
    PLT_PFREQ_FAN_POWER_CONSUME,                                     //26    �������õ�
    PLT_PFREQ_FAN_POWER_CONSUME_LOW,                                 //27    �������õ��λ 
    
    PLT_FRONT_BEAR_TEMP,                                             //28    ǰ����
    PLT_REAR_BEAR_TEMP,                                             //29    ������ 
    
    PLT_RUN_TIME,                                                   //30  ����ʱ��
    PLT_RUN_TIME_MINUTE,											//31  ��ʷ����ʱ����� 
    PLT_LOAD_TIME,                                                  //32  ��ʷ����ʱ��
    PLT_LOAD_TIME_MINUTE,											//33  ��ʷ����ʱ�����
    PLT_OILFILT_TIME,                                               //34  ������ʹ��ʱ��
    PLT_OILSEPA_TIME,                                               //35  �ͷ���ʹ��ʱ��
    PLT_GASFILT_TIME,                                               //36  ������ʹ��ʱ��
    PLT_LUBE_TIME,                                                  //37  ����ʹ��ʱ��
    PLT_GREASE_TIME,                                                //38  ��֬ʹ��ʱ��
    
    PLT_MAX_USE_TIME,                                               //39���ʹ��ʱ��
    PLT_OILFILT_MAX_HOUR,                                           //40 ���������ʹ��
    PLT_OILSEPA_MAX_HOUR,                                           //41  �ͷ������ʹ��  
    PLT_GASFILT_MAX_HOUR,                                           //42  ���������ʹ��
    PLT_LUBE_MAX_HOUR,                                              //43  �������ʹ��
    PLT_GREAS_MAX_HOUR,                                             //44  ��֬���ʹ��
    PLT_UNLOAD_PRESS,                                               //45  ж��ѹ��
    PLT_LOAD_PRESS,                                                 //46  ����ѹ��
    PLT_MAIN_CFREQ_PRESS,                                             //47    ����ѹ�� 
    PLT_STOP_PRESS,                                                 //48  ����ͣ��ѹ��
    PLT_UNLOAD_MAX_PRESS,                                           //49  ж��ѹ������
    PLT_FAN_STOP_TEMP,                                              //50  ֹͣ�¶� 
    PLT_FAN_START_TEMP,                                             //51  �����¶�
    PLT_FAN_CFREQ_TEMP,                                             //52    ����¶�
    PLT_PRALARM_TEMP,                                               //53  Ԥ���¶�
    PLT_ALARM_TEMP,                                                 //54  ͣ���¶�
    PLT_START_DELAY,                                                //55  ������ʱ
    PLT_LOAD_DELAY,                                                 //56  ������ʱ



    PLT_UNLOAD_DELAY,                                               //57  ������ʱ
    PLT_STOP_DELAY,                                                 //58  ͣ����ʱ
   
    PLT_MAIN_RATE_CURR,                                             //59  ���������   
    PLT_CURR_UNBALANCE,                                             //60  ������ƽ���    
    PLT_MAIN_DELAY,                                                 //61  ����������ʱ
    PLT_XINJIAO_DELAY,                                              //62  �ǽ���ʱ
    PLT_FAN_RATE_CURR,                                              //63  ��������
    PLT_FAN_DELAY,                                                  //64  ���������ʱ
    PLT_USR_PASSWORD,                                               //65  �û�����
    PLT_FAC_PASSWORD,                                               //66  ��������    
   
    PLT_STATUS_2,                                                   //67״̬2     �޶�ӦKEY
    PLT_PRE_ALARM,                                                    //68Ԥ��        �޶�ӦKEY
    PLT_RUN_STATA,                                                    //69����״̬    �޶�ӦKEY
    PLT_FAULT,                                                        //70����        �޶�ӦKEY

    PLT_MAIN_ALARM_VALUE,                                            //71  ������Ƶ����ֵ
    PLT_MAIN_RUN_STATE,                                                //72  ������Ƶ����״̬
    PLT_MAIN_TOPLIMIT_FREQ,                                            //73  ������Ƶ����Ƶ��
    PLT_MAIN_LOWLIMIT_FREQ,                                            //74  ������Ƶ����Ƶ��
    PLT_MAIN_ACC_TIME,                                                //75 ������Ƶ ����ʱ��
    PLT_MAIN_DEC_TIME,                                                //76  ������Ƶ ����ʱ��
    PLT_MAIN_MODEL,                                                    //77  ������Ƶ�ͺ�

    PLT_FAN_ALARM_VALUE,                                            //78 �����Ƶ����ֵ
    PLT_FAN_RUN_STATE,                                                //79 �����Ƶ����״̬
    PLT_FAN_TOPLIMIT_FREQ,                                            //80 �����Ƶ����Ƶ��
    PLT_FAN_LOWLIMIT_FREQ,                                            //81 �����Ƶ����Ƶ��
    PLT_FAN_ACC_TIME,                                                //82 �����Ƶ ����ʱ��
    PLT_FAN_DEC_TIME,                                                //83 �����Ƶ ����ʱ��
    PLT_FAN_MODEL,                                                    //84 �����Ƶ�ͺ�
    
    //MAM6080������������96��
    PLT_SysPressure,        // ϵͳѹ��
    PLT_PhaseProVolt,        // ���򱣻���ѹ
    PLT_OpenPhaseProVolt,    // ȱ�ౣ����ѹ
    PLT_Volt,                // ��ѹ
    PLT_WarningValue,        // Ԥ��ֵ
    PLT_RunStatus,            // ����״̬
    PLT_Timing,                // ��ʱ
    PLT_Fault,                // ����
    PLT_FaultValue,            // ����ֵ
    PLT_OilPressDif,        // �ͷ�ѹ��
    PLT_MainStatus,            // ����״̬��
    PLT_MainFault,            // ����������
    PLT_FanStatus,            // ���״̬��
    PLT_FanFault,            // ���������
    PLT_MainPfreqPowerThis,    // ��Ƶ���������õ�
    PLT_FanPfreqPowerThis,    // ��Ƶ��������õ�
    PLT_MainPfreqUI,        // ��Ƶ����UI
    PLT_FanPfreqUI,            // ��Ƶ���UI
    
    
    PLT_TempUnit,                // �¶ȵ�λ
    PLT_PressureUnit,            // ѹ����λ
    PLT_WarningStop,            // Ԥ������ͣ��
    PLT_FrontBearingWarnTemp,    // ǰ���Ԥ���¶�
    PLT_FrontBearingAlarmTemp,    // ǰ��б����¶�
    PLT_OilPressDifWarn,        // �ͷ�Ԥ��ѹ��
    PLT_OilPressDifAlarm,        // �ͷֱ���ѹ��
    PLT_DrainOpenDelay,            // ��ˮ����ʱ
    PLT_DrainCloseDelay,        // ��ˮ����ʱ
    PLT_SoftStartDelay,            // ������ʱ
    PLT_AssistStartTime,        // ��������ʱ��
    PLT_AssistLoadDelay,        // ����������ʱ
    PLT_AssistUnloadDelay,        // ����ж����ʱ
    PLT_AssistStartTemp,        // �������¶�
    PLT_LoadMode,                // ���ط�ʽ
    PLT_StartStopMode,            // ��ͣ��ʽ
    PLT_CorrespondMode,            // ͨ�ŷ�ʽ
    PLT_LanguageSelection,        // ����ѡ��
    PLT_RunMode,                // ���з�ʽ
    PLT_SysStopPressure,        // ϵͳͣ��ѹ��
    PLT_HistoryFaultReset,        // ��ʷ���ϸ�λ
    PLT_FactoryCode1,            // ��������1
    PLT_FactoryCode2,            // ��������2
    PLT_FactoryDate,            // ��������
    
    
    PLT_MainIntegInitValue,        // �������ֳ�ֵ
    PLT_MainIntegRange,            // �������ַ�Χ
    PLT_MainRatioGain,            // ������������
    PLT_MainIntegGain,            // ������������
    PLT_MainDiffGain,            // ����΢������
    PLT_MainFreqToplimit,        // ����Ƶ������
    PLT_MainFreqLowlimit,        // ����Ƶ������
    PLT_MainIdlingFreq,            // ��������Ƶ��
    PLT_MainVfdNum,                // ������Ƶ��վ��
    PLT_MainPIDPeriod,            // ����PID����
    PLT_MainVfdModel,            // ������Ƶ���ͺ�
    PLT_FanIntegInitValue,        // ������ֳ�ֵ
    PLT_FanIntegRange,            // ������ַ�Χ
    PLT_FanRatioGain,            // �����������
    PLT_FanIntegGain,            // �����������
    PLT_FanDiffGain,            // ���΢������
    PLT_FanFreqToplimit,        // ���Ƶ������
    PLT_FanFreqLowlimit,        // ���Ƶ������
    PLT_FanIdlingFreq,            // �������Ƶ��
    PLT_FanVfdNum,                // �����Ƶ��վ��
    PLT_FanPIDPeriod,            // ���PID����
    PLT_FanVfdModel,            // �����Ƶ���ͺ�
    PLT_VoltOvertop,            // ��ѹ����
    PLT_VoltOverlow,            // ��ѹ����
    PLT_CorrespondOverTime,        // ͨ�ų�ʱ


    PLT_ReFreqPressure,            // ��Ƶѹ��
    PLT_MainRiseRate,            // ������������
    PLT_MainDownRate,            // �����½�����
    PLT_MainPower,                // ��������
    PLT_MainRotationRate,        // ����ת��
    PLT_FanRiseRate,            // �����������
    PLT_FanDownRate,            // ����½�����
    PLT_FanPower,                // �������
    PLT_FanRotationRate,        // ���ת��
    PLT_FanFreqStart,            // ��Ƶ�����
    PLT_FanFreqStop,            // ��Ƶ���ͣ
    PLT_MainStopMode,            // ����ͣ����ʽ
    PLT_TimeStartStopFunc,        // ��ʱ��ͣ����
    PLT_TimePressureFunc,        // ��ʱѹ������
    PLT_LowTempProtect,            // ���±���
    PLT_MainVfdStartMode,        // ����Ƶ��������ʽ
    PLT_FanVfdStartMode,        // �����Ƶ��������ʽ
    PLT_CorrespondStartVfdNum,    // ͨ������Ƶ������
    PLT_CorrespondStopVfdNum,    // ͨ��ͣ��Ƶ������
    PLT_MainPfreqPowerFactor,    // ��Ƶ��������ϵ��
    PLT_MainfreqPowerFactor,    // ��Ƶ��������ϵ��
    PLT_FanPfreqPowerFactor,    // ��Ƶ�������ϵ��
    PLT_FanfreqPowerFactor,        // ��Ƶ�������ϵ��
    PLT_ProMainVfdDelay,        // Ԥ��������Ƶ����ʱ
    PLT_PowerDownRestart,        // ������������
    PLT_FreqSelect,                // Ƶ��ѡ��
    PLT_PipePressure,            // ��·ѹ��
    PLT_RearBearingWarnTemp,    // �����Ԥ���¶�
    PLT_RearBearingAlarmTemp,    // �����ͣ���¶�
    
    
    PLT_ALLOW_WRITE,            //д��ʶ  �޶�ӦKEY
    
}VFD_PLT_ENYM;


typedef enum {
    PLT_Man_PRESSURE = 0,                                               //  ����ѹ��
    PLT_Man_TEMPERATURE,                                                //  �����¶�
    
    PLT_Man_RUN_TIME,                                                   //  ����ʱ��
    PLT_Man_LOAD_TIME,                                                  //  ����ʱ��
    
    PLT_Man_CURRENT_A,                                                  //  ����A�����
    PLT_Man_CURRENT_B,                                                  //  ����B�����
    PLT_Man_CURRENT_C,                                                  //  ����C�����
        
    PLT_Man_STATUS_1,                                                   //  ״̬1    
    PLT_Man_STATUS_2,                                                   //  ״̬2  �޶�ӦKEY
    
    PLT_Man_OILFILT_TIME,                                               //  ������ʹ��ʱ��
    PLT_Man_OILSEPA_TIME,                                               //  �ͷ���ʹ��ʱ��
    PLT_Man_GASFILT_TIME,                                               //  ������ʹ��ʱ��
    PLT_Man_LUBE_TIME,                                                  //  ����ʹ��ʱ��
    PLT_Man_GREASE_TIME,                                                //  ��֬ʹ��ʱ��
    PLT_Man_BELT_TIME,													//  Ƥ��ʹ��ʱ��
  
    PLT_Man_FAN_CURRENTA,                                            //  �������A
    PLT_Man_FAN_CURRENTB,                                            //  �������B
    PLT_Man_FAN_CURRENTC,                                            //  �������C
    PLT_Man_PHASE_PROVOLT,

   	PLT_Man_VF_FREQUENCY,              // ��Ƶ���Ƶ��
   	PLT_Man_VF_VOLTAGE,				   // ��Ƶ�����ѹ						
   	PLT_Man_VF_CURRENT,				   // ��Ƶ�������
   	PLT_Man_VF_POWER,				   // ��Ƶ�������	
	PLT_Man_VF_ROTATIONL_SPEED,		   // ��Ƶ���ת��
   	PLT_Man_FALT,					   // ���ϴ���
   	PLT_Man_WARNING,				   // Ԥ������
   	PLT_Man_OILFILT_MAXTIME,
   	PLT_Man_OILSEPA_MAXTIME,
   	PLT_Man_GASFILT_MAXTIME,
   	PLT_Man_LUBE_MAXTIME,
   	PLT_Man_GREASE_MAXTIME,
   	PLT_Man_LOADPRESS,				//����ѹ��
   	PLT_Man_UNLOADPRESS,  //ж��ѹ��
   	PLT_Man_CQUNECEPRESS,   //������ƵĿ��ѹ��
   	PLT_Man_START_TEMP,	//�����¶�
   	PLT_Man_STOP_TEMP,  //ͣ���¶�
   	
    PLT_Man_ALLOW_WRITE                                             //д��ʶ  �޶�ӦKEY
    
}VFD_PLT_MAM860_ENYM;


typedef  enum{
	H2U_PRESSURE = 0,                                               //0  ����ѹ��
    H2U_TEMPERATURE,                                                //1  �����¶�
    H2U_PWR_VOLT,                                                   //2  ��Դ��ѹ    
    H2U_RUNSTATE,                                                   //3 ����״̬   
	H2U_P2PRESSURE,

	H2U_P3PRESSURE,
	H2U_TEMPERATURE1,
    H2U_FAN_CURRENTA,                                               //7  �������A
    H2U_FAN_CURRENTB,                                               //8  �������B
    H2U_FAN_CURRENTC,                                               //9  �������C

    H2U_MAIN_OUT_FREQ,                                              //10  �������Ƶ��
    H2U_MAIN_OUT_CURR,                                              //12  �����������
    H2U_MAIN_OUT_VOLT,                                              //13  ���������ѹ
    H2U_MAIN_OUT_POWER,                                             //14  �����������
    H2U_FAN_OUT_FREQ,                                               //15  ������Ƶ��

    H2U_FAN_OUT_CURR,                                               //17  ����������
    H2U_FAN_OUT_VOLT,                                               //18  ��������ѹ
    H2U_FAN_OUT_POWER,                                              //19  ����������
    H2U_RUN_TIME,                                                   //30  ����ʱ��
    H2U_LOAD_TIME,                                                  //32  ��ʷ����ʱ��

	H2U_CURRENT_RUNTIME,
	H2U_CURRENT_RUNMINUTE,
	H2U_WATERFILT_TIME,
    H2U_GASFILT_TIME,                                               //36  ������ʹ��ʱ��
    H2U_MAX_USE_TIME,                                               //39���ʹ��ʱ��

    H2U_WATERFILT_MAX_HOUR,                                           //40 ���������ʹ��
    H2U_GASFILT_MAX_HOUR,                                           //42  ���������ʹ��
    H2U_UNLOAD_PRESS,                                               //45  ж��ѹ��
    H2U_LOAD_PRESS,                                                 //46  ����ѹ��
    H2U_MAIN_CFREQ_PRESS,                                             //47    ����ѹ�� 

    H2U_STOP_PRESS,                                                 //48  ����ͣ��ѹ��
    H2U_UNLOAD_MAX_PRESS,                                           //49  ж��ѹ������
    H2U_FAN_STOP_TEMP,                                              //50  ֹͣ�¶� 
    H2U_FAN_START_TEMP,                                             //51  �����¶�
    H2U_FAN_CFREQ_TEMP,                                             //52    ����¶�

    H2U_PRALARM_TEMP,                                               //53  Ԥ���¶�
    H2U_ALARM_TEMP,                                                 //54  ͣ���¶�
	H2U_RUNMODE,													//���з�ʽ
	H2U_TOTALPOWER_L,
	H2U_TOTALPOWER_H,
	H2U_LOWWATERPERTECT,

	H2U_AUTOCHANGEWATER,
	H2U_AUTOCHANGECYCLE,
	H2U_MAXTIMEFUNC,
	H2U_VALVE_STATE,
	H2U_MAIN_IGBT_TMP,
	H2U_MAINVFD_ALARMDATA,
	H2U_FANVFD_ALARMDATA,
	H2U_FAULTSTATUS1,
	H2U_FAULTSTATUS2,
	H2U_FAULTSTATUS3,
	H2U_FAULTSTATUS4,
	H2U_ALLOW_WRITE
}VFD_H2U_ENUM;

#if MONITOR_METER_ON

typedef enum {

    XY_VOLTAGE_A,                                                   //  A���ѹ
    XY_VOLTAGE_B,                                                   //  B���ѹ
    XY_VOLTAGE_C,                                                   //  C���ѹ
	XY_VOLTAGE_AB,                                                   //  AB��ѹ
    XY_VOLTAGE_BC,                                                   //  BC��ѹ
    XY_VOLTAGE_CA,                                                   //  CA��ѹ
	XY_CURRENT_A,                                                  //  A�����
    XY_CURRENT_B,                                                  //  B�����
    XY_CURRENT_C,                                                  //  C�����
    
    xy_ACTIVE_POWER_TOTAL,                                            //���й�����
    xy_REACTIVE_POWER_TOTAL,                                        //���޹�����
    XY_APPARENT_POWER_TOTAL,                                        //�����ڹ���
    XY_POWER_FACTOR_TOTAL,                                            //�ܹ�������
    XY_FREQUENCY,                                                    //Ƶ��
    XY_POSITIVE_ACTIVE_POWER,                                          //���ù�����  ����
//    XY_POSITIVE_ACTIVE_POWER_LOW,                                      //���ù�����  ��λ
//    XY_POSITIVE_ACTIVE_POWER_DEC,                                      //���ù�����  С��λ
//	XY_LINE_NET,													// ���߷�ʽ
	XY_CT,															//  �������			
//    �����Ʋ���    
    FLOW_TRANSIENT_FLOW,                                            // ˲ʱ����  
    FLOW_FREQUENCY,                                                    // Ƶ��
    FLOW_PRESSURE,                                                    // ѹ��
    FLOW_TEMP,                                                        // �¶�
    FLOW_DENSITY,                                                    // �ܶ� 
    FLOW_TOTAL_FLOW,                                                // �ۻ�����    
    FLOW_NUMBER,                                                    // ������վ��
    
}VFD_XY_ENYM;

#endif


#define Int  0
#define Str  1
#define Flo  2 
#define Hex  3 
#define Bit  4 

#define Dec0  0
#define Dec1  1
#define Dec2  2 
#define Dec3  3 
#define Dec4  4 

#define W_F 0
#define W_T 1

#define S_F 0
#define S_T 1

#define PLT_DATA_LIST_MAX    182  //86+96    
#define PLT_Mam860_DATA_LIST_MAX  37  //27+5+5
#define    XY_DATA_LIST_MAX    23
#define H2U_PLC_LIST_MAX     53

#define SERVER_DATA_MAX_BUF  20

typedef struct {
    
    u16 Adrr[SERVER_DATA_MAX_BUF];
    u16 Data[SERVER_DATA_MAX_BUF];
    
    u8 Start;
    u8 End;
    u8 Len;
    u8 Flag;
}SERVER_WRITER_DATA_STRUCT;



PltExt bool RemoteWritePara;
PltExt bool EnterPltParaWrite;
PltExt bool    PltAlowWrite;

PltExt void    GetPltAllPara( char *pBuf, u16 *pLen); 
PltExt char    Plt1SysVarRead(u16 Addr, char *pBuf, u16 *pLen, ADDR_TYPE_ENUM *pType);
PltExt char    Plt3SysVarRead(u16 Addr, char *pBuf, u16 *pLen, ADDR_TYPE_ENUM *pType);
PltExt void    PltDevDataPrase(u16 Index, u16 Data, u8 Type);
PltExt void    PltDevMan860DataPrase(u16 Index, u16 Data, u8 Type);
PltExt u16     GetPltReadAddr(void);
PltExt void    PltUsrHourAlarmCheck(void);
PltExt void    PltParaWrite(MODBUS_HOST_STRUCT *pMdBus, u16 Nms);
PltExt void   XYDevDataDeal(u8 *Data, u8 Len, u8 Type);
PltExt char    XYMeterVarRead(u16 Addr, char *pBuf, u16 *pLen, ADDR_TYPE_ENUM *pType);
PltExt bool PltSysVarWriter(u16 Addr, char *Pbuf);
PltExt bool Server_Writer_Data_Buf(u16 addr, u16 data, u8 Len);
PltExt bool Server_Writer_Data_SendBuf(u16 *addr, u16 *data);

void Plt_PreAlarm_Deal(u16 Code);
void Plt_RunStata_Deal(u16 Code);
void Plt_Fault_Deal(u16 Code);
void  GetPlt1SpecPara(u8 pstype, char *pBuf);
void  GetPlt2SpecPara(char *pBuf);
void  GetPlt3SpecPara(char *pBuf);
void  GetMeterReadAddr(u16 *DatAddr, u8 *DatLen);
void  GetMeter2ReadAddr(u16 *DatAddr, u8 *DatLen);
void  PltMam6080OtherDataPrase(u16 Index, u16 Data);
void  PltDevH2UParse(u16 Index, u16 Data);
char    PltMam6080OtherVarRead(u16 Addr, char *pBuf, u16 *pLen, ADDR_TYPE_ENUM *pType);
#endif


