/*
 * gwWifiParseGwHbFeedback.h
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef GWWIFIPARSEHBFEEDBACK_H_
#define GWWIFIPARSEHBFEEDBACK_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"
#include "etagStateMachine.h"




extern void parseHbFeedback(uint8* shortPW, uint8* hbFeedbackPackage, uint16 hbFeedbackPackage_length, uint8* myMacBytes);



#endif /* GWWIFIPARSEHBFEEDBACK_H_ */
