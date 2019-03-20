#ifndef _SST25VF_FLASH_H_
#define _SST25VF_FLASH_H_

#ifndef  _InSstFlash
#define SSTFlashExt extern
#else
#define SSTFlashExt    
#endif




SSTFlashExt void SST25V_Init(void);
SSTFlashExt void SST25V_BufferRead(unsigned int ReadAddr, char* pBuffer, unsigned short NumByteToRead);
SSTFlashExt void SST25V_HighSpeedBufferRead(unsigned int ReadAddr, char* pBuffer, unsigned short NumByteToRead);
SSTFlashExt char SST25V_HighSpeedRead(unsigned int ReadAddr);


SSTFlashExt void SST25V_BufferWrite(unsigned int WriteAddr, char* pBuffer, unsigned short NumByteToWrite);
SSTFlashExt void WriteBufToSst25vf016_Sector1(unsigned int WriteAddr, char* pBuffer, unsigned short NumByteToWrite);
SSTFlashExt void WriteBufToSst25vf016_Sector2(unsigned int WriteAddr, char* pBuffer, unsigned short NumByteToWrite);

SSTFlashExt void SST25V_SectorErase_4KByte(unsigned int Addr);
SSTFlashExt void SST25V_BlockErase_32KByte(unsigned int Addr);
SSTFlashExt void SST25V_BlockErase_64KByte(unsigned int Addr);
SSTFlashExt void SST25V_ChipErase(void);



void    SST25V_Test(void);



#endif

