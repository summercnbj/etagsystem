/*
 * etag.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#include "etagBleParse.h"

void etagDispseEtagState(uint8 etagState)
{
	switch(etagState)
	{
	case Etag_State_Illegal:// =0xff:非法：数据库里没有该mac
	{
		etagResetFactory();
		//保持出厂设置显示默认图案
	}
	break;

	//未初始化，未绑定有1种:
	case Etag_State_Initial_ProductUnbound:// 0x01//未绑定： 数据库里有该mac, 但是无绑定商品信息，无图案信息
	{
	}
	break;

	//已初始化，未绑定
	case Etag_State_Offline_ProductUnbound:// 0x02//有3种(都是不在线；若在线会被自动置为Etag_State_Initial_ProductUnbound):
	{
	}
	break;
	case Etag_State_NeverOnline_ProductUnbound:// 0x21
	{
	}
	break;
	case Etag_State_Offline_ShortPWmodified_ProductUnbound:// 0x22
	{
	}
	break;
	case Etag_State_Offline_ShortPWok_ProductUnbound:// 0x23
	{
	}
	break;

	//未初始化，已绑定
	case Etag_State_Initial_ProductBound:// 0x03
	{
	}
	break;

	//已初始化，已绑定且在线
	case Etag_State_Online_ProductBound:// 0x04//有2种:
	{
		//TODO 删除TIMER: TAG_RETURN_RATIO*TAG_INTERVAL_at_HALFMINUTE*30秒钟仍未收到云服务器返回数据包则置为Etag_State_Offline，在屏幕上增加"警示未接入网络"的标记)，TAG_RETURN_RATIO暂定为10；


	}
	break;
	case Etag_State_Online_Normal_ProductBound:// 0x41//没有新图案。
	{
		//TODO 删除TIMER: TAG_RETURN_RATIO*TAG_INTERVAL_at_HALFMINUTE*30秒钟仍未收到云服务器返回数据包则置为Etag_State_Offline，在屏幕上增加"警示未接入网络"的标记)，TAG_RETURN_RATIO暂定为10；

	}
	break;
	case Etag_State_Online_ProductBound_New_Pixeldata:// 0x42// 有了新图案
	{
		//TODO 删除TIMER: TAG_RETURN_RATIO*TAG_INTERVAL_at_HALFMINUTE*30秒钟仍未收到云服务器返回数据包则置为Etag_State_Offline，在屏幕上增加"警示未接入网络"的标记)，TAG_RETURN_RATIO暂定为10；

	}
	break;

	//已初始化，已绑定且不在线
	case Etag_State_Offline_ProductBound:// 0x05//有3种:
	{
	}
	break;
	case Etag_State_NeverOnline_ProductBound:// 0x51//, 0x52没有图案不允许绑定。
	{
	}
	break;
	case Etag_State_Offline_ShortPWmodified_ProductBound:// 0x53//, 0x54没有图案不允许绑定。
	{
	}
	break;
	case Etag_State_Offline_ShortPWok_ProductBound:// 0x55//,0x56没有图案不允许绑定。
	{
	}
	break;

	//泛状态
	case Etag_State_Offline:// =0xfe//包含已初始化，未绑定Etag_State_Offline_ProductUnbound = 0x02有3种和已初始化，已绑定且不在线Etag_State_Offline_ProductBound =0x05有3种。
	{
	}
	break;
	default:
			break;
	}
}



void slaveParseBlePackage(uint8* package,uint16 package_length)
{
	if(NULL == package || package_length < CMD_LENGTH)
	{
		return ;
	}

	switch(*package)
	{
	case CMD_TAG_GW_HB_FEEDBACK://心跳包
	{
		if(package_length < TAG_GW_HB_FEEDBACK_ONBLE_HEADER_LENGTH)
		{
			return;
		}

//		etagDispseEtagState(etagState);
	}
		break;
	case CMD_GW_NEW_SHORTPW://网关发放新密码
	{
		if(package_length - CMD_LENGTH < SHORTPW_LENGTH)
		{
			return;
		}
		uint8* newShortPW = package + CMD_LENGTH;
		itr_bool save = saveNvramId(NVRAMID_SHORTPW,  newShortPW,  SHORTPW_LENGTH);

		//TODO 将newShortPW更新到当前的全局变量里

	}
		break;
	default:
		break;
	}
}



