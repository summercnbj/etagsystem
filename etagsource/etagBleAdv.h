/*
 * etagBleAdv.h
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#ifndef ETAGBLEADV_H_
#define ETAGBLEADV_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"



//根据参数生成adv数据写入buffer,buffer_length必须>=TAG_HB_ADV_LENGTH
extern void genAdvIntoBuffer(uint8* shortPW,uint8* productModel, uint8*softwareVersion,uint8* hardwareVersion,
		uint8 battPercentage, uint8* md5_16_bytes, uint8* buffer, uint16 buffer_length);

#endif /* ETAGBLEADV_H_ */
