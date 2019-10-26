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

#define REMEMBER_MAC 1 //用于gwBle master:gwBleMasterCache.c

#define MEDIA_AIR_FROM_WIFI_TO_CLOUD  1
#define MEDIA_UART_FROM_WIFI_TO_GWBLE  2
#define MEDIA_BLE_FROM_GWBLE_TO_ETAGBLE 3


#define CACHE_SIZE 50//使用数组或者链表都可以
struct myCache_struct
{
#if defined REMEMBER_MAC
uint8* targetMacBytes;//长度6bytes。仅仅用于gwBle master
#endif

uint8 media;//TARGET_TO_SEND_XXX


uint8* package[CACHE_SIZE];
uint32 package_length[CACHE_SIZE];

	//TODO 请自行设计FIFO缓存结构.多线程要做线程锁。



};
typedef struct myCache_struct MyFIFOCache;

//加入缓存
extern int8 appendIntoCache(MyFIFOCache* cache, uint8* chararray, uint32 length);


//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
extern int8 peekCache(MyFIFOCache* cache );
extern int8 removeCache(MyFIFOCache* cache );

#endif /* CACHEMANAGER_H_ */
