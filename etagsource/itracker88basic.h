#ifndef _itracker88basic_
#define _itracker88basic_



#include "itrackerMemory.h"
//#include "itrackerString.h"
//#include "itrackerCharArray.h"
//
//#if defined (_itracker_DEBUGMEMORY_ )
//	#include "itrackerMemoryWatcher.h" //debug memory
//#endif
//
//
//#include "itrackerChecksum.h"
//  #include "itrackerDictionary.h"  //string constant


#define CHAR_UNDERLINE '_'
#define CHAR_UNDERLINE_WCHAR L'_'
#define EXTENSION_SEPERATOR '.'
#define EXTENSION_SEPERATOR_WCHAR L'.'
#if defined WIN32
#define CHAR_COLON ':'
#define PATH_SEPERATOR  '\\'
#define CHAR_COLON_WCHAR L':'
#define PATH_SEPERATOR_WCHAR  L'\\'
#else
#define PATH_SEPERATOR '/'
#define PATH_SEPERATOR_WCHAR L'/'
#endif





#define TEMP_FILENAME_APPENDIX "_tmp"
#define DEBUG_FILENAME_APPENDIX "_debug"
#define TEMP_FILENAME_APPENDIX_WCHAR L"_tmp"
#define DEBUG_FILENAME_APPENDIX_WCHAR L"_debug"





//typedef unsigned char U8;


	#define cmdseconds 10
	//90 seconds

	#define redoWhenSocketBusy 10*1000
	//10 seconds





//extern int commandNumberInSending;  //in disposeMsg.c
//extern int lock_commandNumberInSending ;


//extern int internetAccess;
//extern int redoDelay_ms ;   //in socket.c





/*  timer used in itracker project
 *
 * GIS_TIMER_ID_0   for led_start0; see powermanage.c line87
 * GIS_TIMER_ID_1   for led_start1; see powermanage.c line124
 *
 * GIS_TIMER_ID_2	for login() and sendingcmd() because of commandNumberInSending !=0
 * GIS_TIMER_ID_3   for sendOneLocation() because of commandNumberInSending !=0
 * GIS_TIMER_ID_4   for CMD5_itGetDeviceConfig because of commandNumberInSending !=0
 * GIS_TIMER_ID_5   for cancelServerCMD8 because of commandNumberInSending !=0
 * GIS_TIMER_ID_6   for devicestateservice.c  because of commandNumberInSending !=0
 * GIS_TIMER_ID_7   for startItrackerLogin in itrakcerlogin.c
 
 
 * GIS_TIMER_ID_11  for cancelServerCMD16
 * GIS_TIMER_ID_12  for gpsservicemain idle timer; see gpsservice.c 
 * GIS_TIMER_ID_13  for socket timeout in sendBySocket(): StartTimer(GIS_TIMER_ID_13,SO_TIMEOUT,itrackerCloseSingleSocket);
 * GIS_TIMER_ID_14  
 * GIS_TIMER_ID_15  for if is connecting when timeout in itrackerCloseSingleSocket():StartTimer(GIS_TIMER_ID_15,redoDelay_ms*1000,redoWithoutNotifyConn);
 * GIS_TIMER_ID_16  for any redo in redoBusinessWhenFail():StartTimer(GIS_TIMER_ID_14,(SO_TIMEOUT+redoDelay_ms)*1000,redobusiness);
 * GIS_TIMER_ID_17  for SOS_CancelTimeout waiting for possible cancel by pwrkey
 * GIS_TIMER_ID_18  for readSystemDataContinue for test on time only
 * GIS_TIMER_ID_19  for for isRechargingLed0Flashing in powermanage.c

*/
	






//#include <stdio.h>  //for NULL
//#include <stdlib.h>  //for malloc and free
//#include <string.h>  //for memset



















//extern void redoBusinessWhenFail(void);

#endif
