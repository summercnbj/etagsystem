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


extern int stringlen(uint8* string);


#define VERSION_BYTE_LENGTH 2
//分成2bytes。   "87a.a66"-->87,0; "  87.6a6"-->87,6;  " 287.6 9"-->31,6;  因为287超过了256
extern int8 versionBytes(uint8* version, uint8* buffer, uint8 bufferlen);

//在原数据的基础上重新排列。在使用前请复制原来的数据
extern void doOffsetByShortPW(uint8* shortPW, uint8* data, uint16 data_length);

//在offset数据的基础上复原原来数据，长度不变。在使用前请复制原来的数据
extern void restoreOffsetByShortPW(uint8* shortPW, uint8* offsetData, uint16 offsetData_length);

#endif /* CTOOLS_H_ */
