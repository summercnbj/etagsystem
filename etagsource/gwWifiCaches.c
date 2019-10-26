/*
 * gwWifiCache2Uart.c
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */

#include "gwWifiCaches.h"
#include "gwWifiDriver.h"

MyFIFOCache cache2Uart_A;
MyFIFOCache cache2Uart_B;
MyFIFOCache cache2Uart_C;


MyFIFOCache cache2Cloud;//用来做流控



void initCaches()
{
	cache2Cloud.media = MEDIA_AIR_FROM_WIFI_TO_CLOUD;

	cache2Uart_A.media = MEDIA_UART_FROM_WIFI_TO_GWBLE;
	cache2Uart_B.media = MEDIA_UART_FROM_WIFI_TO_GWBLE;
	cache2Uart_C.media = MEDIA_UART_FROM_WIFI_TO_GWBLE;
}




int8 appendCache2Uart_A( uint8* chararray, uint32 length)
{
	return appendIntoCache( &cache2Uart_A,  chararray,  length);
}
int8 appendCache2Uart_B( uint8* chararray, uint32 length)
{
	return appendIntoCache( &cache2Uart_B,  chararray,  length);
}
int8 appendCache2Uart_C( uint8* chararray, uint32 length)
{
	return appendIntoCache( &cache2Uart_C,  chararray,  length);
}

int8 appendCache2AllUarts( uint8* chararray, uint32 length)
{
	myPrintf("[appendCache2AllUarts] length=%lld\n", length);

	appendCache2Uart_A(chararray,length);
	appendCache2Uart_B(chararray,length);
	appendCache2Uart_C(chararray,length);

#if defined TESTING_SUMMER
	//only for test
	wifiSend2Uart( chararray,  length);
#endif
	return 0;
}


/**  chararray里的数据是自明的，里面包含了价签mac。
 * 根据价签UUID和ABC缓存大小来决定分发到哪路UART: appendCache2Uart_A,appendCache2Uart_B,appendCache2Uart_C
 */
int8 appendCache2Uart( uint8* etagMacBytes, uint8* chararray, uint32 length)
{
	//TODO

	myPrintf("[appendCache2Uart] length=%lld\n", length);


#if defined TESTING_SUMMER
	//only for test
	wifiSend2Uart( chararray,  length);
#endif




	return 0;
}


int8 appendCache2Cloud( uint8* chararray, uint32 length)
{
	myPrintf("[appendCache2Cloud] length=%lld\n", length);

	return appendIntoCache( &cache2Cloud,  chararray,  length);
}
