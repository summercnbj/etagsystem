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
 * sendFirstInCache发送第一个，但是不移除。等到发送成功了对方应答了后，再removeCache。
 *
 */


void initMyFIFOCache(MyFIFOCache* cache)
{
	memset(cache,0,sizeof(MyFIFOCache));
}




//加入到缓存最后
int8 appendIntoCache(MyFIFOCache* cache, uint8* targetMacBytes, uint8* chararray, uint32 length)
{

	//TODO

	return 0;
}

//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
int8 sendFirstInCache(MyFIFOCache* cache )
{

	if( MEDIA_AIR_FROM_WIFI_TO_CLOUD == cache->media)
	{
		wifiSend2Cloud( cache->units[0].package, cache->units[0].package_length );
	}
	else if( MEDIA_UART_FROM_WIFI_TO_GWBLE == cache->media)
	{
		wifiSend2Uart( cache->units[0].package, cache->units[0].package_length );
	}
//	else if( MEDIA_BLE_FROM_GWBLE_TO_ETAGBLE == cache->media)
//	{
//		masterSendPackageToSlaveMac(  cache->units[0].package, cache->units[0].package_length, getWifiShortPW(), cache->units[0].targetMacBytes);
//	}

	return 0;
}

//移除并释放第一个
int8 removeCache(MyFIFOCache* cache )
{


	//TODO remove [0], free


	//TODO 将后面的往前移动一个脚标


	return 0;
}

//只查看下一个要发的数据
CacheUnit peekCache(MyFIFOCache* cache)
{
	return cache->units[0];
}
