/*
 * etagBleDriver.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */


#include "etagBleDriver.h"
#include "bleDriver.h"


void etagResetFactory()
{
	//TODO  删除数据SAP等，all NVRAMIDs




	//最后
	bleRebooting();
}




/**
 * 保存大数据。非NVRAMID。
 * @sector_base从哪个扇区开始存储
 * @serial 序号
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

}
