/*
 * pixeldataCommon.c
 *
 *  Created on: 2019年10月24日
 *      Author: summer
 */


#include "pixeldataCommon.h"


//根据驱动扫描是横向还是纵向，计算SAP里的pixeldata size
uint32 getSizeOfSingleAreaPixeldata(uint32 horizontal, uint32 vertical, uint8 driver_type)
{
	if( DRIVER_TYPE_by_VERTICAL == driver_type)
	{
<<<<<<< HEAD
		uint32 ver = get_ceiling_bytes_len( vertical);
=======
		uint32_itr ver = get_ceiling_bytes_len( vertical);
>>>>>>> cd3803a... aaaaaa
		myPrintf("ver= %d\n",ver);
		return ver*horizontal;
	}
	else if( DRIVER_TYPE_by_VERTICAL == driver_type)
	{
		uint32 hor = get_ceiling_bytes_len( horizontal);
		return vertical*hor;
	}
	return 0;
}




#if defined _itrackerDebug_
void printETAGabstract(ETAGabstract* abstract)
{
	if( abstract == NULL)
	{
		myPrintf("printETAGabstract abstract is NULL\n");
		return;
	}
	myPrintf("abstractLength= %d\n", abstract->abstractLength );

	myPrintf("horizontal= %ld\n", abstract->horizontal );
	myPrintf("vertical= %ld\n", abstract->vertical );
	myPrintf("colors= %s\n\n", abstract->colors );
}
#endif

void freeETAGabstract(ETAGabstract* abstract)
{
	if(abstract)
	{
		myFree(abstract->colors);
		myFree(abstract);
	}
}

#define ETAGABSTRACT_LENGTH_MAX 20
uint8* formEtagAbstract(uint32 horizontal, uint32 vertical, char backcolor,char forecolor1,char forecolor2)
{
	uint8 buffer[ETAGABSTRACT_LENGTH_MAX];
	memset(buffer,0,ETAGABSTRACT_LENGTH_MAX);

	uint8* p=buffer;
	*p++ = '[';
	ulltoa(horizontal,p,10);
	p = buffer + strlen(buffer);
	*p++ = ',';

	ulltoa(vertical,p,10);
	p = buffer + strlen(buffer);
	*p++ = ',';

	*p++ = backcolor;
	*p++ = forecolor1;
	*p++ = forecolor2;
	*p++ = ']';
	return copyCharArray(buffer,strlen(buffer));
}


ETAGabstract* parseETAG_abstract(uint8* abstract, uint32 abstract_length)
{

	if(abstract == NULL || abstract_length < 2 )//"[]"
	{
		return NULL;
	}

	uint8 finish =0;
	ETAGabstract * structAbstract = NULL;

#define UNPACKFCSAP_BUFFER_LENGTH 10
	uint8 buf[UNPACKFCSAP_BUFFER_LENGTH];
	uint8* b ;
	uint8 counter =0;

	uint8* p = abstract;
	if( *p == '[')
	{
		structAbstract = (ETAGabstract*)myMalloc(sizeof(ETAGabstract),_FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_);
		if(structAbstract == NULL)
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

	while( p-abstract < abstract_length)
	{
		if( *p == ',' || *p == ']')
		{

			if(0 == counter)
			{
				long long digit = atoll(b);
				if(structAbstract == NULL)
				{//缺少开始的 '['
					return NULL;
				}
				else
					structAbstract->horizontal = digit;
			}
			else if(1 == counter)
			{
				long long digit = atoll(b);
				if(structAbstract == NULL)
				{//缺少开始的 '['
					return NULL;
				}
				else
					structAbstract->vertical = digit;
			}
			else if(2 == counter)
			{
				if(structAbstract == NULL)
				{//缺少开始的 '['
					return NULL;
				}
				else
					structAbstract->colors = copyCharArray(b,strlen(b)+1);
			}
			else if(3 == counter)
			{//error
			}
			//next
			b= buf;
			memset(b,0,UNPACKFCSAP_BUFFER_LENGTH);
			counter ++;
			if( *p == ']')
			{
//				finish =1;
				structAbstract->abstractLength = p+1-abstract;
				return structAbstract;//成功
//				break;//finish quit
			}
		}
		else
		{
			strcatChar(b,*p);
		}
		p++;
	}

	if(structAbstract == NULL)
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
			freeETAGabstract(structAbstract);
			return NULL;
		}
	}
	return NULL;
}


#if 0
int main()
{
	uint16 horizontal = 1024;
	uint16 vertical=740;
	char backcolor = CHAR_COLOR_WHITE;
	char forecolor1 = CHAR_COLOR_BLACK;
	char forecolor2 = CHAR_COLOR_RED;
	uint8* abstract = formEtagAbstract(horizontal, vertical, backcolor,forecolor1, forecolor2);

	myPrintf("abstract =%s\n",abstract);
	myFree(abstract);
	return 0;
}
#endif
