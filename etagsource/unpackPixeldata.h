/*
 * unpackPixeldata.h
 *
 *  Created on: 2019年10月24日
 *      Author: summer
 */

#ifndef UNPACKPIXELDATA_H_
#define UNPACKPIXELDATA_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"


//{0,0,295,127,w,r,1,4736} or  {0,0,295,127,w,r,1,4736,0,4088}
struct bracketHeader_struct
{
	uint16 headerLength;//{0,0,295,127,w,r,1,4736}长度为24

	uint32 horizontal ;
	uint32 vertical ;
	char backcolor ;
	char forecolor;
	uint8 driver_type ;
	uint32 pixeldataSize;

	uint32 number;
	uint32 piecelen;
};

typedef struct bracketHeader_struct BracketHeader;


//[560,zlib1.2]  FCSSP中的格式化头
struct FCSSP_Formatter_struct
{
	uint16 formatterLength;//[560,zlib1.2]长度为13

	uint32 csspLength;//[560,zlib1.2] CSSP长度为560
	uint8* compressor;//string为"zlib1.2"

	uint8* formatterStart;//原字符串FCSSPs中的该FCSSP起始指针
};
typedef struct FCSSP_Formatter_struct FCSSP_Formatter;


//价签概要[296,128,wbr](ETAG abstract参见《电子价签云服务器接口规范三(价签布局，ETAG LAYOUT)》)
struct ETAG_abstract_struct
{
	uint16 etagLength;//[296,128,wbr]的长度为13

	uint32 horizontal;//296
	uint32 vertical;//128
	uint8* colors;//string "wbr"
};
typedef struct ETAG_abstract_struct ETAG_abstract;

#if defined _itrackerDebug_
extern void printBracketHeader(BracketHeader* header);
extern void printFCSSP_Formatter(FCSSP_Formatter* formatter);
extern void printETAG_abstract(ETAG_abstract* abstract);
#endif

//void freeCSSP_Formatter(CSSP_Formatter* formatter);






#endif /* UNPACKPIXELDATA_H_ */
