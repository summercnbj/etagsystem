/*
 * gwWifiCache2Uart.h
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */

#ifndef GWWIFICACHES_H_
#define GWWIFICACHES_H_
#include "cacheManager.h"
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"
#include "gwWifiDriver.h"

extern int8 appendCache2AllUarts( uint8* chararray, uint32 length);

extern int8 appendCache2Uart( uint8* etagMacBytes, uint8* chararray, uint32 length);

extern int8 appendCache2Cloud( uint8* chararray, uint32 length);

#endif /* GWWIFICACHES_H_ */
