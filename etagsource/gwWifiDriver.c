/*
 * gwWifiDriver.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#include "gwWifiDriver.h"


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
