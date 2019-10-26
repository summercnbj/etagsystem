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

/*
 * 适用于 SSPheader 例子   {0,0,295,127,w,r,1,4736,0,4088}   or
 *     SAPheader 例子   {0,0,295,127,w,r,1,4736}  or
 *     SAFSheader例子   {0,0,295,127,w,r,1,4736,2},{0,0,1023,739,w,b,1,95232,24}
 */
struct bracketHeader_struct
{
	uint16 headerLength;//{0,0,295,127,w,r,1,4736,2,4092} SSPheader字节长度为31

	uint32 lefttopHorizontal;
	uint32 lefttopVertical;

	uint32 rightbuttonHorizontal;//=horizontal-1
	uint32 rightbuttonVertical;//=vertical-1

	char backcolor ;
	char forecolor;
	uint8 driver_type ;
	uint32 pixeldataSize;

	uint32 number;
	uint32 sliceLen;
};
typedef struct bracketHeader_struct BracketHeader;

//{0,0,295,127,w,r,1,4736,2,4092}字节长度为31
typedef BracketHeader SSPheader;


struct SAPheader_struct
{
	uint16 headerLength;//{0,0,295,127,w,r,1,4736}字节长度为24

	uint32 lefttopHorizontal;
	uint32 lefttopVertical;

	uint32 rightbuttonHorizontal;//=horizontal-1
	uint32 rightbuttonVertical;//=vertical-1

	char backcolor ;
	char forecolor;
	uint8 driver_type ;
	uint32 pixeldataSize;
};
typedef struct SAPheader_struct SAPheader;


//SAFS header例子{0,0,295,127,w,r,1,4736,2}共计2个分片数据,{0,0,1023,739,w,b,1,95232,24}共计24个分片数据
struct SAFSheader_struct
{
	uint16 headerLength;//{0,0,295,127,w,r,1,4736,2}字节长度为26

	uint32 lefttopHorizontal;
	uint32 lefttopVertical;

	uint32 rightbuttonHorizontal;//=horizontal-1
	uint32 rightbuttonVertical;//=vertical-1

	char backcolor ;
	char forecolor;
	uint8 driver_type ;
	uint32 pixeldataSize;

	uint32 totalSlices;//总共分片数
};
typedef struct SAFSheader_struct SAFSheader;



//[560,zlib1.2]  FCSSP中的格式化头
struct FCSSP_Formatter_struct
{
	uint8* fcsspPointer;//原字符串FCSSP的起始指针，长度为formatterLength+csspLength.要发往uart.
	uint8* csspPointer;//原字符串FCSSP中的该cssp压缩二进制的起始指针

	uint16 formatterLength;//[560,zlib1.2]长度为13
	uint32 csspLength;//[560,zlib1.2] CSSP长度为560
	//以上两部分长度构成了总字节数

	uint8* compressor;//string为"zlib1.2"  malloc
};
typedef struct FCSSP_Formatter_struct FCSSPformatter;




/*
总结：最后给FFCS计算MD5_16 16HEX转化为8bytes
 FFCS = ABSTRACT + SAFS0 + SAFS1
   = ABSTRACT + (SAFS header + FCSSPs) + (SAFS header + FCSSPs)
   = ABSTRACT + (SAFS header + 多个(FCSSP Formatter + CSSP(压缩二进制)))
              + (SAFS header + 多个(FCSSP Formatter + CSSP(压缩二进制)))
               其中ABSTRACT例子[296,128,wbr]
 SAFS = SAFS header + FCSSPs
              其中SAFS header例子{0,0,295,127,w,r,1,4736,2},{0,0,1023,739,w,b,1,95232,24}
 FCSSP = FCSSP Formatter + CSSP(压缩二进制)
             其中FCSSP Formatter例子[560,zlib1.2]

 CSSP二进制 由 SSP压缩转化而来。

 SSP = SSP header + 分片点阵数据(pixeldata slice)
             其中SSP header例子{0,0,1023,739,w,r,1,95232,22,4092}第22条数据长度4092字节。(从0条开始计数)
 */

//三色屏的完整分片压缩数据描述
struct FFCS_Details_struct
{
	ETAGabstract* etagAbstract;

	SAFSheader* SAFSheader0;//
	FCSSPformatter** fcsspFormaters0;
	uint16 fcsspFormaters0_qty;

	SAFSheader* SAFSheader1;//
	FCSSPformatter** fcsspFormaters1;
	uint16 fcsspFormaters1_qty;
};
typedef struct FFCS_Details_struct FFCSdetails;


extern SSPheader* parseSSPheader(uint8* header, uint32 header_length);
extern SAPheader* parseSAPheader(uint8* header, uint32 header_length);
extern SAFSheader* parseSAFSheader(uint8* header, uint32 header_length);

#if defined _itrackerDebug_
extern void printBracketHeader(BracketHeader* header);
extern void printSSPheader(SSPheader* header);
extern void printSAPheader(SAPheader* header);
extern void printSAFSheader(SAFSheader* header);
extern void printFCSSPformatter(FCSSPformatter* formatter);
extern void printFFCSdetails(FFCSdetails * ffcs);
#endif

extern void freeBracketHeader(BracketHeader* header);
extern void freeSSPheader(SSPheader* header);
extern void freeSAPheader(SAPheader* header);
extern void freeSAFSheader(SAFSheader* header);
extern void freeFCSSPformatter(FCSSPformatter* structFormatter);
extern void freeFFCSdetails(FFCSdetails* details);


/*
 * 解析FCSSP中的formatter到结构体
 * 将[560,zlib1.2]byte0~byte559中的[560,zlib1.2]解析成结构体.其中的560是CSSP长度，压缩结果的字节串。
 */
extern FCSSPformatter* parseFCSSPformatter(uint8* formatter, uint32 formatter_length);



/*
 * 从FCSSPs串中得到第number个FCSSP的结构体描述。用完要myFree()
 * 从[560,zlib1.2]byte0~byte559[89,zlib1.2]byte0~byte88多个FCSSP中获取到第number个FCSSP
 *
 * FCSSP0FCSSP1FCSSP2FCSSP3......  得到其中的第几个FCSSP的结构体描述
 */
extern FCSSPformatter* getNumberFCSSP(uint8* fcssps,uint32 fcssps_length, uint32 number);


/*  网关调用解析总点阵数据。并将每个FCSSP通过uart-->ble发往etag
总结：最后给FFCS计算MD5_16 16HEX转化为8bytes
 FFCS = ABSTRACT + SAFS0 + SAFS1
   = ABSTRACT + (SAFS header + FCSSPs) + (SAFS header + FCSSPs)
   = ABSTRACT + (SAFS header + 多个(FCSSP Formatter + CSSP(压缩二进制)))
              + (SAFS header + 多个(FCSSP Formatter + CSSP(压缩二进制)))
               其中ABSTRACT例子[296,128,wbr]
 SAFS = SAFS header + FCSSPs
              其中SAFS header例子{0,0,295,127,w,r,1,4736,2},{0,0,1023,739,w,b,1,95232,24}
 FCSSP = FCSSP Formatter + CSSP(压缩二进制)
             其中FCSSP Formatter例子[560,zlib1.2]

 CSSP二进制 由 SSP压缩转化而来。

 SSP = SSP header + 分片点阵数据(pixeldata slice)
             其中SSP header例子{0,0,1023,739,w,r,1,95232,22,4092}第22条数据长度4092字节。(从0条开始计数)
 */
extern FFCSdetails* parseFFCS(uint8* ffcs, uint32 ffcs_length);


/*
 * 发送一条md5_16_bytes + FFCS
 */
extern int8 sendOneFFCS(uint8* etagMacBytes, uint8 etagState, uint8* md5_16_bytes, uint8* ffcs, uint32 ffcs_length);

/*
 * etagBle里调用，解析并解压缩FCSSP得到自明的SSP分片数据(带有SSPheader)
 * 将FCSSP [560,zlib1.2]byte0~byte559中的byte0~byte559解压缩到SSPbuffer里，长度返回为*SSPbuffer_len。
 */
extern int8 uncompressFCSSPtoSSP(uint8* fcssp, uint32 fcssp_length, uint8* SSPbuffer, uint32 *SSPbuffer_len);


/* etagBle里调用
 * 解析SSP得到SSPheader
 * slice数据在ssp + SSPheader->headerLength，长度为 SSPheader->sliceLen。
 */
extern SSPheader* parseSSP(uint8* ssp, uint32 ssp_length);




#endif /* UNPACKPIXELDATA_H_ */
