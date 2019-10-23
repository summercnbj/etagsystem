/*
 * testGwHb.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#include "gwWifiHb.h"
#include "serverParseHb.h"

void testGwHb_andParse()
{
	uint8* shortPW = "123456";
	copyCharArrayIntoBuffer(shortPW,SHORTPW_LENGTH,getShortPW());
	uint8 macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
	copyCharArrayIntoBuffer(macBytes,MAC_BYTE_LENGTH,getWifiMacBytes());

	uint8* uuidBytes = formUuidBytes( macBytes);
//	uint8 uuidBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33
//			,0,0,0,0,0,0  ,0,0,0,0,0,0 ,0,0,0,0,0,0 ,0,0,0,0,0,0 ,0,0,0,0,0,0 ,0,0,0,0,0,0 };
//	printf("=%d\n",uuidBytes[2]);
	uint8 battPercentage = 39;
	setGwBattPercentage(battPercentage);
	uint8 rootMacBytes[MAC_BYTE_LENGTH] = {0x12,0x34,0x56,0x78,0x9a,0xbc};
	copyCharArrayIntoBuffer(rootMacBytes,MAC_BYTE_LENGTH,getRootMacBytes());
	itr_bool isBusy =0;
//	uint8* productModel = "et-1099";
//	uint8*softwareVersion = "66.77";
	uint8*hardwareVersion = "88.99";
	uint8* productModel = NULL;
	uint8*softwareVersion = NULL;
//	uint8*hardwareVersion = NULL;

	copyStringIntoBufferWithLimit(productModel,getGwProductModel(),PRODUCTMODEL_LENGTH_MAX+1);
	copyStringIntoBufferWithLimit(softwareVersion,getGwSoftwareVersion(),SOFTWAREVERSION_LENGTH_MAX+1);
	copyStringIntoBufferWithLimit(hardwareVersion,getGwHardwareVersion(),HARDWAREVERSION_LENGTH_MAX+1);

	uint16 package_length =0;
	uint8* package = getGwHbPackage( &package_length);

	myPrintf("package_length = %d\n", package_length);



	ParseHbResult* hb = parseHb( shortPW,  package, package_length);
	myFree(package);
	if(hb == NULL)
	{//parse lose
		return;
	}

	if(HB_TYPE_from_GW == hb->type)
	{
		if( hb->length >= sizeof(GwHbPackage))
		{
			GwHbPackage* gwHbPackage = hb->package;
			printGwHbPackage(gwHbPackage);
		}
	}
	else if(HB_TYPE_from_ETAG == hb->type)
	{
		if( hb->length >= sizeof(EtagHbPackage))
		{
			EtagHbPackage* etagHbPackage = hb->package;
//			printGwHbPackage_struct(gwHbPackage);
		}
	}

}


#include "serverGwHbFeedback.h"
#include "gwWifiParseHbFeedback.h"
void testGwHbFeedbackState_andParse()
{
	uint8* shortPW = "123456";
	uint16 flowNo = 22855;
	uint8 macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
	uint8 gwState = GW_State_Initial_NotLocated;

	uint16 package_length =0;
	uint8* feedbackState = getGwHbFeedbackStatePackage(shortPW,  flowNo, macBytes, gwState,&package_length);

	parseHbFeedback( shortPW,  feedbackState,  package_length,  macBytes);
	myFree(feedbackState);
}

void testGwHbFeedbackNewShortPW_andParse()
{
	uint8* shortPW = "123456";
	uint16 flowNo = 22855;
	uint8 macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
	uint8* newShortPW = "888888";

	uint16 package_length =0;
	uint8*package = getGwHbFeedbackNewShortPWPackage( shortPW, flowNo,  macBytes,  newShortPW, &package_length);


	parseHbFeedback( shortPW,  package,  package_length,  macBytes);
	myFree(package);
}


#if 0
int main()
{

	testGwHb_andParse();
//	testGwHbFeedbackState_andParse();

//	testGwHbFeedbackNewShortPW_andParse();
}
#endif
