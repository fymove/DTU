#include <includes.h>
#include "sfud.h"


void    SoftWareInit(void)
{
    AppDebugInit();
    
//  AppDebug.Bits.Enable = TRUE;
    DebugMsg(DEBUG_NONE, "\r\n\r\n/**********************************************/\r\n");
    DebugMsg(DEBUG_NONE, "Device Model: %s\r\n", PRODUCT_MODLE);         
    DebugMsg(DEBUG_NONE, "App Version : %s.%s\r\n", APP_VERSION, ID_HEADER);  
    DebugMsg(DEBUG_NONE, "Build Time  : %s %s\r\n", __DATE__, __TIME__); 
    DebugMsg(DEBUG_NONE, "/**********************************************/\r\n\r\n");    
//    AppDebug.Bits.Enable = TRUE;
	
#if USE_RTC_EN
//    InitRtc();
#endif    
    FeedDog();
    SysVarInit();
    SysParaRead();
    FeedDog();
}
#if 0


#define SFUD_DEMO_TEST_BUFFER_SIZE                     1024

static void sfud_demo(uint32_t addr, size_t size, uint8_t *data);

static uint8_t sfud_demo_test_buf[SFUD_DEMO_TEST_BUFFER_SIZE];
void test()
{
	
    /* SFUD initialize */
    if (sfud_init() == SFUD_SUCCESS) {
        sfud_demo(0, sizeof(sfud_demo_test_buf), sfud_demo_test_buf);
    }

}


/**
 * SFUD demo for the first flash device test.
 *
 * @param addr flash start address
 * @param size test flash size
 * @param size test flash data buffer
 */


static void sfud_demo(uint32_t addr, size_t size, uint8_t *data) {
    sfud_err result = SFUD_SUCCESS;
    const sfud_flash *flash = sfud_get_device_table() + 0;
    size_t i;
    /* prepare write data */
    for (i = 0; i < size; i++) {
        data[i] = i;
    }
    /* erase test */
    result = sfud_erase(flash, addr, size);
    if (result == SFUD_SUCCESS) {
        DebugMsg(DEBUG_SFUD,"Erase the %s flash data finish. Start from 0x%08X, size is %ld.\r\n", flash->name, addr,
                size);
    } else {
        DebugMsg(DEBUG_SFUD,"Erase the %s flash data failed.\r\n", flash->name);
        return;
    }
    /* write test */
    result = sfud_write(flash, addr, size, data);
    if (result == SFUD_SUCCESS) {
        DebugMsg(DEBUG_SFUD,"Write the %s flash data finish. Start from 0x%08X, size is %ld.\r\n", flash->name, addr,
                size);
    } else {
        DebugMsg(DEBUG_SFUD,"Write the %s flash data failed.\r\n", flash->name);
        return;
    }
    /* read test */
    result = sfud_read(flash, addr, size, data);
    if (result == SFUD_SUCCESS) {
        DebugMsg(DEBUG_SFUD,"Read the %s flash data success. Start from 0x%08X, size is %ld. The data is:\r\n", flash->name, addr,
                size);
        DebugMsg(DEBUG_SFUD,"Offset (h) 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F\r\n");
        for (i = 0; i < size; i++) {
            if (i % 16 == 0) {
                DebugMsg(DEBUG_SFUD,"[%08X] ", addr + i);
            }
            DebugMsg(DEBUG_SFUD,"%02X ", data[i]);
            if (((i + 1) % 16 == 0) || i == size - 1) {
                Debug("\r\n");
            }
        }
		Debug("\r\n");
    } else {
        DebugMsg(DEBUG_SFUD,"Read the %s flash data failed.\r\n", flash->name);
    }
    /* data check */
    for (i = 0; i < size; i++) {
        if (data[i] != i % 256) {
            DebugMsg(DEBUG_SFUD,"Read and check write data has an error. Write the %s flash data failed.\r\n", flash->name);
			break;
        }
    }
    if (i == size) {
        DebugMsg(DEBUG_SFUD,"The %s flash test is success.\r\n", flash->name);
    }
}

#endif

//RCC_ClocksTypeDef get_rcc_clock;
int  main (void)
{          
    u16  Time1sCnt = 0;
    bool bFirst = TRUE;
	
//	RCC_GetClocksFreq(&get_rcc_clock);
	
#ifndef PRJ_RELEASE
    Simulation();
#endif

    HardWareInit();
	AppDebug.Flag = FALSE;
    SoftWareInit();   
    AlarmEventInit();
    GprsAppInit();  
    ProSendInit();
    MultFunInit();    
    RS485ComInit();
    Task_MeterInit();
    Task_Meter2Init();

    while(1) 
    {
        Task_ProDeal();
        Task_VfdDeal();
        Task_MeterDeal();
		
        Task_Meter2Deal();
        
        if(!AlmDealDelay.Bits.Flag) 
        {                               //  防止上电通信异常报警
            AlarmEventDeal();
        } 

        if(TimeFlag.Bits.N2ms) 
        {
            TimeFlag.Bits.N2ms = FALSE;
            if(CfgDelay.Bits.Flag || GbDtuEnterCfg || AppDebug.Bits.Enable) 
            {
                if(UartTest.Rcv.Bits.RS485_0) 
                {
                    UartTest.Rcv.Bits.RS485_0 = FALSE;
                    if((CFG_DATA_HEAD_1 ==(u8)UartTest.Buf[0]) && (CFG_DATA_HEAD_1 == (u8)UartTest.Buf[1]))
                    {                                                                
                        GbCfgCmd = TRUE;
                        if(dtuFactoryConfig(UartTest.Buf, UartTest.Len)) 
                        {  //  退出配置
                            if(!CfgDelay.Bits.Flag) 
                            {
                                RS485SndDly();
                                RS485SndDly();
                                RS485SndDly();
                                RS485SndDly();
                                RS485SndDly();
                                RS485SndDly();
                                Task_VfdInit();                     //  超过10s,退出是初始化控制器接口
                                GbCfgCmd = FALSE;
                            }
                        }
                    } 
                    else 
                    {
                        GbCfgCmd = FALSE;
                        if(!GbDtuEnterCfg) 
                        {
                            UsrCmdParse(UartTest.Buf, UartTest.Buf);
                            if(bFirst) 
                            {
                                bFirst = FALSE;
                                USART1->CR1 |= USART_TX_ON;     //  发送关闭  
                                USART1->CR1 |= USART_RX_ON;     //  接收开启
                            }
    
                            DebugMsg(DEBUG_NONE, UartTest.Buf);
                        }
                    }
                }   
            } 
            else 
            {
                Task_VfdComm(pVfd, 2); 
				
			}
		# if 0
			if (GpSysPara->Dev.BindSatus & (3<<1))  
			{
				Task_MeterComm(pMeter, 5);
			}
		#endif 
			Task_MeterComm(pMeter, 5);	
			Task_Meter2Comm(pMeter2, 5);
		
        }
        
        if(TimeFlag.Bits.N500ms) 
        {
            TimeFlag.Bits.N500ms = FALSE;
           DevStatToSystem();
            SysParaStorage();  
            FeedDog();
         
            if(++Time1sCnt >= 2) 
            {                                  //  1s
                Time1sCnt = 0;

                Task_MultFun_1s();
            }
        } 
        else if(TimeFlag.Bits.N50ms) 
        {
            TimeFlag.Bits.N50ms = FALSE;
            TaskGC65(50);  
            AlarmFilterTimer(50);  
            SysComLed(50);
         //   SysRunLed(50);
         	Rs485ComLed(50);
            UpgradeTask();

            if(RebootTime.Bits.Flag) 
            {
                if(RebootTime.Bits.Timer >= 50) 
                {
                    RebootTime.Bits.Timer -= 50; 
                } 
                else 
                {
                    while(1);
                }
            }

          //  PltUsrHourAlarmCheck();                                 //  普乐特耗材模拟预警判断  test
        } 
        else if(TimeFlag.Bits.N20ms) 
        {
            TimeFlag.Bits.N20ms = FALSE;
            Task_ProSend(20);            
        }
		
    }
}


