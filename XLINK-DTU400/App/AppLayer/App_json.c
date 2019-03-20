#define _InJson
#include "App_json.h"
#include "includes.h"
#include "struct.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
//#include "comm.h"
extern SYS_MONITOR_DATA_STRUCT Plt_Mam6080_DataList[PLT_DATA_LIST_MAX];
extern SYS_MONITOR_DATA_STRUCT Xy_DataList[XY_DATA_LIST_MAX];
extern SYS_MONITOR_DATA_STRUCT Plt_Mam860_DataList[PLT_Mam860_DATA_LIST_MAX];
extern const SYS_MONITOR_DATA_STRUCT H2U_PLC_DataList[H2U_PLC_LIST_MAX];


void    JSON_ObjectBegin(char *pBuf)
{
    strcpy(pBuf, "{");
}

void    JSON_ObjectEnd(char *pBuf)
{
    u16 Len = strlen(pBuf);

    if(1 == Len) {                                                  //  无数据
        Len++;
    }

    if('}' != pBuf[Len-1]) {
        pBuf[Len-1] = '}';
        pBuf[Len] = 0;
    }
}

void    JSON_AddrStringDataToObject(char *pBuf, u16 Addr, char *pStr)
{
    sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%s\",", Addr, pStr);
}

void    JSON_AddrNumberDataToObject(char *pBuf, u16 Addr, u32 Data)
{
    if((2 == Addr) || ((Addr >= 166) && (Addr <= 177))) {               //  温度,位置区号,小区ID                                             //  小区ID
//       sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%04X\",", Addr, Data);
		 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
    } else if((300 == Addr) || (302 == Addr)) {                     //  报警值,预警值  
        sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%04X\",", Addr, Data);   //  一体机8字节
    } else {
        sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%ld\",", Addr, Data);
    }
}



bool  JSON_AddrAndDataToObject(char *pBuf, u16 Addr, u32 Data, char *pStr)
{
//    u8  Xiaoshu_Len = 0;
    double data_fp = 0.0;
//	s16   data_fushu = 0;	
//    bool  fushu_flag;
	u16 i;

	const SYS_MONITOR_DATA_STRUCT * ptmp;

	u16  listmax;
	switch (GpSysPara->Dev.Bits.PS)
	{
		case PS_MAM860_870_880:
		case PS_MAM860C_880C:
			ptmp  = Plt_Mam860_DataList;
			listmax = PLT_Mam860_DATA_LIST_MAX;
		break;
		case PS_MAM6080_6090:
		case PS_MAM6070:
		case PS_MAM6090:
			ptmp = Plt_Mam6080_DataList;
			listmax = PLT_DATA_LIST_MAX;
		break;
		case PS_HC:
			ptmp = H2U_PLC_DataList;
			listmax  = H2U_PLC_LIST_MAX;
			break;
		default:
			break;
	}


	for(i = 0; i < listmax; i++)
	{
		if(ptmp[i].Key_Value == Addr)
		{		
			switch(ptmp[i].DataType) 
			{
				case Str:   
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%s\",", Addr, pStr);
					 break; 

				case Int:      
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;	
					 
				case Flo:   								 
					 if(ptmp[i].DecNum==Dec1) 
					 {
						data_fp = (float)Data / 10.0;
						sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.1f\",", Addr, data_fp);
					 } 
					 else if(ptmp[i].DecNum==Dec2) 
					 {
						data_fp = (float)Data / 100.0;
						sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.2f\",", Addr, data_fp);
					 } 
					 else if(ptmp[i].DecNum==Dec3) 
					 {
						data_fp = (float)Data / 1000.0;
						sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.3f\",", Addr, data_fp);
					 } 
					 else if(ptmp[i].DecNum==Dec4) 
					 {
						data_fp = (float)Data / 10000.0;
						sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.4f\",", Addr, data_fp);
					 }
					 else 
					 {					
					 }
					 break;
				case Hex:      
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;	
				case Bit:      
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;	
				default:
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;
			}
			
			return TRUE;
		}
	}
	return  FALSE;
}

bool  JSON_FlowDataToObject(char *pBuf, u16 Addr, u32 Data, char *pStr)
{

    float data_fp = 0.0;
	u16 i;

	
	for(i = 0; i < XY_DATA_LIST_MAX; i++)
	{
		if(Xy_DataList[i].Key_Value == Addr)
		{	
			switch(Xy_DataList[i].DataType) 
			{
				case Str:   
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%s\",", Addr, pStr);
					 break; 

				case Int:      
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;	
					 
				case Flo: 
					data_fp =Hex2Float(&Data);			
					 if(Xy_DataList[i].DecNum==Dec1) 
					 {
						//data_fp = (float)Data / 10.0;
						sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.1f\",", Addr, data_fp);
					 } 
					 else if(Xy_DataList[i].DecNum==Dec2) 
					 {
						//data_fp = (float)Data / 100.0;
						sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.2f\",", Addr, data_fp);
					 } 
					 else if(Xy_DataList[i].DecNum==Dec3) 
					 {
						//data_fp = (float)Data / 1000.0;
						sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.3f\",", Addr, data_fp);
					 } 
					 else if(Xy_DataList[i].DecNum==Dec4) 
					 {
						//data_fp = (float)Data / 10000.0;
						sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.4f\",", Addr, data_fp);
					 }
					 else 
					 {					
					 }
					 break;
				case Hex:      
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;	
				case Bit:      
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;	
				default:
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;
			}
			
			return TRUE;
		}
	}
	
	
	
	return  FALSE;

}

bool  JSON_MeterDataToObject(char *pBuf, u16 Addr, u32 Data, char *pStr)
{

    double data_fp = 0.0;
	u16 factor = GpSysStat->MeterData.CT;
	u16 i;

	
	for(i = 0; i < XY_DATA_LIST_MAX; i++)
	{
		if(Xy_DataList[i].Key_Value == Addr)
		{	
			switch(Xy_DataList[i].DataType) 
			{
				case Str:   
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%s\",", Addr, pStr);
					 break; 

				case Int:      
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;	
					 
				case Flo: 
							//data_fp =Hex2Float(&Data);			
					 if(Xy_DataList[i].DecNum==Dec1) 
					 {
						
						data_fp = (float)Data/10.0;
						sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.1f\",", Addr, data_fp);
					 } 
					 else if(Xy_DataList[i].DecNum==Dec2) 
					 {
						 if (Addr>=403 && Addr<=405 )   //电流  要乘以CT ,保留一位小数
						 {
							 data_fp = (float)Data*factor / 100.0 ;   // 一次侧电流  = CT * 二次侧电流
							 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.1f\",", Addr, data_fp);   // 电流只显示一位小数
						 }
						 else if (Addr == 411) //电能
						 {
							 data_fp = (float)Data *factor / 100.0 ;  // 一次侧电能
							  sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.2f\",", Addr, data_fp);  
						 }
						 else
						 {
							 data_fp = (float)Data / 100.0;
							 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%.2f\",", Addr, data_fp);
						 }

					 }
					 else if(Xy_DataList[i].DecNum == Dec3)
					 {
					 	/* 功率 功率因素 补码形式存储，需要转换*/

						
					 	char sign = ' ';
					 	if (Addr != 409)  // 功率
					 	{
					 	
					 		if (Data & (1ul<<31)) // 负数
					 		{
					 			Data = 0xffffffff+1 - Data;
					 			sign = '-';
					 		}
					 		
					 		data_fp = (float)Data*factor / 1000.0 ; 
		
							sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%c%.2f\",", Addr, sign, data_fp);
					 	}
					 	else   // 功率因素
					 	{

					 		if (Data & (1ul<<15))
					 		{

					 			Data = 0xffff + 1 - Data;
					 			sign = '-';
					 		}
					 		data_fp = (float)Data/ 1000.0 ; 
							sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%c%.2f\",", Addr, sign, data_fp);
					 	}
					 }
			
					 else 
					 {					
					 }
					 break;
				case Hex:      
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;	
				case Bit:      
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;	
				default:
					 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;
			}
			
			return TRUE;
		}
	}
	
	
	
	return  FALSE;

}


void    JSON_EventNoInfToObject(char *pBuf, u16 Addr)
{
    sprintf(&pBuf[strlen(pBuf)], "\"%d\":{},", Addr);
}

void    JSON_EventWithInfToObject(char *pBuf, u16 Addr, u16 AlmCode, char *pInf)
{
    if(NULL == pInf) {                                              //  无报警附加信息
        sprintf(&pBuf[strlen(pBuf)], "\"%d\":{\"%d\":\"\"},", Addr, AlmCode);
    } else {                                                        //  有报警附加信息
        if(0xffff == AlmCode) {                                     //  无报警代码
            sprintf(&pBuf[strlen(pBuf)], "\"%d\":{\"\":\"%s\"},", Addr, pInf);  
        } else {                                                    //  有报警代码
            sprintf(&pBuf[strlen(pBuf)], "\"%d\":{\"%d\":\"%s\"},", Addr, AlmCode, pInf);
        }
    }    
}

void    JSON_NumberValToObject(char *pBuf, char *pTitle, u32 Data)
{
    sprintf(&pBuf[strlen(pBuf)], "\"%s\":\"%d\",", pTitle, Data);
}


void    JSON_StringValToObject(char *pBuf, char *pTitle, char *pString)
{
    sprintf(&pBuf[strlen(pBuf)], "\"%s\":\"%s\",", pTitle, pString);
}

void    JSON_ExtractInit(JSON_NODE_STRUCT *pNode)
{
    pNode->Begin = FALSE;
}

bool    JSON_Extract(char **pBuf, JSON_NODE_STRUCT *pNode)
{
    char *p = *pBuf;
    char *pTmp = *pBuf;
    bool bRet = FALSE;
    bool bFindFlg = FALSE;

    bFindFlg = FALSE;
    while(*p) {
        if((',' == *p) || ('}' == *p)) { 
            bFindFlg = TRUE;
            *p = 0;
            break;
        }  
        p++;
    }

    if(!bFindFlg) {
        return bRet;
    }

    p = pTmp;
    
    if('\"' != *p++) {
        return bRet;
    }

    pNode->pKey = p;

    bFindFlg = FALSE;
    while(*p) { 
        if('\"' == *p) {
            *p++ = 0;
            bFindFlg = TRUE;           
            break;
        }
        p++;
    }  

    if(!bFindFlg) {       
        return bRet;
    }
    
    if(':' != *p++) {
        return bRet;   
    }

    if('\"' != *p++) {
        return bRet;
    }

    pNode->pVal = p;

    bFindFlg = FALSE;
    while(*p) { 
        if('\"' == *p) {
            bFindFlg = TRUE;
           *p++ = 0;
            break;
        }
        p++;
    }

    if(bFindFlg) {
        bRet = TRUE;
        *pBuf = p + 1;        
    }

    return bRet;    
}

bool    JSON_IsObjectBegin(char **pBuf)
{
    char *p = *pBuf;

    if('{' == *p) {                                                 //  JSON头
        if('}' == p[strlen(p)-1]) {                                  //  JSON尾
            *pBuf = p + 1;            
            return TRUE;
        }
    }

    return FALSE;
}

bool    JSON_ArrayExtract(char **pBuf, char *pKey, JSON_ARRAY_STRUCT *pList, u16 MaxArrayNum)
{
    char *p = *pBuf;
    char *pTmp = *pBuf;
    bool bRet = FALSE;
    bool bFindFlg = FALSE;
    char *pAddr;
    bool bEnd = FALSE;
    u8 KeyLen = strlen(pKey);

    if(('\"' != p[0]) || ('\"' != p[KeyLen+1]) || (':' != p[KeyLen+2])) {
        return bRet;
    }
    if(strncmp(p+1, pKey, KeyLen)) {
        return bRet;
    }
    p += strlen(pKey) + 3;
    

    if('[' != *p++) {
        return bRet;
    }

    pTmp = p;
    bFindFlg = FALSE;
    while(*p) {
        if((']' == *p)) { 
            bFindFlg = TRUE;
            *p = 0;
            break;
        }  
        p++;
    }

    if(!bFindFlg) {
        return bRet;
    }

    p = pTmp;

    while(*p) {
        bRet = FALSE;
        
        if('\"' != *p++) {            
            break;
        }

        pAddr = p;          

        bFindFlg = FALSE;
        while(*p && ('\"' != *p)) {     
            p++;
        }  
        
        if('\"' == *p) {
            *p++ = 0;
        } else {
            break;
        }

        if('\0' == *p) {
            bEnd = TRUE;
        } else if(',' != *p) {
            break;
        }
        *p = 0;

        pList->ValAddr[pList->Cnt++] = (u32)pAddr;
        bRet = TRUE;   
        if(bEnd) {
            *pBuf = p + 2;
            break;
        }
            
        if(pList->Cnt >= MaxArrayNum) {
            break;
        }
        p++;
    }       

    return bRet;    
}

bool    JSON_AddrListExtract(char **pBuf, JSON_ADDR_LIST_STRUCT *pAddrList)
{
    u16 i;
    JSON_ARRAY_STRUCT *pArray = &JsonArrayBuf;
    char TmpBuf[10];

    pArray->Cnt = 0;
    if(JSON_ArrayExtract(pBuf, "AL", pArray, MAX_HEART_ADDR_NUM)) {
        for(i=0; i<pArray->Cnt; i++) {
            strcpy(TmpBuf, (char *)pArray->ValAddr[i]);
            pAddrList->List[i] = my_atoi(TmpBuf);
        }
        pAddrList->Cnt = pArray->Cnt;
        return TRUE;
    }

    return FALSE;
}

bool	JSON_ExtractObjNode(char **pBuf, JSON_OBJNODE_STRUCT * pObjNode)
{
	char *p ;
   
    bool bRet = FALSE;
    bool bFindFlg = FALSE;
	JSON_NODE_STRUCT Node;
    bFindFlg = FALSE;

	JSON_Extract(pBuf, &Node);
	p = *pBuf;

	pObjNode->ptype = Node.pKey;
	pObjNode->ptypeval = Node.pVal;

	if ('\"' != *p++)
		return bRet;
	pObjNode->pbody = p;
	
	bFindFlg = FALSE;
    while(*p) { 
        if('\"' == *p) {
            *p++ = 0;
            bFindFlg = TRUE;           
            break;
        }
        p++;
    }  
	
	if(!bFindFlg) { 	  
		  return bRet;
	  }
	if (':' != *p++)
	{
		return bRet;
	}
	if ('{' !=  *p++)
	{
		return  bRet;
	}

	if ('\"' != *p++)
	{
		return bRet;
	}
	pObjNode->pmt = p;

	
	bFindFlg = FALSE;
    while(*p) { 
        if('\"' == *p) {
            *p++ = 0;
            bFindFlg = TRUE;           
            break;
        }
        p++;
    }  
	
	if(!bFindFlg) { 	  
		  return bRet;
	  }

	if (':' != *p++){
			return bRet;
		}
	if ('\"' != *p++){
			return bRet;
		}
	pObjNode->pmtval  = p;
	
	bFindFlg = FALSE;
    while(*p) { 
        if('\"' == *p) {
            *p++ = 0;
            bFindFlg = TRUE;           
            break;
        }
        p++;
    }  
	
	if(!bFindFlg) { 	  
		  return bRet;
	  }	

	if (',' != *p || '\"' != *(p+1) ){
			return bRet;
		}

	p += 2;
	pObjNode->pcb = p;

	bFindFlg = FALSE;
    while(*p) { 
        if('\"' == *p) {
            *p++ = 0;
            bFindFlg = TRUE;           
            break;
        }
        p++;
    }  
	
	if(!bFindFlg) { 	  
		  return bRet;
	  }	
	
	  if (':' != *p++)
	  {
		  return bRet;
	  }
	
	if ('{' !=	*p++)
		{
			return	bRet;
		}
	
		if ('\"' != *p++)
		{
			return bRet;
		}
		pObjNode->pstatus = p;
	
		
		bFindFlg = FALSE;
		while(*p) { 
			if('\"' == *p) {
				*p++ = 0;
				bFindFlg = TRUE;		   
				break;
			}
			p++;
		}  
		
		if(!bFindFlg) { 	  
			  return bRet;
		  }
	
		if (':' != *p++){
				return bRet;
			}
		if ('\"' != *p++){
				return bRet;
			}
		pObjNode->pstatusval  = p;
		
		bFindFlg = FALSE;
		while(*p) { 
			if('\"' == *p) {
				*p++ = 0;
				bFindFlg = TRUE;		   
				break;
			}
			p++;
		}  
		
		if(!bFindFlg) { 	  
			  return bRet;
		  } 
		
	    if(bFindFlg) {
	        bRet = TRUE;
	        *pBuf = p + 1;        
	    }

	    return bRet;    
			
}




