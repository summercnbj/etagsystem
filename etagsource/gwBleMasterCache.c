/*
 * gwBleMasterCache.c
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */


#include "gwBleMasterCache.h"
#include "cacheManager.h"


//激活cacheManager.h里的宏REMEMBER_MAC
MyFIFOCache cache2Slave;



int8 appendCache2Slave( uint8* etagMacBytes, uint8* chararray, uint32 length)
{
	myPrintf("[appendCache2Slave] length=%lld\n", length);

	return appendIntoCache( &cache2Slave,  chararray,  length);
}



int8 splitingToSend( uint8* etagMacBytes, uint8* package_ONBLE, uint32 package_length_ONBLE)
{
	myPrintf("[splitingToSend] package_length_ONBLE=%lld\n", package_length_ONBLE);

#if defined TESTING_SUMMER
#include "etagBleParse.h"
	slaveParseBlePackage( package_ONBLE, package_length_ONBLE);
#endif

	//TODO 分包协议 并添加到缓存里：要同时记录peripheralMacBytes,然后过滤该mac去连接发送。




//多次发送到cache
//	return appendIntoCache( &cache2Slave,  chararray,  length);

	return 0;
}


