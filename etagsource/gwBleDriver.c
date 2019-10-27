/*
 * bleDriver.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#include "gwBleDriver.h"
#if TESTING_SUMMER  //testing
#include "gwWifiParseUart.h"
#endif

//~~~~~~~~~~~~~~~~内存变量~~~~~~~~~~~~~~~~~~~~~~~
static uint8 gwBleShortPW[SHORTPW_LENGTH];
static uint8 newGwBleShortPW[SHORTPW_LENGTH];

uint8* getGwBleShortPW()
{
	return gwBleShortPW;
}
uint8* getNewGwBleShortPW()
{
	return newGwBleShortPW;
}



//~~~~~~~~~~~~~~~~上面是内存变量~~~~~~~~~~~~~~~~~~~~~~~





void bleSend2Uart(uint8* data,uint16 data_length)
{
	myPrintf("sendUart data_length= %d\n",data_length);
	//测试wifi里处理etagHb

#if TESTING_SUMMER
	wifiParseUart( data,  data_length );//gwWifi代码
#endif


	//TODO 调用封装了校验、应答和失败重发的uart协议



}



#include "gwBleParseUart.h"
//TODO 被驱动调用：从uart协议里解出的data
void bleParseUart(uint8* data,uint16 data_length)
{
	bleParseUartPackage( data, data_length);
}
