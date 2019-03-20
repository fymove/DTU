#define _InUpgrade
#include "stm32f10x.h"
#include "typedef.h"
#include "gc65.h"
#include "app_upgrade.h"
#include "app_debug.h"
#include "app_cfg.h"
//#include "SPIFlash.h"
#include "string.h"
#include "gc65.h"
#include "gc65_bsp.h"
#include "comm.h"
#include "sfud.h"
#include "crc32.h"

//#define MemError(fmt, args...)   ErrorMsg("App_Upgrade.c", __LINE__, fmt, ##args)

#define ADDR_BOOTLOADER         0x00000000                          //  Bootloader起始地址
#define ADDR_APP_FLAG           0x00006000                          //  应用程序高低区标识
#define ADDR_PARA               0x00006800                          //  系统参数起始地址
#define ADDR_APP_LOW            0x0000E000                          //  应用程序低区起始地址
#define ADDR_APP_HIGH           0x00027000                          //  应用程序高区起始地址
#define FALSH_SECTOR_SIZE       0x800                               //  Flash扇区大小

//#define APP_LOW_FLAG    "LowAddr"
//#define APP_HIGH_FLAG   "HighAddr"

//#define SSTFLASH_SECTOR_SIZE    4096

u8 UpgradeBuf[512];

char    UpdateFileCrcCheck(void)
{
    u8  ret = FALSE;
    u8  *pBuf;
//    u32 FileCrc;
    u32 Addr = SST_UPDATE_ADDR + SSTFLASH_PAGE_SIZE;
	
	const sfud_flash * flash_table = sfud_get_device_table();

//    pBuf = (u8 *)kmalloc(512);
//    if(NULL == pBuf) {
//        MemError("kmalloc fail\r\n");
//        return FALSE;
//    }
    pBuf = UpgradeBuf;
    CRC32_CTX ctx = { 0 };

    CRC32_Init(&ctx);
   

   
  //  CRC32CalcReset();
    sfud_err  result = SFUD_SUCCESS;
    FtpInf.AllGetSize = 0;    
    do {
        FtpInf.CurGetSize = ((FtpInf.FileSize-FtpInf.AllGetSize)>= 512) ? 512 : (FtpInf.FileSize-FtpInf.AllGetSize);
		result = sfud_read(flash_table, Addr, FtpInf.CurGetSize, pBuf );
		if (SFUD_SUCCESS != result)
		{
			DebugMsg(DEBUG_UPGRADE, "flash read faild,Err_no:%d, Read addr:[%8X]\r\n", result, Addr);
			goto EXIT;
		}
       // SPIFlashRead(Addr, pBuf, FtpInf.CurGetSize);
       // FileCrc = CRC32Calc(pBuf, FtpInf.CurGetSize);
        CRC32_Update(&ctx, pBuf, FtpInf.CurGetSize);
        Addr += FtpInf.CurGetSize;
        FtpInf.AllGetSize += FtpInf.CurGetSize;
        FeedDog();
    } while(FtpInf.AllGetSize < FtpInf.FileSize);
	
	CRC32_Final(&ctx);
    if(FtpInf.FileCrc == ctx.crc) {
        ret = TRUE;
        DebugMsg(DEBUG_UPGRADE, "Crc OK\r\n");
    } else {
        DebugMsg(DEBUG_UPGRADE, "File crc %08X != Calc crc %08X\r\n", FtpInf.FileCrc, ctx.crc);
    }

//    kfree(pBuf);
EXIT:
	return ret;
}

#define UPGRADE_FLAG        "XWL "
void    SysAppInfUpdate(void)
{
	
    u8  FlagLen = strlen(UPGRADE_FLAG);
    u32 FileSize = FtpInf.FileSize;
	
	const sfud_flash * flash_table = sfud_get_device_table();
	
    sfud_write(flash_table, SST_UPDATE_ADDR,  FlagLen, (u8*)UPGRADE_FLAG);
    sfud_write(flash_table, SST_UPDATE_ADDR+FlagLen, 4, (u8*)&FileSize);
    sfud_write(flash_table, SST_UPDATE_ADDR+FlagLen+4, 3, (u8*)"END");

    #if 0
    SPIFlashWrite(SST_UPDATE_ADDR, (u8*)UPGRADE_FLAG, FlagLen);
    SPIFlashWrite(SST_UPDATE_ADDR+FlagLen, (u8*)&FileSize, 4);
    SPIFlashWrite(SST_UPDATE_ADDR+FlagLen+4, (u8*)"END", 3);
    #endif
}

void    UpgradeSectorErase(void)
{
	const sfud_flash * flash_table = sfud_get_device_table();
	sfud_erase(flash_table, SST_UPDATE_ADDR+SSTFLASH_PAGE_SIZE, FtpInf.FileSize);
#if 0 
    u16 i;
    u16 EraseSector = FtpInf.FileSize / SSTFLASH_PAGE_SIZE + 2;
    
    for(i=0; i<EraseSector; i++) {
    	sfud_erase(flash_table, SST_UPDATE_ADDR + i * SSTFLASH_PAGE_SIZE, 1024*4);
     //   SPIFlashErase4K(SST_UPDATE_ADDR + i * SSTFLASH_PAGE_SIZE);
        FeedDog();
    }
	
	
   #endif 
  	FeedDog();
    DebugMsg(DEBUG_UPGRADE, "File Size: %d\r\n", FtpInf.FileSize);
}


char    FtpDataGetFlag(void)
{
    if(GprsCtrlInfo.Rlst2.Bits.FTP_GETOVER) {
        GprsCtrlInfo.Rlst2.Bits.FTP_GETOVER = FALSE;
        GprsCtrlInfo.blTimeOut = FALSE;
        return TRUE;
    }

    return FALSE;
}


u8  ModelIsFtping(void)
{
    return GprsCtrlInfo.Module.Bits.Ftping;
}

void    FTPConnectRequestSet(void)
{
    GprsCtrlInfo.Reqult.Bits.FTP_CONNECT = TRUE;
}

void    FtpTimeDelay(int DelayMs)
{
#if GPRS_FTP_EN
#endif
    GprsCtrlInfo.Rlst2.Flag = 0;
    
    GprsCtrlInfo.TmrMsCnt = DelayMs;
    GprsCtrlInfo.blTimeOut = FALSE;
    GprsCtrlInfo.Rlst.Flag = 0;
}


void    UpdateFileGet(void)
{
    u32 SurplusSize;

    SurplusSize = FtpInf.FileSize - FtpInf.AllGetSize;
    FtpInf.CurGetSize = (SurplusSize >= 512) ? 512 : SurplusSize;
    if(0 == FtpInf.AllGetSize) {
        FtpInf.CurGetSize++;                                        //  第一包多获取1字节
    }
    
    DebugMsg(DEBUG_UPGRADE, "CurGetSize: %d\r\n", FtpInf.CurGetSize);
    GprsUartDMAReceive(FtpInf.CurGetSize);

//    FtpTimeDelay((0 == FtpInf.AllGetSize) ? 30000 : 20000);
    FtpTimeDelay(30000);
}

int    UpdateFileWrite(void)
{
    char i;
    u8 *pBuf;
    const sfud_flash * flash_table = sfud_get_device_table();
    GetGprsUartDMABuf(&pBuf);
    
    if(0 == FtpInf.AllGetSize) {        
        for(i=0; i<2; i++) {
            if((0x0D == *pBuf) || (0x0A == *pBuf)) {
                pBuf++;
                FtpInf.CurGetSize--;
            } else {
                break;
            }
        }        
    }
    DebugMsg(DEBUG_UPGRADE, "Write Addr: %04X %d\r\n", Upgrade.BeginAddr+FtpInf.AllGetSize, FtpInf.CurGetSize);
    sfud_err result = SFUD_SUCCESS;
    
	result =  sfud_write(flash_table, Upgrade.BeginAddr+FtpInf.AllGetSize, FtpInf.CurGetSize, pBuf);
	if (SFUD_SUCCESS == result)
	{
		 FtpInf.AllGetSize += FtpInf.CurGetSize;
   		 DebugMsg(DEBUG_UPGRADE, "Get Size %5d/%5d\r\n", FtpInf.AllGetSize, FtpInf.FileSize);
	}
	else
	{
		UpgradeCancel();
		DebugMsg(DEBUG_UPGRADE, "-----Write faild!------ errno:%d, current write addr:[%8x]\r\n", result, Upgrade.BeginAddr+FtpInf.AllGetSize);
		goto ERROR_EXIT;
	}
	return 0;
ERROR_EXIT:
	return -1;
	
	
	//SPIFlashWrite(Upgrade.BeginAddr+FtpInf.AllGetSize, pBuf, FtpInf.CurGetSize);
   
}

void    UpgradeFlagSet(void)
{
    GPRS_DISABLE_RECEIVE();    
    Upgrade.bits.Flag = TRUE;
    Upgrade.Step = 0;
}

void UpgradeCancel(void)
{
	GPRS_ENABLE_RECEIVE();
	Upgrade.bits.Flag = FALSE;
    Upgrade.Step = 0;
}

static char GbRebootFlag = FALSE;
void    RebootRequest(void)
{
    GbRebootFlag = TRUE;
}

char    GetRebootFlag(void)
{
    return GbRebootFlag;
}


void    UpgradeTask(void)
{    
    if(!Upgrade.bits.Flag){
        return;
    }

    switch(Upgrade.Step) {
        case 0:
            FtpInf.FileGetFinish = FALSE;
            Upgrade.BeginAddr = SST_UPDATE_ADDR + SSTFLASH_PAGE_SIZE;
            Upgrade.Step++;
            break;
        case 1:                                                     //  擦除扇区
            UpgradeSectorErase();
            Upgrade.Step++;
            
            break;
        case 2:                                                     //  获取第一包数据
            FtpInf.AllGetSize = 0;
            UpdateFileGet();
            Upgrade.Step++;
            break;
        case 3:                                                     //  获取数据
            if(FtpDataGetFlag()) {                
               if (0 != UpdateFileWrite())
               	break;
//                DebugMsg(DEBUG_UPGRADE, "Update data is %s\r\n", DMAUart3Buf);
                
                if(FtpInf.AllGetSize >= FtpInf.FileSize) {                  
                    GPRS_ENABLE_RECEIVE();     
                    FtpInf.FileGetFinish = TRUE;
                    Upgrade.Step++;
                    break;
                }

                UpdateFileGet(); 
            } else if(!ModelIsFtping()) {
                Upgrade.Step = 0;                
                DebugMsg(DEBUG_UPGRADE, "Update Fail\r\n");
                Upgrade.bits.Flag = FALSE;
            }
            break;
        case 4:                                                     //  CRC校验
            if(UpdateFileCrcCheck()) {
                SysAppInfUpdate();
                Upgrade.Step++;
            } else {
                Upgrade.Step = 0;                
                DebugMsg(DEBUG_UPGRADE, "Update Fail\r\n");
                Upgrade.bits.Flag = FALSE;
            }
            break;
        case 5:                                                     //  重启
//            TaskStackCheck();
            Upgrade.bits.Flag = FALSE;            
            RebootRequest(); 
            Upgrade.Step = 0;
            while(1);           
//            break;
        case 6:
            break;
        default:
            Upgrade.Step = 0;
            break;
    }
}

extern void    FTPConnectRequestSet(void);
void    FtpInfoInit(char *pIp, char *pFile)
{
    char *p;
    
    memset((char *)&FtpInf, 0, sizeof(FtpInf));
    strcpy(FtpInf.Domain, pIp);
    strcpy(FtpInf.FileName, pFile);
    FtpInf.Port = 18421;
    strcpy(FtpInf.Usr, "xwl");
    strcpy(FtpInf.Pwd, "xwl001");
    strcpy(FtpInf.Path, "/");
    FtpInf.FileSize = 0;   
    p = strtok(pFile, "_");
    p = strtok(NULL, "_");
    p = strtok(NULL, ".");
    if(p) {
        FtpInf.FileCrc = StringToHex(p, 4);
        DebugMsg(DEBUG_UPGRADE, "File crc %8X\r\n", FtpInf.FileCrc );
        FTPConnectRequestSet();
    }
}


char    UpgradeVersionInit(char *pName)
{
    char *pVal = pName;
    char *pModel, *pVersion, *pCrc;
    char FileName[32];
    //  YT170-V1.00-8A1B4C93.bin
    
    memset(FileName, 0, sizeof(FileName));
    strcpy(FileName, pName);
    
    pModel = strtok(pVal, "_");                                          
    pVersion = strtok(NULL, "_");   
    pCrc = strtok(NULL, ".");
    if((NULL == pModel) || (NULL == pVersion) || (NULL == pCrc)) {
        return FALSE;
    }

    if(strcmp(pModel, PRODUCT_MODLE)) {                                 //  型号不匹配
        return FALSE;
    }
    
    if(0 == strcmp(pVersion, PRODUCT_VERSION)) {                        //  与现在的版本相同,不用升级
        DebugMsg(DEBUG_UPGRADE, "Version is same, update cancel\r\n");
        if(FtpInf.Bits.Ftping) {
            FtpInf.Bits.Cancel = TRUE;                              //  如果升级过程中,则取消升级
        }
        return 2;
    } else if(0 == strcmp(pVersion, FtpInf.FileName)) {             //  升级版本相同
        return TRUE;
    }

    memset((char *)&FtpInf, 0, sizeof(FtpInf));
    strcpy(FtpInf.FileName, FileName);
    FtpInf.FileCrc = StringToHex(pCrc, 4);

    return TRUE;
}

char    UpgradeSizeInit(char *pInf)
{
    FtpInf.FileSize = atoi(pInf);
    return TRUE;
}

char    UpgradeServerInit(char *pInf)
{
    char *pBuf;
    
    pBuf = strtok(pInf, ":");    
    if(NULL == pBuf) {
        return FALSE;
    }

    strcpy(FtpInf.Domain, pBuf);
    FtpInf.Port = atoi(pInf+strlen(FtpInf.Domain)+1);
    return TRUE;
}

char    UpgradeUsrInit(char *pInf)
{
    char *pBuf;
    
    pBuf = strtok(pInf, ":");    
    if(NULL == pBuf) {
        return FALSE;
    }

    strcpy(FtpInf.Usr, pBuf);
    strcpy(FtpInf.Pwd, pBuf+strlen(FtpInf.Usr)+1);
    
    return TRUE;
}





