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


//API:返回malloc，用完需要释放myFree(...)
uint8* get_ETAG_GW_HB_FEEDBACK_STATE_ONUART(uint8* etagMacBytes, uint8 etagState,uint8* FFCS_md5_16_bytes, uint8* fcssp, uint32 FCSSP_length,uint32 *package_length )
{

	*package_length = TAG_ETAG_GW_HB_FEEDBACK_STATE_ONUART_HEADER_LENGTH;
	if(FCSSP_length > 0)
		*package_length += MD5_16_BYTE_LENGTH +FCSSP_length ;

	myPrintf("FCSSP_length=%lld, *package_length=%lld\n",FCSSP_length, *package_length);
<<<<<<< HEAD
	uint8* package = (uint8*)myMalloc(*package_length , _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
=======
	uint8_itr* package = (uint8_itr*)myMalloc(*package_length , _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
>>>>>>> cd3803a... aaaaaa
	if(package ==NULL)
	{
		return NULL;
	}

	*package = CMD_TAG_ETAG_GW_HB_FEEDBACK_STATE;
	copyCharArrayIntoBuffer(etagMacBytes,MAC_BYTE_LENGTH,package + CMD_LENGTH);
	*(package +CMD_LENGTH + MAC_BYTE_LENGTH) = SUBCMD_TAG_STATE;
	*(package +CMD_LENGTH + MAC_BYTE_LENGTH + SUBCMD_LENGTH) = etagState;

	if(FCSSP_length > 0)
	{
		copyCharArrayIntoBuffer(FFCS_md5_16_bytes,MD5_16_BYTE_LENGTH, package +TAG_ETAG_GW_HB_FEEDBACK_STATE_ONUART_HEADER_LENGTH);
		copyCharArrayIntoBuffer(fcssp,FCSSP_length, package +TAG_ETAG_GW_HB_FEEDBACK_STATE_ONUART_HEADER_LENGTH+MD5_16_BYTE_LENGTH );
	}
	return package;
}


