/*
 * gwWifi.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#include "gwWifiHb.h"

#include "itrackerBlowFish.h"



/** 获得已经加密组装了流水号的GW心跳包，准备发送到云服务器
 * @uuid 长度为UUID_BYTE_LENGTH=42
 * @battPercentage  电量百分比
 * @rootMacBytes 长度为MAC_BYTE_LENGTH
 * @isBusy 暂不用，填0
 * @productModel 型号常量字符串
 * @softwareVersion 软件版本常量字符串
 * @hardwareVersion 硬件版本常量字符串
 * @return 心跳包; 或者  内存分配失败返回NULL
 * 心跳包总长度为：
 * int length = header_len + stringlen(productModel) + stringlen(softwareVersion) + stringlen(hardwareVersion) +3;
 * 其中
 * int header_len = CMD_LENGTH + UUID_BYTE_LENGTH + BATTPERCENTAGE_LENGTH + MAC_BYTE_LENGTH + BUSY_LENGTH =51;
 *
 */
uint8* getGwHbCore(uint8* uuidBytes,uint8 gwBattPercentage,uint8* rootMacBytes,
		itr_bool isBusy,uint8* gwProductModel,uint8*gwSoftwareVersion,uint8*gwHardwareVersion,uint16 *gwHbCore_length)
{
	printf("length= %d\n", 0 );
	if(uuidBytes ==NULL || rootMacBytes==NULL)
	{
		return NULL;
	}
//	if(productModel==NULL || softwareVersion == NULL ||hardwareVersion==NULL)
//	{
//		return NULL;
//	}

	int header_len = GW_HBCORE_HEADER_LENGTH;

	int productModel_length = stringlen(gwProductModel) ;
	int softwareVersion_length = stringlen(gwSoftwareVersion) ;
	int hardwareVersion_length = stringlen(gwHardwareVersion) ;

	*gwHbCore_length = header_len + productModel_length+softwareVersion_length+hardwareVersion_length +3;
	printf("*gwHbCore_length= %d\n", *gwHbCore_length );
	//3 is for ending 0 of productModel,softwareVersion,hardwareVersion
	uint8* core = (uint8*)myMalloc(*gwHbCore_length,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);

//	return NULL;
	if(core == NULL)
		return NULL;

	core[0] = CMD_GW_HB;
	copyCharArrayIntoBuffer(uuidBytes, UUID_BYTE_LENGTH, core + CMD_LENGTH);
	core[CMD_LENGTH + UUID_BYTE_LENGTH] = gwBattPercentage;
	copyCharArrayIntoBuffer(uuidBytes, MAC_BYTE_LENGTH, core + CMD_LENGTH + UUID_BYTE_LENGTH + BATTPERCENTAGE_LENGTH);

	core[CMD_LENGTH + UUID_BYTE_LENGTH + BATTPERCENTAGE_LENGTH + MAC_BYTE_LENGTH] =isBusy;

	copyCharArrayIntoBuffer(gwProductModel,productModel_length,core + header_len);
	core[header_len + productModel_length] =0;//ending 0

	copyCharArrayIntoBuffer(gwSoftwareVersion,softwareVersion_length,core + header_len +productModel_length +1);
	core[header_len + productModel_length +1 + softwareVersion_length] =0;//1 is for ending 0

	copyCharArrayIntoBuffer(gwHardwareVersion,hardwareVersion_length,core + header_len +productModel_length +1 +softwareVersion_length +1 );
	core[header_len + productModel_length +1 + softwareVersion_length + 1+ hardwareVersion_length] =0;//1 is for ending 0

	return core;
}



void TIMER_TIMEOUT_SET_GW_OFFLINE()
{

	//TODO cloud LED 灭 。  表示访问云服务器失败

}


#include "gwWifiEncDec.h"
/**
 * @shortPW 密码
 * @flowNo 云请求的流水号
 * @macBytes 长度为MAC_BYTE_LENGTH=6
 * @battPercentage  电量百分比
 * @rootMacBytes 长度为MAC_BYTE_LENGTH
 * @isBusy 暂不用，填0
 * @productModel 型号常量字符串
 * @softwareVersion 软件版本常量字符串
 * @hardwareVersion 硬件版本常量字符串
 * @package_length 保存最终的字节总数
 * @return 心跳包; 或者  内存分配失败返回NULL
 * 心跳包总长度为package_length。
 *
 */
uint8* formGwHbPackage(uint8* shortPW, uint16 flowNo, uint8* wifiMacBytes,uint8 gwBattPercentage,uint8* rootMacBytes,
		itr_bool isBusy,uint8* gwProductModel,uint8*gwSoftwareVersion,uint8*gwHardwareVersion,uint16 *package_length)
{
	uint8* uuidBytes = formUuidBytes( wifiMacBytes);

	uint16 gwHbCore_length =0;
	uint8* gwHbCore = getGwHbCore( uuidBytes, gwBattPercentage, rootMacBytes,
			 isBusy, gwProductModel,gwSoftwareVersion,gwHardwareVersion,&gwHbCore_length);

	myFree(uuidBytes);
	if( gwHbCore_length < GW_HBCORE_HEADER_LENGTH)
	{//error
		myFree(gwHbCore);
		return NULL;
	}

	uint16 gwHbCoreEncrypt_length =0;
	uint8* gwHbCoreEncrypt = getHbCoreEncrypt( shortPW,  gwHbCore , gwHbCore_length,&gwHbCoreEncrypt_length);
	myFree(gwHbCore);

	uint8* package = formHbPackage( shortPW,  flowNo,  wifiMacBytes,  gwHbCoreEncrypt , gwHbCoreEncrypt_length, package_length);
	myFree(gwHbCoreEncrypt);


	if(package != NULL)
	{
		//TODO
		/*
		start a timer: TIMER_TIMEOUT_SET_GW_OFFLINE:
		timeout: GW_RETURN_RATIO *GW_INTERVAL_at_HALFMINUTE * 30 seconds

		*/
	}


	return package;//用完后需要myFree
}

uint8* getGwHbPackage(uint16 *package_length)
{
	addFlowNo();
	return formGwHbPackage(getShortPW(), getFlowNo(), getWifiMacBytes(),getGwBattPercentage(),getRootMacBytes(),
			0, getGwProductModel(), getGwSoftwareVersion(), getGwHardwareVersion(), package_length);
}


/*~~~~~~~~~~~~~~~~~~~~~~TEST~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void testGwHb()
{
	uint8 macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
	uint8* uuidBytes = formUuidBytes( macBytes);
//	uint8 uuidBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33
//			,0,0,0,0,0,0  ,0,0,0,0,0,0 ,0,0,0,0,0,0 ,0,0,0,0,0,0 ,0,0,0,0,0,0 ,0,0,0,0,0,0 };
//	printf("=%d\n",uuidBytes[2]);
	uint8 battPercentage = 39;
	uint8 rootMacBytes[MAC_BYTE_LENGTH] = {0x12,0x34,0x56,0x78,0x9a,0xbc};
	itr_bool isBusy =0;
//	uint8* productModel = "et-1099";
//	uint8*softwareVersion = "66.77";
	uint8*hardwareVersion = "88.99";
	uint8* productModel = NULL;
	uint8*softwareVersion = NULL;
//	uint8*hardwareVersion = NULL;

	uint16 gwHbCore_length =0;
	uint8* ret = getGwHbCore( uuidBytes, battPercentage, rootMacBytes,
			 isBusy, productModel,softwareVersion,hardwareVersion,&gwHbCore_length);

	if(uuidBytes !=NULL)
		myFree(uuidBytes);
	if(ret == NULL)
	{
		printf("ret is NULL\n");
		return ;
	}
	int header_len = GW_HBCORE_HEADER_LENGTH;

	int productModel_length = stringlen(productModel) ;
	int softwareVersion_length =stringlen(softwareVersion) ;
	int hardwareVersion_length =stringlen(hardwareVersion) ;

	//ret的总长度为：
	printf("gwHbCore_ength length= %d\n", gwHbCore_length);
	printCharArray("getGwHbStr ", ret , header_len);
	printf("productModel= %s\n", ret + header_len);
	printf("softwareVersion= %s\n", ret + header_len + stringlen(productModel) +1);
	printf("hardwareVersion= %s\n", ret + header_len +  stringlen(productModel) +1 + stringlen(softwareVersion) +1);


	uint8* shortPW = "123456";
	uint8* gwHbCore = ret;

	uint16 encryptedSize =0;
	uint8* encode = getHbCoreEncrypt( shortPW, gwHbCore, gwHbCore_length, &encryptedSize);
	printf("encryptedSize= %d\n", encryptedSize);

	myFree(gwHbCore);

	uint16 decryptSize =0;
	uchar* decode = blowfishDec(shortPW, encode, encryptedSize, &decryptSize);
	printf("decryptSize= %d\n", decryptSize);
}

void fish()
{
	uint8* shortPW = "123456";
	uint8* gwHbStr = "abced";
	uint16 gwHbStr_length = 5;

	uint16 encryptedSize =0;
	uint8* encode = blowfishEnc( shortPW, gwHbStr, gwHbStr_length, &encryptedSize);
	printf("encryptedSize= %d\n", encryptedSize);

	uint16 decryptSize =0;
	uchar* decode = blowfishDec(shortPW, encode, encryptedSize, &decryptSize);
	printf("decryptSize= %d\n", decryptSize);
	printf("decode= %s\n", decode);
}

#if 0
int main()
{
//	fish();
	testGwHb();


	return 0;
}
#endif
