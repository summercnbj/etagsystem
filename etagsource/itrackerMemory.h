
#ifndef ITRACKERMEMORY_H_
#define ITRACKERMEMORY_H_
#include "itracker88basic.h"
#include "itracker88Platform.h"
//in itrackerMemory.c or itrackerMemoryWatcher.c, we cannot use myPrintf or winPrintf. we can only use printf in macro WIN32.
//if we use  myPrintf or winPrintf, it will lead to loop error, because  myPrintf or winPrintf are invoking memory module.

//if we should track memory leak in orther platform not WIN32,we should use other xxxprintf without memory module invoked! and included with its platform macro


extern void * myMalloc ( uint32 size,const char* filename,const char* functionname, uint32 linenumber ) ;

//api
extern void myFree(void *p);
//api over


//#define ITRACKER_MMU

#if defined ITRACKER_MMU
#include "itrackerMemoryWatcher.h"
#define MMU_QTY 64
typedef struct MemoryManagementUnit
{
	//int id;  //start from 1, not 0
	unsigned char allocState;  //1 allocated; 2 freed (8bit char)
	uint16 size;//int up to max 4G
	void * address;//void *

#if defined _itracker_DEBUGMEMORY_details_NOTFREED || defined _itracker_DEBUGMEMORY_details_FREED
	 unsigned char  filename[FILENAME_LEN];//to save __FUNCTION__ and __LINE__
	 uint32 linenumber;
#endif
} ItrackerMMU;


#endif//ITRACKER_MMU













#endif
