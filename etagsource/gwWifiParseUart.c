/*
 * gwWifiParseUart.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#include "gwWifiParseUart.h"
#include "gwWifiCaches.h"
#include "gwWifiDriver.h"
#include "gwWifiEtagHb.h"






void wifiParseUart(uint8* package, uint32 package_length )
{
	if(package == NULL || package_length < CMD_LENGTH)
		return;
	switch(*package)
	{
	case CMD_TAG_HB:
	{
		if( package_length < TAG_HB_ONUART_LENGTH)
		{
			myPrintf("gwWifiParseUart package_length= %d\n" , package_length);
		}


		uint16 hbPackage_length =0;
		uint8* hbPackage = getGwWifiEtagHbPackage( getWifiShortPW(),  getFlowNo(),  getWifiMacBytes(), getGwBattPercentage(),  getRootMacBytes(), package +CMD_LENGTH,
				&hbPackage_length);
		myPrintf("wifiParseUart hbPackage_length= %d\n" , hbPackage_length);
		myPrintf("wifiParseUart flowNo= %d\n" , getFlowNo());


		appendCache2Cloud(hbPackage, hbPackage_length);


		//发送完要myFree
		myFree(hbPackage);
	}
		break;

	default:
		break;

	}
}

