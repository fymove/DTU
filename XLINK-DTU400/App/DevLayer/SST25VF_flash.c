#define _InSstFlash
#include "sst25vf_bsp.h"
#include "sst25vf_flash.h"

#if USE_SST_FLASH_EN


#define Read_Data                     0x03       //¶ÁÈ¡´æ´¢Æ÷Êý¾Ý
#define HighSpeedReadData             0x0B       //¿ìËÙ¶ÁÈ¡´æ´¢Æ÷Êý¾Ý
#define SectorErace_4KB               0x20       //ÉÈÇø²Á³ý
#define BlockErace_32KB               0x52       //32KB¿é²Á³ý
#define BlockErace_64KB               0xD8       //64KB¿é²Á³ý
#define ChipErace                     0x60       //Æ¬²Á³ý

#define Byte_Program                  0x02       //Ò³Ãæ±à³Ì--Ð´Êý¾Ý
#define AAI_WordProgram               0xAD
#define ReadStatusRegister            0x05       //¶Á×´Ì¬¼Ä´æÆ÷
#define EnableWriteStatusRegister     0x50
#define WriteStatusRegister           0x01       //Ð´×´Ì¬¼Ä´æÆ÷

#define WriteEnable                   0x06       //Ð´Ê¹ÄÜ£¬ÉèÖÃ×´Ì¬¼Ä´æÆ÷
#define WriteDisable                  0x04       //Ð´½ûÖ¹
#define ReadDeviceID                  0xAB       //»ñÈ¡Éè±¸IDÐÅÏ¢

#define ReadJedec_ID                  0x9F       //JEDECµÄIDÐÅÏ¢

#define EBSY                          0X70
#define DBSY                          0X80

#define Dummy_Byte                      0xff


char    SST25V_ByteRead(unsigned int ReadAddr)
{
    char Temp = 0;
    SST25V_CS_LOW();
    SPI_Flash_SendByte(Read_Data);
    SPI_Flash_SendByte((ReadAddr & 0xFF0000) >> 16);
    SPI_Flash_SendByte((ReadAddr & 0xFF00) >> 8);
    SPI_Flash_SendByte(ReadAddr & 0xFF);

    Temp = SPI_Flash_ReceiveByte();
    SST25V_CS_HIGH();
    return Temp;
}

void    SST25V_BufferRead(unsigned int ReadAddr, char* pBuffer, unsigned short NumByteToRead)
{
    SST25V_CS_LOW();
    SPI_Flash_SendByte(Read_Data);
    SPI_Flash_SendByte((ReadAddr & 0xFF0000) >> 16);
    SPI_Flash_SendByte((ReadAddr & 0xFF00) >> 8);
    SPI_Flash_SendByte(ReadAddr & 0xFF);

    while(NumByteToRead--) {
        *pBuffer = SPI_Flash_ReceiveByte();
        pBuffer++;
    }
    SST25V_CS_HIGH();
}

void    SST25V_HighSpeedBufferRead(unsigned int ReadAddr, char* pBuffer, unsigned short NumByteToRead)
{
    SST25V_CS_LOW();
    SPI_Flash_SendByte(HighSpeedReadData);
    SPI_Flash_SendByte((ReadAddr & 0xFF0000) >> 16);
    SPI_Flash_SendByte((ReadAddr & 0xFF00) >> 8);
    SPI_Flash_SendByte(ReadAddr & 0xFF);
    SPI_Flash_SendByte(Dummy_Byte);

    while(NumByteToRead--) {
        *pBuffer = SPI_Flash_ReceiveByte();
        pBuffer++;
    }
    SST25V_CS_HIGH();
}

char    SST25V_HighSpeedRead(unsigned int ReadAddr)
{
    unsigned int Temp = 0;
    SST25V_CS_LOW();
    SPI_Flash_SendByte(HighSpeedReadData);
    SPI_Flash_SendByte((ReadAddr & 0xFF0000) >> 16);
    SPI_Flash_SendByte((ReadAddr & 0xFF00) >> 8);
    SPI_Flash_SendByte(ReadAddr & 0xFF);
    SPI_Flash_SendByte(Dummy_Byte);
    Temp = SPI_Flash_ReceiveByte();
    SST25V_CS_HIGH();
    return Temp;
}

void    SST25V_WriteEnable(void)
{
    SST25V_CS_LOW();
    SPI_Flash_SendByte(WriteEnable);
    SST25V_CS_HIGH();
}

void    SST25V_WriteDisable(void)
{
    SST25V_CS_LOW();
    SPI_Flash_SendByte(WriteDisable);     
    SST25V_CS_HIGH();
}

void    SST25V_WaitForWriteEnd(void)
{
    char FLASH_Status = 0;
    
    SST25V_CS_LOW();
    SPI_Flash_SendByte(ReadStatusRegister);
    do {
        FLASH_Status = SPI_Flash_SendByte(Dummy_Byte);
    }
    while((FLASH_Status & WriteStatusRegister) != 0);

    SST25V_CS_HIGH();
}

void    SST25V_ByteWrite(char Byte, unsigned int WriteAddr)
{
    SST25V_WriteEnable();
    SST25V_WP_DISABLE();
    SST25V_CS_LOW();    
    SPI_Flash_SendByte(Byte_Program);
    SPI_Flash_SendByte((WriteAddr & 0xFF0000) >> 16);
    SPI_Flash_SendByte((WriteAddr & 0xFF00) >> 8);
    SPI_Flash_SendByte(WriteAddr & 0xFF);
    SPI_Flash_SendByte(Byte);
    SST25V_CS_HIGH();    
    SST25V_WaitForWriteEnd();
    SST25V_WriteDisable();
    SST25V_WaitForWriteEnd();
    SST25V_WP_ENABLE();
}

char    SST25V_ReadStatusRegister(void)
{
    char StatusRegister = 0;
    SST25V_CS_LOW();
    SPI_Flash_SendByte(ReadStatusRegister);
    StatusRegister = SPI_Flash_ReceiveByte();
    SST25V_CS_HIGH();
    return StatusRegister;
}


void    SST25V_Wait_Busy_AAI(void)
{
    while(SST25V_ReadStatusRegister() == 0x43) {  /* µÈ´ý¿ÕÏÐ */    
        SST25V_ReadStatusRegister();
    }  
}

void    SST25V_BufferWrite(unsigned int WriteAddr, char* pBuffer, unsigned short NumByteToWrite)
{
    unsigned int i, length;
    length = NumByteToWrite;
    if(length % 2 != 0)length++; //²»×ãË«Êý²¹1

    SST25V_WriteEnable();
    SST25V_WP_DISABLE();
    SST25V_CS_LOW();    
    
    SPI_Flash_SendByte(AAI_WordProgram);

    SPI_Flash_SendByte((WriteAddr & 0xFF0000) >> 16);
    SPI_Flash_SendByte((WriteAddr & 0xFF00) >> 8);
    SPI_Flash_SendByte(WriteAddr & 0xFF);

    SPI_Flash_SendByte(pBuffer[0]);
    SPI_Flash_SendByte(pBuffer[1]);

    SST25V_CS_HIGH();   
    
    SST25V_Wait_Busy_AAI();
    
    for(i = 2; i < length; i += 2) {
        SST25V_CS_LOW();
        SPI_Flash_SendByte(AAI_WordProgram);
        SPI_Flash_SendByte(pBuffer[i]);
        SPI_Flash_SendByte(pBuffer[i + 1]);
        SST25V_CS_HIGH();
        SST25V_Wait_Busy_AAI();
    }
   
    SST25V_WriteDisable();
    SST25V_Wait_Busy_AAI();
    SST25V_WP_ENABLE();
}





// ÉÈÇø²Á³ý
void    SST25V_SectorErase_4KByte(unsigned int Addr)
{
    SST25V_WriteEnable();
    SST25V_WP_DISABLE();
    SST25V_CS_LOW();    
    SPI_Flash_SendByte(SectorErace_4KB);
    SPI_Flash_SendByte((Addr & 0xFF0000) >> 16);
    SPI_Flash_SendByte((Addr & 0xFF00) >> 8);
    SPI_Flash_SendByte(Addr & 0xFF);
    SST25V_CS_HIGH();
    SST25V_WaitForWriteEnd();
    SST25V_WriteDisable();
    SST25V_WaitForWriteEnd();
    SST25V_WP_ENABLE();
}

void    SST25V_BlockErase_32KByte(unsigned int Addr)
{
    SST25V_WriteEnable();
    SST25V_WP_DISABLE();
    SST25V_CS_LOW();    
    SPI_Flash_SendByte(BlockErace_32KB);
    SPI_Flash_SendByte((Addr & 0xFF0000) >> 16);
    SPI_Flash_SendByte((Addr & 0xFF00) >> 8);
    SPI_Flash_SendByte(Addr & 0xFF);
    SST25V_CS_HIGH();
    SST25V_WaitForWriteEnd();
    SST25V_WriteDisable();
    SST25V_WaitForWriteEnd();
    SST25V_WP_ENABLE();
}

void    SST25V_BlockErase_64KByte(unsigned int Addr)
{
    SST25V_WriteEnable();
    SST25V_WP_DISABLE();
    SST25V_CS_LOW();
    SPI_Flash_SendByte(BlockErace_64KB);
    SPI_Flash_SendByte((Addr & 0xFF0000) >> 16);
    SPI_Flash_SendByte((Addr & 0xFF00) >> 8);
    SPI_Flash_SendByte(Addr & 0xFF);
    SST25V_CS_HIGH();
    SST25V_WaitForWriteEnd();
    SST25V_WriteDisable();
    SST25V_WaitForWriteEnd();
    SST25V_WP_ENABLE();
}

void    SST25V_ChipErase(void)
{
    SST25V_WriteEnable();
    SST25V_WP_DISABLE();
    SST25V_CS_LOW();
    SPI_Flash_SendByte(ChipErace);
    SST25V_CS_HIGH();
    SST25V_WaitForWriteEnd();
    SST25V_WriteDisable();
    SST25V_WaitForWriteEnd();
    SST25V_WP_ENABLE();
}




void    SST25V_EnableWriteStatusRegister(void)
{
    SST25V_CS_LOW();
    SPI_Flash_SendByte(EnableWriteStatusRegister);
    SST25V_CS_HIGH();
}

void    SST25V_WriteStatusRegister(char Byte)
{
    SST25V_EnableWriteStatusRegister();
    SST25V_CS_LOW();
    SPI_Flash_SendByte(WriteStatusRegister);
    SPI_Flash_SendByte(Byte);
    SST25V_CS_HIGH();
}



void    SST25V_EBSY(void)
{
    SST25V_CS_LOW();
    SPI_Flash_SendByte(EBSY);
    SST25V_CS_HIGH();
}

void    SST25V_DBSY(void)
{
    SST25V_CS_LOW();
    SPI_Flash_SendByte(DBSY);
    SST25V_CS_HIGH();
}


void    SST25V_ReadID(char *pID)
{
    char    i;

    SST25V_CS_LOW();
    SPI_Flash_SendByte(ReadJedec_ID);
    for(i=0; i<3; i++) {
        pID[i] = SPI_Flash_ReceiveByte();
    }   
    SST25V_CS_HIGH();   
}

//Ð´µÚÒ»ÉÈÇøÊý¾Ý
void    WriteBufToSst25vf016_Sector1(unsigned int WriteAddr, char* pBuffer, unsigned short NumByteToWrite)
{ 
    SST25V_SectorErase_4KByte(WriteAddr);
    SST25V_BufferWrite(WriteAddr, pBuffer, NumByteToWrite);   
}

void    SST25V_Init(void)
{      
    InitSPI_SSTFlash();
    SST25V_EnableWriteStatusRegister();      //Ê¹ÄÜÐ´×´Ì¬¼Ä´æÆ÷
    SST25V_WriteStatusRegister(0);             //Ð´×´Ì¬¼Ä´æÆ÷  ÉèÖÃ   BPL BP3 BP2 BP1 BP0  0 0 0 0 0
    SST25V_DBSY();
}


#if 0
#include "app_debug.h"
void    SST25V_Test(void)
{
    char FlashID[3];
    char DataBuf[50];
    short i;
    
//    SST25V_Init();    
    DebugMsg("flash init\r\n");
    SST25V_ReadID(FlashID);
    DebugMsg("Flash ID is %02X %02X %02X\r\n", FlashID[0], FlashID[1], FlashID[2]);
    
    memset(DataBuf, 0x00, sizeof(DataBuf));
    SST25V_BufferRead(0, DataBuf, sizeof(DataBuf));
    for(i=0; i<sizeof(DataBuf); i++) {
        if(0x36 != DataBuf[i]) {
            break;
        }
    }
    if(i < sizeof(DataBuf)) {
        DebugMsg("Flash data error\r\n");
        SST25V_SectorErase_4KByte(0);
        memset(DataBuf, 0x36, sizeof(DataBuf));
        SST25V_BufferWrite(0, DataBuf, sizeof(DataBuf));
    } else {
        DebugMsg("Flash data ok\r\n");
    }
}
#endif

#endif

