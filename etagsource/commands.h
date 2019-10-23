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
#define MD5_16_BYTE_LENGTH 8

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
#define STATE_LENGTH 1
#define GW_HB_FEEDBACK_LENGTH (CMD_LENGTH+SHORTPW_LENGTH+SUBCMD_LENGTH+STATE_LENGTH)//9

#define GW_RETURN_RATIO 10
#define GW_INTERVAL_at_HALFMINUTE 20



//~~~~~~~~~~~CMD_TAG_HB~~~~~~~~~~~~~~~~
#define CMD_TAG_HB  0x91
#define TAG_HB_LENGTH 21
#define PRODUCTMODEL_LENGTH_MAX 7


//~~~~~~~~~~~CMD_TAG_GW_HB~~~~~~~~~~~~~~~~
#define CMD_TAG_GW_HB 0x91
#define TAG_HB_LENGTH 21
#define TAG_HB_ADV_LENGTH 30
#define ADV_BYTEPOSITION_FOLLOWINGLENGTH 3
#define FOWLLOWINGLENGTH 0x19
#define ADV_BYTEPOSITION_VENDORMARK 5
#define VENDORMARK_0 'X'
#define VENDORMARK_1 'L'
#define VENDORMARK_2 'W'
#define ADV_BYTEPOSITION_CMD 8
#define ADV_BYTEPOSITION_OFFSETDATA 9
#define ADV_HEADER_LENGTH ADV_BYTEPOSITION_OFFSETDATA


#define TAG_HB_ONUART_LENGTH 27


//~~~~~~~~~~~CMD_TAG_GW_HB_FEEDBACK ONUART~~~~~~~~~~~~~~~~
#define CMD_TAG_GW_HB_FEEDBACK 0x92
//#define ETAG_GW_HB_FEEDBACK_LENGTH 9+N



//~~~~~~~~~~~CMD_TAG_GW_HB_FEEDBACK ONBLE~~~~~~~~~~~~~~~~
#define TAG_GW_HB_FEEDBACK_ONBLE_HEADER_LENGTH (CMD_LENGTH+SUBCMD_LENGTH+STATE_LENGTH)//9









//~~~~~~~~~~~SUBCMD_GW_NEW_SHORTPW~~~~~~~~~~~~~~~~
#define SUBCMD_GW_NEW_SHORTPW 0x02
#define GW_NEW_SHOWRTPW_LENGTH 14


//~~~~~~~~~~~CMD_GW_NEW_SHORTPW~~~~~~~~~~~~~~~~
#define CMD_GW_NEW_SHORTPW 0xc1
#define GW_NEW_SHORTPW_ONUART_LENGTH 7
#define PERIOD_for_FIND_NO_ETAG_min 30
#define BLESCAN_TYPE_HB 1
#define BLESCAN_TYPE_SENDNEWSHORTPW 2
#define GW_NEW_SHORTPW_ONBLE_LENGTH 7

#define CMD_TAG_GW_HB_FEEDBACK 0x92








#endif /* COMMANDS_H_ */
