/*
 * gwEncDec.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */
<<<<<<< HEAD
#include "gwWifiEncDec.h"
#include "itrackerBlowFish.h"

=======
#include "include/Cetagsource/gwWifiEncDec.h"
<<<<<<< HEAD
//#include "include/Ctools/itrackerBlowFish.h"
#include "include/Ctools/itrackerEncryptCs.h"
=======
#include "include/Ctools/itrackerBlowFish.h"

>>>>>>> c1497af... a
>>>>>>> cd3803a... aaaaaa

/**
 * 给心跳包hbCore做blowfish加密
 * @shortPW 密码
 * @hbCore 心跳包
 * @hbCore_length 心跳包长度
 * @encryptedSize 密文长度存入该地址
 * @return 密文
 */
<<<<<<< HEAD
uint8* getHbCoreEncrypt(uint8* shortPW, uint8* hbCore ,uint16 hbCore_length, uint16 *encryptedSize)
=======
uint8_itr* getHbCoreEncrypt(uint8_itr* shortPW, uint8_itr* hbCore ,uint16_itr hbCore_length, uint16_itr *encryptedSize)
>>>>>>> cd3803a... aaaaaa
{
	if(hbCore == NULL || hbCore_length == 0)
	{
		return NULL;
	}

<<<<<<< HEAD
	uint8* encode = blowfishEnc(shortPW, hbCore,hbCore_length, encryptedSize);
=======
	uint8_itr* encode = blowfishEnc(shortPW, hbCore,hbCore_length, encryptedSize);
>>>>>>> cd3803a... aaaaaa
	myPrintf("encryptedSize= %d\n", *encryptedSize);

	return encode;
}

<<<<<<< HEAD
uint8* formHbPackage(uint8* shortPW,  uint16 flowNo, uint8* wifiMacBytes, uint8* hbCoreEncrypt ,uint16 hbCoreEncrypt_length, uint16 *package_length)
=======
uint8_itr* formHbPackage(uint8_itr* shortPW,  uint16_itr flowNo, uint8_itr* wifiMacBytes, uint8_itr* hbCoreEncrypt ,uint16_itr hbCoreEncrypt_length, uint16_itr *package_length)
>>>>>>> cd3803a... aaaaaa
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
