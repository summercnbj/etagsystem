/*
 * unpackPixeldata.c
 *
 *  Created on: 2019年10月24日
 *      Author: summer
 */


#include "unpackPixeldata.h"


//~~~~~~~~~~~~~~~~~~~~~~~解析所有的{header}:SAP header or SSP header~~~~~~~~~~~~~~~~~~~~~~~~~~

/* 返回malloc。用完要myFree()
 * 适用于 SSPheader 例子   {0,0,295,127,w,r,1,4736,0,4088}   or
 *     SAPheader 例子   {0,0,295,127,w,r,1,4736}  or
 *     SAFSheader例子   {0,0,295,127,w,r,1,4736,2},{0,0,1023,739,w,b,1,95232,24}
 */
uint8* parseBracketHeader(uint8* header, uint32 header_length)
{
	if(header == NULL || header_length ==0)
	{
		return NULL;
	}
	BracketHeader * bracketheader = NULL;

#define UNPACKFCSAP_BUFFER_LENGTH 10
	uint8 buf[UNPACKFCSAP_BUFFER_LENGTH];
	uint8* b ;
	uint8 counter =0;

	uint8 finish =0;
	uint8* p = header;
	while( p-header < header_length)
	{
		if( *p == '{')
		{
			bracketheader = (BracketHeader*)myMalloc(sizeof(BracketHeader),_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);

			if(bracketheader == NULL)
			{
				return NULL;
			}
			counter =0;
			b= buf;
			memset(b,0,UNPACKFCSAP_BUFFER_LENGTH);
		}
		else if( *p == ',' || *p == '}')
		{
			if(0 == counter)
			{
				long long digit = atoll(b);
				if(bracketheader == NULL)
				{//没有开头的 '{'
					return NULL;
				}
				else
				bracketheader->lefttopHorizontal = digit;
			}
			else if(1 == counter)
			{
				long long digit = atoll(b);
				if(bracketheader == NULL)
				{//没有开头的 '{'
					return NULL;
				}
				else
				bracketheader->lefttopVertical = digit;
			}
			else if(4 == counter)
			{
				if(bracketheader == NULL)
				{//没有开头的 '{'
					return NULL;
				}
				else
				bracketheader->backcolor = *b;
			}
			else if(5 == counter)
			{
				if(bracketheader == NULL)
				{//没有开头的 '{'
					return NULL;
				}
				else
				bracketheader->forecolor = *b;
			}
			else
			{
				long long digit = atoll(b);
				if(2 == counter)
				{
					if(bracketheader == NULL)
					{//没有开头的 '{'
						return NULL;
					}
					else
					bracketheader->rightbuttonHorizontal = digit;
				}
				else if(3 == counter)
				{
					if(bracketheader == NULL)
					{//没有开头的 '{'
						return NULL;
					}
					else
					bracketheader->rightbuttonVertical = digit;
				}
				else if(6 == counter)
				{
					if(bracketheader == NULL)
					{//没有开头的 '{'
						return NULL;
					}
					else
					bracketheader->driver_type = digit;
				}
				else if(7 == counter)
				{
					if(bracketheader == NULL)
					{//没有开头的 '{'
						return NULL;
					}
					else
					bracketheader->pixeldataSize = digit;
				}
				else if(8 == counter)
				{
					if(bracketheader == NULL)
					{//没有开头的 '{'
						return NULL;
					}
					else
					bracketheader->number = digit;
				}
				else if(9 == counter)
				{
					if(bracketheader == NULL)
					{//没有开头的 '{'
						return NULL;
					}
					else
					bracketheader->sliceLen = digit;
				}
			}

			//next
			b= buf;
			memset(b,0,UNPACKFCSAP_BUFFER_LENGTH);
			counter ++;
			if( *p == '}')
			{
//				finish =1;
//				break;//finish quit
				bracketheader->headerLength = p- header +1;
				return (uint8*)bracketheader;
			}
		}
		else
		{
			strcatChar(b,*p);
		}

		p++;
	}

	if(bracketheader == NULL)
	{
		//缺少开始的 '{'
		return NULL;
	}
	else
	{
		if(finish)
		{//成功
//			bracketheader->headerLength = p- header +1;
//			return bracketheader;
		}
		else
		{
			//缺少结束的 '}'
			myFree(bracketheader);
			return NULL;
		}
	}
	return NULL;
}

SSPheader* parseSSPheader(uint8* header, uint32 header_length)
{
	return  (SSPheader*)parseBracketHeader( header,  header_length);
}

SAPheader* parseSAPheader(uint8* header, uint32 header_length)
{
	return  (SAPheader*)parseBracketHeader( header,  header_length);
}

SAFSheader* parseSAFSheader(uint8* header, uint32 header_length)
{
	return  (SAFSheader*)parseBracketHeader( header,  header_length);
}


#if defined _itrackerDebug_
/*
 * 适用于 SSPheader 例子   {0,0,295,127,w,r,1,4736,0,4088}   or
 *     SAPheader 例子   {0,0,295,127,w,r,1,4736}  or
 *     SAFSheader例子   {0,0,295,127,w,r,1,4736,2},{0,0,1023,739,w,b,1,95232,24}
 */
void printBracketHeader(BracketHeader* header)
{
	uint8* functionname = "printBracketHeader";
	myPrintf("[%s]:\n",functionname);
	if( header == NULL)
	{
		myPrintf("[%s] header is NULL\n",functionname);
		return;
	}
	myPrintf("headerLength= %d\n", header->headerLength );
	myPrintf("lefttopHorizontal= %ld\n", header->lefttopHorizontal );
	myPrintf("lefttopVertical= %ld\n", header->lefttopVertical );

	myPrintf("rightbuttonHorizontal= %ld\n", header->rightbuttonHorizontal );
	myPrintf("rightbuttonVertical= %ld\n", header->rightbuttonVertical );

	myPrintf("backcolor= %c\n", header->backcolor );
	myPrintf("forecolor= %c\n", header->forecolor );
	myPrintf("driver_type= %d\n", header->driver_type );
	myPrintf("pixeldataSize= %ld\n", header->pixeldataSize );

	myPrintf("number= %lld\n", header->number );
	myPrintf("piecelen= %ld\n\n", header->sliceLen );
}

void printSSPheader(SSPheader* header)
{
	uint8* functionname = "printSSPheader";
	myPrintf("[%s]:\n",functionname);
	if( header == NULL)
	{
		myPrintf("[%s] header is NULL\n",functionname);
		return;
	}
	myPrintf("headerLength= %d\n", header->headerLength );
	myPrintf("lefttopHorizontal= %ld\n", header->lefttopHorizontal );
	myPrintf("lefttopVertical= %ld\n", header->lefttopVertical );

	myPrintf("rightbuttonHorizontal= %ld\n", header->rightbuttonHorizontal );
	myPrintf("rightbuttonVertical= %ld\n", header->rightbuttonVertical );

	myPrintf("backcolor= %c\n", header->backcolor );
	myPrintf("forecolor= %c\n", header->forecolor );
	myPrintf("driver_type= %d\n", header->driver_type );
	myPrintf("pixeldataSize= %ld\n", header->pixeldataSize );

	myPrintf("number= %lld\n", header->number );
	myPrintf("piecelen= %ld\n\n", header->sliceLen );
}


void printSAPheader(SAPheader* header)
{
	uint8* functionname = "printSAPheader";
	myPrintf("[%s]:\n",functionname);
	if( header == NULL)
	{
		myPrintf("[%s] header is NULL\n",functionname);
		return;
	}
	myPrintf("headerLength= %d\n", header->headerLength );
	myPrintf("lefttopHorizontal= %ld\n", header->lefttopHorizontal );
	myPrintf("lefttopVertical= %ld\n", header->lefttopVertical );

	myPrintf("rightbuttonHorizontal= %ld\n", header->rightbuttonHorizontal );
	myPrintf("rightbuttonVertical= %ld\n", header->rightbuttonVertical );

	myPrintf("backcolor= %c\n", header->backcolor );
	myPrintf("forecolor= %c\n", header->forecolor );
	myPrintf("driver_type= %d\n", header->driver_type );
	myPrintf("pixeldataSize= %ld\n", header->pixeldataSize );
}


//SAFS header例子{0,0,295,127,w,r,1,4736,2},{0,0,1023,739,w,b,1,95232,24}
void printSAFSheader(SAFSheader* header)
{
	uint8* functionname = "printSAFSheader";
	myPrintf("[%s]:\n",functionname);
	if( header == NULL)
	{
		myPrintf("[%s] header is NULL\n",functionname);
		return;
	}
	myPrintf("headerLength= %d\n", header->headerLength );

	myPrintf("lefttopHorizontal= %lld\n", header->lefttopHorizontal );
	myPrintf("lefttopVertical= %lld\n", header->lefttopVertical );
	myPrintf("rightbuttonHorizontal= %lld\n", header->rightbuttonHorizontal );
	myPrintf("rightbuttonVertical= %lld\n", header->rightbuttonVertical );

	myPrintf("backcolor= %c\n", header->backcolor );
	myPrintf("forecolor= %c\n", header->forecolor );
	myPrintf("driver_type= %d\n", header->driver_type );
	myPrintf("pixeldataSize= %lld\n", header->pixeldataSize );

	myPrintf("totalSlices= %lld\n", header->totalSlices );
}

void printFCSSPformatter(FCSSPformatter* formatter)
{
	uint8* functionname = "printFCSSPformatter";
	myPrintf("[%s]:\n",functionname);
	if( formatter == NULL)
	{
		myPrintf("[%s] formatter is NULL\n",functionname);
		return;
	}
	myPrintf("formatterLength= %d\n", formatter->formatterLength );

	myPrintf("csspLength= %ld\n", formatter->csspLength );
	myPrintf("compressor= %s\n", formatter->compressor );
	myPrintf("fcsspPointer= %s\n", formatter->fcsspPointer );
	myPrintf("csspPointer= 0x%x\n\n", formatter->csspPointer );

}


/*
 * FFCS = ABSTRACT + SAFS1 + SAFS2
 *     ABSTRACT例子[296,128,wbr]
 * SAFS = SAP header + FCSSPs
 *     SAP header例子{0,0,295,127,w,r,1,4736}
 * FCSSP = FCSSP Formatter + CSSP(压缩二进制)
 *     FCSSP Formatter例子[560,zlib1.2]
 *
 * CSSP二进制 由 SSP压缩转化而来
 *
 * SSP = SSP header + 分片pixeldata
 *     SSP header例子{0,0,1023,739,w,r,1,95232,22,4092}第22条数据。(从0条开始计数)
 */

void printFFCSdetails(FFCSdetails * details)
{
	uint8* functionname = "printFFCSdetails";
	myPrintf("[%s]:\n",functionname);
	if( details == NULL)
	{
		myPrintf("[%s] ffcs is NULL\n",functionname);
		return;
	}
	printETAGabstract(details->etagAbstract );

#include "etagBleParse.h"
	uint8 SSPbuffer[SSP_LENGTH_MAX];//解压缩看看是否成功！！
	uint32 SSPbuffer_len;


	printSAFSheader(details->SAFSheader0 );
	myPrintf("fcsspFormaters0_qty= %d\n", details->fcsspFormaters0_qty );

	uint16 i;
	for(i=0;i< details->fcsspFormaters0_qty;i++)
	{
		myPrintf("printFFCSdetails NO.0 FCSSP %lld of %lld:\n", i+1, details->fcsspFormaters0_qty);
		printFCSSPformatter((details->fcsspFormaters0)[i]);
	}

	printSAFSheader(details->SAFSheader1 );
	myPrintf("fcsspFormaters1_qty= %d\n", details->fcsspFormaters1_qty );

	for(i=0;i< details->fcsspFormaters1_qty;i++)
	{
		myPrintf("printFFCSdetails NO.1 FCSSP %lld of %lld:\n", i+1, details->fcsspFormaters1_qty);
		printFCSSPformatter((details->fcsspFormaters1)[i]);

		//解压CSSP到SSP 并打印slicePixeldata
		SSPbuffer_len = SSP_LENGTH_MAX;
		memset(SSPbuffer,0,SSPbuffer_len);
		int result = uncompress (SSPbuffer, &SSPbuffer_len, (details->fcsspFormaters1)[i]->csspPointer, (details->fcsspFormaters1)[i]->csspLength);
		myPrintf("result=%d, SSPbuffer_len=%lld, SSPbuffer=%s\n",result, SSPbuffer_len, SSPbuffer);

		SSPheader* sspHeader = parseSSP( SSPbuffer,  SSPbuffer_len);
		myPrintf("slicePixeldata len=%lld, slicePixeldata=%s\n", strlen(SSPbuffer+sspHeader->headerLength), SSPbuffer+sspHeader->headerLength);
	}
}

#endif


void freeBracketHeader(BracketHeader* header)
{
	myFree(header);
}
void freeSSPheader(SSPheader* header)
{
	myFree(header);
}
void freeSAPheader(SAPheader* header)
{
	myFree(header);
}
void freeSAFSheader(SAFSheader* header)
{
	myFree(header);
}
void freeFCSSPformatter(FCSSPformatter* structFormatter)
{
	if(structFormatter)
	{
		myFree(structFormatter->compressor);
		myFree(structFormatter);
	}
}

void freeFFCSdetails(FFCSdetails* details)
{

	uint8* functionname = "freeFFCSdetails";
	myPrintf("[%s]:\n",functionname);
	if( details == NULL)
	{
		myPrintf("[%s] ffcs is NULL\n",functionname);
		return;
	}
	freeETAGabstract(details->etagAbstract );

	freeSAFSheader(details->SAFSheader0 );

	uint16 i;
	for(i=0;i< details->fcsspFormaters0_qty;i++)
	{
		freeFCSSPformatter((details->fcsspFormaters0)[i]);
	}
	myFree(details->fcsspFormaters0);

	freeSAFSheader(details->SAFSheader1 );

	for(i=0;i< details->fcsspFormaters1_qty;i++)
	{
		freeFCSSPformatter((details->fcsspFormaters1)[i]);
	}
	myFree(details->fcsspFormaters1);

	myFree(details);
}





/*
 * 解析FCSSP中的formatter到结构体
 * 将[560,zlib1.2]byte0~byte559中的[560,zlib1.2]解析成结构体.其中的560是CSSP长度，压缩结果的字节串。
 */
FCSSPformatter* parseFCSSPformatter(uint8* formatter, uint32 formatter_length)
{

	if(formatter == NULL || formatter_length < 2 )//"[]"
	{
		return NULL;
	}

	uint8 finish =0;
	FCSSPformatter * structFormatter = NULL;

#define UNPACKFCSAP_BUFFER_LENGTH 10
	uint8 buf[UNPACKFCSAP_BUFFER_LENGTH];
	uint8* b ;
	uint8 counter =0;

	uint8* p = formatter;
	if( *p == '[')
	{
		structFormatter = (FCSSPformatter*)myMalloc(sizeof(FCSSPformatter),_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
		if(structFormatter == NULL)
		{
			return NULL;
		}
		counter =0;
		b= buf;
		memset(b,0,UNPACKFCSAP_BUFFER_LENGTH);
	}
	else
	{
		return NULL;//first char is NOT '['
	}
	p++;

	while( p-formatter < formatter_length)
	{
		if( *p == ',' || *p == ']')
		{
			if(0 == counter)
			{
				long long digit = atoll(b);
				if(structFormatter == NULL)
				{//缺少开始的 '['
					return NULL;
				}
				else
					structFormatter->csspLength = digit;
			}
			else if(1 == counter)
			{
				if(structFormatter == NULL)
				{//缺少开始的 '['
					return NULL;
				}
				else
					structFormatter->compressor = copyCharArray(b,strlen(b)+1);
			}
			else if(2 == counter)
			{//error
			}

			//next
			b= buf;
			memset(b,0,UNPACKFCSAP_BUFFER_LENGTH);
			counter ++;
			if( *p == ']')
			{
//				finish =1;
				p++;
				structFormatter->fcsspPointer = formatter;
				structFormatter->csspPointer = p;
				structFormatter->formatterLength = p- formatter;
				return structFormatter;//成功
//				break;//finish quit
			}
		}
		else
		{
			strcatChar(b,*p);
		}
		p++;
	}

	if(structFormatter == NULL)
	{
		//缺少开始的 '['
		return NULL;
	}
	else
	{
		if(finish)
		{
//			structFormatter->formatterLength = p- formatter;
//			return structFormatter;//成功
		}
		else
		{
			//缺少结束的 ']'
			freeFCSSPformatter(structFormatter);
			return NULL;
		}
	}
	return NULL;
}




/*
 * 从FCSSPs串中得到第number个FCSSP的结构体描述。用完要myFree()
 * 从[560,zlib1.2]byte0~byte559[89,zlib1.2]byte0~byte88多个FCSSP中获取到第number个FCSSP
 *
 * FCSSP0FCSSP1FCSSP2FCSSP3......  得到其中的第几个FCSSP的结构体描述
 */
FCSSPformatter* getNumberFCSSP(uint8* fcssps,uint32 fcssps_length, uint32 number)
{
	uint8* p = fcssps;
	uint32 length = fcssps_length;
	FCSSPformatter*formatter = NULL;

	uint32 i=0;
	while( p-fcssps < fcssps_length)
	{
		formatter = parseFCSSPformatter( p, length);
		if(formatter == NULL)
		{
			return NULL;//error data or broken data
		}
		if(i == number)
		{
			return formatter;
		}

		//next
		i++;
		p += length + formatter->csspLength;
	}

	return NULL;
}

/*
总结：最后给FFCS计算MD5_16 16HEX转化为8bytes
 FFCS = ABSTRACT + SAFS0 + SAFS1
   = ABSTRACT + (SAFS header + FCSSPs) + (SAFS header + FCSSPs)
   = ABSTRACT + (SAFS header + 多个(FCSSP Formatter + CSSP(压缩二进制)))
              + (SAFS header + 多个(FCSSP Formatter + CSSP(压缩二进制)))
               其中ABSTRACT例子[296,128,wbr]
 SAFS = SAFS header + FCSSPs
              其中SAFS header例子{0,0,295,127,w,r,1,4736,2},{0,0,1023,739,w,b,1,95232,24}
 FCSSP = FCSSP Formatter + CSSP(压缩二进制)
             其中FCSSP Formatter例子[560,zlib1.2]

 CSSP二进制 由 SSP压缩转化而来。

 SSP = SSP header + 分片点阵数据(pixeldata slice)
             其中SSP header例子{0,0,1023,739,w,r,1,95232,22,4092}第22条数据长度4092字节。(从0条开始计数)
 */
FFCSdetails* parseFFCS(uint8* ffcs, uint32 ffcs_length)
{
	if(ffcs == NULL)
	{
		return NULL;
	}
	FFCSdetails* details = (FFCSdetails*)myMalloc(sizeof(FFCSdetails),_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
	if(details == NULL)
	{
		myPrintf("parseFFCS malloc FFCSdetails fail.");
		return NULL;
	}

	ETAGabstract* abstract = parseETAG_abstract( ffcs, ffcs_length);
#if defined _itrackerDebug_
	printETAGabstract(abstract);
#endif
	if(abstract  ==NULL)
	{
		myPrintf("parseFFCS parseETAG_abstract fail.");
		return NULL;
	}

	details->etagAbstract = abstract;


	SAFSheader* safsHeader = NULL;
	uint8* p = ffcs + abstract->abstractLength;//指向第一个
	uint32 remaining_len = ffcs_length - abstract->abstractLength;
	uint32 i;
	if(remaining_len >0)
	{
		safsHeader = parseSAFSheader(p, remaining_len);
#if defined _itrackerDebug_
		printSAFSheader(safsHeader);
#endif
		if(safsHeader  ==NULL)
		{
			myPrintf("parseFFCS No.0 parseSAFSheader fail.");
			return NULL;
		}

		details->SAFSheader0 = safsHeader;
		details->fcsspFormaters0_qty = safsHeader->totalSlices;

		details->fcsspFormaters0 = (FCSSPformatter**)myMalloc(sizeof(FCSSPformatter*)*details->fcsspFormaters0_qty,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
		if(abstract  ==NULL)
		{
			myPrintf("parseFFCS No.0 malloc %d pices of FCSSPformatter* fail.", details->fcsspFormaters0_qty);
			return NULL;
		}

		p += safsHeader->headerLength;
		remaining_len -= safsHeader->headerLength;
		for(i=0; i<details->fcsspFormaters0_qty ;i++)
		{
			(details->fcsspFormaters0)[i] = parseFCSSPformatter(p,remaining_len);
			if(safsHeader  ==NULL)
			{
				myPrintf("parseFFCS No.0 parseFCSSPformatter fail.");
				return NULL;
			}

#if defined _itrackerDebug_
			myPrintf("printFFCSdetails NO.0 FCSSP %lld of %lld:\n", i+1, details->fcsspFormaters0_qty);
			printFCSSPformatter((details->fcsspFormaters0)[i]);
#endif

			//to next
			p += (details->fcsspFormaters0)[i]->formatterLength + (details->fcsspFormaters0)[i]->csspLength ;
			remaining_len -= (details->fcsspFormaters0)[i]->formatterLength + (details->fcsspFormaters0)[i]->csspLength ;
		}
	}

	if(remaining_len >0)
	{
		safsHeader = parseSAFSheader(p, remaining_len);
#if defined _itrackerDebug_
		printSAFSheader(safsHeader);
#endif
		if(safsHeader  ==NULL)
		{
			myPrintf("parseFFCS No.1 parseSAFSheader fail.");
			return NULL;
		}

		details->SAFSheader1 = safsHeader;
		details->fcsspFormaters1_qty = safsHeader->totalSlices;

		details->fcsspFormaters1 = (FCSSPformatter**)myMalloc(sizeof(FCSSPformatter*)*details->fcsspFormaters1_qty,_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
		if(abstract  ==NULL)
		{
			myPrintf("parseFFCS No.1 malloc %d pices of FCSSPformatter* fail.", details->fcsspFormaters1_qty);
			return NULL;
		}

		p += safsHeader->headerLength;
		remaining_len -= safsHeader->headerLength;
		for(i=0; i<details->fcsspFormaters1_qty ;i++)
		{
			(details->fcsspFormaters1)[i] = parseFCSSPformatter(p,remaining_len);
			if(safsHeader  ==NULL)
			{
				myPrintf("parseFFCS No.1 parseFCSSPformatter fail.");
				return NULL;
			}

#if defined _itrackerDebug_
			myPrintf("printFFCSdetails NO.1 FCSSP %lld of %lld:\n", i+1, details->fcsspFormaters1_qty);
			printFCSSPformatter((details->fcsspFormaters1)[i]);
#endif

			//to next
			p += (details->fcsspFormaters1)[i]->formatterLength + (details->fcsspFormaters1)[i]->csspLength ;
			remaining_len -= (details->fcsspFormaters1)[i]->formatterLength + (details->fcsspFormaters1)[i]->csspLength ;
		}
	}

	return details;
}

#include "gwWifi2Uart.h"
#include "gwWifiCaches.h"
int8 sendOneFFCSdetails(uint8* etagMacBytes, uint8 etagState, uint8* md5_16_bytes, FFCSdetails* details)
{
#if defined _itrackerDebug_
	uint8* functionname = "sendOneFFCSdetails";
	myPrintf("[%s]:\n",functionname);
#endif
	if( details == NULL)
	{
#if defined _itrackerDebug_
		myPrintf("[%s] ffcs is NULL\n",functionname);
#endif
		return -1;
	}

	int8 ret =-1;
	uint32 package_length =0;
	uint8* package = NULL;
	uint16 i;
	for(i=0;i< details->fcsspFormaters0_qty;i++)
	{
		package_length =0;
		package = get_ETAG_GW_HB_FEEDBACK_STATE_ONUART( etagMacBytes, etagState, md5_16_bytes,
				(details->fcsspFormaters0)[i]->fcsspPointer, (details->fcsspFormaters0)[i]->formatterLength + (details->fcsspFormaters0)[i]->csspLength, &package_length);
		appendCache2Uart( etagMacBytes, package,package_length);
	}

	for(i=0;i< details->fcsspFormaters1_qty;i++)
	{
		package_length =0;
		package = get_ETAG_GW_HB_FEEDBACK_STATE_ONUART( etagMacBytes, etagState, md5_16_bytes,
				(details->fcsspFormaters1)[i]->fcsspPointer,(details->fcsspFormaters1)[i]->formatterLength + (details->fcsspFormaters1)[i]->csspLength, &package_length);
		appendCache2Uart( etagMacBytes, package,package_length);
	}

	return 0;
}

int8 sendOneFFCS(uint8* etagMacBytes, uint8 etagState, uint8* md5_16_bytes, uint8* ffcs, uint32 ffcs_length)
{
	FFCSdetails* details = parseFFCS( ffcs,  ffcs_length);

	int8 send = sendOneFFCSdetails(etagMacBytes, etagState, md5_16_bytes,details);

	freeFFCSdetails(details);
	return send;
}

/*
 * etagBle里调用，解析并解压缩FCSSP得到自明的SSP分片数据(带有SSPheader)
 * 将FCSSP [560,zlib1.2]byte0~byte559中的byte0~byte559解压缩到SSPbuffer里，长度返回为*SSPbuffer_len。
 */
int8 uncompressFCSSPtoSSP(uint8* fcssp, uint32 fcssp_length, uint8* SSPbuffer, uint32 *SSPbuffer_len)
{
	FCSSPformatter* formatter = parseFCSSPformatter( fcssp, fcssp_length);
	if(formatter == NULL)
	{
		return -1;
	}

	memset(SSPbuffer,0,*SSPbuffer_len);
	int result = uncompress (SSPbuffer, SSPbuffer_len, formatter->csspPointer, formatter->csspLength);
#if defined _itrackerDebug_
	myPrintf("uncompress result = %ld, uncompress into size of ssplen= %ld\n",result, *SSPbuffer_len );
	myPrintf("uncompress ssp+17 = %d\n", *(SSPbuffer + 17));
	myPrintf("uncompress into strlen of %lld, into = %s\n", strlen(SSPbuffer),SSPbuffer);
#endif
	freeFCSSPformatter(formatter);
	return result;
}


/* etagBle里调用
 * 解析SSP得到SSPheader
 * slice数据在ssp + SSPheader->headerLength，长度为 SSPheader->sliceLen。
 */
SSPheader* parseSSP(uint8* ssp, uint32 ssp_length)
{
	return  (SSPheader*)parseBracketHeader( ssp,  ssp_length);
}
