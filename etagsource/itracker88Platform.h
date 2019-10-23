#ifndef ITRACKER88PLATFORM_H_
#define ITRACKER88PLATFORM_H_





//#define DLL_GENERATE 1

#if defined (DLL_GENERATE)

	#define	DLL_EXTERNC  extern "C" _declspec(dllexport)
	#define DLL_EXTERNC_HEADER extern "C" _declspec(dllexport)

	#include "Windows.h"
	#define MFC_WIN32   //WINDOWS JAVA should general dll 
#else
	#define DLL_EXTERNC
	#define DLL_EXTERNC_HEADER extern
#endif


//select biz type:
//	#define ITRACKER_LEARNING 1
//	#define ITRACKER_SPORTING 1
//#define ITRACKER_HEALTH
//#define ITRACKER_FRAMEWORK



//choose one of the following

//for ble in windows, or in server java
//	#define VIRTUAL_LTP 1
//	#define VIRTUAL_BTP 1
	#define _itrackerDebug_WIN32_  1
//	#define WIN32 1
//	#define _itracker_DEBUGMEMORY_  1
//	#define MULTI_THREADS

//#define NORDIC_nRF52832_BROADCASTER_OBSERVER
//#define _PST_DEBUG_ 1

#if defined CC2541 || defined CC2540 || defined CC2640
//#if  0
//
////for real ble pst
//	#define EMBEDDED_BLE_PST 1
//        #define _C_BTP_CHANELS_ 1
//        #define _PST_DEBUG_ 1
//	#define  _PST_TEST_ 1
//        //#define BOND_PASSCODE_TT_TT 1
//#else
////for EMBEDDED ble pih
//			#define EMBEDDED_PLATFORM 1
//          #define EMBEDDED_BLE_PIH 1
//#define EMBEDDED_BLE_PIH_USER 1
//          #define _C_BTP_CHANELS_ 1   // or _SIMPLEBLECENTRAL_
//          #define IOS_BLE_PIH 1
//	  #define _itrackerDebug_EMBEDDED_BLE_PIH_ 1
//          #define itracker_IW6681 1
//	  //#define I2C_SLAVE_LTP 1
//          #define _PIH_TEST_
//#endif
#endif //

//for iOS

//	#define IOS_PLATFORM 1
//	#define IOS_BLE_PIH 1
//	#define _itracker_DEBUGMEMORY_  1
	#define _itrackerDebug_IOS_BLE_PIH_ 1
//	#define MULTI_THREADS
//  #define IOS_CARITL
//	#define P2P_SERVER



//for Android
//	#define ANDROID_PLATFORM 1
//	#define ANDROID_BLE_PIH 1
//	#define ITRACKER_JNI
//	#define _itrackerDebug_ANDROID_ 1
//	#define MULTI_THREADS

//for mtk itracker
//	#define MTK_TERMINAL 1
	//#define I2C_MASTER_LTP 1
//	#define ITRACKER_LEARNING 1
//	#define ITRACKER_SPORTING 1
//	#define EMBEDDED_BLE_PIH_USER 1
//	#define _itrackerDebug_MTK_TERMINAL_ 1
//	#define _itracker_DEBUGMEMORY_  1
	//if in MODIS, WIN32 will be true automatically
//	#define iTIMEZONE_RELEASE  TIMEZONE_BEIJING//E8 or GMT+8 or UTC+8 ; possible changed by product setup



//for java lib
//#define ITRACKER_JNI
//#define _itrackerDebug_JAVA_SERVER
//#define P2P_SERVER
//#define MULTI_THREADS


//for nuvoton MINI58
//#define NUVOTON_MCU_MINI58
//#define _itrackerDebug_NUVOTON_MCU_MINI58
//#define ITL9001
//#define CARITL_1_3
//#define CARITL_5_0
//#define CARITL_7_0
//#define IHL
//#define CARTURNSIMULATOR7_20
#if (defined ITL9001 || defined CARITL_1_3 || defined CARITL_5_0 || defined CARITL_7_0) && !defined CARTURNSIMULATOR7_20
#define I2C_MASTER
#define GPS_BOARD
#endif



//timers
#if defined MULTI_THREADS
#define TIMERS_BY_THREADS
#define SIMULATING_SINGLE_TIMER_BY_THREAD
#endif

#if defined IOS_PLATFORM || defined ANDROID_PLATFORM || \
(!defined MFC_WIN32 && !defined MTK_TERMINAL && !defined EMBEDDED_BLE_PST && !defined EMBEDDED_BLE_PIH && !defined NUVOTON_MCU_MINI58)
	//#define LINUX_SINGLE_TIMER
#endif


#define JNI_VERSION_1_1   0x00010001
#define JNI_VERSION_1_2   0x00010002
#define JNI_VERSION_1_4   0x00010004
#define JNI_VERSION_1_6   0x00010006

	#define CA_EXPANSION_STATE  1
	#define CA_EXPANSION_DIGIT  1
	#define CA_EXPANSION_ANYINSTANCE  1


//in mtk, typedef cannot been included by other headers

	#define itr_bool unsigned char
	#define uint8 unsigned char
	#define sint8 signed char
	#define int8 signed char
	#define uchar unsigned char
	#define schar signed char
	#define uint16 unsigned short
	#define int16 signed short
	#define uint32 unsigned long  //%lu to print unsigned long int
	#define int32 signed long  // %ld to print long int;
	#define int64 long long int  //%lld to print long long int;
	#define uint64 unsigned long long int  //  %llu to print unsigned long long int

//typedef struct array64bit
//{
//	uint8 data[8];
//}uint64_chararray;

	#define itr_true 1
	#define itr_false 0

	#define TIMEZONE_BEIJING 8  //E8 or GMT+8 or UTC+8
	#define iTIMEZONE_CLOUD  TIMEZONE_BEIJING  //E8 or GMT+8 or UTC+8
	#define BEIJING_TIME_ZONE_DOUBLE ((+8)*2)   //E8 or UTC+8

#define PTHREAD_MUTEX_TRYINGLOCK_WAITING_MAX_ms 10
#define PTHREAD_MUTEX_TRYINGLOCK_WAITING_MAX_us 10000

#define PTHREAD_MUTEX_TRYINGLOCK_WAITING_MIN_ms 2    //only for timerByThread use
#define PTHREAD_MUTEX_TRYINGLOCK_WAITING_MIN_us 2000 //only for timerByThread use



#if !defined ITRACKER_JNI
//#define _ITRACKER_MAIN_
#endif
#define _LOCAL_P2P_TEST_

#define ITRACKER_TEST
#define ITRACKER_STUB_SUPPORT
#define ITRACKER_MOCK_SUPPORT
#define ITRACKER_TEST_by_P2P
//debug--------------------automatically--------------------------------------------

#if defined MTK_TERMINAL
#define my_fs_open FS_Open 
#define my_fs_seek FS_Seek  
#define my_fs_read FS_Read  
#define my_fs_write FS_Write
#define my_fs_close FS_Close
#define my_fs_createdir FS_CreateDir
#define my_fs_delete FS_Delete
#define wchar_t WCHAR
#endif


#if defined  _itracker_DEBUGMEMORY_

#define _FILENAME_STRING_   __FILE__
#define _FUNCTIONNAME_STRING_  __FUNCTION__
#define _LINE_NUMBER_   __LINE__

#else

#define _FILENAME_STRING_   NULL
#define _FUNCTIONNAME_STRING_  NULL
#define _LINE_NUMBER_   0

#endif




#if defined _itrackerDebug_WIN32_ || defined _itrackerDebug_IOS_BLE_PIH_ 
    #include "stdlib.h"
    #define OslMalloc malloc
	#define OslMfree free
    #define _itrackerDebug_
	#define myPrintf  winPrintf   //to avoid error of printf NULL
	//#define directPrintf printf //if non embedded, some embedded will error while printf; so should define to nothing function
#endif
#if defined _itrackerDebug_MALLOC_
	#define directPrintf printf //if non embedded, some embedded will error while printf; so should define to nothing function
#endif
#if defined _PST_DEBUG_ || defined _itrackerDebug_EMBEDDED_BLE_PIH_

        //#define directPrintf printf //if non embedded, some embedded will error while printf; so should define to nothing function
        #define _itrackerDebug_  1
#if defined CC2541 || defined CC2540
        #include "MyUart.h"
        #define MACRO_PRINTF myUartPrintf
#endif
#if defined NORDIC_nRF52832_BROADCASTER_OBSERVER //defined in project options--Project Macros
        #include "nrf_log.h" //need this
        #include "nrf_log_backend_uart.h" //need this
        #define MACRO_PRINTF nrf_uart_print_String //NRF_LOG_INFO error
#endif
      //  #include "itrackerWinPrintf.h"
	//#define myPrintf myFormatPrintf
        #define myPrintf winPrintf
        //#define _PST_DEBUG_EVENTS_
#endif


#if defined _itrackerDebug_MTK_TERMINAL_
    #define _itrackerDebug_  1
    #include "itrackerString.h"
    #include "itrackerUartMTK.h"
	//#if defined WIN32
		#define myPrintf  winPrintf   //to avoid error of printf NULL
	//#else
		//#define myPrintf myDbg_print
	//#endif
#endif

#if (defined _itrackerDebug_JAVA_SERVER||defined _itrackerDebug_ANDROID_ ) && defined ITRACKER_JNI
    #define _itrackerDebug_  1
	#define FORMATCONTROLSTRINGLEN 2048
	#include "jni.h"
	extern void print_btp_log( const  char * fmt,...);//first setSbtp_log(SendingBTP * btp);
//	#include "androidCcallPihApi.h"//erro of SKETCH
//	#define myPrintf print_btp_log
	#define directPrintf print_btp_log //if non embedded, some embedded will error while printf; so should define to nothing function

#define myPrintf  winPrintf
#define MACRO_PRINTF print_btp_log
//	extern void print_chararray_btp_log( const uint8* memo,const uint8* chararray, uint16 length);
//	#define printCharArray  print_chararray_btp_log

//	#include <android/log.h>
//#include <cutils/log.h>
//for logger _android_log_write(ANDROID_LOG_WARN,"CmyDebug--BTP--","here is an example...\r\n")
//and _android_log_print(ANDROID_LOG_WARN,"CmyDebug--BTP--","here is an example...%d\r\n", temp)
//we should add LOCAL_LDLIBS +=-llog before include $(BUILD_SHARED_LIBRARY) in android.mk
#endif




#if (defined MTK_TERMINAL)
	#include "drv_comm.h"   //for dbg_print()
	#include "stack_ltlcom.h"  //for SEND_ILM
	#include "Kal_trace.h"//for catcher
	#include "mmi_frm_mem_gprot.h"   //for Oslmalloc() Oslmfree()
	#include "TimerEvents.h"  // for GIS_TIMER_ID_11
	#include "mmi_frm_timer_gprot.h"//startimer stoptimer
	#include "custom_mmi_default_value.h"  //for MYTIME
//	extern MYTIME  init_time;//not applib_time_struct and include "app_datetime.h"
//mtk modis will automatically define WIN32

	#define _PEDOMETER_ANALYSIS_BY_MMA9555_ 1
//	#define CA_EXPANSION_STATE  1
//	#define CA_EXPANSION_DIGIT  1
//	#define CA_EXPANSION_ANYINSTANCE  1
#endif

#if  defined  I2C_MASTER_LTP ||defined I2C_SLAVE_LTP ||defined VIRTUAL_LTP || defined EMBEDDED_BLE_PIH
#define CA_EXPANSION_STATE  1
#define CA_EXPANSION_DIGIT  1
//	#define CA_EXPANSION_ANYINSTANCE  1
//	#define CAU_EXPANSION_DISPOSE  1
//	#define CAU_EXPANSION_CAULENGTH_LIMITED_REPLACINGFIRST 100
//	#define CAU_EXPANSION_CAULENGTH_LIMITED_IGNORETHIS 100
#endif



#if defined NORDIC_nRF52832_BROADCASTER_OBSERVER
			  #define OslMalloc malloc
			  #define OslMfree free
#endif
//#if (defined EMBEDDED_BLE_PST || defined EMBEDDED_BLE_PIH)
			  //#define _C_BTP_CHANELS_  //in preprocessor
#if defined CC2541 || defined CC2540
                          #include "OSAL.h"
			  #define OslMalloc osal_mem_alloc
			  #define OslMfree osal_mem_free
#endif
#if defined CC2640
      extern void *ICall_heapMalloc( uint16 size);//cc2640
      extern void ICall_heapFree(void *blk);//cc2541
      #define OslMalloc ICall_heapMalloc
      #define OslMfree ICall_heapFree
#endif
//#endif

#if defined EMBEDDED_BLE_PIH
#define  I2C_SLAVE_LTP  1
#define CAU_EXPANSION_CAULENGTH_LIMITED_REPLACINGFIRST 100
#endif

#if (defined ANDROID_PLATFORM) || ( (defined IOS_PLATFORM) && !(defined EMBEDDED_BLE_PIH) ) || (defined VIRTUAL_BTP) || (defined VIRTUAL_LTP) || (defined ITRACKER_JNI )
	#define OslMalloc malloc
	#define OslMfree free
#endif
#if (defined ANDROID_BLE_PIH) || ( (defined IOS_BLE_PIH) && !(defined EMBEDDED_BLE_PIH) ) || (defined VIRTUAL_BTP) || (defined VIRTUAL_LTP) || (defined ITRACKER_JNI )
	#define _C_BTP_CHANELS_  1


#endif


#if (defined ANDROID_BLE_PIH) || (defined IOS_BLE_PIH) || (defined VIRTUAL_BTP)
	#define _PEDOMETER_ANALYSIS_BY_GSENSOR_  1

#endif


#if defined NUVOTON_MCU_MINI58
      #include "stdlib.h"
      	#define OslMalloc malloc
	#define OslMfree free
#endif
#if defined _itrackerDebug_NUVOTON_MCU_MINI58
#define _itrackerDebug_//FORMATSTRINGLEN in itrackerWinPrintf.h should be 100, if too large, will "In Hard Fault Handler r0  = 0xfffffff9 r1 " because stack is small
#include "stdio.h"  //for printf() to print into uart
#define MACRO_PRINTF printf 
#define directPrintf printf
#endif
      
      
      
#if defined _itrackerDebug_
//#include "itrackerWinPrintf.h" 
//extern void winPrintf(const char * fmt,...);  //point to itrackerWinPrintf.h
#define myPrintf  printf//winPrintf   //to avoid error of printf NULL; and can also debug into debugfile
//extern void general_win_print_fun( uint8* string );
//#define MACRO_PRINTF general_win_print_fun    //in itrackerDebugUtils.h;  if we use MACRO_PRINTF, donot use set_win_print_fun.
#endif


//all including the following~~~~~~~~~~~~~~~~~~~~


#define COMPARE_ERROR -1
#define COMPARE_SAME 0
#define COMPARE_DIFFERENT 1
#define COMPARE_CAPITALSAME 2  // same without capital cared

#define SWITCHING_ENABLE 1
#define SWITCHING_DISABLE 0
#define SWITCHING_START 1
#define SWITCHING_STOP 0
#define SWITCHING_HIGH 1
#define SWITCHING_LOW 0        
#define SWITCHING_ON 1
#define SWITCHING_OFF 0    



#include <stdio.h>  //for NULL
#include <stdlib.h>  //for malloc and free
#include <string.h>  //for memset
      typedef int (* my_print_fun_t )(const char* );
      typedef void (*Func_start) (void * arg);
    typedef int16 (*Func_start_I) (void * arg);
      #define FUNC_V_VP Func_start
	typedef void (*Func_V_V)();//parameter void, return void
	typedef unsigned char (*Func_UC_UC)(unsigned char); //parameter unsigned char , return unsigned char
	typedef void (*Func_UC_V)(unsigned char); //parameter unsigned char , return void
	typedef unsigned char (*Func_V_UC)(); //parameter void , return unsigned char
	typedef void (* SendOutCharArray_t)(  unsigned char * chararray , uint16 length );//send out one pcs
	typedef int16 (*Func_V_I)();

#if defined IOS_BLE_PIH || defined EMBEDDED_BLE_PIH
    typedef void (* ConnectPstFunc)(uint8 onoff); //0 is disconnect; 1 is connect
	typedef void (* SendJsonStrFunc)(uint8 tt,uint32 cn,uint8 * chararray,uint16 length);//terminalType/0, CN/CT, jsonstr, length
#endif

#if defined IOS_BLE_PIH || defined EMBEDDED_BLE_PIH  || defined MTK_TERMINAL //MTK_TERMINAL to parse data transfed from ble I2C or HCI
	typedef void (* SendObjectFunc)(uint8 tt,uint32 cn, void * obj);//terminalType/0, CN/CT, object
#endif



#define RESULT_of_SUCCESS 0
#define RESULT_of_PARAMETER_ERROR (-1)
#define RESULT_of_BUSY_ERROR (-2)
#define RESULT_of_SOCKET_ERROR (-3)
#define RESULT_of_HARDWARE_COMMUNICATION_ERROR (-4)  //-400 +?
#define RESULT_of_PTHREAD_ERROR (-5)
#define RESULT_of_FILEOPERATION_ERROR (-6)
#define RESULT_of_PERMISSION_ERROR (-7)  //-700 +?
#define RESULT_of_MEMORY_ERROR (-8)
#define RESULT_of_DEVICE_ERROR (-9)
#define RESULT_of_FAIL (-10)
#define RESULT_of_COMMAND_INVALID (-11)
#define RESULT_of_NO_OUTPUT (-12)
#define RESULT_of_SOFTWARE_GRAMMER_ERROR (-13)  //-1300 +?
#define RESULT_of_NUMBER_OVERFLOW (-14)
#define RESULT_of_DATA_ERROR (-15)
#define RESULT_of_DATA_TYPE_ERROR  (-16)
#define RESULT_of_STATE_ERROR  (-17)
#define RESULT_of_UNKNOWN_EXCEPTION (-100)



#define RESULT_of_SOCKET_CLOSED -30


#define RESULT_of_TARGET_DEVICE_LOCKED -90
#define RESULT_of_TARGET_DEVICE_ABSENCE -91
#define RESULT_of_BUFFER_LENGTH_NOT_ENOUGH -92
#define RESULT_of_TARGET_SIZE_ZERO -93

#define RESULT_of_NULL_DATA_ERROR -101
#define RESULT_of_NULL_POINTER_ERROR -102

#define RESULT_of_STATE_ERROR_EXISTED  (-170)

#define _PRINT_FULL_MYSELF_FUNC_   myPrintf("[%s],[%d],[%s]\r\n",__FILE__,__LINE__ ,__func__);
#define _PRINT_MYSELF_FUNC_       myPrintf("[%s]\r\n",__func__);


#endif /* ITRACKER88PLATFORM_H_ */
