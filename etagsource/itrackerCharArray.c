#include "itracker88Platform.h"
#include "itracker88basic.h"
#include "itrackerCharArray.h"
#include "itrackerMemory.h"

itr_bool chararrayIsZero( uint8* chararray, uint16 length )
{
	int i;
	if( NULL == chararray || 0 == length )
		return itr_true;

	for( i=0; i<length; i++ )
	{
		if( 0 != *(chararray+i) )
		{
			return itr_false;
		}
	}
	return itr_true;
}

void copyRearCharArrayIntoFixedLengthBuffer( uint8* chararray, uint16 length, uint8* buffer, uint16 buffer_length  )
{
	if( chararray )
	{
		if( length >  ( buffer_length-1) )
		{
			chararray += length - ( buffer_length-1);
			length =  ( buffer_length-1);
		}
		memcpy( buffer ,   chararray, length );//to save __FILENAME__ and __LINE__
	}
}




void freeOneTotalCA(CA *oneca)
{
	if(oneca == NULL)
		return;

#if defined CA_EXPANSION_ANYINSTANCE
	myFree(oneca->anyInstance);
#endif
	myFree(oneca->chararray);
	myFree(oneca);
}

char valueIntoHexChar( uint8 value )
{
  if( value >= 16)
    return 0;
  
  if( value < 10)
    return '0'+value;
  else
    return 'A'+value-10;  
}



int8 getHexValueFromSingleLiteralChar(unsigned char ch)
{
	if(ch <= '9' && ch >= '0')
		return ch - '0';
	else if(ch <= 'F' && ch >= 'A')
		return ch -'A' + 10;
	else if(ch <= 'f' && ch >= 'a')
		return ch -'a' +10;
	else
		return -1;

}


int8 getUint32FromHexChars_BigEndian( uint32* to_save, unsigned char* hexes, uint8 length )
{
  if( NULL == to_save || NULL == hexes || 0 == length )
    return -1;
  //printf("[%s] %s;length=%d\r\n",__func__, hexes, length );
  
  uint8 real_length = length;
  
  if( length>8 )
    real_length =8;
  
  length -= real_length; //to save chars of longer
  
  *to_save =0;//maybe no hex
  int8 val;
  while(real_length--)
  {
    val = getHexValueFromSingleLiteralChar( *hexes);
  //printf("[%s] *hexes=%c,val=%d\r\n",__func__, *hexes , val );
    if( val >= 0 )
    {//valid hex
      *to_save = ( (*to_save)<<4 ) + val;
    }
    else if( 0 == *hexes )
    {//end
      return -1;//exception with \0
    }
    else
    {//skip NOT hex
      if( length )
      {
        real_length++;//compensate
        length--;
      }
    }
    hexes ++;
  }
  return 0;
}


itr_bool findStringInCharArray( const uint8* chararray, uint16 length )
{
	int16 i=0;
	if( NULL == chararray || 0 == length )
		return itr_false;

	for( ;i<length; i++ )
	{
		if( 0 == *(chararray+i) )
		{
			return itr_true;
		}
	}
	return itr_false;
}

#if defined _itrackerDebug_ && !defined ITRACKER_JNI

//in ITRACKER_JNI, use print_chararray_btp_log as printCharArray
//android uses print_chararray_btp_log
void printCharArray( char *memo, const unsigned char * src, uint16 length)
{
	uint32 i =0;

	if(NULL == src || 0==length)
	{
		myPrintf(memo);
		myPrintf(" (null)\n");
		return;
	}
	myPrintf(( const char *)memo);

	for(i=0; i<length; i++)
	{
		myPrintf((const char*)"%x,",*(src+i) );
	}
	myPrintf((const char*)"  printCharArray over\n");

}
#endif

#if defined _itrackerDebug_
void printOneCA( const char * note,CA * ca)
{
	myPrintf(note);
	myPrintf("-----------\n");
	if(NULL == ca)
	{
		myPrintf("the ca is NULL.");
		return;
	}

	myPrintf((const char*)"printOneCA() ca =%x\n" ,ca);
		if(NULL != ca)
		{
			myPrintf((const char*)"ca->chararray =%x\n" ,ca->chararray);
			myPrintf((const char*)"ca->length =%d\n" ,ca->length);
			printCharArray(( char*)"chararray:",ca->chararray,ca->length);

	#if defined CA_EXPANSION_STATE
	myPrintf((const char*)"printCA() state=%d\n",ca->state);
	#endif //CA_EXPANSION_STATE
	#if defined CA_EXPANSION_DIGIT
	myPrintf((const char*)"printCA() digit=%d\n",ca->digit);
	#endif //CA_EXPANSION_DIGIT
	#if defined CA_EXPANSION_ANYINSTANCE
	myPrintf((const char*)"printCA() anyInstance address=%x\n", ca->anyInstance );
		#if defined CA_EXPANSION_DIGIT
		//printOneObjByEntityNumber( ca->digit, ca->anyInstance  );
		#endif //CA_EXPANSION_DIGIT
	#endif//CA_EXPANSION_ANYINSTANCE
		}
		else
		{
			myPrintf("ca is null\n");
		}

}

#endif//_itrackerDebug_CA_


//from two characters to Int
uint32 dualCharsToInt(unsigned char firstChar,unsigned char secondChar)
{
	return firstChar * 256 + secondChar;
}


//gracestar will compensate ' '; standard compensate 0
uint32 charArraySumToInt(const unsigned char* src, uint16 length, char odd_compensate )
{//if length =0, return 0
	uint32 sum = 0;
	uint16 i;
	uint16 pair = length/2;

//	myPrintf("pair=%d\n",pair);

	if(NULL == src || length == 0)
		return 0;

	//len = strLength(src) -1;

	if(length % 2 != 0)
		sum += dualCharsToInt(src[length - 1], odd_compensate );   //do the last odd one


	for(i = 0; i < pair; i++)
		sum += dualCharsToInt(src[2 * i], src[2 * i +1]);

	return sum;
}



void fillHighEndZeroCharOnCharArray(unsigned char *src,uint16 srcLength, uint16 actualLength )
{ //actualLength < srcLength, both length within \0
	int16 i;
	if(NULL == src || srcLength <= actualLength)
		return ;


	for(i=srcLength -1; i >= 0 ; i--)
	{
		if(i < srcLength - actualLength)
			*(src + i) = '0';
		else
			*(src +i) = *(src+i -(srcLength-actualLength));
	}
}

//byteBuffer should has length > (length/2 )
void hexStringIntoByteBuffer_big_endian( const uint8* hexString, uint16 length, uint8* byteBuffer ,uint16 bufferLength )
{
	if( NULL == hexString || 0 == length || byteBuffer == NULL || bufferLength < length/2)
		return ;
	uint16 i;
	for( i=0; i<length/2; i++)
	{
		byteBuffer[i] = dualHexIntoByte_big_endian( hexString + (2*i) );
	}
}

//byteBuffer should has length > (length/2 )
void hexStringIntoByteBuffer_little_endian( const uint8* hexString, uint16 length, uint8* byteBuffer ,uint16 bufferLength )
{
	if( NULL == hexString || 0 == length || byteBuffer == NULL || bufferLength < length/2)
		return ;
	uint16 i;
	for( i=0; i<length/2; i++)
	{
		byteBuffer[i] = dualHexIntoByte_little_endian( hexString + (2*i) );
	}
}

unsigned char dualHexIntoByte_big_endian(const unsigned char * hexChars)
{
	int8 tmp;
	unsigned char sum =0;

	if(NULL == hexChars)
		return 0;
	tmp = getHexValueFromSingleLiteralChar(*hexChars++);

	if(tmp > -1)
		sum += (tmp << 4);  //valid > -1

	tmp = getHexValueFromSingleLiteralChar(*hexChars++);

	if(tmp > -1)
		sum |= tmp;

	return sum;
}

unsigned char dualHexIntoByte_little_endian(const unsigned char * hexChars)
{
	int8 tmp;
	unsigned char sum =0;

	if(NULL == hexChars)
		return 0;
	tmp = getHexValueFromSingleLiteralChar(*hexChars++);

	if(tmp > -1)
		sum |= tmp;  //valid > -1

	tmp = getHexValueFromSingleLiteralChar(*hexChars++);

	if(tmp > -1)
		sum |= (tmp << 4);


	return sum;
}

//high byte first, high 4-bits first. big-endian
void turnOneByteIntoDualHex_big_endian(const unsigned char b, uchar* targetBuffer)
{
#if 0  
	uchar * r;
	sprintf( (char*)targetBuffer,"%X", b); //turn into 2 hex chars and 1 ending \0;  if use 02x , error in IAR

//	 fillHighEndZeroCharOnCharArray(result, 3*sizeof(unsigned char), strLength(result) );
        r= targetBuffer;
	r++;//to first 
	if('\0' == *r )
	{
		*r = *targetBuffer;
		*targetBuffer = '0'; //fill highend zero of '0'
	}
#else
        if( NULL == targetBuffer )
          return;
        
        
        *targetBuffer  = valueIntoHexChar( (b>>4)&0x0f );//high first
        *(targetBuffer+1) = valueIntoHexChar( b&0x0f );

#endif
}

//high byte first, high 4-bits first
void turnOneUint16IntoHexChar( uint16 data, uint8* targetBuffer, uint8 buffer_length )
{
  char i;
  char howmany_hex = 16/4;
  if( NULL == targetBuffer || buffer_length < howmany_hex )
    return;
  for( i=0; i<howmany_hex; i++)
  {
    *(targetBuffer+i)  = valueIntoHexChar( ( data>>(4*(howmany_hex-1-i)) )&0x0f );//high first
  }
}

//high byte first, high 4-bits first
void turnOneUint32IntoHexChar( uint32 data, uint8* targetBuffer, uint8 buffer_length  )
{
  char i;
  char howmany_hex = 32/4;
  if( NULL == targetBuffer || buffer_length < howmany_hex )
    return;  
  for( i=0; i<howmany_hex; i++)
  {
	  //sprintf(data, "%08X", H0,);
    *(targetBuffer+i)  = valueIntoHexChar( ( data>>(4*(howmany_hex-1-i)) )&0x0f );//high first
  }
}

void turnOneUint64IntoHexChar( uint64 data, uint8* targetBuffer, uint8 buffer_length  )
{
  char i;
  char howmany_hex = 64/4;
  if( NULL == targetBuffer || buffer_length < howmany_hex )
    return;  
  for( i=0; i<howmany_hex; i++)
  {
    *(targetBuffer+i)  = valueIntoHexChar( ( data>>(4*(howmany_hex-1-i)) )&0x0f );//high first
  }
}

//need length*8
void uint32ArrayIntoHex( uint32* data, uint32 length, uint8* targetBuffer )
{

	uint32 i;
	for(i=0; i< length; i++)
	{
		//sprintf(data, "%08X", H0,);
		turnOneUint32IntoHexChar( *data++ , targetBuffer + (i*8), 8 );
	}
}

unsigned char *oneByteIntoDualHex(const unsigned char b)
{
	 uchar * result = (unsigned char *)myMalloc(3*sizeof(unsigned char), _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_ );  //1 is easy for ending \0
	 uchar * r = result;
		if(result == NULL)
		{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
			return NULL;
		}

        
	 
#if 0
	sprintf( (char*)result,"%X", b); //turn into 2 hex chars

//	 fillHighEndZeroCharOnCharArray(result, 3*sizeof(unsigned char), strLength(result) );

	r++;//to first 
	if('\0' == *r )
	{
		*r = *result;
		*result = '0'; //fill highend zero
	}
#else
        turnOneByteIntoDualHex_big_endian( b, result);
#endif

	return (uchar*)result;
}

unsigned char *intIntoFourHex(uint32 num)
{
	unsigned char c1 = num / 256 ;
	unsigned char c2 = num % 256 ;

	 uchar * result = ( uchar *)myMalloc(5*sizeof(unsigned char) , _FILENAME_STRING_, _FUNCTIONNAME_STRING_,_LINE_NUMBER_ );//1 is for \0
	 uchar * r = result;
		if(result == NULL)
		{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
			return NULL;
		}

#if 0
	sprintf( (char*)r,"%X", c1); //turn into 2 hex chars
	r++;
	if('\0' == *r )
	{
		*r = *result;
		*result = '0'; //fill highend zero
	}
#else
      turnOneByteIntoDualHex_big_endian( c1, r);  
#endif
	r = result +2;
        
#if 0
	sprintf( (char*)r,"%X", c2); //turn into 2 hex chars
	r++;
	if('\0' == *r )
	{
		*r = *(r-1);
		*(r-1) = '0'; //fill highend zero
	}
#else
        turnOneByteIntoDualHex_big_endian( c2, r);  
#endif
	return (uchar*)result;
}


//digits: how many bits;  should <=3.  digitals should < 256
unsigned char decimalCharsIntoOneByte(const unsigned char *digitals,  char digits)
{
	unsigned char i=0, sum =0;

	if(NULL == digitals || digits < 1)
		return 0;

	for(i=0; i < digits ; i++)
	{
		if(*digitals < '0' || *digitals > '9')
			return 0;   //invalid char will return 0
		else
			sum = sum*10 + (*digitals - '0') ;

		digitals++;
	}
	return sum;

}


//if NULL return -1; if all value return 1; if someone not this value return 0
int8 checkAllSameValue(uint8 * chararray, uint64 length, uint8 value )
{
  uint64 i=0;
  if(chararray == NULL)
    return -1;

  for( ; i<length; i++)
  {
    if( value != *(chararray + i))//someone not value
      return 0;
  }
  return 1;//all same value
}
//text_length is from text to the end of text, maybe without \0; return the next space after nex whole word. if reach the end of text, return NULL
uchar* copyNextWholeWordInText( uchar* text, uint16 text_length, uchar* buffer, uint8 buffer_length )
{
    memset( buffer, 0, buffer_length );
    if( NULL == text || 0 == text_length )
    {
        return NULL;
    }

    while( (*text == ' ' || *text == '\r' || *text == '\n' || *text == '\0'  )  && text_length > 0 )//space
    {
        text++;
        text_length--;
    }
    if( 0 == text_length || *text == '\0' )
    {
        return NULL;
    }

    while( (*text != ' ' && *text != '\r' && *text != '\n' && *text != '\0'  ) && text_length > 0 )//space
    {
        if( buffer_length > 1  )//1 is for \0
        {
            *buffer = *text;
            buffer++;
            buffer_length--;
        }
        //else if( 1 == buffer_length  )
       // {
       //     *buffer = 0;
        //}

        text++;
        text_length--;

    }

    if( 0 == text_length || *text == '\0' )
    {
        return NULL;
    }

    return text;
}


void init_buffer_with_special_uchar( uchar* buffer, uint16 buffer_length, uchar special_uchar, uint16 length )
{
    uint16 i;
    if( NULL == buffer ||  buffer_length <= 1 )//1 is for \0
        return;
    if( length >= buffer_length )
        length = buffer_length -1;//1 is for \0

    memset( buffer, 0, buffer_length );
    for( i=0;i<length;i++)
    {
        *buffer++ = special_uchar;
    }
}

//write date into this address , without malloc
void writeDateInto7Chars(unsigned char * date, uint16 length, unsigned char * targetAddress)
{
	if(length < 19)
		return;
	*targetAddress++ = decimalCharsIntoOneByte(date,   2);
	*targetAddress++ = decimalCharsIntoOneByte(date+2, 2);
	*targetAddress++ = decimalCharsIntoOneByte(date+5, 2);
	*targetAddress++ = decimalCharsIntoOneByte(date+8, 2);
	*targetAddress++ = decimalCharsIntoOneByte(date+11,2);
	*targetAddress++ = decimalCharsIntoOneByte(date+14,2);
	*targetAddress++ = decimalCharsIntoOneByte(date+17,2);
}

//the former will fill zero
unsigned char * oneByteIntoDecimalChars(unsigned char srcNumber,  char digits)
{
	unsigned char * result = (unsigned char *)myMalloc((digits+1)*sizeof(unsigned char) , _FILENAME_STRING_, _FUNCTIONNAME_STRING_,_LINE_NUMBER_ );//1 is for \0

	if(result == NULL)
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}


        
#if 0
	sprintf((char*)result,"%d",srcNumber);
#else
        turnIntIntoDecStr( srcNumber, result, digits+1);
#endif
        
//        #include "itrackerString.h"
//	fillHighEndZeroCharOnCharArray((uchar*)result ,digits, strLength(result)-1 );

	return ( uchar*)result;
}






float sixCharIntoFloat(uint8* fnum, uint8 length)
{


	float f =0.0;
#if defined _itrackerDebug_CA_
	myPrintf("fiveCharIntoFloat length=%d\n",length);
#endif
	if(fnum == NULL || length ==0)
		return 0.0;


	if(length >1)
	{
		f =   *(fnum+1) ;

		if(length >2)
		{
			f =  ( ((uint16)(*(fnum+1))) << 8) + *(fnum+2) ;

#if defined _itrackerDebug_CA_
			myPrintf("fiveCharIntoFloat f=%f\n",f);
#endif
			if(length > 3)
			{
				f += ((float)(*(fnum+3)))/100.0;
				if(length > 4)
				{
					f += ((float)(*(fnum+4)))/10000.0;
					if(length > 5)
					{
						f += ((float)(*(fnum+5)))/1000000.0;
					}
				}
			}

		}
	}

	if (*fnum == 255)
		f = f* (-1.0);
	return f;
}


//integer part into 2 char (int16). after point, every 2 digits into 1char , total 6 digits
unsigned char *floatInto6Char(float d)
{
//	uchar * dStr =NULL;
	uchar *result =NULL;
//	int serial=0;
//	char length =0;
	uint16 intpart = (int32)d;
	float minipart = d - intpart;


#if defined (_itrackerDebug_CA_ )
	myPrintf("floatInto5Char() d =%f\n",d);
	myPrintf("floatInto5Char() intpart =%d\n",intpart);
#endif

//	dStr = 	(uchar *)floatToStr(d);
//#if defined (_itrackerDebug_CA_ )
//	myPrintf("floatInto5Char() dStr =%s\n",dStr);
//#endif
//	if(NULL == dStr)
//		return NULL;

	result = (uchar *)myMalloc(7 * sizeof(uchar) , _FILENAME_STRING_, _FUNCTIONNAME_STRING_,_LINE_NUMBER_ );  //final is \0
	if(result == NULL)
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}

	if(d < 0)
		result[0] =255;//-

//	serial = findFirstPosInStr(dStr, '.');
//	length = strLength(dStr) -1;

	result[1] = (uint8)( (intpart>>8) & 0x00ff ) ;
	result[2] = (uint8)( intpart & 0x00ff ) ;
#if defined (_itrackerDebug_CA_ )
	myPrintf("floatInto6Char() result[0] =%d\n",result[1]);
	myPrintf("floatInto6Char() result[1] =%d\n",result[2]);
	myPrintf("floatInto6Char() minipart =%f\n",minipart);
#endif

	{//has point;  float has 6 digits after point!  0.000000

			d = minipart * 100;
			result[3] = (uint8)(d);
			minipart =  d - result[3];

			d = minipart * 100;
			result[4] = (uint8)(d);
			minipart =  d - result[4];

			d = minipart * 100;
			result[5] = (uint8)(d);


	}
//	myFree(dStr);

	return result;


}



char toLower(char c)
{
	if(c >= 'A' && c <= 'Z')
		return (c-'A' + 'a');
	return c;
}

char toUp(char c)
{
	if(c >= 'a' && c <= 'z')
		return (c-'a' + 'A');
	return c;
}

CA* replacePartOfCA(CA* ca, uint16 offset, uint16 old_length, uint8* new_part, uint16 new_part_length )
{
	uint16 first_part_length = 0;
	uint16 old_second_part_length = 0;
	uint16 third_part_length = 0 ;
	uint16 new_second_part_length = 0;
	CA * new_ca = NULL;
	if( NULL == ca || ca->length < offset || NULL == new_part )
		return NULL;

	first_part_length = offset;
	if( offset + old_length < ca->length )
	{
		old_second_part_length = old_length;
		third_part_length = ca->length - offset - old_length ;
	}
	else
	{
		old_second_part_length = ca->length - offset ;
		third_part_length = 0;
	}
	new_second_part_length = new_part_length;

	new_ca = (CA*)myMalloc( sizeof( CA ),  _FILENAME_STRING_, _FUNCTIONNAME_STRING_,_LINE_NUMBER_ );
	if( NULL == new_ca )
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}


	new_ca->length = first_part_length+ new_second_part_length+ third_part_length;
	if ( 0 == new_ca->length )
	{//ca->chararray cannot be null
		new_ca->chararray = (uchar*)myMalloc( sizeof( uchar )*1,  _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		if( NULL == new_ca->chararray  )
		{
			myFree(new_ca);
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %llu\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
			return NULL;
		}

	}
	else
	{
		new_ca->chararray = (uchar*)myMalloc( sizeof( uchar )*(new_ca->length),  _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		if( NULL == new_ca->chararray  )
		{
			myFree(new_ca);
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %llu\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
			return NULL;
		}

#if defined _itrackerDebug_CA_
	myPrintf("first_part_length=%u, old_second_part_length=%u,third_part_length=%u , new_second_part_length=%u, new_ca->length=%u\n",
			first_part_length,old_second_part_length , third_part_length, new_second_part_length, new_ca->length);
#endif
		copyCharArrayIntoBuffer( ca->chararray, first_part_length ,  new_ca->chararray );
		copyCharArrayIntoBuffer( new_part, new_second_part_length ,  new_ca->chararray + first_part_length );
		copyCharArrayIntoBuffer( ca->chararray+ first_part_length+old_second_part_length , third_part_length ,  new_ca->chararray+ first_part_length+new_second_part_length );
	}
	return new_ca;
}


//0 is same; 2 is same without capital cared; 1 is different
uint8 charCompare(char c1, char c2)
{
	if(c1 == c2)
		return 0;
	else if( toUp(c1) == toUp(c2) )
		return 2;  // same without capital cared

	return 1;//different
}

//0 is same; 1 is different;  2 is same without capital cared
uint8 chararrayCompare(const uint8* chararray1, uint16 length1, const uint8* chararray2, uint16 length2, uint8 supportTrim)
{
		uint16 i = 0;
		uint8 capitalSame = 0;//0 is all same
		CA * ca1 = NULL, *ca2 =NULL;

		uint8* cArr1,*cArr2;
		uint16 len1,len2;
//memoryWatcherReport("chararrayCompare1");
		if(chararray1 == NULL && chararray2 == NULL )
			return 0;//same

		if(chararray1 ==NULL || chararray2==NULL)
			return 1;//not same

		if(supportTrim != 0)//YES TRIM
		{
			ca1 = trimCharArray(chararray1,length1);//new malloc
			ca2 = trimCharArray(chararray2,length2);//new malloc
			cArr1 = ca1->chararray;
			cArr2 = ca2->chararray;
			len1 = ca1->length;
			len2 = ca2->length;
		}
		else
		{
			cArr1 = (uint8*)chararray1;
			cArr2 = (uint8*)chararray2;
			len1 = length1;
			len2 = length2;
		}
//memoryWatcherReport("chararrayCompare2");
		if(len1 != len2)
		{
			if(supportTrim != 0)
			{
				freeOneTotalCA(ca1);//free new malloced,  original parameter NOT freed
				freeOneTotalCA(ca2);//free new malloced,  original parameter NOT freed
			}

			return 1;//not same
		}
//memoryWatcherReport("chararrayCompare3");
		while(i < len1)
		{
			if( 2 == charCompare(*(cArr1 +i) , *(cArr2 +i))  )
			{
				capitalSame = 2;//anyone
			}
			else if( *(cArr1 +i) != *(cArr2 +i)  )
			{
				if(supportTrim != 0)
				{
//memoryWatcherReport("chararrayCompare4");
					freeOneTotalCA(ca1);//free new malloced,  original parameter NOT freed
					freeOneTotalCA(ca2);//free new malloced,  original parameter NOT freed
				}
				return 1;
			}
			i++;
		}

		if(supportTrim != 0)
		{
//memoryWatcherReport("chararrayCompare5");
			freeOneTotalCA(ca1);//free new malloced,  original parameter NOT freed
			freeOneTotalCA(ca2);//free new malloced,  original parameter NOT freed
		}
//memoryWatcherReport("chararrayCompare5");
#if defined _itrackerDebug_CA_
		myPrintf("capitalSame=%d\n",capitalSame);
#endif
		return capitalSame;//same or capital same
}


//0 is same; 1 is different;  2 is same without capital cared
uint8 caContentCompare(CA * ca1, CA * ca2,   uint8 supportTrim)
{
	uint16 i = 0;
	uint8 capitalSame = 0;//0 is all same
	if(ca1 == NULL && ca2 == NULL )
		return 0;//same
	if( ca1 != NULL && ca2 != NULL &&  ca1->chararray ==NULL && ca2->chararray==NULL)
		return 0;//same

	if(ca1 == NULL || ca2 == NULL || ca1->chararray ==NULL || ca2->chararray==NULL)
		return 1;//not same

	if(supportTrim != 0)
	{
		ca1 = trimCA(ca1);//new malloc
		ca2 = trimCA(ca2);//new malloc
	}

	if(ca1->length != ca2->length)
	{
		if(supportTrim != 0)
		{
			freeOneTotalCA(ca1);//free new malloced,  original parameter NOT freed
			freeOneTotalCA(ca2);//free new malloced,  original parameter NOT freed
		}

		return 1;//not same
	}

	while(i< ca1->length)
	{
		if( 2 == charCompare(*((ca1->chararray) +i) , *((ca2->chararray) +i))  )
		{
			capitalSame = 2;//anyone
		}
		else if( *((ca1->chararray) +i) != *((ca2->chararray) +i)  )
		{
			if(supportTrim != 0)
			{
				freeOneTotalCA(ca1);//free new malloced,  original parameter NOT freed
				freeOneTotalCA(ca2);//free new malloced,  original parameter NOT freed
			}
			return 1;//anyone different
		}
		i++;
	}

	if(supportTrim != 0)
	{
		freeOneTotalCA(ca1);//free new malloced,  original parameter NOT freed
		freeOneTotalCA(ca2);//free new malloced,  original parameter NOT freed
	}
	return capitalSame;//same or capital same
}



//into chArr1
void appendCharArrayWithoutRemalloc(uint8* chArr1, uint16 chArr1_len, uint8 * chArr2, uint16 chArr2_len)
{
	if(chArr1 == NULL )
		return;
	copyCharArrayIntoBuffer(chArr2,chArr2_len, chArr1+chArr1_len);
}

CA* trimCAFree(CA* oneca)
{
	CA * ca = trimCA(oneca);
	freeOneTotalCA(oneca);
	return ca;
}

CA* trimCA(CA* ca)
{
	if(ca == NULL)
		return NULL;

	return trimCharArray(ca->chararray,ca->length);
}

CA* trimCharArrayFree(uint8* chararray, uint16 length)
{
	CA * ca = trimCharArray((uint8*)chararray,length);
	myFree(chararray);
	return ca;
}

CA* trimCharArray(const uint8* chararray, uint16 length)
{
	uint8 * temp = NULL;
	CA * ca = NULL;
	if(chararray == NULL)
		return NULL;

	temp = (uint8*)chararray + length -1;
	while(temp >= chararray && *temp == '\0'  )//temp >= chararray should do first . because when length=0 , or will out of bound
	{
		temp--;
	}
	length =  temp - chararray +1 ;//form a new chararray

	temp = (uint8*)chararray;
	while(temp <= chararray + length -1 && *temp == '\0'  )
	{
		temp++;
	}
	length = length - (temp-chararray );

	ca = (CA*) myMalloc(sizeof(CA) , _FILENAME_STRING_, _FUNCTIONNAME_STRING_,_LINE_NUMBER_ );
	if(ca == NULL)
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}
	ca->chararray = copyCharArray(temp,length);
	ca->length = length;

	return ca;
}

//trim0ofFormer:0 is donot trim the former chararray; 1 is trimming one ending \0 of the former chararray; 2 is trimming all ending \0
CA* appendCharArrayWithRemalloc(uint8* chArr1, uint16 chArr1_len, uint8 * chArr2, uint16 chArr2_len, uint8 trim0ofFormer)
{
	CA * ret =NULL;
	uint8 *temp=NULL;
	uint16 trimming =0;

	if(chArr1 == NULL && chArr2 == NULL )
		return NULL;

	if(chArr1 == NULL || chArr1_len == 0 )
	{
		chArr1_len = 0;
		trimming =0;
	}
	else if(trim0ofFormer ==1 && *(chArr1 + chArr1_len -1) == '\0' )
	{
		trimming =1;
	}
	else if(trim0ofFormer ==2 )
	{//trimming all ending \0
		if( chArr1_len > 0)
		{
			temp = chArr1 + chArr1_len-1 ;// at the end byte

			while(*temp == '\0' && temp >= chArr1)
			{
				temp--;
			}
			trimming = (chArr1_len -1) - (temp - chArr1 );
		}
		else
			trimming = 0;
	}
	else
	{
		trimming = 0;
	}


	if(chArr2 == NULL )
		chArr2_len = 0;

	ret = (CA *)myMalloc(sizeof(CA) , _FILENAME_STRING_, _FUNCTIONNAME_STRING_,_LINE_NUMBER_ );
	if(ret == NULL)
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}
	ret->chararray = (uint8 *)myMalloc(sizeof(uint8)*(chArr1_len + chArr2_len +1 - trimming) , _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_ ); //1 \0 is easy for print
	if(ret == NULL)
	{
		myFree(ret);
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}

	ret->length = chArr1_len + chArr2_len -trimming;

	copyCharArrayIntoBuffer(chArr1,chArr1_len, ret->chararray);
	copyCharArrayIntoBuffer(chArr2,chArr2_len, ret->chararray + chArr1_len -trimming);

	return ret;
}

//trim0ofFormer:0 is donot trim the former chararray; 1 is trimming one ending \0 of the former chararray; 2 is trimming all ending \0
CA* appendCAWithRemalloc(CA * ca1, CA * ca2, uint8 trim0ofFormer)
{
	uint8* chArr1 =NULL;
	uint16 chArr1_len =0;
	uint8 * chArr2 =NULL;
	uint16 chArr2_len =0;

	if(ca1 != NULL)
	{
		chArr1 = ca1 ->chararray;
		chArr1_len = ca1 ->length;
	}

	if(ca2 != NULL)
	{
		chArr2 = ca2 ->chararray;
		chArr2_len = ca2 ->length;
	}
	return appendCharArrayWithRemalloc( chArr1,  chArr1_len,  chArr2,  chArr2_len,  trim0ofFormer);//1 is easy for print

}


//without \0
unsigned char *copyCharArray(const unsigned char * source, uint16 length)
{
	unsigned int i;
	unsigned char *result ;
	if(source == NULL || 0 == length)
		return NULL;

	result = (unsigned char *)myMalloc((length +1)*sizeof(unsigned char) , _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_ );//1 is easy for print
	if(result == NULL)
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}

	for(i=0;i<length; i++)
	{
		result[i] = source[i];
	}

	return result;
}


void copyCharArrayIntoBuffer(const unsigned char * source,  uint16 length, unsigned char * target)
{
	unsigned int i;

	if(source == NULL || target == NULL || length ==0)
		return;

	for(i=0;i<length; i++)
	{
		target[i] = source[i];
	}

}

void copyCharArrayIntoBufferWithLimit(const unsigned char * source,  uint16 length, unsigned char * target, uint16 length_limit)
{
	if(length > length_limit)
	{
		length = length_limit;
	}
	copyCharArrayIntoBuffer( source,  length,  target);
}

void copyStringIntoBufferWithLimit(const unsigned char * string, unsigned char * target, uint16 length_limit)
{
	uint16 length = strlen(string)+1;//1 if for ending 0
	if(length > length_limit)
	{
		length = length_limit;
	}
	copyCharArrayIntoBuffer( string,  length,  target);
}

itr_bool caIsNull(CA* oneca)
{
	if(oneca == NULL || oneca->chararray ==NULL )  //|| oneca->length == 0
		return itr_true  ;

	return itr_false;
}

/*
#define PURE_DIGIT_NUMBER 1
#define FIRST_DIGIT_NUMBER 2
#define DIGIT_NUMBER 3
#define ENGLISH_EMAIL_CHAR 4
#define ENGLISH_NAME_CHAR 5
#define PRINTABLE_CHAR 6
 */
unsigned char checkFormatOnChar(unsigned char c, unsigned char format)
{
	unsigned char re = 0xff;

	switch(format)
	{
	case PURE_DIGIT_NUMBER:
		if(c >= '0' && c <= '9')
			re =0;
		break;

	case PURE_DIGIT_NUMBER_OR_DOT:
		if((c >= '0' && c <= '9') ||  '.' == c )
			re =0;
		break;

	case FIRST_DIGIT_NUMBER:
		if((c >= '0'|| c <= '9') || '.' == c || '+' == c || '-' == c)
			re =0;
		break;

	case FIRST_DIGIT_NUMBER_OF_INT:
		if((c >= '0'|| c <= '9') || '+' == c || '-' == c)
			re =0;
		break;

	case FIRST_DIGIT_NUMBER_OF_UINT:
		if((c >= '0'|| c <= '9') || '+' == c)
			re =0;
		break;

	case ENGLISH_EMAIL_CHAR://_ . 0~9 A~Z a~z
		if(c == '_' || c == '.' || (c >= '0' && c <= '9')
				|| (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
			re =0;
		break;

	case ENGLISH_NAME_CHAR: // ' space - _ . 0~9 A~Z a~z
		if(c == '\'' ||c == ' ' ||c == '-' ||  c == '_' || c == '.' || (c >= '0' && c <= '9')
				|| (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
			re =0;
		break;

	case PRINTABLE_CHAR:
		if(c >= 0x20 && c <= 0x7E)
			re =0;
		break;

	case DATE_CHAR:  //2014-12-12 02:33:12
		if( (c >= '0' && c <= '9') || '-' == c || ':' ==c ||' ' ==c )
			re =0;
		break;

	default:  //default will return -1
		break;
	}

	return re;
}

uint16 formInt16(uint8 CN_MSB, uint8 CN_LSB)
{
	return ( ((uint16)CN_MSB)<<8 ) + (uint16)CN_LSB;
}

uint8 getMSB(uint16 num)
{
	return (uint8)((num >> 8) & 0x00ff);
}
uint8 getLSB(uint16 num)
{
	return (uint8)(num & 0x00ff);
}


int32 matchCharArray(const uint8* src_chararray, uint16 src_length , const uint8* sub_chararray, uint16 sub_length )
{
	uint16 i =0, j=0;
	for( ;i<src_length; i++ )
	{
		for( j=0; j<sub_length; j++ )
		{
			if( src_chararray[i+j] != sub_chararray[j] )
			{
				break;
			}
		}

		if( j == sub_length )
			return i;//found it
	}

	return -1;//not found
}


//filter out all the char not complied with the format
unsigned char * filterCharArray(unsigned char * chararray,unsigned char arraysize, unsigned char format)
{
	unsigned char * p= NULL, *result = NULL;
	unsigned char i ;
	unsigned char sum =0;//for \0

	if(0 == arraysize || NULL == chararray)
		return NULL;

	for(i=0; i < arraysize; i++)
	{//get the total of all numbers
//		if(chararray[i] >= '0' && chararray[i] <= '9')
		if( !checkFormatOnChar(chararray[i], format))
			sum++;
	}

	if(1 == sum)
		return NULL;//only '\0'

	result = (unsigned char *)myMalloc((sum+1)*sizeof(unsigned char) , _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_ );//1 is easy for print
	if(result == NULL)
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}
	p = result;

	for(i=0; i < arraysize; i++)
	{//get the total of all numbers
//		if(chararray[i] >= '0' && chararray[i] <= '9')
		if( !checkFormatOnChar(chararray[i], format))
			*p++ = chararray[i];
	}

	return result;

}

//return new malloc ca and chararray; withou free source
CA* upgradeCharArrayInQuote(uint8* source, uint16 length)
{
	uint16 count =0, i=0 ;
	uint8* src = source;
	uint8* ret=NULL, *temp=NULL;
	CA * ca=NULL;
	if(src == NULL)
		return NULL;

	while(i < length)
	{
		if(*src == '\\' || *src == '\"' || *src == '{' || *src == '}'   )
		{
			count++;
		}
		i++;
		src++;
	}
	ret = (uint8*)myMalloc(sizeof(uint8)*(length + count +1) , _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_ );  //i is \0
	if(ret == NULL)
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}
	src = source;
	temp = ret;
	i=0;
	while(i < length)
	{
		if(*src == '\\' || *src == '\"' || *src == '{' || *src == '}'   )
		{
			*temp++ = '\\';
		}
		*temp++ = *src++;
		i++;
	}
	ca = (CA*)myMalloc(sizeof(CA) , _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
	if(ca == NULL)
	{
		myFree(ret);
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %llu\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}
	ca->chararray = ret;
	ca->length = length + count;
	return ca;
}


//return new malloc ca and chararray; withou free source
CA* degradeCharArrayInQuote(uint8* source, uint16 length)
{
	uint16 count =0;
	uint8* src = source;
	uint8* ret, * temp=NULL;
	CA * ca;
	if(src == NULL)
		return NULL;

	ret = (uint8*)myMalloc(sizeof(uint8)*(length+1) , _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_ );  //1 is possible needing \0
	if(ret == NULL)
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}
	temp = ret;

	while(*(src+1))
	{
		if( *src == '\\' && ( *(src+1) == '\\' || *(src+1) == '\"' || *(src+1) == '{' || *(src+1) == '}' )  )
		{
			*temp++ = *(src+1);//copy the latter
			src +=2;//skip one
			count++;//remember how many matches
		}
		else
		{
			*temp++ = *src++;
		}
	}
	*temp++ = *src++; //last one not 0

//	myPrintf("count=%d\n",count);
	ca = (CA*)myMalloc(sizeof(CA) , _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
	if(ca == NULL)
	{
		myFree(ret);
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}
	ca->chararray = ret;
	ca->length = length - count;
	return ca;
}


itr_bool checkAllSpecialChar(const uint8* chararray, uint16 length, uint8 oneSpecialChar)
{
	uint16 i=0;
	uint8 flag = itr_true;

	if(chararray == NULL || length ==0)
		return itr_true;

	for(; i<length; i++)
	{
		if(*(chararray + i) != oneSpecialChar)
		{
			flag = itr_false;
		}
	}
	return flag;
}

//if NULL return itr_true
itr_bool checkAllZero(uint8 * chararray, uint16 length)
{
  uint16 i=0;
  if(chararray == NULL)
    return itr_true;
  
  for( ; i<length; i++)
  {
    if( 0 != *(chararray + i))
      return itr_false;
  }
  return itr_true;
}


void myMemCopy(void * source, void *target, uint16 len)
{
	uint16 i =0;
	uint8* sou = (uint8*)source;
	uint8* tar = (uint8*)target;
	
	if( NULL == source || NULL == target || 0 == len)
		return;

	for(;i<len;i++)
	{
		*(tar++) = *(sou++);
	}
}

void myMemset(void * memAddr, uint8 value, uint16 len)
{
	uint16 i =0;
	uint8* mem = (uint8*)memAddr;

	if( NULL == memAddr || 0 == len)
		return;

	for(;i<len;i++)
	{
		*(mem++) = value;
	}
}


int8 checkHexFormat( uint8 character )
{
	if( (character >= '0' && character<='9') || (character>='A' && character<='F') || (character>='a' && character<='f') )
		return 0;
	else
		return -1;
}



//A3-4B-0C-0D-EE-FF
//A3:4B:0C:0D:EE:FF
//A3 4B 0C 0D EE FF
//A34B0C0DEEFF
//big endian
uint8* parseFormatHexMacIntoCharArraySix( uint8* mac, uint8 length )
{
	uint8* mac_ca = NULL;
	uint8 containsDash = 0;
	uint8 containsColon = 0;
	uint8 containsSpace = 0;
	uint8 continuousHex = 0;

	if( length < 12 || NULL == mac )
		return NULL;//invalid mac

	mac_ca = (uint8*)myMalloc( 7  , _FILENAME_STRING_, _FUNCTIONNAME_STRING_,_LINE_NUMBER_ );//with ending \0
	if( NULL == mac_ca )
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}

	if( 0 == checkHexFormat(mac[0]) && 0 == checkHexFormat(mac[1]) )
	{
		mac_ca[0] = ( (uint8)getHexValueFromSingleLiteralChar( mac[0]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar( mac[1] ) );
	}
	else
	{
		myFree( mac_ca );
		return NULL;//invalid mac
	}

	if( '-' == mac[2] )
	{
		containsDash = 1;
	}
	else if( ':' == mac[2] )
	{
		containsColon = 1;
	}
	else if( ' ' == mac[2] )
	{
		containsSpace = 1;
	}
	else if( 0 == checkHexFormat(mac[2]) )
	{
		continuousHex = 1;
	}
	else
	{
		myFree( mac_ca );
		return NULL;//invalid mac
	}

	if( continuousHex )
	{
		if( 0 == checkHexFormat(mac[3]) )
		{
			if(			 0 == checkHexFormat(mac[2]) &&  0 == checkHexFormat(mac[3])
					 &&  0 == checkHexFormat(mac[4]) &&  0 == checkHexFormat(mac[5])
					 &&  0 == checkHexFormat(mac[6]) &&  0 == checkHexFormat(mac[7])
					 &&  0 == checkHexFormat(mac[8]) &&  0 == checkHexFormat(mac[9])
					 &&  0 == checkHexFormat(mac[10]) &&  0 == checkHexFormat(mac[11]))
			{
				mac_ca[1] = ( (uint8)getHexValueFromSingleLiteralChar( mac[2]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar( mac[3])  );
				mac_ca[2] = ( (uint8)getHexValueFromSingleLiteralChar(mac[4]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar(mac[5])  );
				mac_ca[3] = ( (uint8)getHexValueFromSingleLiteralChar(mac[6]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar(mac[7])  );
				mac_ca[4] = ( (uint8)getHexValueFromSingleLiteralChar(mac[8]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar(mac[9])  );
				mac_ca[5] = ( (uint8)getHexValueFromSingleLiteralChar(mac[10]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar(mac[11])  );
			}
			else
			{
				myFree( mac_ca );
				return NULL;//invalid mac
			}



		}
		else
		{
			myFree( mac_ca );
			return NULL;//invalid mac
		}
	}
	else
	{
		if( length < 17 )
		{
			myFree( mac_ca );
			return NULL;//invalid mac
		}

		if( containsDash )
		{
			if( '-' == mac[5] && '-' == mac[8] && '-' == mac[11] && '-' == mac[14]  )
			{
			}
			else
			{
				myFree( mac_ca );
				return NULL;//invalid mac
			}
		}
		else if( containsColon )
		{
			if( ':' == mac[5] && ':' == mac[8] && ':' == mac[11] && ':' == mac[14]  )
			{
			}
			else
			{
				myFree( mac_ca );
				return NULL;//invalid mac
			}
		}
		else if( containsSpace )
		{
			if( ' ' == mac[5] && ' ' == mac[8] && ' ' == mac[11] && ' ' == mac[14]  )
			{
			}
			else
			{
				myFree( mac_ca );
				return NULL;//invalid mac
			}
		}
		else
		{
			myFree( mac_ca );
			return NULL;//invalid mac
		}

		if(			 0 == checkHexFormat(mac[3]) &&  0 == checkHexFormat(mac[4])
				 &&  0 == checkHexFormat(mac[6]) &&  0 == checkHexFormat(mac[7])
				 &&  0 == checkHexFormat(mac[9]) &&  0 == checkHexFormat(mac[10])
				 &&  0 == checkHexFormat(mac[12]) &&  0 == checkHexFormat(mac[13])
				 &&  0 == checkHexFormat(mac[15]) &&  0 == checkHexFormat(mac[16]))
		{
			mac_ca[1] = ( (uint8)getHexValueFromSingleLiteralChar(mac[3]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar(mac[4]) );
			mac_ca[2] = ( (uint8)getHexValueFromSingleLiteralChar(mac[6]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar(mac[7])  );
			mac_ca[3] = ( (uint8)getHexValueFromSingleLiteralChar(mac[9]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar(mac[10]) );
			mac_ca[4] = ( (uint8)getHexValueFromSingleLiteralChar(mac[12]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar(mac[13]) );
			mac_ca[5] = ( (uint8)getHexValueFromSingleLiteralChar(mac[15]) << 4 ) + ( (uint8)getHexValueFromSingleLiteralChar(mac[16]) );
		}
		else
		{
			myFree( mac_ca );
			return NULL;//invalid mac
		}
	}
	return mac_ca;
}

#define B_ADDR_LEN 6
//pAddr with length of B_ADDR_LEN; str with lenght of 13
void MacSixIntoMac12HexChar( uint8 *pAddr ,uint8 length6byte, uint8* str, uint8 length13bytes )
{
  if( length6byte <B_ADDR_LEN)
    return;
  
  //6*2 +1 for \0
  if(length13bytes < 13)
    return;
  
  memset(str,0,length13bytes);
  turnOneByteIntoDualHex_big_endian( *pAddr,  str );
  turnOneByteIntoDualHex_big_endian( *(pAddr+1),  str+2 );
  turnOneByteIntoDualHex_big_endian( *(pAddr+2),  str+4 );
  turnOneByteIntoDualHex_big_endian( *(pAddr+3),  str+6 );
  turnOneByteIntoDualHex_big_endian( *(pAddr+4),  str+8 );
  turnOneByteIntoDualHex_big_endian( *(pAddr+5),  str+10 );
}

uint8* parseCharArraySixIntoMac12HexChar( uint8* chararray , uint8 length )//into 12 char + 1 for \0
{
	uint8* ret = NULL;
	if( NULL == chararray || length < 6 )
		return NULL;
	ret = (uint8*)myMalloc( 13 , _FILENAME_STRING_,_FUNCTIONNAME_STRING_, _LINE_NUMBER_  );
	if( NULL == ret )
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}
	turnOneByteIntoDualHex_big_endian( *chararray,  ret );
	turnOneByteIntoDualHex_big_endian( *(chararray+1),  ret+2 );
	turnOneByteIntoDualHex_big_endian( *(chararray+2),  ret+4 );
	turnOneByteIntoDualHex_big_endian( *(chararray+3),  ret+6 );
	turnOneByteIntoDualHex_big_endian( *(chararray+4),  ret+8 );
	turnOneByteIntoDualHex_big_endian( *(chararray+5),  ret+10 );

	return ret;
}

void uint16_into_big_endian_bytes(uint16 number, uint8* buffer, uint16 buffer_len)
{
	if(buffer == NULL || buffer_len < 2)
		return ;

	*buffer = number/256;
	*(buffer+1) = number%256;
}



/*********************************************************************
 * @fn      bdAddr2Str
 *
 * @brief   Convert Bluetooth address to str with inverse order
 *
 * @return  none
 *///same with void turnOneByteIntoDualHex_big_endian(const unsigned char b, uchar* targetBuffer)

#define B_ADDR_LEN 6
//pAddr with length of B_ADDR_LEN; str with lenght of 13
void bdAddr2Str( uint8 *pAddr ,uint8 length6byte, char* str, uint8 length13bytes )
{
  if( length6byte <B_ADDR_LEN)
    return;
  
  //6*2 +1 for \0
  if(length13bytes < 13)
    return;
  
  memset(str,0,length13bytes);
  uint8       i;
  char        hex[] = "0123456789ABCDEF";
  //static char str[B_ADDR_STR_LEN];
  char        *pStr = str;
  
  //*pStr++ = '0';
  //*pStr++ = 'x';
  
  // Start from end of addr
  pAddr += B_ADDR_LEN-1;
  
  for ( i = B_ADDR_LEN; i > 0; i-- )
  {//same with android scanning
    *pStr++ = hex[*pAddr >> 4];//hight bits first 
    *pStr++ = hex[*pAddr & 0x0F];//low bits
    if(i>1)//not first one
      pAddr--;
  //void turnOneByteIntoDualHex_big_endian(const unsigned char b, uchar* targetBuffer)
  } 
  *pStr = 0;
  
 // return str;
}

uchar* reach_next_No_char( uint8* start, uint16 next_length , uchar c,  uint16 no )
{
  if( NULL == start  )
    return NULL;
  if( 0== no )
    return start;  
  
    uchar* p= start;
    while( p-start <next_length  )
    {
      if( c == *p )
      {
        no--;
        if( 0 == no )
        {
          return p;
        }
      }     
      p++;
    }    
    return NULL;
}

uint16 find_howmany_char( uint8* start, uint16 next_length , uchar c )
{
    if( NULL == start )
    return 0;
    
    uint16 i=0;
    uchar* p= start;
    while( p-start <next_length  )
    {
      if( c == *p )
      {
        i++;
      }     
      p++;
    }    
    return i;
}

#if (defined VIRTUAL_BTP) ||(defined ANDROID_BLE_PIH) || (defined IOS_BLE_PIH) || (defined  EMBEDDED_BLE_PIH) || (defined EMBEDDED_BLE_PIH_USER)|| (defined EMBEDDED_BLE_PST)||(defined EMBEDDED_BLE_PST_USER )

uint32 parse7CharsIntoDateLongS(uint8 * chararray)
{
	ItrackerDate d ;
	if( NULL == chararray )
		return 0;
	d.iYear = (*chararray) *100 + *(chararray+1);
	d.iMonth = *(chararray+2);
	d.iDay = *(chararray+3);
	d.iHour = *(chararray+4);
	d.iMin = *(chararray+5);
	d.iSec = *(chararray+6);
	return dateToSec( &d );
}

uint8* parse7CharsIntoDate(uint8 * chararray)
{
	uint8* date = (unsigned char *)myMalloc(20*sizeof(unsigned char) , _FILENAME_STRING_, _FUNCTIONNAME_STRING_,_LINE_NUMBER_ );
	unsigned char * digitals;
	if(date == NULL)
	{
#if defined _itrackerDebug_MALLOC_
		directPrintf("malloc memory fails... quit@ %s, %s, %u\n", _FILENAME_STRING_, _FUNCTIONNAME_STRING_, _LINE_NUMBER_ );
		//if non embedded, some embedded will error while printf; so should define to nothing function
#if defined _itracker_DEBUGMEMORY_
		memoryWatcherReport( "when malloc fail:" );
#endif
#endif
		return NULL;
	}
	//	memset(date, 0, 20*sizeof(char));


	digitals = (unsigned char *)oneByteIntoDecimalChars(chararray[0] , 2);
	copyCharArrayIntoBuffer(digitals,2, date); //last one for \0
	myFree(digitals);

	digitals = (unsigned char *)oneByteIntoDecimalChars(chararray[1] , 2);
	copyCharArrayIntoBuffer(digitals,2, date + 2); //last one for \0
	myFree(digitals);

	*(date + 4) = '-';//-
	digitals = (unsigned char *)oneByteIntoDecimalChars(chararray[2] , 2);
	copyCharArrayIntoBuffer(digitals,2, date + 5); //last one for \0
	myFree(digitals);

	*(date + 7) = '-';//-
	digitals = (unsigned char *)oneByteIntoDecimalChars(chararray[3] , 2);
	copyCharArrayIntoBuffer(digitals,2, date + 8); //last one for \0
	myFree(digitals);

	*(date + 10) = ' ';//space
	digitals = (unsigned char *)oneByteIntoDecimalChars(chararray[4] , 2);
	copyCharArrayIntoBuffer(digitals,2, date + 11); //last one for \0
	myFree(digitals);

	*(date + 13) = ':';//:
	digitals = (unsigned char *)oneByteIntoDecimalChars(chararray[5] , 2);
	copyCharArrayIntoBuffer(digitals,2, date + 14); //last one for \0
	myFree(digitals);

	*(date + 16) = ':';//:
	digitals = (unsigned char *)oneByteIntoDecimalChars(chararray[6] , 2);
	copyCharArrayIntoBuffer(digitals,2, date + 17); //last one for \0
	myFree(digitals);

	return date;//with length of 19
}


#endif

/*

int main()
{
	char * bString="{\"com.itracker88.tracker.common.entity.Device\":[{\"bizType\":1,\"deviceSerialNumber\":\"123456\",\"onlineTime\":0,\"deviceName\":\"summer\",\"simNumber\":\"13100000000\"}],\"com.itracker88.tracker.common.entity.Command\":[{\"commandNumber\":1,\"bizType\":1,\"randomKey\":\"adfadfdsfadierewertj\",\"deviceId\":80030}]}\0";
			//{"com.aaaa":[{"xxx":1,"yyy":"mm","sss":"nn"},{"xxx":1,"yyy":"mm","sss":"nn"}],"com.ddd.bbbb":[{"xxx":1,"yyy":"uu","ttt":"vv"}]}

	char * incr=NULL , *ret=NULL;
	Struct_Command *ccccc;


//	initMeoryWatcher();
//
//	incr = (char *)increaseQuoteInQuoteFree(bString);
//	myPrintf("bString=%s\n",bString);
//	myPrintf("incr=%s\n",incr);
//
////	myFree(incr);
////	c = &myCommand;
////
////	c->randomKey = incr;
////
////	ret = (char *)commandToJsonStr(c);
//////	myFree(incr);
////
////	myPrintf("ret=%s\n",ret);
////
////	myFree(ret);
//
//	incr = (char *)increaseQuoteInQuoteFree(incr);
//	incr = (char *)increaseQuoteInQuoteFree(incr);
//	incr = (char *)increaseQuoteInQuoteFree(incr);
//	incr = (char *)increaseQuoteInQuoteFree(incr);
//	incr = (char *)increaseQuoteInQuoteFree(incr);
////	incr = (char *)increaseQuoteInQuoteFree(incr);s
////	incr = (char *)increaseQuoteInQuoteFree(incr);
////	incr = (char *)increaseQuoteInQuoteFree(incr);
////	incr = (char *)increaseQuoteInQuoteFree(incr);
//
//
//	myPrintf("incr=%s\n",incr);
//
//	ret = (char *)decreaseQuoteInQuoteFree(incr);
//	ret = (char *)decreaseQuoteInQuoteFree(ret);
//	ret = (char *)decreaseQuoteInQuoteFree(ret);
//	ret = (char *)decreaseQuoteInQuoteFree(ret);
//	ret = (char *)decreaseQuoteInQuoteFree(ret);
//	ret = (char *)decreaseQuoteInQuoteFree(ret);
//	ret = (char *)decreaseQuoteInQuoteFree(ret);
//	ret = (char *)decreaseQuoteInQuoteFree(ret);
////	myFree(incr);
//
////	ret = (char *)formatDashesQuote(0);
//
//	myPrintf("ret=%s\n",ret);


//	ret = replaceSubstring(bString, "itracker88\0","summer\0");
//	ret = replaceSubstring("", "summer111","jenny");
//	myPrintf("ret=%s\n",ret);
////	memoryWatcherReport();//watch memory
//
//	unsigned char *rrr = intIntoFourHex(14);
//	myPrintf("rrr=%s\n",rrr);



int num=0;
char * a = myMalloc(9,0);
char * b = myMalloc(9,0);
char * c = myMalloc(9,0);
char * d = myMalloc(9,0);
char * e = myMalloc(9,0);
char * f = myMalloc(9,0);
char * g = myMalloc(9,0);
char * h = myMalloc(9,0);
char * i = myMalloc(9,0);
char * j = myMalloc(9,0);
char * k = myMalloc(9,0);
char * l = myMalloc(9,0);
char * m = myMalloc(9,0);

char aaa= 'A', bbb = '1', ccc = 'a';

for( num=0; num<9-1 ; num++)
{
	a[num] = aaa;
	b[num] = bbb;
	c[num] = ccc;
	d[num] = aaa+1;
	e[num] = bbb+1;
	f[num] = ccc+1;
	g[num] = aaa+2;
	h[num] = bbb+2;
	i[num] = ccc+2;
	j[num] = aaa+3;
	k[num] = bbb+3;
	l[num] = ccc+3;
	m[num] = ccc+4;
}
//
myPrintf("a=%s\n",a);
SKETCH*  sketch = NULL;
CAU *p = NULL;
 sketch = addLastCAU(  sketch,  909, a, 8,1, NULL);
sketch = addLastCAU(  sketch,  909, b, 8,1, NULL);
sketch = addLastCAU(  sketch,  799, c, 8,0, NULL);
sketch = addLastCAU(  sketch,  1001, d, 8,1, NULL);
sketch = addLastCAU(  sketch,  999, e, 8,0, NULL);
sketch = addLastCAU(  sketch,  9999, f, 9,4, NULL);
sketch = addLastCAU(  sketch,  9999, g, 9,0, NULL);
sketch = addLastCAU(  sketch,  899, h, 9,1, NULL);
sketch = addLastCAU(  sketch,  899, i, 9,1, NULL);
sketch = addLastCAU(  sketch,  6101, j,9, 0, NULL);
sketch = addLastCAU(  sketch,  6101, k,9, 0, NULL);
sketch = addLastCAU(  sketch,  909, l,9, 0, NULL);
sketch = addLastCAU(  sketch,  909, m, 8,1, NULL);
printAllCAU(sketch);

p = findFirstOneCAUbyDigit(sketch, 9999);
printOneCAU(p);



num= deleteCAUsbyDigit(sketch, 909);
printAllCAU(sketch);

myPrintf("num=%d\n",num);

int s = countTotalCharArrayLengthOnStateForCAU(sketch, 1);
myPrintf("s=%d\n",s);

CAU* temp = NULL;
temp = popupFirstCAU(sketch);
printOneCAU(temp);

//printAllCAU(header);
freeOneTotalCAU(temp);

myPrintf("getCAULength=%d\n",getCAULength(sketch));
//
temp = findOneCAUBySerialFromOne(sketch,0);
printOneCAU(temp);

num = deleteOneTotalCAU(sketch, temp);
myPrintf("num=%d\n",num);

myPrintf("getCAULength=%d\n",getCAULength(sketch));

num = deleteOneTotalCAU(sketch, peekLastCAU(sketch));
myPrintf("num=%d\n",num);
myPrintf("getCAULength=%d\n",getCAULength(sketch));

printOneCAU(peekLastCAU(sketch));



temp= popupLastCAU(sketch);
printOneCAU(temp);
myPrintf("getCAULength=%d\n",getCAULength(sketch));

temp= popupLastCAU(sketch);
printOneCAU(temp);
myPrintf("getCAULength=%d\n",getCAULength(sketch));


temp = findOneCAUBySerialFromOne(sketch,0);
printOneCAU(temp);

myPrintf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~length=%d~~~~~~~~~~~~~\n",getCAULength(sketch));

char * jj = myMalloc(9,0);
char * kk = myMalloc(9,0);
char * ll = myMalloc(9,0);
char * mm = myMalloc(9,0);
char * nn = myMalloc(9,0);
char * pp = myMalloc(9,0);
jj[0] = 200;
kk[0] = 201;
ll[0] = 201;
mm[0] = 'a';
nn[0] = 'A';
pp[0] = 200;

jj[7] = 200;
kk[7] = 201;
ll[7] = 201;
mm[7] = 'M';
nn[7] = 'm';
pp[7] = 200;

//sketch = addLastCAU(  sketch,  6101, jj,9, 0, NULL);
//sketch = addLastCAU(  sketch,  6101, kk,9, 0, NULL);
//sketch = addLastCAU(  sketch,  909, ll,9, 0, NULL);
//sketch = addLastCAU(  sketch,  909, mm, 8,1, NULL);
//
//printAllCAU(sketch);


//num = getCAUStates(header);
//myPrintf("num=%d\n",num);
//
//
//num = packingAllCharArray(sketch);
//printOneCAU(peekFirstCAU(sketch));
//myPrintf("num=%d\n",num);

//num = packingAllCharArrayByState(sketch, 1);
//printOneCAU(findFirstOneCAUbyState(sketch,1));
//myPrintf("num=%d\n",num);

//sketch = addLastCAUbyDigit(  sketch,1,  9999, nn, 8,1, NULL);
//temp = (findFirstOneCAUbyDigit(sketch,9999));
//printOneCAU(temp);
//
//temp = getPreviousCAU(sketch, temp);
//printOneCAUinSketch( sketch,temp);
//
//sketch = offerFirstCAU(  sketch,  1000, pp, 8,1, NULL);
//temp = peekFirstCAU(  sketch);
//printOneCAUinSketch( sketch,temp);
//
////SKETCH * copySketch = copySketchWithoutCAU(sketch);
////SKETCH * copySketch = copySketchCAUListWithoutCa(sketch);
//SKETCH * copySketch = copyTotalSketchCAUList(sketch);
//myPrintf("sketch=%x\n",sketch);
//myPrintf("copySketch=%x\n",copySketch);
//myPrintf("sketch->header=%x\n",sketch->header);
//myPrintf("copySketch->header=%x\n",copySketch->header);
//myPrintf("sketch->end=%x\n",sketch->end);
//myPrintf("copySketch->end=%x\n",copySketch->end);
//
//myPrintf("sketch->header->ca=%x\n",((CAU*)(sketch->header))->ca);
//myPrintf("copySketch->header->ca=%x\n",((CAU*)(copySketch->header))->ca);
//myPrintf("sketch->header->ca->chararray=%x\n",((CAU*)(sketch->header))->ca->chararray);
//myPrintf("copySketch->header->ca->chararray=%x\n",((CAU*)(copySketch->header))->ca->chararray);
//
//myPrintf("sketch->end->ca=%x\n",((CAU*)(sketch->end))->ca);
//myPrintf("copySketch->end->ca=%x\n",((CAU*)(copySketch->end))->ca);
//myPrintf("sketch->end->ca->chararray=%x\n",((CAU*)(sketch->end))->ca->chararray);
//myPrintf("copySketch->end->ca->chararray=%x\n",((CAU*)(copySketch->end))->ca->chararray);
//
//num = getCAULength(sketch);
//myPrintf("getCAULength=%d\n",num);
//myPrintf("reviewCAULength=%d\n",reviewCAULength(sketch));
//
//uint8* abcd = "dddd";//"aaaaaaddd";
//uint8* kkk= NULL;
//myPrintf("test = %s,,,%s----\n",kkk,abcd);
//int iiii= 100;
//myPrintf("test = %d---%d--%d--\n",iiii,iiii+2);
//
//float uuu= 56.9f , yyy=-34566.00999f;
//float * vvv= &uuu;
//
//myPrintf("test = %f,,,,%d,,,,\n",yyy, iiii);
//
//myPrintf("test = %x,,,%x,,,,,,\n",abcd,abcd);
//
//uint8* target = (uint8*)myMalloc(sizeof(uint8)*20);
//
//float dou = -345.567;
//sprintf(pp,"%f", dou);
//myPrintf("pp=%s\n",pp);

//myPrintf("charCompare=%d\n",charCompare('g' , 'g' ));

CA * ca1 = (CA*)myMalloc(sizeof(CA), selfstructTYPE);
CA * ca2 = (CA*)myMalloc(sizeof(CA), selfstructTYPE);
CA * ca3 = (CA*)myMalloc(sizeof(CA), selfstructTYPE);
CA * ca4 = (CA*)myMalloc(sizeof(CA), selfstructTYPE);
CA * ca5= (CA*)myMalloc(sizeof(CA), selfstructTYPE);

CA * ca6 = NULL;
ca1->chararray = jj;
ca2->chararray = kk;
ca3->chararray = ll;
ca1->length = 8;//space is 9 , with \0
ca2->length = 8;//space is 9 , with \0
ca3->length = 8;//space is 9 , with \0

ca4->chararray = mm;
ca5->chararray = nn;
ca4->length = 9;
ca5->length = 9;

unsigned char sign =0;
sign = caContentCompare(ca4, ca5, 0);
myPrintf("sign=%d\n",sign);

myPrintf("caIsNull=%d\n",caIsNull(ca5));

printOneCA("ca4:",ca4);
printOneCA("ca5:",ca5);


CA * ca10 =appendCharArrayWithRemalloc(ca4->chararray, ca4->length,  ca5->chararray  , ca5->length ,1 );
printOneCA("ca10:",ca10);

ca4->length = 0;

ca10 = appendCAWithRemalloc(ca4,ca5, 1);
printOneCA("ca10:",ca10);






	return 0;
}
*/
#if 0
int main()
{

	set_win_print_fun( printf );
	uint64 mac_num1 = 0, mac_num2=0, mac_num3=0, mac_num4=0;
	uint8 * mac1 = "A3-4B-0C-0D-EE-FF";
	uint8 * mac2 = "00:4B:0C:0D:EE:FF";
	uint8 * mac3 = "A3 4B 00 0D EE FF";
	uint8 * mac4 = "A34B0C0DEE00";
	//big endian

	CA * ca = (CA*)myMalloc( sizeof( CA ),  _FILENAME_STRING_, _LINE_NUMBER_ );
	ca->chararray = "0123456789abcdefghijklmn";//24
	ca->length = strLength( ca->chararray )-1;
	printOneCA("ca=", ca );

	uint16 offset=0;
	uint16 old_length=29;
	uint8* new_part="ABCDE";
	int16 new_part_length=0;

	CA* new_ca = replacePartOfCA( ca,  offset,  old_length,  new_part,  new_part_length );
	printOneCA("new_ca=", new_ca );
	memoryWatcherReport("end ");
return 0;
}
#endif
