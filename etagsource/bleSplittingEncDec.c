/*
 * bleSplitting.c
 *
 *  Created on: 2019年10月27日
 *      Author: summer
 */


#include "bleSplittingEncDec.h"

#include "gwBleScanAndConnect.h"


/** TODO
 * 需要拆开后添加包头信息，确保能够组装起来。所以叫bleSplittingEncDec
 */



int8 splitingToSend( uint8* etagMacBytes, uint8* package_ONBLE, uint32 package_length_ONBLE)
{
	myPrintf("[splitingToSend] package_length_ONBLE=%lld\n", package_length_ONBLE);

#if defined TESTING_SUMMER
#include "etagBleParse.h"
	slaveParseBlePackage( package_ONBLE, package_length_ONBLE);
#endif

	//TODO 分包协议 并添加到缓存里：要同时记录peripheralMacBytes,然后过滤该mac去连接发送。





	//先连接etagMacBytes

	uint8* chararray1 = NULL;
	uint8 length1 =0;

	masterSendPackageToSlave( chararray1,  length1);

	return 0;
}
