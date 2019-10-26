/*
 * pixeldataCommon.h
 *
 *  Created on: 2019年10月24日
 *      Author: summer
 */

#ifndef PIXELDATACOMMON_H_
#define PIXELDATACOMMON_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"

#define SSPHEADER_LENGTH_MAX 48  // (SSPheader len > SAFSheader len > SAPheader len)

//价签概要[296,128,wbr](ETAG abstract参见《电子价签云服务器接口规范三(价签布局，ETAG LAYOUT)》)
struct ETAG_abstract_struct
{
	uint16 abstractLength;//[296,128,wbr]的长度为13

	uint32 horizontal;//296
	uint32 vertical;//128
	uint8* colors;//string "wbr"
};
typedef struct ETAG_abstract_struct ETAGabstract;





#define DRIVER_TYPE_by_VERTICAL 1
#define DRIVER_TYPE_by_HORIZONTAL 2

#define CHAR_COLOR_WHITE 'w'
#define CHAR_COLOR_BLACK 'b'
#define CHAR_COLOR_RED 'r'


//根据驱动扫描是横向还是纵向，计算SAP里的pixeldata size
extern uint32 getSizeOfSingleAreaPixeldata(uint32 horizontal, uint32 vertical, uint8 driver_type);

extern void freeETAGabstract(ETAGabstract* abstract);

extern uint8* formEtagAbstract(uint32 horizontal, uint32 vertical, char backcolor,char forecolor1,char forecolor2);

extern ETAGabstract* parseETAG_abstract(uint8* abstract, uint32 abstract_length);

#if defined _itrackerDebug_
extern void printETAGabstract(ETAGabstract* abstract);
#endif

#endif /* PIXELDATACOMMON_H_ */
