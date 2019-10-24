/*
 * testEtagHb.c
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */


#include "etagBleAdv.h"
#include "gwBleScanAndConnect.h"
#include "serverEtagHbFeedback.h"

void testEtagHbAdv_andParse()
{
	uint8* shortPW = "123456";
	uint8* productModel = "ET-1199";
	uint8*softwareVersion = "0.04";
	uint8* hardwareVersion = "66.00";

	uint8 battPercentage =99;
	uint8 md5_16_bytes[MD5_16_BYTE_LENGTH] = {0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18};
	uint8 buffer[TAG_HB_ADV_LENGTH];
	uint16 buffer_length =TAG_HB_ADV_LENGTH;

	genAdvIntoBuffer( shortPW, productModel, softwareVersion, hardwareVersion,
			 battPercentage,  md5_16_bytes,  buffer,  buffer_length);

	uint8 peripheralMacBytes[MAC_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
	masterParseBleAdvPackage( buffer, TAG_HB_ADV_LENGTH,  shortPW, peripheralMacBytes);

}

void testEtagHbFeedbackState_andParse()
{
	uint8* shortPW = "123456";
	uint16 flowNo = 22855;
	uint8 macBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
	uint8 etagState = Etag_State_Illegal;


	uint16 md5_and_CTPE_length = 200;
	uint8 md5_and_CTPE[md5_and_CTPE_length];


	uint16 package_length =0;
	uint8* feedbackState = getEtagHbFeedbackStatePackage(shortPW,  flowNo, macBytes, etagState,md5_and_CTPE, md5_and_CTPE_length,&package_length);

	parseHbFeedback( shortPW,  feedbackState,  package_length,  macBytes);
	myFree(feedbackState);
}


#if 0
int main()
{

//	testEtagHbAdv_andParse();
	testEtagHbFeedbackState_andParse();

}
#endif
