#ifndef _SST25VF_BSP_H_
#define _SST25VF_BSP_H_

#ifndef _InSSTBSP
#define SSTBSPExt   extern
#else
#define SSTBSPExt
#endif

#include "bsp.h"
#include "app_cfg.h"

#define SPI_SST_FLASH       SPI1
#define RCC_SPI_SST_FLASH   RCC_APB2Periph_SPI1

#define SST25V_CS_LOW()     GPIO_ResetBits(SST25V_CS_PORT, SST25V_CS_PIN)
#define SST25V_CS_HIGH()    GPIO_SetBits(SST25V_CS_PORT, SST25V_CS_PIN)

#define SST25V_WP_ENABLE()  GPIO_ResetBits(SST25V_WP_PORT, SST25V_WP_PIN)
#define SST25V_WP_DISABLE() GPIO_SetBits(SST25V_WP_PORT, SST25V_WP_PIN)


SSTBSPExt void    InitSPI_SSTFlash(void);
SSTBSPExt char    SPI_Flash_SendByte(char byte);
SSTBSPExt char    SPI_Flash_ReceiveByte(void);

#endif

