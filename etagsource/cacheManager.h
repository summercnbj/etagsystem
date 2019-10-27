/*
 * myCache.h
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */

#ifndef CACHEMANAGER_H_
#define CACHEMANAGER_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "nvramApi.h"


#define MEDIA_AIR_FROM_WIFI_TO_CLOUD  1
#define MEDIA_UART_FROM_WIFI_TO_GWBLE  2

struct CacheUnit_struct
{
	uint8* package;
	uint32 package_length;

};
typedef struct CacheUnit_struct CacheUnit;


#define CACHE_SIZE 50//使用数组或者链表都可以
struct myFIFOCache_struct
{
	uint8 media;//TARGET_TO_SEND_XXX

	CacheUnit units[CACHE_SIZE];

};
typedef struct myFIFOCache_struct MyFIFOCache;



extern void initMyFIFOCache(MyFIFOCache* cache);


//加入缓存最后
extern int8 appendIntoCache(MyFIFOCache* cache, uint8* targetMacBytes, uint8* chararray, uint32 length);


//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
extern int8 sendFirstInCache(MyFIFOCache* cache );
extern int8 removeCache(MyFIFOCache* cache );//移除并释放第一个
extern CacheUnit peekCache(MyFIFOCache* cache);//只查看下一个要发的数据

#endif /* CACHEMANAGER_H_ */
