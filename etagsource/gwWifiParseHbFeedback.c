/*
 * gwWifiParseGwHbFeedback.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */
<<<<<<< HEAD
#include "gwWifiParseHbFeedback.h"
#include "unpackPixeldata.h"
#include "gwWifiCaches.h"
#include "itrackerBlowFish.h"

=======
#include "include/Cetagsource/gwWifiParseHbFeedback.h"
#include "include/Cetagsource/unpackPixeldata.h"
#include "include/Cetagsource/gwWifiCaches.h"
<<<<<<< HEAD
//#include "include/Ctools/itrackerBlowFish.h"
#include "include/Ctools/itrackerEncryptCs.h"
=======
#include "include/Ctools/itrackerBlowFish.h"

>>>>>>> c1497af... a
>>>>>>> cd3803a... aaaaaa

//~~~~~~~~~~~~~~~~~~~~见十~~~~~~~~~~~~~~~~~~~

uint8 newShortPWResponse =0;

//TODO 必须等收到了所有的应答后才能删除NVRAM ID UPDATING_SHORTPW_TO_BLE
//被uart RX解析应答uart id时候调用：
void receiveNewShortPWResponse()
{
	newShortPWResponse++;

	if( newShortPWResponse >= GW_BLE_QTY )
	{
		itr_bool delete = deleteNvramId(NVRAMID_UPDATING_SHORTPW_TO_BLE);
	}
}

#include "gwWifi2Uart.h"
void to_send_NEW_SHORTPW_ONUART(uint8* newShortPW)
{
	printCharArray("todoNewShortPW:", newShortPW, SHORTPW_LENGTH);
	newShortPWResponse =0;//reset
	//TODO  向网关里的所有蓝牙发送GW_NEW_SHORTPW_ONUART并确保都收到了: 发向缓存sendingCache2Uart

	uint8* pack = get_GW_NEW_SHORTPW_ONUART(newShortPW);

	int8 append = appendCache2AllUarts( pack, GW_NEW_SHORTPW_ONUART_LENGTH);

	myFree(pack);

	//必须等收到了所有的应答后才能删除NVRAM ID UPDATING_SHORTPW_TO_BLE
}


//开机即检查：如果NVRAM添加ID UPDATING_SHORTPW_TO_BLE值为0x01
void onBoot_check_UPDATING_SHORTPW_TO_BLE(uint8* shortPW)
{
	//如果NVRAM ID UPDATING_SHORTPW_TO_BLE存在，值为0x01，send_NEW_SHORTPW_ONUART(shortPW);
	uint16 length =0;
	uint8* UPDATING_SHORTPW_TO_BLE = readNvramId( NVRAMID_UPDATING_SHORTPW_TO_BLE,&length);

	if(UPDATING_SHORTPW_TO_BLE != NULL)
	{
		to_send_NEW_SHORTPW_ONUART(shortPW);
	}

}


//SHORTPW_LENGTH
void todoNewShortPW(uint8* newShortPW)
{

	//更改 NVRAM ID SHORTPW的值为newShortPW,长度SHORTPW_LENGTH
	saveNvramId(NVRAMID_SHORTPW,newShortPW,SHORTPW_LENGTH);

	//在NVRAM添加ID UPDATING_SHORTPW_TO_BLE值为0x01
	uint8 value =0x01;
	itr_bool save = saveNvramId(NVRAMID_UPDATING_SHORTPW_TO_BLE, &value, 1);

	to_send_NEW_SHORTPW_ONUART( newShortPW);

}




void disposeGwState(uint8 gwState)
{
	switch(gwState)
	{
	case GW_State_Illegal:// =0xff:
	{
		//TODO  mac 地址非法: ssid/cloud/shop 3 alert RED LEDs 同时慢闪
	}
	break;
	case GW_State_Initial_NotLocated:// =0x01
	{
		//自动删除网关配置GW_CONFIG (SSID/PWD, CLOUD_INFO,shortPW 用户短密码)。删完后ssid/cloud/shop 3 alert RED LEDs全常亮。
		wifiResetFactory();
	}
	break;
	case GW_State_Online_Located:// =0x04
	{
		//TODO 心跳包正常在线且已绑定门店。 ssid/cloud/shop 3个alert RED LEDs都灭
	}
	break;
	case GW_State_Online_Error_Located://=0xfd
	{
		//TODO 如果某一个routerMac 下有网关捆绑了多个店，则这些网关的shop RED led 都快闪，	提示要检查其中某些网关捆绑错了门店.  ssid/cloud 2个alert RED LEDs都灭
	}
	break;
	default:
		break;
	}

}

void disposeEtagState(uint8* etagMacBytes, uint8 etagState,uint8* decoded_hbfeedback, uint16 decryptSize)
{
	uint8* etagGwHbFeedbackOnUart_header = decoded_hbfeedback;

	if( Etag_State_Online_ProductBound == etagState)
	{
//			先所有都不发向UART。// 也许改为：	每TAG_RETURN_RATIO个才转发一个到uart。
	}
	else
	{
		// 全部转发: 有MD5_16_bytes + FFCS数据
		if(decryptSize > ETAG_HB_FEEDBACK_HEADER_LENGTH + MD5_16_BYTE_LENGTH)
		{//分包处理

			//参见  电子价签云服务器接口规范二 价签点阵数据定义V1.1

			uint8* md5_16_bytes = decoded_hbfeedback + ETAG_HB_FEEDBACK_HEADER_LENGTH; //MD5_16_BYTE_LENGTH
			uint8* ffcs = decoded_hbfeedback + ETAG_HB_FEEDBACK_HEADER_LENGTH + MD5_16_BYTE_LENGTH;
			uint16 FFCS_length = decryptSize - ETAG_HB_FEEDBACK_HEADER_LENGTH - MD5_16_BYTE_LENGTH;

			//分包后全部放入缓存
			int8 send = sendOneFFCS(etagMacBytes, etagState, md5_16_bytes,  ffcs,  FFCS_length);
		}
		else
		{
			appendCache2Uart(etagMacBytes, etagGwHbFeedbackOnUart_header,ETAG_HB_FEEDBACK_HEADER_LENGTH);
		}
	}
}

#include "gwWifiDriver.h"
//API: 被wifi接收函数调用
<<<<<<< HEAD
void parseHbFeedback(uint8* shortPW, uint8* hbFeedbackPackage, uint16 hbFeedbackPackage_length, uint8* myMacBytes)
=======
void parseHbFeedback(uint8_itr* shortPW, uint8_itr* hbFeedbackPackage, uint16_itr hbFeedbackPackage_length, uint8_itr* myMacBytes)
>>>>>>> cd3803a... aaaaaa
{
	if(shortPW == NULL || hbFeedbackPackage ==NULL || myMacBytes == NULL)
	{
		return ;
	}
	if(hbFeedbackPackage_length < FLOWNO_BYTE_LENGTH )
	{
		return ;//太短
	}

	uint16 receiveFlowNo = getUint16_big_endian(hbFeedbackPackage);

	itr_bool valid = flowNoValid(receiveFlowNo);
	if(!valid)
	{
		//该包已过期timeout
		return;
	}
<<<<<<< HEAD

	uint16 decryptSize =0;
	uchar* decode = blowfishDec(shortPW, hbFeedbackPackage + FLOWNO_BYTE_LENGTH ,
=======
<<<<<<< HEAD
#if defined _itrackerDebug_
	myPrintf("[parseHbFeedback] get decrypted=%s\n" ,  hbFeedbackPackage +FLOWNO_BYTE_LENGTH  );
#endif
=======
>>>>>>> c1497af... a

	uint16_itr decryptSize =0;
	uchar_itr* decode = blowfishDec(shortPW, hbFeedbackPackage + FLOWNO_BYTE_LENGTH ,
>>>>>>> cd3803a... aaaaaa
			hbFeedbackPackage_length -(FLOWNO_BYTE_LENGTH ) , &decryptSize);

	//ETAG_GW_HB_FEEDBACK_STATE_LENGTH=9 or ETAG_GW_HB_FEEDBACK_STATE_LENGTH(9+N) or GW_NEW_SHOWRTPW_LENGTH=14
	if(decode == NULL || decryptSize < ETAG_GW_HB_FEEDBACK_STATE_LENGTH)
	{//blowfish解密失败
		return ;
	}

	//0 is same; 1 is different;  2 is same without capital cared
	uint8 compare = chararrayCompare( decode + CMD_LENGTH,  MAC_BYTE_LENGTH, myMacBytes,  MAC_BYTE_LENGTH, 0);
	if( compare !=0 )
	{//blowfish解密失败，因为密码不正确，得到了错误的数据.所以mac匹配不上。
		return ;
	}


<<<<<<< HEAD
	uint8 subcmd = *(decode +CMD_LENGTH + MAC_BYTE_LENGTH );
=======
	uint8_itr subcmd = *(decode +CMD_LENGTH + MAC_BYTE_LENGTH );
>>>>>>> cd3803a... aaaaaa

	myPrintf("parseHbFeedback cmd =0x%x, subcmd= 0x%x\n",*decode,subcmd);
	if(CMD_ETAG_GW_HB_FEEDBACK_STATE == *decode)
	{
		//TODO cancel TIMER_TIMEOUT_SET_GW_OFFLINE  (in gwWifiHb.c)

		if( SUBCMD_GW_STATE == subcmd )
		{
<<<<<<< HEAD
			uint8 gwState = *(decode +CMD_LENGTH + MAC_BYTE_LENGTH + SUBCMD_LENGTH);
=======
			uint8_itr gwState = *(decode +CMD_LENGTH + MAC_BYTE_LENGTH + SUBCMD_LENGTH);
>>>>>>> cd3803a... aaaaaa
			myPrintf("parseHbFeedback gwState =0x%x\n",gwState);
			disposeGwState(gwState);
		}
		else if( SUBCMD_GW_NEW_SHORTPW == subcmd )
		{
			uint8* newShortPW = (decode +CMD_LENGTH + MAC_BYTE_LENGTH + SUBCMD_LENGTH);
			todoNewShortPW(newShortPW);
		}
	}
	else if(CMD_TAG_ETAG_GW_HB_FEEDBACK_STATE == *decode)
	{
		if( SUBCMD_TAG_STATE == subcmd )
		{
<<<<<<< HEAD
			uint8 etagState = *(decode +CMD_LENGTH + MAC_BYTE_LENGTH + SUBCMD_LENGTH + MAC_BYTE_LENGTH);
			myPrintf("parseHbFeedback etagState =0x%x\n",etagState);

			uint8* etagMacBytes = decode +CMD_LENGTH + MAC_BYTE_LENGTH + SUBCMD_LENGTH;
=======
			uint8_itr etagState = *(decode +CMD_LENGTH + MAC_BYTE_LENGTH + SUBCMD_LENGTH + MAC_BYTE_LENGTH);
			myPrintf("parseHbFeedback etagState =0x%x\n",etagState);

			uint8_itr* etagMacBytes = decode +CMD_LENGTH + MAC_BYTE_LENGTH + SUBCMD_LENGTH;
>>>>>>> cd3803a... aaaaaa
			disposeEtagState(etagMacBytes,etagState, decode,decryptSize );
		}
	}

}
