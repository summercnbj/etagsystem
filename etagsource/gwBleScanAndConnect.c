/*
 * gwBleScan.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#include "gwBleScanAndConnect.h"



uint8 bleScan_type = BLESCAN_TYPE_HB;

void set_bleScan_type(uint8 type)
{
	bleScan_type = type;
}
uint8 get_bleScan_type( )
{
	return bleScan_type;
}

//十一，网关里的蓝牙通知价签新密码(GW_NEW_SHORTPW_ONBLE)：从网关上的蓝牙到价签蓝牙
#include "gwWifi2Uart.h"
uint8* getGW_NEW_SHORTPW_ONBLE(uint8* newShortPW)
{
	return get_GW_NEW_SHORTPW_ONUART(newShortPW);//两者相同
}


#include "gwBleDriver.h"
//三，价签心跳包(ETAG_HB)：从价签蓝牙到网关上的蓝牙  2.使用蓝牙广播
//通过广播读取心跳包
void masterParseBleAdvPackage(uint8* package,uint16 package_length, uint8* shortPW, uint8* peripheralMacBytes)
{
	if(NULL == package || package_length < TAG_HB_ADV_LENGTH)
	{
		myPrintf("masterParseBleAdvPackage package NULL or short package_length= %d\n",package_length);
		return ;
	}
	if( *(package + ADV_BYTEPOSITION_FOLLOWINGLENGTH) < ADV_HEADER_LENGTH)
	{//error
		myPrintf("masterParseBleAdvPackage error following length =%d\n",*(package + ADV_BYTEPOSITION_FOLLOWINGLENGTH));
		return;
	}
	if( VENDORMARK_0 != *(package + ADV_BYTEPOSITION_VENDORMARK)
	 || VENDORMARK_1 != *(package + ADV_BYTEPOSITION_VENDORMARK +1)
     || VENDORMARK_2 != *(package + ADV_BYTEPOSITION_VENDORMARK +2)  )
	{//error
		myPrintf("masterParseBleAdvPackage error vendormark\n");
		return;
	}
	switch(*(package + ADV_BYTEPOSITION_CMD))
	{
	case CMD_TAG_GW_HB:
	{
		uint8* offsetData = package + ADV_BYTEPOSITION_OFFSETDATA;
		if(package_length < ADV_BYTEPOSITION_OFFSETDATA + TAG_HB_LENGTH)
		{
			myPrintf("masterParseBleAdvPackage 30 > error length = %d\n",package_length );
			return;
		}

		restoreOffsetByShortPW( shortPW,  offsetData, TAG_HB_LENGTH);

		//检查offsetdata是否正确
		if( CMD_TAG_HB != *offsetData)
		{
			myPrintf("masterParseBleAdvPackage error cmd = %d\n",*offsetData );
			return;
		}

		//在最后添加peripheralMacBytes，然后通过uart传输给wificpu
		uint8* etagHb2Uart = (uint8*)myMalloc(TAG_HB_ONUART_LENGTH,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
		if(etagHb2Uart == NULL)
		{
			return;
		}
		copyCharArrayIntoBuffer( offsetData, TAG_HB_LENGTH,etagHb2Uart);
		copyCharArrayIntoBuffer( peripheralMacBytes,MAC_BYTE_LENGTH,etagHb2Uart + TAG_HB_LENGTH);

		sendUart(etagHb2Uart,TAG_HB_ONUART_LENGTH);

		myFree(etagHb2Uart);
	}
		break;
	default:
		break;
	}
}





