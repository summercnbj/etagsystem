/*
 * gwBle.h
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef GWBLEPARSEUART_H_
#define GWBLEPARSEUART_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"


extern void parseUartPackage(uint8* package,uint16 package_length);

#endif /* GWBLEPARSEUART_H_ */
