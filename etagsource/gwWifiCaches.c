/*
 * gwWifiCache2Uart.c
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */

#include "gwWifiCaches.h"
#include "gwWifiDriver.h"


#if defined TESTING_SUMMER
#include "gwBleParseUart.h"
#include "serverParseHb.h"
#endif

MyFIFOCache cache2Uart_A;
MyFIFOCache cache2Uart_B;
MyFIFOCache cache2Uart_C;


MyFIFOCache cache2Cloud;//用来做流控



void initCaches()
{

	initMyFIFOCache( &cache2Uart_A );
	initMyFIFOCache( &cache2Uart_B );
	initMyFIFOCache( &cache2Uart_C );
	initMyFIFOCache( &cache2Cloud );

	cache2Cloud.media = MEDIA_AIR_FROM_WIFI_TO_CLOUD;

	cache2Uart_A.media = MEDIA_UART_FROM_WIFI_TO_GWBLE;
	cache2Uart_B.media = MEDIA_UART_FROM_WIFI_TO_GWBLE;
	cache2Uart_C.media = MEDIA_UART_FROM_WIFI_TO_GWBLE;
}




int8 appendCache2Uart_A( uint8* chararray, uint32 length)
{
	return appendIntoCache( &cache2Uart_A, NULL, chararray,  length);
}
int8 appendCache2Uart_B( uint8* chararray, uint32 length)
{
	return appendIntoCache( &cache2Uart_B, NULL, chararray,  length);
}
int8 appendCache2Uart_C( uint8* chararray, uint32 length)
{
	return appendIntoCache( &cache2Uart_C, NULL, chararray,  length);
}

int8 appendCache2AllUarts( uint8* chararray, uint32 length)
{
	myPrintf("[appendCache2AllUarts] length=%lld\n", length);
#if defined TESTING_SUMMER
	bleParseUartPackage(chararray,length);//gwBle代码
#endif


	appendCache2Uart_A(chararray,length);
	appendCache2Uart_B(chararray,length);
	appendCache2Uart_C(chararray,length);

	return 0;
}


/**  chararray里的数据是自明的，里面包含了价签mac。
 * 根据价签UUID和ABC缓存大小来决定分发到哪路UART: appendCache2Uart_A,appendCache2Uart_B,appendCache2Uart_C
 */
int8 appendCache2Uart( uint8* etagMacBytes, uint8* chararray, uint32 length)
{
	myPrintf("[appendCache2Uart] length=%lld\n", length);

#if defined TESTING_SUMMER
	//only for test
	bleParseUartPackage(chararray,length);
#endif

	//TODO  选择哪个发送？








	return 0;
}


int8 appendCache2Cloud( uint8* chararray, uint32 length)
{
	myPrintf("[appendCache2Cloud] length=%lld\n", length);

#if defined TESTING_SUMMER
	parseHb2Db( getWifiShortPW(), chararray, length);
#endif

	return appendIntoCache( &cache2Cloud, NULL, chararray,  length);//server代码
}






//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
int8 sendFirstInCache2Uart_A()
{
	return sendFirstInCache( &cache2Uart_A);
}

int8 removeCache2Uart_A( )
{
	return removeCache( &cache2Uart_A);
}

//只查看下一个要发的数据
CacheUnit peekCache2Uart_A()
{
	return peekCache(&cache2Uart_A);
}

//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
int8 sendFirstInCache2Uart_B()
{
	return sendFirstInCache( &cache2Uart_B);
}

int8 removeCache2Uart_B( )
{
	return removeCache( &cache2Uart_B);
}

//只查看下一个要发的数据
CacheUnit peekCache2Uart_B()
{
	return peekCache(&cache2Uart_B);
}

//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
int8 sendFirstInCache2Uart_C()
{
	return sendFirstInCache( &cache2Uart_C);
}

int8 removeCache2Uart_C( )
{
	return removeCache( &cache2Uart_C);
}

//只查看下一个要发的数据
CacheUnit peekCache2Uart_C()
{
	return peekCache(&cache2Uart_C);
}

//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
int8 sendFirstInCache2Cloud()
{
	return sendFirstInCache( &cache2Cloud);
}

int8 removeCache2Cloud( )
{
	return removeCache( &cache2Cloud);
}

//只查看下一个要发的数据
CacheUnit peekCache2Cloud()
{
	return peekCache(&cache2Cloud);
}

