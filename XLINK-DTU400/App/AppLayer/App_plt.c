#define _InPlt
#include "app_plt.h"
#include "app_para.h"
#include "includes.h"


//key,  addr,  DataLen（数据长度）
//datatype（数据类泻0整数，1：字符串，2：浮点类型，3:16进制显示，4：多状态位 ,
//DecNum  （小数点位数DataType=2时，小数点位数，0、1、2、3、4）
//WriterFlag(写标W_F 0：只读W_T 1：可读写）
//StorageFlag（存储标志0：不存储，1：需存储）


const SYS_MONITOR_DATA_STRUCT Plt_Mam860_DataList[PLT_Mam860_DATA_LIST_MAX] = 
{
    /*         压力    					温度    	      	历史运行时间    			历史负载时间  	 */
	{1,0,2,Flo,Dec2,W_F,S_T},{2,1,2,Flo,Dec1,W_F,S_T},{2000,2,4,Int,Dec0,W_F,S_F},{2002,3,4,Int,Dec0,W_F,S_F},
		
	/*         主电流A    				主电流B    				主电流C     	    		 */
	{6,4,2,Flo,Dec1,W_F,S_T},{7,5,2,Flo,Dec1,W_F,S_T},{8,6,2,Flo,Dec1,W_F,S_T},
	/*   		机器状态 	             机器状态2  	   油滤器使用时间    */
	{5,7,2,Bit,Dec0,W_F,S_T},{0,8,2,Bit,Dec0,W_F,S_T},	{2004,10,2,Int,Dec0,W_F,S_F},
			
	/*   油分器使用时间             	空滤器使用时间        	 润滑油使用时间           	 润滑脂使用时间          */
	{2005,11,2,Int,Dec0,W_F,S_F},{2006,12,2,Int,Dec0,W_F,S_F},{2007,13,2,Int,Dec0,W_F,S_F},{2008,14,2,Int,Dec0,W_F,S_F},		
	
	/*  皮带使用时间                   风电流A    						 风电流B    				风电流C                        */
	{2009,15,2,Int,Dec0,W_F,S_F},{9,16,2,Flo,Dec1,W_F,S_T},{10,17,2,Flo,Dec1,W_F,S_T},{11,18,2,Flo,Dec1,W_F,S_T},
		
	/*  相序保护电压					   变频器输出频率 						变频器输出电压 					变频器输出电流                 		 */	
	{211,21,2,Flo,Dec1,W_F,S_F},{40,24,2,Flo,Dec1,W_F,S_F},{43,25,2,Flo,Dec1,W_F,S_F},{42,26,2,Flo,Dec1,W_F,S_F},

	/* 变频输出功率 					变频输出转速								故障					预警值     */
	{44,27,2,Flo,Dec1,W_F,S_F}, {41,28,2,Int,Dec0,W_F,S_F},{217,37,2,Int,Dec0,W_F,S_F},{214,39,2,Int,Dec0,W_F,S_F},
	

	/*      油滤器最大时间    			       油分器最大时间           				 	空滤器最大时间          */
	{2102,100,2,Int,Dec0,W_T,S_F},{2103,101,2,Int,Dec0,W_T,S_F},{2104,102,2,Int,Dec0,W_T,S_F},
		
	/*   润滑油最大时间         				润滑脂最大时间       					加载压力			     		卸载压力		  */
	{2105,103,2,Int,Dec0,W_T,S_T},{2106,104,2,Int,Dec0,W_T,S_T},{2108,80,2,Flo,Dec2,W_T,S_T},{2107,81,2,Flo,Dec2,W_T,S_T},
	
		/* 目标压力								风机启温度     					风机停温度   */
	{2109,82,2,Flo,Dec2,W_T,S_T},{2113,83,2,Flo,Dec1,W_T,S_F},{2112,84,2,Flo,Dec1,W_T,S_F},
	
		/* 写标识   最高位为1 可写 */
	{0, 20, 2,Bit, Dec0, W_F, S_F}

	
};



const SYS_MONITOR_DATA_STRUCT Plt_Mam6080_DataList[PLT_DATA_LIST_MAX] = 
{
    /*         压力    					温度    				电源电压                                    		 */
	{1,0,2,Flo,Dec2,W_F,S_T},{2,1,2,Flo,Dec1,W_F,S_T},{4,24,2,Int,Dec0,W_F,S_T},
		
	/*         机器状态             	主电流A    				主电流B    				主电流C     	    		 */
	{5,7,2,Bit,Dec0,W_F,S_T},{6,4,2,Flo,Dec1,W_F,S_T},{7,5,2,Flo,Dec1,W_F,S_T},{8,6,2,Flo,Dec1,W_F,S_T},
		
	/*         风电流A    				风电流B    				风电流C                           					 */
	{9,17,2,Flo,Dec1,W_F,S_T},{10,18,2,Flo,Dec1,W_F,S_T},{11,19,2,Flo,Dec1,W_F,S_T},
		
	/*    主机变频输出频率          	主转速                  主机变频输出电流                           			 */
	{40,34,2,Flo,Dec2,W_F,S_T},{41,40,2,Int,Dec0,W_F,S_T},{42,33,2,Flo,Dec1,W_F,S_T},
		
	/*    主机变频输出电压          	主机变频输出功率        风机变频输出频率          	风转速          		 */
	{43,32,2,Flo,Dec1,W_F,S_T},{44,35,2,Flo,Dec1,W_F,S_T},{70,38,2,Flo,Dec2,W_F,S_T},{71,41,2,Int,Dec0,W_F,S_T},
		
	/*    风机变频输出电流         		风机变频输出电压        风机变频输出功率          主机累计用电     			 */
	{72,37,2,Flo,Dec1,W_F,S_T},{73,36,2,Flo,Dec1,W_F,S_T},{74,39,2,Flo,Dec1,W_F,S_T},{200,77,4,Int,Dec0,W_F,S_F},
			
	/* 	  主机累计用电                 风机累计用电                 风机累计用电  	            工频主机累计用电     */
	{200,78,4,Int,Dec0,W_F,S_F}, {202,79,4,Int,Dec0,W_F,S_F}, {202,80,4,Int,Dec0,W_F,S_F},  {204,83,4,Int,Dec0,W_F,S_F},
	
	/*   工频主机累计用电              工频风机累计用电             工频风机累计用电       	    前轴承温度           */	
	{204,84,4,Int,Dec0,W_F,S_F}, {206,89,4,Int,Dec0,W_F,S_F},{206,90,4,Int,Dec0,W_F,S_F},{208,16,2,Flo,Dec1,W_F,S_F},
		
	/*   后轴承温度                 	历史运行时间小时       				历史运行时间分钟      						历史负载时间小时				历史负载时间分钟          			      油滤器使用时间          */
	{209,62,2,Flo,Dec1,W_F,S_F},{2000,2,2,Int,Dec0,W_F,S_F},{1998,2007,2,Int,Dec0,W_F,S_F},{2002,3,2,Int,Dec0,W_F,S_F}, {1999,2011,2,Int,Dec0,W_F,S_F},	{2004,10,2,Int,Dec0,W_F,S_F},
		
	/*   油分器使用时间             	空滤器使用时间        	 润滑油使用时间           	 润滑脂使用时间          */
	{2005,11,2,Int,Dec0,W_F,S_F},{2006,12,2,Int,Dec0,W_F,S_F},{2007,13,2,Int,Dec0,W_F,S_F},{2008,14,2,Int,Dec0,W_F,S_F},
		
	/*   最大使用时间               		油滤器最大时间           油分器最大时间           	 	空滤器最大时间          */
	{2100,3017,2,Int,Dec0,W_T,S_F},{2102,1018,2,Int,Dec0,W_T,S_F},{2103,1019,2,Int,Dec0,W_T,S_F},{2104,1020,2,Int,Dec0,W_T,S_F},
		
	/*   润滑油最大时间         			润滑脂最大时间              卸载压力                  	加载压力               */
	{2105,1021,2,Int,Dec0,W_T,S_T},{2106,1022,2,Int,Dec0,W_T,S_T},{2107,1003,2,Flo,Dec2,W_T,S_T},{2108,1002,2,Flo,Dec2,W_T,S_T},
		
	/*   目标压力                   		停机压力                    卸载高限                  	停止温度                */
	{2109,3061,2,Flo,Dec2,W_T,S_F},{2110,3006,2,Flo,Dec2,W_T,S_F},{2111,3008,2,Flo,Dec2,W_T,S_F},{2112,1001,2,Flo,Dec1,W_T,S_F},	
	
	/*   启动温度                   		目标温度                    预警温度                  	停机温度                */
	{2113,1000,2,Flo,Dec1,W_T,S_F},{2114,3066,2,Flo,Dec1,W_T,S_F},{2115,3002,2,Flo,Dec1,W_T,S_F},{2116,3003,2,Flo,Dec1,W_T,S_F},
		
	/*   重启延时               			加载延时                    空载延时                   	停机延时              	*/
	{2118,1007,2,Int,Dec0,W_T,S_F},{2119,1005,2,Int,Dec0,W_T,S_F},{2120,1010,2,Int,Dec0,W_T,S_F},{2121,1006,2,Int,Dec0,W_T,S_F},			

	/*   主额流                     		电流不平衡度   					主机延时                     星角延时       	*/
	{2326,3000,2,Flo,Dec1,W_T,S_F},{2327,3009,2,Int,Dec0,W_T,S_F},{2328,1008,2,Int,Dec0,W_T,S_F},{2329,1004,2,Int,Dec0,W_T,S_F},
		
	/*   风额流              				风机延时                     	用户密码                  	厂家密码             */
	{2366,3001,2,Flo,Dec1,W_T,S_F},{2368,1009,2,Int,Dec0,W_T,S_F},{3000,1017,10,Str,Dec0,W_T,S_F},{3005,3018,10,Str,Dec0,W_T,S_F},	

	/*   状态2             				预警                    	运行状态             故障   	             */
	{0,8,2,Bit,Dec0,W_F,S_F},{0,25,2,Hex,Dec0,W_F,S_F},{0,26,2,Hex,Dec0,W_F,S_F},{0,28,2,Hex,Dec0,W_F,S_F},	
	
	/*   主机变频报警数据        主机变频运行状态            主机变频上限频率                主机变频下限频率    */
	{46,74,2,Int,Dec0,W_F,S_F},{47,73,2,Int,Dec0,W_F,S_F},{49,3024,2,Flo,Dec2,W_T,S_F},{50,3025,2,Flo,Dec2,W_T,S_F},	
	/*   主机变频加速时间        	主机变频减速时间                主机变频器型号     */
	{51,3019,2,Flo,Dec1,W_T,S_F},{52,3062,2,Flo,Dec1,W_T,S_F},{2300,3029,2,Bit,Dec0,W_F,S_F},	
	
	/*   风机变频报警数据         风机变频运行状态             风机变频上限频率                风机变频下限频率    */
	{76,76,2,Int,Dec0,W_F,S_F},{77,75,2,Int,Dec0,W_F,S_F},{79,3035,2,Flo,Dec2,W_T,S_F},{80,3036,2,Flo,Dec2,W_T,S_F},	
	/*   风机变频加速时间        	 风机变频减速时间                 风机变频器型号     */
	{81,3030,2,Flo,Dec1,W_T,S_F},{82,3068,2,Flo,Dec1,W_T,S_F},{2340,3040,2,Bit,Dec0,W_F,S_F},
	
//84+96,额外新增参数
	/*18  系统压力					相序保护电压				缺相保护电压				电压	 */
	{210,15,2,Flo,Dec2,W_F,S_F},{211,22,2,Int,Dec0,W_F,S_F},{212,23,2,Int,Dec0,W_F,S_F},{213,24,2,Int,Dec0,W_F,S_F},
	/*  预警值						运行状态					计时						故障	 */
	{214,25,2,Int,Dec0,W_F,S_F},{215,26,2,Int,Dec0,W_F,S_F},{216,27,2,Int,Dec0,W_F,S_F},{217,28,2,Int,Dec0,W_F,S_F},
	/*  故障值						油分压差					主机状态字					主机故障字	 */
	{218,29,2,Int,Dec0,W_F,S_F},{219,63,2,Flo,Dec2,W_F,S_F},{220,73,2,Int,Dec0,W_F,S_F},{221,74,2,Int,Dec0,W_F,S_F},
	/*  风机状态字					风机故障字					工频主机本次用电			工频风机本次用电 */
	{222,75,2,Int,Dec0,W_F,S_F},{223,76,2,Int,Dec0,W_F,S_F},{224,81,4,Flo,Dec1,W_F,S_F},{226,87,4,Flo,Dec1,W_F,S_F},
	/*  工频主机UI					工频风机UI */
	{228,85,4,Int,Dec0,W_F,S_F},{230,91,4,Int,Dec0,W_F,S_F},
	
	
	/*24 温度单位						压力单位						预警过久停机				前轴预警温度  	*/
	{2138,1034,2,Int,Dec0,W_T,S_F},{2139,1033,2,Int,Dec0,W_T,S_F},{2140,3016,2,Int,Dec0,W_T,S_F},{2141,3004,2,Flo,Dec1,W_T,S_F},		
	/*  前轴报警温度			 		油分预警压差					油分报警压差				排水开延时		*/
	{2142,3005,2,Flo,Dec1,W_T,S_F},{2143,3090,2,Flo,Dec2,W_T,S_F},{2144,3091,2,Flo,Dec2,W_T,S_F},{2147,1023,2,Int,Dec0,W_T,S_F},
	/*  排水关延时						软启延时  						辅助启动时间				辅助加载延时 	*/
	{2148,1024,2,Int,Dec0,W_T,S_F},{2149,1025,2,Int,Dec0,W_T,S_F},{2150,1026,2,Int,Dec0,W_T,S_F},{2151,1027,2,Int,Dec0,W_T,S_F},
	/*  辅助卸载延时					辅助启温度						加载方式					启停方式	 	*/
	{2152,1028,2,Int,Dec0,W_T,S_F},{2153,1029,2,Flo,Dec1,W_T,S_F},{2154,1030,2,Int,Dec0,W_T,S_F},{2155,1031,2,Int,Dec0,W_T,S_F},
	/*  通信方式						语音选择 						运行方式					系统停机压力	*/
	{2156,1032,2,Int,Dec0,W_T,S_F},{2157,1035,2,Int,Dec0,W_T,S_F},{2158,1036,2,Int,Dec0,W_T,S_F},{2159,3007,2,Flo,Dec2,W_T,S_F},
	/*  历史故障复位					出厂编码1						出厂编码2 					出厂日期		*/
	{2160,3011,2,Int,Dec0,W_T,S_F},{2161,3012,2,Int,Dec0,W_T,S_F},{2162,3013,2,Int,Dec0,W_T,S_F},{2163,3014,2,Int,Dec0,W_T,S_F},
	                    
		
	/*25  主机积分初值					主机积分范围					主机比例增益				主机积分增益	 */
	{2380,3019,2,Flo,Dec1,W_T,S_F},{2381,3020,2,Flo,Dec2,W_T,S_F},{2382,3021,2,Flo,Dec1,W_T,S_F},{2383,3022,2,Flo,Dec1,W_T,S_F},		
	/*  主机微分增益					主机频率上限					主机频率下限				主机空载频率 */
	{2384,3023,2,Flo,Dec1,W_T,S_F},{2385,3024,2,Flo,Dec2,W_T,S_F},{2386,3025,2,Flo,Dec2,W_T,S_F},{2387,3026,2,Flo,Dec2,W_T,S_F},
	/*   主机变频器站号					主机PID周期						主机变频器型号				风机积分初值*/
	{2388,3027,2,Int,Dec0,W_T,S_F},{2389,3028,2,Int,Dec0,W_T,S_F},{2390,3029,2,Int,Dec0,W_T,S_F},{2391,3030,2,Flo,Dec1,W_T,S_F},
	/*   风机积分范围					风机比例增益					风机积分增益				风机微分增益*/
	{2392,3031,2,Flo,Dec2,W_T,S_F},{2393,3032,2,Flo,Dec1,W_T,S_F},{2394,3033,2,Flo,Dec1,W_T,S_F},{2395,3034,2,Flo,Dec1,W_T,S_F},
	/*   风机频率上限					风机频率下限					风机空载频率				风机变频器站号*/
	{2396,3035,2,Flo,Dec2,W_T,S_F},{2397,3036,2,Flo,Dec2,W_T,S_F},{2398,3037,2,Flo,Dec2,W_T,S_F},{2399,3038,2,Int,Dec0,W_T,S_F},
	/*   风机PID周期					风机变频器型号					电压过高					电压过低	*/
	{2400,3039,2,Int,Dec0,W_T,S_F},{2401,3040,2,Int,Dec0,W_T,S_F},{2128,3041,2,Int,Dec0,W_T,S_F},{2129,3042,2,Int,Dec0,W_T,S_F},
	/*   通信超时*/
	{2404,3043,2,Int,Dec0,W_T,S_F},
	
	
	/*29   降频压力						主机上升速率				主机下降速率				主机功率	*/
	{2420,3060,2,Flo,Dec2,W_T,S_F},{2421,3062,2,Flo,Dec1,W_T,S_F},{2422,3063,2,Flo,Dec1,W_T,S_F},{2423,3064,2,Flo,Dec1,W_T,S_F},
	/*   主机转速						风机上升速率				风机下降速率				风机功率*/
	{2424,3065,2,Int,Dec0,W_T,S_F},{2425,3068,2,Flo,Dec1,W_T,S_F},{2426,3069,2,Flo,Dec1,W_T,S_F},{2427,3070,2,Flo,Dec1,W_T,S_F},
	/*   风机转速						变频风机启					变频风机停					主机停机方式	*/
	{2428,3071,2,Int,Dec0,W_T,S_F},{2429,3072,2,Flo,Dec1,W_T,S_F},{2430,3073,2,Flo,Dec1,W_T,S_F},{2431,3074,2,Int,Dec0,W_T,S_F},
	/*   定时启停功能					定时压力功能				低温保护					主变频器启动方式*/
	{2432,3075,2,Int,Dec0,W_T,S_F},{2433,3076,2,Int,Dec0,W_T,S_F},{2117,3077,2,Flo,Dec1,W_T,S_F},{2435,3078,2,Int,Dec0,W_T,S_F},
	/*   风机变频器启动方式				通信启变频器次数			通信停变频器次数			工频主机功率系数*/
	{2436,3079,2,Int,Dec0,W_T,S_F},{2437,3080,2,Int,Dec0,W_T,S_F},{2438,3081,2,Int,Dec0,W_T,S_F},{2450,3083,2,Flo,Dec2,W_T,S_F},
	/*   变频主机功率系数				变频风机功率系数			工频风机功率系数			预开主机变频器延时*/
	{2451,3084,2,Flo,Dec2,W_T,S_F},{2452,3085,2,Flo,Dec2,W_T,S_F},{2453,3086,2,Flo,Dec2,W_T,S_F},{2454,3087,2,Int,Dec0,W_T,S_F},
	/*   掉电重启功能					频率选择					管路压阻					后轴承预警温度*/
	{2455,3088,2,Int,Dec0,W_T,S_F},{2456,3089,2,Int,Dec0,W_T,S_F},{2457,3092,2,Flo,Dec2,W_T,S_F},{2458,3093,2,Flo,Dec1,W_T,S_F},
	/*  后轴承停机温度       */
	{2459,3094,2,Flo,Dec1,W_T,S_F},	
		
	/*   写标志            */
	{0,20,2,Bit,Dec0,W_F,S_F},	
	
};

const SYS_MONITOR_DATA_STRUCT H2U_PLC_DataList[H2U_PLC_LIST_MAX] = 
{
		/*		   压力						温度					电源电压				 */
		{1,163,2,Flo,Dec2,W_F,S_T},{2,164,2,Flo,Dec1,W_F,S_T},{4,1282,2,Flo,Dec1,W_F,S_T},
			
		/*		  运行状态 						P2水压 			 		  P3压力					一级排气温度*/
		{9010,161,2,Bit,Dec0,W_F,S_T},{14,915,2,Flo,Dec2,W_F,S_T},{15,56,2,Flo,Dec2,W_F,S_T},{17,916,2,Flo,Dec1,W_F,S_T},
			
		/*		   风电流A					风电流B					风电流C												 */
		{9,25,2,Flo,Dec2,W_F,S_T},{10,25,2,Flo,Dec2,W_F,S_T},{11,25,2,Flo,Dec2,W_F,S_T},
			
		/*	  主机变频输出频率				主机变频输出电流 									 */
		{40,168,2,Flo,Dec2,W_F,S_T},{42,169,2,Flo,Dec1,W_F,S_T},
			
		/*	  主机变频输出电压				主机变频输出功率						风机变频输出频率			 */
		{43,1284,2,Int,Dec0,W_F,S_T},{44,942,2,Flo,Dec1,W_F,S_T},{70,170,2,Flo,Dec2,W_F,S_T},
			
		/*	  风机变频输出电流				  风机变频输出电压					  风机变频输出功率		  					 历史运行时间小时				 */
		{72,25,2,Flo,Dec1,W_F,S_T},{73,1190,2,Flo,Dec1,W_F,S_T}, {74,943,2,Flo,Dec1,W_F,S_T},{2000,1818,2,Int,Dec0,W_F,S_F},
				
		/*	历史负载时间小时					 本次使用时间小时  						 本次使用时间分钟 		      	 	  	水滤器使用时间 		 */
		{2002,1426,2,Int,Dec0,W_F,S_F},	{33,35,2,Int,Dec0,W_F,S_F},	{34,36,2,Int,Dec0,W_F,S_F},{2010,1810,2,Int,Dec0,W_F,S_F},
			
		/*	空滤器使用时间			 				最大使用时间 						水滤器最大时间							空滤器最大时间		   	*/
		{2006,1808,2,Int,Dec0,W_F,S_F},{2100,1635,2,Int,Dec0,W_T,S_F},{2012,1951,2,Int,Dec0,W_T,S_F},{2104,1950,2,Int,Dec0,W_T,S_F},
			
				
		/*	 		 卸载压力 					加载压力			  			 目标压力							停机压力				 */
		{2107,1904,2,Flo,Dec2,W_T,S_T},{2108,1908,2,Flo,Dec2,W_T,S_T},{2109,1900,2,Flo,Dec2,W_T,S_F},{2110,1909,2,Flo,Dec2,W_T,S_F},
			
		/*		     卸载高限					        停止温度				 启动温度						    目标温度					*/
		{2111,1904,2,Flo,Dec2,W_T,S_F},{2112,1913,2,Int,Dec0,W_T,S_F},{2113,1912,2,Int,Dec0,W_T,S_F},{2114,1910,2,Int,Dec0,W_T,S_F},
		
		/*			预警温度							停机温度					运行方式         		*/
		{2115,1914,2,Int,Dec0,W_T,S_F},{2116,1915,2,Int,Dec0,W_T,S_F},{2158,1917,2,Int,Dec0,W_T,S_F},
			
		/* 		       整机电量低位      			整机电量高位              			低水进水保护        	   		     自动换水动作*/
		{436,1062,2,Int,Dec0,W_T,S_F},{436,1063,2,Int,Dec0,W_T,S_F}, {2460,1161,2,Int,Dec0,W_T,S_F},{2461,1162,2,Int,Dec0,W_T,S_F},

		/* 自动换水周期      						       限时运行功能  				 阀门状态     					  	主机IGBT温度*/
		{2462,1163,2,Int,Dec0,W_T,S_F},{2470,1061,2,Int,Dec0,W_T,S_F},{16,59,2,Int,Dec0,W_T,S_F},{231,1280,2,Int,Dec0,W_T,S_F},

		/* 主机变频器报警数据   			          风机变频器报警数据      				         报警状态1           			     报警状态2 */
		{46,924,2,Int,Dec0,W_F,S_F},{76,925,2,Int,Dec0,W_F,S_F},{9020,158,2,Int,Dec0,W_F,S_F},{9021,159,2,Int,Dec0,W_F,S_F},

			/* 报警状态3 				    			 报警状态4         				     写标志*/
		{9022,152,2,Int,Dec0,W_F,S_F},{9023,248,2,Int,Dec0,W_F,S_F},{0,164,2,Bit,Dec0,W_F,S_F}
};

#if MONITOR_METER_ON

#if 0

/*鑫宇电表*/
const SYS_MONITOR_DATA_STRUCT Xy_DataList[XY_DATA_LIST_MAX] = 
{		
	/*   A相电压      					B相电压  					C相电压      		 */
	{400,20,2,Flo,Dec1,W_F,S_F},{401,21,2,Flo,Dec1,W_F,S_F},{402,22,2,Flo,Dec1,W_F,S_F},
		
	/*   UAB      					  UBC					   UCA      		 */
	{414,23,2,Flo,Dec1,W_F,S_F},{415,25,2,Flo,Dec1,W_F,S_F},{416,24,2,Flo,Dec1,W_F,S_F},
		
	/* 	 A相电流      					B相电流      				C相电流  			 */
	{403,26,2,Flo,Dec3,W_F,S_F},{404,27,2,Flo,Dec3,W_F,S_F},{405,28,2,Flo,Dec3,W_F,S_F},
		
	/*  总有功功率  					总无功功率					总视在功率					总功率因素   	 */
	{406,33,2,Flo,Dec1,W_F,S_F},{407,37,2,Flo,Dec1,W_F,S_F},{408,41,2,Flo,Dec1,W_F,S_F},{409,45,2,Flo,Dec3,W_F,S_F},
	
	/*  频率							正用功电能高位   					正用功电能小数位  								接线方式*/
	{410,46,2,Flo,Dec2,W_F,S_F},{411,47,4,Flo,Dec2,W_F,S_F},{411,49,2,Flo,Dec2,W_F,S_F},  {412,1, 2,Int,Dec0,W_F,S_F},
	
	/*电流变比CT*/
	{413,3, 2,Int,Dec0,W_F,S_F},
	
	//流量计参数
	/*  	瞬时流量 					频率						压力						温度  	 	*/
	{420,0,4,Flo,Dec2,W_F,S_F},{422,2,4,Flo,Dec2,W_F,S_F},{424,6,4,Flo,Dec2,W_F,S_F},{426,8,4,Flo,Dec1,W_F,S_F},
	
	/*  	密度						累积流量  					流量计站号 			*/
	{428,10,4,Flo,Dec2,W_F,S_F},{430,24,4,Flo,Dec2,W_F,S_F},{432,1007,2,Int,Dec0,W_F,S_F},
		
};	


/*永诺电表*/
const SYS_MONITOR_DATA_STRUCT Xy_DataList[XY_DATA_LIST_MAX] = 
{		
	/*   A相电压      					B相电压  					C相电压      		 */
	{400,70,2,Flo,Dec1,W_F,S_F},{401,71,2,Flo,Dec1,W_F,S_F},{402,72,2,Flo,Dec1,W_F,S_F},
		
	/*   UAB      					  UBC					   UCA      		 */
	{414,73,2,Flo,Dec1,W_F,S_F},{415,74,2,Flo,Dec1,W_F,S_F},{416,75,2,Flo,Dec1,W_F,S_F},
		
	/* 	 A相电流      					B相电流      				C相电流  			 */
	{403,76,2,Flo,Dec2,W_F,S_F},{404,77,2,Flo,Dec2,W_F,S_F},{405,78,2,Flo,Dec2,W_F,S_F},
		
	/*  总有功功率  					总无功功率					总视在功率					总功率因素   	 */
	{406,82,2,Flo,Dec2,W_F,S_F},{407,86,2,Flo,Dec2,W_F,S_F},{408,90,2,Flo,Dec2,W_F,S_F},{409,94,2,Flo,Dec2,W_F,S_F},
	
	/*  频率							正有功电能   				接线方式*/
	{410,95,2,Flo,Dec2,W_F,S_F},{411,101,4,Flo,Dec2,W_F,S_F}, {412,531, 2,Int,Dec0,W_F,S_F},
	
	/*电流变比CT*/
	{413,537, 2,Int,Dec0,W_F,S_F},
	
	//流量计参数
	/*  	瞬时流量 					频率						压力						温度  	 	*/
	{420,0,4,Flo,Dec2,W_F,S_F},{422,2,4,Flo,Dec2,W_F,S_F},{424,6,4,Flo,Dec2,W_F,S_F},{426,8,4,Flo,Dec1,W_F,S_F},
	
	/*  	密度						累积流量  					流量计站号 			*/
	{428,10,4,Flo,Dec2,W_F,S_F},{430,24,4,Flo,Dec2,W_F,S_F},{432,1007,2,Int,Dec0,W_F,S_F},
		
};	
#else
/*安科瑞电表*/
const SYS_MONITOR_DATA_STRUCT Xy_DataList[XY_DATA_LIST_MAX] = 
{		
	/*   A相电压      					B相电压  					C相电压      		 */
	{400,97,2,Flo,Dec1,W_F,S_F},{401,98,2,Flo,Dec1,W_F,S_F},{402,99,2,Flo,Dec1,W_F,S_F},
		
	/*   UAB      					  UBC					   UCA      		 */
	{414,120,2,Flo,Dec1,W_F,S_F},{415,121,2,Flo,Dec1,W_F,S_F},{416,122,2,Flo,Dec1,W_F,S_F},
		
	/* 	 A相电流      					B相电流      				C相电流  			 */
	{403,100,2,Flo,Dec2,W_F,S_F},{404,101,2,Flo,Dec2,W_F,S_F},{405,102,2,Flo,Dec2,W_F,S_F},
		
	/*  总有功功率  					总无功功率					总视在功率					总功率因素   	 */
	{406,362,4,Flo,Dec3,W_F,S_F},{407,370,4,Flo,Dec3,W_F,S_F},{408,378,4,Flo,Dec3,W_F,S_F},{409,383,2,Flo,Dec3,W_F,S_F},
	
	/*  频率							正有功电能   					电流变比CT*/
	{410,119,2,Flo,Dec2,W_F,S_F},{411,10,4,Flo,Dec2,W_F,S_F},{413,142, 2,Int,Dec0,W_F,S_F},
	
	//流量计参数
	/*  	瞬时流量 					频率						压力						温度  	 	*/
	{420,0,4,Flo,Dec2,W_F,S_F},{422,2,4,Flo,Dec2,W_F,S_F},{424,6,4,Flo,Dec2,W_F,S_F},{426,8,4,Flo,Dec1,W_F,S_F},
	
	/*  	密度						累积流量  					流量计站号 			*/
	{428,10,4,Flo,Dec2,W_F,S_F},{430,24,4,Flo,Dec2,W_F,S_F},{432,1007,2,Int,Dec0,W_F,S_F},
		
};	

#endif	

#endif

SERVER_WRITER_DATA_STRUCT  Server_Data_Buf;



u16  GetPltReadAddr(void)
{
	u16 Temp = 0;
	switch(GpSysPara->Dev.Bits.PS) 
	{
			case PS_MAM_KY_G:
			case PS_MAM_KY_C:
			case PS_MAM260:
			case PS_MAM260A:
			case PS_MAM280:
			case PS_MAM660_670_680:	
            case PS_MAM860_870_880:                                       //  普乐特               
            case PS_MAM860C_880C:  
			case PS_MAM890: 
				if (GpSysPara->Dev.Bits.PS == PS_MAM860_870_880 && VfdCtrl.ReadIndex == PLT_Man_WARNING )
				{
					Temp = 21;
				}
				else if (GpSysPara->Dev.Bits.PS == PS_MAM860_870_880 && VfdCtrl.ReadIndex == PLT_Man_FALT)
				{
						Temp = 20;
				}
				else
				{
					Temp = Plt_Mam860_DataList[VfdCtrl.ReadIndex].Addr;
				}
			
				break;
            case PS_MAM6080_6090:
			case PS_MAM6090:
			case PS_MAM6070:
				Temp = Plt_Mam6080_DataList[VfdCtrl.ReadIndex].Addr;
                break;
			case PS_HC:
				Temp = H2U_PLC_DataList[VfdCtrl.ReadIndex].Addr;
				break;
			#if MONITOR_METER_ON
			case PS_TYPE_XY_1942E:	//鑫宇电表
				Temp = Xy_DataList[VfdCtrl.ReadIndex].Addr;
                break;
			#endif
			
            default:
            	Temp = Plt_Mam6080_DataList[VfdCtrl.ReadIndex].Addr;
                break;
    }  
    
	return Temp;
}



void  GetMeterReadAddr(u16 *DatAddr, u8 *DatLen)
{
	
	*DatAddr = Xy_DataList[MeterCtrl.ReadIndex].Addr;
    *DatLen  = Xy_DataList[MeterCtrl.ReadIndex].DataLen;		
}

void  GetMeter2ReadAddr(u16 *DatAddr, u8 *DatLen)
{
	
	*DatAddr = Xy_DataList[Meter2Ctrl.ReadIndex].Addr;
    *DatLen  = Xy_DataList[Meter2Ctrl.ReadIndex].DataLen;		
}

//厂家参数
void  GetPlt3SpecPara(char *pBuf)
{ 
	JSON_AddrAndDataToObject(pBuf, 2100, GpUsrPara->Hour.MaxUseTime, NULL); 		//最大使用时限
	JSON_AddrAndDataToObject(pBuf, 2110, GpSysStat->Share.StopPress, NULL);  		//停机压力
	JSON_AddrAndDataToObject(pBuf, 2111, GpSysStat->Share.MaxUnloadPress, NULL);  	//卸载高限 
	JSON_AddrAndDataToObject(pBuf, 2115, GpSysStat->Fan.PreAlmTemp, NULL); 			//预警温度
	JSON_AddrAndDataToObject(pBuf, 2116, GpSysStat->Fan.AlmTemp, NULL); 			//停机温度
	JSON_AddrAndDataToObject(pBuf, 2326, GpSysStat->Main.RateCurrent, NULL); 		//主额流
	JSON_AddrAndDataToObject(pBuf, 2366, GpSysStat->Fan.RateCurrent, NULL); 		//风额流 
	JSON_AddrAndDataToObject(pBuf, 2327, GpSysStat->Share.UnblanceCurrent, NULL); 	//电流不平衡度
}

//用户参数
void  GetPlt2SpecPara(char *pBuf)
{    
	JSON_AddrAndDataToObject(pBuf, 2109, GpSysStat->Main.Cfreq_Press, NULL);  	//目标压力	  
	JSON_AddrAndDataToObject(pBuf, 2108, GpSysStat->Share.LoadPress, NULL);  	//加载压力   
	JSON_AddrAndDataToObject(pBuf, 2107, GpSysStat->Share.UnLoadPress, NULL); 	//卸载压力 
	JSON_AddrAndDataToObject(pBuf, 2114, GpSysStat->Fan.Cfreq_Temp, NULL);  	//目标温度
	JSON_AddrAndDataToObject(pBuf, 2113, GpSysStat->Fan.StartTemp, NULL);  		//启动温度
	JSON_AddrAndDataToObject(pBuf, 2112, GpSysStat->Fan.StopTemp, NULL);  		//停止温度
	
	JSON_AddrAndDataToObject(pBuf, 2118, GpSysStat->Share.StartDelay, NULL); 	//重启延时
	JSON_AddrAndDataToObject(pBuf, 2119, GpSysStat->Share.LoadDelay, NULL); 	//加载延时
	JSON_AddrAndDataToObject(pBuf, 2120, GpSysStat->Share.UnloadDelay, NULL); 	//空载延时
	JSON_AddrAndDataToObject(pBuf, 2121, GpSysStat->Share.StopDelay, NULL); 	//停机延时
	JSON_AddrAndDataToObject(pBuf, 2328, GpSysStat->Share.MainDelay, NULL);  	//主机延时
	JSON_AddrAndDataToObject(pBuf, 2329, GpSysStat->Share.XinJiaoDelay, NULL);  //星角延时
	JSON_AddrAndDataToObject(pBuf, 2368, GpSysStat->Share.FanDelay, NULL); 		//风机延时
	JSON_AddrAndDataToObject(pBuf, 2158, GpSysStat->OtherData.RunMode, NULL);   // 运行方式
	
}
//保养参数
void  GetPlt1SpecPara(u8          pstype, char *pBuf)
{
	if (pstype == CLASS_6080)
	{
		JSON_AddrAndDataToObject(pBuf, 200, GpSysStat->Main.Power_Consume_Total, NULL); 
		JSON_AddrAndDataToObject(pBuf, 202, GpSysStat->Fan.Power_Consume_Total, NULL); 
		JSON_AddrAndDataToObject(pBuf, 204, GpSysStat->Main.Pfreq_Power_Consume_Total, NULL); 
		JSON_AddrAndDataToObject(pBuf, 206, GpSysStat->Fan.Pfreq_Power_Consume_Total, NULL); 
		JSON_AddrNumberDataToObject(pBuf, 436, GpSysStat->Share.Total_Power);											
	}
	
	if (pstype == CLASS_860C || pstype == CLASS_6080)
	{
		JSON_AddrNumberDataToObject(pBuf, 2102, GpUsrPara->Hour.MaxOilFiltTime);
	    JSON_AddrNumberDataToObject(pBuf, 2103, GpUsrPara->Hour.MaxOilSepaTime);
	    JSON_AddrNumberDataToObject(pBuf, 2104, GpUsrPara->Hour.MaxGasFiltTime);
	    JSON_AddrNumberDataToObject(pBuf, 2105, GpUsrPara->Hour.MaxlubeTime);
	    JSON_AddrNumberDataToObject(pBuf, 2106, GpUsrPara->Hour.MaxGreaseTime);
	}
 
    JSON_AddrNumberDataToObject(pBuf, 2006, GpSysStat->Run.GasFiltHour);
    JSON_AddrNumberDataToObject(pBuf, 2007, GpSysStat->Run.lubeHour);
    JSON_AddrNumberDataToObject(pBuf, 2008, GpSysStat->Run.GreaseHour);  
    JSON_AddrNumberDataToObject(pBuf, 2004, GpSysStat->Run.OilFiltHour);	
    JSON_AddrNumberDataToObject(pBuf, 2005, GpSysStat->Run.OilSepaHour);
    
    if (pstype == CLASS_860)
    {
    	JSON_AddrNumberDataToObject(pBuf, 2009, GpSysStat->Run.BeltHour);  //皮带运行时间
    }

	if (pstype == CLASS_HC)
	{
	   JSON_AddrNumberDataToObject(pBuf, 2104, GpUsrPara->Hour.MaxGasFiltTime);
	   JSON_AddrNumberDataToObject(pBuf, 2012, GpUsrPara->Hour.MaxWaterFiltTime);
		JSON_AddrNumberDataToObject(pBuf, 2010, GpSysStat->Run.WaterFiltHour);
		
	}
}


char VarBuf[GPRS_DOMAIN_SIZE+1]; 
void    GetPltAllPara( char *pBuf, u16 *pLen) 
{
		u8 i;
    u16 Addr, Data, Len;
    ADDR_TYPE_ENUM AddrType;

    JSON_ObjectBegin(pBuf);  
    JSON_RtcTimeGet(pBuf);
    JSON_NumberValToObject(pBuf, "PS", GpSysPara->Dev.Bits.PS);

        /*
         *  网络参数
         */
        for(Addr = 2600; Addr <= 2645; Addr+=15) {
            memset(VarBuf, 0, sizeof(VarBuf));
            SysVarRead(Addr, VarBuf, &Len, &AddrType);
            JSON_AddrStringDataToObject(pBuf, Addr, VarBuf);
        }
        for(Addr = 2660; Addr <= 2662; Addr++) {
            SysVarRead(Addr, VarBuf, &Len, &AddrType);
            Data = DevTwoByteToWord(VarBuf);           
            JSON_AddrNumberDataToObject(pBuf, Addr, Data);
        }  
        
        JSON_AddrStringDataToObject(pBuf, 2513, PCB_VERSION);       //  版本日期
        JSON_AddrStringDataToObject(pBuf, 2518, APP_VERSION);       //  软件版本
        JSON_AddrStringDataToObject(pBuf, 2523, GpSysPara->Dev.ID); //  终端编号
        JSON_AddrStringDataToObject(pBuf, 150, GprsCtrlInfo.IMEI);  //  SIM卡串号
	    JSON_AddrStringDataToObject(pBuf, 158, GprsCtrlInfo.CCID);  //  SIM卡号码
	
		for(i=166; i<184; i++)
		{
			SpecAddrRead(i, VarBuf, &Len, &AddrType);
			Data = DevTwoByteToWord(VarBuf);           
            JSON_AddrNumberDataToObject(pBuf, i, Data);
		}

		// 设备串口通信状态
	 JSON_AddrNumberDataToObject(pBuf, 9000,  GpSysStat->Share.DTU_COMM_STATUS);	
	
			//用户参数
			JSON_AddrAndDataToObject(pBuf, 2109, GpSysStat->Main.Cfreq_Press, NULL);  	//目标压力	  
			JSON_AddrAndDataToObject(pBuf, 2108, GpSysStat->Share.LoadPress, NULL);  	//加载压力   
			JSON_AddrAndDataToObject(pBuf, 2107, GpSysStat->Share.UnLoadPress, NULL); 	//卸载压力 
			JSON_AddrAndDataToObject(pBuf, 2113, GpSysStat->Fan.StartTemp, NULL);  		//启动温度
			JSON_AddrAndDataToObject(pBuf, 2112, GpSysStat->Fan.StopTemp, NULL);  		//停止温度

			if (GpSysPara->Dev.Bits.PS != PS_MAM860C_880C)
			{
				JSON_AddrAndDataToObject(pBuf, 2114, GpSysStat->Fan.Cfreq_Temp, NULL);
  	//目标温度
				
				JSON_AddrNumberDataToObject(pBuf, 2158, GpSysStat->OtherData.RunMode);	// 运行方式
						      
			   //厂家参数
			   JSON_AddrAndDataToObject(pBuf, 2100, GpUsrPara->Hour.MaxUseTime, NULL);		   //最大使用时限
			   JSON_AddrAndDataToObject(pBuf, 2110, GpSysStat->Share.StopPress, NULL);		   //停机压力
			   JSON_AddrAndDataToObject(pBuf, 2111, GpSysStat->Share.MaxUnloadPress, NULL);    //卸载高限 
			   JSON_AddrAndDataToObject(pBuf, 2115, GpSysStat->Fan.PreAlmTemp, NULL);		   //预警温度
			   JSON_AddrAndDataToObject(pBuf, 2116, GpSysStat->Fan.AlmTemp, NULL);			   //停机温度
			   
			   JSON_AddrAndDataToObject(pBuf, 2128, GpSysStat->OtherData.VoltOvertop, NULL);		   //电源上限电压
			   JSON_AddrAndDataToObject(pBuf, 2129, GpSysStat->OtherData.VoltOverlow, NULL);		   //电源下限电压
			   JSON_AddrAndDataToObject(pBuf, 2300,GpSysStat->VFD.MainVfd_Model, NULL); 		   //主机变频器型号
			   JSON_AddrAndDataToObject(pBuf, 2340, GpSysStat->VFD.FanVfd_Model, NULL); 		   //风机变频器型号

			  

			}
		
			if (GpSysPara->Dev.Bits.PS == PS_HC)
			{
				 JSON_AddrAndDataToObject(pBuf, 2460, GpSysStat->OtherData.LowWaterProtectTime, NULL); 
				  JSON_AddrAndDataToObject(pBuf, 2461, GpSysStat->OtherData.AutoChangeWaterActTime, NULL); 
				  JSON_AddrAndDataToObject(pBuf, 2462, GpSysStat->OtherData.AutoChangeWaterCycle, NULL); 
				  JSON_AddrAndDataToObject(pBuf, 2470, GpSysStat->OtherData.MaxUseTimeFunc, NULL); 
			}

//    switch(PSVal) {
//        case PS_TYPE_PLT_MAM670:
//        case PS_TYPE_PLT_MAM680D:
//        case PS_TYPE_NO_ALM:
//        case PS_TYPE_PLT_MAM6080:
//		case PS_TYPE_PLT_MAM6090:
////          GetPlt3SpecPara(pBuf);
////			GetPlt2SpecPara(pBuf);
////			GetPlt1SpecPara(pBuf);
//            break;
//        default:
//            break;
//    }
    
    JSON_ObjectEnd(pBuf);

    ++ParaUpload.Bits.Index;
    ParaUpload.Bits.Send = FALSE;

    *pLen = strlen(pBuf);    
}


char    Plt1SysVarRead(u16 Addr, char *pBuf, u16 *pLen, ADDR_TYPE_ENUM *pType)
{
	u8 Err =TRUE;
    *pLen = 2;
    *pType = ADDR_TYPE_OTHER;  
    
    switch(Addr) { 
		
		case 9:          //风机A相电流 
			   memcpy(pBuf, (char *)&GpSysStat->Fan.A_Current, 2);
			   break;
		case 10:          //风机B相电流 
			   memcpy(pBuf, (char *)&GpSysStat->Fan.B_Current, 2);
			   break;		
		case 11:          //风机C相电流 
			   memcpy(pBuf, (char *)&GpSysStat->Fan.C_Current, 2);
			   break;
		
        default:           
            Err =FALSE;
		break;
    }  

    return Err;
}


char    Plt3SysVarRead(u16 Addr, char *pBuf, u16 *pLen, ADDR_TYPE_ENUM *pType)
{
	 char  ret = TRUE;
    *pLen = 2;
    *pType = ADDR_TYPE_OTHER;  

    switch(Addr) {  
		
		case 4:          //电源电压
			   memcpy(pBuf, (char *)&GpSysStat->Share.PowerVolt, 2);
			   break;
		case 9:          //风机A相电流 
			   memcpy(pBuf, (char *)&GpSysStat->Fan.A_Current, 2);
			   break;
		case 10:          //风机B相电流 
			   memcpy(pBuf, (char *)&GpSysStat->Fan.B_Current, 2);
			   break;
		
		case 11:          //风机C相电流 
			   memcpy(pBuf, (char *)&GpSysStat->Fan.C_Current, 2);
			   break;
		case 33:		// 本次运行时间 小时
				memcpy(pBuf, (char *)&GpSysStat->Run.CurrentRunHour, 2);
				break;
		case  34:    //本次运行时间   	分钟
				memcpy(pBuf, (char *)&GpSysStat->Run.CurrentRunMinute, 2);
				break;

		case 40:          //主机变频输出频率
			   memcpy(pBuf, (char *)&GpSysStat->Main.OutFreq, 2);
			   break;
		case 41:          //主转速
			   memcpy(pBuf, (char *)&GpSysStat->Main.OutSpeed, 2);
			   break;
		
		
		case 42:          //主机变频输出电流
			   memcpy(pBuf, (char *)&GpSysStat->Main.OutCurrent, 2);
			   break;
		case 43:          //主机变频输出电压
			   memcpy(pBuf, (char *)&GpSysStat->Main.OutVolt, 2);
			   break;
		case 44:          //主机变频输出功率
			   memcpy(pBuf, (char *)&GpSysStat->Main.OutPower, 2);
			   break;
		
		case 46:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.MainVfd_AlarmValue, 2);
			   break;
		case 47:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.MainVfd_RunState, 2);
			   break;
		case 49:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.MainVfd_TopLimitFreq, 2);
			   break;
		case 50:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.MainVfd_LowLimitFreq, 2);
			   break;
		case 51:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.MainVfd_AccelerateTime, 2);
			   break;
		case 52:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.MainVfd_DecelerateTime, 2);
			   break;
		case 2300:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.MainVfd_Model, 2);
			   break;
		
		case 70:          //风机变频输出频率 
			  memcpy(pBuf, (char *)&GpSysStat->Fan.OutFreq, 2);
			  break;
		case 71:          //风转速
			   memcpy(pBuf, (char *)&GpSysStat->Fan.OutSpeed, 2);
			   break;
		
		case 72:          //风机变频输出电流 
			  memcpy(pBuf, (char *)&GpSysStat->Fan.OutCurrent, 2);
			  break;
		case 73:          //风机变频输出电压 
			   memcpy(pBuf, (char *)&GpSysStat->Fan.OutVolt, 2);
			   break;
		case 74:          //风机变频输出功率 
			  memcpy(pBuf, (char *)&GpSysStat->Fan.OutPower, 2);
			  break;
		
		case 76:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.FanVfd_AlarmValue, 2);
			   break;
		case 77:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.FanVfd_RunState, 2);
			   break;
		case 79:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.FanVfd_TopLimitFreq, 2);
			   break;
		case 80:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.FanVfd_LowLimitFreq, 2);
			   break;
		case 81:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.FanVfd_AccelerateTime, 2);
			   break;
		case 82:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.FanVfd_DecelerateTime, 2);
			   break;
		case 2340:          //
			   memcpy(pBuf, (char *)&GpSysStat->VFD.FanVfd_Model, 2);
			   break;
		
		
        case 200:          //主机累计用电                                                  
         	memcpy(pBuf, (char *)&GpSysStat->Main.Power_Consume_Total, 4);
			*pLen = 4;
            break;
		case 202:           //风机累计用电                                                   
         	memcpy(pBuf, (char *)&GpSysStat->Fan.Power_Consume_Total, 4);
			*pLen = 4;
            break;
		case 204:           //工频主机累计用电                                                  
         	memcpy(pBuf, (char *)&GpSysStat->Main.Pfreq_Power_Consume_Total, 4);
			*pLen = 4;
            break;
		case 206:           //工频风机累计用电                                                  
         	memcpy(pBuf, (char *)&GpSysStat->Fan.Pfreq_Power_Consume_Total, 4);
			*pLen = 4;
            break;
        case 436:   /* 整机累计用电    */
        	if (GpSysPara->Dev.Bits.PS != PS_HC && GpSysStat->MeterData.Volt_AB != 0)
        	{
        	/*
        		GpSysStat->Share.Total_Power = GpSysStat->Fan.Power_Consume_Total + \
        						GpSysStat->Fan.Pfreq_Power_Consume_Total + \
        						GpSysStat->Main.Power_Consume_Total + \
        						GpSysStat->Main.Pfreq_Power_Consume_Total;
        	*/
        		GpSysStat->Share.Total_Power = GpSysStat->MeterData.Positive_Active_Power * GpSysStat->MeterData.CT / 100;
        	}
        	else 
        	{
        				GpSysStat->Share.Total_Power = GpSysStat->Fan.Power_Consume_Total + \
							GpSysStat->Fan.Pfreq_Power_Consume_Total + \
							GpSysStat->Main.Power_Consume_Total + \
							GpSysStat->Main.Pfreq_Power_Consume_Total;
        	}
        	memcpy(pBuf, (char *)&GpSysStat->Share.Total_Power, 4);
			*pLen = 4;
        	break;
		case 208:           //前轴承温度                                                  
         	memcpy(pBuf, (char *)&GpSysStat->Share.Front_Bear_Temp, 2);
            break;
		case 209:          	//后轴承温度                                                  
         	memcpy(pBuf, (char *)&GpSysStat->Share.Rear_Bear_Temp, 2);
			break;
		
		case 2000:          //  历史运行时间                                         
         	memcpy(pBuf, (char *)&GpSysStat->Run.RunHour, 2);
			break;
		
		case 1998:			//	历史运行时间分钟
			memcpy(pBuf, (char *)&GpSysStat->Run.RunMinute, 2);
			break;
		
		case 2002:          //  历史负载时间                                               
         	memcpy(pBuf, (char *)&GpSysStat->Run.LoadHour, 2);
			break;
		
		case 1999:			//	历史负载时间分钟
			memcpy(pBuf, (char *)&GpSysStat->Run.LoadMinute, 2);
			break;

		case 2004:          //  油滤器使用时间                                              
         	memcpy(pBuf, (char *)&GpSysStat->Run.OilFiltHour, 2);
			break;
		case 2005:          //  油分器使用时间                                              
         	memcpy(pBuf, (char *)&GpSysStat->Run.OilSepaHour, 2);
			break;
		case 2006:          //  空滤器使用时间                                              
         	memcpy(pBuf, (char *)&GpSysStat->Run.GasFiltHour, 2);
			break;
		case 2007:          //  润滑油使用时间                                             
         	memcpy(pBuf, (char *)&GpSysStat->Run.lubeHour, 2);
			break;
		case 2008:         //  润滑脂使用时间                                              
         	memcpy(pBuf, (char *)&GpSysStat->Run.GreaseHour, 2);
			break;
		case 2009:
			memcpy(pBuf, (char *)&GpSysStat->Run.BeltHour, 2);
			break;
		case 2100:          //                                                
         	memcpy(pBuf, (char *)&GpUsrPara->Hour.MaxUseTime, 2);
			break;
		case 2102:          //  油滤器最大时间      
			if ((GpSysPara->Dev.Bits.PS != 111)  )
         	{
         		memcpy(pBuf, (char *)&GpUsrPara->Hour.MaxOilFiltTime, 2);
         	}
         	else
         	{
         		ret = FALSE;
         	}
			break;
		case 2103:          //  油分器最大时间 
			if ((GpSysPara->Dev.Bits.PS != 111) )
         	{
         		memcpy(pBuf, (char *)&GpUsrPara->Hour.MaxOilSepaTime, 2);
         	}
         	else
         	{
         		ret = FALSE;
         	}
			break;
		case 2104:          //  空滤器最大时间   
		if ((GpSysPara->Dev.Bits.PS != 111)  )
         	{
         		memcpy(pBuf, (char *)&GpUsrPara->Hour.MaxGasFiltTime, 2);
         	}
         	else
         	{
         		ret = FALSE;
         	}
			break;
		case 2105:          //  润滑油最大时间    
			if ((GpSysPara->Dev.Bits.PS != 111) )
         	{
         	memcpy(pBuf, (char *)&GpUsrPara->Hour.MaxlubeTime, 2);
         	}
         	else
         	{
         		ret = FALSE;
         	}
			break;
		case 2106:          //  润滑脂最大时间      
		if ((GpSysPara->Dev.Bits.PS != 111) )
         	{
         		memcpy(pBuf, (char *)&GpUsrPara->Hour.MaxGreaseTime, 2);
         	}
         	else
         	{
         		ret = FALSE;
         	}
			break;
		
		case 2107:          //卸载压力           
		   memcpy(pBuf, (char *)&GpSysStat->Share.UnLoadPress, 2);
		   break;
				
		case 2108:          //加载压力         
		   memcpy(pBuf, (char *)&GpSysStat->Share.LoadPress, 2);
		   break;

		case 2109:          //目标压力	  
			memcpy(pBuf, (char *)&GpSysStat->Main.Cfreq_Press, 2);
			  break;
		case 2110:          //停机压力
		   memcpy(pBuf, (char *)&GpSysStat->Share.StopPress, 2);
		   break;
	
		case 2111:          //卸载高限 
		   memcpy(pBuf, (char *)&GpSysStat->Share.MaxUnloadPress, 2);
		   break;
				
		case 2112:          //停止温度
		   memcpy(pBuf, (char *)&GpSysStat->Fan.StopTemp, 2);
		   break;

		case 2113:          //启动温度
		   memcpy(pBuf, (char *)&GpSysStat->Fan.StartTemp, 2);
		   break;
		case 2114:          //目标温度
		   memcpy(pBuf, (char *)&GpSysStat->Fan.Cfreq_Temp, 2); 
		   break;				
		case 2115:          //预警温度
		   memcpy(pBuf, (char *)&GpSysStat->Fan.PreAlmTemp, 2);
		   break;
				
		case 2116:          //停机温度
		   memcpy(pBuf, (char *)&GpSysStat->Fan.AlmTemp, 2);
		   break;
							
				
		case 2118:          //重启延时
		   memcpy(pBuf, (char *)&GpSysStat->Share.StartDelay, 2);
		   break;
		
		
		case 2119:          //加载延时
		   memcpy(pBuf, (char *)&GpSysStat->Share.LoadDelay, 2);
		   break;
		
		case 2120:          //空载延时
		   memcpy(pBuf, (char *)&GpSysStat->Share.UnloadDelay, 2);
		   break;
		
		case 2121:          //停机延时
		   memcpy(pBuf, (char *)&GpSysStat->Share.StopDelay, 2);
		   break;
		
		
		case 2326:          //主额流
		   memcpy(pBuf, (char *)&GpSysStat->Main.RateCurrent, 2);
		   break;
		case 2328:          //主机延时
			memcpy(pBuf, (char *)&GpSysStat->Share.MainDelay, 2);  
			break;
		case 2329:          //星角延时
			memcpy(pBuf, (char *)&GpSysStat->Share.XinJiaoDelay, 2);
			break;
		
		case 2366:          //风额流 
		   memcpy(pBuf, (char *)&GpSysStat->Fan.RateCurrent, 2);
		   break;
		case 2327:          //电流不平衡度
		   memcpy(pBuf, (char *)&GpSysStat->Share.UnblanceCurrent, 2);
		   break;
		case 2368:          //风机延时
		   memcpy(pBuf, (char *)&GpSysStat->Share.FanDelay, 2);
		   break;
				
		
		case 3000:          //用户密码 
		   memcpy(pBuf, (char *)&GpSysStat->Share.UsrPassword , 10);
		   *pLen = 10;
           *pType = ADDR_TYPE_STRING;
		   break;
		case 3005:          //厂家密码 
		   memcpy(pBuf, (char *)&GpSysStat->Share.FacPassword, 10);
		   *pLen = 10;
           *pType = ADDR_TYPE_STRING;
		   break;
		case 14:  //
			memcpy(pBuf, (char *)&GpSysStat->Share.Pressure2, 2);
			break;
		case 15:  //
			memcpy(pBuf, (char *)&GpSysStat->Share.Pressure3, 2);
			break;
		case 17:
			memcpy(pBuf, (char *)&GpSysStat->Share.Temprature2, 2);
			break;
		case 16:
			memcpy(pBuf, (char *)&GpSysStat->OtherData.ValveState, 2);
			break;
		case 231:
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainIGBTemp, 2);
			break;
		case 2010:
			memcpy(pBuf, (char *)&GpSysStat->Run.WaterFiltHour, 2);
			break;
		case 2012:
			memcpy(pBuf, (char *)&GpUsrPara->Hour.MaxWaterFiltTime, 2);
			break;
		case 2460: 
			memcpy(pBuf, (char *)&GpSysStat->OtherData.LowWaterProtectTime, 2);
			break;
		case 2461: 
			memcpy(pBuf, (char *)&GpSysStat->OtherData.AutoChangeWaterActTime, 2);
			break;
		case 2462: 
			memcpy(pBuf, (char *)&GpSysStat->OtherData.AutoChangeWaterCycle, 2);
			break;
		case 2470: 
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MaxUseTimeFunc, 2);
			break;
		case 9010:
			memcpy(pBuf, (char *)&GpSysStat->OtherData.RunStatus, 2);
			break;
		case 9020:
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FaultStatus1, 2);
			break;
		case 9021:
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FaultStatus2, 2);
			break;
		case 9022:
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FaultStatus3, 2);
			break;
		case 9023:
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FaultStatus4, 2);
			break;
        default:           
            ret =  FALSE;
    }  

    return ret;
}


char    PltMam6080OtherVarRead(u16 Addr, char *pBuf, u16 *pLen, ADDR_TYPE_ENUM *pType)
{
    *pLen = 2;
    *pType = ADDR_TYPE_OTHER;  
    
    switch(Addr) 
	{  
					
		case 210:         // 系统压力
			memcpy(pBuf, (char *)&GpSysStat->OtherData.SysPressure, 2);
			break;				
		case 211:         // 相序保护电压
			memcpy(pBuf, (char *)&GpSysStat->OtherData.PhaseProVolt, 2);
			break;
		case 212:         // 缺相保护电压
			memcpy(pBuf, (char *)&GpSysStat->OtherData.OpenPhaseProVolt, 2);
			break;
		case 213:         // 电压
			memcpy(pBuf, (char *)&GpSysStat->OtherData.Volt, 2);
			break;
		case 214:         // 预警值
			memcpy(pBuf, (char *)&GpSysStat->OtherData.WarningValue, 2);
			break;
		case 215:         // 运行状态
			memcpy(pBuf, (char *)&GpSysStat->OtherData.RunStatus, 2);
			break;		
		case 216:         // 计时
			memcpy(pBuf, (char *)&GpSysStat->OtherData.Timing, 2);
			break;				
		case 217:         // 故障
			memcpy(pBuf, (char *)&GpSysStat->OtherData.Fault, 2);
			break;
		case 218:         // 故障值
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FaultValue, 2);
			break;
		case 219:         // 油分压差
			memcpy(pBuf, (char *)&GpSysStat->OtherData.OilPressDif, 2);
			break;
		case 220:         // 主机状态字
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainStatus, 2);
			break;
		case 221:         // 主机故障字
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainFault, 2);
			break;
		case 222:         // 风机状态字
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanStatus, 2);
			break;				
		case 223:         // 风机故障字
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanFault, 2);
			break;
		
		case 224:         // 工频主机本次用电
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainPfreqPowerThis, 4);
			*pLen = 4;
			break;
		case 226:         // 工频风机本次用电
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanPfreqPowerThis, 4);
			*pLen = 4;
			break;
		case 228:         // 工频主机UI
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainPfreqUI, 4);
			*pLen = 4;
			break;
		case 230:         // 工频风机UI
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanPfreqUI, 4);
			*pLen = 4;
			break;
		
		
		case 2138:         // 温度单位
			memcpy(pBuf, (char *)&GpSysStat->OtherData.TempUnit, 2);
			break;				
		case 3239:         // 压力单位
			memcpy(pBuf, (char *)&GpSysStat->OtherData.PressureUnit, 2);
			break;
		case 2140:         // 预警过久停机
			memcpy(pBuf, (char *)&GpSysStat->OtherData.WarningStop, 2);
			break;
		case 2141:         // 前轴承预警温度
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FrontBearingWarnTemp, 2);
			break;
		case 2142:         // 前轴承报警温度
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FrontBearingAlarmTemp, 2);
			break;
		case 2143:         // 油分预警压差
			memcpy(pBuf, (char *)&GpSysStat->OtherData.OilPressDifWarn, 2);
			break;
		case 2144:         // 油分报警压差
			memcpy(pBuf, (char *)&GpSysStat->OtherData.OilPressDifAlarm, 2);
			break;	
		
		case 2147:         // 排水开延时
			memcpy(pBuf, (char *)&GpSysStat->OtherData.DrainOpenDelay, 2);
			break;
		case 2148:         // 排水关延时
			memcpy(pBuf, (char *)&GpSysStat->OtherData.DrainCloseDelay, 2);
			break;
		case 2149:         // 软启延时
			memcpy(pBuf, (char *)&GpSysStat->OtherData.SoftStartDelay, 2);
			break;
		case 2150:         // 辅助启动时间
			memcpy(pBuf, (char *)&GpSysStat->OtherData.AssistStartTime, 2);
			break;
		case 2151:         // 辅助加载延时
			memcpy(pBuf, (char *)&GpSysStat->OtherData.AssistLoadDelay, 2);
			break;
		case 2152:         // 辅助卸载延时
			memcpy(pBuf, (char *)&GpSysStat->OtherData.AssistUnloadDelay, 2);
			break;				
		case 2153:         // 辅助启温度
			memcpy(pBuf, (char *)&GpSysStat->OtherData.AssistStartTemp, 2);
			break;
		case 2154:         // 加载方式
			memcpy(pBuf, (char *)&GpSysStat->OtherData.LoadMode, 2);
			break;
		case 2155:         // 启停方式
			memcpy(pBuf, (char *)&GpSysStat->OtherData.StartStopMode, 2);
			break;
		case 2156:         // 通信方式
			memcpy(pBuf, (char *)&GpSysStat->OtherData.CorrespondMode, 2);
			break;
		case 2157:         // 语言选择
			memcpy(pBuf, (char *)&GpSysStat->OtherData.LanguageSelection, 2);
			break;
		case 2158:         // 运行方式
			memcpy(pBuf, (char *)&GpSysStat->OtherData.RunMode, 2);
			break;				
		case 2159:         // 系统停机压力
			memcpy(pBuf, (char *)&GpSysStat->OtherData.SysStopPressure, 2);
			break;
		case 2160:         // 历史故障复位
			memcpy(pBuf, (char *)&GpSysStat->OtherData.HistoryFaultReset, 2);
			break;
		case 2161:         // 出厂编码1
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FactoryCode1, 2);
			break;
		case 2162:         // 出厂编码2
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FactoryCode2, 2);
			break;
		case 2163:         // 出厂日期
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FactoryDate, 2);
			break;
		
		
		
		case 2380:         // 主机积分初值
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainIntegInitValue, 2);
			break;				
		case 2381:         // 主机积分范围
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainIntegRange, 2);
			break;
		case 2382:         // 主机比例增益
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainRatioGain, 2);
			break;
		case 2383:         // 主机积分增益
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainIntegGain, 2);
			break;
		case 2384:         // 主机微分增益
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainDiffGain, 2);
			break;
		case 2385:         // 主机频率上限
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainFreqToplimit, 2);
			break;
		case 2386:         // 主机频率下限
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainFreqLowlimit, 2);
			break;				
		case 2387:         // 主机空载频率
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainIdlingFreq, 2);
			break;
		case 2388:         // 主机变频器站号
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainVfdNum, 2);
			break;
		case 2389:         // 主机PID周期
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainPIDPeriod, 2);
			break;
		case 2390:         // 主机变频器型号
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainVfdModel, 2);
			break;
		case 2391:         // 风机积分初值
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanIntegInitValue, 2);
			break;
		case 2392:         // 风机积分范围
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanIntegRange, 2);
			break;				
		case 2393:         // 风机比例增益
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanRatioGain, 2);
			break;
		case 2394:         // 风机积分增益
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanIntegGain, 2);
			break;
		case 2395:         // 风机微分增益
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanDiffGain, 2);
			break;
		case 2396:         // 风机频率上限
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanFreqToplimit, 2);
			break;
		case 2397:         // 风机频率下限
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanFreqLowlimit, 2);
			break;
		case 2398:         // 风机空载频率
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanIdlingFreq, 2);
			break;				
		case 2399:         // 风机变频器站号
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanVfdNum, 2);
			break;
		case 2400:         // 风机PID周期
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanPIDPeriod, 2);
			break;
		case 2401:         // 风机变频器型号
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanVfdModel, 2);
			break;
		case 2128:         // 电压过高
			memcpy(pBuf, (char *)&GpSysStat->OtherData.VoltOvertop, 2);
			break;
		case 2129:         // 电压过低
			memcpy(pBuf, (char *)&GpSysStat->OtherData.VoltOverlow, 2);
			break;
		case 2404:         // 通信超时
			memcpy(pBuf, (char *)&GpSysStat->OtherData.CorrespondOverTime, 2);
			break;


		
		case 2420:         // 降频压力
			memcpy(pBuf, (char *)&GpSysStat->OtherData.ReFreqPressure, 2);
			break;
		case 2421:         // 主机上升速率
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainRiseRate, 2);
			break;
		case 2422:         // 主机下降速率
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainDownRate, 2);
			break;
		case 2423:         // 主机功率
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainPower, 2);
			break;
		case 2424:         // 主机转速
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainRotationRate, 2);
			break;
		case 2425:         // 风机上升速率
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanRiseRate, 2);
			break;				
		case 2426:         // 风机下降速率
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanDownRate, 2);
			break;
		case 2427:         // 风机功率
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanPower, 2);
			break;
		case 2428:         // 风机转速
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanRotationRate, 2);
			break;
		case 2429:         // 变频风机启
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanFreqStart, 2);
			break;
		case 2430:         // 变频风机停
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanFreqStop, 2);
			break;
		case 2431:         // 主机停机方式
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainStopMode, 2);
			break;				
		case 2432:         // 定时启停功能
			memcpy(pBuf, (char *)&GpSysStat->OtherData.TimeStartStopFunc, 2);
			break;
		case 2433:         // 定时压力功能
			memcpy(pBuf, (char *)&GpSysStat->OtherData.TimePressureFunc, 2);
			break;
		case 2117:         // 低温保护
			memcpy(pBuf, (char *)&GpSysStat->OtherData.LowTempProtect, 2);
			break;
		case 2435:         // 主变频器启动方式
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainVfdStartMode, 2);
			break;
		case 2436:         // 风机变频器启动方式
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanVfdStartMode, 2);
			break;
		case 2437:         // 通信启变频器次数
			memcpy(pBuf, (char *)&GpSysStat->OtherData.CorrespondStartVfdNum, 2);
			break;				
		case 2438:         // 通信停变频器次数
			memcpy(pBuf, (char *)&GpSysStat->OtherData.CorrespondStopVfdNum, 2);
			break;
		
		case 2450:         // 工频主机功率系数
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainPfreqPowerFactor, 2);
			break;
		case 2451:         // 变频主机功率系数
			memcpy(pBuf, (char *)&GpSysStat->OtherData.MainfreqPowerFactor, 2);
			break;
		case 2452:         // 变频风机功率系数
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanPfreqPowerFactor, 2);
			break;
		case 2453:         // 工频风机功率系数
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FanfreqPowerFactor, 2);
			break;
		case 2454:         // 预开主机变频器延时
			memcpy(pBuf, (char *)&GpSysStat->OtherData.ProMainVfdDelay, 2);
			break;				
		case 2455:         // 掉电重启功能
			memcpy(pBuf, (char *)&GpSysStat->OtherData.PowerDownRestart, 2);
			break;
		case 2456:         // 频率选择
			memcpy(pBuf, (char *)&GpSysStat->OtherData.FreqSelect, 2);
			break;
		case 2457:         // 管路压阻
			memcpy(pBuf, (char *)&GpSysStat->OtherData.PipePressure, 2);
			break;
		case 2458:         // 后轴承预警温度
			memcpy(pBuf, (char *)&GpSysStat->OtherData.RearBearingWarnTemp, 2);
			break;
		case 2459:         // 后轴承停机温度
			memcpy(pBuf, (char *)&GpSysStat->OtherData.RearBearingAlarmTemp, 2);
			break;		
		
        default:           
            return FALSE;
    }  

    return TRUE;
}

bool PltSysVarWriter(u16 Addr, char *Pbuf)
{
    double data_fp = 0.0;
	u32 data_int;
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
		if((ptmp[i].Key_Value == Addr) &&(ptmp[i].WriterFlag == W_T))
		{		
			switch(ptmp[i].DataType) 
			{
				case Str:   
					 data_int = my_atoi(Pbuf);
					 break; 

				case Int:      
					 data_int = my_atoi(Pbuf);
					 break;	
					 
				case Flo:   
					 data_fp = my_atof(Pbuf);					
					 if(ptmp[i].DecNum==Dec1) 
					 {
						data_int = (data_fp+0.01)*10;
					 } 
					 else if(ptmp[i].DecNum==Dec2) 
					 {
						data_int = (data_fp+0.001)*100;	
					 } 
					 else if(ptmp[i].DecNum==Dec3) 
					 {
						data_int = (data_fp+0.0001)*1000;
					 } 
					 else if(ptmp[i].DecNum==Dec4) 
					 {
						data_int = (data_fp+0.00001)*10000;
					 }
					 else 
					 {					
					 }
					 break;
				case Hex:      
					 data_int = my_atoi(Pbuf);
					 break;	
				case Bit:      
					 data_int = my_atoi(Pbuf);
					 break;	
				default:
			//		 sprintf(&pBuf[strlen(pBuf)], "\"%d\":\"%d\",", Addr, Data);
					 break;
			}
			if (GpSysPara->Dev.Bits.PS != PS_HC)
			{
			if((ptmp[i].Key_Value == 2112) || (ptmp[i].Key_Value == 2113) || (ptmp[i].Key_Value == 2114) ||
			   (ptmp[i].Key_Value == 2115) || (ptmp[i].Key_Value == 2116) )
				{
					data_int /= 10;
				}	
			}
			Server_Writer_Data_Buf(ptmp[i].Addr,data_int,ptmp[i].DataLen);
		   if (GpSysPara->Dev.Bits.PS == PS_MAM860C_880C  || GpSysPara->Dev.Bits.PS == PS_MAM860_870_880)
			{
		 	  PltDevMan860DataPrase(i, data_int, GpSysPara->Dev.Bits.PS);
			}
			else if (GpSysPara->Dev.Bits.PS == PS_MAM6080_6090 || GpSysPara->Dev.Bits.PS == PS_MAM6090 || GpSysPara->Dev.Bits.PS == PS_MAM6070)
			{
				PltDevDataPrase(i, data_int, GpSysPara->Dev.Bits.PS);
			}
			else if (GpSysPara->Dev.Bits.PS == PS_HC)
			{
				PltDevH2UParse(i, data_int);
			}
			return TRUE;
		}		 
	}
	return FALSE;
}
	

#if MONITOR_METER_ON

char    XYMeterVarRead(u16 Addr, char *pBuf, u16 *pLen, ADDR_TYPE_ENUM *pType)
{
//	uint64_t Temp = 0;
	u32 Tmp32 = 0;
	char *pArr = NULL;
    *pLen = 2;
    *pType = ADDR_TYPE_OTHER;  
  	GpSysStat->MeterData.Line_Net = 1;  // 3P3L
	
    switch(Addr) {    
        case 400: 
			if(GpSysStat->MeterData.Line_Net & 0x00ff)  //  3P3L
			{
				memcpy(pBuf, (char *)&GpSysStat->MeterData.Volt_AB, 2); 
			}
			else  // 3P4L
			{
				memcpy(pBuf, (char *)&GpSysStat->MeterData.Volt_A, 2);  
			}
            break;	   
		case 401: 
			if(GpSysStat->MeterData.Line_Net & 0x00ff)  //  3P3L
			{
				memcpy(pBuf, (char *)&GpSysStat->MeterData.Volt_BC, 2); 
			}
			else  // 3P4L
			{
				memcpy(pBuf, (char *)&GpSysStat->MeterData.Volt_B, 2);  
			}
            break;
		case 402: 
			if(GpSysStat->MeterData.Line_Net & 0x00ff)  //  3P3L
			{
				memcpy(pBuf, (char *)&GpSysStat->MeterData.Volt_CA, 2); 
			}
			else  // 3P4L
			{			
				memcpy(pBuf, (char *)&GpSysStat->MeterData.Volt_C, 2);	
			}
            break;
		case 403: 
			memcpy(pBuf, (char *)&GpSysStat->MeterData.Current_A, 2);  
            break;	   
		case 404: 
			memcpy(pBuf, (char *)&GpSysStat->MeterData.Current_B, 2);  
            break;
		case 405: 
			memcpy(pBuf, (char *)&GpSysStat->MeterData.Current_C, 2);  
            break;	
		case 406: 
			memcpy(pBuf, (char *)&GpSysStat->MeterData.Active_Power_Total, 4);  
			*pLen = 4;
            break;	   
		case 407: 
			memcpy(pBuf, (char *)&GpSysStat->MeterData.Reactive_Power_Total, 4); 
			*pLen = 4;
            break;
		case 408: 
			memcpy(pBuf, (char *)&GpSysStat->MeterData.Apparent_Power_Total, 4);  
			*pLen = 4;
            break;
		case 409: 
			memcpy(pBuf, (char *)&GpSysStat->MeterData.Power_Factor_Total, 2);  
            break;	   
		case 410: 
			memcpy(pBuf, (char *)&GpSysStat->MeterData.Frequency, 2);  
            break;
		case 411:
		{ 
//			Temp +=GpSysStat->MeterData.Positive_Active_Power*100;
//			Temp =(u64)GpSysStat->MeterData.Positive_Active_Power*100 + GpSysStat->MeterData.Positive_Active_Power_Dec/10;
			memcpy(pBuf, (char *)&GpSysStat->MeterData.Positive_Active_Power, 4); 
			*pLen = 4;
			*pType = ADDR_TYPE_OTHER;  		

            break;
		}	
		
		case 415://电表站号
		{
			memcpy(pBuf, (char *)&GpSysPara->Dev.MeterNum, 2);         
			break;
		}
		
		
		case 420://瞬时流量
		{
			// fengyang 2018-4-10 10:52:01
			//Tmp32 = GpSysStat->FlowData.Transient_Flow.F_Data * 100;
			pArr = GpSysStat->FlowData.Transient_Flow.Array;
			memcpy(pBuf, pArr, 4);   
			*pLen = 4;
			*pType = ADDR_TYPE_OTHER; 
			break;
		}
		case 422://频率
		{
//			Tmp32 = GpSysStat->FlowData.Frequency.F_Data * 100;
//			memcpy(pBuf, (char *)&Tmp32, 4);   
			pArr = GpSysStat->FlowData.Frequency.Array;
			memcpy(pBuf, pArr, 4);
			*pLen = 4;
			*pType = ADDR_TYPE_OTHER; 
			break;
		}
		case 424://压力
		{
//			Tmp32 = GpSysStat->FlowData.Pressure.F_Data * 100;
//			memcpy(pBuf, (char *)&Tmp32, 4);   
			pArr = GpSysStat->FlowData.Pressure.Array;
			memcpy(pBuf, pArr, 4);
			*pLen = 4;
			*pType = ADDR_TYPE_OTHER; 
			break;
		}
		case 426://温度
		{
//			Tmp32 = GpSysStat->FlowData.Temp.F_Data * 10;
//			memcpy(pBuf, (char *)&Tmp32, 4);   
			pArr = GpSysStat->FlowData.Temp.Array;
			memcpy(pBuf, pArr, 4);
			*pLen = 4;
			*pType = ADDR_TYPE_OTHER; 
			break;
		}
		case 428://密度
		{
//			Tmp32 = GpSysStat->FlowData.Density.F_Data * 100;
//			memcpy(pBuf, (char *)&Tmp32, 4);   
			pArr = GpSysStat->FlowData.Density.Array;
			memcpy(pBuf, pArr, 4);
			*pLen = 4;
			*pType = ADDR_TYPE_OTHER; 
			break;
		}
		case 430://累计流量
		{
//			Tmp32 = GpSysStat->FlowData.Total_Flow.F_Data * 100;
//			memcpy(pBuf, (char *)&Tmp32, 4); 
			pArr = GpSysStat->FlowData.Total_Flow.Array;
			memcpy(pBuf, pArr, 4);			
			*pLen = 4;
			*pType = ADDR_TYPE_OTHER; 
			break;
		}
		case 432://流量计站号
		{
			memcpy(pBuf, (char *)&GpSysPara->Dev.FlowNum, 2);      
			break;
		}
		
		case 433://比功率
		{
			Tmp32 = GpSysStat->FlowData.Specific_Power * 100;
			memcpy(pBuf, (char *)&Tmp32, 4);   
			*pLen = 4;
			*pType = ADDR_TYPE_OTHER; 
			break;
		}
		case 435://单位能耗
		{
			Tmp32 = GpSysStat->FlowData.Energy_Unit * 100;
			memcpy(pBuf, (char *)&Tmp32, 4);   
			*pLen = 4;
			*pType = ADDR_TYPE_OTHER; 
			break;
		}
		
        default:           
            return FALSE;
    }  

    return TRUE;
}
#endif
/*
void    PltUsrHourAlarmCheck(void)
{
    char Flag;

    if(PS_MAM860C_880C != GpSysPara->Dev.Bits.PS) {
        return;
    }

    Flag = FALSE;
    if(GpUsrPara->Hour.MaxOilFiltTime) {
        if(GpSysStat->Run.OilFiltHour >= GpUsrPara->Hour.MaxOilFiltTime) {
            Flag = TRUE;
        }
    }
    AlmStat.PreAlarm.Bits.OverMaxOilFiltTime = Flag; 

    Flag = FALSE;
    if(GpUsrPara->Hour.MaxOilSepaTime) {
        if(GpSysStat->Run.OilSepaHour >= GpUsrPara->Hour.MaxOilSepaTime) {
            Flag = TRUE;
        }
    }
    AlmStat.PreAlarm.Bits.OverMaxOilSepaTime = Flag;

    Flag = FALSE;
    if(GpUsrPara->Hour.MaxGasFiltTime) {
        if(GpSysStat->Run.GasFiltHour >= GpUsrPara->Hour.MaxGasFiltTime) {
            Flag = TRUE;
        }
    }
    AlmStat.PreAlarm.Bits.OverMaxGasFiltTime = Flag;  

    Flag = FALSE;
    if(GpUsrPara->Hour.MaxlubeTime) {
        if(GpSysStat->Run.lubeHour >= GpUsrPara->Hour.MaxlubeTime) {
            Flag = TRUE;
        }
    }
    AlmStat.PreAlarm.Bits.OverMaxlubeTime = Flag;  

    Flag = FALSE;
    if(GpUsrPara->Hour.MaxGreaseTime) {
        if(GpSysStat->Run.GreaseHour>= GpUsrPara->Hour.MaxGreaseTime) {
            Flag = TRUE;
        }
    }
    AlmStat.PreAlarm.Bits.OverMaxGreaseTime = Flag;  
}
*/

u16 PltTestData;
bool    PltAlowWrite = FALSE;


extern bool g_b2mintues;
void  PltDevH2UParse(u16 Index, u16 Data)
{
	static  u32  tmp;
	static  u16 LastMachineStat = STATUS_UNKNOW;
	//static  u16 LastMachineStat = STATUS_UNKNOW;
    switch(Index) {
        case H2U_PRESSURE:
            GpSysStat->Share.Pressure1 = Data;                      //  2位小数点,已扩大100倍                
            break;
        case H2U_TEMPERATURE:
      		 GpSysStat->Share.Temprature1 = Data * 10;
             break;
        case H2U_PWR_VOLT:
			GpSysStat->Share.PowerVolt = Data;
        	break;
        case H2U_RUNSTATE:
        	GpSysStat->OtherData.RunStatus = Data;
        	
        	switch (Data)
        	{
        		case 1:
        		case 6:
        		case 7:
        		case 17:
        		case  18:
        		 GpSysStat->Share.MachineStat = STOP_STATE; //停机
        		 break;
        		case 19:
        		tmp = MACHINE_ALARM;  //报警
        		break;
        		case 3:
        		case 13:
        			GpSysStat->Share.MachineStat = JIA_ZAI_RUN_STATE; //加载运行
        			break;
        		case 12:
        			GpSysStat->Share.MachineStat = KONG_ZAI_RUN_STATE; //空载运行
        			break;
        		case 4:
        			GpSysStat->Share.MachineStat = KONG_JIU_STOP_STATE; //空久休眠
        			break;
        		default:
        			break;
        	}
        	if (GpSysStat->Share.MachineStat != LastMachineStat)
        	{

        		LastMachineStat = GpSysStat->Share.MachineStat;    		
        		GpSysStat->Share.MachineStat = tmp;
        		GpSysStat->Share.UpdataParaFlag |= (1<<3);
				ParaUpdate.val |= (1<<3);
        	}
        
        	break;
        case H2U_P2PRESSURE:
        	GpSysStat->Share.Pressure2 =Data;
        	break;
        case H2U_P3PRESSURE:
        	GpSysStat->Share.Pressure3 = Data;
        	break;
        case H2U_TEMPERATURE1:
        	GpSysStat->Share.Temprature2 = Data*10;
        	break;
        case H2U_FAN_CURRENTA:
        	GpSysStat->Fan.A_Current = Data;
        	break;
        case H2U_FAN_CURRENTB:
        	GpSysStat->Fan.B_Current = Data;
        	break;
        case H2U_FAN_CURRENTC:
        	GpSysStat->Fan.C_Current = Data;
        	break;
        case H2U_MAIN_OUT_FREQ:
        	GpSysStat->Main.OutFreq = Data;
        	break;
        case H2U_MAIN_OUT_CURR:
        	GpSysStat->Main.OutCurrent = Data;
        	break;
        case H2U_MAIN_OUT_VOLT:
        	GpSysStat->Main.OutVolt = Data;
        	break;
        case H2U_MAIN_OUT_POWER:
        	GpSysStat->Main.OutPower = Data;
        	break;
        case H2U_FAN_OUT_FREQ:
        	GpSysStat->Fan.OutFreq = Data;
        	break;
        case H2U_FAN_OUT_CURR:
        	GpSysStat->Fan.OutCurrent = Data;
        	break;
        case H2U_FAN_OUT_VOLT:
        	GpSysStat->Fan.OutVolt = Data;
        	break;
        case H2U_FAN_OUT_POWER:
        	GpSysStat->Fan.OutPower = Data;
        	break;
        case H2U_RUN_TIME:
			if(GpSysStat->Run.RunHour != Data)
			{
				GpSysStat->Run.RunHour = Data; 
			}
            break;
        case H2U_LOAD_TIME:          
			if(GpSysStat->Run.LoadHour != Data)
			{
				GpSysStat->Run.LoadHour = Data;  
			}
            break;
		case H2U_CURRENT_RUNTIME:
				if(GpSysStat->Run.CurrentRunHour != Data)
			{
				GpSysStat->Run.CurrentRunHour = Data;  
			}
			break;
		case H2U_CURRENT_RUNMINUTE:
			if(GpSysStat->Run.CurrentRunMinute != Data)
			{
				GpSysStat->Run.CurrentRunMinute = Data;  
			}
			break;
		case H2U_WATERFILT_TIME:
			if (GpSysStat->Run.WaterFiltHour != Data)
			{
				GpSysStat->Run.WaterFiltHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}
			break;
		case H2U_GASFILT_TIME:
			if (GpSysStat->Run.GasFiltHour != Data)
			{
				GpSysStat->Run.GasFiltHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}
			break;	

		case H2U_MAX_USE_TIME:
			if (GpUsrPara->Hour.MaxUseTime != Data)
			{
				GpUsrPara->Hour.MaxUseTime = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_WATERFILT_MAX_HOUR:
			if (GpUsrPara->Hour.MaxWaterFiltTime != Data)
			{
				GpUsrPara->Hour.MaxWaterFiltTime = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}
			break;
		case H2U_GASFILT_MAX_HOUR:
			if (GpUsrPara->Hour.MaxGasFiltTime != Data)
			{
				GpUsrPara->Hour.MaxGasFiltTime = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}
			break;
		case H2U_UNLOAD_PRESS:
			if (GpSysStat->Share.UnLoadPress != Data)
			{
				GpSysStat->Share.UnLoadPress = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
			break;
		case H2U_LOAD_PRESS:
			if (GpSysStat->Share.LoadPress != Data)
			{
				GpSysStat->Share.LoadPress = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
			break;			
		case H2U_MAIN_CFREQ_PRESS:	
			if (GpSysStat->Main.Cfreq_Press != Data)
			{
				 GpSysStat->Main.Cfreq_Press = Data;
				 GpSysStat->Share.UpdataParaFlag |= 0x0002;
			 }
			break;	
		case  H2U_STOP_PRESS:
			if (GpSysStat->Share.StopPress != Data)
			{
				 GpSysStat->Share.StopPress = Data;
				 GpSysStat->Share.UpdataParaFlag |= 0x0002;
			 }		
			break;
		case H2U_UNLOAD_MAX_PRESS:
			if (GpSysStat->Share.MaxUnloadPress != Data)
			{
				GpSysStat->Share.MaxUnloadPress = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_FAN_STOP_TEMP:
			if (GpSysStat->Fan.StopTemp != Data)
			{
				GpSysStat->Fan.StopTemp = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_FAN_START_TEMP:
			if (GpSysStat->Fan.StartTemp != Data)
			{
				GpSysStat->Fan.StartTemp = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_FAN_CFREQ_TEMP:
			if (GpSysStat->Fan.Cfreq_Temp != Data)
			{
				GpSysStat->Fan.Cfreq_Temp = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case  H2U_PRALARM_TEMP:
			if (GpSysStat->Fan.PreAlmTemp != Data)
			{
				GpSysStat->Fan.PreAlmTemp = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_ALARM_TEMP:
			if (GpSysStat->Fan.AlmTemp != Data)
			{
				GpSysStat->Fan.AlmTemp = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_RUNMODE:
			switch (Data)
			{
				case 0:    //工频
				 tmp = 1;
				 break;
				case 1:
					tmp = 3;  
					break;
				default:
				break;
			}
			if( GpSysStat->OtherData.RunMode != tmp)
			{
				
GpSysStat->OtherData.RunMode = tmp;
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
			break;
		case H2U_TOTALPOWER_L:
			tmp= (u32)Data;
			break;
		case H2U_TOTALPOWER_H:
			tmp |= Data<<16;
			GpSysStat->Share.Total_Power = tmp;
			break;
		case H2U_LOWWATERPERTECT:
			if (GpSysStat->OtherData.LowWaterProtectTime != Data)
			{
				
GpSysStat->OtherData.LowWaterProtectTime = Data;	
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_AUTOCHANGEWATER:
			if (GpSysStat->OtherData.AutoChangeWaterActTime != Data)
			{
				
GpSysStat->OtherData.AutoChangeWaterActTime = Data;	
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_AUTOCHANGECYCLE:
			if (GpSysStat->OtherData.AutoChangeWaterCycle != Data)
			{
				
GpSysStat->OtherData.AutoChangeWaterCycle = Data;	
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_MAXTIMEFUNC:
			if (GpSysStat->OtherData.MaxUseTimeFunc != Data)
			{
				
GpSysStat->OtherData.MaxUseTimeFunc = Data;	
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_VALVE_STATE:
			if (GpSysStat->OtherData.ValveState != Data)
			{
				
GpSysStat->OtherData.ValveState = Data;	
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case H2U_MAIN_IGBT_TMP:
			if (GpSysStat->OtherData.MainIGBTemp != Data)
			{
				
GpSysStat->OtherData.MainIGBTemp = Data;	
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
			break;
		case  H2U_MAINVFD_ALARMDATA:
			GpSysStat->VFD.MainVfd_AlarmValue = Data;
			break;
		case H2U_FANVFD_ALARMDATA:
			GpSysStat->VFD.FanVfd_AlarmValue = Data;
			break;
		case H2U_FAULTSTATUS1:
			GpSysStat->OtherData.FaultStatus1 = Data;
			AlmStat.PreAlarm.Bits.OverMaxTemp = (Data & (1 << 0))  ? TRUE : FALSE; //温度预警	
		    AlmStat.Alarm.Bits.OverMaxTemp1   = (Data & (1 << 1)) ? TRUE : FALSE;  //温度超限
		    AlmStat.Alarm.Bits.OverMaxPres1 	= (Data & (1 << 2)) ? TRUE : FALSE;  //压力超限
		    AlmStat.Alarm.Bits.PresSen1Fault     = (Data & (1 << 3)) ? TRUE : FALSE;  //压力传感器故障
		    AlmStat.Alarm.Bits.TempSen1Fault     = (Data & (1 << 4)) ? TRUE : FALSE;  //温度传感器故障
			AlmStat.Alarm.Bits.OverMaxCurr	   = (Data & (1 << 15)) ? TRUE : FALSE;	//主机过流 
			break;
		case H2U_FAULTSTATUS2:	
			GpSysStat->OtherData.FaultStatus2 = Data;
			AlmStat.Alarm.Bits.LackPhase     = (Data & (1 << 0)) ? TRUE : FALSE;  //输入缺相  	
		    AlmStat.Alarm.Bits.OverMaxUsrHour =   (Data & (1 << 11)) ? TRUE : FALSE;	//超过使用时限
		    AlmStat.Alarm.Bits.PluseError     = (Data & (1 << 1)) ? TRUE : FALSE;  //相序错误
		    AlmStat.Alarm.Bits.MainVfdAlarm     = (Data & (1 << 2)) ? TRUE : FALSE;  //主机变频器故障 
			AlmStat.Alarm.Bits.FanVfdAlarm     = (Data & (1 << 9)) ? TRUE : FALSE;  //风机变频器故障	
		    AlmStat.Alarm.Bits.FanOverCurr     = (Data & (1 << 10) || Data & (1<<12)) ? TRUE : FALSE;  //风机过流
		    
			break;
		case H2U_FAULTSTATUS3:
			GpSysStat->OtherData.FaultStatus3 = Data;

			break;
		case H2U_FAULTSTATUS4:
			GpSysStat->OtherData.FaultStatus4 = Data;
		  AlmStat.Alarm.Bits.LackWater =   (Data & (1 << 2)) ? TRUE : FALSE;	//缺水故障
		  AlmStat.PreAlarm.Bits.WatarLevelHigh =(Data & (1 << 3)) ? TRUE : FALSE;	//水位高
		  AlmStat.PreAlarm.Bits.WaterLevelLow =(Data & (1 << 4)) ? TRUE : FALSE;	//水位低
		  AlmStat.PreAlarm.Bits.PipeBlock =(Data & (1 << 5)) ? TRUE : FALSE;	//水管堵塞
			break;
		case  H2U_ALLOW_WRITE:
			  PltAlowWrite =  TRUE;
			  break;
		default:
			break;
	}
}


void    PltDevDataPrase(u16 Index, u16 Data, u8 Type)
{
//    bool Flag = FALSE;
	static u16 Power_Consume_Total[4]={0};
	static  u16 LastMachineStat = STATUS_UNKNOW;
    switch(Index) {
        case PLT_PRESSURE:
            GpSysStat->Share.Pressure1 = Data;                      //  2位小数点,已扩大100倍                
            break;
        case PLT_TEMPERATURE:
            switch(Type) {
			
                case PS_MAM6080_6090:
				case PS_MAM6090:
				case PS_MAM6070:
                    GpSysStat->Share.Temprature1 = ((s16)(Data - 50)) * 10;
                    break;
				
                default:
                    GpSysStat->Share.Temprature1 = Data * 10;
                    break;
            }            
            break;
        case PLT_RUN_TIME:
			if(GpSysStat->Run.RunHour != Data)
			{
				GpSysStat->Run.RunHour = Data; 
			}
            break;
		
		case PLT_RUN_TIME_MINUTE:
			if(GpSysStat->Run.RunMinute != Data)
			{
				GpSysStat->Run.RunMinute = Data;  
			}
			break;
			
        case PLT_LOAD_TIME:          
			if(GpSysStat->Run.LoadHour != Data)
			{
				GpSysStat->Run.LoadHour = Data;  
			}
            break;
		
		case PLT_LOAD_TIME_MINUTE:
			if(GpSysStat->Run.LoadMinute != Data)
			{
				GpSysStat->Run.LoadMinute = Data; 
			}
			break;
        case PLT_CURRENT_A:
			if (StartFilterTimer == 0)  // 启动10s之后才读取电流
            {
           		 GpSysStat->Main.A_Current = Data;                       //  1位小数点,已扩大10倍
			}
			break;
        case PLT_CURRENT_B:
			if (StartFilterTimer == 0)  // 启动10s之后才读取电流
            {
           		 GpSysStat->Main.B_Current = Data;                       //  1位小数点,已扩大10倍
			}
            //GpSysStat->Main.B_Current = Data;                       //  1位小数点,已扩大10倍
            break;
        case PLT_CURRENT_C:
			if (StartFilterTimer == 0)  // 启动10s之后才读取电流
            {
           		 GpSysStat->Main.C_Current = Data;                       //  1位小数点,已扩大10倍
			}
           // GpSysStat->Main.C_Current = Data;                       //  1位小数点,已扩大10倍
            break;             
        case PLT_STATUS_1:
           GpSysStat->Share.AlmVal = Data;
            if(Data & (1 << 15)) 
			{
               // if(STOP_STATE == GpSysStat->Share.MachineStat) 
				//{
                //    AlmStat.Flag.Bits.Boot = TRUE;
                //    if(RmtBootTimer.Bits.Flag) 
				//	{
                //        RmtBootTimer.Val = 0;
                //        AlmStat.BootType = BOOT_TYPE_SERVER;                        
                //    } 
				//	else 
				//	{
               //         AlmStat.BootType = BOOT_TYPE_KEY;
                //    }
				//	AlmStat.DevAlarm.Bits.DevStartUp =TRUE;
               // }

				if(GpSysStat->Share.MachineStat != KONG_JIU_STOP_STATE)
				{
					if (GpSysStat->Share.MachineStat != STATUS_UNKNOW)
					{
						AlmStat.DevAlarm.Bits.DevDormancy =TRUE;
					}
					GpSysStat->Share.MachineStat = KONG_JIU_STOP_STATE;
				}
				GpSysStat->Share.RunState = RUN_STATE;
            } 
			else if(Data & (1 << 1)) 
			{
				GpSysStat->Share.RunState = RUN_STATE;
                if(STOP_STATE == GpSysStat->Share.MachineStat) 
				{
                    AlmStat.Flag.Bits.Boot = TRUE;
					StartFilterTimer = Start_FILTER_TIME;
                    if(RmtBootTimer.Bits.Flag) 
					{
                        RmtBootTimer.Val = 0;
                        AlmStat.BootType = BOOT_TYPE_SERVER;                        
                    } 
					else 
					{
                        AlmStat.BootType = BOOT_TYPE_KEY;
                    }
					AlmStat.DevAlarm.Bits.DevStartUp =TRUE;
                }
                if(Data & 0x01) 
				{
					if(GpSysStat->Share.MachineStat != JIA_ZAI_RUN_STATE)
					{
						GpSysStat->Share.MachineStat = JIA_ZAI_RUN_STATE;
						AlmStat.DevAlarm.Bits.LoadingRun =TRUE;
					}
                } 
				else 
				{
					if(GpSysStat->Share.MachineStat != KONG_ZAI_RUN_STATE)
					{
						GpSysStat->Share.MachineStat = KONG_ZAI_RUN_STATE;
						AlmStat.DevAlarm.Bits.IdlerRun =TRUE;
					}                   
                }
            } 
			else 
			{
				GpSysStat->Share.RunState = STOP_STATE;
                if(STOP_STATE != GpSysStat->Share.MachineStat)
				{
					if (STATUS_UNKNOW != GpSysStat->Share.MachineStat)
                   {
              			StopFilterTimer = STOP_FILTER_TIME;
	                   	AlmStat.Flag.Bits.Stop = TRUE;
	                    if(RmtStopTimer.Bits.Flag) 
						{
	                        RmtStopTimer.Val = 0;
	                        AlmStat.StopType = STOP_TYPE_SERVER;   
	                    } 
						else 
						{
	                        AlmStat.StopType = STOP_TYPE_KEY;
	                    }
						AlmStat.DevAlarm.Bits.DevStop =TRUE;
                	}
					GpSysStat->Share.MachineStat = STOP_STATE;
            	}
			}
			if ( GpSysStat->Share.MachineStat != LastMachineStat)
				{
					GpSysStat->Share.UpdataParaFlag |= (1<<3);
					ParaUpdate.val |= (1<<3);
					LastMachineStat =  GpSysStat->Share.MachineStat;						
				}
            
            if(PS_MAM860C_880C != GpSysPara->Dev.Bits.PS) 
			{
                AlmStat.Alarm.Bits.OverMaxTemp1   = (Data & (1 << 3)) ? TRUE : FALSE;
                AlmStat.Alarm.Bits.PluseError     = (Data & (1 << 4)) ? TRUE : FALSE;
                AlmStat.Alarm.Bits.MainCurrFault  = (Data & (1 << 5)) ? TRUE : FALSE;
                AlmStat.Alarm.Bits.FanCurrFault   = (Data & (1 << 9)) ? TRUE : FALSE;
                AlmStat.Alarm.Bits.OverMaxPres1 = (Data & (1 << 14)) ? TRUE : FALSE;				
            } 
            break;
        case PLT_STATUS_2:
            GpSysStat->Share.PreAlmVal = Data;
            if(PS_MAM860C_880C != GpSysPara->Dev.Bits.PS) {
				/*
                AlmStat.PreAlarm.Bits.OverMaxGreaseTime  = (Data & (1 << 3)) ? TRUE : FALSE;
                AlmStat.PreAlarm.Bits.OverMaxlubeTime    = (Data & (1 << 4)) ? TRUE : FALSE;
                AlmStat.PreAlarm.Bits.OverMaxGasFiltTime = (Data & (1 << 5)) ? TRUE : FALSE;
                AlmStat.PreAlarm.Bits.OverMaxOilSepaTime = (Data & (1 << 6)) ? TRUE : FALSE;
                AlmStat.PreAlarm.Bits.OverMaxOilFiltTime = (Data & (1 << 7)) ? TRUE : FALSE;
                */
                AlmStat.PreAlarm.Bits.OverMaxTemp = (Data & (1 << 8))  ? TRUE : FALSE;
                AlmStat.Alarm.Bits.LackWater      = (Data & (1 << 13)) ? TRUE : FALSE;
                AlmStat.Alarm.Bits.TempSen1Fault  = (Data & (1 << 14)) ? TRUE : FALSE;
                AlmStat.Alarm.Bits.PresSen1Fault  = (Data & (1 << 15)) ? TRUE : FALSE;
//                AlmDealFlag = TRUE;
            }
            break;
        case PLT_OILFILT_TIME:          
			if(GpSysStat->Run.OilFiltHour != Data)
			{
				GpSysStat->Run.OilFiltHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}
			          
            break;
        case PLT_OILSEPA_TIME:

           	if(GpSysStat->Run.OilSepaHour != Data)
			{
				GpSysStat->Run.OilSepaHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}
            
            break;
        case PLT_GASFILT_TIME:
 
            if(GpSysStat->Run.GasFiltHour != Data)
			{
				GpSysStat->Run.GasFiltHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}
            break;
        case PLT_LUBE_TIME:
             if(GpSysStat->Run.lubeHour != Data)
			{
				GpSysStat->Run.lubeHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			} 
            break;
        case PLT_GREASE_TIME:
             if(GpSysStat->Run.GreaseHour != Data)
			{
				GpSysStat->Run.GreaseHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}                
            break;      
        case PLT_FAN_CURRENTA:
            GpSysStat->Fan.A_Current= Data;
//			if(GpSysStat->Fan.A_Current > 10) //   风机电流大于 1 A
//			{
//				if(AlmStat.DevAlarm.Bits.FanRun != TRUE)
//				{
//					AlmStat.DevAlarm.Bits.FanRun = TRUE;					
//				}
//				AlmStat.DevAlarm.Bits.FanStop = FALSE;
//			}
//			else if(GpSysStat->Fan.A_Current < 1)
//			{
//				if(AlmStat.DevAlarm.Bits.FanStop != TRUE)
//				{				
//					AlmStat.DevAlarm.Bits.FanStop = TRUE;
//				}
//				AlmStat.DevAlarm.Bits.FanRun = FALSE;
//			}
            break; 
        case PLT_FAN_CURRENTB:
            GpSysStat->Fan.B_Current = Data;
            break;                  
        case PLT_FAN_CURRENTC:
            GpSysStat->Fan.C_Current = Data;
            break;                  
        case PLT_MAIN_OUT_VOLT:
            GpSysStat->Main.OutVolt = Data;
            break;  
        case PLT_MAIN_OUT_CURR:
            GpSysStat->Main.OutCurrent = Data;
            break;  
        case PLT_MAIN_OUT_FREQ:
            GpSysStat->Main.OutFreq = Data * 10;        //
            break;  
        case PLT_MAIN_OUT_POWER:
            GpSysStat->Main.OutPower = Data;            
            break;  
        case PLT_FAN_OUT_VOLT:
            GpSysStat->Fan.OutVolt = Data;
            break;  
        case PLT_FAN_OUT_CURR:
            GpSysStat->Fan.OutCurrent = Data;
            break;  
        case PLT_FAN_OUT_FREQ:
            GpSysStat->Fan.OutFreq = Data * 10; 
            break;  
        case PLT_FAN_OUT_POWER:
            GpSysStat->Fan.OutPower = Data;
            break;  
        case PLT_MAIN_OUT_SPEED:
            GpSysStat->Main.OutSpeed = Data;
            break;   
        case PLT_FAN_OUT_SPEED:
            GpSysStat->Fan.OutSpeed = Data;
//			if(GpSysStat->Fan.OutSpeed > 100) //   风机转速大于 100
//			{
//				if(AlmStat.DevAlarm.Bits.FanRun != TRUE)
//				{
//					AlmStat.DevAlarm.Bits.FanRun = TRUE;					
//				}
//				AlmStat.DevAlarm.Bits.FanStop = FALSE;
//			}
//			else if(GpSysStat->Fan.OutSpeed < 10)
//			{
//				if(AlmStat.DevAlarm.Bits.FanStop != TRUE)
//				{				
//					AlmStat.DevAlarm.Bits.FanStop = TRUE;
//				}
//				AlmStat.DevAlarm.Bits.FanRun = FALSE;
//			}
            break;                 
        case PLT_FAN_START_TEMP:          
			if(GpSysStat->Fan.StartTemp != Data * 10)
			{
				GpSysStat->Fan.StartTemp = Data * 10; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_FAN_STOP_TEMP:          
			if(GpSysStat->Fan.StopTemp != Data * 10)
			{
				GpSysStat->Fan.StopTemp = Data * 10; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_LOAD_PRESS:
			if(GpSysStat->Share.LoadPress != Data)
			{
				GpSysStat->Share.LoadPress = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;            
			
        case PLT_UNLOAD_PRESS:            
			if(GpSysStat->Share.UnLoadPress != Data)
			{
				GpSysStat->Share.UnLoadPress = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_XINJIAO_DELAY:           
			if(GpSysStat->Share.XinJiaoDelay != Data)
			{
				GpSysStat->Share.XinJiaoDelay = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_LOAD_DELAY:           
			if(GpSysStat->Share.LoadDelay != Data)
			{
				GpSysStat->Share.LoadDelay = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_STOP_DELAY:          
			if(GpSysStat->Share.StopDelay != Data)
			{
				GpSysStat->Share.StopDelay = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_START_DELAY:         
			if(GpSysStat->Share.StartDelay != Data)
			{
				GpSysStat->Share.StartDelay = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_MAIN_DELAY:        
			if(GpSysStat->Share.MainDelay != Data)
			{
				GpSysStat->Share.MainDelay = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_FAN_DELAY:           
			if(GpSysStat->Share.FanDelay != Data)
			{
				GpSysStat->Share.FanDelay = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_UNLOAD_DELAY:           
			if(GpSysStat->Share.UnloadDelay != Data)
			{
				GpSysStat->Share.UnloadDelay = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_OILFILT_MAX_HOUR:
            GpUsrPara->Hour.MaxOilFiltTime = Data;
            break;                 
        case PLT_OILSEPA_MAX_HOUR:
            GpUsrPara->Hour.MaxOilSepaTime= Data;
            break;        
			
        case PLT_GASFILT_MAX_HOUR:
            GpUsrPara->Hour.MaxGasFiltTime= Data;
            break;                 
        case PLT_LUBE_MAX_HOUR:
            GpUsrPara->Hour.MaxlubeTime= Data;
            break;                 
        case PLT_GREAS_MAX_HOUR:
            GpUsrPara->Hour.MaxGreaseTime= Data;
            break;                 
        case PLT_MAIN_RATE_CURR:           
			if(GpSysStat->Main.RateCurrent != Data)
			{
				GpSysStat->Main.RateCurrent = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
            break;  
        case PLT_FAN_RATE_CURR:          
			if(GpSysStat->Fan.RateCurrent != Data)
			{
				GpSysStat->Fan.RateCurrent = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
            break;      
        case PLT_PRALARM_TEMP:           
			if(GpSysStat->Fan.PreAlmTemp != Data * 10)
			{
				GpSysStat->Fan.PreAlmTemp = Data * 10; 
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
            break;                 
        case PLT_ALARM_TEMP:            
			if(GpSysStat->Fan.AlmTemp != Data * 10)
			{
				GpSysStat->Fan.AlmTemp = Data * 10; 
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
            break;                 
        case PLT_STOP_PRESS:       
			if(GpSysStat->Share.StopPress != Data)
			{
				GpSysStat->Share.StopPress = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
            break;                 
        case PLT_UNLOAD_MAX_PRESS:           
			if(GpSysStat->Share.MaxUnloadPress != Data)
			{
				GpSysStat->Share.MaxUnloadPress = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
            break;                 
        case PLT_CURR_UNBALANCE:        
			if(GpSysStat->Share.UnblanceCurrent != Data)
			{
				GpSysStat->Share.UnblanceCurrent = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
            break;      
			
        case PLT_MAX_USE_TIME:            
			if(GpUsrPara->Hour.MaxUseTime != Data)
			{
				GpUsrPara->Hour.MaxUseTime = Data;  
				GpSysStat->Share.UpdataParaFlag |= 0x0004;
			}
            break;    
        case PLT_USR_PASSWORD:
			my_itoa((char*)&GpSysStat->Share.UsrPassword, Data); 
            
            break;
        case PLT_FAC_PASSWORD:         
			my_itoa((char*)&GpSysStat->Share.FacPassword, Data); 
            break;               
        case PLT_PWR_VOLT:
            GpSysStat->Share.PowerVolt = Data;
            break;


		case PLT_FRONT_BEAR_TEMP:
			
		GpSysStat->Share.Front_Bear_Temp = Data >200 ? 0: ((s16)(Data - 50)) * 10;
            break;
		case PLT_REAR_BEAR_TEMP:
            GpSysStat->Share.Rear_Bear_Temp = Data >200 ? 0: ((s16)(Data - 50)) * 10;
            break;
		
		case PLT_MAIN_POWER_CONSUME:
            Power_Consume_Total[0] = Data;
            break;
		case PLT_MAIN_POWER_CONSUME_LOW:
            GpSysStat->Main.Power_Consume_Total = (Power_Consume_Total[0]<<16) |Data;
            GpSysStat->Main.Power_Consume_Total /= 10;
			break;
		
		case PLT_FAN_POWER_CONSUME:
            Power_Consume_Total[1] = Data;
            break;
		case PLT_FAN_POWER_CONSUME_LOW:
            GpSysStat->Fan.Power_Consume_Total = (Power_Consume_Total[1]<<16) |Data;
            GpSysStat->Fan.Power_Consume_Total /= 100;
			break;
		
		case PLT_PFREQ_MAIN_POWER_CONSUME:
            Power_Consume_Total[2] = Data;
            break;
		case PLT_PFREQ_MAIN_POWER_CONSUME_LOW:
            GpSysStat->Main.Pfreq_Power_Consume_Total = (Power_Consume_Total[2]<<16) |Data;
            GpSysStat->Main.Pfreq_Power_Consume_Total /= 10;
			break;
		
		case PLT_PFREQ_FAN_POWER_CONSUME:
            Power_Consume_Total[3] = Data;
            break;
		case PLT_PFREQ_FAN_POWER_CONSUME_LOW:
            GpSysStat->Fan.Pfreq_Power_Consume_Total = (Power_Consume_Total[3]<<16) |Data;
            GpSysStat->Fan.Pfreq_Power_Consume_Total /= 100;	
			break;
		
		case PLT_MAIN_CFREQ_PRESS:         
			if(GpSysStat->Main.Cfreq_Press != Data)
			{
				GpSysStat->Main.Cfreq_Press = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;
		case PLT_FAN_CFREQ_TEMP:
			if(GpSysStat->Fan.Cfreq_Temp != Data * 10)
			{
				 GpSysStat->Fan.Cfreq_Temp = Data * 10;
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;

		case PLT_PRE_ALARM:
            Plt_PreAlarm_Deal(Data);
            break;
		case PLT_RUN_STATA:
            Plt_RunStata_Deal(Data);
            break;
		case PLT_FAULT:
            Plt_Fault_Deal(Data);
            break;

		case PLT_MAIN_ALARM_VALUE:
            GpSysStat->VFD.MainVfd_AlarmValue = Data;
            break;
		case PLT_MAIN_RUN_STATE:
            GpSysStat->VFD.MainVfd_RunState = Data;
            break;	
		case PLT_MAIN_TOPLIMIT_FREQ:
            GpSysStat->VFD.MainVfd_TopLimitFreq = Data *10;
            break;
		case PLT_MAIN_LOWLIMIT_FREQ:
            GpSysStat->VFD.MainVfd_LowLimitFreq = Data *10;
            break;
		case PLT_MAIN_ACC_TIME:
            GpSysStat->VFD.MainVfd_AccelerateTime = Data *10;
            break;
		case PLT_MAIN_DEC_TIME:
            GpSysStat->VFD.MainVfd_DecelerateTime = Data *10;
            break;
		case PLT_MAIN_MODEL:			//主机变频器型号
			switch ( GpSysPara->Dev.Bits.PS)
				{
					case PS_MAM6080_6090:
					case PS_MAM6090:
					case PS_MAM6080_1:
					if (3 == Data)
					{
						Data = 0;
					}
					else if (7 == Data)
					{
						Data = 1;
					}
					else 
					{
						;
					}
					break;
					case PS_MAM6070:
					if (2 == Data)
					{
						Data = 0;
					}
					else if (6 == Data)
					{
						Data = 1;
					}
					else if (7 == Data)
					{
						Data = 2;
					}
					else 
					{
						;
					}
					break;
					default:
						break;
				}
		
            GpSysStat->VFD.MainVfd_Model = Data;
            break;

		case PLT_FAN_ALARM_VALUE:
            GpSysStat->VFD.FanVfd_AlarmValue = Data;
            break;
		case PLT_FAN_RUN_STATE:
            GpSysStat->VFD.FanVfd_RunState = Data;
            break;	
		case PLT_FAN_TOPLIMIT_FREQ:
            GpSysStat->VFD.FanVfd_TopLimitFreq = Data *10;
            break;
		case PLT_FAN_LOWLIMIT_FREQ:
            GpSysStat->VFD.FanVfd_LowLimitFreq = Data *10;
            break;
		case PLT_FAN_ACC_TIME:
            GpSysStat->VFD.FanVfd_AccelerateTime = Data *10;
            break;
		case PLT_FAN_DEC_TIME:
            GpSysStat->VFD.FanVfd_DecelerateTime = Data *10;
            break;
		case PLT_FAN_MODEL: 				// 风机变频器型号
			switch ( GpSysPara->Dev.Bits.PS)
				{
					case PS_MAM6080_6090:
					case PS_MAM6090:
					case PS_MAM6080_1:
					if (3 == Data)
					{
						Data = 0;
					}
					else if (7 == Data)
					{
						Data = 2;
					}
					else if ( 2 == Data)
					{
						Data = 1;
					}
					else
					{
						;
						}
					break;
					case PS_MAM6070:
					if (2 == Data)
					{
						Data = 0;
					}
					else if (6 == Data)
					{
						Data = 2;
					}
					else if (7 == Data)
					{
						Data = 1;
					}
					else 
					{
						;
					}
					break;
					default:
						break;
				}
            GpSysStat->VFD.FanVfd_Model = Data;
            break;	
		case PLT_ALLOW_WRITE:
            PltAlowWrite = (Data & 0x80) ? TRUE : FALSE;
            break;
        default:
			PltMam6080OtherDataPrase(Index, Data);
            break;
    }
}


void  PltMam6080OtherDataPrase(u16 Index, u16 Data)
{

    switch(Index) 
	{
        case PLT_SysPressure:						// 系统压力
            GpSysStat->OtherData.SysPressure = Data;                               
            break;
		case PLT_PhaseProVolt:						// 相序保护电压
            GpSysStat->OtherData.PhaseProVolt = Data;                               
            break;		
		case PLT_OpenPhaseProVolt:					// 缺相保护电压
            GpSysStat->OtherData.OpenPhaseProVolt = Data;                               
            break;
		case PLT_Volt:								// 电压
            GpSysStat->OtherData.Volt = Data;                               
            break;		
		case PLT_WarningValue:						// 预警值
            GpSysStat->OtherData.WarningValue = Data;                               
            break;
		case PLT_RunStatus:							// 运行状态
            GpSysStat->OtherData.RunStatus = Data;                               
            break;
		case PLT_Timing:							// 计时
            GpSysStat->OtherData.Timing = Data;                               
            break;
		case PLT_Fault:								// 故障
            GpSysStat->OtherData.Fault = Data;                               
            break;		
		case PLT_FaultValue:						// 故障值
            GpSysStat->OtherData.FaultValue = Data;                               
            break;
		case PLT_OilPressDif:						// 油分压差
            GpSysStat->OtherData.OilPressDif = Data;                               
            break;		
		case PLT_MainStatus:						// 主机状态字
            GpSysStat->OtherData.MainStatus = Data;                               
            break;
		case PLT_MainFault:							// 主机故障字
            GpSysStat->OtherData.MainFault = Data;                               
            break;
		case PLT_FanStatus:							// 风机状态字
            GpSysStat->OtherData.FanStatus = Data;                               
            break;
		case PLT_FanFault:							// 风机故障字
            GpSysStat->OtherData.FanFault = Data;                               
            break;		
		case PLT_MainPfreqPowerThis:				// 工频主机本次用电
            GpSysStat->OtherData.MainPfreqPowerThis = Data;                               
            break;
		case PLT_FanPfreqPowerThis:					// 工频风机本次用电
            GpSysStat->OtherData.FanPfreqPowerThis = Data;                               
            break;		
		case PLT_MainPfreqUI:						// 工频主机UI
            GpSysStat->OtherData.MainPfreqUI = Data;                               
            break;
		case PLT_FanPfreqUI:						// 工频风机UI
            GpSysStat->OtherData.FanPfreqUI = Data;                               
            break;
		
		
		case PLT_TempUnit:							// 温度单位
            GpSysStat->OtherData.TempUnit = Data;                               
            break;
		case PLT_PressureUnit:						// 压力单位
            GpSysStat->OtherData.PressureUnit = Data;                               
            break;		
		case PLT_WarningStop:						// 预警过久停机
            GpSysStat->OtherData.WarningStop = Data;                               
            break;
		case PLT_FrontBearingWarnTemp:				// 前轴承预警温度
            GpSysStat->OtherData.FrontBearingWarnTemp = Data;                               
            break;		
		case PLT_FrontBearingAlarmTemp:				// 前轴承报警温度
            GpSysStat->OtherData.FrontBearingAlarmTemp = Data;                               
            break;
		case PLT_OilPressDifWarn:					// 油分预警压差
            GpSysStat->OtherData.OilPressDifWarn = Data;                               
            break;
		case PLT_OilPressDifAlarm:					// 油分报警压差
            GpSysStat->OtherData.OilPressDifAlarm = Data;                               
            break;
		case PLT_DrainOpenDelay:					// 排水开延时
            GpSysStat->OtherData.DrainOpenDelay = Data;                               
            break;		
		case PLT_DrainCloseDelay:					// 排水关延时
            GpSysStat->OtherData.DrainCloseDelay = Data;                               
            break;
		case PLT_SoftStartDelay:					// 软启延时
            GpSysStat->OtherData.SoftStartDelay = Data;                               
            break;		
		case PLT_AssistStartTime:					// 辅助启动时间
            GpSysStat->OtherData.AssistStartTime = Data;                               
            break;
		case PLT_AssistLoadDelay:					// 辅助加载延时
            GpSysStat->OtherData.AssistLoadDelay = Data;                               
            break;
		case PLT_AssistUnloadDelay:					// 辅助卸载延时
            GpSysStat->OtherData.AssistUnloadDelay = Data;                               
            break;
		case PLT_AssistStartTemp:					// 辅助启温度
            GpSysStat->OtherData.AssistStartTemp = Data;                               
            break;		
		case PLT_LoadMode:							// 加载方式
            GpSysStat->OtherData.LoadMode = Data;                               
            break;
		case PLT_StartStopMode:						// 启停方式
            GpSysStat->OtherData.StartStopMode = Data;                               
            break;		
		case PLT_CorrespondMode:					// 通信方式
            GpSysStat->OtherData.CorrespondMode = Data;                               
            break;
		case PLT_LanguageSelection:					// 语言选择
            GpSysStat->OtherData.LanguageSelection = Data;                               
            break;
		case PLT_RunMode:							// 运行方式  
			if(GpSysStat->OtherData.RunMode != Data)
			{
				 GpSysStat->OtherData.RunMode = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;
		case PLT_SysStopPressure:					// 系统停机压力
            GpSysStat->OtherData.SysStopPressure = Data;                               
            break;		
		case PLT_HistoryFaultReset:					// 历史故障复位
            GpSysStat->OtherData.HistoryFaultReset = Data;                               
            break;
		case PLT_FactoryCode1:						// 出厂编码1
            GpSysStat->OtherData.FactoryCode1 = Data;                               
            break;	
		case PLT_FactoryCode2:						// 出厂编码2
            GpSysStat->OtherData.FactoryCode2 = Data;                               
            break;
		case PLT_FactoryDate:						// 出厂日期
            GpSysStat->OtherData.FactoryDate = Data;                               
            break;
	
		
		
		case PLT_MainIntegInitValue:				// 主机积分初值
            GpSysStat->OtherData.MainIntegInitValue = Data;                               
            break;
		case PLT_MainIntegRange:					// 主机积分范围
            GpSysStat->OtherData.MainIntegRange = Data;                               
            break;		
		case PLT_MainRatioGain:						// 主机比例增益
            GpSysStat->OtherData.MainRatioGain = Data;                               
            break;
		case PLT_MainIntegGain:						// 主机积分增益
            GpSysStat->OtherData.MainIntegGain = Data;                               
            break;		
		case PLT_MainDiffGain:						// 主机微分增益
            GpSysStat->OtherData.MainDiffGain = Data;                               
            break;
		case PLT_MainFreqToplimit:					// 主机频率上限
            GpSysStat->OtherData.MainFreqToplimit = Data/10;                               
            break;
		case PLT_MainFreqLowlimit:					// 主机频率下限
            GpSysStat->OtherData.MainFreqLowlimit = Data/10;                               
            break;
		case PLT_MainIdlingFreq:					// 主机空载频率
            GpSysStat->OtherData.MainIdlingFreq = Data/10;                               
            break;		
		case PLT_MainVfdNum:						// 主机变频器站号
            GpSysStat->OtherData.MainVfdNum = Data;                               
            break;
		case PLT_MainPIDPeriod:						// 主机PID周期
            GpSysStat->OtherData.MainPIDPeriod = Data/10;                               
            break;		
		case PLT_MainVfdModel:						// 主机变频器型号
            GpSysStat->OtherData.MainVfdModel = Data;                               
            break;
		case PLT_FanIntegInitValue:					// 风机积分初值
            GpSysStat->OtherData.FanIntegInitValue = Data;                               
            break;
		case PLT_FanIntegRange:						// 风机积分范围
            GpSysStat->OtherData.FanIntegRange = Data;                               
            break;
		case PLT_FanRatioGain:						// 风机比例增益
            GpSysStat->OtherData.FanRatioGain = Data;                               
            break;		
		case PLT_FanIntegGain:						// 风机积分增益
            GpSysStat->OtherData.FanIntegGain = Data;                               
            break;
		case PLT_FanDiffGain:						// 风机微分增益
            GpSysStat->OtherData.FanDiffGain = Data;                               
            break;		
		case PLT_FanFreqToplimit:					// 风机频率上限
            GpSysStat->OtherData.FanFreqToplimit = Data/10;                               
            break;
		case PLT_FanFreqLowlimit:					// 风机频率下限
            GpSysStat->OtherData.FanFreqLowlimit = Data/10;                               
            break;
		case PLT_FanIdlingFreq:						// 风机空载频率
            GpSysStat->OtherData.FanIdlingFreq = Data/10;                               
            break;
		case PLT_FanVfdNum:							// 风机变频器站号
            GpSysStat->OtherData.FanVfdNum = Data;                               
            break;		
		case PLT_FanPIDPeriod:						// 风机PID周期
            GpSysStat->OtherData.FanPIDPeriod = Data/10;                               
            break;
		case PLT_FanVfdModel:						// 风机变频器型号
            GpSysStat->OtherData.FanVfdModel = Data;                               
            break;		
		case PLT_VoltOvertop:						// 电压过高
            GpSysStat->OtherData.VoltOvertop = Data;                               
            break;
		case PLT_VoltOverlow:						// 电压过低
            GpSysStat->OtherData.VoltOverlow = Data;                               
            break;
		case PLT_CorrespondOverTime:				// 通信超时
            GpSysStat->OtherData.CorrespondOverTime = Data;                               
            break;
		
		
		
		case PLT_ReFreqPressure:					// 降频压力
            GpSysStat->OtherData.ReFreqPressure = Data;                               
            break;
		
		case PLT_MainRiseRate:						// 主机上升速率
            GpSysStat->OtherData.MainRiseRate = Data;                               
            break;
		case PLT_MainDownRate:						// 主机下降速率
            GpSysStat->OtherData.MainDownRate = Data;                               
            break;
		
		case PLT_MainPower:							// 主机功率
            GpSysStat->OtherData.MainPower = Data/10;                               
            break;
		case PLT_MainRotationRate:					// 主机转速
            GpSysStat->OtherData.MainRotationRate = Data;                               
            break;
		case PLT_FanRiseRate:						// 风机上升速率
            GpSysStat->OtherData.FanRiseRate = Data;                               
            break;
		case PLT_FanDownRate:						// 风机下降速率
            GpSysStat->OtherData.FanDownRate = Data;                               
            break;	
		case PLT_FanPower:							// 风机功率
            GpSysStat->OtherData.FanPower = Data/10;                               
            break;			
		case PLT_FanRotationRate:					// 风机转速
            GpSysStat->OtherData.FanRotationRate = Data;                               
            break;
		case PLT_FanFreqStart:						// 变频风机启
            GpSysStat->OtherData.FanFreqStart = Data;                               
            break;
		case PLT_FanFreqStop:						// 变频风机停
            GpSysStat->OtherData.FanFreqStop = Data;                               
            break;
		case PLT_MainStopMode:						// 主机停机方式
            GpSysStat->OtherData.MainStopMode = Data;                               
            break;
		
		case PLT_TimeStartStopFunc:					// 定时启停功能
            GpSysStat->OtherData.TimeStartStopFunc = Data;                               
            break;
		case PLT_TimePressureFunc:					// 定时压力功能
            GpSysStat->OtherData.TimePressureFunc = Data;                               
            break;
		
		case PLT_LowTempProtect:					// 低温保护
            GpSysStat->OtherData.LowTempProtect = Data;                               
            break;
		case PLT_MainVfdStartMode:					// 主变频器启动方式
            GpSysStat->OtherData.MainVfdStartMode = Data;                               
            break;
		case PLT_FanVfdStartMode:					// 风机变频器启动方式
            GpSysStat->OtherData.FanVfdStartMode = Data;                               
            break;
		case PLT_CorrespondStartVfdNum:				// 通信启变频器次数
            GpSysStat->OtherData.CorrespondStartVfdNum = Data;                               
            break;
		
		case PLT_CorrespondStopVfdNum:				// 通信停变频器次数
            GpSysStat->OtherData.CorrespondStopVfdNum = Data;                               
            break;
		case PLT_MainPfreqPowerFactor:				// 工频主机功率系数
            GpSysStat->OtherData.MainPfreqPowerFactor = Data/10;                               
            break;
		
		case PLT_MainfreqPowerFactor:				// 变频主机功率系数
            GpSysStat->OtherData.MainfreqPowerFactor = Data/10;                               
            break;
		case PLT_FanPfreqPowerFactor:				// 变频风机功率系数
            GpSysStat->OtherData.FanPfreqPowerFactor = Data/10;                               
            break;
		case PLT_FanfreqPowerFactor:				// 工频风机功率系数
            GpSysStat->OtherData.FanfreqPowerFactor = Data/10;                               
            break;			
		case PLT_ProMainVfdDelay:					// 预开主机变频器延时
            GpSysStat->OtherData.ProMainVfdDelay = Data/10;                               
            break;	
		case PLT_PowerDownRestart:					// 掉电重启功能
            GpSysStat->OtherData.PowerDownRestart = Data;                               
            break;	
		case PLT_FreqSelect:						// 频率选择
            GpSysStat->OtherData.FreqSelect = Data;                               
            break;	
		case PLT_PipePressure:						// 管路压阻
            GpSysStat->OtherData.PipePressure = Data;                               
            break;	
		case PLT_RearBearingWarnTemp:				// 后轴承预警温度
            GpSysStat->OtherData.RearBearingWarnTemp = Data;                               
            break;	
		case PLT_RearBearingAlarmTemp:				// 后轴承停机温度
            GpSysStat->OtherData.RearBearingAlarmTemp = Data;                               
            break;	
		
		default: 
			break;
	}
}

void    PltDevMan860DataPrase(u16 Index, u16 Data, u8 Type)
{
	static  u16 LastMachineStat = STATUS_UNKNOW;
    switch(Index) {
        case PLT_Man_PRESSURE:
            GpSysStat->Share.Pressure1 = Data;                      //  2位小数点,已扩大100倍                
            break;
		
        case PLT_Man_TEMPERATURE:
            switch(Type) 
			{
	
                case PS_MAM860_870_880:		
                    GpSysStat->Share.Temprature1 = ((s16)(Data - 50)) * 10;
                    break;
                case PS_MAM860C_880C:
                    GpSysStat->Share.Temprature1 = ((s16)(Data - 20)) * 10;
                    break;	
                    /*
				case PS_MAM260:
					GpSysStat->Share.Temprature1 = ((s16)(Data - 150)) * 10;
                    break;
				case PS_MAM260A:
					GpSysStat->Share.Temprature1 = ((s16)(Data - 145)) * 10;
                    break;
				case PS_MAM280:
					GpSysStat->Share.Temprature1 = ((s16)(Data - 125)) * 10;
                    break;
                   */
                default:
                    GpSysStat->Share.Temprature1 = Data * 10;
                    break;
            }            
            break;
			
		case PLT_Man_STATUS_1:
		 GpSysStat->Share.AlmVal = Data;
            if(Data & (1 << 15)) 
			{

				if(GpSysStat->Share.MachineStat != KONG_JIU_STOP_STATE)
				{
					if (GpSysStat->Share.MachineStat != STATUS_UNKNOW)
					{
						AlmStat.DevAlarm.Bits.DevDormancy =TRUE;
					}
					GpSysStat->Share.MachineStat = KONG_JIU_STOP_STATE;
				}
				GpSysStat->Share.RunState = RUN_STATE;
            } 
			else if(Data & (1 << 1)) 
			{
				GpSysStat->Share.RunState = RUN_STATE;
                if(STOP_STATE == GpSysStat->Share.MachineStat) 
				{
                    AlmStat.Flag.Bits.Boot = TRUE;
					StartFilterTimer = Start_FILTER_TIME;
                    if(RmtBootTimer.Bits.Flag) 
					{
                        RmtBootTimer.Val = 0;
                        AlmStat.BootType = BOOT_TYPE_SERVER;                        
                    } 
					else 
					{
                        AlmStat.BootType = BOOT_TYPE_KEY;
                    }
					AlmStat.DevAlarm.Bits.DevStartUp =TRUE;
                }
                if(Data & 0x01) 
				{
					if(GpSysStat->Share.MachineStat != JIA_ZAI_RUN_STATE)
					{
						GpSysStat->Share.MachineStat = JIA_ZAI_RUN_STATE;
						AlmStat.DevAlarm.Bits.LoadingRun =TRUE;
					}
                } 
				else 
				{
					if(GpSysStat->Share.MachineStat != KONG_ZAI_RUN_STATE)
					{
						GpSysStat->Share.MachineStat = KONG_ZAI_RUN_STATE;
						AlmStat.DevAlarm.Bits.IdlerRun =TRUE;
					}                   
                }
            } 
			else 
			{
				GpSysStat->Share.RunState = STOP_STATE;
                if(STOP_STATE != GpSysStat->Share.MachineStat)
				{
					if (STATUS_UNKNOW != GpSysStat->Share.MachineStat)
                   {
              			StopFilterTimer = STOP_FILTER_TIME;
	                   	AlmStat.Flag.Bits.Stop = TRUE;
	                    if(RmtStopTimer.Bits.Flag) 
						{
	                        RmtStopTimer.Val = 0;
	                        AlmStat.StopType = STOP_TYPE_SERVER;   
	                    } 
						else 
						{
	                        AlmStat.StopType = STOP_TYPE_KEY;
	                    }
						AlmStat.DevAlarm.Bits.DevStop =TRUE;
                	}
					GpSysStat->Share.MachineStat = STOP_STATE;
            	}
            }

			if ( GpSysStat->Share.MachineStat != LastMachineStat)
				{
					GpSysStat->Share.UpdataParaFlag |= (1<<3);
					ParaUpdate.val |= (1<<3);
					LastMachineStat =  GpSysStat->Share.MachineStat;						
				}
           
            break;
        case PLT_Man_STATUS_2:
            GpSysStat->Share.PreAlmVal = Data;
            if(PS_MAM860_870_880 == GpSysPara->Dev.Bits.PS) 
			{
				/*
                AlmStat.PreAlarm.Bits.OverMaxGreaseTime  = (Data & (1 << 3)) ? TRUE : FALSE;
                AlmStat.PreAlarm.Bits.OverMaxlubeTime    = (Data & (1 << 4)) ? TRUE : FALSE;
                AlmStat.PreAlarm.Bits.OverMaxGasFiltTime = (Data & (1 << 5)) ? TRUE : FALSE;
                AlmStat.PreAlarm.Bits.OverMaxOilSepaTime = (Data & (1 << 6)) ? TRUE : FALSE;
                AlmStat.PreAlarm.Bits.OverMaxOilFiltTime = (Data & (1 << 7)) ? TRUE : FALSE;
                */
             //   AlmStat.PreAlarm.Bits.OverMaxTemp = (Data & (1 << 8))  ? TRUE : FALSE;
			
               // AlmStat.Alarm.Bits.LackWater      = (Data & (1 << 13)) ? TRUE : FALSE;
              //  AlmStat.Alarm.Bits.TempSen1Fault  = (Data & (1 << 14)) ? TRUE : FALSE;
              //  AlmStat.Alarm.Bits.PresSen1Fault  = (Data & (1 << 15)) ? TRUE : FALSE;
			//	AlmStat.Alarm.Bits.Reserved =  (Data & 0x0001) ? TRUE : FALSE;		//其它报警
				
            }
            break;
			
        case PLT_Man_RUN_TIME:
			if(GpSysStat->Run.RunHour != Data)
			{
				GpSysStat->Run.RunHour = Data;  
			}
            break;
        case PLT_Man_LOAD_TIME:          
			if(GpSysStat->Run.LoadHour != Data)
			{
				GpSysStat->Run.LoadHour = Data;  
			}
            break;
        case PLT_Man_CURRENT_A:
            GpSysStat->Main.A_Current = Data;                       //  1位小数点,已扩大10倍
            break;
        case PLT_Man_CURRENT_B:
            GpSysStat->Main.B_Current = Data;                       //  1位小数点,已扩大10倍
            break;
        case PLT_Man_CURRENT_C:
            GpSysStat->Main.C_Current = Data;                       //  1位小数点,已扩大10倍
            break;                                 
       
		case PLT_Man_OILFILT_TIME:          
			if(GpSysStat->Run.OilFiltHour != Data)
			{
				GpSysStat->Run.OilFiltHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}		          
            break;
			
        case PLT_Man_OILSEPA_TIME:
                
            if(GpSysStat->Run.OilSepaHour != Data)
			{
				GpSysStat->Run.OilSepaHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}		         
			
            break;
		
        case PLT_Man_GASFILT_TIME:
            
             if(GpSysStat->Run.GasFiltHour != Data)
			{
				GpSysStat->Run.GasFiltHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}		  
            break;
		
        case PLT_Man_LUBE_TIME:
          
             if(GpSysStat->Run.lubeHour != Data)
			{
				GpSysStat->Run.lubeHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}		
            break;
		
        case PLT_Man_GREASE_TIME:

             if(GpSysStat->Run.GreaseHour != Data)
			{
				GpSysStat->Run.GreaseHour = Data;
				GpSysStat->Share.UpdataParaFlag |= 0x0001;
			}		
            break;  
		 case PLT_Man_BELT_TIME:
				if ( GpSysPara->Dev.Bits.PS == PS_MAM860C_880C) //880C
				{
				  if(GpSysStat->Run.BeltHour != Data)
					{
						GpSysStat->Run.BeltHour = Data;
						GpSysStat->Share.UpdataParaFlag |= 0x0001;
					}
				}
				else
				{
					GpSysStat->Fan.A_Current = Data;
				}
				break;
			case PLT_Man_FAN_CURRENTA:
			if ( GpSysPara->Dev.Bits.PS == PS_MAM860C_880C) //880C
				{
				  GpSysStat->Fan.A_Current = Data;
				}
				else
				{
					GpSysStat->Fan.B_Current = Data;
				}		
				 break; 
			case PLT_Man_FAN_CURRENTB:
				if ( GpSysPara->Dev.Bits.PS == PS_MAM860C_880C) //880C
				{
				  GpSysStat->Fan.B_Current = Data;
				}
				else
				{
					GpSysStat->Fan.C_Current = Data;
				}		
				break;	 
        case PLT_Man_FAN_CURRENTC:
        	if ( GpSysPara->Dev.Bits.PS == PS_MAM860C_880C) //880C
			{
				  GpSysStat->Fan.C_Current = Data;
			}
            break;   
		case PLT_Man_PHASE_PROVOLT:
			GpSysStat->OtherData.PhaseProVolt = Data;
			break;
		case PLT_Man_VF_FREQUENCY:
			GpSysStat->Main.OutFreq = Data;
			break;
		case PLT_Man_VF_VOLTAGE:
			GpSysStat->Main.OutVolt = Data;
			break;
		case PLT_Man_VF_CURRENT:
			GpSysStat->Main.OutCurrent  = Data;
			break;
		case PLT_Man_VF_POWER:
			GpSysStat->Main.OutPower = Data;
			break;
		case PLT_Man_VF_ROTATIONL_SPEED:
			GpSysStat->Main.OutSpeed = Data;
			break;
		case PLT_Man_FALT:
			GpSysStat->OtherData.Fault = Data>>8;
		if (GpSysPara->Dev.Bits.PS == PS_MAM860C_880C)
		{
		
			switch (GpSysStat->OtherData.Fault)
			{	
				case 0:
					 AlmStat.Alarm.Flag = 0;
					 break;
				// 风机过流
				case 8:
					 AlmStat.Alarm.Bits.FanOverCurr = TRUE;
				break;
				
				// 温度传感器失灵	
				case 11:
					AlmStat.Alarm.Bits.TempSen1Fault = TRUE;
				break;

				/* 排气温度高 */
				case 13:
					AlmStat.Alarm.Bits.OverMaxTemp1 = TRUE;
				break;

				/* 压力传感器失灵 */
				case 16:
					AlmStat.Alarm.Bits.PresSen1Fault = TRUE;
				break;

				/* 供气压力高*/
				case 18:
					AlmStat.Alarm.Bits.OverMaxPres1 = TRUE;
					break;

				/* 变频器故障*/
				case 19:
					AlmStat.Alarm.Bits.MainVfdAlarm = TRUE;
					break;

				/* 外部故障*/
				case 20:
		     //	AlmStat.Alarm.Bits.outfault = TRUE;
					break;

				/*预警过久停机*/
				case 21:
				//	AlmStat.Alarm.Bits.prealarmtoolong = TRUE;
					break;

				/*相序错误*/
				case 23:
					AlmStat.Alarm.Bits.PluseError = TRUE;
					break;

				/* 温度过低*/
				case 24:
					AlmStat.Alarm.Bits.OverMinTemp = TRUE;
					break;

				default:
					break;
			}
		}
		else 
		{
			switch (GpSysStat->OtherData.Fault)
			{	
			case 0:
				 AlmStat.Alarm.Flag = 0;
				 break;
			// 风机过流

			case 3:  //主机过流
				AlmStat.Alarm.Bits.OverMaxCurr = TRUE;
				break;
			case 8:
				 AlmStat.Alarm.Bits.FanOverCurr = TRUE;
			break;
			
			// 温度传感器失灵	
			case 10:
				AlmStat.Alarm.Bits.TempSen1Fault = TRUE;
			break;

			/* 排气温度高 */
			case 11:
				AlmStat.Alarm.Bits.OverMaxTemp1 = TRUE;
			break;

			/* 压力传感器失灵 */
			case 12:
				AlmStat.Alarm.Bits.PresSen1Fault = TRUE;
			break;

			/* 供气压力高*/
			case 13:
				AlmStat.Alarm.Bits.OverMaxPres1 = TRUE;
				break;
			case 14: //电压过高
				AlmStat.Alarm.Bits.SupplyVoltageOverMax = TRUE;
				break;
			case 15: // 电压过低
				AlmStat.Alarm.Bits.SupplyVoltageOverMin = TRUE;
				break;

			/*相序错误*/
			case 16:
				AlmStat.Alarm.Bits.PluseError = TRUE;
				break;
				
			default:
				break;
		}	
	   }
			break;
		case PLT_Man_WARNING:
			GpSysStat->OtherData.WarningValue = Data;
			if (GpSysPara->Dev.Bits.PS == PS_MAM860C_880C)
			{
 			switch (Data)
			{
				case 0:
				AlmStat.PreAlarm.Flag = 0;
				break;
				/*排气温度高*/
				case 11:
                	AlmStat.PreAlarm.Bits.OverMaxTemp = TRUE;
                	break;
                default:
                	break;
			}
			}
			else
			{
			switch (Data)
			{
				case 0:
				AlmStat.PreAlarm.Flag = 0;
				GpSysStat->Share.MatainAlarm = 0;
				break;
				/*排气温度高*/
				case 1:
                	AlmStat.PreAlarm.Bits.OverMaxTemp = TRUE;
                	break;
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
          
                	if (GpSysStat->Share.MatainAlarm != Data)
                	{
                		GpSysStat->Share.MatainAlarm = Data;
                		ParaUpdate.Bits.MatainAlarmVal = TRUE;
						GpSysStat->Share.UpdataParaFlag |= 0x0008; 
                	}
                	break;
                default:
                	break;
			}
			
			}
			break;
		case PLT_Man_OILFILT_MAXTIME:
		if (GpUsrPara->Hour.MaxOilFiltTime != Data)
		{
			GpUsrPara->Hour.MaxOilFiltTime = Data;
			GpSysStat->Share.UpdataParaFlag |= 0x0001;
		}
		break;
		case PLT_Man_OILSEPA_MAXTIME:
		if (GpUsrPara->Hour.MaxOilSepaTime != Data)
		{
			GpUsrPara->Hour.MaxOilSepaTime = Data;
			GpSysStat->Share.UpdataParaFlag |= 0x0001;
		}
		break;
		case PLT_Man_GASFILT_MAXTIME:
		if (GpUsrPara->Hour.MaxGasFiltTime != Data)
		{
			GpUsrPara->Hour.MaxGasFiltTime = Data;				
			GpSysStat->Share.UpdataParaFlag |= 0x0001;
		}
		break;
		case PLT_Man_LUBE_MAXTIME:
		if (GpUsrPara->Hour.MaxlubeTime != Data)
		{
			GpUsrPara->Hour.MaxlubeTime = Data;		
			GpSysStat->Share.UpdataParaFlag |= 0x0001;
		}
		break;
		case PLT_Man_GREASE_MAXTIME:
		if (GpUsrPara->Hour.MaxGreaseTime != Data)
		{
			GpUsrPara->Hour.MaxGreaseTime = Data;
			GpSysStat->Share.UpdataParaFlag |= 0x0001;
		}
		break;

	 case PLT_Man_START_TEMP:          
			if(GpSysStat->Fan.StartTemp != Data * 10)
			{
				GpSysStat->Fan.StartTemp = Data * 10; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_Man_STOP_TEMP:          
			if(GpSysStat->Fan.StopTemp != Data * 10)
			{
				GpSysStat->Fan.StopTemp = Data * 10; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;                 
        case PLT_Man_LOADPRESS:
			if(GpSysStat->Share.LoadPress != Data)
			{
				GpSysStat->Share.LoadPress = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break;            
			
        case PLT_Man_UNLOADPRESS:            
			if(GpSysStat->Share.UnLoadPress != Data)
			{
				GpSysStat->Share.UnLoadPress = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
            break; 

		case PLT_Man_CQUNECEPRESS:
			if(GpSysStat->Main.Cfreq_Press != Data)
			{
				GpSysStat->Main.Cfreq_Press = Data; 
				GpSysStat->Share.UpdataParaFlag |= 0x0002;
			}
			break;	
		case PLT_Man_ALLOW_WRITE:
            PltAlowWrite =  TRUE;
            break;
        default:
            break;
    }
}

#if MONITOR_METER_ON
void   XYDevDataDeal(u8 *Data, u8 Len, u8 Type)
{ 
    
    switch(MeterCtrl.ReadIndex) 
//	switch(Meter2Ctrl.ReadIndex) 
	{
        case XY_VOLTAGE_A:
		memcpy((char *)&GpSysStat->MeterData.Volt_A, Data, Len);
 //           GpSysStat->MeterData.Volt_A = Data;                      //  A相电压             
            break;
        case XY_VOLTAGE_B:											 //  B相电压
        memcpy((char *)&GpSysStat->MeterData.Volt_B, Data, Len);
//			GpSysStat->MeterData.Volt_B = Data;            
            break;
        case XY_VOLTAGE_C:											 //  C相电压
        memcpy((char *)&GpSysStat->MeterData.Volt_C, Data, Len); 
//			GpSysStat->MeterData.Volt_C = Data;   
            break;
	    case XY_VOLTAGE_AB:
		memcpy((char *)&GpSysStat->MeterData.Volt_AB, Data, Len);
 //           GpSysStat->MeterData.Volt_A = Data;                      //  AB电压             
            break;
        case XY_VOLTAGE_BC:											 //  BC电压
        memcpy((char *)&GpSysStat->MeterData.Volt_BC, Data, Len);
//			GpSysStat->MeterData.Volt_B = Data;            
            break;
        case XY_VOLTAGE_CA:											 //  CA电压
        memcpy((char *)&GpSysStat->MeterData.Volt_CA, Data, Len); 
//			GpSysStat->MeterData.Volt_C = Data;   
            break;
        case XY_CURRENT_A:
        memcpy((char *)&GpSysStat->MeterData.Current_A, Data, Len);
		//fengyang 2018-4-12 13:57:03
		//	GpSysStat->MeterData.Current_A /= 100;	
		//	GpSysStat->MeterData.Current_A;			//  A相电流
            break;
        case XY_CURRENT_B:
        memcpy((char *)&GpSysStat->MeterData.Current_B, Data, Len);
		//	GpSysStat->MeterData.Current_B;                   //  B相电流
            break;
        case XY_CURRENT_C:
        memcpy((char *)&GpSysStat->MeterData.Current_C, Data, Len);
		//	GpSysStat->MeterData.Current_C;                  //  C相电流
            break;
        case xy_ACTIVE_POWER_TOTAL:
		memcpy((char *)&GpSysStat->MeterData.Active_Power_Total, Data, Len);
//			GpSysStat->MeterData.Active_Power_Total = Data;          //  总有功功率
            break;             
        case xy_REACTIVE_POWER_TOTAL:
		memcpy((char *)&GpSysStat->MeterData.Reactive_Power_Total, Data, Len);
//			GpSysStat->MeterData.Reactive_Power_Total = Data;       //  总无功功率
            break;   
		case XY_APPARENT_POWER_TOTAL:
		memcpy((char *)&GpSysStat->MeterData.Apparent_Power_Total, Data, Len);  
//			GpSysStat->MeterData.Apparent_Power_Total = Data;        //  总视在功率
            break;   
		case XY_POWER_FACTOR_TOTAL:
		memcpy((char *)&GpSysStat->MeterData.Power_Factor_Total, Data, Len);  
//			GpSysStat->MeterData.Power_Factor_Total = Data;         //  总功率因素
            break;   
		case XY_FREQUENCY:
		memcpy((char *)&GpSysStat->MeterData.Frequency, Data, Len);
//			GpSysStat->MeterData.Frequency = Data;                 // 频率
            break;   
	
		case XY_POSITIVE_ACTIVE_POWER:
		memcpy((char *)&GpSysStat->MeterData.Positive_Active_Power, Data, Len); 
//			GpSysStat->MeterData.Positive_Active_Power = Data; //  正用功电能  高位
            break;   
//		case XY_POSITIVE_ACTIVE_POWER_LOW:
//		 
//			GpSysStat->MeterData.Positive_Active_Power_Low = Data; //  正用功电能  低位
//            break;   
//		case XY_POSITIVE_ACTIVE_POWER_DEC:
//		memcpy((char *)&GpSysStat->MeterData.Positive_Active_Power_Dec, Data, Len);	 

//			GpSysStat->MeterData.Positive_Active_Power_Dec = Data;  //  正用功电能  小数位
 //           break;  
//		case  XY_LINE_NET:
//			memcpy((char *)&GpSysStat->MeterData.Line_Net, Data, Len);
//			break;
		case  XY_CT:
		memcpy((char *)&GpSysStat->MeterData.CT, Data, Len);
			break;
		//流量计数据解析		
		case FLOW_TRANSIENT_FLOW:	
		memcpy((char *)&GpSysStat->FlowData.Transient_Flow.Array, Data, Len);	
//			GpSysStat->FlowData.Transient_Flow = Data;  			// 瞬时流量  
            break; 
		case FLOW_FREQUENCY:
		memcpy((char *)&GpSysStat->FlowData.Frequency.Array, Data, Len);	
//			GpSysStat->FlowData.Frequency = Data;  					// 频率
            break; 
		case FLOW_PRESSURE:	
		memcpy((char *)&GpSysStat->FlowData.Pressure.Array, Data, Len);	
//			GpSysStat->FlowData.Pressure = Data;  					// 压力
            break; 
		case FLOW_TEMP:	
		memcpy((char *)&GpSysStat->FlowData.Temp.Array, Data, Len);	
//			GpSysStat->FlowData.Temp = Data;  						// 温度
            break; 
		case FLOW_DENSITY:	
		memcpy((char *)&GpSysStat->FlowData.Density.Array, Data, Len);	
//			GpSysStat->FlowData.Density = Data;  					// 密度 
            break; 
		case FLOW_TOTAL_FLOW:	
		memcpy((char *)&GpSysStat->FlowData.Total_Flow.Array, Data, Len);	
//			GpSysStat->FlowData.Total_Flow = Data;  				// 累积流量	
            break; 
		case FLOW_NUMBER:	
		memcpy((char *)&GpSysStat->FlowData.Number, Data, Len);	
//			GpSysStat->FlowData.Number = Data;  					// 流量计站号
            break; 
		
        default:
            break;
    }
}
#endif



bool    RemoteWritePara = FALSE;


bool Server_Writer_Data_Buf(u16 addr, u16 data, u8 Len)
{
	 bool Err = FALSE;
	 if(Server_Data_Buf.Start != ((Server_Data_Buf.End +1)%SERVER_DATA_MAX_BUF))
	 {
		 
		 Server_Data_Buf.Adrr[Server_Data_Buf.End] =addr;
		 Server_Data_Buf.Data[Server_Data_Buf.End] =data;
		 
		 Server_Data_Buf.End = (Server_Data_Buf.End +1)%SERVER_DATA_MAX_BUF;
		 Server_Data_Buf.Flag = 1;
		 RemoteWritePara = TRUE;
	 }
	 else
	 {
		 Err = TRUE;
	 }
	 return Err;
 }

 
bool Server_Writer_Data_SendBuf(u16 *addr, u16 *data)
{
	 bool Err = TRUE;
	 if(Server_Data_Buf.Start != Server_Data_Buf.End)
	 {
		 
		 *addr = Server_Data_Buf.Adrr[Server_Data_Buf.Start];
		 *data = Server_Data_Buf.Data[Server_Data_Buf.Start];
		
		 Server_Data_Buf.Start = (Server_Data_Buf.Start+1) % SERVER_DATA_MAX_BUF;
	 }
	 else
	 {
		 Server_Data_Buf.Flag = 0;
		 Err = FALSE;
	 }
	 return Err;
}


void Plt_PreAlarm_Deal(u16 Code)
{
	switch(Code)
	{
		case 1:	  //排气温度高预警		
//			AlmStat.PreAlarm.Bits.OverMaxTemp = TRUE;	
			break;
		case 2:		//系统温度高	
			break;
		case 3:		//温度3高	
			break;
//		case 8:		//油滤器使用时间到	
//			AlmStat.PreAlarm.Bits.OverMaxOilFiltTime = TRUE;	
//			break;
//		case 9:		//油分器使用时间到	
//			AlmStat.PreAlarm.Bits.OverMaxOilSepaTime = TRUE;
//			break;
//		case 10:	//空滤器使用时间到	
//			AlmStat.PreAlarm.Bits.OverMaxGasFiltTime = TRUE;
//			break;
//		case 11:	//润滑油使用时间到	
//			AlmStat.PreAlarm.Bits.OverMaxlubeTime = TRUE;			
//			break;
//		case 12:	//润滑脂使用时间到	
//			AlmStat.PreAlarm.Bits.OverMaxGreaseTime = TRUE;			
//			break;
//		case 13:			
//			break;
//		case 14:			
//			break;
//		case 15:			
//			break;
//		case 16:			
//			break;
//		case 17:			
//			break;
//		case 18:			
//			break;
		default :
			break;
		
	}
	return ;
}

void Plt_RunStata_Deal(u16 Code)
{
	switch(Code)
	{
		case 1:			//故障停机
			GpSysStat->Share.MachineStat = STOP_STATE;
			break;
		case 2:			//急停
			GpSysStat->Share.MachineStat = STOP_STATE;
			break;
		case 3:			//停机延时
			GpSysStat->Share.MachineStat = STOP_DELAY_RUN_STATE;
			break;
		
//		case 4:			
//			break;
//		case 5:			
//			break;
//		case 6:			
//			break;
		case 7:			//自动卸载运行
			GpSysStat->Share.MachineStat = KONG_ZAI_RUN_STATE;
			break;
		case 8:			//自动加载运行
			GpSysStat->Share.MachineStat = JIA_ZAI_RUN_STATE;
			break;
		case 9:			//空车过久停机
			GpSysStat->Share.MachineStat = KONG_JIU_STOP_STATE;
			break;
		case 10:		//设备已停止	
			GpSysStat->Share.MachineStat = STOP_STATE;
			break;
//		case 11:			
//			break;
//		case 12:			
//			break;
		
//		case 16:			
//			break;
		case 17:		//手动卸载运行
			GpSysStat->Share.MachineStat = KONG_ZAI_RUN_STATE;			
			break;
		case 18:		//手动加载运行	
			GpSysStat->Share.MachineStat = JIA_ZAI_RUN_STATE;
			break;
		
//		case 19:			
//			break;
//		case 21:			
//			break;
//		case 22:			
//			break;
		case 23:		//温度过低	
			AlmStat.PreAlarm.Bits.OverMinTemp = TRUE;	
			break;
//		case 24:			
//			break;
//		case 25:			
//			break;
		default :
			break;
		
	}
	return ;
}

void Plt_Fault_Deal(u16 Code)
{
	switch(Code)
	{
		case 0:
			AlmStat.Alarm.Flag = 0;
			break;
		case 1:			//主机过载
			AlmStat.Alarm.Bits.OverMaxCurr = TRUE;	
			break;
		case 2:			//主机不平衡
			AlmStat.Alarm.Bits.CurrImbalance = TRUE;	
			break;
//		case 3:			
//			break;
		case 4:			//风机过载
			AlmStat.Alarm.Bits.FanOverCurr = TRUE;	
			break;
	
		case 6:			//温度1传感器失灵
//			AlmStat.Alarm.Bits.TempSen1Fault = TRUE;
			break;
		case 7:			//：温度1高
//			AlmStat.Alarm.Bits.OverMaxTemp1 = TRUE;
			break;
	
		case 10:		//压力1传感器失灵	
//			AlmStat.Alarm.Bits.PresSen1Fault = TRUE;	
			break;
		case 11:		//压力1高	
//			AlmStat.Alarm.Bits.OverMaxPres1 = TRUE;	
			break;
//		case 12:		//压力2传感器失灵	
//			break;
//		case 13:		//压力2高	
//			break;
//		case 14:		//压差高停机	
//			break;
////		case 16:			
////			break;
//		case 17:		//预警过久停机	
//			break;
		case 18:		//电压过低
			AlmStat.Alarm.Bits.SupplyVoltageOverMin = TRUE;			
			break;
		
		case 19:		//电压过高	
			AlmStat.Alarm.Bits.SupplyVoltageOverMax = TRUE;
			break;
		case 20:		//相序错误 错相	
//			AlmStat.Alarm.Bits.PluseError = TRUE;
			break;
		case 21:		//相序错误	缺相
			AlmStat.Alarm.Bits.LackPhase = TRUE;
			break;
		case 22:		//缺水
//			AlmStat.Alarm.Bits.LackWater = TRUE;
			break;
//		case 23:			
//			break;
//		case 24:			
//			break;
//		case 25:			
//			break;
//		case 26:			
//			break;
		case 27:		//主机过载
			AlmStat.Alarm.Bits.OverMaxCurr = TRUE;			
			break;
		case 28:		//风机过载	
			AlmStat.Alarm.Bits.FanOverCurr = TRUE;	
			break;
//		case 29:			
//			break;
//		case 30:			
//			break;
		case 31:		//	主机变频器故障I/O
			AlmStat.Alarm.Bits.MainVfdAlarm = TRUE;
			break;
		case 32:		//	风机变频器故障I/0
			AlmStat.Alarm.Bits.FanVfdAlarm = TRUE;	
			break;
		case 33:		//	读主机变频器故障
//			AlmStat.Alarm.Bits.MainVfdAlarm = TRUE;
			break;
//		case 34:			
//			break;
		case 35:		//	主机变频器故障（通信读取）
			AlmStat.Alarm.Bits.MainVfdAlarm = TRUE;
			break;
		case 36:		//	读风机变频器故障
//			AlmStat.Alarm.Bits.FanVfdAlarm = TRUE;	
			break;
//		case 37:			
//			break;		
		case 38:		//	风机变频器故障（通信读取）
			AlmStat.Alarm.Bits.FanVfdAlarm = TRUE;	
			break;
//		case 39:		//	温度2传感器失灵
//			break;
//		case 40:		//	温度2高
//			break;
//		
//		case 41:		//	温度3传感器失灵
//			break;
//		case 42:		//	温度3高
//			break;

		default :
			break;	
		
	}
	return ;
}

	
