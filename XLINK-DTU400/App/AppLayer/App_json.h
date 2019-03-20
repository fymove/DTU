#ifndef _APP_JSON_H_
#define _APP_JSON_H_

#ifndef _InJson
#define JSONExt extern
#else
#define JSONExt
#endif

#include "typedef.h"

typedef struct {
    bool Begin;
    char *pKey;
    char *pVal;
}JSON_NODE_STRUCT;
JSONExt JSON_NODE_STRUCT    JsonNode;

typedef  struct {
	char * ptype;    
	char * ptypeval;
	char *pbody;
	char *pmt;
	char *pmtval;
	char *pcb;
	char *pstatus;
	char *pstatusval;
}JSON_OBJNODE_STRUCT;
JSONExt JSON_OBJNODE_STRUCT   JsonObjNode;

#define MAX_HEART_ADDR_NUM  80
typedef struct {
    u8  Cnt;
    u16 List[MAX_HEART_ADDR_NUM];
}JSON_ADDR_LIST_STRUCT;
JSONExt JSON_ADDR_LIST_STRUCT   HeartAddrList;

typedef struct {
    u16 Cnt;
    u32 ValAddr[MAX_HEART_ADDR_NUM];
}JSON_ARRAY_STRUCT;
JSONExt JSON_ARRAY_STRUCT JsonArrayBuf;



JSONExt void    JSON_ObjectBegin(char *pBuf);
JSONExt void    JSON_ObjectEnd(char *pBuf);
JSONExt bool    JSON_IsObjectBegin(char **pBuf);
JSONExt bool    JSON_Extract(char **pBuf, JSON_NODE_STRUCT *pNode);
JSONExt void    JSON_AddrNumberDataToObject(char *pBuf, u16 Addr, u32 Data);
JSONExt void    JSON_AddrStringDataToObject(char *pBuf, u16 Addr, char *pStr);
JSONExt void    JSON_EventWithInfToObject(char *pBuf, u16 Addr, u16 AlmCode, char *pInf);
JSONExt void    JSON_EventNoInfToObject(char *pBuf, u16 Addr);
JSONExt void    JSON_StringValToObject(char *pBuf, char *pTitle, char *pString);
JSONExt bool    JSON_ArrayExtract(char **pBuf, char *pHeard, JSON_ARRAY_STRUCT *pList, u16 MaxArrayNum);
JSONExt bool    JSON_AddrListExtract(char **pBuf, JSON_ADDR_LIST_STRUCT *pList);
JSONExt void    JSON_NumberValToObject(char *pBuf, char *pTitle, u32 Data);
JSONExt bool    JSON_AddrAndDataToObject(char *pBuf, u16 Addr, u32 Data, char *pStr);
JSONExt void    JSON_KeyValToObject(char *pBuf, u32 Key, u32 Value);
JSONExt bool  JSON_MeterDataToObject(char *pBuf, u16 Addr, u32 Data, char *pStr);
JSONExt bool  JSON_FlowDataToObject(char *pBuf, u16 Addr, u32 Data, char *pStr);
JSONExt bool	JSON_ExtractObjNode(char **pBuf, JSON_OBJNODE_STRUCT * pObjNode);

#endif


