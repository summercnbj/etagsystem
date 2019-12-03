/*
 * gwBleScan.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#include "gwBleScanAndConnect.h"
#include "gwBleMasterCache.h"

/*
 *
 * BLESCAN_TYPE_SENDNEWSHORTPW=1  停止解析广告中的心跳包行为，扫描到任意mac的etag就连接发送密码
 * BLESCAN_TYPE_HB=2 扫描到任意mac的etag都解析广告中的心跳包；发现缓存里指定mac的etag就发送缓存里的数据。
 *
 */

uint8 bleScan_type = BLESCAN_TYPE_HB;

void set_bleScan_type(uint8 type)
{
	bleScan_type = type;
}
uint8 get_bleScan_type( )
{
	return bleScan_type;
}

#define SENDING_BUFFER_LENGTH 22
static uint8 sendingBuffer[SENDING_BUFFER_LENGTH];//固定长度的buffer

/* API
 * 连接当前的蓝牙slaveMacBytes
 */
int8 connectSlave(uint8 *slaveMacBytes)
{
	//TODO


	return 0;
}

int8 disconnectSlave()
{
	//TODO  断开当前连接


	return 0;
}

/* API
 * 被  UUID_NEWSHORTPW 发现回调
 */
int8 sendingShortPW()
{
	//TODO 向指定UUID_NEWSHORTPW发送sendingBuffer[SENDING_BUFFER_LENGTH]




	int8 ret = 0;


	disconnectSlave();
	return ret;
}


/* API
 * 被  UUID_cachedata 发现回调
 * 发送来自gwBleMasterCache-->bleSplittingEncDec的数据
 */
int8 sendingSplitting()
{
	//TODO 向指定UUID_cachedata发送sendingBuffer[SENDING_BUFFER_LENGTH]





	int8 ret = 0;


	if( 0 == ret)
	{
		{
			//看有没有下一条数据。若有，继续发masterSendPackageToSlave(next)； 若没有断开连接。



		}
	}

	return ret;
}

//发送单条数据，长度不超过20字节.写入 sendingBuffer[SENDING_BUFFER_LENGTH]
void masterSendPackageToSlave(uint8* package_ONBLE,uint32 package_length_ONBLE)
{
	//TODO 向指定UUID写入数据
	if( package_length_ONBLE < SENDING_BUFFER_LENGTH)
	{
		copyCharArrayIntoBuffer(package_ONBLE,package_length_ONBLE,sendingBuffer);
	}
}









//十一，网关里的蓝牙通知价签新密码(GW_NEW_SHORTPW_ONBLE)：从网关上的蓝牙到价签蓝牙


#include "gwBleDriver.h"



<<<<<<< HEAD
=======

>>>>>>> cd3803a... aaaaaa


//三，价签心跳包(ETAG_HB)：从价签蓝牙到网关上的蓝牙  2.使用蓝牙广播
//通过广播读取心跳包
void masterParseBleAdvPackage(uint8* package,uint16 package_length, uint8* shortPW, uint8* slaveMacBytes)
{
	if(NULL == package || package_length < TAG_HB_ADV_LENGTH)
	{
		myPrintf("masterParseBleAdvPackage package NULL or short package_length= %d\n",package_length);
		return ;
	}
	if( *(package + ADV_BYTEPOSITION_FOLLOWINGLENGTH) < ADV_HEADER_LENGTH)
	{//error
		myPrintf("masterParseBleAdvPackage error following length =%d\n",*(package + ADV_BYTEPOSITION_FOLLOWINGLENGTH));
		return;
	}
	if( VENDORMARK_0 != *(package + ADV_BYTEPOSITION_VENDORMARK)
	 || VENDORMARK_1 != *(package + ADV_BYTEPOSITION_VENDORMARK +1)
     || VENDORMARK_2 != *(package + ADV_BYTEPOSITION_VENDORMARK +2)  )
	{//error
		myPrintf("masterParseBleAdvPackage error vendormark\n");
		return;
	}

	//确认了是etag

	if(BLESCAN_TYPE_SENDNEWSHORTPW == bleScan_type)
	{
		//连接该etag，并发送新密码
		//等待连接成功回调，再discoverService,在得到uuid回调中开始发送数据。
		connectSlave(slaveMacBytes);


		return;//停止解析广告中的心跳包行为
	}
	else if(BLESCAN_TYPE_HB == bleScan_type)
	{
		//扫描到任意mac的etag都解析广告中的心跳包；发现缓存里指定mac的etag就发送缓存里的数据。

		int8 send = sendCache2Slave( slaveMacBytes );
		if(send<0)
		{
			uint8 machexstr[13];
			memset(machexstr,0,13);
			MacSixIntoMac12HexChar( slaveMacBytes ,6, machexstr, 13 );
			myPrintf("%s no data to send\n", machexstr );
		}
	}


	switch(*(package + ADV_BYTEPOSITION_CMD))
	{
	case CMD_TAG_GW_HB:
	{
		uint8* offsetData = package + ADV_BYTEPOSITION_OFFSETDATA;
		if(package_length < ADV_BYTEPOSITION_OFFSETDATA + TAG_HB_LENGTH)
		{
			myPrintf("masterParseBleAdvPackage 30 > error length = %d\n",package_length );
			return;
		}

		restoreOffsetByShortPW( shortPW,  offsetData, TAG_HB_LENGTH);

		//检查offsetdata是否正确
		if( CMD_TAG_HB != *offsetData)
		{
			myPrintf("masterParseBleAdvPackage error cmd = %d\n",*offsetData );
			return;
		}

		//在最后添加peripheralMacBytes，然后通过uart传输给wificpu
<<<<<<< HEAD
		uint8* etagHb2Uart = (uint8*)myMalloc(TAG_HB_ONUART_LENGTH,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
=======
		uint8_itr* etagHb2Uart = (uint8_itr*)myMalloc(TAG_HB_ONUART_LENGTH,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
>>>>>>> cd3803a... aaaaaa
		if(etagHb2Uart == NULL)
		{
			return;
		}
		copyCharArrayIntoBuffer( offsetData, TAG_HB_LENGTH,etagHb2Uart);
		copyCharArrayIntoBuffer( slaveMacBytes,MAC_BYTE_LENGTH,etagHb2Uart + TAG_HB_LENGTH);

		bleSend2Uart(etagHb2Uart,TAG_HB_ONUART_LENGTH);

		myFree(etagHb2Uart);
	}
		break;
	default:
		break;
	}
}


uint8* get_ETAG_GW_HB_FEEDBACK_STATE_ONBLE_from_ONUART(uint8* package_ONUART,uint32 package_length_ONUART)
{
	uint8* package2etag = (uint8*)myMalloc(package_length_ONUART - MAC_BYTE_LENGTH,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
	* package2etag = *package_ONUART;
	* (package2etag+CMD_LENGTH) = *(package_ONUART + CMD_LENGTH + MAC_BYTE_LENGTH);
	* (package2etag+CMD_LENGTH+SUBCMD_LENGTH) = *(package_ONUART + CMD_LENGTH + MAC_BYTE_LENGTH+SUBCMD_LENGTH);
	copyCharArrayIntoBuffer( package_ONUART + TAG_ETAG_GW_HB_FEEDBACK_STATE_ONUART_HEADER_LENGTH,
			package_length_ONUART -TAG_ETAG_GW_HB_FEEDBACK_STATE_ONUART_HEADER_LENGTH, package2etag +TAG_ETAG_GW_HB_FEEDBACK_STATE_ONBLE_HEADER_LENGTH);

	return package2etag;
}









