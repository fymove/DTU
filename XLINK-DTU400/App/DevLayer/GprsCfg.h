#ifndef _GPRS_CFG_H_
#define    _GPRS_CFG_H_

#define GPRS_FTP_EN         1

#define GPRS_DATA_EN        1                                       //  GPRS数据收发使能

#define GPRS_CSQ_EN         1                                       //  是否自动检测CSQ
#define CSQ_CHECK_INTERVAL  10000                                   //  CSQ检测间隔,单位ms
#define GPRS_LOC_EN         1

#define    MDL_AT_RESP_LEN        300//50                                      //  模块AT命令应答最大长度
#define AT_RESP_Q_SIZE      3  

#define MAX_GPRS_BUF_SIZE   1024
#define SIM_NO_LEN          15

#if GPRS_DATA_EN
#define GPRS_RCV_Q_SIZE     2
#define GPRS_SND_Q_SIZE     2
#define URGEN_SND_Q_SIZE    0
#endif


#define    MDL_AT_SEND_LEN        50
#define AT_SEND_Q_SIZE      3

#define    PIPE_LEN_INFO_SIZE    2

//#define    GPRS_SEND_DATA_LEN    800
#define    GPRS_SEND_DATA_LEN    1280
#define GPRS_SND_PIPE_CNT   1

#define    GPRS_RECV_DATA_LEN   800
#define    GPRS_RCV_PIPE_CNT   1


#define GPRS_SND_PIPE_SIZ   (PIPE_LEN_INFO_SIZE+GPRS_SEND_DATA_LEN)

#define GPRS_RCV_PIPE_SIZ   (PIPE_LEN_INFO_SIZE+GPRS_RECV_DATA_LEN)


#define    MDL_AT_RESP_LEN        300//50
#define    AT_RESP_PIPE_CNT    3                                           //  2??üéùóú3??
#define    AT_RESP_PIPE_SIZ    (PIPE_LEN_INFO_SIZE+MDL_AT_RESP_LEN)


#define    AT_SEND_DATA_LEN    50
#define    AT_SEND_PIPE_CNT    1
#define    AT_SEND_PIPE_SIZ    (PIPE_LEN_INFO_SIZE+AT_SEND_DATA_LEN)


#endif

