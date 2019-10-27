/*
 * gwBleMasterCache.h
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */

#ifndef GWBLEMASTERCACHE_H_
#define GWBLEMASTERCACHE_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "nvramApi.h"

#include "commands.h"



struct MacCacheUnit_struct
{
	uint8* targetMacBytes;//长度6bytes。仅仅用于gwBle master

	uint8* package;
	uint32 package_length;

};
typedef struct MacCacheUnit_struct MacCacheUnit;

#define BLEMASTER_CACHE_SIZE 50//使用数组或者链表都可以
struct MacCache_struct
{
	MacCacheUnit units[BLEMASTER_CACHE_SIZE];

	int16 sendingFoot ;//当前在发送中的脚标
};
typedef struct MacCache_struct MyMacCache;


extern void initCache2Slave();

//发送指定mac的数据。待到收到对方应答再移除(removeCache2Slave)
extern int8 sendCache2Slave( uint8* slaveMacBytes );

extern int8 removeCache2Slave();

//etagMacBytes用于过滤连接slave
extern int8 appendCache2Slave( uint8* etagMacBytes, uint8* chararray, uint32 length);






#endif /* GWBLEMASTERCACHE_H_ */
