/*
 * gwBleScan.h
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#ifndef GWBLESCANANDCONNECT_H_
#define GWBLESCANANDCONNECT_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"




extern void set_bleScan_type(uint8 type);
extern uint8 get_bleScan_type( );


//三，价签心跳包(ETAG_HB)：从价签蓝牙到网关上的蓝牙  2.使用蓝牙广播
//通过广播读取心跳包
extern void masterParseBleAdvPackage(uint8* package,uint16 package_length, uint8* shortPW, uint8* peripheralMacBytes);


extern uint8* get_ETAG_GW_HB_FEEDBACK_STATE_ONBLE_from_ONUART(uint8* package_ONUART,uint32 package_length_ONUART);

//发送单条数据，长度不超过20字节
extern void masterSendPackage(uint8* package_ONBLE,uint32 package_length_ONBLE, uint8* shortPW, uint8* peripheralMacBytes);

#endif /* GWBLESCANANDCONNECT_H_ */
