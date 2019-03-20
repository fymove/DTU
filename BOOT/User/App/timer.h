#ifndef _TIMER_H_
#define _TIMER_H_

typedef union {
    u8  Flag;
    struct {
        u8  T1s: 1;
    }Bits;
    
}TIMER_FLAG_UNION;

extern TIMER_FLAG_UNION   TimeFlag;


#endif
