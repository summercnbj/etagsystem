/*
 * etagGwHb.h
 *
 *  Created on: 2019年10月23日
 *      Author: summer
 */

#ifndef GWWIFIETAGHB_H_
#define GWWIFIETAGHB_H_
#include "itracker88Platform.h"
#include "itrackerCharArray.h"
#include "cTools.h"
#include "commands.h"
#include "gwStateMachine.h"
#include "nvramApi.h"


/** 获得已经加密组装了流水号的ETAG GW心跳包，准备发送到云服务器
 * @shortPW 密码
 * @flowNo 云请求的流水号
 * @wifiMacBytes 长度为MAC_BYTE_LENGTH=6
 * @gwBattPercentage  gw电量百分比
 * @rootMacBytes 长度为MAC_BYTE_LENGTH
 * @rootMacBytes 路由器MAC
 * @etagHbOnUart_body 通过uart从蓝牙收到的包去掉CMD的尾巴，长度为TAG_HB_ONUART_LENGTH-1
 * @package_length 保存最终的字节总数
 * @return 心跳包; 或者  内存分配失败返回NULL
 * 心跳包总长度为package_length。
 *
 */
extern uint8* getGwWifiEtagHbPackage(uint8* shortPW, uint16 flowNo, uint8* wifiMacBytes,uint8 gwBattPercentage, uint8* rootMacBytes,uint8* etagHbOnUart_body,
		uint16 *package_length);


#endif /* GWWIFIETAGHB_H_ */
