/*
 * nvramApi.h
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#ifndef NVRAMAPI_H_
#define NVRAMAPI_H_

#include "itracker88Platform.h"
//#include "itrackerCharArray.h"
//#include "cTools.h"
//#include "commands.h"



#define NVRAMID_SHORTPW 1
#define NVRAMID_UUID 2
#define NVRAMID_GW_INTERVAL_at_HALFMINUTE 3
#define NVRAMID_CLOUDINFO_PROTOCOL 4
#define NVRAMID_CLOUDINFO_HOST 5
#define NVRAMID_CLOUDINFO_PORT 6
#define NVRAMID_CLOUDINFO_HB 7
#define NVRAMID_ROUTER_SSID 8
#define NVRAMID_ROUTER_ENCRYPT 9
#define NVRAMID_ROUTER_PW 10
#define NVRAMID_ROUTER_MAC 11
#define NVRAMID_UPDATING_SHORTPW_TO_BLE 12

//~~~~~~~~~~~~~~~~ble master in gw~~~~~~~~~~~~~~~~~~~~
#define NVRAMID_SHORTPW 1
#define NVRAMID_NEW_SHORTPW 2
#define NVRAMID_PERIOD_for_FIND_NO_ETAG_min 3

//~~~~~~~~~~~~~~~~ble peripheral in etag~~~~~~~~~~~~~~~~~~~~
#define NVRAMID_SHORTPW 1
#define NVRAMID_SAP0_FACTORY 2
#define NVRAMID_TAG_INTERVAL_at_HALFMINUTE 3
#define NVRAMID_TAG_RETURN_RATIO 4
#define NVRAMID_MD5_16_for_ PIXELDATA 5
#define NVRAMID_SAP0 6
#define NVRAMID_SAP1 7

//读ID。长度存入data_length
extern uint8* readNvramId(uint16 id, uint16* data_length);

//删除ID
extern itr_bool deleteNvramId(uint16 id);

//添加或修改ID
extern itr_bool saveNvramId(uint16 id, uint8* data, uint16 data_length);


#endif /* NVRAMAPI_H_ */
