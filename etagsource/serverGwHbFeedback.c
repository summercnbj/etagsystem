/*
 * etagServerHbFeedback.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#include "serverGwHbFeedback.h"



/**
 * 给心跳包gwHbFeedbackCore做blowfish加密
 * @shortPW 密码
 * @gwHbFeedbackCore 心跳包
 * @gwHbFeedbackCore_length 心跳包长度
 * @encryptedSize 密文长度存入该地址
 * @return 密文
 */
uint8* getGwHbFeedbackCoreEncrypt(uint8* shortPW, uint8* gwHbFeedbackCore ,uint16 gwHbFeedbackCore_length, uint16 *encryptedSize)
{
	if(gwHbFeedbackCore == NULL || gwHbFeedbackCore_length == 0)
	{
		return NULL;
	}

	uint8* encode = blowfishEnc(shortPW, gwHbFeedbackCore,gwHbFeedbackCore_length, encryptedSize);
	myPrintf("encryptedSize= %d\n", *encryptedSize);

	return encode;
}

uint8* formGwHbFeedbackPackage(uint8* shortPW,  uint16 flowNo, uint8* gwHbFeedbackCoreEncrypt ,uint16 gwHbFeedbackCoreEncrypt_length, uint16 *package_length)
{
	if(gwHbFeedbackCoreEncrypt_length ==0)
		return NULL;
	*package_length = FLOWNO_BYTE_LENGTH +  gwHbFeedbackCoreEncrypt_length;
	uint8* package = (uint8*)myMalloc(*package_length,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
	if(package == NULL)
	{
		return NULL;
	}

	uint16_into_big_endian_bytes( flowNo,  package,  *package_length);
	copyCharArrayIntoBuffer( gwHbFeedbackCoreEncrypt, gwHbFeedbackCoreEncrypt_length, package + FLOWNO_BYTE_LENGTH );

	return package;
}



//~~~~~~~~~~~~~~~~~~~~返回网关状态~~~~~~~~~~~~~~~~~~~~


uint8* getGwHbFeedbackStateCore(uint8* macBytes, uint8 gwState)
{
	if(macBytes == NULL)
		return NULL;
	uint8* core = (uint8*)myMalloc(GW_HB_FEEDBACK_LENGTH,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
	*(core) = CMD_GW_HB_FEEDBACK;
	copyCharArrayIntoBuffer(macBytes, MAC_BYTE_LENGTH, core + CMD_LENGTH);
	*(core + CMD_LENGTH + MAC_BYTE_LENGTH) = SUBCMD_GW_STATE;
	*(core + CMD_LENGTH + MAC_BYTE_LENGTH +SUBCMD_LENGTH) = gwState;

	return core;
}



uint8* getGwHbFeedbackStatePackage(uint8* shortPW, uint16 flowNo, uint8* macBytes, uint8 gwState,uint16 *package_length)
{
	uint8* core = getGwHbFeedbackStateCore( macBytes,  gwState);
	if( core == NULL)
	{//error
		return NULL;
	}
	uint16 encryptedSize =0;
	uint8* coreEncrypt = getGwHbFeedbackCoreEncrypt(shortPW, core ,GW_HB_FEEDBACK_LENGTH, &encryptedSize);
	myFree(core);
	uint8* package = formGwHbFeedbackPackage( shortPW, flowNo,  coreEncrypt ,encryptedSize, package_length);
	myFree(coreEncrypt);
	return package;
}




//~~~~~~~~~~~~~~~~~~~~修改shortPW~~~~~~~~~~~~~~~~~~~~

uint8* getGwHbFeedbackNewShortPWCore(uint8* macBytes, uint8* newShortPW)
{
	if(macBytes == NULL)
		return NULL;
	uint8* core = (uint8*)myMalloc(GW_NEW_SHOWRTPW_LENGTH, _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
	*(core) = CMD_GW_HB_FEEDBACK;
	copyCharArrayIntoBuffer(macBytes, MAC_BYTE_LENGTH, core + CMD_LENGTH);
	*(core + CMD_LENGTH + MAC_BYTE_LENGTH) = SUBCMD_GW_NEW_SHORTPW;
	copyCharArrayIntoBuffer(newShortPW, SHORTPW_LENGTH, core + CMD_LENGTH+ MAC_BYTE_LENGTH +SUBCMD_LENGTH);
	return core;
}

uint8* getGwHbFeedbackNewShortPWPackage(uint8* shortPW, uint16 flowNo, uint8* macBytes, uint8* newShortPW,uint16 *package_length)
{
	uint8* core = getGwHbFeedbackNewShortPWCore( macBytes,  newShortPW);
	if( core == NULL)
	{//error
		return NULL;
	}
	uint16 encryptedSize =0;
	uint8* coreEncrypt = getGwHbFeedbackCoreEncrypt(shortPW, core ,GW_NEW_SHOWRTPW_LENGTH, &encryptedSize);
	myFree(core);
	uint8* package = formGwHbFeedbackPackage( shortPW, flowNo,  coreEncrypt ,encryptedSize, package_length);
	myFree(coreEncrypt);
	return package;
}





