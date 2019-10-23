/*
 * etagServer.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#include "serverParseHb.h"


void printGwHbPackage_struct(struct gwHbPackage_struct * package)
{
	if(package == NULL)
	{
		myPrintf("package is NULL\n");
		return;
	}
	myPrintf("type = %d\n", package->type);
	myPrintf("flowNo = %d\n", package->flowNo);
	printCharArray("uuidBytes = ", package->uuidBytes, UUID_BYTE_LENGTH);
	myPrintf("battPercentage = %d\n", package->battPercentage);
	printCharArray("routerMacBytes = ", package->routerMacBytes, MAC_BYTE_LENGTH);
	myPrintf("isBusy = %d\n", package->isBusy);
	myPrintf("productModel = %s\n", package->productModel);
	myPrintf("softwareVersion = %s\n", package->softwareVersion);
	myPrintf("hardwareVersion = %s\n", package->hardwareVersion);
}


struct gwHbPackage_struct * parseGwHbPackage(uint8* shortPW, uint8* gwHbPackage, uint16 gwHbPackage_length, uint8* gwHbCore, uint16 gwHbCore_length)
{
	if(gwHbCore_length < GW_HBCORE_HEADER_LENGTH)
		return NULL;
	struct gwHbPackage_struct *gwHbPackageStruct = (struct gwHbPackage_struct*)myMalloc(sizeof(struct gwHbPackage_struct)
				,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );

	if(gwHbPackageStruct == NULL)
	{
		return NULL;
	}
	gwHbPackageStruct->type = HB_TYPE_from_GW;
	gwHbPackageStruct->flowNo = (gwHbPackage[0] << 8) + gwHbPackage[1];//big endian

	copyCharArrayIntoBuffer( gwHbCore + CMD_LENGTH, UUID_BYTE_LENGTH ,gwHbPackageStruct->uuidBytes );

	gwHbPackageStruct->battPercentage = *(gwHbCore +CMD_LENGTH+ UUID_BYTE_LENGTH);
	copyCharArrayIntoBuffer( gwHbCore + CMD_LENGTH +UUID_BYTE_LENGTH +BATTPERCENTAGE_LENGTH, MAC_BYTE_LENGTH ,gwHbPackageStruct->routerMacBytes );
	gwHbPackageStruct->isBusy = *(gwHbCore +CMD_LENGTH +UUID_BYTE_LENGTH +BATTPERCENTAGE_LENGTH+ MAC_BYTE_LENGTH);

	uint8* pStart= gwHbCore +CMD_LENGTH +UUID_BYTE_LENGTH +BATTPERCENTAGE_LENGTH+ MAC_BYTE_LENGTH + BUSY_LENGTH;
	uint8* p= pStart;
	while(p - gwHbCore < gwHbCore_length && *p )
	{
		p++;
	}

	if(*p ==0 )
	{
		 uint8*  productModel= (uint8*)myMalloc(p-pStart+1  //1 is ending 0
					,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		 gwHbPackageStruct->productModel = productModel;
		 copyCharArrayIntoBuffer( pStart, p-pStart ,productModel );

		 printf("parseGwHbPackage productModel =%s\n", productModel);
	}
	else
	{
		return gwHbPackageStruct;
	}


	//下一个
	p++;
	pStart = p;
	while(p - gwHbCore < gwHbCore_length && *p )
	{
		p++;
	}

	if(*p ==0 )
	{
		 uint8* softwareVersion= (uint8*)myMalloc(p-pStart+1  //1 is ending 0
					,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		 gwHbPackageStruct->softwareVersion = softwareVersion;
		 copyCharArrayIntoBuffer( pStart, p-pStart ,softwareVersion );
		 printf("parseGwHbPackage softwareVersion =%s\n", softwareVersion);
	}
	else
	{
		return gwHbPackageStruct;
	}

	//下一个
	p++;
	pStart = p;
	while(p - gwHbCore < gwHbCore_length && *p )
	{
		p++;
	}

	if(*p ==0 )
	{
		 uint8* hardwareVersion= (uint8*)myMalloc(p-pStart+1  //1 is ending 0
					,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		 gwHbPackageStruct->hardwareVersion = hardwareVersion;
		 copyCharArrayIntoBuffer( pStart, p-pStart , hardwareVersion );
		 printf("parseGwHbPackage hardwareVersion =%s\n", hardwareVersion);
	}
	else
	{
		return gwHbPackageStruct;
	}

	return gwHbPackageStruct;
}

uint8* parseHb(uint8* shortPW, uint8* hbPackage, uint16 hbPackage_length)
{
	if(hbPackage_length < FLOWNO_BYTE_LENGTH + MAC_BYTE_LENGTH )
	{
		return NULL;//太短
	}

	uint16 decryptSize =0;
	uchar* decode = blowfishDec(shortPW, hbPackage +FLOWNO_BYTE_LENGTH + MAC_BYTE_LENGTH ,
			hbPackage_length -(FLOWNO_BYTE_LENGTH + MAC_BYTE_LENGTH) , &decryptSize);

	if(decode == NULL || decryptSize < CMD_LENGTH)
	{//blowfish解密失败
		return NULL;
	}

	//0 is same; 1 is different;  2 is same without capital cared
	uint8 compare = chararrayCompare( hbPackage + FLOWNO_BYTE_LENGTH,  MAC_BYTE_LENGTH, decode+CMD_LENGTH,  MAC_BYTE_LENGTH, 0);
	if( compare !=0 )
	{//blowfish解密失败，因为密码不正确，得到了错误的数据。所以mac匹配不上。
		return NULL;
	}

	if(*decode == CMD_GW_HB)
	{
		printf("ready to parseGwHbPackage");
		return parseGwHbPackage( shortPW,  hbPackage,  hbPackage_length,  decode,  decryptSize);
	}
//	else if(*decode == CMD_ETAG_HB)
//	{
//printf("ready to parseEtagHbPackage");
//	}
	return NULL;

}
