/*
 * etagServer.h
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef SERVERPARSEHB_H_
#define SERVERPARSEHB_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"

struct gwHbPackage_struct
{
	uint8 type;
	uint16 flowNo;
//	uint8 macBytes[MAC_BYTE_LENGTH];
	uint8 uuidBytes[UUID_BYTE_LENGTH];
	uint8 battPercentage;
	uint8 routerMacBytes[MAC_BYTE_LENGTH];
	uint8 isBusy;
	uint8* productModel;
	uint8* softwareVersion;
	uint8* hardwareVersion;
};


#define HB_TYPE_from_GW 1
#define HB_TYPE_from_ETAG 2

extern void printGwHbPackage_struct(struct gwHbPackage_struct * package);

extern uint8* parseHb(uint8* shortPW, uint8* gwHbPackage, uint16 gwHbPackage_length);

#endif /* SERVERPARSEHB_H_ */
