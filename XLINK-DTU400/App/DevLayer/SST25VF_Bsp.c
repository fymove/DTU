#define _InSSTBSP
#include "sst25vf_bsp.h"
#include "stm32f10x_conf.h" 

#if USE_SST_FLASH_EN
#define Dummy_Byte      0xff

void    InitSPI_SSTFlash(void)
{
    SPI_InitTypeDef  SPI_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_SPI_SST_FLASH, ENABLE);

    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    
    /* Configure SPI1 pins: SCK, MISO and MOSI */    
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = SST25V_SCK_PIN | SST25V_MISO_PIN | SST25V_MOSI_PIN;
    GPIO_Init(SST25V_SCK_PORT, &GPIO_InitStructure);

    /* Configure I/O for Flash Chip select */    
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin  = SST25V_CS_PIN;
    GPIO_Init(SST25V_CS_PORT, &GPIO_InitStructure);

    /* Deselect the FLASH: Chip Select high */
    SST25V_CS_HIGH();

    /* SPI1 configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL      = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA      = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_InitStructure.SPI_FirstBit  = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI_SST_FLASH, &SPI_InitStructure);

    /* Enable SPI1  */
    SPI_Cmd(SPI_SST_FLASH, ENABLE);
}

char    SPI_Flash_SendByte(char byte)
{
    while(SPI_I2S_GetFlagStatus(SPI_SST_FLASH, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI_SST_FLASH, byte);   

    while(SPI_I2S_GetFlagStatus(SPI_SST_FLASH, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI_SST_FLASH);
}

char    SPI_Flash_ReceiveByte(void)
{
    return (SPI_Flash_SendByte(Dummy_Byte));
}
#endif

