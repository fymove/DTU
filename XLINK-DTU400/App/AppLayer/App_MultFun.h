#ifndef _MULT_FUN_H_
#define _MULT_FUN_H_


#ifndef _InMult
#define MultExt  extern
#else
#define MultExt  
#endif

#include "struct.h"

typedef struct {
    struct {
        u32 Flag: 1;                                                //  计时标识
        u32 Hour: 7;                                                //  小时计数
        u32 Min:  6;                                                //  分钟计数
        u32 Sec:  6;                                                //  秒计数
    }Cnt;

    struct {
        u32 CSQ1: 5;                                                //  GPRS错误时的信号
        u32 CSQ2: 5;
        u32 CSQ3: 5;
        u32 ErrCode1: 4;                                            //  GPRS错误码1
        u32 ErrCode2: 4;                                            //  GPRS错误码2
        u32 ErrCode3: 4;                                            //  GPRS错误码3
    }Info;
}BEFORE_REG_INFO;

MultExt BEFORE_REG_INFO BeforeReg;
MultExt BEFORE_REG_INFO RS485ErrTime;
MultExt u32 MoneyCheckTimer;

MultExt DELAY_TIMER RmtBootTimer;
MultExt DELAY_TIMER RmtStopTimer;
MultExt DELAY_TIMER CfgDelay;
MultExt DELAY_TIMER AlmDealDelay;   

MultExt void    RegTimerStop(void);
MultExt void    RegTimerErrCode(void);
MultExt void    MultFunInit(void);
MultExt void    Task_MultFun_1s(void);

#endif

