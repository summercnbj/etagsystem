/*
 * etagBle.h
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef ETAGBLEPARSE_H_
#define ETAGBLEPARSE_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"
#include "etagStateMachine.h"


#include "bleDriver.h"
	//解压CSSP到SSP
#define SSP_LENGTH_MAX (ETAG_FLASH_SECTOR_SIZE+ SSPHEADER_LENGTH_MAX)


extern void slaveParseBlePackage(uint8* package,uint32 package_length);




#endif /* ETAGBLEPARSE_H_ */
