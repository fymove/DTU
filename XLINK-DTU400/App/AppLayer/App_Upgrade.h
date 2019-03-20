#ifndef _APP_UPGRADE_H_
#define _APP_UPGRADE_H_

#include "typedef.h"
//#include <stdint.h>

#ifndef _InUpgrade
#define UpgradeExt  extern
#else
#define UpgradeExt  
#endif

typedef struct {
    struct {
        u8  Flag: 1;                                                //  升级标识
        u8  LowAddr: 1;                                             //  应用程序地址空间
    }bits;
    u8  Step;
    u32 BeginAddr;
}UPGRADE_INFO_STRUCT;

UpgradeExt  UPGRADE_INFO_STRUCT  Upgrade;    
//UpgradeExt u32     AppOffset;
UpgradeExt void    UpgradeInit(void);
UpgradeExt void    UpgradeTask(void);
UpgradeExt void    UpgradeFlagSet(void);
UpgradeExt void    UpgradeCancel(void);
char    UpgradeSizeInit(char *pInf);
char    UpgradeServerInit(char *pInf);
char    UpgradeUsrInit(char *pInf);
char    UpgradeVersionInit(char *pName);
void    RebootRequest(void);
char    GetRebootFlag(void);
void    FtpInfoInit(char *pIp, char *pFile);
#endif

