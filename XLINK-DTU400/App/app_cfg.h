/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2006; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                      APPLICATION CONFIGURATION
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210E-EVAL Evaluation Board
*
* Filename      : app_cfg.h
* Version       : V1.00
* Programmer(s) : BAN
*********************************************************************************************************
*/

#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__


/*
 *  DTU-K V0.2  20160328    
        1.485接口通信异常时记录异常时刻时间
        2.支持MAM680D(主机变频,风机工频,温度偏差20,能读取预警信息,能远程开关机)
    DTU-K V0.3  20160330
        1.修正无开机/停机事件上传的BUG
    DTU-K V0.4  20160408
        1.修正APN参数不能设置问题
        2.远程修改域名和端口后自动重连且重传终端所有参数
        3.远程修改APN参数后自动重连,不重传终端参数
        4.区分远程开/关机和按键开/关机
        5.增加版本日期,终端编号,GPRS位置区号,小区ID,普罗特报警值,预警值上传
        6.上电1h后终端进行余额查询
        7.将HMI失败次数作为485接口当前失败次数
    DTU-K V0.5  20160430
        1.修正串口配置软件不稳定的BUG     
    DTU-K V0.6  20170912
        1.新增对接鑫宇电表参数 
    DTU-K V0.7  20170918
        1.新增MAM-6090读参数
    DTU-K V0.8  20170919
        1.新增远程升级功能
    DTU-K V0.9  20170923
        1.新增MAM-6090写参数、事件处理
        2.GPRS网络时间读取
        3.优化心跳计时，优化部分代码，减少代码空间
        4.新增内部软件时钟处理
    DTU-K V1.0  20171024
        1.修改ID号的格式
        2.修改COM黄色指示灯，连接到服务器时闪烁
        3.修改外部看门狗喂狗
        
    DTU-K V1.01  20171104
        1.修改目标温度显示错误
        2.修改主机累计用电、  风机累计用电 工频主机累计用电  工频风机累计用电 显示错误
        3.修改前轴温度与后轴温度无效时，显示为0
        
    DTU-K V1.02  20171127
        1.修改GPRS信号值未定时上传。
        2.修改风机频率*10
        3.修改主机累计用电、风机累计用电、工频累计用电、工频风机累计用电的参数定位为u32。
        4.新增用户参数、保养参数、厂家参数上电后全部上传一遍，以及参数变化时附加到心跳包中上传。
        5.新增事件：设备加电、设备开机、设备停机、设备停止、加载运行、空载运行、空久休眠、风机启动、风机停止等事件。
        6.KEY值列表数组最大值60改为80.
        
    DTU-K V1.03  20171218    
        1.新增多基站功能。
        2.新增统一域名功能。
        3.新增变频器报警代码
        4.新增控制器写密码可修改
        
   DTU-K V1.04  20171222
        1.新增MAM860/870/880控制器类型
        2.新增MAM660/670/680控制器类型
        3.新增MAM100/200/260/280/300控制器类型
        4.风机累计用电缩小10倍

   DTU-K V2.01  20180119
        1.硬件版本升级到V2.0
        2.新增2路485驱动和CAN驱动
        3.新增流量计数据读取功能
        4.屏蔽风机启动与停止事件
        
	
	DTU-K V2.01  20180119
		1. 修复流量计参数解析错误问题
        
	DTU-K V2.02  2018-04-19
		
	1. 电能表 新增如下参数
	   CT(电流互感器变比) LINE_NET(接线方式 --3P3L/3P4L)
	   UAB UBC UCA；
	2. 上报的电流 改为一次侧电流（乘以了CT 即实际电流值）；
	3.上报的电压根据当前接线方式的不同，自动选择上传线电压还是相  电压；
	4. 电表默认站号修改为1， 流量计站号默认修改为15
	5. 修复电能溢出的问题
	6. 新增 RS485 通信状态指示 状态字
	   绿色指示灯 轮流指示 控制器、电表、流量计 通信状态
	
	DTU-K V2.03  2018-04-26
	
	1.新增设备串口通信状态变更 004
	2.新增电表流量计绑定 解绑消息


	DTU-K  V2.04 2018-04-27
	1. 新增历史运行时间分钟、历史负载时间分钟
	2. 心跳中去除参数变化上报，参数变化立即上传
	3. 提高参数上报优先级，使得其优先级高于事件上报
	4. 初始化参数只在注册成功后上报一次
	
	DTU-K  V2.05 2018-6-28 20:25:57
	1. 支持MAM860 -- 工频   MAM860C ---- 变频
	2. 调试模式下，默认读取电表流量计参数
	3. 新增 key 436 --- 整机电量
	4. 保养参数由之前的油滤器变化上报改为 所有变化上报
	5. 历史运行/加载时间由变化上报改为2min中内只上报一次
	6. Run运行指示灯恢复为之前的状态， 即只指示控制器485连接的状态


	DTU-K V2.06  2018-07-30 
	1. 新增永诺电表YN300-E 协议

	DTU-K  V2.07  2018-8-27
	1. 时间上报只有分钟变化才上报
	2. 修复DTU编号修改失败的Bug
	
	v2.10
	XLINK 使用外部晶振
	
	v2.11 
	1.修正电源电压超过上下限没有报警的问题
	2. DTU设备编号前缀依旧为 X18, XLINK设备编号前缀为XBD
	
	v2.12
	1. Spi Flash  驱动改为通用的SFUD驱动，支持更多的SPI flash芯片
	2. 电表协议更改为 安科瑞电表(之前为永诺电表),显示的总电量为电表的电量
	
	
*/
#define  XLINK    //如果硬件是xlink 则开启此宏

#define ID_HEADER_LEN   3    

#ifdef XLINK
#define PRODUCT_MODLE  "X-LINK-1"
#define APP_VERSION    "LNK_V2.12"             //  软件版本（平台显示）
#define ID_HEADER       "XBD"

#else
#define PRODUCT_MODLE   "X-DTU"                 //  产品型号
#define APP_VERSION     "DTU_V2.12"             //  软件版本（平台显示）
#define ID_HEADER       "X18"
 

#endif
#define PRODUCT_VERSION         "V2.12"                 //  远程升级软件版本 比较

#define PCB_VERSION             "DTU_V2.0"              //  硬件版本
#define SERVER_TYPE             1                         // 服务器平台类型：0未知，1葆德，2星物联，3封边机 （用于获取重定向服务器域名端口）


#define MAIN_VFD_NODE_ADDR      1                       //  主机变频器默认地址
#define FAN_VFD_NODE_ADDR       2                       //  风机变频器默认地址
#define VFD_READ_OPT_INTEVAL    50                      //  变频器读数据间隔
#define METER_READ_OPT_INTEVAL  500                     //  变频器读数据间隔


#define VFD_READ_RETRY_NUM      3                       //  变频器读操作重试次数
#define VFD_WRITE_RETRY_NUM     5                       //  变频器写操作重试次数


#define PRO_DATA_BIG_ENDIAN     1                       //  协议数据大端模式
#define PRO_NOT_USE_CRC         1                       //  不使用CRC,该字段为0

#define USE_RTC_EN              0                       //  使用RTC时间

#define PROTOCOL_USE_ONE_SNNO   1                       //  1:只使用协议头流水号,消息体中无流水号信息


#define RS485_SEND_DELAY        0                       //  RS485数据发送后延时切换为接收状态

#define USE_UART_DEBUG_INFO     1

#define  DEBUG_USE_STR          1              //   GPRS 发送的数据 按字符串打印
	
											     //  否则打印十六进制



/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/
#define CUSTOMER_BD
//#define CUSTOMER_XWL

#ifdef  CUSTOMER_BD

#define SERVER_DOMAIN   "bd.qhxwl.com"
#define SERVER_PORT     9003
#endif


#ifdef  CUSTOMER_XWL
#define SERVER_DOMAIN   "test.qhxwl.com"
//#define SERVER_DOMAIN   "xwl.test.qhxwl.com"
#define SERVER_PORT     9003

//#define SERVER_DOMAIN   "test.qhxwl.com"
//#define SERVER_PORT     9003
//#define SERVER_DOMAIN   "main.test.qhxwl.com"        // 统一代理服务器域名，用于获取重定向域名端口
//#define SERVER_PORT     9000
#endif

#define SST_UPDATE_ADDR         (4<<10)             // 升级起始地址: 4K
#define SSTFLASH_PAGE_SIZE      4096




/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/


#define TASK_SVRCOMM_EN  
#define TASK_VFDCOMM_EN
#define TASK_VFDDEAL_EN

    
#define TASK_START_PRIO                    1
#define TASK_VFDDEAL_PRIO               4
#define TASK_VFDCOMM_PRIO               5

#define TASK_PRODEAL_PRIO               6
#define TASK_SVRCOMM_PRIO                7
#define TASK_PROSEND_PRIO               8


//#define  OS_PROBE_TASK_PRIO              (OS_LOWEST_PRIO - 3)
#define  OS_TASK_TMR_PRIO                (OS_LOWEST_PRIO - 2)

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/


//#define TASK_START_STK_SIZE         120
//#define TASK_SVRCOMM_STK_SIZE       150
//#define TASK_PRODEAL_STK_SIZE       150
//#define TASK_PROSEND_STK_SIZE       100
//#define TASK_VFDCOMM_STK_SIZE       100
//#define TASK_VFDDEAL_STK_SIZE       100




#endif
