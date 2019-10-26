/*
 * gwWifiDriver.h
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#ifndef GWWIFIDRIVER_H_
#define GWWIFIDRIVER_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"


#define GW_BLE_QTY 3



extern void addFlowNo();
extern uint16 getFlowNo();
//判断接受到的receiveFlowNo是否比当前的flowNo小。若小则无效timeout.
extern itr_bool flowNoValid(uint16 receiveFlowNo);
extern void setGwBattPercentage(uint8 batt);
extern uint8 getGwBattPercentage();
extern uint8* getShortPW();
extern uint8* getWifiMacBytes();
extern uint8* getRootMacBytes();
extern uint8* getGwProductModel();
extern uint8* getGwSoftwareVersion();
extern uint8* getGwHardwareVersion();

extern void wifiResetFactory();


//macBytes with length of MAC_BYTE_LENGTH=6
extern uint8* formUuidBytes(uint8* macBytes);



extern void wifiSend2Uart(uint8* data, uint32 length);


//http flow up flow down
extern void wifiSend2Cloud(uint8* data, uint32 length);

#endif /* GWWIFIDRIVER_H_ */
