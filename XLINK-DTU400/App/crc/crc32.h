
#ifndef __CRC32_H__
#define __CRC32_H__

#ifndef  __INCRC32
#define  CRC32_EXTERN  extern 
#else
#define  CRC32_EXTERN 

#endif


typedef struct {
    unsigned long crc;
}CRC32_CTX;
 
CRC32_EXTERN void CRC32_Init(CRC32_CTX *ctx);

 
CRC32_EXTERN void CRC32_Update(CRC32_CTX *ctx, const unsigned char *data,  unsigned long len);

 
CRC32_EXTERN void CRC32_Final(CRC32_CTX *ctx);

#endif
