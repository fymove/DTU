#include "comm.h"
#include "struct.h"

/*
 *  小写字母转换成大写字母
 */
char    CharConvert(char dat)
{
    if((dat >= 'a') && (dat <= 'z')) {
        dat -= 32;
    }

    return dat;
}

char    stricmp(char *s1, char *s2)
{
    char char1;
    char char2;
    
    while(1) {
        char1 = CharConvert(*s1++);
        char2 = CharConvert(*s2++);

        if(char1 == char2) {
            if(0 == char1) {
                return 0;
            }
        } else {
            break;
        }
    }
    
    return(((unsigned char)char1 < (unsigned char)char2) ? -1 : +1);
}


char    memicmp(char *s1, char *s2, unsigned short Len)
{
    unsigned short i;
    char char1;
    char char2;

    for(i=0; i<Len; i++)
    {
        char1 = CharConvert(*s1++);
        char2 = CharConvert(*s2++);
        if(char1 != char2) {
            break;
        }
    }

    if(char1 == char2) {
        return 0;
    } 
    return(((unsigned char)char1 < (unsigned char)char2) ? -1 : +1);
}

char    StringiCmp(char *p1, char *p2)
{
    if(strlen(p1) != strlen(p2)) {
        return 1;                                                   //  不同返回1
    }

    return(memicmp(p1, p2, strlen(p1)));
}

char    IsNumber(char *p)
{
    if(NULL == *p) {                                                //  为空
        return FALSE;
    }

    while(*p) {
        if((*p < '0') || (*p > '9')) {
            return FALSE;
        }
        p++;
    }
    
    return TRUE;
}

char    IsID(char *p)
{
    if(NULL == *p) {                                                    //  为空
        return FALSE;
    }

    while(*p) {
        if(((*p >= '0')&&(*p <= '9')) || 
           ((*p >= 'A')&&(*p <= 'Z')) || 
           ((*p >= 'a')&&(*p <= 'z'))) {
            p++;
        } else {
            return FALSE;
        }
    }
    
    return TRUE;
}

char    IsIp(char *p)
{
    char bRet = FALSE;
    char ZoneCnt = 0;
    char i = 0;
    
    if((strlen(p) < 7) || (strlen(p) > 15)) {
        return bRet;
    }

    while(*p) {
        if((*p >= '0') && (*p <= '9')) {
            i++;
            p++;
        } else if('.' == *p) {
            if(0 == i) {
                ZoneCnt = 5;
                break;
            } else {
                ZoneCnt++;
                i = 0;
            }
            p++;
        } else {
            ZoneCnt = 5;
            i = 0;
            break;
        }
    }

    if((3 == ZoneCnt) && i) {
        bRet = TRUE;
    }   
        
    return bRet;
}


char    ASCIIToHex(char Data)
{
    char ret = 0;

    if((Data >= '0') && (Data <= '9')) {
        ret = Data - '0';
    } else if((Data >= 'a') && (Data <= 'f')) {
        ret = 10 + Data - 'a';
    } else if((Data >= 'A') && (Data <= 'F')) {
        ret = 10 + Data - 'A';
    } 
    
    return ret;
}

u32    StringToHex(char *pStr, char NByte)
{
    u32 uiTmpData = 0;
    
    switch(NByte) {
        case 1:
            uiTmpData = (ASCIIToHex(*pStr) << 4) | (ASCIIToHex(*(pStr+1)) << 0);
            break;
        case 2:
            uiTmpData = (ASCIIToHex(*pStr) << 12) | (ASCIIToHex(*(pStr+1)) << 8) | (ASCIIToHex(*(pStr+2)) << 4) | ASCIIToHex(*(pStr+3));
            break;
		case 4:
            uiTmpData = (ASCIIToHex(*pStr) << 28) | (ASCIIToHex(*(pStr+1)) << 24) | (ASCIIToHex(*(pStr+2)) << 20) | (ASCIIToHex(*(pStr+3)) << 16) |
						(ASCIIToHex(*(pStr+4)) << 12) | (ASCIIToHex(*(pStr+5)) << 8) | (ASCIIToHex(*(pStr+6)) << 4) | ASCIIToHex(*(pStr+7));
            break;
        default:
            break;
    }

    return uiTmpData;
}


/*
 *  提取指定字符串之后的数据
 */
char	*StrtokAfter(char *s, char *delim)
{
	short i;
	short Len = strlen(s);

	for(i=0; i<Len; i++) {
		if(!memcmp(&s[i], delim, strlen(delim))) {
			return &s[i+strlen(delim)];
		}		
	}

	return NULL;
}

/*
 *  提取指定字符串之前的数据
 */
char	*StrtokBefore(char *s, char *delim)
{
	short i;
	short Len = strlen(s);

	for(i=0; i<Len; i++) {
		if(!memcmp(&s[i], delim, strlen(delim))) {
			s[i] = 0;
			return s;
		}		
	}

	return NULL;
}




char    IsDigit(char dat)
{
    if((dat >= '0') && (dat <= '9'))
    {
        return TRUE;
    }

    return FALSE;
}


const u8 chCRCHTalbe[] =                                            //  CRC 高位字节值表
{
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
  0x00, 0xC1, 0x81, 0x40
};

const u8 chCRCLTalbe[] =                                            //  CRC 低位字节值表
{
  0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
  0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
  0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
  0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
  0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
  0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
  0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
  0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
  0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
  0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
  0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
  0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
  0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
  0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
  0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
  0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
  0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
  0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
  0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
  0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
  0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
  0x41, 0x81, 0x80, 0x40
};

u16     CRC16_1(char* pchMsg, u16 wDataLen)
{
    u8 chCRCHi = 0xFF;                                              //  高CRC字节初始化
    u8 chCRCLo = 0xFF;                                              //  低CRC字节初始化
    u16 wIndex;                                                     //  CRC循环中的索引

    while (wDataLen--) {
        wIndex = chCRCLo ^ *pchMsg++ ;
        chCRCLo = chCRCHi ^ chCRCHTalbe[wIndex]; 
        chCRCHi = chCRCLTalbe[wIndex] ;
    }

    return ((chCRCHi << 8) | chCRCLo) ;
}


char    WordToBuf(u16 inWord, char *pBuf)
{
#if PRO_DATA_BIG_ENDIAN
	*pBuf++ = (INT8U)((inWord & 0xFF00) >> 8);
	*pBuf   = (INT8U)(inWord & 0x00FF);
#else
	*pBuf++ = (INT8U)(inWord & 0x00FF);
	*pBuf   = (INT8U)((inWord & 0xff00) >> 8);
#endif
	return TRUE;
}

u16 NetTwoByteToWord(char *pBuf)
{
	u16 ret = 0;
#if PRO_DATA_BIG_ENDIAN
	ret = (*pBuf << 8) | (*(pBuf + 1));
#else
    ret = (*(pBuf+1) << 8) | (*pBuf);
#endif
	return ret;
}

u16 DevTwoByteToWord(char *pBuf)
{
    u16 ret = 0;
    ret = (*(pBuf+1) << 8) | (*pBuf);
    return ret;
}

u32 NetFourByteToDWord(char *pBuf)
{
	u32 ret = 0;
#if PRO_DATA_BIG_ENDIAN
	ret = (*pBuf << 24) | (*(pBuf+1) << 16) | (*(pBuf+2) << 8) | (*(pBuf+3));
#else
    ret = (*(pBuf+3) << 24) | (*(pBuf+2) << 16) | (*(pBuf+1) << 8) | (*pBuf);
#endif
	return ret;
}


u32 DevFourByteToDWord(char *pBuf)
{

	u32 ret = 0;
    ret = (*(pBuf+3) << 24) | (*(pBuf+2) << 16) | (*(pBuf+1) << 8) | (*pBuf);
	return ret;
}

 //LH LL  HH HL ----> HL HH LL LH  数据接收时交换的
//HL HH LL LH  ---->  HH HL LH LL  目标
u32 BufExchange(char *pBuf)
{
	u32 ret = 0;
    ret = (*(pBuf+1) << 24) | (*(pBuf) << 16) | (*(pBuf+3) << 8) | (*(pBuf+2));
	return ret;

}
 //LH LL  HH HL ---->  LL LH HL HH
////u32 DevFourByteToDWord(char *pBuf)
////{
////	
////	u32 ret = 0;
////    ret = (*(pBuf+1) << 24) | (*(pBuf) << 16) | (*(pBuf+3) << 8) | (*(pBuf+2));
////	return ret;
////}

/**
*  16进制转换为浮点数
*/
float Hex2Float(uint32_t * pdata)
{
	return  *((float *)pdata);	
}
u16 DevFourByteToU16(char *pBuf)
{
	u8 i, tmp;
	u16 ret = 0;
	for(i=0;i<4;i++)
	{
		tmp = *pBuf++;
		if(tmp >= '0' && tmp <= '9')
				tmp -= 0x30;
		else if(tmp >= 'a' && tmp <= 'f')
			tmp -= 0x57;
		else if(tmp >= 'A' && tmp <= 'F')
			tmp -= 0x37;
		
		ret <<= 4;   
		ret |=tmp;
	}
	
//    ret = (*(pBuf+3)-0x30) | ((*(pBuf+2)-0x30) << 4) | 
//			((*(pBuf+1)-0x30) << 8) | (((*pBuf)-0x30) << 12);
	return ret;
}


uint64_t DevEightByteToDWord(char *pBuf)
{
	uint64_t ret = 0;
	u8 i;
	
	for(i=0; i< 7 ; i++)
	{
		ret |= *(pBuf+7-i) ;
		ret <<= 8; 
	}
	ret |= *pBuf;
	
//    ret = (*(pBuf+7) << 56) | (*(pBuf+6) << 48) | (*(pBuf+5) << 40) | (*(pBuf+4)<<32) | 
//		  (*(pBuf+3) << 24) | (*(pBuf+2) << 16) | (*(pBuf+1) << 8) | (*pBuf);
	
	return ret;
}

char    DWordToBuf(u32 DWord, char *pBuf)
{
#if PRO_DATA_BIG_ENDIAN
    *pBuf++ = (char)(DWord >> 24);
	*pBuf++ = (char)(DWord >> 16);
	*pBuf++ = (char)(DWord >> 8);
	*pBuf++ = (char)(DWord >> 0);
#else
    *pBuf++ = (char)(DWord >> 0);
	*pBuf++ = (char)(DWord >> 8);
	*pBuf++ = (char)(DWord >> 16);
	*pBuf++ = (char)(DWord >> 24);
#endif
	return TRUE;
}


int my_atoi(char* pstr)  
{  
    int Ret_Integer = 0;  
    int Integer_sign = 1;  
      
    /* 
    * 判断指针是否为空 
    */  
    if(pstr == NULL)  
    {          
        return 0;  
    } 
    
      
    /* 
    * 判断正负号 
    * 如果是正号，指针指向下一个字符 
    * 如果是符号，把符号标记为Integer_sign置-1，然后再把指针指向下一个字符 
    */  
    if(*pstr == '-')  
    {  
        Integer_sign = -1;  
    }  
    if(*pstr == '-' || *pstr == '+')  
    {  
        pstr++;  
    }  
      
    /* 
    * 把数字字符串逐个转换成整数，并把最后转换好的整数赋给Ret_Integer 
    */  
    while(*pstr >= '0' && *pstr <= '9')  
    {  
        Ret_Integer = Ret_Integer * 10 + *pstr - '0';  
        pstr++;  
    }  
    Ret_Integer = Integer_sign * Ret_Integer;  
      
    return Ret_Integer;  
}  



int64_t my_atod(char* pstr)  
{  
    int64_t Ret_Integer = 0;  
    int64_t Integer_sign = 1;  
      
    /* 
    * 判断指针是否为空 
    */  
    if(pstr == NULL)  
    {          
        return 0;  
    } 
    
      
    /* 
    * 判断正负号 
    * 如果是正号，指针指向下一个字符 
    * 如果是符号，把符号标记为Integer_sign置-1，然后再把指针指向下一个字符 
    */  
    if(*pstr == '-')  
    {  
        Integer_sign = -1;  
    }  
    if(*pstr == '-' || *pstr == '+')  
    {  
        pstr++;  
    }  
      
    /* 
    * 把数字字符串逐个转换成整数，并把最后转换好的整数赋给Ret_Integer 
    */  
    while(*pstr >= '0' && *pstr <= '9')  
    {  
        Ret_Integer = Ret_Integer * 10 + *pstr - '0';  
        pstr++;  
    }  
    Ret_Integer = Integer_sign * Ret_Integer;  
      
    return Ret_Integer;  
}  


void my_itoa(char* pstr, u32 Data)  
{  
    u32 Tempt=1000000000;  
	u8 i,integer,S=0;
    /* 
    * 判断指针是否为空 
    */  
    if(pstr == NULL)  
    {          
        return ;  
    } 
	
    for(i = 0; i<10; i++)
	{
		integer = Data/Tempt;	
		if((integer)||(S ==1))
		{
			S = 1;
			*pstr++ = integer +0x30;  
		}
		Data %= Tempt;
		Tempt /= 10;
	}
      
    return ;  
}  


double my_atof(char* pstr)  
{  
    double Ret_tmp = 0; 
	float tmp = 10.0;
    u8 dec = 0;  
      
 
    //判断指针是否为空   
    if(pstr == NULL)  
    {          
        return 0;  
    } 
    
      
    while((*pstr >= '0' && *pstr <= '9') ||(*pstr == '.') )
    {  
    	if(*pstr == '.') 
		{
			dec = 1;
			pstr++; 
			continue;
		}
		
		if(dec)
		{
        	Ret_tmp = Ret_tmp + (float)(*pstr - '0')/tmp;  //具体赋值
        	tmp *= 10;      
		}
		else
		{
			Ret_tmp = Ret_tmp * 10 + *pstr - '0';  //具体赋值
		}
		pstr++;  
    }  

      
    return Ret_tmp;  
}  


