/*
 * itrackerWinPrintf.h
 *
 *  Created on: Oct 13, 2016
 *      Author: gracestar
 */

#ifndef ITRACKERWINPRINTF_H_
#define ITRACKERWINPRINTF_H_

#include "itracker88Platform.h"
#include "itracker88basic.h"
//#include "itrackerDebugUtils.h"
#define nullstring  (const uchar*)"<null>"


//#define MAXCHARS	512
#define my_MAXFRACT    	10000
#define my_NumFract        4
#define my_BL_SLIM_UDIV_R(N, D, R) (((R)=(N)%(D)), ((N)/(D)))

   
#define MY_ITOA_BUFFERLEN   20
extern void my_itoa( char **buf, uint32 i, uint32 base);
extern void my_itof( char **buf, int32 i);
extern void turnIntIntoDecStr( int32 val, char* buffer , uint16 buffer_length );

#if defined  _itrackerDebug_    //donot use _itrackerDebug_itrackerString_
#if defined SKETCH_THREADS
#include "itrackerThreadUtils.h"
//#include <pthread.h>
extern void init_mutex_winprintf();
#endif
//typedef int (* my_print_fun_t )(const char* );
//#include <stdarg.h>
#define FORMATSTRINGLEN  100
extern void winPrintf(const char * fmt,...);

#if defined _PST_DEBUG_ || defined _itrackerDebug_EMBEDDED_BLE_PIH_
//typedef int (* my_print_fun_t )(const char* );//defined here ;others define in itracker88Platform.h
#endif 

extern void set_win_print_fun (my_print_fun_t t);
#endif







#endif /* ITRACKERWINPRINTF_H_ */
