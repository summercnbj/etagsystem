/*
 * etagBleDriver.h
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#ifndef ETAGBLEDRIVER_H_
#define ETAGBLEDRIVER_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"


#include "bleDriver.h"

//~~~~~~~~~~~~~~~~内存变量~~~~~~~~~~~~~~~~~~~~~~~
extern void setEtagBattPercentage(uint8 batt);
extern uint8 getEtagBattPercentage();
extern uint8* getEtagShortPW();
extern uint8* getEtagMacBytes();
extern uint8* getEtagMd5_16_bytes();

extern uint8* getEtagProductModel();
extern uint8* getEtagSoftwareVersion();
extern uint8* getEtagHardwareVersion();

//~~~~~~~~~~~~~~~~上面是内存变量~~~~~~~~~~~~~~~~~~~~~~~



extern void etagResetFactory();



#define SECTOR_BASE_for_BLACK   11  //要修订数据
#define SECTOR_BASE_for_RED     41
extern int8 saveSector( uint16 sector_base, uint16 serial, uint8* chararray, uint32 length);


#endif /* ETAGBLEDRIVER_H_ */
