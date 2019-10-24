/*
 * gwWifi2Uart.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */
#include "gwWifi2Uart.h"


//十一，网关WIFICPU通知网关里的蓝牙新密码(GW_NEW_SHORTPW_ONUART)：从网关WIFICPU到网关上的蓝牙
//API:返回malloc，用完需要释放myFree(...)
uint8* get_GW_NEW_SHORTPW_ONUART(uint8* newShortPW)
{
	uint8* package = (uint8*)myMalloc(GW_NEW_SHORTPW_ONUART_LENGTH, _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);

	if(NULL == package)
	{
		return NULL;
	}

	*package =CMD_GW_NEW_SHORTPW;
	copyCharArrayIntoBuffer(newShortPW,SHORTPW_LENGTH,package);
	return package;
}








