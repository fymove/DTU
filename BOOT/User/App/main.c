#include "stm32f10x.h"
#include "bsp.h"
#include "timer.h"
#include "SPIFlash.h"
#include "STFlash.h"
#include "string.h"

#define SST_UPDATE_ADDR     (4<<10)                           //  SST Flash 4K´¦
#define STM_APP_ADDR        (4 << 10)
#define UPGRADE_FLAG        "XWL "
#define STM_FLASH_PAGE_SIZE 0x400                               //  Ò³´óÐ¡:1K

//#define BOOTLOADER_VERSION  "STM32F103C8_Boot_V1.00"



#define UPDATE_DATA_BUF_DIZE    512

u8  Update[20];
u32 UpdateSize;
u8  UpdateData[UPDATE_DATA_BUF_DIZE];


typedef  void (*pFunction)(void);
pFunction Jump_To_Application;
uint32_t JumpAddress;


int main(void)
{    
    u16 i;
    u16 PageNum;
    u16 ReadLen;
    u32 SSTAddr, STMAddr;
    u32 AppAddr = 0x8000000 + STM_APP_ADDR;
    
    init_hw();
    
//    DebugMsg("\r\n\r\n");
//    DebugMsg(BOOTLOADER_VERSION);
    
    SPIFlashInit();
    wdg_feed();    
    
    SPIFlashRead(SST_UPDATE_ADDR, Update, 8);
    if(0 == memcmp(Update, UPGRADE_FLAG, strlen(UPGRADE_FLAG))) {
//        DebugMsg("\r\nSystem Update ...\r\n");
        memcpy((char *)&UpdateSize, &Update[strlen(UPGRADE_FLAG)], 4);
        if((UpdateSize >= (10<<10)) && (UpdateSize <= (200<<10))) {
            PageNum = UpdateSize / STM_FLASH_PAGE_SIZE;
            if(UpdateSize % STM_FLASH_PAGE_SIZE) {
                PageNum += 1;
            }

//            DebugMsg("Erase flash ...\r\n");
            for(i=0; i<PageNum; i++) {
                STFlashErase(AppAddr + i * STM_FLASH_PAGE_SIZE);
                wdg_feed();
            }

            SSTAddr = SST_UPDATE_ADDR + 4096;
            STMAddr = AppAddr;

//            DebugMsg("Copy file ...\r\n");

            while(UpdateSize) {
                ReadLen = (UpdateSize >= UPDATE_DATA_BUF_DIZE) ? UPDATE_DATA_BUF_DIZE : UpdateSize;
                SPIFlashRead(SSTAddr, UpdateData, ReadLen);
                STFlashWrite(STMAddr, UpdateData, ReadLen);
                SSTAddr += ReadLen;
                STMAddr += ReadLen;
                UpdateSize -= ReadLen;
                wdg_feed();
            }
        }
        SPIFlashErase4K(SST_UPDATE_ADDR);
    }
    
//    DebugMsg("\r\nEnter system ...\r\n");
    wdg_feed();
    
    JumpAddress = *(__IO uint32_t*) (AppAddr + 4);
    Jump_To_Application = (pFunction) JumpAddress;
    /* Initialize user application's Stack Pointer */
    __set_MSP(*(__IO uint32_t*) AppAddr);
    Jump_To_Application();
}



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
