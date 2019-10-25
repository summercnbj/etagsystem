/*
 * unpackPixeldata.c
 *
 *  Created on: 2019年10月24日
 *      Author: summer
 */


#include "unpackPixeldata.h"


//~~~~~~~~~~~~~~~~~~~~~~~解析所有的{header}:SAP header or SSP header~~~~~~~~~~~~~~~~~~~~~~~~~~

//返回malloc。用完要myFree()
//适用于{0,0,295,127,w,r,1,4736} SAP_header or  {0,0,295,127,w,r,1,4736,0,4088}  SSP_header 解析成结构体
BracketHeader* parseBracketHeader(uint8* header, uint32 header_length)
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
			if(0 == counter || 1 == counter)
			{
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
					bracketheader->horizontal = digit +1;
				}
				else if(3 == counter)
				{
					if(bracketheader == NULL)
					{//没有开头的 '{'
						return NULL;
					}
					else
					bracketheader->vertical = digit +1;
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
					bracketheader->piecelen = digit;
				}
			}

			//next
			b= buf;
			memset(b,0,UNPACKFCSAP_BUFFER_LENGTH);
			counter ++;
			if( *p == '}')
			{
				finish =1;
				break;//finish quit
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
			bracketheader->headerLength = p- header +1;
			return bracketheader;
		}
		else
		{
			//缺少结束的 '}'
			myFree(bracketheader);
			return NULL;
		}
	}
}


#if defined _itrackerDebug_
//适用于{0,0,295,127,w,r,1,4736} SAP_header or  {0,0,295,127,w,r,1,4736,0,4088}  SSP_header
void printBracketHeader(BracketHeader* header)
{
	if( header == NULL)
	{
		myPrintf("printBracketHeader header is NULL\n");
		return;
	}
	myPrintf("headerLength= %d\n", header->headerLength );
	myPrintf("horizontal= %ld\n", header->horizontal );
	myPrintf("vertical= %ld\n", header->vertical );
	myPrintf("backcolor= %c\n", header->backcolor );
	myPrintf("forecolor= %c\n", header->forecolor );
	myPrintf("driver_type= %d\n", header->driver_type );
	myPrintf("pixeldataSize= %ld\n", header->pixeldataSize );

	myPrintf("number= %ld\n", header->number );
	myPrintf("piecelen= %ld\n\n", header->piecelen );
}


//SAFS header例子{0,0,295,127,w,r,1,4736,2},{0,0,1023,739,w,b,1,95232,24}
void printSAFS_header(SAFS_header* header)
{
	if( header == NULL)
	{
		myPrintf("printSAFS_header header is NULL\n");
		return;
	}
	myPrintf("lefttopHorizontal= %lld\n", header->lefttopHorizontal );
	myPrintf("lefttopVertical= %lld\n", header->lefttopVertical );
	myPrintf("rightbuttonHorizontal= %lld\n", header->rightbuttonHorizontal );
	myPrintf("rightbuttonVertical= %lld\n", header->rightbuttonVertical );

	myPrintf("backcolor= %c\n", header->backcolor );
	myPrintf("forecolor= %c\n", header->forecolor );
	myPrintf("driver_type= %d\n", header->driver_type );
	myPrintf("pixeldataSize= %lld\n", header->pixeldataSize );

	myPrintf("totalSlices= %d\n", header->totalSlices );
}

void printFCSSP_Formatter(FCSSP_Formatter* formatter)
{
	if( formatter == NULL)
	{
		myPrintf("printCSSP_Formatter formatter is NULL\n");
		return;
	}
	myPrintf("formatterLength= %d\n", formatter->formatterLength );

	myPrintf("csspLength= %ld\n", formatter->csspLength );
	myPrintf("compressor= %s\n", formatter->compressor );
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

void printFFCS_Details(FFCS_Details * ffcs)
{
	if( ffcs == NULL)
	{
		myPrintf("printFFCS_Details ffcs is NULL\n");
		return;
	}
	myPrintf("etagAbstract= %s\n", ffcs->etagAbstract );
	myPrintf("SAFSheader1= %s\n", ffcs->SAFSheader1 );

	myPrintf("fcsspFormaters1_qty= %d\n", ffcs->fcsspFormaters1_qty );

	uint16 i;
	for(i=0;i< ffcs->fcsspFormaters1_qty;i++)
	{
		printFCSSP_Formatter((ffcs->fcsspFormaters1)[i]);
	}

	myPrintf("SAFSheader2= %s\n", ffcs->SAFSheader2 );
	myPrintf("fcsspFormaters2_qty= %d\n", ffcs->fcsspFormaters2_qty );
	for(i=0;i< ffcs->fcsspFormaters2_qty;i++)
	{
		printFCSSP_Formatter((ffcs->fcsspFormaters2)[i]);
	}
}

#endif

void freeFCSSP_Formatter(FCSSP_Formatter* structFormatter)
{
	if(structFormatter)
	{
		myFree(structFormatter->compressor);
		myFree(structFormatter);
	}
}
void freeETAG_abstract(ETAG_abstract* abstract)
{
	if(abstract)
	{
		myFree(abstract->colors);
		myFree(abstract);
	}
}






/*
 * 解析FCSSP中的formatter到结构体
 * 将[560,zlib1.2]byte0~byte559中的[560,zlib1.2]解析成结构体.其中的560是CSSP长度，压缩结果的字节串。
 */
FCSSP_Formatter* parseFCSSP_Formatter(uint8* formatter, uint32 formatter_length)
{

	if(formatter == NULL || formatter_length < 2 )//"[]"
	{
		return NULL;
	}

	uint8 finish =0;
	FCSSP_Formatter * structFormatter = NULL;

#define UNPACKFCSAP_BUFFER_LENGTH 10
	uint8 buf[UNPACKFCSAP_BUFFER_LENGTH];
	uint8* b ;
	uint8 counter =0;

	uint8* p = formatter;
	if( *p == '[')
	{
		structFormatter = (FCSSP_Formatter*)myMalloc(sizeof(FCSSP_Formatter),_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
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
				structFormatter -> csspPointer = p;
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
			freeFCSSP_Formatter(structFormatter);
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
FCSSP_Formatter* getNumberFCSSP(uint8* fcssps,uint32 fcssps_length, uint32 number)
{
	uint8* p = fcssps;
	uint32 length = fcssps_length;
	FCSSP_Formatter*formatter = NULL;

	uint32 i=0;
	while( p-fcssps < fcssps_length)
	{
		formatter = parseFCSSP_Formatter( p, length);
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

FFCS_Details* parseFFCS(uint8* ffcs, uint32 ffcs_length)
{
	if(ffcs == NULL)
	{
		return NULL;
	}
	ETAG_abstract* abstract = parseETAG_abstract( ffcs, ffcs_length);






}


#if 0

void test_parseBracketheader()
{
	//{0,0,295,127,w,r,1,4736} or  {0,0,295,127,w,r,1,4736,0,4088}

	uint8* header = "{0,0,295,127,w,r,1,4736}ssssss";
//	uint8* header = "{0,0,295,127,w,r,1,4736,0,4088}xxxx";

	uint32 length =strlen(header) ;
	BracketHeader* bHeader = parseBracketHeader(header, &length);
	printBracketHeader(bHeader);
	myPrintf("BracketHeader length= %ld\n",length);
}

void test_parseFCSSP_Formatter()
{
	uint8* formatter = "[560,zlib1.2]xxxxxx";
	uint32* formatter_length = strlen(formatter);
	FCSSP_Formatter* fFormatter = parseFCSSP_Formatter(formatter, &formatter_length);

	printFCSSP_Formatter(fFormatter);
	myPrintf("FCSSP_Formatter formatter_length= %ld\n",formatter_length);
}


void test_getNumberFCSSP()
{
	uint8* fcssps = "[36,zlib1.2]abcdefghijklmnopqrstuvwxyz1234567890[26,zlib1.2]abcdefghijklmnopqrstuvwxyz[10,zlib1.2]1234567890[1,zlib1.2]1[4,zlib1.2]1111";
	uint32 fcssps_length = strlen(fcssps);
	uint32 number = 0;
	FCSSP_Formatter* fFormatter = getNumberFCSSP(fcssps,fcssps_length,  number);

	printFCSSP_Formatter(fFormatter);
	if(fFormatter)
		myPrintf("number %ld csspPointer= %s\n",number, fFormatter->csspPointer);
}



int main()
{
	test_parseBracketheader();
//
//	test_parseFCSSP_Formatter();

	test_getNumberFCSSP();
	return 0;
}



#endif
