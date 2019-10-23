/*
 * gwWifiParseGwHbFeedback.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */
#include "gwWifiParseHbFeedback.h"

//开机即检查：如果NVRAM添加ID UPDATING_SHORTPW_TO_BLE值为0x01
void onBoot_check_UPDATING_SHORTPW_TO_BLE(uint8* shortPW)
{
	//TODO 如果NVRAM ID UPDATING_SHORTPW_TO_BLE存在，值为0x01，send_NEW_SHORTPW_ONUART(shortPW);
	itr_bool UPDATING_SHORTPW_TO_BLE = 0;
	if(UPDATING_SHORTPW_TO_BLE )
	{
		send_NEW_SHORTPW_ONUART(shortPW);
	}

}


void send_NEW_SHORTPW_ONUART(uint8* shortPW)
{
	printCharArray("todoNewShortPW:", shortPW, SHORTPW_LENGTH);

	//TODO  向网关里的所有蓝牙发送GW_NEW_SHORTPW_ONUART并确保都收到了

	//TODO 必须等收到了所有的应答后才能删除NVRAM ID UPDATING_SHORTPW_TO_BLE

}




//SHORTPW_LENGTH
void todoNewShortPW(uint8* newShortPW)
{

	//TODO  更改 NVRAM ID SHORTPW的值为newShortPW,长度SHORTPW_LENGTH

	//TODO 在NVRAM添加ID UPDATING_SHORTPW_TO_BLE值为0x01


	send_NEW_SHORTPW_ONUART( newShortPW);

}

void parseHbFeedback(uint8* shortPW, uint8* hbFeedbackPackage, uint16 hbFeedbackPackage_length, uint8* myMacBytes)
{
	if(shortPW == NULL || hbFeedbackPackage ==NULL || myMacBytes == NULL)
	{
		return ;
	}
	if(hbFeedbackPackage_length < FLOWNO_BYTE_LENGTH )
	{
		return ;//太短
	}

	uint16 decryptSize =0;
	uchar* decode = blowfishDec(shortPW, hbFeedbackPackage +FLOWNO_BYTE_LENGTH  ,
			hbFeedbackPackage_length -(FLOWNO_BYTE_LENGTH ) , &decryptSize);

	//GW_HB_FEEDBACK_LENGTH=9 or ETAG_GW_HB_FEEDBACK_LENGTH(9+N) or GW_NEW_SHOWRTPW_LENGTH=14
	if(decode == NULL || decryptSize < GW_HB_FEEDBACK_LENGTH)
	{//blowfish解密失败
		return ;
	}

	//0 is same; 1 is different;  2 is same without capital cared
	uint8 compare = chararrayCompare( decode + CMD_LENGTH,  MAC_BYTE_LENGTH, myMacBytes,  MAC_BYTE_LENGTH, 0);
	if( compare !=0 )
	{//blowfish解密失败，因为密码不正确，得到了错误的数据.所以mac匹配不上。
		return ;
	}


	uint8 subcmd = *(decode +CMD_LENGTH + MAC_BYTE_LENGTH );

	myPrintf("cmd =0x%x, subcmd= 0x%x\n",*decode,subcmd);
	if(*decode == CMD_GW_HB_FEEDBACK )
	{
		//TODO cancel TIMER_TIMEOUT_SET_GW_OFFLINE  (in gwWifiHb.c)



		if( subcmd == SUBCMD_GW_STATE )
		{
			uint8 gwState = *(decode +CMD_LENGTH + MAC_BYTE_LENGTH + SUBCMD_LENGTH);
			myPrintf("gwState =0x%x\n",gwState);
			switch(gwState)
			{
			case GW_State_Illegal:// =0xff:
			{
				//TODO  mac 地址非法: ssid/cloud/shop leds 同时慢闪
			}
			break;
			case GW_State_Initial_NotLocated:// =0x01
			{
				//TODO 自动删除网关配置GW_CONFIG (SSID/PWD, CLOUD_INFO,shortPW 用户短密码)。
			}
			break;
			case GW_State_Online_Located:// =0x04
			{
				//心跳包正常在线且已绑定门店。
			}
			break;
			case GW_State_Online_Error_Located://=0xfd
			{
				//TODO 如果某一个routerMac 下有网关捆绑了多个店，则这些网关的shop RED led 都快闪，	提示要检查其中某些网关捆绑错了门店
			}
			break;
			default:
				break;
			}
		}
		else if( subcmd == SUBCMD_GW_NEW_SHORTPW )
		{

			uint8* newShortPW = (decode +CMD_LENGTH + MAC_BYTE_LENGTH + SUBCMD_LENGTH);
			todoNewShortPW(newShortPW);
		}

	}
	else if(*decode == CMD_TAG_GW_HB_FEEDBACK )
	{



	}

}
