/*
 * bleSplitting.h
 *
 *  Created on: 2019年10月27日
 *      Author: summer
 */

#ifndef BLESPLITTINGENCDEC_H_
#define BLESPLITTINGENCDEC_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "nvramApi.h"


/** TODO
 * 需要拆开后添加包头信息，确保能够组装起来。所以叫bleSplittingEncDec
 */

extern int8 splitingToSend( uint8* etagMacBytes, uint8* package_ONBLE, uint32 package_length_ONBLE);


#endif /* BLESPLITTINGENCDEC_H_ */
