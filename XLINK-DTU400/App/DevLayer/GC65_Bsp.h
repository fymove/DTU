#ifndef _GPRS_GC65_BSP_H_
#define _GPRS_GC65_BSP_H_

#include "bsp.h"

#define    GPRS_PWRKEY_LOW()    GPIO_ResetBits(GPRS_PWRKEY_PORT, GPRS_PWRKEY_PIN)
#define    GPRS_PWRKEY_HIGH()    GPIO_SetBits(GPRS_PWRKEY_PORT, GPRS_PWRKEY_PIN)

#define    GPRS_POWER_ON()        GPIO_ResetBits(GPRS_POWER_PORT, GPRS_POWER_PIN)
#define    GPRS_POWER_OFF()    GPIO_SetBits(GPRS_POWER_PORT, GPRS_POWER_PIN)


#define GPRS_DISABLE_RECEIVE()    GPIO_SetBits(GPRS_RTS_PORT, GPRS_RTS_PIN)   
#define GPRS_ENABLE_RECEIVE()    GPIO_ResetBits(GPRS_RTS_PORT, GPRS_RTS_PIN) 

void    GprsUartCmd(char *pCmd, unsigned short Len);
void    GetGprsUartDMABuf(u8 **ppBuf);
void    GprsUartDMAReceive(u16 GetSize);
void    GPRSUartDMAInit(void);
void    GprsUART_SetDMAReceive(u8 *pSrc, u32 DesLen);
void    GprsDMAReceiveDisable(void);

#endif

