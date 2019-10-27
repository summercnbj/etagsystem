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


#include "bleDriver.h"


//~~~~~~~~~~~~~~~~内存变量~~~~~~~~~~~~~~~~~~~~~~~
extern uint8* getGwBleShortPW();
extern uint8* getNewGwBleShortPW();

//~~~~~~~~~~~~~~~~上面是内存变量~~~~~~~~~~~~~~~~~~~~~~~









extern void bleSend2Uart(uint8* data,uint16 data_length);


#endif /* GWBLEDRIVER_H_ */
