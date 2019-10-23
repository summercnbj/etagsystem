#include "itrackerWinPrintf.h"


//the following is for va_list
#include<stdio.h>
#include <stdarg.h>

/*
//#define FORMATSTRINGLEN 100
#if defined MTK_TERMINAL

#include "drv_comm.h"   //for dbg_print()
void myDbg_print(const char * fmt,...)
{
	va_list ap;
	int i=0;
	char string[4096] ;
	memset(string,0, 4096);


	 for(;i < 4096; i++)
	 {
	    string[i] =0;
	 }


	   if(NULL == fmt)
	   {
		  dbg_print((const char*)nullstring);
	      return;

	   }


	va_start(ap,fmt);
	    //if NULL how to do ????
	vsprintf(string,fmt,ap);
	va_end(ap);

	dbg_print(string);
}
#endif*/



/**********************************************************
Description : Convert an integer as string.
Input       : Buffer pointer, value to convert.
Output      : Non
***********************************************************/

void my_itoa( char **buf, uint32 i, uint32 base)
{//max is UINT32
   char *s;

   uint32 rem;
   char rev[MY_ITOA_BUFFERLEN+1];

   rev[MY_ITOA_BUFFERLEN] = 0;
   if (i == 0)
   {
      (*buf)[0] = '0';
      ++(*buf);
      return;
   }
   s = (char*)&rev[MY_ITOA_BUFFERLEN];
   while (i)
   {
      i = my_BL_SLIM_UDIV_R(i, base, rem);
      if (rem < 10)
         *--s = rem + '0';
      else if (base == 16)
         *--s = "abcdef"[rem - 10];
   }
   while (*s)
   {
      (*buf)[0] = *s++;
      ++(*buf);
   }
}

void my_itoa64( char **buf, uint64 i, uint64 base)
{//max is UINT32
   char *s;

   uint64 rem;
   char rev[MY_ITOA_BUFFERLEN+1];

   rev[MY_ITOA_BUFFERLEN] = 0;
   if (i == 0)
   {
      (*buf)[0] = '0';
      ++(*buf);
      return;
   }
   s = (char*)&rev[MY_ITOA_BUFFERLEN];
   while (i)
   {
      i = my_BL_SLIM_UDIV_R(i, base, rem);
      if (rem < 10)
         *--s = rem + '0';
      else if (base == 16)
         *--s = "abcdef"[rem - 10];
   }
   while (*s)
   {
      (*buf)[0] = *s++;
      ++(*buf);
   }
}

/**********************************************************
Description : Convert floating point to string.
Input       : Buffer pointer, value to convert.
Output      : Non
***********************************************************/

void my_itof( char **buf, int32 i)
{
   char *s;

   int32 rem, j;
   char rev[MY_ITOA_BUFFERLEN+1];

   rev[MY_ITOA_BUFFERLEN] = 0;
   s = (char*)&rev[MY_ITOA_BUFFERLEN];
   for (j= 0 ; j < my_NumFract ; j++)
   {
      i = my_BL_SLIM_UDIV_R(i, 10, rem);
      *--s = rem + '0';
   }
   while (*s)
   {
      (*buf)[0] = *s++;
      ++(*buf);
   }
}


void turnIntIntoDecStr( int32 val, char* buffer , uint16 buffer_length )
{
    uint32 b = val>0?val:(-val);
    if( buffer_length > MY_ITOA_BUFFERLEN )
      buffer_length = MY_ITOA_BUFFERLEN;

    char* start = buffer; //buffer's value is changed by my_itoa(). so shuld remember it now.

    my_itoa( (char**)&buffer, b, 10 );
//    printf("buffer=%s\n",start);
    if( val<0 )
    {
      char * t= start;
      while( *t && t-start < buffer_length-1 )
      {//stop at '\0' or the final one in temp
        t++;
      }

      while( t>start )
      {
        *t = *(t-1);
        t--;
      }
      *t = '-';//nagative
//      *t = '\0';//nagative

      *(start + buffer_length-1) = 0;//always
    }
//    printf("buffer=%s\n",start);
}


void turnInt64IntoDecStr( int64 val, char* buffer , uint16 buffer_length )
{
    uint64 b = val>0?val:(-val);
    if( buffer_length > MY_ITOA_BUFFERLEN )
      buffer_length = MY_ITOA_BUFFERLEN;

    char* start = buffer; //buffer's value is changed by my_itoa(). so shuld remember it now.

    my_itoa64( (char**)&buffer, b, 10 );
//    printf("buffer=%s\n",start);
    if( val<0 )
    {
      char * t= start;
      while( *t && t-start < buffer_length-1 )
      {//stop at '\0' or the final one in temp
        t++;
      }

      while( t>start )
      {
        *t = *(t-1);
        t--;
      }
      *t = '-';//nagative
//      *t = '\0';//nagative

      *(start + buffer_length-1) = 0;//always
    }
//    printf("buffer=%s\n",start);
}


#if defined  _itrackerDebug_

//#if defined SKETCH_THREADS
//static pthread_mutex_t mutex_winprintf;
//
//void init_mutex_winprintf()
//{
//	pthread_mutex_init( &mutex_winprintf, NULL );
//}
//
//#endif

static volatile my_print_fun_t my_print_fun = NULL;
void set_win_print_fun (my_print_fun_t f )
{
  my_print_fun = f;
}


//#include "I:\61D\summer6261D\11CW1352MP_JOYA61D_CN_11C_V14_GPRS_MMI\tools\MinGW\include\varargs.h"   //in mmi_app.mak : INC_DIR += tools\MinGW\include
//printf chanot print NULL to %s in modis

// cannot has more % than args
// float can only use one in a sentence!!
void winPrintf(const char * fmt,...)
{//should be locked




	va_list ap;
	char target[ FORMATSTRINGLEN];  //appendWatcherUnitWhenAlloc will looping call this, error
	char* bp = target;

	double dval;
	int32 ival;

	char *p =NULL;
	char *sval=NULL;
	int last_l =0;


	//int len =0;

	memset( target, 0,  FORMATSTRINGLEN );
	if(fmt == NULL)
	{
#if defined _itrackerDebug_
          if( my_print_fun )
            my_print_fun( "fmt is NULL\r\n" );

#endif

//#if defined SKETCH_THREADS
//		my_unlock_mutex(&mutex_winprintf);
//#endif
		return ;
	}
	va_start(ap,fmt);//ap has got the first

	for ( p= (char*)fmt; *p && (bp-target < FORMATSTRINGLEN-11 ); p++ )
	{//11 is for nonstring length

		if( 0 == last_l )
		{
			if (*p != '%'  )
			{
			  if( bp - target < FORMATSTRINGLEN )
				*bp++= *p;

				continue;
			}
			else
			{
				p++;//skip %
			}
		}
		else
		{
		}

		//label:
		switch ( *p )
		{
		case 'd':

			if( 0 == last_l )
			{//d for int16
				int16 val ;
				val= va_arg(ap, int );//signed or unsigned in mingw error
				if (val < 0)
                {
                    if( bp - target < FORMATSTRINGLEN )
					*bp++= '-';

					 val= -val;
				}
				if( bp - target + 10 < FORMATSTRINGLEN )
				  my_itoa (&bp, val, 10);
			}
			else if( 1 == last_l )
			{//ld for int32
				int32 val = va_arg(ap, long );//signed or unsigned in mingw error
				char temp[MY_ITOA_BUFFERLEN+2];
				char* t =temp;
				memset(temp,0,22);
#if 0
                                sprintf((char*)temp,"%ld",val);// long
#else
                                turnIntIntoDecStr( val, temp , MY_ITOA_BUFFERLEN+2 );
#endif


				//ld mtk modis, but right in mingw eclipse lld
				for (  ; (t && *t) ; t++ )
				{
                   if( bp - target < FORMATSTRINGLEN )
					*bp++= *t;
				}
			}
			else
			{//lld for int64
				int64 val = va_arg(ap, long long );//signed or unsigned in mingw error
				char temp[22];
				char* t =temp;
				memset(temp,0,22);


//				sprintf((char*)temp,"%lld",val);//unsigned long
				turnInt64IntoDecStr( val, temp , MY_ITOA_BUFFERLEN+2 );

				//ld mtk modis, but right in mingw eclipse lld
				for (  ; (t && *t) ; t++ )
				{
                    if( bp - target < FORMATSTRINGLEN )
					*bp++= *t;
				}

			}

			last_l = 0;
			break;

		case 'u':

			if( 0 == last_l )
			{//u for uint16
				uint16 uval;
				uval= va_arg(ap, int );//signed or unsigned in mingw error

                if( bp - target +10 < FORMATSTRINGLEN )
				my_itoa (&bp, uval, 10);
			}
			else if( 1 == last_l )
			{//lu for uint32
				uint32 val = va_arg(ap, long );//signed or unsigned in mingw error
				char temp[22];
				char* t =temp;
				memset(temp,0,22);
				sprintf((char*)temp,"%lu",val);//unsigned long
				//lu mtk modis, but right in mingw eclipse llu
				for (  ; (t && *t) ; t++ )
				{
                   if( bp - target < FORMATSTRINGLEN )
					*bp++= *t;
				}
			}
			else
			{//llu for uint64
				uint64 val = va_arg(ap, long long );
				char temp[22];
				char* t =temp;
				memset(temp,0,22);
				sprintf((char*)temp,"%llu",val);//unsigned long
				//lu mtk modis, but right in mingw eclipse llu
				for (  ; (t && *t) ; t++ )
				{
                    if( bp - target < FORMATSTRINGLEN )
					*bp++= *t;
				}
			}

			last_l = 0;
			break;

		case 'o':
			ival= va_arg(ap, int);
			if (ival < 0)
			{
			  if( bp - target < FORMATSTRINGLEN )
				*bp++= '-';
				 ival= -ival;
			}
			if( bp - target < FORMATSTRINGLEN )
			  *bp++= '0';

			if( bp - target +8 < FORMATSTRINGLEN )
			  my_itoa (&bp, ival, 8);
			last_l = 0;
			break;

		case 'x':
			ival= va_arg(ap, unsigned int );
#if 0
			if (ival < 0)
			{
			  if( bp - target < FORMATSTRINGLEN )
				 *bp++= '-';
                          ival= -ival;
			}
#endif
			if( bp - target+16 < FORMATSTRINGLEN )
			{
			  my_itoa (&bp, ival, 16);
			}
			last_l = 0;
			break;
		case 'X':  //will preadd 0x than 'x'
			ival= va_arg(ap, unsigned int );
#if 0
			if (ival < 0)
			{
			  if( bp - target < FORMATSTRINGLEN )
				 *bp++= '-';
                          ival= -ival;
			}
#endif
			if( bp - target < FORMATSTRINGLEN )
			  *bp++= '0';
			if( bp - target < FORMATSTRINGLEN )
			  *bp++= 'x';
			if( bp - target+16 < FORMATSTRINGLEN )
			  my_itoa (&bp, ival, 16);
			last_l = 0;
			break;
		case 'c':
			{
			  char cval;
			  cval= va_arg(ap, int);
			  if( bp - target < FORMATSTRINGLEN )
				*bp++= cval;
			}
			last_l = 0;
			break;

		case 'f':
			{
				int fract;
				dval= va_arg(ap, double);
				if (dval < 0)
				{
				  if( bp - target < FORMATSTRINGLEN )
					*bp++= '-';
				  dval= -dval;
				}
				if (dval >= 1.0)
				{
				  if( bp - target +10 < FORMATSTRINGLEN )
					my_itoa (&bp, (int)dval, 10);
				}
				else
				{
				  if( bp - target < FORMATSTRINGLEN )
					*bp++= '0';
				}

				if( bp - target < FORMATSTRINGLEN )
				  *bp++= '.';

				fract= (int)((dval- (double)(int)dval)*(double)(my_MAXFRACT));

				if( bp - target+20 < FORMATSTRINGLEN )
				  my_itof(&bp, fract);
			}
			last_l = 0;
			break;

		case 'l':
			last_l++;
			//goto label;
			break;

		case 's':  //if NULL , va_arg(ap, char* ) will get invalid pointer
			{

				sval = (char*)va_arg(ap, char* );


				//printf("%x,",sval);
				if( NULL == sval)
					sval = (char*)nullstring;
				for (  ; ( *sval && bp-target < FORMATSTRINGLEN ) ; sval++ )
				{
					//kk++;
					//printf("%d,",kk);

					*bp++ = *sval;
				}
			}
			last_l = 0;
			break;
		default :
			if( my_print_fun )
			  my_print_fun("Invalid control format\r\n");
			last_l = 0;
			break;
		}
	}

	//len = (unsigned short)(bp - target);
	va_end(ap);

	if( bp - target < FORMATSTRINGLEN )
	  *bp= 0;
	else
	  target[FORMATSTRINGLEN -1] =0;


//to printf((uint8*)target)




//#if defined SKETCH_THREADS
//		pthread_mutex_lock (&mutex_winprintf);
//#endif


#if defined _itrackerDebug_
//    MACRO_PRINTF((uint8*)target);//write into stdout_printf and  debugfile
#endif


//#if defined SKETCH_THREADS
//		my_unlock_mutex(&mutex_winprintf);
//#endif


#if 0
	if( my_print_fun )
	  my_print_fun( target );


		fflush(stdout);
#endif
	//printf(target);
}




#endif
