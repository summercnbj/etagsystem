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


#define ETAG_FLASH_SECTOR_SIZE 4096
#define NVRAMID_LENGTH 2
#define NVRAMID_SIZE_LENGTH 2
#if SSP_IN_NVRAM
#define NVRAMID_HEADER_SIZE (NVRAMID_LENGTH+NVRAMID_SIZE_LENGTH)
#endif
#define FLASH_SECTOR_REAR_HIDDEN_SIZE 4 //for sector data restore
#define FLASH_SECTOR_VALID_SIZE (ETAG_FLASH_SECTOR_SIZE-FLASH_SECTOR_REAR_HIDDEN_SIZE)

extern void etagResetFactory();



#endif /* ETAGBLEDRIVER_H_ */
