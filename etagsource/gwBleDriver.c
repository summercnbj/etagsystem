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
}

#include "gwBleParseUart.h"
//TODO 被驱动调用：从uart协议里解出的data
void parseUart(uint8* data,uint16 data_length)
{
	parseUartPackage( data, data_length);
}
