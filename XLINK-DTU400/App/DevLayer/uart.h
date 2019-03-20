#ifndef _UART_H_
#define _UART_H_

#ifndef  _InUart
#define UartExt extern
#else
#define UartExt    
#endif

#include "bsp.h"

#define UART_TEST_BUF_SIZE  100

typedef struct {
    char Flag:  1;
    char Timer: 7;
}UART_TIMER;

typedef union {
    char Flag;
    struct {
        char RS485_0: 1;
        char RS485_1: 1;
        char RS485_2: 1;
        char HMI:     1;
    }Bits;
}RCV_DATA_FALG;

typedef struct {
    char Flag;
    RCV_DATA_FALG Rcv;
    UART_TIMER Uart1;
//    UART_TIMER Uart2;
//    UART_TIMER Uart4;
//    UART_TIMER Uart5;
    short Len;
    char Buf[UART_TEST_BUF_SIZE+1]; 
}UART_TEST_STRUCT;

UartExt void    UartSendData(UART_COM_ENUM UartNum, char *pBuf, int Len);
UartExt void    UartIntSendData(UART_COM_ENUM UartNum, char *pBuf, short Len);

UartExt char DebugUartRcvStat;

UartExt UART_TEST_STRUCT    UartTest;
UartExt char    UartFirstChar(UART_TIMER *pUrtTim);
UartExt char    UartTimerOver(UART_TIMER *pUrtTim);

#endif

