/*
 * bleDriver.h
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#ifndef GWBLEDRIVER_H_
#define GWBLEDRIVER_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"


extern void sendUart(uint8* data,uint16 data_length);

//TODO 被驱动调用：从uart协议里解出的data
extern void wifiParseUart(uint8* data,uint16 data_length);

#endif /* GWBLEDRIVER_H_ */
