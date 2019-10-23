/*
 * bleDriver.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#include "gwBleDriver.h"

void sendUart(uint8* data,uint16 data_length)
{
	//TODO 调用封装了校验、应答和失败重发的uart协议

	myPrintf("sendUart data_length= %d\n",data_length);

	//测试wifi里处理etagHb

#if TESTING_SUMMER  //testing
	extern void wifiParseUart(uint8* package, uint16 package_length );
	wifiParseUart( data,  data_length );
#endif

}

#include "gwBleParseUart.h"
//TODO 被驱动调用：从uart协议里解出的data
void bleParseUart(uint8* data,uint16 data_length)
{
	bleParseUartPackage( data, data_length);
}
