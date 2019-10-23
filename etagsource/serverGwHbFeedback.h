/*
 * etagServerHbFeedback.h
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef SERVERGWHBFEEDBACK_H_
#define SERVERGWHBFEEDBACK_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"

extern uint8* getGwHbFeedbackStatePackage(uint8* shortPW, uint16 flowNo, uint8* uuidBytes, uint8 gwState,uint16 *package_length);


extern uint8* getGwHbFeedbackNewShortPWPackage(uint8* shortPW, uint16 flowNo, uint8* macBytes, uint8* newShortPW,uint16 *package_length);


#endif /* SERVERGWHBFEEDBACK_H_ */
