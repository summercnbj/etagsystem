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

#include "gwWifiParseHbFeedback.h"
#include "serverPixeldata.h"
void testEtagHbFeedbackState_andParse()
{
	uint8* shortPW = "123456";
	uint16 flowNo = 22855;
	uint8 wifiMacBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};

	uint8 etagMacBytes[UUID_BYTE_LENGTH] = {0xaa,0xbb,0xcc,0x11,0x22,0x33};
//	uint8 etagState = Etag_State_Illegal;
	uint8 etagState = Etag_State_Online_ProductBound_New_Pixeldata;

	uint8 md5_16_bytes[MD5_16_BYTE_LENGTH] = {0x88,0x77,0x66,0x55,0x44,0x33,0x22,0x11};


	uint16 horizontal = 1024;
	uint16 vertical=740;
	uint8 driver_type = DRIVER_TYPE_by_VERTICAL;
	char backcolor = CHAR_COLOR_WHITE;
	char forecolor1 = CHAR_COLOR_BLACK;
	char forecolor2 = CHAR_COLOR_RED;
	uint32 pixeldata_size = getSizeOfSingleAreaPixeldata(horizontal,  vertical,  driver_type);
	uint8 pixeldata[pixeldata_size];


#define TO_SEE_COMPRESSED_CONTENT 1
#if TO_SEE_COMPRESSED_CONTENT
		//to see the content
		uint32 i =0;
		for(i=0;i<pixeldata_size;i++)
		{
			uint8 c = i & 0xff;
			if( c < '!')
			{
				c = '!';
			}
			else if( c > '}')
			{
				c = '}';
			}
			*(pixeldata + i) = c;//test data
		}
#endif

	uint32 FFCS_length =0;
	uint8* ffcs = formFFCS( horizontal,  vertical,  driver_type, pixeldata,
			 backcolor, forecolor1, forecolor2, &FFCS_length);


	uint32 package_length =0;
	uint8* feedbackState = getEtagHbFeedbackStatePackage(shortPW,  flowNo, wifiMacBytes, etagMacBytes, etagState, md5_16_bytes,ffcs ,FFCS_length ,&package_length);

	parseHbFeedback( shortPW,  feedbackState,  package_length,  wifiMacBytes);
	myFree(feedbackState);
}


#if 1
int main()
{

//	testEtagHbAdv_andParse();
	testEtagHbFeedbackState_andParse();

}
#endif
