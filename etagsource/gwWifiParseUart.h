/*
 * gwWifiParseUart.h
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#ifndef GWWIFIPARSEUART_H_
#define GWWIFIPARSEUART_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"


extern void wifiParseUart(uint8* package, uint32 package_length );


#endif /* GWWIFIPARSEUART_H_ */
