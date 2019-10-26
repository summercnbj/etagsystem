/*
 * gwBleMasterCache.h
 *
 *  Created on: 2019年10月26日
 *      Author: summer
 */

#ifndef GWBLEMASTERCACHE_H_
#define GWBLEMASTERCACHE_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "nvramApi.h"

#include "commands.h"



extern int8 splitingToSend( uint8* etagMacBytes, uint8* package_ONBLE, uint32 package_length_ONBLE);


#endif /* GWBLEMASTERCACHE_H_ */
