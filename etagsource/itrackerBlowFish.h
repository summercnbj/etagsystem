#ifndef _itrackerblowfish_
#define _itrackerblowfish_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "itrackerWinPrintf.h"
#if defined _itrackerDebug_ &&  !defined ITRACKER_JNI
//#define _itrackerDebug_BLOWFISH_
#endif
typedef struct
{
	int *S0;
	int *S1;
	int *S2;
	int *S3;  //s-boxes
	int *P;   //p-array to contains ^password


} BlowFishStruct;



extern BlowFishStruct * blowFishInit_itra( char * C_key);
extern void clearBlowFishStruct_itra(BlowFishStruct * bfs);


////return bytearray without '\0'; length saved into *encryptedSize. output has not freed
//extern  char* encrypting_itra(const  char* sourceString, int offset, int * encryptedSize, BlowFishStruct *bfs);//into byte[] without '\0'
//
////return string with '\0';  output has not freed
//extern  char* decrypting_itra(const  char* sourceByteArray, int sourceLength ,BlowFishStruct *bfs);//from byte[], into string with '\0'

////freed sourceString
////return bytearray without '\0'; length saved into *encryptedSize. output has not freed
//extern  char* encrypting_itraFree( char* sourceString, int offset, int * encryptedSize, BlowFishStruct *bfs);//into byte[] without '\0'

////freed sourceByteArray
////return string with '\0';  output has not freed
//extern  char* decrypting_itraFree( char* sourceByteArray, int sourceLength ,BlowFishStruct *bfs);//from byte[], into string with



extern uchar* encrypting_itraCA(const char* sourceString,uint16 length, int offset, uint16 * encryptedSize, BlowFishStruct *bfs);
extern  struct CharArray * decrypting_itraCA(const char* sourceByteArray, int sourceLength ,BlowFishStruct *bfs);



/**
 * @passwd 是blowfish密码
 * @source 明文
 * @len 明文长度
 * @encryptedSize 加密后的长度存入encryptedSize
 * @return malloc的密文 或者NULL(内存分配失败)
 */
extern uchar* blowfishEnc(char*passwd, char* source,int len, uint16* encryptedSize);


/**
 * @passwd 是blowfish密码
 * @csEncryptedString 密文
 * @encryptedSize 密文长度
 * @decryptSize 解密后的长度存入decryptSize
 * @return malloc的明文 或者NULL(内存分配失败)
 */
extern uchar* blowfishDec(char*passwd, char* csEncryptedString,int encryptedSize, uint16 *decryptSize);

//~~~~~~~~~~~~~~~functions not api~~~~~~~~~~~~~~~~
extern void SetKey_itra(char* key,BlowFishStruct *bfs);
extern void processTable_itra(int xl, int xr, int table[], int tableSize,BlowFishStruct *bfs);
extern int F_itra(int x, BlowFishStruct *bfs);
extern int processBlock_itra(const char* in, int inoff, char* out, int outoff, int inSize, int outSize,BlowFishStruct *bfs,char select);
extern void encryptBlock_itra(const char* src, int srcIndex, char* dst, int dstIndex,BlowFishStruct *bfs);
extern void decryptBlock_itra(const char* src, int srcIndex, char* dst, int dstIndex,BlowFishStruct *bfs);
extern int BytesTo32bits_itra(const char* b, int i);
extern void Bits32ToBytes_itra(const int in, char* b, int offset);




#endif




