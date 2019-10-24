/*
 * cTools.c
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */
#include "itracker88Platform.h"
#include "cTools.h"
#include "commands.h"


int stringlen(uint8* string)
{
	int string_length =0;
	if(string !=NULL)
	{
		string_length = strlen(string);
	}
	return string_length;
}


//分成2bytes。   "87a.a66"-->87,0; "  87.6a6"-->87,6;  " 287.6 9"-->31,6;  因为287超过了256
int8 versionBytes(uint8* version, uint8* buffer, uint8 bufferlen)
{
	if(version == NULL || buffer == NULL || bufferlen < VERSION_BYTE_LENGTH)
		return -1;
	memset(buffer,0, VERSION_BYTE_LENGTH);

	int len = strlen(version);

	uint8* v[len+1];
	copyCharArrayIntoBuffer(version, len,v);
	char * point = strchr(v, '.');//记录c第一次在s出现的位置,并记录当前指针
	if(point != NULL)
	{
		*point = 0;//split on .
		int num2 = atoi(point+1);
		* (buffer+1) = num2;
	}
	int num1 = atoi(v);
	* buffer = num1;
	return 0;//success
}

void oneByte2String(uint8 oneByte, uint8* buf, uint16 buf_length)
{
	if(buf == NULL || buf_length < 3)
	{
		return;
	}
	itoa(oneByte,buf,10);//转化成十进制字符串
}

void versionBytes2String(uint8* twoBytes, uint8* buf, uint16 buf_length)
{
	if(buf_length < SOFTWAREVERSION_LENGTH_MAX)
		return ;
	uint8 b[4];
	memset(b,0,4);
	oneByte2String(*twoBytes, b, 4);
	copyCharArrayIntoBuffer(b,strlen(b),buf);

	strcat(buf,".");

	memset(b,0,4);
	oneByte2String(*(twoBytes+1), b, 4);
	strcat(buf,b);
}




//在原数据的基础上重新排列，长度不变。在使用前请复制原来的数据
void doOffsetByShortPW(uint8* shortPW, uint8* data, uint16 data_length)
{

	myPrintf("doOffsetByShortPW data_length= %d\n",data_length);

}

//在offset数据的基础上复原原来数据，长度不变。在使用前请复制原来的数据
void restoreOffsetByShortPW(uint8* shortPW, uint8* offsetData, uint16 offsetData_length)
{

	myPrintf("restoreOffsetByShortPW offsetData_length= %d\n",offsetData_length);

}


uint32 ceil(uint32 num,uint32 dividor)
{
	uint32 ret = num/dividor;
	if( num % dividor != 0)
	{
		ret ++;
	}
	return ret;
}




//~~~~~~~~~~~~~~~~~~from itrackerMath.c~~~~~~~~~~~~~~~~~~~~~~~~~~
uint32 get_ceiling_bytes_len( uint32 bits_len)
{
	uint32 bytes_len = bits_len/8;

	if( 0 != bits_len%8 )
	{
		bytes_len++;
	}
	return bytes_len;
}
uint16 getUint16_big_endian( uint8* p )
{
    return (((uint16)(*p)) << 8) + *(p+1) ;
}

void uint16_into_big_endian_bytes(uint16 number, uint8* buffer, uint16 buffer_len)
{
	if(buffer == NULL || buffer_len < 2)
		return ;

	*buffer = (number>>8) & 0xff;
	*(buffer+1) = number & 0xff;
}




#if 0
int main()
{
	uint8* version = " 267.6 9";
	uint8 buffer[3];
	uint8 bufferlen =2;
	int8 ver = versionBytes( version,  buffer,  bufferlen);

	printCharArray("buffer ",buffer,2);


	uint8 buf[8];
	versionBytes2String( buffer, buf, 8);

	myPrintf("buf= %s\n", buf);
}

#endif
