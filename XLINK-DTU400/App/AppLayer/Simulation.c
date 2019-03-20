#define _InSimulation
#include "simulation.h"

#include "struct.h"
#include "app_para.h"
#include "app_json.h"

#ifndef PRJ_RELEASE
 short TotalParaLen;
void    Simulation(void)
{
   
    
    TotalParaLen = SYS_PARA_BUF_SIZE;
    if(TotalParaLen != (DEV_PARA_SIZE + NET_PARA_SIZE + 6)) {
        while(1);
    }
    if(0 != (TotalParaLen % 4)) {
        while(1);
    }      
   
    TotalParaLen = USR_PARA_BUF_SIZE;
    if(TotalParaLen != (MAX_TIME_SIZE + 6)) {
        while(1);
    }
    if(0 != (TotalParaLen % 4)) {
        while(1);
    }   

    TotalParaLen = OTH_INFO_BUF_SIZE;
    if(TotalParaLen != (ERR_INFO_SIZE + 6)) {
        while(1);
    }
    if(0 != (TotalParaLen % 4)) {
        while(1);
    }

    TotalParaLen = ALM_INFO_BUF_SIZE;
    if(TotalParaLen != (sizeof(ALARM_FLAG_UNION) + sizeof(PREALM_FLAG_UNION) + 8)) {
        while(1);
    }
    if(0 != (TotalParaLen % 4)) {
        while(1);
    }

//    ProDataDealTest();    
}
#endif
