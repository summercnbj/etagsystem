/*
 * gwWifi2Uart.h
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#ifndef GWWIFI2UART_H_
#define GWWIFI2UART_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"


//固定长度。返回malloc，用完要释放myFree()
extern uint8* get_GW_NEW_SHORTPW_ONUART(uint8* newShortPW);

//长度为*package_length。返回malloc，用完要释放myFree()
extern uint8* get_ETAG_GW_HB_FEEDBACK_STATE_ONUART(uint8* etagMacBytes, uint8 etagState,uint8* FFCS_md5_16_bytes, uint8* fcssp, uint32 FCSSP_length,uint32 *package_length );


#endif /* GWWIFI2UART_H_ */
