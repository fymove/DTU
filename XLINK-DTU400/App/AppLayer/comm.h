#ifndef _COMM_H_
#define _COMM_H_

#include "string.h"
#include "typedef.h"

char    stricmp(char *s1, char *s2);
char    memicmp(char *s1, char *s2, unsigned short Len);
char    StringiCmp(char *p1, char *p2);
char    IsDigit(char dat);
char    IsNumber(char *p);
char    IsID(char *p);
char    IsIp(char *p);
//char    IsDomain(char *p);
char	*StrtokAfter(char *s, char *delim);
char	*StrtokBefore(char *s, char *delim);
char	*StrtokLastOneBefore(char *s, char *delim);
unsigned char  BcdToDec8U(unsigned char bcd);
char    XORCalc(char *pBuf, short Len);
char    BcdToHex(char bcd);
char    Dec8UToBcd(char dec);
u16     CRC16_1(char* pchMsg, u16 wDataLen);
char    WordToBuf(u16 inWord, char *pBuf);
u16     NetTwoByteToWord(char *pBuf);
u32     NetFourByteToDWord(char *pBuf);
char    DWordToBuf(u32 DWord, char *pBuf);
u32    StringToHex(char *pStr, char NByte);
void    WordChgToBigEnd(u16 Word, char *pBuf);
void    DwordChgToBigEnd(u32 Word, char *pBuf);
int my_atoi(char* pstr);
u32 DevFourByteToDWord(char *pBuf);
u16 DevTwoByteToWord(char *pBuf);
uint64_t DevEightByteToDWord(char *pBuf);
int64_t my_atod(char* pstr) ;
void my_itoa(char* pstr, u32 Data); 
double my_atof(char* pstr);
u16 DevFourByteToU16(char *pBuf);
float Hex2Float(uint32_t * pdata);
u32 BufExchange(char *pBuf);
#endif
