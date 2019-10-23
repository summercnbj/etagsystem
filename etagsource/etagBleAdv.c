/*
 * etagBleAdv.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */


#include "etagBleAdv.h"


//生成TAG_HB 原始数据21字节
uint8* getOffsetDataCore(uint8* productModel, uint8*softwareVersion,uint8* hardwareVersion,uint8 battPercentage, uint8* md5_16_bytes )
{
	myPrintf("getOffsetDataCore productModel= %s\n",productModel);
	uint8* dataCore = (uint8*)myMalloc(TAG_HB_LENGTH,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
	if(dataCore == NULL)
		return NULL;

	*dataCore = CMD_TAG_HB;

	int len = stringlen(productModel) +1;//1 is for ending 0
	if(len > PRODUCTMODEL_LENGTH_MAX)
	{
		len = PRODUCTMODEL_LENGTH_MAX;
	}
	if(productModel)
		copyCharArrayIntoBuffer(productModel,len,dataCore + CMD_LENGTH);
	uint8 buffer[3];
	uint8 bufferlen =2;
	if(softwareVersion)
	{
		int8 ver = versionBytes( softwareVersion,  buffer,  bufferlen);
		copyCharArrayIntoBuffer(buffer,VERSION_BYTE_LENGTH,dataCore + CMD_LENGTH + PRODUCTMODEL_LENGTH_MAX);
	}
	if(hardwareVersion)
	{
		int ver = versionBytes( hardwareVersion,  buffer,  bufferlen);
		copyCharArrayIntoBuffer(buffer,VERSION_BYTE_LENGTH,dataCore + CMD_LENGTH + PRODUCTMODEL_LENGTH_MAX + VERSION_BYTE_LENGTH);
	}
	*(dataCore + CMD_LENGTH + PRODUCTMODEL_LENGTH_MAX + VERSION_BYTE_LENGTH +VERSION_BYTE_LENGTH) = battPercentage;
	if(md5_16_bytes)
	{
		copyCharArrayIntoBuffer(md5_16_bytes, MD5_16_BYTE_LENGTH,dataCore + CMD_LENGTH + PRODUCTMODEL_LENGTH_MAX + VERSION_BYTE_LENGTH+VERSION_BYTE_LENGTH + BATTPERCENTAGE_LENGTH);
	}
	return dataCore;
}

//根据参数生成adv数据写入buffer,buffer_length必须>=TAG_HB_ADV_LENGTH
void genAdvIntoBuffer(uint8* shortPW,uint8* productModel, uint8*softwareVersion,uint8* hardwareVersion,
		uint8 battPercentage, uint8* md5_16_bytes, uint8* buffer, uint16 buffer_length)
{
	myPrintf("genAdvIntoBuffer buffer_length= %d\n",buffer_length);
	if(buffer == NULL || buffer_length< TAG_HB_ADV_LENGTH)
		return ;
	*buffer = 0x02;
	*(buffer+1) = 0x01;
	*(buffer+2) = 0x06;
	*(buffer+ ADV_BYTEPOSITION_FOLLOWINGLENGTH) = FOWLLOWINGLENGTH;
	*(buffer+4) = 0xff;
	*(buffer+ ADV_BYTEPOSITION_VENDORMARK) = VENDORMARK_0;
	*(buffer+ADV_BYTEPOSITION_VENDORMARK+1) = VENDORMARK_1;
	*(buffer+ADV_BYTEPOSITION_VENDORMARK+2) = VENDORMARK_2;
	*(buffer+ADV_BYTEPOSITION_CMD) =CMD_TAG_HB;

	//生成TAG_HB 原始数据21字节
	uint8* dataCore = getOffsetDataCore( productModel, softwareVersion, hardwareVersion, battPercentage, md5_16_bytes );
	if(dataCore == NULL)
	{
		return;
	}
	doOffsetByShortPW(shortPW, dataCore, TAG_HB_LENGTH);

	copyCharArrayIntoBuffer(dataCore, TAG_HB_LENGTH, buffer+ADV_BYTEPOSITION_CMD + CMD_LENGTH);
	myFree(dataCore);
}


