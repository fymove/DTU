#ifndef _STRUCT_H_
#define    _STRUCT_H_

#include "typedef.h"
#include <stdint.h>

#ifndef TRUE
#define    TRUE                1
#endif

#ifndef FALSE
#define    FALSE                0
#endif

#include "app_cfg.h"
#include "gprscfg.h"


typedef enum {
    PROTOCOL_UDP = 0,
    PROTOCOL_TCP    
}PROTOCOL_ENUM;    


typedef enum {
    DTU_AT_MODE = 0,                                                //  ATģʽ
    DTU_ONLINE_NORMAL,                                              //  ��Զ����ģʽ
    DTU_ONLINE_WAKEUP,                                              //  ��������ģʽ
    DTU_ONLINE_REQUIRED                                             //  ��������ģʽ
}DTU_MOED;



typedef enum {
    BOOT_TYPE_HMI = 1,                                              //  ����������
    BOOT_TYPE_KEY,                                                  //  ��������
    BOOT_TYPE_SERVER,                                               //  Զ�̿��� 
    BOOT_TYPE_TIMER,                                                //  ��ʱ����
        BOOT_TYPE_LINK,                                                                                                    //  ��������
        BOOT_TYPE_REBOOT,                                               //  ��λ����
        BOOT_TYPE_COM_RECOVER,                                                                                    // ͨ�Żָ�����
}BOOT_TYPE_ENUM;                                                    //  ��������

typedef enum {
    STOP_TYPE_HMI = 1,                                              //  ������ͣ��
    STOP_TYPE_KEY,                                                  //  ����ͣ��
    STOP_TYPE_SERVER,                                               //  Զ��ͣ�� 
    STOP_TYPE_TIMER,                                                //  ��ʱͣ��
        STOP_TYPE_LINK,
        STOP_TYPE_URGENT,                                               //  ��ͣ
    STOP_TYPE_ALARM,                                                //  ����ͣ��
    STOP_TYPE_COM_FAULT                                                                                            //ͨ�Ź���ͣ��
}STOP_TYPE_ENUM;                                                    //  ͣ������



typedef enum {
    RESET_TYPE_POWERON = 1,                                         //  �ϵ縴λ
    RESET_TYPE_WDOG,                                                //  ���Ź���λ
    RESET_TYPE_PIN,                                                 //  �ܽŸ�λ
    RESET_TYPE_SOFT,                                                //  ������λ
    RESET_TYPE_OTHER,                                               //  ����    
}RESET_TYPE_ENUM;                                                   //  ��λ����


typedef struct {
    struct {
        char Idle:  1;
        char SndReg:1;
    }Bits;

    unsigned short NoDataCnt;    
}DTU_STATUS_INFO;


typedef union {
    char Flag;
    struct {
        char N2ms: 1;
        char N20ms: 1;
        char N50ms: 1;
        char N500ms: 1;
        char TimeChkOK: 1;                                          //  Уʱ��ʶ
    }Bits;
}TIME_FLAG_UNION;

typedef union {
    u32 Val;
    struct {
        u32 Flag: 1;
        u32 Timer: 31;
    }Bits;
}DELAY_TIMER;




#pragma pack(1)


typedef union {
    char Flag;
    struct {
        char Bit0: 1; 
        char Bit1: 1;
        char Bit2: 1;
        char Bit3: 1;
        char Bit4: 1;
        char Bit5: 1;
        char Bit6: 1;
        char Bit7: 1;        
    }Bits;
}CHAR_UNION;

/*******************************************************************
                        ϵͳ�����ṹ�嶨��                       
*******************************************************************/
#define CT_GEAR_SMALL       0                                       //  ������С����
#define CT_GEAR_BIG         1                                       //  ������������

#define FREQ_SELECT_50HZ    0                                       //  50Hz
#define FREQ_SELECT_60HZ    1                                       //  60Hz
    
#define DRV_TYPE_AC         0                                       //  ��Ƶ����
#define DRV_TYPE_VFD        1                                       //  ��Ƶ����

#define BIT_PARA_FREQ_SELECT    0
#define BIT_PARA_FAN_DRV_TYPE   1
#define BIT_PARA_FAN_CT_GEAR    6


//typedef union {
//    u32 Flag;
//    struct {        
//        u32 FreqSelect: 1;                                          //  Ƶ��ѡ��        0��50Hz     1��60Hz
//        u32 FanDrvType: 1;                                          //  �������        0����Ƶ     1����Ƶ��
//        u32 FreeSleep:  1;                                          //  �վ�����        0���ر�     1������
//        u32 PhaseSeqChk:1;                                          //  ������        0: �ر�     1: ����
//        u32 PowerRestart: 1;                                        //  �ϵ�����        0���ر�     1������   
//        u32 FanCurrChk: 1;                                          //  ����������    0���ر�     1������
//        u32 FanCTGear:  1;                                          //  �����������λ  0��С����   1��������

//        /**********���²�����δ�滮��ַ************/

//    }Bits;
//}BIT_PARA_STRUCT;
//#define BIT_PARA_SIZE           sizeof(BIT_PARA_STRUCT)
//#define BIT_PARA_START_ADDR     8200
//#define BIT_PARA_END_ADDR       8206

#define TOUCH_VER_SIZE          10
#define DEV_ID_SIZE             10
#define PCB_VER_SIZE            10
#define APP_VER_SIZE            10
#define MAC_SN_SIZE             20
typedef struct {
    char MachineSN[MAC_SN_SIZE];                                    //  �������    
    u16 MacYear;                                                    //  ����������
    u16 MacMonth;                                                   //  ����������
    u16 MacDay;                                                     //  ����������

    char TOUCHVer[TOUCH_VER_SIZE];                                     //�������汾

    char AppVer[APP_VER_SIZE];                                      //  �����汾

    char ID[DEV_ID_SIZE];                                           //  �豸���
    u16 DevYear;                                                    //  �豸������
    u16 DevMonth;                                                   //  �豸������
    u16 DevDay;                                                     //  �豸������
    
    char PCBVer[PCB_VER_SIZE];                                      //  Ӳ���汾
    /**********���²�����δ�滮��ַ************/
    struct {
        u16 PS: 8;
        u16 AlmSaveFlg: 1;                                          //  ����ֵ�洢
    }Bits;
    
    u16 PasswordAdrr[3];                    //������д���������ַ
    u16 PasswordData[3];                    //������д��������ֵ
    
    u16 MeterNum;                            //���MODBUS��ַ
    u16 FlowNum;                            //������MODBUS��ַ
    u16 BindSatus;							// ������������������ư�״̬   bit0 ������ bit1 ��� bit2 ������ 1���� 0��δ��
    u16 reserv;
}DEV_PARA_STRUCT;

                     
#define PS_MAM_KY_G              123     //���幤Ƶ��MAM100/200/260/280A/300�¶�ƫ��20
#define PS_MAM_KY_C              124     //�����Ƶ��MAM100/200/260/280A/300�¶�ƫ��20
#define PS_MAM260                  125     //�¶�ƫ��150 
#define PS_MAM260A              126     //�¶�ƫ��145
#define PS_MAM280                  127     //�¶�ƫ��125  

#define PS_MAM660_670_680          118     //�¶�ƫ��50   δ����

#define PS_MAM860_870_880          111     //�¶�ƫ��20�Ѳ���
#define PS_MAM860C_880C          112     //�¶�ƫ��50  ��Ƶ
#define PS_MAM890                  113     //�¶�ƫ��20  ��Ƶ

#define PS_MAM6080_6090         101        //�¶�ƫ��50 ��׼��  �Ѳ���
#define PS_MAM6090                 102     //������MAM6090ϵ��,�¶Ȳ�ֵ50
#define PS_MAM6080_1            103        //��6080��һЩ���������ڳ���Ĳ����ݵ���
#define PS_MAM6070				104


#define PS_HC                  160   //�㴨������
//#define PS_TYPE_H2U_8A91G          131     //  
//#define PS_TYPE_ATLAS_STD         141     //     ������˹��׼��
#define CLASS_6080      1
#define CLASS_860       2
#define CLASS_860C      3
#define CLASS_HC 		4

#define PS_TYPE_XY_1942E        201     //  ����XY194E���


#define DEV_PARA_SIZE           sizeof(DEV_PARA_STRUCT)
#define DEV_PARA_START_ADDR     2500
#define DEV_PARA_END_ADDR       2530

typedef struct {
    
    u16 MainVfd_AlarmValue;                                         //  ����Ƶ����ֵ
    u16 MainVfd_RunState;                                            //    ������Ƶ����״̬
    
  //  u16 MainVfd_MaxFreq;                                            //  ������Ƶ�����Ƶ��
    u16 MainVfd_TopLimitFreq;                                       //  ������Ƶ������Ƶ��
    u16 MainVfd_LowLimitFreq;                                         //  ������Ƶ������Ƶ��
    u16 MainVfd_AccelerateTime;                                     //  ������Ƶ������ʱ��
    u16 MainVfd_DecelerateTime;                                     //  ������Ƶ������ʱ��
    u16 MainVfd_Model;                                              //  ������Ƶ���ͺ�
    
    u16 FanVfd_AlarmValue;                                          //  ���Ƶ����ֵ
    u16 FanVfd_RunState;                                            //    �����Ƶ����״̬
    
  //  u16 FanVfd_MaxFreq;                                                //  �����Ƶ�����Ƶ��
    u16 FanVfd_TopLimitFreq;                                           //  �����Ƶ������Ƶ��
    u16 FanVfd_LowLimitFreq;                                         //  �����Ƶ������Ƶ��
    u16 FanVfd_AccelerateTime;                                         //  �����Ƶ������ʱ��
    u16 FanVfd_DecelerateTime;                                         //  �����Ƶ������ʱ��
    u16 FanVfd_Model;                                               //  �����Ƶ���ͺ�
    
}VFD_PARA_STRUCT;

#define VFD_ADDR_SIZE           sizeof(VFD_PARA_STRUCT)


#define GPRS_DOMAIN_SIZE        30
#define GPRS_APN_SIZE           30
#define GPRS_USR_SIZE           30
#define GPRS_PWD_SIZE           30
#define GPRS_YUECMD_SIZE        10
#define GPRS_LLCMD_SIZE         10
#define CARR_OPER_TEL_SIZE      10
typedef struct {
        char APN[GPRS_APN_SIZE];                                        //  �����
    char USR[GPRS_USR_SIZE];                                        //  �û���
    char PWD[GPRS_PWD_SIZE];                                        //  ����
    char Domain[GPRS_DOMAIN_SIZE];                                  //  ����������        
    u16  Port;                                                      //  �������˿�
    u16  Interval;                                                  //  �������
    u16  RealTime_Monitor;                                            //ʵʱ���ʱ��
    u16  Temp_Null;                                                    //�����ֽڣ��Լ�4�ֽڶ��룬�����дFlashУ�����
    
}NET_PARA_STRUCT;

#define NET_PARA_SIZE           sizeof(NET_PARA_STRUCT)
#define NET_PARA_START_ADDR     2600
#define NET_PARA_END_ADDR       2662

typedef struct {    
    u16 RunHour;                                                    //  ����������ʱ��Сʱ
    u16 RunMinute;													//  ����������ʱ�����
    u16 LoadHour;                                                   //  ����������ʱ��Сʱ
    u16 LoadMinute;													//	����������ʱ�����
    u16 OilFiltHour;                                                //  ������ʹ��ʱ��
    u16 OilSepaHour;                                                //  �ͷ���ʹ��ʱ��
    u16 GasFiltHour;                                                //  ������ʹ��ʱ��
	u16 WaterFiltHour;
    u16 lubeHour;                                                   //  ����ʹ��ʱ��
    u16 GreaseHour;                                                 //  ��֬ʹ��ʱ��
	u16 BeltHour;
    /**********���²�����δ�滮��ַ************/
    u16 CurrentRunHour;											// ��������ʱ��--Сʱ
    u16 CurrentRunMinute;										//��������ʱ�� ---����
    u32 TotalEle;                                                   //  ��ʷ�ܺĵ�,Ԥ��
}RUN_HOUR_STRUCT;

#define RUN_HOUR_SIZE           sizeof(RUN_HOUR_STRUCT)
#define RUN_HOUR_START_ADDR     1998
#define RUN_HOUR_END_ADDR       2008

#define RUN_MIN_ADDR            2009                                 //  ����������ʱ���     
#define LOAD_MIN_ADDR           2010                                 //  ����������ʱ���


typedef struct {
    u32 MaxUseTime;                                                 //  ����ʹ�����ʱ��
    u16 MaxOilFiltTime;                                             //  ������ʹ�����ʱ��
    u16 MaxOilSepaTime;                                             //  �ͷ���ʹ�����ʱ��
    u16 MaxGasFiltTime;                                             //  ������ʹ�����ʱ��
    u16 MaxlubeTime;                                                //  ����ʹ�����ʱ��
    u16 MaxGreaseTime;                                              //  ��֬ʹ�����ʱ��
    u16 MaxWaterFiltTime;
	u16 Reserved;
}MAX_TIME_STRUCT;
#define MAX_TIME_SIZE           sizeof(MAX_TIME_STRUCT)
#define MAX_TIME_START_ADDR     2100
#define MAX_TIME_END_ADDR       2106


typedef struct {
    u16 RS485ErrCnt;                                                //  DTU�Ϳ�����֮ǰ��ͨ���쳣�ƴ�
	u16 MeterErrCnt;
	u16 FlowErrCnt;
	u16 ParaWrErrCnt;                                               //  д�����쳣�ƴ�
    u16 Res;
//    u16 FanVfd;                                                     //  �����Ƶͨ���쳣�ƴ�
}ERR_INFO_STRUCT;
#define ERR_INFO_SIZE           sizeof(ERR_INFO_STRUCT)
#define ERR_CNT_START_ADDR      100
#define ERR_CNT_END_ADDR        101


/*******************************************************************
                        ����״̬�ṹ�嶨��                       
*******************************************************************/

typedef struct {
    u16 Pressure1;                                                  //  ѹ��ֵ1
    s16 Temprature1;                                                //  �¶�1
    u16 CSQ;                                                        //  �ź�����
    u16 Pressure2;                                                  //  ѹ��ֵ2
	u16 Pressure3;												// ����Ͱѹ��
	u16 WaterPressure;												//  ˮѹ
    s16 Temprature2;                                                //  �¶�2
    u16 Pres1AdcVolt;                                               //  ѹ��1��ѹ
    u16 Pres2AdcVolt;                                               //  ѹ��2��ѹ
    u16 Temp1AdcVolt;                                               //  �¶�1��ѹ
    u16 Temp2AdcVolt;                                               //  �¶�1��ѹ
    u16 MachineStat;                                                //  ����״̬   
	
	/*************����Ϊ�ѹ滮***********************/
	u16 RunState;													// ����״̬�� ���С� ֹͣ
    u16 LoadPress;
    u16 UnLoadPress;
    u16 StopPress;
    u16 MaxUnloadPress;
    u16 XinJiaoDelay;
    u16 LoadDelay;
    u16 StopDelay;
    u16 StartDelay;
    u16 MainDelay;
    u16 FanDelay;
    u16 UnloadDelay;
    u16 UnblanceCurrent;

    u8 UsrPassword[10];                                             //  �û�����
    u8 FacPassword[10];                                             //  ��������
    u16 PowerVolt;                                                  //  ��Դ��ѹ
    u16 RS485ErrCnt;                                                //  485ͨ���쳣�ƴ�
    u16 GPRSLac;
    u32 GPRSCID;
    u16 AlmVal;
    u16 PreAlmVal;

    u16 Front_Bear_Temp;                                            //ǰ����¶�
    u16 Rear_Bear_Temp;                                                //������¶�
    
    u16 UpdataParaFlag:4;                                           //  ��0λ  ���������и��£� ��1λ �û������и���  ��2λ  ���Ҳ����и���,��3λ�豸״̬����

	u16 DTU_COMM_STATUS; 											//DTU 485ͨѶָʾ

	u32 Total_Power;     				// �������� ����� + ������
	u16 MatainAlarm;                  //��������״̬��
	
}SHARE_STAT_STRUCT;


typedef struct {  
    u16 Volt_A;                                                           //  A���ѹ
    u16 Volt_B;                                                           //  B���ѹ
    u16 Volt_C;                                                           //  C���ѹ
	u16 Volt_AB;
	u16 Volt_BC;
	u16 Volt_CA;
	u16 Current_A;                                                  //  A�����
    u16 Current_B;                                                  //  B�����
    u16 Current_C;                                                  //  C�����
    
    u32 Active_Power_Total;                                            //���й�����
    u32 Reactive_Power_Total;                                        //���޹�����
    u32 Apparent_Power_Total;                                        //�����ڹ���
    u16 Power_Factor_Total;                                            //�ܹ�������
    u16 Frequency;                                                    //Ƶ��
    u32 Positive_Active_Power;                                      //���ù�����  ����
    u16 Positive_Active_Power_Dec;                                  //���ù�����  С��λ
	u16 Line_Net;													//���߷�ʽ
	u16 CT;														    //�������   ����
}XY_METER_STAT_STRUCT;                                                //������ ����״̬�ṹ��

typedef union {
    
    float  F_Data;
    char   Array[4];
    
    }IEEE_FLOAT_PARA;

typedef struct {  
    
    IEEE_FLOAT_PARA Transient_Flow;                                                // ˲ʱ����  
    IEEE_FLOAT_PARA Frequency;                                                    // Ƶ��
    IEEE_FLOAT_PARA Pressure;                                                    // ѹ��
    IEEE_FLOAT_PARA Temp;                                                        // �¶�
    IEEE_FLOAT_PARA Density;                                                    // �ܶ� 
    IEEE_FLOAT_PARA Total_Flow;                                                    // �ۻ�����    

    u16 Number;                                                     // ������վ��
    u32 Specific_Power;                                                // �ȹ���    
    u32 Energy_Unit;                                                // ��λ�ܺ�
    
}FLOW_METER_STAT_STRUCT;                                            // ������ ���ݽṹ��




#define SHARE_STAT_SIZE         sizeof(SHARE_STAT_STRUCT)
#define SHARE_STAT_START_ADDR   1
#define SHARE_STAT_END_ADDR     30
#define SHARE_STAT_NUM          (SHARE_STAT_END_ADDR-SHARE_STAT_START_ADDR+1)


typedef union {
    u32 Flag;
    struct {
        u32 Reserved:1;
        u32 LackWater: 1;                                           //  ????
        u32 LackPhase: 1;                                              //  ????            
        u32 PluseError: 1;                                          //  ??????
        u32    AxialTemperOver: 1;                                        //???????                                    //    ???????

        u32 MainVfdAlarm: 1;                                        //  ??????
        u32 Reserved1: 1;//MainVfdComErr: 1;                        //  ?????????
        u32 OverMaxCurr: 1;                                         //  ????
        u32 MainCurrFault: 1;                                       //  ??????(??????)
        u32 CurrImbalance: 1;                                       //  ???????
        
        u32 FanVfdAlarm: 1;                                         //  ??????            
        u32 Reserved2: 1;//FanVfdComErr:  1;                        //  ????????? 
        u32 FanOverCurr: 1;                                         //  ????
        u32 FanCurrFault:  1;                                       //  ??????(??????)
        u32 FanCurrImbalance: 1;                                    //  ???????
            
        u32 OverMaxPres1: 1;                                        //  ??1????
        u32 PresSen1Fault: 1;                                       //  ?????1????
        
        u32 OverMaxTemp1:  1;                                       //  ??1??????
        u32 TempSen1Fault: 1;                                       //  ?????1????                                     
        u32 OverMinTemp:   1;                                       //  ??????
        u32 TempImbalance: 1;                                       //  ????????            
        u32 OverMaxUsrHour: 1;                                      //  ????????
        u32 SupplyVoltageOverMax: 1;                                //  ??????                                //     ??????
        u32 SupplyVoltageOverMin: 1;                                //  ??????                                //     ??????
       u32 RS485CommErr: 1;                                        //  DTU?????????
       // u32 RS485MeterErr:1;									    //  DTU ?????????
		//u32 RS485FlowErr:1;											//  DTU ?????????
		//u32 Rs485ResErr:1;											// ???485 ????
       // u32 Bit28_31: 4;            
          u32 Bit25_31:7;                             
    }Bits;
}ALARM_FLAG_UNION;
typedef union {
    u32 Flag;
    struct {
     //   u32 OverMaxOilFiltTime: 1;                                  //  ������Ԥ�� 
    //    u32 OverMaxOilSepaTime: 1;                                  //  �ͷ���Ԥ��
    //    u32 OverMaxGasFiltTime: 1;                                  //  ������Ԥ��
    //    u32 OverMaxlubeTime:    1;                                  //  ����Ԥ��
    //    u32 OverMaxGreaseTime:  1;                                  //  ��֬Ԥ��
    //    u32 Bit5_7: 3;
        
   //     u32 Bit8_15: 8;
        
        u32 OverMinTemp: 1;                                        //  ��ʱ���������Ԥ��
        u32 OverMaxTemp: 1;                                        //  �¶ȹ���Ԥ��
        u32 FrontTempHigh:1;
        u32 oilDifference:1;
        u32 WatarLevelHigh:1;
        u32 WaterLevelLow:1;
        u32 PipeBlock:1;
        u32 Reserved:1;
		
        u32 Bit8_31: 24; 
  
    }Bits;
}PREALM_FLAG_UNION;
typedef union {
    u32 Flag;
    struct {
        u32 DevPowerOn: 1;                                  //  �豸�ӵ�
        u32 DevStartUp: 1;                                  //  �豸����
        u32 DevShutDown: 1;                                 //  �豸ͣ��
        u32 Bit3_5: 3; 
        
        u32 DevStop:    1;                                  //  ����ֹͣ        
        u32 LoadingRun:  1;                                 //  ��������
        u32 IdlerRun: 1;                                    // ��������        
        u32 DevDormancy: 1;                                    // �վ�����        
        u32 Bit10_14: 5;                                    //  Ԥ��

        u32 FanRun: 1;                                      //  �������
        u32 FanStop: 1;                                        //  ���ֹͣ

        u32 Bit17_31: 15;        
    }Bits;
}DEVALM_FLAG_UNION;




typedef union {
    u32 Flag;
    struct {
        u32 RouchScreenReboot: 1;                 //  ��������������
        u32 RtcFault: 1;                          //  RTC����
        u32 MemoryFault: 1;                       //  �洢������
        u32 MainVfdComErr: 1;                     //  ������Ƶ��ͨ���쳣
          u32 FanVfdComErr:  1;                     //  �����Ƶ��ͨ���쳣 
        
        u32 Bit5_7: 3;
        u32 Bit8_15: 8;
        u32 Bit16_23: 8;
        u32 Bit24_31: 8;        
    }Bits;
}OTHERS_ALM_FLAG_UNION;



typedef struct{

    u16 Key_Value;       //�������KEYֵ
    u32 Addr;             //KEYֵ��Ӧ�Ŀ����� ��ַ
    u8    DataLen;         //���ݳ���
    u8  DataType: 3;     //�������ͣ�0������1���ַ�����2���������ͣ�3:16������ʾ��4����״̬λ
    u8    DecNum:3;         //DataType=2ʱ��С����λ����0��1��2��3��4
    u8    WriterFlag:1;     //0��ֻ����1���ɶ�д
    u8    StorageFlag:1;     //0�����洢��1����洢
    
}SYS_MONITOR_DATA_STRUCT;




typedef struct{

    u16 SysPressure;        // ϵͳѹ��
    u16 PhaseProVolt;        // ���򱣻���ѹ
    u16 OpenPhaseProVolt;    // ȱ�ౣ����ѹ
    u16 Volt;                // ��ѹ
    u16 WarningValue;        // Ԥ��ֵ
    u16 RunStatus;            // ����״̬
    u16 Timing;                // ��ʱ
    u16 Fault;                // ����
    u16 FaultValue;            // ����ֵ
    u16 OilPressDif;        // �ͷ�ѹ��
    u16 MainStatus;            // ����״̬��
    u16 MainFault;            // ����������
    u16 FanStatus;            // ���״̬��
    u16 FanFault;            // ���������
    u32 MainPfreqPowerThis;    // ��Ƶ���������õ�
    u32 FanPfreqPowerThis;    // ��Ƶ��������õ�
    u32 MainPfreqUI;        // ��Ƶ����UI
    u32 FanPfreqUI;            // ��Ƶ���UI
    
    
    u16 TempUnit;                // �¶ȵ�λ
    u16 PressureUnit;            // ѹ����λ
    u16 WarningStop;            // Ԥ������ͣ��
    u16 FrontBearingWarnTemp;    // ǰ���Ԥ���¶�
    u16 FrontBearingAlarmTemp;    // ǰ��б����¶�
    u16 OilPressDifWarn;        // �ͷ�Ԥ��ѹ��
    u16 OilPressDifAlarm;        // �ͷֱ���ѹ��
    u16 DrainOpenDelay;            // ��ˮ����ʱ
    u16 DrainCloseDelay;        // ��ˮ����ʱ
    u16 SoftStartDelay;            // ������ʱ
    u16 AssistStartTime;        // ��������ʱ��
    u16 AssistLoadDelay;        // ����������ʱ
    u16 AssistUnloadDelay;        // ����ж����ʱ
    u16 AssistStartTemp;        // �������¶�
    u16 LoadMode;                // ���ط�ʽ
    u16 StartStopMode;            // ��ͣ��ʽ
    u16 CorrespondMode;            // ͨ�ŷ�ʽ
    u16 LanguageSelection;        // ����ѡ��
    u16 RunMode;                // ���з�ʽ
    u16 SysStopPressure;        // ϵͳͣ��ѹ��
    u16 HistoryFaultReset;        // ��ʷ���ϸ�λ
    u16 FactoryCode1;            // ��������1
    u16 FactoryCode2;            // ��������2
    u16 FactoryDate;            // ��������
    
    
    u16 MainIntegInitValue;        // �������ֳ�ֵ
    u16 MainIntegRange;            // �������ַ�Χ
    u16 MainRatioGain;            // ������������
    u16 MainIntegGain;            // ������������
    u16 MainDiffGain;            // ����΢������
    u16 MainFreqToplimit;        // ����Ƶ������
    u16 MainFreqLowlimit;        // ����Ƶ������
    u16 MainIdlingFreq;            // ��������Ƶ��
    u16 MainVfdNum;                // ������Ƶ��վ��
    u16 MainPIDPeriod;            // ����PID����
    u16 MainVfdModel;            // ������Ƶ���ͺ�
    u16 FanIntegInitValue;        // ������ֳ�ֵ
    u16 FanIntegRange;            // ������ַ�Χ
    u16 FanRatioGain;            // �����������
    u16 FanIntegGain;            // �����������
    u16 FanDiffGain;            // ���΢������
    u16 FanFreqToplimit;        // ���Ƶ������
    u16 FanFreqLowlimit;        // ���Ƶ������
    u16 FanIdlingFreq;            // �������Ƶ��
    u16 FanVfdNum;                // �����Ƶ��վ��
    u16 FanPIDPeriod;            // ���PID����
    u16 FanVfdModel;            // �����Ƶ���ͺ�
    u16 VoltOvertop;            // ��ѹ����
    u16 VoltOverlow;            // ��ѹ����
    u16 CorrespondOverTime;        // ͨ�ų�ʱ


    u16 ReFreqPressure;            // ��Ƶѹ��
    u16 MainRiseRate;            // ������������
    u16 MainDownRate;            // �����½�����
    u16 MainPower;                // ��������
    u16 MainRotationRate;        // ����ת��
    u16 FanRiseRate;            // �����������
    u16 FanDownRate;            // ����½�����
    u16 FanPower;                // �������
    u16 FanRotationRate;        // ���ת��
    u16 FanFreqStart;            // ��Ƶ�����
    u16 FanFreqStop;            // ��Ƶ���ͣ
    u16 MainStopMode;            // ����ͣ����ʽ
    u16 TimeStartStopFunc;        // ��ʱ��ͣ����
    u16 TimePressureFunc;        // ��ʱѹ������
    u16 LowTempProtect;            // ���±���
    u16 MainVfdStartMode;        // ����Ƶ��������ʽ
    u16 FanVfdStartMode;        // �����Ƶ��������ʽ
    u16 CorrespondStartVfdNum;    // ͨ������Ƶ������
    u16 CorrespondStopVfdNum;    // ͨ��ͣ��Ƶ������
    u16 MainPfreqPowerFactor;    // ��Ƶ��������ϵ��
    u16 MainfreqPowerFactor;    // ��Ƶ��������ϵ��
    u16 FanPfreqPowerFactor;    // ��Ƶ�������ϵ��
    u16 FanfreqPowerFactor;        // ��Ƶ�������ϵ��
    u16 ProMainVfdDelay;        // Ԥ��������Ƶ����ʱ
    u16 PowerDownRestart;        // ������������
    u16 FreqSelect;                // Ƶ��ѡ��
    u16 PipePressure;            // ��·ѹ��
    u16 RearBearingWarnTemp;    // �����Ԥ���¶�
    u16 RearBearingAlarmTemp;    // �����ͣ���¶�
    u16 LowWaterProtectTime;
    u16 AutoChangeWaterActTime;  //�Զ���ˮ����
    u16 AutoChangeWaterCycle;   //�Զ���ˮ����
    u16 MaxUseTimeFunc; 		//���ʹ��ʱ�书��
   	u16 ValveState;            //����״̬
   	u16 MainIGBTemp;  		 // ����IGBT�¶�
   	u16 FaultStatus1;   
   	u16 FaultStatus2;
   	u16 FaultStatus3;   
   	u16 FaultStatus4;
    
    
}MAM6080_OTHER_PARA_STRUCT;

/*******************************************************************
                        ������ַ�궨��                       
*******************************************************************/
#define SHARE_Pressure1_KEY                   1
#define SHARE_Temprature1_KEY                 2
#define SHARE_CSQ_KEY                         3
#define SHARE_PowerVolt_KEY                 4
#define SHARE_MachineStat_KEY                 5
#define SHARE_MAIN_A_Current_KEY              6
#define SHARE_MAIN_B_Current_KEY              7
#define SHARE_MAIN_C_Current_KEY              8
#define SHARE_FAN_A_Current_KEY               9
#define SHARE_FAN_B_Current_KEY               10
#define SHARE_FAN_C_Current_KEY               11
#define SHARE_Pressure2_KEY                   12
#define SHARE_Temprature2_KEY                 13

#define MAIN_OutFreq_KEY                         40
#define MAIN_OutSpeed_KEY                         41

#define MAIN_OutCurrent_KEY                     42
#define MAIN_OutVolt_KEY                         43
#define MAIN_OutPower_KEY                         44
#define FAN_OutFreq_KEY                         70
#define FAN_OutSpeed_KEY                         71
#define FAN_OutCurrent_KEY                         72
#define FAN_OutVolt_KEY                         73
#define FAN_OutPower_KEY                         74

#define SIM_IMEI_KEY                             150
#define SIM_SIMNum_KEY                           158
#define SIM_GPRSLac_KEY                          166
#define SIM_GPRSCID_KEY                          167

#define MAIN_Power_Consume_Total_KEY             200
#define POWER_Consume_Total_KEY                 202
#define MAIN_PFREQ_Power_Consume_Total_KEY         204
#define FAN_PFREQ_Power_Consume_Total_KEY         206
#define FRONT_Bear_Temp_KEY                     208
#define REAR_Bear_Temp_KEY                         209

#define METER_VOLTAGE_A_KEY                      400                                        //  A���ѹ
#define METER_VOLTAGE_B_KEY                      401                                        //  B���ѹ
#define METER_VOLTAGE_C_KEY                      402                                        //  C���ѹ
#define METER_CURRENT_A_KEY                      403                                     //  A�����
#define METER_CURRENT_B_KEY                      404                                     //  B�����
#define METER_CURRENT_C_KEY                      405                                     //  C�����
    
#define METER_ACTIVE_POWER_TOTAL_KEY              406                                        //���й�����
#define METER_REACTIVE_POWER_TOTAL_KEY          407                                        //���޹�����
#define METER_APPARENT_POWER_TOTAL_KEY          408                                        //�����ڹ���
#define METER_POWER_FACTOR_TOTAL_KEY              409                                        //�ܹ�������
#define METER_FREQUENCY_KEY                      410                                        //Ƶ��
#define METER_POSITIVE_ACTIVE_POWER_KEY          411                                        //���ù�����  ��λ

#define RUN_RunHour_KEY                         2000
#define RUN_LoadHour_KEY                         2002
#define RUN_OilFiltHour_KEY                     2004
#define RUN_OilSepaHour_KEY                     2005
#define RUN_GasFiltHour_KEY                     2006
#define RUN_lubeHour_KEY                         2007
#define RUN_GreaseHour_KEY                         2008
#define HOUR_MaxUseTime_KEY                     2100
#define HOUR_MaxOilFiltTime_KEY                 2102
#define HOUR_MaxOilSepaTime_KEY                 2103
#define HOUR_MaxGasFiltTime_KEY                 2104
#define HOUR_MaxlubeTime_KEY                     2105
#define HOUR_MaxGreaseTime_KEY                     2106

#define SHARE_UnLoadPress_KEY                     2107
#define SHARE_LoadPress_KEY                     2108
#define MAIN_Cfreq_Press_KEY                     2109
#define SHARE_StopPress_KEY                     2110
#define SHARE_MaxUnloadPress_KEY                 2111
#define FAN_StopTemp_KEY                         2112
#define FAN_StartTemp_KEY                        2113
#define FAN_Cfreq_Temp_KEY                         2114
#define FAN_PreAlmTemp_KEY                         2115
#define FAN_AlmTemp_KEY                         2116

#define SHARE_StartDelay_KEY                     2118
#define SHARE_LoadDelay_KEY                     2119
#define SHARE_UnloadDelay_KEY                     2120
#define SHARE_StopDelay_KEY                     2121
#define MAIN_RateCurrent_KEY                     2326
#define SHARE_MainDelay_KEY                       2328
#define SHARE_XinJiaoDelay_KEY                    2329
#define FAN_RateCurrent_KEY                       2366
#define SHARE_UnblanceCurrent_KEY                 2327
#define SHARE_FanDelay_KEY                        2368

#define ADJ_Press1MinVolt_KEY   2200
#define ADJ_Press1MaxVolt_KEY   2201
#define ADJ_Press2MinVolt_KEY   2202
#define ADJ_Press2MaxVolt_KEY   2203
#define ADJ_Temp1MinVolt_KEY    2204
#define ADJ_Temp1MaxVolt_KEY    2205
#define ADJ_Temp2MinVolt_KEY    2206
#define ADJ_Temp2MaxVolt_KEY    2207
#define ADJ_PowerVoltageK_KEY   2208

#define DEV_MachineSN_KEY         2500
#define DEV_MacYear_KEY           2510
#define DEV_MacMonth_KEY          2511
#define DEV_MacDay_KEY            2512
#define DEV_SCREENVer_KEY         2513
#define DEV_AppVer_KEY            2518
#define DEV_ID_KEY                2523
#define DEV_DevYear_KEY           2528
#define DEV_DevMonth_KEY          2529
#define DEV_DevDay_KEY            2530

#define NET_APN_KEY             2600  
#define NET_USR_KEY             2615 
#define NET_PWD_KEY             2630 
#define NET_Domain_KEY          2645 
#define NET_Port_KEY            2660 
#define NET_Interval_KEY        2661 
#define NET_Monitor_KEY         2662 

#define PASSWORD_UsrSvr_KEY        3000
#define PASSWORD_FacSvr_KEY        3005
#define PASSWORD_SenSvr_KEY        3010



#pragma pack()




#endif


