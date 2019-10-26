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


extern void etagResetFactory();



#define SECTOR_BASE_for_BLACK   11  //要修订数据
#define SECTOR_BASE_for_RED     41
extern int8 saveSector( uint16 sector_base, uint16 serial, uint8* chararray, uint32 length);


#endif /* ETAGBLEDRIVER_H_ */
