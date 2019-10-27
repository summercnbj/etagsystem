/*
 * gwBleMasterCache.c
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */


#include "gwBleMasterCache.h"

#include "bleSplittingEncDec.h"
#include "gwBleScanAndConnect.h"
#include "gwBleDriver.h"

#if TESTING_SUMMER //testing
#include "serverParseHb.h"
#endif

MyMacCache cache2Slave;

void initCache2Slave()
{
	memset(&cache2Slave,0,sizeof(MyMacCache));
	cache2Slave.sendingFoot =-1;
}

void freeMacCacheUnit(MacCacheUnit* unit)
{
	myFree(unit->targetMacBytes);
	myFree(unit->package);
}


int16 findEtagMacBytes( uint8* etagMacBytes)
{
	//TODO  在cache2Slave中找etagMacBytes所在的脚标



//	失败返回-1
	return -1;
}

//发送指定mac的数据。待到收到对方应答再移除(removeCache2Slave)
int8 sendCache2Slave( uint8* slaveMacBytes )
{
	//TODO  查找etagMacBytes

	int16 foot = findEtagMacBytes( slaveMacBytes);
	if(foot <0 )
	{
		return -1;
	}
	cache2Slave.sendingFoot = foot;
	splitingToSend(slaveMacBytes,  cache2Slave.units[foot].package, cache2Slave.units[foot].package_length);
	return 0;
}

int8 removeCache2Slave( )
{
	freeMacCacheUnit(&(cache2Slave.units[cache2Slave.sendingFoot]));
	cache2Slave.sendingFoot = -1;
	//最后删除该条
	memset( &(cache2Slave.units[cache2Slave.sendingFoot]), 0, sizeof(MacCacheUnit));
	return 0;
}

int16 findZero()
{
	//TODO  在cache2Slave中为空的位置， 遍历发现是0的条。返回脚标


//	失败返回-1
	return -1;
}


int8 appendCache2Slave( uint8* etagMacBytes, uint8* chararray, uint32 length)
{

	int16 foot = findZero();
	if(foot <-1)
	{
		return -1;
	}

	//如果上文已经释放，则这里要复制malloc
	cache2Slave.units[foot].targetMacBytes = etagMacBytes;
	cache2Slave.units[foot].package = chararray;
	cache2Slave.units[foot].package_length = length;
	return 0;
}









