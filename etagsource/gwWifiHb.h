/*
 * gwWifi.h
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef GWWIFIHB_H_
#define GWWIFIHB_H_

#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "nvramApi.h"




/*
 * timer to do gwhb();
 * 要确保该timer一直生存。
 *
 */
extern void gwhb();


#endif /* GWWIFIHB_H_ */
