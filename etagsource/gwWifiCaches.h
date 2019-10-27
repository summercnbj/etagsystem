/*
 * gwWifiCache2Uart.h
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */

#ifndef GWWIFICACHES_H_
#define GWWIFICACHES_H_
#include "cacheManager.h"
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"
#include "gwWifiDriver.h"

extern void initCaches();

extern int8 appendCache2AllUarts( uint8* chararray, uint32 length);


/**  chararray里的数据是自明的，里面包含了价签mac。
 * 根据价签UUID和ABC缓存大小来决定分发到哪路UART: appendCache2Uart_A,appendCache2Uart_B,appendCache2Uart_C
 */
extern int8 appendCache2Uart( uint8* etagMacBytes, uint8* chararray, uint32 length);

extern int8 appendCache2Cloud( uint8* chararray, uint32 length);


//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
extern int8 sendFirstInCache2Uart_A();

extern int8 removeCache2Uart_A( );

//只查看下一个要发的数据
extern CacheUnit peekCache2Uart_A();

//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
extern int8 sendFirstInCache2Uart_B();

extern int8 removeCache2Uart_B( );

//只查看下一个要发的数据
extern CacheUnit peekCache2Uart_B();

//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
extern int8 sendFirstInCache2Uart_C();

extern int8 removeCache2Uart_C( );

//只查看下一个要发的数据
extern CacheUnit peekCache2Uart_C();

//发送第一个，但是不移除。待到收到对方应答再移除(removeCache)
extern int8 sendFirstInCache2Cloud();

extern int8 removeCache2Cloud( );

//只查看下一个要发的数据
extern CacheUnit peekCache2Cloud();



#endif /* GWWIFICACHES_H_ */
