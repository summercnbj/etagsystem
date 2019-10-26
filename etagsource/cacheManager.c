/*
 * myCache.c
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */


#include "cacheManager.h"


#include "gwBleScanAndConnect.h"
#include "gwWifiDriver.h"


/*
 * MyFIFOCache模型,需要考虑线程并发。该部分仅供参考。
 *
 * peekCache发送第一个，但是不移除。等到发送成功了对方应答了后，再removeCache。
 *
 */


//加入缓存
int8 appendIntoCache(MyFIFOCache* cache, uint8* chararray, uint32 length)
{
	//TODO

	return 0;
}

//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
int8 peekCache(MyFIFOCache* cache )
{

	if( MEDIA_AIR_FROM_WIFI_TO_CLOUD == cache->media)
	{
		wifiSend2Cloud( cache->package[0], cache->package_length[0] );
	}
	else if( MEDIA_UART_FROM_WIFI_TO_GWBLE == cache->media)
	{
		wifiSend2Uart( cache->package[0], cache->package_length[0] );
	}
	else if( MEDIA_BLE_FROM_GWBLE_TO_ETAGBLE == cache->media)
	{
		masterSendPackage( cache->package[0], cache->package_length[0], getShortPW(), cache->targetMacBytes);
	}

	//TODO 将后面的往前移动一个脚标


	return 0;
}

//移除并释放第一个
int8 removeCache(MyFIFOCache* cache )
{


	//TODO




	return 0;
}
