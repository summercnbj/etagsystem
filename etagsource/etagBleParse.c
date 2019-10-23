/*
 * etag.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#include "etagBleParse.h"






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



