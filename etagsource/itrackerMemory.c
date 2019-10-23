#include "itracker88Platform.h"
#include "itrackerMemory.h"
//#include "itrackerMemoryWatcher.h"
#include <stdlib.h>


#if defined ITRACKER_MMU
static volatile ItrackerMMU myMMU[ MMU_QTY ];

void* get_one_idle_mmu()
{
	int i =0;
	for( ;i< MMU_QTY; i++ )
	{
		if( (uint8)NOTFREEDMEMORY == myMMU[i].allocState )
			return (void*)&myMMU[i];
	}
	return NULL;
}

//get heap header from the system
void* get_heap_header()
{


	return NULL;
}

void* get_heap_tail()
{

	return NULL;
}

void mmu_fragmentless()
{




}


#endif//#if defined ITRACKER_MMU


void* get_real_memory(void* p )
{
#if defined ITRACKER_MMU
	ItrackerMMU* findit = NULL;
	if( NULL == p )
		return NULL;
	findit = (ItrackerMMU*)p;

	if( NOTFREEDMEMORY == findit->allocState )
	{
		return findit->address;
	}
	return NULL;
#else
	return p;
#endif//#if defined ITRACKER_MMU
}



//in itrackerMemory.c or itrackerMemoryWatcher.c, we cannot use myPrintf or winPrintf. we can only use printf in macro WIN32.
//if we use  myPrintf or winPrintf, it will lead to loop error, because  myPrintf or winPrintf are invoking memory module.

//if we should track memory leak in orther platform not WIN32,we should use other xxxprintf without memory module invoked! and included with its platform macro

//including memset
void * myMalloc (uint32 size,const char* filename, const char* functionname, uint32 linenumber )
{//size_t is int
#if defined ITRACKER_MMU

	void *p = NULL;
	int len=0;
	ItrackerMMU* findit =NULL;
	if(0 == size)
		return NULL;

	findit =(ItrackerMMU*)get_one_idle_mmu();
	if( NULL == findit )
		return NULL;

	p=(void *)OslMalloc(size);
	memset(p,0,size);
	if(NULL == p)
	{
#if defined WIN32
		//printf("no memory by malloc");
#endif
		return NULL;
	}

	findit->address = p;
	findit->size = size;
	findit->allocState = (uint8)NOTFREEDMEMORY; //allocated
	#ifdef _itracker_DEBUGMEMORY_
	#if defined _itracker_DEBUGMEMORY_details_NOTFREED || defined _itracker_DEBUGMEMORY_details_FREED
		if( filename )
		{
			len = strlen(filename);
			if( len >  (FILENAME_LEN-1) )
			{
				filename += len - (FILENAME_LEN-1);
				len =  (FILENAME_LEN-1);
			}

			memcpy( &(findit->filename[0]), filename, len );//to save __FILENAME__ and __LINE__
		}
		findit->linenumber = linenumber;
	#endif
	#endif

	return (void*)findit;


#else//#if defined ITRACKER_MMU
	void *p = NULL;
	if(0 == size)
		return NULL;

	p=(void *)OslMalloc(size);
#ifdef _itracker_DEBUGMEMORY_
	appendWatcherUnitWhenAlloc(p, size, (uint8*)filename,(uint8*)functionname ,linenumber );
#endif

	if(NULL == p)
	{
#if defined MFC_WIN32


#elif defined WIN32
		//printf("no memory by malloc");
#endif
		return NULL;
	}

	memset(p,0,size);//if size if too big, memset will not works

//	uint32 i;
//	for( i=0; i< size; i++)
//	{
//		*((uint8*)p) = 0;
//		p++;
//	}

	return p;
#endif//#if defined ITRACKER_MMU
}

void myFree(void *p)
{
#if defined ITRACKER_MMU
	ItrackerMMU* findit =NULL;
	if( NULL == p )
		return;
	findit = (ItrackerMMU*)p;

	findit->allocState = (uint8)FREEDMEMORY;
	OslMfree(findit->address);
	findit->address = NULL;
	findit->size =0;

#else//#if defined ITRACKER_MMU
	if(p!=NULL)
	{
#ifdef _itracker_DEBUGMEMORY_
		markWatcherUnitWhenFree(p );
#endif
		OslMfree(p);

	}

#endif//#if defined ITRACKER_MMU
}






