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

extern void copyCharArrayIntoBuffer(const unsigned char * source,  uint16 length, unsigned char * target);

#endif /* CTOOLS_H_ */
