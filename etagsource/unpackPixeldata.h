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



struct bracketHeader_struct
{
	uint32 horizontal ;
	uint32 vertical ;
	uint8 driver_type ;
	char backcolor ;
	char forecolor;
	uint32 pixeldataSize;

	uint32 number;
	uint32 piecelen;
};

typedef struct bracketHeader_struct BracketHeader;




#endif /* UNPACKPIXELDATA_H_ */
