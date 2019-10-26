/*
 * gwEncDec.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */
#include "gwWifiEncDec.h"
#include "itrackerBlowFish.h"


/**
 * 给心跳包hbCore做blowfish加密
 * @shortPW 密码
 * @hbCore 心跳包
 * @hbCore_length 心跳包长度
 * @encryptedSize 密文长度存入该地址
 * @return 密文
 */
uint8* getHbCoreEncrypt(uint8* shortPW, uint8* hbCore ,uint16 hbCore_length, uint16 *encryptedSize)
{
	if(hbCore == NULL || hbCore_length == 0)
	{
		return NULL;
	}

	uint8* encode = blowfishEnc(shortPW, hbCore,hbCore_length, encryptedSize);
	myPrintf("encryptedSize= %d\n", *encryptedSize);

	return encode;
}

uint8* formHbPackage(uint8* shortPW,  uint16 flowNo, uint8* wifiMacBytes, uint8* hbCoreEncrypt ,uint16 hbCoreEncrypt_length, uint16 *package_length)
{
	if(hbCoreEncrypt_length ==0)
		return NULL;
	*package_length = FLOWNO_BYTE_LENGTH + MAC_BYTE_LENGTH + hbCoreEncrypt_length;
	uint8* package = (uint8*)myMalloc(*package_length,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
	if(package == NULL)
	{
		return NULL;
	}

	uint16_into_big_endian_bytes( flowNo,  package,  package_length);
	copyCharArrayIntoBuffer( wifiMacBytes, MAC_BYTE_LENGTH, package + FLOWNO_BYTE_LENGTH );
	copyCharArrayIntoBuffer( hbCoreEncrypt, hbCoreEncrypt_length, package + FLOWNO_BYTE_LENGTH + MAC_BYTE_LENGTH );

	return package;
}
