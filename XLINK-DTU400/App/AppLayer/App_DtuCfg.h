#ifndef _APP_DTUCFG_H_
#define _APP_DTUCFG_H_

#ifndef _InDtuCfg
#define DTUCfgExt   extern
#else
#define DTUCfgExt
#endif

#include "struct.h"

#define    CFG_CMD_ENTER        0x01
#define    CFG_CMD_READ        0x02
#define    CFG_CMD_WRITE        0x03
#define    CFG_CMD_EXIT        0x04

#define    CFG_ADDR_NONE        0x0000
#define    CFG_ADDR_USR        0x0003
#define    CFG_ADDR_PWD        0x0004
#define    CFG_ADDR_APN        0x0013
#define    CFG_ADDR_DOMAIN        0x000C
#define    CFG_ADDR_IP            0x000D
#define    CFG_ADDR_PORT        0x000E
#define    CFG_ADDR_CNT_TYPE    0x000F
#define    CFG_ADDR_PROTOCOL    0x4006
#define    CFG_ADDR_ID            0x3002
#define    CFG_ADDR_SIM        0x3003
#define    CFG_ADDR_BINDSTATUS  0x3004
#define    CFG_ADDR_HEART        0x0011
#define    CFG_ADDR_TRANS_TYPE    0x8002
#define    CFG_ADDR_REG_TYPE    0x8004
#define    CFG_ADDR_REG_DATA    0x8005
#define    CFG_ADDR_HEAT_DATA    0x8006

#define    CFG_ADDR_SMS_NO0    0x8100
#define    CFG_ADDR_SMS_NO1    0x8101
#define    CFG_ADDR_SMS_NO2    0x8102
#define    CFG_ADDR_SMS_NO3    0x8103
#define    CFG_ADDR_SMS_NO4    0x8104
#define    CFG_ADDR_SMS_NO5    0x8105
#define    CFG_ADDR_SMS_NO6    0x8106
#define    CFG_ADDR_SMS_NO7    0x8107
#define    CFG_ADDR_SMS_PWD    0x8108
#define    CFG_ADDR_SMS_RCV    0x8109

#define    CFG_ADDR_BAND        0x8601
#define    CFG_ADDR_PARITY        0x8602
#define    CFG_ADDR_STOP        0x8603
#define    CFG_ADDR_BITS        0x8604

#define    CFG_DATA_HEAD_1        0xAA
#define    CFG_DATA_HEAD_2        0xAA
//#define    CFG_DATA_HEAD_1        0xEE
//#define    CFG_DATA_HEAD_2        0xEE
#define    CFG_DATA_END_1        0xBB
#define    CFG_DATA_END_2        0xCC
#define    CFG_DATA_END_3        0xDD

typedef enum {
    CONT_TYPE_IP = 0,
    CONT_TYPE_DOMAIN
}CONT_TYPE_ENUM;

//typedef enum {
//    PROTOCOL_UDP = 0,
//    PROTOCOL_TCP    
//}PROTOCOL_ENUM;    

typedef enum {
    REG_TYPE_DEFAULT = 0,
    REG_TYPE_USER
}RET_TYPE_ENUM;    

typedef enum {
    REG_FORM_HEX = 0,
    REG_FORM_ASCII    
}REG_FORM_ENUM;    


DTUCfgExt   char dtuTmpBuf[1024];
DTUCfgExt   char GbCfgCmd;
DTUCfgExt   char GbDtuEnterCfg;
DTUCfgExt   char    dtuFactoryConfig(char *p, short CfgLen);

#endif
