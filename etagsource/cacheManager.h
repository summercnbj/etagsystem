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


struct myCache_struct
{
	//TODO 请自行设计FIFO缓存结构.多线程要做线程锁。

};
typedef struct myCache_struct MyFIFOCache;

//加入缓存
extern int8 appendIntoCache(MyFIFOCache* cache, uint8* chararray, uint32 length);


//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
extern int8 peekCache(MyFIFOCache* cache );
extern int8 removeCache(MyFIFOCache* cache );

#endif /* CACHEMANAGER_H_ */
