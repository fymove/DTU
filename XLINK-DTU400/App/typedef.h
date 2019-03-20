/*****************************************************************************
文件名    :    typedef.h
说明        :    数据类型重定义
******************************************************************************/

#ifndef _TYPE_DEF_H_
#define _TYPE_DEF_H_
#include <stdint.h>

typedef void    OS_EVENT;

#ifndef TRUE
#define TRUE        1
#endif                                                                  /*  TRUE                        */

#ifndef FALSE
#define FALSE       0
#endif                                                                  /*  FALSE                       */

#ifndef NULL
#define NULL        0ul
#endif                                                                  /*  NULL                       */

typedef int                INT;
typedef unsigned int    UINT;

typedef unsigned char    uchar;
typedef unsigned int    uint;


/* These types must be 8-bit integer */
typedef char            CHAR;
typedef unsigned char    UCHAR;
typedef unsigned char    BYTE;
typedef unsigned char     uchar;
/* These types must be 16-bit integer */
typedef short            SHORT;
typedef unsigned short    USHORT;
typedef unsigned short    WORD;
typedef unsigned short    WCHAR;

/* These types must be 32-bit integer */
typedef long            LONG;
typedef unsigned long    ULONG;
typedef unsigned long    DWORD;


typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity                           */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity                           */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity                           */
typedef signed   short INT16S;                   /* Signed   16 bit quantity                           */
typedef unsigned int   INT32U;                   /* Unsigned 32 bit quantity                           */
typedef signed   int   INT32S;                   /* Signed   32 bit quantity                           */
typedef float          FP32;                     /* Single precision floating point                    */
typedef double         FP64;                     /* Double precision floating point                    */

/** @addtogroup Exported_types
  * @{
  */  
/*!< STM32F10x Standard Peripheral Library old types (maintained for legacy purpose) */
typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef const int32_t sc32;  /*!< Read Only */
typedef const int16_t sc16;  /*!< Read Only */
typedef const int8_t sc8;   /*!< Read Only */


typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef const uint32_t uc32;  /*!< Read Only */
typedef const uint16_t uc16;  /*!< Read Only */
typedef const uint8_t uc8;   /*!< Read Only */

typedef signed char bool;

typedef enum {
    ADDR_TYPE_BIT_PARA = 0,
    ADDR_TYPE_BIT_IN,
    ADDR_TYPE_BIT_Q,
    ADDR_TYPE_STRING,
    ADDR_TYPE_OTHER,
}ADDR_TYPE_ENUM;


#endif

