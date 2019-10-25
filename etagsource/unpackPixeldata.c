/*
 * unpackPixeldata.c
 *
 *  Created on: 2019年10月24日
 *      Author: summer
 */


#include "unpackPixeldata.h"


//~~~~~~~~~~~~~~~~~~~~~~~解析所有的{header}:SAP header or SSP header~~~~~~~~~~~~~~~~~~~~~~~~~~

//{0,0,295,127,w,r,1,4736} or  {0,0,295,127,w,r,1,4736,0,4088} 解析成结构体
//返回malloc。用完要myFree()
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
				long digit = atol(b);
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
	myPrintf("formatterStart= 0x%x\n\n", formatter->formatterStart );
}

void printETAG_abstract(ETAG_abstract* abstract)
{
	if( abstract == NULL)
	{
		myPrintf("printETAG_abstract abstract is NULL\n");
		return;
	}
	myPrintf("etagLength= %d\n", abstract->etagLength );

	myPrintf("horizontal= %ld\n", abstract->horizontal );
	myPrintf("vertical= %ld\n", abstract->vertical );
	myPrintf("colors= %s\n\n", abstract->colors );
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
		structFormatter -> formatterStart = p;
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
			long digit = atol(b);
			if(0 == counter)
			{
				long digit = atol(b);
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

	if(structFormatter == NULL)
	{
		//缺少开始的 '['
		return NULL;
	}
	else
	{
		if(finish)
		{
			structFormatter->formatterLength = p- formatter +1;
			return structFormatter;//成功
		}
		else
		{
			//缺少结束的 ']'
			freeFCSSP_Formatter(structFormatter);
			return NULL;
		}
	}
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




#if 1

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
		myPrintf("number %ld formatterStart= %s\n",number, fFormatter->formatterStart);
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
