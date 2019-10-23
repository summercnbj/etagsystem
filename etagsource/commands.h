/*
 * commands.h
 *
 *  Created on: 2019年10月22日
 *      Author: summer
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_


#define CMD_LENGTH 1
#define SUBCMD_LENGTH 1
#define SHORTPW_LENGTH 6
#define UUID_BYTE_LENGTH 42//42Bytes,前面6个事mac，后面填充0
#define MAC_BYTE_LENGTH 6


//~~~~~~~~~~~CMD_GW_HB~~~~~~~~~~~~~~~~
#define CMD_GW_HB 0x3e

#define BATTPERCENTAGE_LENGTH 1
#define MAC_HEXCHAR_LENGTH 12
#define BUSY_LENGTH 1
#define ISBUSY 1
#define NOTBUSY 0
#define GW_HBCORE_HEADER_LENGTH (CMD_LENGTH + UUID_BYTE_LENGTH + BATTPERCENTAGE_LENGTH + MAC_BYTE_LENGTH + BUSY_LENGTH)
#define FLOWNO_BYTE_LENGTH 2

//~~~~~~~~~~~CMD_GW_HB_FEEDBACK~~~~~~~~~~~~~~~~
#define CMD_GW_HB_FEEDBACK 0x3f
#define SUBCMD_GW_STATE 0x01

#define GW_HB_FEEDBACK_LENGTH 9

#define GW_RETURN_RATIO 10
#define GW_INTERVAL_at_HALFMINUTE 20




//~~~~~~~~~~~CMD_TAG_GW_HB_FEEDBACK~~~~~~~~~~~~~~~~
#define CMD_TAG_GW_HB_FEEDBACK 0x92
//#define ETAG_GW_HB_FEEDBACK_LENGTH 9+N




//~~~~~~~~~~~SUBCMD_GW_NEW_SHORTPW~~~~~~~~~~~~~~~~
#define SUBCMD_GW_NEW_SHORTPW 0x02
#define GW_NEW_SHOWRTPW_LENGTH 14





#define CMD_TAG_GW_HB_FEEDBACK 0x92








#endif /* COMMANDS_H_ */
