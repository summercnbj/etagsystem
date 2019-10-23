/*
 * itrackerCharArray.h
 *
 *  Created on: 2014骞�10鏈�20鏃�
 *      Author: summer
 */

#ifndef ITRACKERCHARARRAY_H_
#define ITRACKERCHARARRAY_H_

#include "itracker88Platform.h"
#include "itrackerWinPrintf.h"
	//#define CA_EXPANSION_STATE  1
	//#define CA_EXPANSION_DIGIT  1
	//#define CA_EXPANSION_ANYINSTANCE  1


#if defined _itrackerDebug_ && !defined ITRACKER_JNI
//#define _itrackerDebug_CA_
#endif






struct CharArray
{
	unsigned char * chararray;
	uint16 length;

#if defined CA_EXPANSION_STATE
	uint8 state;//typically 0 and 1,2...
#endif //CA_EXPANSION_STATE
#if defined CA_EXPANSION_DIGIT
	uint32 digit;
#endif //CA_EXPANSION_DIGIT
#if defined CA_EXPANSION_ANYINSTANCE
	void *anyInstance;
#endif//CA_EXPANSION_ANYINSTANCE

};
typedef struct CharArray CA;

extern itr_bool chararrayIsZero( uint8* chararray, uint16 length );
extern void copyRearCharArrayIntoFixedLengthBuffer( uint8* chararray, uint16 length, uint8* buffer, uint16 buffer_length  );


extern void freeOneTotalCA(CA *oneca);


#if defined _itrackerDebug_ && !defined ITRACKER_JNI
//in ITRACKER_JNI, use print_chararray_btp_log as printCharArray
extern void printCharArray( char *memo, const unsigned char * src, uint16 length);
#endif //#if defined _itrackerDebug_ && !defined ITRACKER_JNI

#if defined _itrackerDebug_
extern void printOneCA( const char * note,CA * ca);

#endif

extern char valueIntoHexChar( uint8 value );
extern int8 getHexValueFromSingleLiteralChar(unsigned char ch);//'7' --> 7   , 'B' --> 11, 'F' --> 15

extern int8 getUint32FromHexChars_BigEndian( uint32* to_save, unsigned char* hexes, uint8 length );

extern itr_bool findStringInCharArray( const uint8* chararray, uint16 length );

//extern int dualCharsToInt(unsigned char first, unsigned char second);

//gracestar will compensate ' '; standard compensate 0
extern uint32 charArraySumToInt(const unsigned char* src, uint16 length, char odd_compensate );//in checksum
extern uint32 dualCharsToInt(unsigned char firstChar, unsigned char secondChar);//'8','9'(hex) --> 137

extern void fillHighEndZeroCharOnCharArray(unsigned char *src, uint16 srcLength, uint16 actualLength );//"89 " --> "089"

//byteBuffer should has length > (length/2 )
extern void hexStringIntoByteBuffer_little_endian( const uint8* hexString, uint16 length, uint8* byteBuffer ,uint16 bufferLength );
extern void hexStringIntoByteBuffer_small_endian( const uint8* hexString, uint16 length, uint8* byteBuffer ,uint16 bufferLength );
extern unsigned char dualHexIntoByte_big_endian(const unsigned char * hexChars);//"8A" --> 138
extern unsigned char dualHexIntoByte_little_endian(const unsigned char * hexChars);
extern unsigned char *oneByteIntoDualHex(const unsigned char b);// 138 --> "8A"; 8 --> "08"
extern void turnOneByteIntoDualHex_big_endian(const unsigned char b, uchar* targetBuffer);// 138 --> "8A"; 8 --> "08"

extern void turnOneUint16IntoHexChar( uint16 data, uint8* targetBuffer, uint8 buffer_length );//high byte first, high 4-bits first
extern void turnOneUint32IntoHexChar( uint32 data, uint8* targetBuffer, uint8 buffer_length  );//high byte first, high 4-bits first
extern void turnOneUint64IntoHexChar( uint64 data, uint8* targetBuffer, uint8 buffer_length  );//high byte first, high 4-bits first

extern void uint32ArrayIntoHex( uint32* data, uint32 length, uint8* targetBuffer );//need length*8

extern unsigned char *intIntoFourHex( uint32 num);//8970 --> "230A"; 9 --> "0009";  14 --> "000E"

//digits: how many bits;  should <=3.  digitals should < 256
extern unsigned char decimalCharsIntoOneByte(const unsigned char *digitals,  char digits);//"098" --> 98
extern unsigned char * oneByteIntoDecimalChars(unsigned char srcNumber,  char digits);//98 --> "098"

//if NULL return -1; if all value return 1; if someone not this value return 0
extern int8 checkAllSameValue(uint8 * chararray, uint64 length, uint8 value );

//text_length is from text to the end of text, maybe without \0; return the next space after nex whole word. if reach the end of text, return NULL
extern uchar* copyNextWholeWordInText( uchar* text, uint16 text_length, uchar* buffer, uint8 buffer_length );

extern float sixCharIntoFloat(uint8* fnum, uint8 length);
extern unsigned char *floatInto6Char(float d);

extern char toLower(char c);
extern char toUp(char c);
extern unsigned char checkFormatOnChar(unsigned char c, unsigned char format);//if the char is the format , the function will return 0



extern uint16 formInt16(uint8 CN_MSB, uint8 CN_LSB);
extern uint8 getMSB(uint16 num);
extern uint8 getLSB(uint16 num);

extern int8 checkHexFormat( uint8 character );


//A3-4B-0C-0D-EE-FF
//A3:4B:0C:0D:EE:FF
//A3 4B 0C 0D EE FF
//A34B0C0DEEFF
//big endian
extern uint8* parseFormatHexMacIntoCharArraySix( uint8* mac, uint8 length );

extern void MacSixIntoMac12HexChar( uint8 *pAddr ,uint8 length6byte, uint8* str, uint8 length13bytes );
extern uint8* parseCharArraySixIntoMac12HexChar( uint8* mac , uint8 length );//into 12 char + 1 for \0

extern void uint16_into_big_endian_bytes(uint16 number, uint8* buffer, uint16 buffer_len);

extern void bdAddr2Str( uint8 *pAddr ,uint8 length6byte, char* str, uint8 length13bytes );

//the following is format for checkFormatOnChar()

	#define PURE_DIGIT_NUMBER 1

	#define PURE_DIGIT_NUMBER_OR_DOT 2

	#define FIRST_DIGIT_NUMBER 3

	#define FIRST_DIGIT_NUMBER_OF_INT 4

	#define FIRST_DIGIT_NUMBER_OF_UINT 5

	#define ENGLISH_EMAIL_CHAR 6

	#define ENGLISH_NAME_CHAR 7

	#define PRINTABLE_CHAR 8

	#define DATE_CHAR 9
//2014-12-12 02:33:12

	#define HEX_CHAR 10





extern CA* trimCAFree(CA* oneca);
extern CA* trimCA(CA* ca);
extern CA* trimCharArray(const uint8* chararray, uint16 length);
extern CA* trimCharArrayFree(uint8* chararray, uint16 length);
extern unsigned char *copyCharArray(const unsigned char * source, uint16 length);
extern void copyCharArrayIntoBuffer(const unsigned char * source,  uint16 length, unsigned char * target);
extern void copyCharArrayIntoBufferWithLimit(const unsigned char * source,  uint16 length, unsigned char * target, uint16 length_limit);
extern void copyStringIntoBufferWithLimit(const unsigned char * string, unsigned char * target, uint16 length_limit);


extern CA* replacePartOfCA(CA* ca, uint16 offset, uint16 old_length, uint8* new_part, uint16 new_part_length );

extern uint8 charCompare(char c1, char c2);//0 is same; 2 is same without capital cared; 1 is different
extern void appendCharArrayWithoutRemalloc(uint8* chArr1, uint16 chArr1_len, uint8 * chArr2, uint16 chArr2_len);

//trim0ofFormer: 0 is donot trim the former chararray; 1 is trimming one ending \0 of the former chararray; 2 is trimming all ending \0
extern CA* appendCharArrayWithRemalloc(uint8* chArr1, uint16 chArr1_len, uint8 * chArr2, uint16 chArr2_len, uint8 trim0ofFormer);
//trim0ofFormer:0 is donot trim the former chararray; 1 is trimming one ending \0 of the former chararray; 2 is trimming all ending \0
extern CA* appendCAWithRemalloc(CA * ca1, CA * ca2, uint8 trim0ofFormer);


extern uint8 chararrayCompare(const uint8* chararray1, uint16 length1, const uint8* chararray2, uint16 length2, uint8 supportTrim);//0 is same; 1 is different;  2 is same without capital cared
extern uint8 caContentCompare(CA * ca1, CA * ca2, uint8 supportTrim);//0 is same; 1 is different;  2 is same without capital cared
extern itr_bool caIsNull(CA* oneca);//itr_true if ca is null or chararray  null or length not 0

extern int32 matchCharArray(const uint8* src_chararray, uint16 src_length ,const uint8* sub_chararray, uint16 sub_length );

//filter out all the char not complied with the format
extern unsigned char * filterCharArray(unsigned char * chararray,unsigned char arraysize, unsigned char format);

extern CA* upgradeCharArrayInQuote(uint8* source, uint16 length);//return new malloc ca and chararray; without free source
extern CA* degradeCharArrayInQuote(uint8* source, uint16 length);//return new malloc ca and chararray; without free source

extern itr_bool checkAllSpecialChar(const uint8* chararray, uint16 length, uint8 oneSpecialChar);


//write date into this address , without malloc//"2015-11-12 10:02:33" --> 20 15 11 12 10 02 33
extern void writeDateInto7Chars(unsigned char * date, uint16 length, unsigned char * targetAddress);

//if NULL return itr_true
extern itr_bool checkAllZero(uint8 * chararray, uint16 length);

extern void myMemCopy(void * source, void *target, uint16 len);
extern void myMemset(void * memAddr, uint8 value, uint16 len);

extern uchar* reach_next_No_char( uint8* start, uint16 remaining_length , uchar c,  uint16 no );
extern uint16 find_howmany_char( uint8* start, uint16 next_length , uchar c );


#if (defined VIRTUAL_BTP) ||(defined ANDROID_BLE_PIH) || (defined IOS_BLE_PIH) || (defined  EMBEDDED_BLE_PIH) || (defined EMBEDDED_BLE_PIH_USER)|| (defined EMBEDDED_BLE_PST)||(defined EMBEDDED_BLE_PST_USER )
#include "itrackerDateTime.h"
extern uint32 parse7CharsIntoDateLongS(uint8 * chararray);
extern uint8* parse7CharsIntoDate(uint8 * chararray);//into chararray of 19 , with \0, total 20
#endif

#endif /* ITRACKERCHARARRAY_H_ */
