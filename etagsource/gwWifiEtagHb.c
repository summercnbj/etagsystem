/*
 * etagGwHb.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#include "gwWifiEtagHb.h"
#include "gwWifiDriver.h"

uint8* getGwWifiEtagHbCore( uint8* uuidBytes, uint8 battPercentage, uint8* rootMacBytes, uint8* etagHbOnUart_body,uint16* hbCore_length)
{
	*hbCore_length = ETAG_GW_HB_LENGTH;
	uint8* hbCore = (uint8*)myMalloc(*hbCore_length,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
	if(NULL == hbCore)
		return NULL;
	*hbCore =CMD_TAG_GW_HB;
	copyCharArrayIntoBuffer(uuidBytes,UUID_BYTE_LENGTH, hbCore+ CMD_LENGTH );
	*(hbCore+CMD_LENGTH+ UUID_BYTE_LENGTH) =battPercentage;
	copyCharArrayIntoBuffer(rootMacBytes,MAC_BYTE_LENGTH, hbCore+ CMD_LENGTH+UUID_BYTE_LENGTH+BATTPERCENTAGE_LENGTH );
	copyCharArrayIntoBuffer(etagHbOnUart_body,TAG_HB_ONUART_LENGTH, hbCore+ CMD_LENGTH+UUID_BYTE_LENGTH+BATTPERCENTAGE_LENGTH+MAC_BYTE_LENGTH );

	return hbCore;
}


#include "gwWifiEncDec.h"
/** 获得已经加密组装了流水号的ETAG GW心跳包，准备发送到云服务器
 * @shortPW 密码
 * @flowNo 云请求的流水号
 * @wifiMacBytes 长度为MAC_BYTE_LENGTH=6
 * @gwBattPercentage  gw电量百分比
 * @rootMacBytes 长度为MAC_BYTE_LENGTH
 * @rootMacBytes 路由器MAC
 * @etagHbOnUart_body 通过uart从蓝牙收到的包去掉CMD的尾巴，长度为TAG_HB_ONUART_LENGTH-1
 * @package_length 保存最终的字节总数
 * @return 心跳包; 或者  内存分配失败返回NULL
 * 心跳包总长度为package_length。
 *
 */
uint8* getGwWifiEtagHbPackage(uint8* shortPW, uint16 flowNo, uint8* wifiMacBytes,uint8 gwBattPercentage, uint8* rootMacBytes,uint8* etagHbOnUart_body,
		uint16 *package_length)
{
	addFlowNo();
<<<<<<< HEAD
	uint8* uuidBytes = formUuidBytes( wifiMacBytes);

	uint16 gwWifiEtagHbCore_length =0;
	uint8* gwWifiEtagHbCore = getGwWifiEtagHbCore( uuidBytes, gwBattPercentage, rootMacBytes,etagHbOnUart_body, &gwWifiEtagHbCore_length);
=======
	uint8_itr* uuidBytes = formUuidBytes( wifiMacBytes);

	uint16_itr gwWifiEtagHbCore_length =0;
	uint8_itr* gwWifiEtagHbCore = getGwWifiEtagHbCore( uuidBytes, gwBattPercentage, rootMacBytes,etagHbOnUart_body, &gwWifiEtagHbCore_length);
>>>>>>> cd3803a... aaaaaa
	myPrintf("getGwWifiEtagHbPackage gwWifiEtagHbCore_length= %d\n" , gwWifiEtagHbCore_length);
	myFree(uuidBytes);
	if( gwWifiEtagHbCore_length < GW_HBCORE_HEADER_LENGTH - BUSY_LENGTH) //without busy
	{//error
		myFree(gwWifiEtagHbCore);
		return NULL;
	}

<<<<<<< HEAD
	uint16 gwWifiEtagHbCoreEncrypt_length =0;
	uint8* gwWifiEtagHbCoreEncrypt = getHbCoreEncrypt( shortPW,  gwWifiEtagHbCore , gwWifiEtagHbCore_length,&gwWifiEtagHbCoreEncrypt_length);
=======
	uint16_itr gwWifiEtagHbCoreEncrypt_length =0;
	uint8_itr* gwWifiEtagHbCoreEncrypt = getHbCoreEncrypt( shortPW,  gwWifiEtagHbCore , gwWifiEtagHbCore_length,&gwWifiEtagHbCoreEncrypt_length);
>>>>>>> cd3803a... aaaaaa
	myPrintf("getGwWifiEtagHbPackage gwWifiEtagHbCoreEncrypt_length= %d\n" , gwWifiEtagHbCoreEncrypt_length);
	myFree(gwWifiEtagHbCore);
	if(NULL == gwWifiEtagHbCoreEncrypt)
		return NULL;

<<<<<<< HEAD
	uint8* package = formHbPackage( shortPW,  flowNo,  wifiMacBytes,  gwWifiEtagHbCoreEncrypt , gwWifiEtagHbCoreEncrypt_length, package_length);
=======
	uint8_itr* package = formHbPackage( shortPW,  flowNo,  wifiMacBytes,  gwWifiEtagHbCoreEncrypt , gwWifiEtagHbCoreEncrypt_length, package_length);
>>>>>>> cd3803a... aaaaaa
	myFree(gwWifiEtagHbCoreEncrypt);
	myPrintf("getGwWifiEtagHbPackage package_length= %d\n" , *package_length);

	return package;//用完后需要myFree
}
