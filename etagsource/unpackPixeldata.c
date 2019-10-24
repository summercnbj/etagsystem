/*
 * unpackPixeldata.c
 *
 *  Created on: 2019年10月24日
 *      Author: summer
 */


#include "unpackPixeldata.h"




//{0,0,295,127,w,r,1,4736} or  {0,0,295,127,w,r,1,4736,0,4088}
BracketHeader* unpackBracketHeader(uint8* header, uint32 header_length)
{
	if(header == NULL || header_length ==0)
	{
		return NULL;
	}
	BracketHeader * bracketheader = (BracketHeader*)myMalloc(sizeof(BracketHeader),_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);

	if(bracketheader == NULL)
	{
		return NULL;
	}

#define UNPACKFCSAP_BUFFER_LENGTH 10
	uint8 buf[UNPACKFCSAP_BUFFER_LENGTH];
	uint8* b ;
	uint8 counter =0;

	uint8* p = header;
	while( p-header < header_length)
	{
		if( *p == '{')
		{
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
				bracketheader->backcolor = *b;
			}
			else if(5 == counter)
			{
				bracketheader->forecolor = *b;
			}
			else
			{
				int digit = atoi(b);
				if(2 == counter)
				{
					bracketheader->horizontal = digit +1;
				}
				else if(3 == counter)
				{
					bracketheader->vertical = digit +1;
				}
				else if(6 == counter)
				{
					bracketheader->driver_type = digit;
				}
				else if(7 == counter)
				{
					bracketheader->pixeldataSize = digit;
				}
				else if(8 == counter)
				{
					bracketheader->number = digit;
				}
				else if(9 == counter)
				{
					bracketheader->piecelen = digit;
				}
			}

			//next
			b= buf;
			memset(b,0,UNPACKFCSAP_BUFFER_LENGTH);
			counter ++;
			if( *p == '}')
			{
				break;//finish
			}
		}
		else
		{
			*b = *p;
		}
	}
	return bracketheader;
}


