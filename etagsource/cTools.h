/*
 * cTools.h
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef CTOOLS_H_
#define CTOOLS_H_

#include <stdio.h>  //for NULL
#include <stdlib.h>  //for malloc and free
#include <string.h>  //for memset


//#define myPrintf printf
//#define myMalloc malloc
//#define myFree free




#define VERSION_BYTE_LENGTH 2
//分成2bytes。   "87a.a66"-->87,0; "  87.6a6"-->87,6;  " 287.6 9"-->31,6;  因为287超过了256
extern int8 versionBytes(uint8* version, uint8* buffer, uint8 bufferlen);
extern void versionBytes2String(uint8* twoBytes, uint8* buf, uint16 buf_length);


//在原数据的基础上重新排列。在使用前请复制原来的数据
extern void doOffsetByShortPW(uint8* shortPW, uint8* data, uint16 data_length);

//在offset数据的基础上复原原来数据，长度不变。在使用前请复制原来的数据
extern void restoreOffsetByShortPW(uint8* shortPW, uint8* offsetData, uint16 offsetData_length);



//~~~~~~~~~~~~~~~~~~from itrackerString.c~~~~~~~~~~~~~~~~~~~~~~~~~~
extern void strcatChar(uint8* string, char c);
extern int stringlen(uint8* string);



//~~~~~~~~~~~~~~~~~~from itrackerMath.c~~~~~~~~~~~~~~~~~~~~~~~~~~
extern uint32 ceil(uint32 num,uint32 dividor);

//from itrackerMath.c
extern uint32 get_ceiling_bytes_len( uint32 bits_len);
extern void uint16_into_big_endian_bytes(uint16 number, uint8* buffer, uint16 buffer_len);
extern uint16 getUint16_big_endian( uint8* p );


#endif /* CTOOLS_H_ */
