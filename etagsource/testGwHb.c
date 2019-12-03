/*
 * testGwHb.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

<<<<<<< HEAD
#include "gwWifiHb.h"
#include "serverParseHb.h"
#include "gwWifiDriver.h"
=======
#include "include/Cetagsource/gwWifiHb.h"
#include "include/Cetagsource/serverParseHb.h"
#include "include/Cetagsource/gwWifiDriver.h"
<<<<<<< HEAD
>>>>>>> cd3803a... aaaaaa

=======
>>>>>>> c1497af... a

<<<<<<< HEAD
void testGwHb_andParse()
{
	uint8* shortPW = "123456";
	copyCharArrayIntoBuffer(shortPW,SHORTPW_LENGTH,getWifiShortPW());
	uint8 macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
=======

uint8_itr* getTestPackagOfGwHb( uint8_itr* shortPW, uint32_itr *package_length)
{
<<<<<<< HEAD
#if defined _itrackerDebug_
	myPrintf("[getTestPackagOfGwHb] shortPW=%s\n",shortPW);
#endif
=======
>>>>>>> c1497af... a
	copyCharArrayIntoBuffer(shortPW,SHORTPW_LENGTH,getWifiShortPW());
	uint8_itr macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
>>>>>>> cd3803a... aaaaaa
	copyCharArrayIntoBuffer(macBytes,MAC_BYTE_LENGTH,getWifiMacBytes());

	uint8* uuidBytes = formUuidBytes( macBytes);
//	uint8 uuidBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33
//			,0,0,0,0,0,0  ,0,0,0,0,0,0 ,0,0,0,0,0,0 ,0,0,0,0,0,0 ,0,0,0,0,0,0 ,0,0,0,0,0,0 };
//	printf("=%d\n",uuidBytes[2]);
<<<<<<< HEAD
	uint8 battPercentage = 39;
=======
	uint8_itr battPercentage = 39;
>>>>>>> cd3803a... aaaaaa
	setGwBattPercentage(battPercentage);
	uint8 rootMacBytes[MAC_BYTE_LENGTH] = {0x12,0x34,0x56,0x78,0x9a,0xbc};
	copyCharArrayIntoBuffer(rootMacBytes,MAC_BYTE_LENGTH,getRootMacBytes());
	itr_bool isBusy =0;
<<<<<<< HEAD
//	uint8* productModel = "et-1099";
//	uint8*softwareVersion = "66.77";
	uint8*hardwareVersion = "88.99";
	uint8* productModel = NULL;
	uint8*softwareVersion = NULL;
//	uint8*hardwareVersion = NULL;
=======
//	uint8_itr* productModel = "et-1099";
//	uint8_itr*softwareVersion = "66.77";
	uint8_itr*hardwareVersion = "88.99";
	uint8_itr* productModel = NULL;
	uint8_itr*softwareVersion = NULL;
//	uint8_itr*hardwareVersion = NULL;
>>>>>>> cd3803a... aaaaaa

	copyStringIntoBufferWithLimit(productModel,getGwProductModel(),PRODUCTMODEL_LENGTH_MAX+1);
	copyStringIntoBufferWithLimit(softwareVersion,getGwSoftwareVersion(),SOFTWAREVERSION_LENGTH_MAX+1);
	copyStringIntoBufferWithLimit(hardwareVersion,getGwHardwareVersion(),HARDWAREVERSION_LENGTH_MAX+1);

<<<<<<< HEAD
	uint32 package_length =0;
	uint8* package = getGwHbPackage( &package_length);
=======
<<<<<<< HEAD
//	return NULL;
=======
>>>>>>> c1497af... a
	uint8_itr* package = getGwHbPackage( package_length);
	myPrintf("package_length = %d\n", *package_length);
	return package;
}
>>>>>>> cd3803a... aaaaaa

	myPrintf("package_length = %d\n", package_length);

<<<<<<< HEAD
=======
/**
 * c testing
 */
void testGwHb_andParse()
{
	uint8_itr* shortPW = "123456";
	uint32_itr package_length=0;
	uint8_itr*package = getTestPackagOfGwHb( shortPW,&package_length);
>>>>>>> cd3803a... aaaaaa
	parseHb2Db( shortPW,  package,  package_length);

}


#include "serverGwHbFeedback.h"
#include "gwWifiParseHbFeedback.h"
void testGwHbFeedbackState_andParse()
{
<<<<<<< HEAD
	uint8* shortPW = "123456";
	uint16 flowNo = 22855;
	uint8 macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
	uint8 gwState = GW_State_Initial_NotLocated;

	uint16 package_length =0;
	uint8* feedbackState = getGwHbFeedbackStatePackage(shortPW,  flowNo, macBytes, gwState,&package_length);
=======
	uint8_itr* shortPW = "123456";
	uint16_itr flowNo = 22855;
	uint8_itr macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
	uint8_itr gwState = GW_State_Initial_NotLocated;

	uint16_itr package_length =0;
	uint8_itr* feedbackState = getGwHbFeedbackStatePackage(shortPW,  flowNo, macBytes, gwState,&package_length);
>>>>>>> cd3803a... aaaaaa

	parseHbFeedback( shortPW,  feedbackState,  package_length,  macBytes);
	myFree(feedbackState);
}

void testGwHbFeedbackNewShortPW_andParse()
{
<<<<<<< HEAD
	uint8* shortPW = "123456";
	uint16 flowNo = 22855;
	uint8 macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
	uint8* newShortPW = "888888";

	uint16 package_length =0;
	uint8*package = getGwHbFeedbackNewShortPWPackage( shortPW, flowNo,  macBytes,  newShortPW, &package_length);
=======
	uint8_itr* shortPW = "123456";
	uint16_itr flowNo = 22855;
	uint8_itr macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
	uint8_itr* newShortPW = "888888";

	uint16_itr package_length =0;
	uint8_itr*package = getGwHbFeedbackNewShortPWPackage( shortPW, flowNo,  macBytes,  newShortPW, &package_length);
>>>>>>> cd3803a... aaaaaa


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
