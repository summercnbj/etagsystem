/*
 * gwWifiDriver.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#include "gwWifiDriver.h"


static uint16 flowNo =1;

void addFlowNo()
{
	flowNo++;
}
uint16 getFlowNo()
{
	return flowNo;
}
//判断接受到的receiveFlowNo是否比当前的flowNo小。若小则无效timeout.
itr_bool flowNoValid(uint16 receiveFlowNo)
{
	if(receiveFlowNo < flowNo && flowNo - receiveFlowNo < 10000 )
	{
		return itr_false;
	}
	return itr_true;
}

static uint8 gwBattPercentage =100;
static uint8 shortPW[SHORTPW_LENGTH];
static uint8 wifiMacBytes[MAC_BYTE_LENGTH];
static uint8 rootMacBytes[MAC_BYTE_LENGTH];
void setGwBattPercentage(uint8 batt)
{
	gwBattPercentage = batt;
}
uint8 getGwBattPercentage()
{
	return gwBattPercentage;
}
uint8* getShortPW()
{
	return shortPW;
}
uint8* getWifiMacBytes()
{
	return wifiMacBytes;
}
uint8* getRootMacBytes()
{
	return rootMacBytes;
}

static uint8 gwProductModel[PRODUCTMODEL_LENGTH_MAX+1];//8字节 ET-1101
static uint8 gwSoftwareVersion[SOFTWAREVERSION_LENGTH_MAX+1];//xxx.xx
static uint8 gwHardwareVersion[HARDWAREVERSION_LENGTH_MAX+1];//xxx.xx
uint8* getGwProductModel()
{
	return gwProductModel;
}
uint8* getGwSoftwareVersion()
{
	return gwSoftwareVersion;
}
uint8* getGwHardwareVersion()
{
	return gwHardwareVersion;
}



void rebooting()
{
	//TODO 重启


}

void resetFactory()
{
	deleteNvramId(NVRAMID_CLOUDINFO_PROTOCOL);
	deleteNvramId(NVRAMID_CLOUDINFO_HOST);
	deleteNvramId(NVRAMID_CLOUDINFO_PORT);
	deleteNvramId(NVRAMID_CLOUDINFO_HB);
	deleteNvramId(NVRAMID_ROUTER_SSID);
	deleteNvramId(NVRAMID_ROUTER_ENCRYPT);
	deleteNvramId(NVRAMID_ROUTER_PW);
	deleteNvramId(NVRAMID_ROUTER_MAC);
	deleteNvramId(NVRAMID_UPDATING_SHORTPW_TO_BLE);

	//reset重启
	rebooting();
}


//macBytes with length of MAC_BYTE_LENGTH=6
uint8* formUuidBytes(uint8* macBytes)
{
	if(macBytes == NULL)
		return NULL;
	uint8* uuid = (uint8*)myMalloc(UUID_BYTE_LENGTH,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
	if(uuid == NULL)
		return NULL;
	copyCharArrayIntoBuffer(macBytes,MAC_BYTE_LENGTH,uuid);
	return uuid;
}
