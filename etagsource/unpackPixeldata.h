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


#include "pixeldataCommon.h"

//适用于{0,0,295,127,w,r,1,4736} SAP_header or  {0,0,295,127,w,r,1,4736,0,4088}  SSP_header
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


//SAFS header例子{0,0,295,127,w,r,1,4736,2},{0,0,1023,739,w,b,1,95232,24}
struct SAFS_header_struct
{
	uint32 lefttopHorizontal;
	uint32 lefttopVertical;

	uint32 rightbuttonHorizontal;//=horizontal-1
	uint32 rightbuttonVertical;//=vertical-1

	char backcolor ;
	char forecolor;
	uint8 driver_type ;
	uint32 pixeldataSize;

	uint16 totalSlices;//总共分片数
};
typedef struct SAFS_header_struct SAFS_header;



//[560,zlib1.2]  FCSSP中的格式化头
struct FCSSP_Formatter_struct
{
	uint8* csspPointer;//原字符串FCSSP中的该cssp压缩二进制的起始指针

	uint16 formatterLength;//[560,zlib1.2]长度为13
	uint32 csspLength;//[560,zlib1.2] CSSP长度为560
	uint8* compressor;//string为"zlib1.2"
};
typedef struct FCSSP_Formatter_struct FCSSP_Formatter;




//三色屏的完整分片压缩数据描述
struct FFCS_Details_struct
{
	uint8* etagAbstract;//string

	uint8* SAFSheader1;//string
	FCSSP_Formatter** fcsspFormaters1;
	uint16 fcsspFormaters1_qty;

	uint8* SAFSheader2;//string
	FCSSP_Formatter** fcsspFormaters2;
	uint16 fcsspFormaters2_qty;
};
typedef struct FFCS_Details_struct FFCS_Details;



#if defined _itrackerDebug_
extern void printBracketHeader(BracketHeader* header);
extern void printSAFS_header(SAFS_header* header);
extern void printFCSSP_Formatter(FCSSP_Formatter* formatter);
extern void printFFCS_Details(FFCS_Details * ffcs);
#endif

//void freeCSSP_Formatter(CSSP_Formatter* formatter);





#endif /* UNPACKPIXELDATA_H_ */
