/*
 * testPixeldata.c
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */


#include "testPixeldata.h"



#include "serverPixeldata.h"
#include "unpackPixeldata.h"





#if defined _itrackerDebug_

void compresstest()
{
#define SSPLENGTH 100
	uint8 ssp[SSPLENGTH] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,
			1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20
	};

	uint8 fcssp_buffer[SSPLENGTH + 30];

	uint32 fcssp_len= SSPLENGTH + 30;
	int8 com = zlibCompressSSP2FCSSP( ssp, SSPLENGTH, fcssp_buffer, &fcssp_len);

	myPrintf("com = %d, fcssp_buffer= %s\n",com, fcssp_buffer);

}

void test_formSAP()
{
	uint16 horizontal = 1024;
	uint16 vertical= 740;
	uint8 driver_type = DRIVER_TYPE_by_VERTICAL;
	char backcolor = CHAR_COLOR_WHITE;
	char forecolor = CHAR_COLOR_BLACK;
	uint8 buffer[SSPHEADER_LENGTH_MAX];
	uint16 header_len = SSPHEADER_LENGTH_MAX;
//	int8 ret = genSAPHeader(horizontal, vertical, driver_type, backcolor,forecolor, buffer, header_len);

//	myPrintf("buffer= %s\n",buffer);

	uint32 pixeldataSize = getSizeOfSingleAreaPixeldata(horizontal, vertical, driver_type);
	uint8 pixeldata[pixeldataSize];
	//	memset(pixeldata,0,pixeldataSize);

	//to see the content
	uint32 i =0;
	for(i=0;i<pixeldataSize;i++)
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
		pixeldata[i] = c;//test data
	}


<<<<<<< HEAD
	uint32 SAP_length =0;
	uint8* sap = formSAP(horizontal, vertical, driver_type, pixeldata,  backcolor, forecolor, &SAP_length);
=======
	uint32_itr SAP_length =0;
	uint8_itr* sap = formSAP(horizontal, vertical, driver_type, pixeldata,  backcolor, forecolor, &SAP_length);
>>>>>>> cd3803a... aaaaaa
	myPrintf("sap= %s\n",sap);
	myPrintf("SAP_length= %ld\n",SAP_length);
	myFree(sap);

}


void test_formSSP()
{
	uint32 number = 3;
	uint16 horizontal = 699;//1024;
	uint16 vertical= 158;//740;
	uint8 driver_type = DRIVER_TYPE_by_VERTICAL;
	char backcolor = CHAR_COLOR_WHITE;
	char forecolor = CHAR_COLOR_BLACK;

	uint32 pixeldataSize = getSizeOfSingleAreaPixeldata(horizontal, vertical, driver_type);
	uint8 pixeldata[pixeldataSize];
	memset(pixeldata,0,pixeldataSize);
	//	memset(pixeldata,0,pixeldataSize);

	//to see the content
	uint32 i =0;
	for(i=0;i<pixeldataSize;i++)
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
		pixeldata[i] = c;//test data
	}


	uint32 SSP_length =0;
	uint8*ssp = formSSP( number, horizontal,  vertical,  driver_type, pixeldata,  backcolor, forecolor,&SSP_length);

	myPrintf("ssp= %s\n",ssp);
	myFree(ssp);
}


void test_formFCSSPs()
{
	uint16 horizontal = 1024;
	uint16 vertical=740;
	uint8 driver_type = DRIVER_TYPE_by_VERTICAL;
	char backcolor = CHAR_COLOR_WHITE;
	char forecolor = CHAR_COLOR_BLACK;

	uint32 pixeldataSize = getSizeOfSingleAreaPixeldata(horizontal, vertical, driver_type);
	uint8 pixeldata[pixeldataSize];
	//	memset(pixeldata,0,pixeldataSize);

	//to see the pixeldata
	uint32 i =0;
	for(i=0;i<pixeldataSize;i++)
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
		pixeldata[i] = c;//test data
	}


	uint32 FCSSPs_length =0;
	uint8* fcssps = formFCSSPs(horizontal, vertical, driver_type, pixeldata, backcolor,forecolor,&FCSSPs_length);

	myPrintf("fcssps= %s, SAFS_length =%ld, fcssps length=%ld\n",fcssps,FCSSPs_length,strlen(fcssps));
	myFree(fcssps);

}

uint8*  test_formSAFS_formFFCS(uint32* FFCS_length )
{
	uint16 horizontal = 1024;
	uint16 vertical=740;
	uint8 driver_type = DRIVER_TYPE_by_VERTICAL;
	char backcolor = CHAR_COLOR_WHITE;
	char forecolor = CHAR_COLOR_BLACK;

	uint32 pixeldataSize = getSizeOfSingleAreaPixeldata(horizontal, vertical, driver_type);
	uint8 pixeldata[pixeldataSize];
	//	memset(pixeldata,0,pixeldataSize);

	//to see the pixeldata
	uint32 i =0;
	for(i=0;i<pixeldataSize;i++)
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
		pixeldata[i] = c;//test data
	}

	uint32 SAFS_length =0;
	uint8* safs = formSAFS(horizontal, vertical, driver_type, pixeldata, backcolor,forecolor,&SAFS_length);

	myPrintf("SAFS_length =%lld, safs length=%ld, safs= %s\n",SAFS_length,strlen(safs),safs);
	myFree(safs);

	char forecolor2 = CHAR_COLOR_RED;
	uint8* ffcs = formFFCS(horizontal, vertical, driver_type, pixeldata,
			 backcolor, forecolor, forecolor2, FFCS_length);

	myPrintf("FFCS_length=%lld, ffcs= %s\n",*FFCS_length, ffcs);

//	myFree(ffcs);
	return ffcs;
}





void test_parseBracketheader()
{
	//{0,0,295,127,w,r,1,4736} or  {0,0,295,127,w,r,1,4736,0,4088}

	uint8* header = "{0,0,295,127,w,r,1,4736}ssssss";
//	uint8* header = "{0,0,295,127,w,r,1,4736,0,4088}xxxx";

	uint32 length =strlen(header) ;

	extern uint8* parseBracketHeader(uint8* header, uint32 header_length);
	BracketHeader* bHeader = parseBracketHeader(header, &length);
	printBracketHeader(bHeader);
	myPrintf("BracketHeader length= %ld\n",length);
}

void test_parseFCSSP_Formatter()
{
	uint8* formatter = "[560,zlib1.2]xxxxxx";
	uint32* formatter_length = strlen(formatter);
	FCSSPformatter* fFormatter = parseFCSSPformatter(formatter, &formatter_length);

	printFCSSPformatter(fFormatter);
	myPrintf("FCSSP_Formatter formatter_length= %ld\n",formatter_length);
}


void test_getNumberFCSSP()
{
	uint8* fcssps = "[36,zlib1.2]abcdefghijklmnopqrstuvwxyz1234567890[26,zlib1.2]abcdefghijklmnopqrstuvwxyz[10,zlib1.2]1234567890[1,zlib1.2]1[4,zlib1.2]1111";
	uint32 fcssps_length = strlen(fcssps);
	uint32 number = 0;
	FCSSPformatter* fFormatter = getNumberFCSSP(fcssps,fcssps_length,  number);

	printFCSSPformatter(fFormatter);
	if(fFormatter)
		myPrintf("number %ld csspPointer= %s\n",number, fFormatter->csspPointer);
}




#if 1
int main()
{
//	compresstest();

//	test_formSAP();

//	test_formSSP();

//	test_formFCSSPs();
	uint32 FFCS_length =0;
	uint8* ffcs = test_formSAFS_formFFCS(&FFCS_length);


//	test_parseBracketheader();
//	test_parseFCSSP_Formatter();
//	test_getNumberFCSSP();

	FFCSdetails* details = parseFFCS( ffcs, FFCS_length);
	printFFCSdetails( details);
	return 0;
}
#endif
#endif
