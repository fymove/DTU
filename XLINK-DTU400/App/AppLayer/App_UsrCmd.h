#ifndef _APP_USR_CMD_H_
#define _APP_USR_CMD_H_

#ifndef _InUsrCmd
#define UsrCmdExt   extern
#else
#define UsrCmdExt
#endif

#include "uart.h"
#include "app_debug.h"

typedef struct {
    char Uart1: 1;
    char Uart2: 1;
    char Uart3: 1;
    char Uart5: 1;
}RCV_STRUCT;

UsrCmdExt RCV_STRUCT GbRcvData;

#define UART_TEST_BUF_SIZE      100
UsrCmdExt char    UartTestBuf[UART_TEST_BUF_SIZE];
UsrCmdExt short   UartBufLen;
UsrCmdExt char    GbRS485TstFlg;


/*
 *  串口命令
 *  *RK,SET,03,15-09-10 17:07:00#设置系统时间
 *  *RK,QUERY,00#查询所有参数
 *  *RK,CTRL,01,01#重启系统 
 *  *RK,TEST,01,01#开启RS485测试功能
 *  *RK,DEBUG,00,01#开启调试信息
 */
#define USR_CMD_SET         "SET"
typedef enum {
    CMD_SET_ID = 0x01,                                              //  设置终端ID          0x01
    CMD_SET_SERVER,                                                 //  设置服务器信息      0x02
    CMD_SET_TIME,                                                   //  校时                0x03
    CMD_SET_STMPADDR,                                               //  设置邮件地址        0x04
    CMD_SET_FTPINF,                                                 //  设置FTP信息         0x05
    CMD_SET_SMSALMEN,                                               //  设置短信报警开关    0x06
    CMD_SET_ALMTEL,                                                 //  设置报警电话号码    0x07
    CMD_SET_LOW_VOLT,                                               //  设置低压阀值        0x08
}CMD_SET_ENUM;


#define USR_CMD_QUERY       "QUERY"
typedef enum {
    CMD_QUERY_ALL = 0x00,                                           //  查询所有参数        0x00
    CMD_QUERY_ID,                                                   //  查询终端ID          0x01
    CMD_QUERY_SERVER,                                               //  查询服务器信息      0x02
    CMD_QUERY_TIME,                                                 //  查询时间            0x03
    CMD_QUERY_STMPADDR,                                             //  查询邮件地址        0x04
}CMD_QUERY_ENUM;


#define USR_CMD_CTRL        "CTRL"
typedef enum {
    CMD_CTRL_RESET = 0x01,                                          //  重启设备            0x01
    CMD_CTRL_UPDATE,
}CMD_CTRL_ENUM;


#define USR_CMD_TEST        "TEST"
typedef enum {
    CMD_TEST_RS485 = 0x01,                                          //  485端口测试         0x01
    CMD_TEST_DO,                                                    //  继电器输出测试      0x02
    CMD_TEST_EMAIL,                                                 //  发送邮件测试        0x03
    CMD_TEST_FTP,                                                   //  FTP文件发送测试     0x04
    CMD_TEST_YECX,                                                  //  余额查询            0x05
}CMD_TEST_ENUM;


#define USR_CMD_DEBUG       "DEBUG"
typedef enum {
    CMD_DEBUG_EN = 0x00,                                            //  开启调试信息        0x00
    CMD_DEBUG_STACK,                                                //  任务堆栈            0x01                            
    CMD_DEBUG_AT,                                                   //  AT指令              0x02
    CMD_DEBUG_GPRS_RX,                                              //  接收服务器数据      0x03
    CMD_DEBUG_GPRS_TX,                                              //  发送服务器数据      0x04
    CMD_DEBUG_SMS_RX,                                               //  短信接收数据        0x05
    CMD_DEBUG_SMS_TX,                                               //  短信发送数据        0x06
    CMD_DEBUG_EMAIL,                                                //  EMAIL发送数据       0x07
    CMD_DEBUG_FTP,                                                  //  FTP发送数据         0x08
    CMD_DEBUG_WDMST,                                                //  风速传感器数据      0x09
    CMD_DEBUG_ADC,                                                  //  ADC数据             0x0A
    CMD_DEBUG_VFD,                                                  //  变频器数据          0x0B
    CMD_DEBUG_HMI_MODBUS,
}CMD_DEBUG_ENUM;


UsrCmdExt   void    TaskUartUsrCmd(void);
UsrCmdExt   void    TaskRS485Test(void);
UsrCmdExt   char    UsrCmdParse(char *pRd, char *pRsp);
UsrCmdExt   char    SMSCmdParse(char *pRd, char *pRsp);



#endif
