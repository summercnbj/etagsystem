/*
 * etagBleDriver.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */


#include "etagBleDriver.h"
#include "bleDriver.h"

//~~~~~~~~~~~~~~~~内存变量~~~~~~~~~~~~~~~~~~~~~~~
static uint8 etagBattPercentage =99;
static uint8 etagShortPW[SHORTPW_LENGTH];
static uint8 etagMacBytes[MAC_BYTE_LENGTH];
static uint8 md5_16_bytes[MD5_16_BYTE_LENGTH] = {0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18};

void setEtagBattPercentage(uint8 batt)
{
	etagBattPercentage = batt;
}
uint8 getEtagBattPercentage()
{
	return etagBattPercentage;
}
uint8* getEtagShortPW()
{
	return etagShortPW;
}
uint8* getEtagMacBytes()
{
	return etagMacBytes;
}
uint8* getEtagMd5_16_bytes()
{
	return md5_16_bytes;
}


static uint8 etagProductModel[PRODUCTMODEL_LENGTH_MAX+1];//8字节 ET-1101
static uint8 etagSoftwareVersion[SOFTWAREVERSION_LENGTH_MAX+1];//xxx.xx
static uint8 etagHardwareVersion[HARDWAREVERSION_LENGTH_MAX+1];//xxx.xx

uint8* getEtagProductModel()
{
	return etagProductModel;
}
uint8* getEtagSoftwareVersion()
{
	return etagSoftwareVersion;
}
uint8* getEtagHardwareVersion()
{
	return etagHardwareVersion;
}

//~~~~~~~~~~~~~~~~上面是内存变量~~~~~~~~~~~~~~~~~~~~~~~



void etagResetFactory()
{
	//TODO  删除数据SAP等，all NVRAMIDs




	//最后
	bleRebooting();
}




/**
 * 保存大数据。非NVRAMID。
 * @sector_base从哪个扇区开始存储
 * @serial 序号(数据分片里的序号)
 * @chararray 要存的数据，长度为length
 *
 */
int8 saveSector( uint16 sector_base, uint16 serial, uint8* chararray, uint32 length)
{

	if( length > ETAG_FLASH_SECTOR_SIZE)
	{
		length = ETAG_FLASH_SECTOR_SIZE;
	}

	//TODO  保存到sector_base+serial扇区里




	return 0;
}
